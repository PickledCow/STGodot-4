#ifndef BASIC_ITEM_KIT_H
#define BASIC_ITEM_KIT_H

#include <bullet_kit.hpp>

#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/rendering_server.hpp>

namespace godot {

class BasicItemKit;

// Bullet pool definition.
class BasicItemPool : public AbstractBulletPool<BasicItemKit, Bullet> {

	// void _init_bullet(Bullet* bullet); Use default implementation.
    public:

	void _enable_bullet(Bullet* bullet);
	// void _disable_bullet(Bullet* bullet); Use default implementation.
	bool _process_bullet(Bullet* bullet, double delta);


    // void _init_shot_A1(Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool fade_in);

};


// Bullet kit definition.
class BasicItemKit : public BulletKit {
	GDCLASS(BasicItemKit, BulletKit)
    public:
	// Vector of what directions items naturally fall at. 
	Vector2 gravity = Vector2();
	double damp = 0.95;
	//float spin = 1.0f;
    double magnet_strength = 10.0;

	std::unique_ptr<BulletPool> _create_pool() override;
	// BULLET_KIT(BasicItemPool)

    static void _bind_methods() {};
};

// std::unique_ptr<BulletPool> BasicItemKit::_create_pool() {						
// 	return std::unique_ptr<BulletPool> (new BasicItemKit());						
// }																										
			


std::unique_ptr<BulletPool> BasicItemKit::_create_pool() {						
	return std::unique_ptr<BulletPool> (new BasicItemPool());					
}


void BasicItemPool::_enable_bullet(Bullet* bullet) {
		// Reset some bullet variables that are not set by the create_bullet functions
		bullet->grazed = false;
		bullet->fading = false;
		bullet->magnet_id = 0;
		bullet->layer = 0;
		bullet->lifetime = 0.0f;
		bullet->lifespan = INFINITY;
        bullet->hitbox_scale = 1.0f;
		Rect2 texture_rect = Rect2(-0.5f, -0.5f, 1.0f, 1.0f);
		RID texture_rid = kit->texture->get_rid();
		
		bullet->fade_time = kit->fade_time;
		bullet->fade_timer = kit->fade_time;
    
    bullet->fade_time = kit->fade_time;
    bullet->fade_timer = kit->fade_time;

    // Configure the bullet to draw the kit texture each frame.
    rendering_server->canvas_item_add_texture_rect(bullet->item_rid,
        texture_rect,
        texture_rid);
}


bool BasicItemPool::_process_bullet(Bullet* bullet, double delta) {
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
        if (bullet->fade_timer <= 0.0f) {
            bullet->fade_timer = 0.0f;
            xform = xform.rotated(-xform.get_rotation());
        }
        xform.set_origin(bullet->position);
        bullet->transform = xform;
    } else if (bullet->magnet_id) {
        if (bullet->fade_timer) {
            bullet->fade_timer = 0.0f;
            bullet->transform = bullet->transform.rotated(-bullet->transform.get_rotation());
        }
        Node2D *node = bullet->magnet_target;

        // DANGER: MUST EXIST

        // godot_int instance_id = bullet->magnet_id;
        // if (core_1_1_api->godot_is_instance_valid(core_1_2_api->godot_instance_from_id(instance_id))) {
        //     float angle = ((Vector2)node->get_position()).angle_to_point(bullet->position);
        //     bullet->position += Vector2(kit->magnet_strength * delta, 0.0f).rotated(angle);
        // }
        
        double angle = ((Vector2)node->get_position()).angle_to_point(bullet->position);
        bullet->position += Vector2(kit->magnet_strength * delta, 0.0f).rotated(angle);
    } else {
        bullet->position += kit->gravity * delta;
    }
    if (bullet->position.y < bullet->scale * -0.5f) {
        Vector2 pos = bullet->position;
        pos.y = bullet->scale * 0.5f;
        bullet->transform = bullet->transform.rotated(-bullet->transform.get_rotation());
        bullet->transform.set_origin(pos);
        Color color = bullet->bullet_data;
        color.b = 1.0f;
        rendering_server->canvas_item_set_modulate(bullet->item_rid, color);
    } else { 
        if (last_pos.y < bullet->scale * -0.5f) {
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



};



#endif