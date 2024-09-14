#include <basic_bullet_kit.hpp>

// #include <godot_cpp/variant/color.hpp>

using namespace godot;


void BasicBulletKit::_bind_methods() {};

std::unique_ptr<BulletPool> BasicBulletKit::_create_pool() {						
	return std::unique_ptr<BulletPool> (new BasicBulletPool());					
}

    
void BasicBulletPool::_custom_init(CanvasItem* canvas_parent, int set_index, Ref<BulletKit> kit, int pool_size, int z_index, Vector2 origin) {
    Ref<BasicBulletKit> bullet_kit = (Ref<BasicBulletKit>)kit;
	active_rect = bullet_kit->active_rect;
	bounce_rect = bullet_kit->bounce_rect;
	warp_rect = bullet_kit->warp_rect;
}


BulletID BasicBulletPool::_create_shot_a1(Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool fade_in) {
    available_bullets -= 1;
    active_bullets += 1;

    BasicBullet* bullet = (BasicBullet*)bullets[available_bullets];

    RID rid = bullet->item_rid;

    rendering_server->canvas_item_set_draw_index(rid, (draw_index++));
    bullet->draw_index = draw_index++;
    if (draw_index > 16777215) draw_index = 0; // 2^24
    
    _enable_bullet(bullet);

    bullet->process_mode = A1;

    // A1 type settings
    Transform2D xform = Transform2D(0.0, Vector2(0.0, 0.0)).scaled(bullet_data[4] * Vector2(1.0, 1.0)).rotated(angle + 1.57079632679);
    xform.set_origin(pos);
    bullet->transform = xform;
    bullet->position = pos;
    bullet->scale = bullet_data[4];
    bullet->angle = angle;
    bullet->direction = Vector2(1.0, 0.0).rotated(angle);

    rendering_server->canvas_item_set_transform(rid, xform);

    Color compressed_data = Color();
    compressed_data.r = bullet_data[1] + bullet_data[0] / kit->texture_width;
    compressed_data.g = bullet_data[3] + bullet_data[2] / kit->texture_width;
    compressed_data.b = floor(bullet_data[6]); // Flooring for safety as it *must* be an integer and user could unknowingly have it not be.
    compressed_data.a = floor(bullet_data[7]) + animation_random;

    if (fade_in) {
        compressed_data.b += 0.9999999;
    } else {
        bullet->fade_timer = -0.000000000001;
    }

    bullet->speed = speed;

    bullet->texture_offset = floor(bullet_data[6]);
    bullet->bullet_data = compressed_data;
    rendering_server->canvas_item_set_modulate(rid, compressed_data);
    bullet->hitbox_scale = bullet_data[5];
    bullet->spin = bullet_data[8];
    bullet->layer = bullet_data[9];
    rendering_server->canvas_item_set_draw_index(rid, (bullet->layer << 24) + bullet->draw_index);
            
    Color fade_color = Color(bullet_data[10], bullet_data[11], bullet_data[12]);
    bullet->fade_color = fade_color;
        
    
    

    return BulletID(bullet->cycle, set_index, bullet->persistent_pool_index);
	
}

Array BasicBulletPool::_collide_and_graze(Vector2 pos, double hitbox_radius, double graze_radius) {
    Array collisions_and_graze = Array();
    collisions_and_graze.resize(2);
    Array collisions = Array();
    Array grazes = Array();
    collisions_and_graze[0] = collisions;
    collisions_and_graze[1] = grazes;


	double hitbox_radius_squared = hitbox_radius * hitbox_radius;
	double graze_radius_squared = graze_radius * graze_radius;

	for (int i = pool_size - 1; i >= available_bullets; i--) {
		BasicBullet* bullet = bullets[i];

		double b = bullet->scale * bullet->hitbox_scale;
		double b2 = b * b;

	 	double dist_sq = (bullet->position - pos).length_squared();
		
		if (bullet->fade_timer <= 0.0 && dist_sq <= graze_radius_squared + 2.0 * graze_radius * b + b2) {
            PackedInt64Array bullet_id = PackedInt64Array();
            bullet_id.resize(3);
            bullet_id.set(0, bullets[i]->cycle);
            bullet_id.set(1, set_index);
            bullet_id.set(2, bullets[i]->persistent_pool_index);

			if (!bullets[i]->is_grazed) {
				bullets[i]->is_grazed = true;
                ((Array)collisions_and_graze[1]).append(bullet_id);
			}

			if (dist_sq <= hitbox_radius_squared + 2.0 * hitbox_radius * b + b2) {
				bullets[i]->lifespan = -INFINITY;
                ((Array)collisions_and_graze[0]).append(bullet_id);
			}
		}
	}
	return collisions_and_graze;
}


