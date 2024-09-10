#ifndef BASIC_BULLET_KIT_H
#define BASIC_BULLET_KIT_H

#include <bullet_kit.hpp>

#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/rendering_server.hpp>

namespace godot {

class BasicBulletKit;

// Bullet pool definition.
class BasicBulletPool : public AbstractBulletPool<BasicBulletKit, Bullet> {

	// void _init_bullet(Bullet* bullet); Use default implementation.
    public:

	void _enable_bullet(Bullet* bullet);
	// void _disable_bullet(Bullet* bullet); Use default implementation.
	bool _process_bullet(Bullet* bullet, double delta);

    void _process_A1(Bullet* bullet, double delta);
    void _process_A2(Bullet* bullet, double delta);
    int _process_A3_A(Bullet* bullet, double delta);
    int _process_A3_B(Bullet* bullet, double delta);

    // void _init_shot_A1(Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool fade_in);

};


// Bullet kit definition.
class BasicBulletKit : public BulletKit {
	GDCLASS(BasicBulletKit, BulletKit)
    public:
	std::unique_ptr<BulletPool> _create_pool() override;
	// BULLET_KIT(BasicBulletPool)

    static void _bind_methods() {};
};

// std::unique_ptr<BulletPool> BasicBulletKit::_create_pool() {						
// 	return std::unique_ptr<BulletPool> (new BasicBulletKit());						
// }																										
			


std::unique_ptr<BulletPool> BasicBulletKit::_create_pool() {						
	return std::unique_ptr<BulletPool> (new BasicBulletPool());					
}


void BasicBulletPool::_enable_bullet(Bullet* bullet) {
    // Reset some bullet variables that are not set by the create_bullet functions
    bullet->auto_delete = true;
    bullet->process_mode = A1;
    bullet->grazed = false;
    bullet->layer = 0;
    bullet->lifetime = 0.0;
    bullet->lifespan = INFINITY;
    bullet->wvel = 0.0;
    bullet->max_wvel = 0.0;
    bullet->waccel = 0.0;
    bullet->rotation = 0.0;
    bullet->fade_delete = false;
    bullet->fading = false;
    bullet->bounce_count = 0;
    bullet->bounce_surfaces = 0b1100;
    bullet->patterns.clear();
    Rect2 texture_rect = Rect2(-0.5f, -0.5f, 1.0, 1.0);
    RID texture_rid = kit->texture->get_rid();
    
    bullet->fade_time = kit->fade_time;
    bullet->fade_timer = kit->fade_time;

    // Configure the bullet to draw the kit texture each frame.
    rendering_server->canvas_item_add_texture_rect(bullet->item_rid,
        texture_rect,
        texture_rid);
}


bool BasicBulletPool::_process_bullet(Bullet* bullet, double delta) {
    // Vector2 origin = bullet->transform.get_origin();
	Vector2 origin = bullet->position;

    int bounce_count = 0;

    if (bullet->process_mode < B1) {
        if (bullet->process_mode == A1) _process_A1(bullet, delta);
        else if (bullet->process_mode == A2) _process_A2(bullet, delta);
        else bounce_count = _process_A3_A(bullet, delta);
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
            // what type of pattern is this?
            int type = (int)pattern[1];
            switch (type) {
                case 0: { // Set value
                    Dictionary properties = (Dictionary)pattern[3];
                    Array keys = properties.keys();
                    for(int32_t i = 0; i < keys.size(); i++) {
                        bullet->set(keys[i], properties[keys[i]]);
                    }
                    break;
                }
                    
                case 1: { // Add value
                    Dictionary properties = (Dictionary)pattern[3];
                    Array keys = properties.keys();
                    for(int32_t i = 0; i < keys.size(); i++) {
                        switch (properties[keys[i]].get_type()) {
                            case (Variant::FLOAT):
                                bullet->set(keys[i], (double)bullet->get(keys[i]) + (double)properties[keys[i]]);
                                break;
                            case (Variant::VECTOR2):
                                bullet->set(keys[i], (Vector2)bullet->get(keys[i]) + (Vector2)properties[keys[i]]);
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                }

                case 2: { // Multiply value
                    Dictionary properties = (Dictionary)pattern[3];
                    Array keys = properties.keys();
                    for(int32_t i = 0; i < keys.size(); i++) {
                        switch (properties[keys[i]].get_type()) {
                            case (Variant::FLOAT):
                                bullet->set(keys[i], (double)bullet->get(keys[i]) * (double)properties[keys[i]]);
                                break;
                            case (Variant::VECTOR2): {
                                Vector2 f = (Vector2)properties[keys[i]];
                                Vector2 v = (Vector2)bullet->get(keys[i]);
                                bullet->set(keys[i], Vector2(f.x * v.x, f.y * v.y));
                                break;
                                }
                            default:
                                break;
                        }
                    }
                    break;
                }
                
                case 3: { // aim at point
                    Vector2 point = (Vector2)pattern[3];
                    bullet->angle = (point).angle_to_point(bullet->position);
                    break;
                }

                case 4: { // aim at object
                    // Node2D *node = (Node2D*)pattern[3];
                    // int instance_id = (int)pattern[4];
                    // if (core_1_1_api->godot_is_instance_valid(core_1_2_api->godot_instance_from_id(instance_id))) {
                    //     bullet->angle = ((Vector2)node->get_position()).angle_to_point(bullet->position);
                    // }
                    break;
                }

                case 5: { // go to object
                    // Node2D *node = (Node2D*)pattern[3];
                    // int instance_id = (int)pattern[4];
                    // if (core_1_1_api->godot_is_instance_valid(core_1_2_api->godot_instance_from_id(instance_id))) {
                    //     bullet->position = node->get_position();
                    // }
                    break;
                }

                case 6: { // change bullet type
                    bullet->bullet_data = (Color)pattern[3];
                    bullet->scale = (double)pattern[4];
                    bullet->hitbox_scale = (double)pattern[5];
                    bullet->texture_offset = (double)pattern[6];
                    bullet->spin = (double)pattern[7];
                    bullet->layer = (int)pattern[8];

                    Color color = bullet->bullet_data;
                    color.b = bullet->texture_offset;
                    // Flag for if the bullet should fade in when changing types
                    if (pattern[9]) {
                        bullet->fade_timer = bullet->fade_time * 0.99999f;
                        color.b += bullet->fade_timer / bullet->fade_time;
                        // PhysicsServer2D::get_singleton()->area_set_shape_disabled(shared_area, bullet->shape_index, true);
                    }
                    rendering_server->canvas_item_set_modulate(bullet->item_rid, color);
                    break;
                }

                default:
                    break;
            }
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

void BasicBulletPool::_process_A1(Bullet* bullet, double delta) {
    bullet->position += bullet->direction * bullet->speed * delta;
    bullet->transform.set_origin(bullet->position);
    // bullet->hitbox_transform.set_origin(bullet->position);
}

void BasicBulletPool::_process_A2(Bullet* bullet, double delta) {
    if (bullet->wvel) {
        bullet->direction = bullet->direction.rotated(bullet->wvel * delta);
        bullet->angle += bullet->wvel * delta;
        bullet->transform = bullet->transform.rotated(bullet->wvel * delta);
    }

    if (bullet->accel && bullet->speed != bullet->max_speed) {
        bullet->speed += bullet->accel * delta;
        if (((bullet->speed - bullet->max_speed) * bullet->accel) > 0.0) bullet->speed = bullet->max_speed;
    }

    _process_A1(bullet, delta);
}

int BasicBulletPool::_process_A3_A(Bullet* bullet, double delta) {
    if (bullet->waccel && bullet->wvel != bullet->max_wvel) {
        bullet->wvel += bullet->waccel * delta;
        if (((bullet->wvel - bullet->max_wvel) * bullet->waccel) > 0.0) bullet->wvel = bullet->max_wvel;
    }
    _process_A2(bullet, delta);

    return _process_A3_B(bullet, delta);
}

int BasicBulletPool::_process_A3_B(Bullet* bullet, double delta) {

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

// void BasicBulletPool::_init_shot_A1(Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool fade_in) {

// }





};



#endif