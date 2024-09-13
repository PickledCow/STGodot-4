#ifndef BASIC_ITEM_KIT_H
#define BASIC_ITEM_KIT_H

#include <bullet_kit.hpp>

#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/rendering_server.hpp>

namespace godot {

class BasicItemKit;

// Bullet pool definition.
class BasicItemPool : public AbstractBulletPool<BasicItemKit, BasicItem> {

	// void _init_bullet(Bullet* bullet); Use default implementation.
    public:

	void _enable_bullet(BasicItem* bullet);
	// void _disable_bullet(Bullet* bullet); Use default implementation.
	bool _process_bullet(BasicItem* bullet, double delta);

	Array _collect_and_magnet(Vector2 pos, Node2D* target, double collect_radius, double magnet_radius);
    BulletID _create_item(Vector2 pos, double speed, double angle, double spin, PackedFloat64Array item_data);
    


    // void _init_shot_A1(Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool fade_in);

};


// Bullet kit definition.
class BasicItemKit : public BulletKit {
	GDCLASS(BasicItemKit, BulletKit)
    public:
	// Vector of what directions items naturally fall at. 
	Vector2 gravity = Vector2();
	double damp = 0.95;
    double magnet_strength = 10.0;

	std::unique_ptr<BulletPool> _create_pool() override;
	// BULLET_KIT(BasicItemPool)

    Vector2 get_gravity();
	double get_damp();
    double get_magnet_strength();
    
    void set_gravity(Vector2 value);
    void set_damp(double value);
    void set_magnet_strength(double value);

    static void _bind_methods();

};

};



#endif