void BasicBulletPool::_enable_bullet(BasicBullet* bullet) {
    // Reset some bullet variables that are not set by the create_bullet functions
    bullet->auto_delete = true;
    // bullet->process_mode = A1;
    bullet->is_grazed = false;
    bullet->layer = 0;
    bullet->lifetime = 0.0;
    bullet->lifespan = INFINITY;
    // bullet->wvel = 0.0;
    // bullet->max_wvel = 0.0;
    // bullet->waccel = 0.0;
    bullet->rotation = 0.0;
    bullet->fade_delete = false;
    bullet->fading = false;
    // bullet->bounce_count = 0;
    // bullet->bounce_surfaces = 0b1100;
    bullet->patterns.clear();
    bullet->custom_data.clear();
    Rect2 texture_rect = Rect2(-0.5, -0.5, 1.0, 1.0);
    RID texture_rid = kit->texture->get_rid();
    
    bullet->fade_time = kit->fade_time;
    bullet->fade_timer = kit->fade_time;

    // Configure the bullet to draw the kit texture each frame.
    rendering_server->canvas_item_add_texture_rect(bullet->item_rid,
        texture_rect,
        texture_rid);
}


bool BasicBulletPool::_process_bullet(BasicBullet* bullet, double delta) {
    // Vector2 origin = bullet->transform.get_origin();
	Vector2 origin = bullet->position;

    int bounce_count = 0;

    if (bullet->process_mode < B1) {
        if (bullet->process_mode == A1) _process_a1(bullet, delta);
        else if (bullet->process_mode == A2) _process_a2(bullet, delta);
        else bounce_count = _process_a3_before(bullet, delta);
    }
    if (bullet->spin) {
        bullet->transform = bullet->transform.rotated(bullet->spin * delta);
        bullet->rotation += bullet->spin * delta;
    }

    // Decrease fade-in timer
    if (bullet->fade_timer) {
        bullet->fade_timer -= delta;

        if (!bullet->fading) {
            if (bullet->fade_timer < 0.0) {
                bullet->fade_timer = 0.0;
                bullet->bullet_data.b = bullet->texture_offset;
                rendering_server->canvas_item_set_modulate(bullet->item_rid, bullet->bullet_data);
            } else {
                Color color = bullet->bullet_data;
                color.b = bullet->texture_offset + bullet->fade_timer / bullet->fade_time;
                rendering_server->canvas_item_set_modulate(bullet->item_rid, color);
            }
        } else {
            if (bullet->fade_timer <= 0.0) {
                bullet->fade_timer = 0.0;
            }
            Color color = bullet->bullet_data;
            color.b = -(bullet->texture_offset + 1.0 - bullet->fade_timer / bullet->fade_time);
            rendering_server->canvas_item_set_modulate(bullet->item_rid, color);
        }
    }

    // Auto delete conditions, outside bounds or lifespan depleted
    if((!active_rect.has_point(bullet->position) && bullet->auto_delete) || bullet->lifetime >= bullet->lifespan) {
        // If it should be deleted now 
        if (!bullet->fade_delete || (bullet->fade_timer <= 0.0 && bullet->fading)) {
            return true;
        } else if (!bullet->fading) {
            // Start fading and disable collision
            bullet->fading = true;
            bullet->fade_timer = bullet->fade_time;
            // PhysicsServer2D::get_singleton()->area_set_shape_disabled(shared_area, bullet->shape_index, true);
        }
    }


    // Iterate over existing transformations
    bool pattern_applied = false;
    int j = 0;
    for (int i = 0; i < bullet->patterns.size(); i++) {
        Array pattern = bullet->patterns[i]; // trigger, type, time, properties
        bool should_apply = false;
        int trigger = pattern[0];
        
        // Check if the conditions are met
        switch (trigger) {
            case 0: // Time
                pattern[2] = (double)pattern[2] - delta;
                if ((double)pattern[2] <= 0.0) {
                    should_apply = true;
                    pattern_applied = true;
                    pattern[2] = 0.0;
                } else {
                    bullet->patterns[j] = pattern;
                    j++;
                }
                break;
            case 1: // Bounce
                pattern[2] = (int)pattern[2] - bounce_count;
                if ((int)pattern[2] <= 0) {
                    should_apply = true;
                    pattern_applied = true;
                    pattern[2] = 0;
                } else {
                    bullet->patterns[j] = pattern;
                    j++;
                }
                break;
        }

        if (should_apply) {
            
        }
    }

    // Update position and other data if a transformation has been made
    if (pattern_applied) {
        
        bullet->patterns.resize(j);

        bullet->direction = Vector2(1.0, 0.0).rotated(bullet->angle);
        //bullet->transform.set_rotation(bullet->angle);
        bullet->transform = bullet->transform.scaled((bullet->scale / bullet->transform.get_scale().x) * Vector2(1.0, 1.0)).rotated(bullet->angle - bullet->transform.get_rotation() + rotation_offset + bullet->rotation);
        bullet->transform.set_origin(bullet->position);
        rendering_server->canvas_item_set_draw_index(bullet->item_rid, (bullet->layer << 24) + bullet->draw_index);
    }


    // Bullet is still alive, increase its lifetime.
    bullet->lifetime += delta;
    // Return false if the bullet should not be deleted yet.
    return false;
}

