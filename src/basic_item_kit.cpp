#include <basic_item_kit.hpp>

using namespace godot;


void BasicItemKit::_bind_methods() {

    ClassDB::bind_method(D_METHOD("get_gravity"), &BasicItemKit::get_gravity);
    ClassDB::bind_method(D_METHOD("set_gravity", "p_gravity"), &BasicItemKit::set_gravity);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "gravity"), "set_gravity", "get_gravity");
    
    ClassDB::bind_method(D_METHOD("get_damp"), &BasicItemKit::get_damp);
    ClassDB::bind_method(D_METHOD("set_damp", "p_damp"), &BasicItemKit::set_damp);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "damp"), "set_damp", "get_damp");
    
    ClassDB::bind_method(D_METHOD("get_magnet_strength"), &BasicItemKit::get_magnet_strength);
    ClassDB::bind_method(D_METHOD("set_magnet_strength", "p_magnet_strength"), &BasicItemKit::set_magnet_strength);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "magnet_strength"), "set_magnet_strength", "get_magnet_strength");

    };
 
Vector2 BasicItemKit::get_gravity() {
    return gravity;
}

double BasicItemKit::get_damp() {
    return damp;
}

double BasicItemKit::get_magnet_strength() {
    return magnet_strength;
}

void BasicItemKit::set_gravity(Vector2 value) {
    gravity = value;
}

void BasicItemKit::set_damp(double value) {
    damp = value;
}

void BasicItemKit::set_magnet_strength(double value) {
    magnet_strength = value;
}


    
void BasicItemPool::_custom_init(CanvasItem* canvas_parent, int set_index, Ref<BulletKit> kit, int pool_size, int z_index, Vector2 origin) {
    Ref<BasicItemKit> item_kit = (Ref<BasicItemKit>)kit;
	active_rect = item_kit->active_rect;
}


std::unique_ptr<BulletPool> BasicItemKit::_create_pool() {						
	return std::unique_ptr<BulletPool> (new BasicItemPool());					
}

bool BasicItemPool::_get_is_auto_collected(BulletID bullet_id) {
	int index = persistent_index[bullet_id.index];
	if (is_bullet_valid(bullet_id)) {
		return bullets[index]->is_auto_collected;
	}
	return false;
}



Array BasicItemPool::_collect_and_magnet(Vector2 pos, Node2D* target, double collect_radius, double magnet_radius) {
    Array collected_items = Array();

	double collect_radius_squared = collect_radius * collect_radius;
	double magnet_radius_squared = magnet_radius * magnet_radius;

	for (int i = pool_size - 1; i >= available_bullets; i--) {
		BasicItem* bullet = (BasicItem*)bullets[i];

		double b = bullet->scale * bullet->hitbox_scale;
		double b2 = b * b;

	 	double dist_sq = (bullet->position - pos).length_squared();
		
		if (dist_sq <= collect_radius_squared + 2.0 * magnet_radius * b + b2) {
			if (!bullets[i]->is_grazed) {
				bullet->is_grazed = true;
				bullet->is_magneted = true;
				bullet->magnet_target = target;
			}

			if (dist_sq <= collect_radius_squared + 2.0 * collect_radius * b + b2) {
				bullet->lifespan = -INFINITY;
                PackedInt64Array bullet_id = PackedInt64Array();
                bullet_id.resize(3);
                bullet_id.set(0, bullet->cycle);
                bullet_id.set(1, set_index);
                bullet_id.set(2, bullet->persistent_pool_index);
                collected_items.append(bullet_id);
			}
		}
	}
	return collected_items;
}


