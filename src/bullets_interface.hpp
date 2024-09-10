#ifndef BULLETSINTERFACE_H
#define BULLETSINTERFACE_H

// #include <Godot.hpp>
// #include <Node2D.hpp>
// #include <AtlasTexture.hpp>
// #include <Material.hpp>
// #include <Color.hpp>
// // #include <PackedFloat64Array.hpp>
// #include <Rect2.hpp>
// #include <Array.hpp>
// #include <RegEx.hpp>

// #include <vector>
// #include <memory>

#include <bullet_kit.hpp>
// #include "bullets_pool.h"

using namespace godot;


class BulletsInterface : public Node2D {
	GDCLASS(BulletsInterface, Node2D)
	
private:
	// A pool internal representation with related properties.
	// struct PoolKit {
	// 	std::unique_ptr<BulletPool> pool;
	// 	Ref<BulletKit> bullet_kit;
	// 	int size;
	// 	int z_index;
	// };
	// struct PoolKitSet {
	// 	std::vector<PoolKit> pools;
	// 	int bullets_amount;
	// };

	// An internal reference to a pool-kit pair
	struct PoolKit {
		std::unique_ptr<BulletPool> pool;
		Ref<BulletKit> bullet_kit;
		int size;
		int z_index;
	};


	// // PoolKitSets represent PoolKits organized by their shared area.
	// std::vector<PoolKitSet> pool_sets;
	// // Maps each area RID to the corresponding PoolKitSet index.
	// Dictionary areas_to_pool_set_indices;

	//
	std::vector<PoolKit> pools;

	// Maps each BulletKit to the corresponding PoolKit index.
	Dictionary kits_to_pool_index;

	Node* bullets_environment = nullptr;

	int available_bullets = 0;
	int active_bullets = 0;
	int total_bullets = 0;

	Node2D* parent;
	Vector2 last_origin;

	// Array shared_areas;
	PackedInt64Array invalid_id;

	// double that makes it so bullets fired on different frames aren't syncronised
	double animation_random = 0.0;

	void _clear_rids();

public:
	static void _bind_methods();

	BulletsInterface();
	~BulletsInterface();

	void _init();

	// void _ready();

	void _physics_process(double delta);

	void mount(Node* bullets_environment);
	void unmount(Node* bullets_environment);
	Node* get_bullets_environment();
	// void set_bullets_environment(Node* bullets_environment);

	bool spawn_bullet(Ref<BulletKit> kit, Dictionary properties);
	Variant obtain_bullet(Ref<BulletKit> kit);
	bool release_bullet(Variant id);

	bool is_bullet_valid(Variant id);
	bool is_kit_valid(Ref<BulletKit> kit);

	int get_available_bullets(Ref<BulletKit> kit);
	int get_active_bullets(Ref<BulletKit> kit);
	int get_pool_size(Ref<BulletKit> kit);
	int get_z_index(Ref<BulletKit> kit);

	int get_total_available_bullets();
	int get_total_active_bullets();

	bool is_bullet_existing(RID area_rid, int shape_index);
	Ref<BulletKit> get_kit_from_bullet(Variant id);

	void set_bullet_property(Variant id, String property, Variant value);
	Variant get_bullet_property(Variant id, String property);

	// New stuff

	int collide_and_graze(Ref<BulletKit> kit, Vector2 pos, double hitbox_radius, double graze_radius);


	Variant create_shot_a1(Ref<BulletKit> kit, Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool fade_in);
	Variant create_shot_a2(Ref<BulletKit> kit, Vector2 pos, double speed, double angle, double accel, double max_speed, PackedFloat64Array bullet_data, bool fade_in);

	Variant create_item(Ref<BulletKit> kit, PackedFloat64Array item_data, Vector2 pos, double speed, double angle, double spin);

	Variant create_pattern_a1(Ref<BulletKit> kit, int mode, Vector2 pos, double r1, double speed1, double angle, int density, double spread, PackedFloat64Array bullet_data, bool fade_in);
	Variant create_pattern_a2(Ref<BulletKit> kit, int mode, Vector2 pos, double r1, double r2, double speed1, double speed2, double angle, int density, int stack, double spread, PackedFloat64Array bullet_data, bool fade_in);


	void set_bullet_properties(Variant id, Dictionary properties);
	void set_bullet_properties_bulk(Array bullets, Dictionary properties);

	void set_magnet_target(Variant id, Node2D *target);

	void add_pattern(Variant id, int trigger, int time, Dictionary properties);
	void add_translate(Variant id, int trigger, int time, Dictionary properties);
	void add_multiply(Variant id, int trigger, int time, Dictionary properties);
	void add_aim_at_point(Variant id, int trigger, int time, Vector2 point);
	void add_aim_at_object(Variant id, int trigger, int time, Node2D* object);
	void add_go_to_object(Variant id, int trigger, int time, Node2D* object);
	void add_change_bullet(Variant id, int trigger, int time, PackedFloat64Array bullet_data, bool fade_in);

	void add_pattern_bulk(Array bullets, int trigger, int time, Dictionary properties);
	void add_translate_bulk(Array bullets, int trigger, int time, Dictionary properties);
	void add_multiply_bulk(Array bullets, int trigger, int time, Dictionary properties);
	void add_aim_at_point_bulk(Array bullets, int trigger, int time, Vector2 point);
	void add_aim_at_object_bulk(Array bullets, int trigger, int time, Node2D* object);
	void add_go_to_object_bulk(Array bullets, int trigger, int time, Node2D* object);
	void add_change_bullet_bulk(Array bullets, int trigger, int time, PackedFloat64Array bullet_data, bool fade_in);

	bool is_deleted(Variant id);

	void create_particle(Ref<BulletKit> kit, Vector2 pos, double size, Color color, Vector2 drift, bool upright);

};

#endif