void BasicBulletPool::_process_a1(BasicBullet* bullet, double delta) {
    bullet->position += bullet->direction * bullet->speed * delta;
    bullet->transform.set_origin(bullet->position);
    // bullet->hitbox_transform.set_origin(bullet->position);
}

void BasicBulletPool::_process_a2(BasicBullet* bullet, double delta) {
    if (bullet->wvel) {
        bullet->direction = bullet->direction.rotated(bullet->wvel * delta);
        bullet->angle += bullet->wvel * delta;
        bullet->transform = bullet->transform.rotated(bullet->wvel * delta);
    }

    if (bullet->accel && bullet->speed != bullet->max_speed) {
        bullet->speed += bullet->accel * delta;
        if (((bullet->speed - bullet->max_speed) * bullet->accel) > 0.0) bullet->speed = bullet->max_speed;
    }

    _process_a1(bullet, delta);
}

int BasicBulletPool::_process_a3_before(BasicBullet* bullet, double delta) {
    if (bullet->waccel && bullet->wvel != bullet->max_wvel) {
        bullet->wvel += bullet->waccel * delta;
        if (((bullet->wvel - bullet->max_wvel) * bullet->waccel) > 0.0) bullet->wvel = bullet->max_wvel;
    }
    _process_a2(bullet, delta);

    return _process_a3_after(bullet, delta);
}

int BasicBulletPool::_process_a3_after(BasicBullet* bullet, double delta) {

    int bounce_count = 0;

    int bounce_mode = bullet->bounce_mode;

	bool vertical_bounced = false;
	bool horizontal_bounced = false;

    // Bullet bounce
    if (bullet->bounce_count > 0) {
        // Top
        if (((bullet->bounce_surfaces & 0b0001) == 0b0001) && bullet->position.y < bounce_rect.position.y) {
            vertical_bounced = true;
            if (bounce_mode == 0) bullet->position.y = bounce_rect.position.y + (bounce_rect.position.y - bullet->position.y);
            else bullet->position.y += bounce_rect.size.y;
        }
        // Bottom
        else if (((bullet->bounce_surfaces & 0b0010) == 0b0010) && (bullet->position.y > (bounce_rect.position.y + bounce_rect.size.y))) {
            vertical_bounced = true;
            if (bounce_mode == 0) bullet->position.y = bounce_rect.position.y + bounce_rect.size.y + (bounce_rect.position.y + bounce_rect.size.y - bullet->position.y);
            else bullet->position.y -= bounce_rect.size.y;
        }
        if (vertical_bounced) {
            bounce_count += 1;
            bullet->bounce_count -= 1;
            if (bounce_mode == 0) {
                bullet->angle *= -1.0;
                bullet->direction.y *= -1.0;
                bullet->transform = bullet->transform.rotated(bullet->angle * 2.0);
            }
            // bullet->transform.set_origin(bullet->position);
        }
    }
    if (bullet->bounce_count > 0) {
        // Left
        if (((bullet->bounce_surfaces & 0b0100) == 0b0100) && bullet->position.x < bounce_rect.position.x) {
            horizontal_bounced = true;
            if (bounce_mode == 0) bullet->position.x = bounce_rect.position.x + (bounce_rect.position.x - bullet->position.x);
            else bullet->position.x += bounce_rect.size.x;
        }
        // Right
        else if (((bullet->bounce_surfaces & 0b1000) == 0b1000) && (bullet->position.x > (bounce_rect.position.x + bounce_rect.size.x))) {
            horizontal_bounced = true;
            if (bounce_mode == 0) bullet->position.x = bounce_rect.position.x + bounce_rect.size.x + (bounce_rect.position.x + bounce_rect.size.x - bullet->position.x);
            else bullet->position.x -= bounce_rect.size.x;
        }
        if (horizontal_bounced) {
            bounce_count += 1;
            bullet->bounce_count -= 1;
            if (bounce_mode == 0) {
                bullet->angle = Math_PI - bullet->angle;
                bullet->direction.x *= -1.0;
                bullet->transform = bullet->transform.rotated(-Math_PI + bullet->angle * 2.0);
            }
        }
    }

	if (vertical_bounced || horizontal_bounced) {
		bullet->transform.set_origin(bullet->position);
		// bullet->hitbox_transform.set_origin(bullet->position);
	}

    return bounce_count;
}

// void BasicBulletPool::_create_shot_A1(Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool fade_in) {

// }