BulletID BasicItemPool::_create_item(Vector2 pos, double speed, double angle, double spin, PackedFloat64Array item_data) {
    available_bullets -= 1;
    active_bullets += 1;

    BasicItem* bullet = (BasicItem*)bullets[available_bullets];

    RID rid = bullet->item_rid;

    rendering_server->canvas_item_set_draw_index(rid, (draw_index++));
    bullet->draw_index = draw_index++;
    if (draw_index > 16777215) draw_index = 0; // 2^24
    
    _enable_bullet(bullet);
    Transform2D xform = Transform2D(0.0, Vector2(0.0, 0.0)).scaled(item_data[4] * Vector2(1.0, 1.0));
    if (speed != 0.0) {
        xform = xform.rotated(Math_TAU * (float)rand() / (float)RAND_MAX);
    } else {
        bullet->fade_timer = -1.0;
    }
    xform.set_origin(pos);

    bullet->transform = xform;
    bullet->position = pos;
    bullet->scale = item_data[4];
    bullet->angle = angle;
    bullet->direction = Vector2(1.0, 0.0).rotated(angle);

    rendering_server->canvas_item_set_transform(rid, xform);

    bullet->speed = speed;
    bullet->spin = spin;
    
    Color compressed_data = Color();
    compressed_data.r = item_data[1] + item_data[0] / kit->texture_width;
    compressed_data.g = item_data[3] + item_data[2] / kit->texture_width;
    compressed_data.b = 0.0;
    compressed_data.a = floor(item_data[7]) + animation_random;

    bullet->bullet_data = compressed_data;
    bullet->hitbox_scale = item_data[5];

    bullet->layer = item_data[8];
    rendering_server->canvas_item_set_draw_index(rid, (bullet->layer << 24) + bullet->draw_index);
    rendering_server->canvas_item_set_modulate(bullet->item_rid, compressed_data);


    return BulletID(bullet->cycle, set_index, bullet->persistent_pool_index);
}

void BasicItemPool::_enable_bullet(BasicItem* bullet) {
    // Reset some bullet variables that are not set by the create_bullet functions
    bullet->is_grazed = false;
    bullet->is_magneted = false;
    bullet->is_auto_collected = false;
    bullet->fading = false;
    bullet->layer = 0;
    bullet->lifetime = 0.0;
    bullet->lifespan = INFINITY;
    bullet->hitbox_scale = 1.0;
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


void BasicItemPool::_magnet_all(Node2D* target) {
    for (int i = pool_size - 1; i >= available_bullets; i--) {
		BasicItem* bullet = (BasicItem*)bullets[i];
        bullet->is_grazed = true;
        bullet->is_magneted = true;
        bullet->is_auto_collected = true;
        bullet->magnet_target = target;
    }
}

bool BasicItemPool::_process_bullet(BasicItem* bullet, double delta) {
    Vector2 last_pos = bullet->position;
    if (bullet->fade_timer) {
        bullet->fade_timer -= delta;
        bullet->position += bullet->speed * bullet->direction * delta;
        if (delta == 1.0) {
            bullet->speed *= kit->damp;
        } else {
            bullet->speed *= powf(kit->damp, delta);
        }
        Transform2D xform = bullet->transform.rotated(bullet->spin);
        if (bullet->fade_timer <= 0.0) {
            bullet->fade_timer = 0.0;
            xform = xform.rotated(-xform.get_rotation());
        }
        xform.set_origin(bullet->position);
        bullet->transform = xform;

    } else if (bullet->is_magneted) {
        if (bullet->fade_timer) {
            bullet->fade_timer = 0.0;
            bullet->transform = bullet->transform.rotated(-bullet->transform.get_rotation());
        }
        Node2D *node = bullet->magnet_target;

        double angle = ((Vector2)node->get_position()).angle_to_point(bullet->position);
        bullet->position -= Vector2(kit->magnet_strength * delta, 0.0).rotated(angle);

    } else {
        bullet->position += kit->gravity * delta;

    }

    // If above the top of the screen, show an arrow instead. 
    // This is marked by setting the b channel in the item data to 1
    if (bullet->position.y < bullet->scale * -0.5) { 
        Vector2 pos = bullet->position;
        pos.y = bullet->scale * 0.5;
        bullet->transform = bullet->transform.rotated(-bullet->transform.get_rotation());
        bullet->transform.set_origin(pos);
        Color color = bullet->bullet_data;
        color.b = 1.0;
        rendering_server->canvas_item_set_modulate(bullet->item_rid, color);

    } else { 
        if (last_pos.y < bullet->scale * -0.5) {
            Color color = bullet->bullet_data;
            rendering_server->canvas_item_set_modulate(bullet->item_rid, color);
        }
        bullet->transform.set_origin(bullet->position);

    }
    
    if(!active_rect.has_point(bullet->position) || bullet->lifetime >= bullet->lifespan) {
        return true;
    }

    // Bullet is still alive, increase its lifetime.
    bullet->lifetime += delta;
    // Return false if the bullet should not be deleted yet.
    return false;
}


