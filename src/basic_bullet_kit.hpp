#ifndef BASIC_BULLET_KIT_H
#define BASIC_BULLET_KIT_H

#include <collision_bullet_kit.hpp>

#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/rendering_server.hpp>

namespace godot {

class BasicBulletKit;

// Bullet pool definition.
class BasicBulletPool : public AbstractBulletPool<BasicBulletKit, BasicBullet> {

	// void _init_bullet(Bullet* bullet); Use default implementation.
    public:
    
	void _custom_init(CanvasItem* canvas_parent, int set_index, Ref<BulletKit> kit, int pool_size, int z_index, Vector2 origin);

	void _enable_bullet(BasicBullet* bullet);
	// void _disable_bullet(Bullet* bullet); Use default implementation.
	bool _process_bullet(BasicBullet* bullet, double delta);

    void _process_a1(BasicBullet* bullet, double delta);
    void _process_a2(BasicBullet* bullet, double delta);
    int _process_a3_before(BasicBullet* bullet, double delta);
    int _process_a3_after(BasicBullet* bullet, double delta);


	Array _collide_and_graze(Vector2 pos, double hitbox_radius, double graze_radius); 

    BulletID _create_shot_a1(Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool fade_in);

    BulletID _create_shot_a2(Vector2 pos, double speed, double angle, double accel, double max_speed, PackedFloat64Array bullet_data, bool fade_in);


};


// Bullet kit definition.
class BasicBulletKit : public CollisionBulletKit {
	GDCLASS(BasicBulletKit, CollisionBulletKit)
    public:
	std::unique_ptr<BulletPool> _create_pool() override;
	// BULLET_KIT(BasicBulletPool)

    static void _bind_methods();
};

// std::unique_ptr<BulletPool> BasicBulletKit::_create_pool() {						
// 	return std::unique_ptr<BulletPool> (new BasicBulletKit());						
// }																										
			

}


#endif