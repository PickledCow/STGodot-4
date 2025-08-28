#ifndef BULLETINTERFACE_H
#define BULLETINTERFACE_H

#define _USE_MATH_DEFINES
#include <math.h>

#include <bullet.hpp>

#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/shape2d.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/material.hpp>		
#include <godot_cpp/classes/node2d.hpp>

using namespace godot;


class BulletInterface : public Node2D {
	GDCLASS(BulletInterface, Node2D)
	
public:

	enum BulletDataStructure {
		DATA_SRC_X, 
		DATA_SRC_Y, 
		DATA_SRC_W, 
		DATA_SRC_H, 
		DATA_SIZE, 
		DATA_HITBOX_RATIO, 
		DATA_SPRITE_OFFSET, 
		DATA_ANIM_FRAMES, 
		DATA_SPIN, 
		DATA_LAYER, 
		DATA_CLEAR_R, 
		DATA_CLEAR_G, 
		DATA_CLEAR_B, 
		DATA_DAMAGE_TYPE, 
		DATA_DAMAGE_AMOUNT
	};
	
	enum ItemDataStructure {
		ITEM_DATA_SRC_X, 
		ITEM_DATA_SRC_Y, 
		ITEM_DATA_SRC_W, 
		ITEM_DATA_SRC_H, 
		ITEM_DATA_SIZE, 
		ITEM_DATA_HITBOX_RATIO, 
		ITEM_DATA_SPRITE_OFFSET, 
		ITEM_DATA_ANIM_FRAMES, 
		ITEM_DATA_LAYER, 
		ITEM_DATA_DAMAGE_TYPE, 
		ITEM_DATA_DAMAGE_AMOUNT
	};
	
	enum LaserDataStructure {
		LASER_DATA_SRC_X, 
		LASER_DATA_SRC_Y, 
		LASER_DATA_SRC_W, 
		LASER_DATA_SRC_H, 
		LASER_DATA_HITBOX_RATIO, 
		LASER_DATA_ANIM_FRAMES, 
		LASER_DATA_LAYER, 
		LASER_DATA_SPAWN_SRC_X,
		LASER_DATA_SPAWN_SRC_Y,
		LASER_DATA_SPAWN_SRC_W,
		LASER_DATA_SPAWN_SRC_H,
		LASER_DATA_CLEAR_R, 
		LASER_DATA_CLEAR_G, 
		LASER_DATA_CLEAR_B, 
		LASER_DATA_DAMAGE_TYPE, 
		LASER_DATA_DAMAGE_AMOUNT
	};

	enum WallSides { 
		WALLS_NONE, 
		WALLS_TOP, 
		WALLS_BOTTOM, 
		WALLS_VERTICALS, 
		WALLS_LEFT, 
		WALLS_RIGHT = 8, 
		WALLS_SIDES = 12, 
		WALLS_DOME, 
		WALLS_CUP, 
		WALLS_ALL 
	};

	enum TransformTrigger {
		TRIGGER_TIME
	};

	enum TransformProperty {
		TRANSFORM_SPEED,
		TRANSFORM_ANGLE,
		TRANSFORM_ACCEL,
		TRANSFORM_MAX_SPEED,
		TRANSFORM_WVEL,
	};

	enum TransformStructure {
		TRANSFORM_STRUCTURE_TYPE,
		TRANSFORM_STRUCTURE_TRIGGER_METHOD,
		TRANSFORM_STRUCTURE_TRIGGER_VALUE,
		TRANSFORM_STRUCTURE_PROPERTY,
		TRANSFORM_STRUCTURE_VALUE,
		TRANSFORM_STRUCTURE_MAX
	};


	enum SheetOrientation { SHEET_UP, SHEET_RIGHT, SHEET_DOWN, SHEET_LEFT };

	enum POOLS { BULLETS_POOL, SHOTS_POOL, ITEMS_POOL, PARTICLES_POOL, ENEMIES_POOL, LASERS_POOL, CURVE_LASERS_POOL };

	// VERY BAD COPY PASTE BUT I CAN'T GET IT TO WORK OTHERWISE BECAUSE I'M BAD
	// enum TRIGGERS {TRIGGER_TIME, TRIGGER_BOUNCE, TRIGGER_GRAZE};


	bool mounted = false;

	// Pools. The pools are accessed in reverse.
	Bullet** bullet_pool;
	Bullet** shot_pool;
	Item** item_pool;
	Particle** particle_pool;
	Enemy** enemy_pool;
	Laser** laser_pool;
	CurveLaser** curve_laser_pool;

	// Pool data
	int available_bullets = 0;
	int available_shots = 0;
	int available_items = 0;
	int available_particles = 0;
	int available_enemies = 0;
	int available_lasers = 0;
	int available_curve_lasers = 0;

	int active_bullets = 0;
	int active_shots = 0;
	int active_items = 0;
	int active_particles = 0;
	int active_enemies = 0;
	int active_lasers = 0;
	int active_curve_lasers = 0;

	int total_bullets = 0;
	int total_shots = 0;
	int total_items = 0;
	int total_particles = 0;
	int total_enemies = 0;
	int total_lasers = 0;
	int total_curve_lasers = 0;

	int* persistent_bullet_index;
	int* persistent_shot_index;
	int* persistent_item_index;
	int* persistent_particle_index;
	int* persistent_enemy_index;
	int* persistent_laser_index;
	int* persistent_curve_laser_index;

	// Rendering
	int bullets_z_index = 10;
	int shots_z_index = 10;
	int items_z_index = 5;
	int particles_z_index = 6;
	int lasers_z_index = 8;
	// Curve laser and laser share rendering properties

	int bullets_draw_index = 0;
	int shots_draw_index = 0;
	int items_draw_index = 0;
	int particles_draw_index = 0;
	int lasers_draw_index = 0;

	Ref<Texture2D> bullets_texture;
	Ref<Texture2D> shots_texture;
	Ref<Texture2D> items_texture;
	Ref<Texture2D> particles_texture;
	Ref<Texture2D> lasers_texture;
	Ref<Texture2D> laser_spawns_texture;

	Ref<Material> bullets_material;
	Ref<Material> shots_material;
	Ref<Material> items_material;
	Ref<Material> particles_material;
	Ref<Material> lasers_material;
	Ref<Material> curve_lasers_material;
	// Ref<Material> laser_spawns_material; // Unused

	Ref<Material> bullets_material_add;
	Ref<Material> shots_material_add;
	Ref<Material> items_material_add;
	Ref<Material> particles_material_add;
	Ref<Material> lasers_material_add;
	Ref<Material> curve_lasers_material_add;
	Ref<Material> laser_spawns_material_add;

	SheetOrientation bullet_sheet_orientation = SHEET_UP;
	SheetOrientation shot_sheet_orientation = SHEET_UP;
	SheetOrientation item_sheet_orientation = SHEET_UP;
	SheetOrientation particle_sheet_orientation = SHEET_UP;
	SheetOrientation laser_sheet_orientation = SHEET_UP;

	double bullet_rotation_offset = M_PI_2;
	double shot_rotation_offset = M_PI_2;
	double item_rotation_offset = 0.0;
	double particle_rotation_offset = 0.0;
	double laser_rotation_offset = M_PI_2;

	double bullets_fade_time = 8.0;
	double shots_fade_time = 4.0;
	double items_fade_time = 8.0;
	double lasers_fade_time = 8.0;

	// Item specific
	Vector2 items_gravity = Vector2(0.0, 4.0);
	double items_damp = 0.95;
	double items_magnet_strength = 20.0;

	// Helper unchangings
	double bullets_texture_width;
	RID bullets_texture_rid;
	RID bullets_material_rid;
	RID bullets_material_add_rid;
	double shots_texture_width;
	RID shots_texture_rid;
	RID shots_material_rid;
	RID shots_material_add_rid;
	double items_texture_width;
	RID items_texture_rid;
	RID items_material_rid;
	RID items_material_add_rid;
	double particles_texture_width;
	RID particles_texture_rid;
	RID particles_material_rid;
	RID particles_material_add_rid;
	double lasers_texture_width;
	RID lasers_texture_rid;
	RID lasers_material_rid;
	RID lasers_material_add_rid;
	RID curve_lasers_material_rid;
	RID curve_lasers_material_add_rid;
	double laser_spawns_texture_width;
	RID laser_spawns_texture_rid;
	RID laser_spawns_material_rid;
	RID laser_spawns_material_add_rid;

	// Flags for if the pools have been created
	bool bullets_created = false;
	bool shots_created = false;
	bool items_created = false;
	bool particles_created = false;
	bool enemies_created = false;
	bool lasers_created = false;
	bool curve_lasers_created = false;

	// Field variables
	Rect2 bounce_rect;
	Rect2 bullet_active_rect;
	Rect2 shot_active_rect;
	double time_scale = 1.0;

	Node2D* parent;

	PackedInt64Array invalid_id;
	Array invalid_collide_and_graze_array;

	// Double that makes it so bullets fired on different frames aren't syncronised
	double animation_random = 0.0;

	// Helper singleton references
	RenderingServer* rendering_server;
	RID canvas_parent;
	RID bullets_canvas_item;
	RID shots_canvas_item;
	RID items_canvas_item;
	RID particles_canvas_item;
	RID lasers_canvas_item;
	RID curve_lasers_canvas_item;
	RID curve_lasers_add_canvas_item;
	RID curve_lasers_mesh_item;
	RID curve_lasers_add_mesh_item;

	void unmount();

	void _clear_rids();

	void _init_bullets();
	void _init_shots();
	void _init_items();
	void _init_particles();
	void _init_enemies();
	void _init_lasers();
	void _init_curve_lasers();

	bool _process_bullet(Bullet* bullet, double delta, bool skip_fade, bool skip_rect_check, Rect2 active_rect);
	bool _process_item(Item* item, double delta);
	bool _process_particle(Particle* particle, double delta);
	bool _process_enemy(Enemy* enemy, double delta);
	bool _process_laser(Laser* laser, double delta);
	bool _process_curve_laser(CurveLaser* laser, double delta);

	void _fade_in_bullet(Bullet* bullet, double delta);

	void _process_bullet_a1(Bullet* bullet, double delta);
	void _process_bullet_a2(Bullet* bullet, double delta);
	int _process_bullet_a3(Bullet* bullet, double delta);
	int _process_bullet_a3_after(Bullet* bullet, double delta);
	void _process_bullet_b1(Bullet* bullet, double delta);

	void _release_bullet(int index);
	void _release_shot(int index);
	void _release_item(int index);
	void _release_particle(int index);
	void _release_enemy(int index);
	void _release_laser(int index);
	void _release_curve_laser(int index);

	// Cuts a curve laser into two 
	void _cut_curve_laser(CurveLaser* laser, int collision_point);
	
	template<typename T>
	void _swap(T &a, T &b) {
		T t = a;
		a = b;
		b = t;
	}

	static void _bind_methods();

	BulletInterface();
	~BulletInterface();

	void set_constant(float value);

	int get_NO_CHANGE();

	/* #region setters and getters */ 
	int get_total_bullets();
	void set_total_bullets(int bullets);

	int get_total_shots();
	void set_total_shots(int shots);
	
	int get_total_items();
	void set_total_items(int items);
	
	int get_total_particles();
	void set_total_particles(int particles);
	
	int get_total_enemies();
	void set_total_enemies(int enemies);

	int get_total_lasers();
	void set_total_lasers(int lasers);
	
	int get_total_curve_lasers();
	void set_total_curve_lasers(int lasers);


	int get_bullets_z_index();
	void set_bullets_z_index(int index);
	
	int get_shots_z_index();
	void set_shots_z_index(int index);
	
	int get_items_z_index();
	void set_items_z_index(int index);
	
	int get_particles_z_index();
	void set_particles_z_index(int index);
	
	int get_lasers_z_index();
	void set_lasers_z_index(int index);


	Rect2 get_bounce_rect();
	void set_bounce_rect(Rect2 rect);

	Rect2 get_bullet_active_rect();
	void set_bullet_active_rect(Rect2 rect);
	
	Rect2 get_shot_active_rect();
	void set_shot_active_rect(Rect2 rect);

	double get_time_scale();
	void set_time_scale(double ts);

	double get_bullets_fade_time();
	void set_bullets_fade_time(double time);
	
	double get_shots_fade_time();
	void set_shots_fade_time(double time);
	
	double get_items_fade_time();
	void set_items_fade_time(double time);

	double get_lasers_fade_time();
	void set_lasers_fade_time(double time);

	
	int get_bullet_sheet_orientation();
	void set_bullet_sheet_orientation(int orientation);
	
	int get_shot_sheet_orientation();
	void set_shot_sheet_orientation(int orientation);
	
	int get_laser_sheet_orientation();
	void set_laser_sheet_orientation(int orientation);
	/* #endregion */ 

	/* #region Texture setters/getters */
	Ref<Texture2D> get_bullets_texture();
	void set_bullets_texture(Ref<Texture2D> texture);
	Ref<Material> get_bullets_material();
	void set_bullets_material(Ref<Material> material);
	Ref<Material> get_bullets_material_add();
	void set_bullets_material_add(Ref<Material> material);
	
	Ref<Texture2D> get_shots_texture();
	void set_shots_texture(Ref<Texture2D> texture);
	Ref<Material> get_shots_material();
	void set_shots_material(Ref<Material> material);
	Ref<Material> get_shots_material_add();
	void set_shots_material_add(Ref<Material> material);
	
	Ref<Texture2D> get_items_texture();
	void set_items_texture(Ref<Texture2D> texture);
	Ref<Material> get_items_material();
	void set_items_material(Ref<Material> material);
	Ref<Material> get_items_material_add();
	void set_items_material_add(Ref<Material> material);
	
	Ref<Texture2D> get_particles_texture();
	void set_particles_texture(Ref<Texture2D> texture);
	Ref<Material> get_particles_material();
	void set_particles_material(Ref<Material> material);
	Ref<Material> get_particles_material_add();
	void set_particles_material_add(Ref<Material> material);

	Ref<Texture2D> get_lasers_texture();
	void set_lasers_texture(Ref<Texture2D> texture);
	Ref<Material> get_lasers_material();
	void set_lasers_material(Ref<Material> material);
	Ref<Material> get_lasers_material_add();
	void set_lasers_material_add(Ref<Material> material);
	
	Ref<Material> get_curve_lasers_material();
	void set_curve_lasers_material(Ref<Material> material);
	Ref<Material> get_curve_lasers_material_add();
	void set_curve_lasers_material_add(Ref<Material> material);
	
	Ref<Texture2D> get_laser_spawns_texture();
	void set_laser_spawns_texture(Ref<Texture2D> texture);
	Ref<Material> get_laser_spawns_material();
	void set_laser_spawns_material(Ref<Material> material);
	Ref<Material> get_laser_spawns_material_add();
	void set_laser_spawns_material_add(Ref<Material> material);


	/* #endregion */

	/* #region Getters w/o setters */

	int get_active_bullets();
	int get_active_shots();
	int get_active_items();
	int get_active_particles();
	int get_active_enemies();
	int get_active_lasers();
	int get_active_curve_lasers();

	/* #endregion */

	Vector2 get_items_gravity();
	void set_items_gravity(Vector2 gravity);

	double get_items_damp();
	void set_items_damp(double damp);
	double get_items_magnet_strength();
	void set_items_magnet_strength(double magnet_strength);

	void init(Node2D* root);

	// void _ready();

	void _process(double delta);

	void enable_bullet(Bullet* bullet);
	void enable_shot(Bullet* shot);
	void enable_enemy(Enemy* enemy);
	void enable_laser(Laser* laser);
	void enable_curve_laser(CurveLaser* laser);

	void clear_entity(PackedInt64Array bullet_id);

	PackedInt64Array create_bullet_a1(Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool glow);
	PackedInt64Array create_bullet_a2(Vector2 pos, double speed, double angle, double accel, double max_speed, double w_vel, PackedFloat64Array bullet_data, bool glow);
	
	PackedInt64Array create_bullet_b1(Vector2 pos, Vector2 velocity, Vector2 accel, Vector2 max_velocity, bool rotation_follows_movement, PackedFloat64Array bullet_data, bool glow);

	PackedInt64Array create_shot_a1(Vector2 pos, double speed, double angle, PackedFloat64Array shot_data, bool glow);
	PackedInt64Array create_shot_a2(Vector2 pos, double speed, double angle, double accel, double max_speed, double w_vel, PackedFloat64Array shot_data, bool glow);

	// PackedInt64Array create_shot_b1(Vector2 pos, Vector2 velocity, Vector2 accel, Vector2 max_velocity, PackedFloat64Array bullet_data, bool glow);

	PackedInt64Array create_enemy(double hitbox_size, double hurtbox_size, bool deletes_bullets);

	PackedInt64Array create_straight_laser(Vector2 pos, double angle, double length, double width, double start_margin, double end_margin, double delay, double duration, PackedFloat64Array laser_data, bool glow);
	PackedInt64Array create_loose_laser(Vector2 pos, double speed, double angle, double length, double width, double start_margin, double end_margin, PackedFloat64Array laser_data, bool glow);
	PackedInt64Array create_curve_laser(Vector2 pos, double speed, double angle, int length, double width, int start_margin, int end_margin, PackedFloat64Array laser_data, bool glow);

	void add_bullet_transform_a2(PackedInt64Array bullet_id, int trigger, int trigger_value, double speed, double angle, double accel, double max_speed, double w_vel);

	// bool spawn_bullet(Ref<BulletKit> kit, Dictionary properties);
	// Variant obtain_bullet(Ref<BulletKit> kit);
	// bool release_bullet(Variant id);

	bool is_valid(PackedInt64Array id);
	// bool is_kit_valid(Ref<BulletKit> kit);

	// int get_available_bullets(Ref<BulletKit> kit);
	// int get_active_bullets(Ref<BulletKit> kit);
	// int get_pool_size(Ref<BulletKit> kit);
	// int get_z_index(Ref<BulletKit> kit);

	// int get_total_available_bullets();
	// int get_total_active_bullets();

	// bool is_bullet_existing(RID area_rid, int shape_index);
	// Ref<BulletKit> get_kit_from_bullet(Variant id);


	// Array collide_and_graze_kit(Ref<BasicBulletKit> kit, Vector2 pos, double hitbox_radius, double graze_radius);
	Array collide_and_graze_player(Vector2 pos, double hitbox_radius, double graze_radius);
	Array collide_enemy(Vector2 pos, double hitbox_radius);

	Array collect_and_magnet_items(Vector2 pos, Node2D* target, double collect_radius, double magnet_radius);
	// Array collect_and_magnet_all(Vector2 pos, Node2D* target, double collect_radius, double magnet_radius);
	void magnet_all_items(Node2D* target);
	// void magnet_all_kit(Ref<BasicItemKit> kit, Node2D* target);

	Array clear_bullets(Vector2 pos, double radius, bool ignore_pierce);

	PackedInt64Array create_item(Vector2 pos, double speed, double angle, double spin, PackedFloat64Array item_data, bool glow);
	
    // PackedInt64Array create_particle(Ref<BasicParticleKit> kit, Vector2 pos, Vector2 drift, double rotation, double size, Color color);

	Array get_enemy_collisions(PackedInt64Array enemy_id);

	Array get_enemies_in_range(Vector2 pos, float radius);

	Vector2 get_position(PackedInt64Array bullet_id);
	void set_position(PackedInt64Array bullet_id, Vector2 position);

	double get_damage(PackedInt64Array bullet_id);
	void set_damage(PackedInt64Array bullet_id, double damage);
	
	int get_damage_type(PackedInt64Array bullet_id);
	void set_damage_type(PackedInt64Array bullet_id, int damage_type);

	int get_layer(PackedInt64Array bullet_id);
	void set_layer(PackedInt64Array bullet_i, int layer);

	void skip_fade(PackedInt64Array bullet_id);

	void deal_damage(PackedInt64Array enemy_id, float damage);

	// Item

	// Unimplemented

	double get_speed(PackedInt64Array bullet_id);
	void set_speed(PackedInt64Array bullet_id, double speed);

	double get_angle(PackedInt64Array bullet_id);
	void set_angle(PackedInt64Array bullet_id, double angle);
	
	PackedFloat64Array get_bullet_data(PackedInt64Array bullet_id);
	void set_bullet_data(PackedInt64Array bullet_id, PackedFloat64Array bullet_data);

	// Collision Bullets
	
    double get_hitbox_scale(PackedInt64Array bullet_id);
    void set_hitbox_scale(PackedInt64Array bullet_id, double hitbox_scale);

    bool get_is_grazed(PackedInt64Array bullet_id);
    void set_is_grazed(PackedInt64Array bullet_id, bool is_grazed);

	// General Movement
	
    double get_spin(PackedInt64Array bullet_id);
    void set_spin(PackedInt64Array bullet_id, double spin);

	
    double get_rotation(PackedInt64Array bullet_id);
    void set_rotation(PackedInt64Array bullet_id, double rotation);

	// A2 Movement

	double get_accel(PackedInt64Array bullet_id);
	void set_accel(PackedInt64Array bullet_id, double accel);
	
	double get_max_speed(PackedInt64Array bullet_id);
	void set_max_speed(PackedInt64Array bullet_id, double max_speed);

    double get_wvel(PackedInt64Array bullet_id);
    void set_wvel(PackedInt64Array bullet_id, double wvel);

	// A3 Movement
	
    int get_bounce_mode(PackedInt64Array bullet_id);
    void set_bounce_mode(PackedInt64Array bullet_id, int bounce_mode);

    int get_bounce_count(PackedInt64Array bullet_id);
    void set_bounce_count(PackedInt64Array bullet_id, int bounce_count);

    int get_bounce_surfaces(PackedInt64Array bullet_id);
    void set_bounce_surfaces(PackedInt64Array bullet_id, int bounce_surfaces);


    double get_waccel(PackedInt64Array bullet_id);
    void set_waccel(PackedInt64Array bullet_id, double waccel);

    double get_max_wvel(PackedInt64Array bullet_id);
    void set_max_wvel(PackedInt64Array bullet_id, double max_wvel);



	// Bullet setters and getters
	double get_lifetime(PackedInt64Array bullet_id);
	void set_lifetime(PackedInt64Array bullet_id, double lifetime);
	
	double get_lifespan(PackedInt64Array bullet_id);
	void set_lifespan(PackedInt64Array bullet_id, double lifespan);
	
	bool get_pierce(PackedInt64Array bullet_id);
	void set_pierce(PackedInt64Array bullet_id, bool pierce);



	// Item setters and getters

	int get_item_type(PackedInt64Array item_id);

	void set_item_magnet(PackedInt64Array item_id, Node2D* target);


	// double get_(PackedInt64Array bullet_id);
	// void set_(PackedInt64Array bullet_id, double );





	bool get_is_auto_collected(PackedInt64Array bullet_id);
	// void set_bullet_properties(Variant id, Dictionary properties);
	// void set_bullet_properties_bulk(Array bullets, Dictionary properties);

	void set_magnet_target(Variant id, Node2D *target);

	// void add_pattern(Variant id, int trigger, int time, Dictionary properties);
	// void add_translate(Variant id, int trigger, int time, Dictionary properties);
	// void add_multiply(Variant id, int trigger, int time, Dictionary properties);
	// void add_aim_at_point(Variant id, int trigger, int time, Vector2 point);
	// void add_aim_at_object(Variant id, int trigger, int time, Node2D* object);
	// void add_go_to_object(Variant id, int trigger, int time, Node2D* object);
	// void add_change_bullet(Variant id, int trigger, int time, PackedFloat64Array bullet_data, bool fade_in);

	// void add_pattern_bulk(Array bullets, int trigger, int time, Dictionary properties);
	// void add_translate_bulk(Array bullets, int trigger, int time, Dictionary properties);
	// void add_multiply_bulk(Array bullets, int trigger, int time, Dictionary properties);
	// void add_aim_at_point_bulk(Array bullets, int trigger, int time, Vector2 point);
	// void add_aim_at_object_bulk(Array bullets, int trigger, int time, Node2D* object);
	// void add_go_to_object_bulk(Array bullets, int trigger, int time, Node2D* object);
	// void add_change_bullet_bulk(Array bullets, int trigger, int time, PackedFloat64Array bullet_data, bool fade_in);

	bool is_deleted(Variant id);

};



VARIANT_ENUM_CAST(BulletInterface::BulletDataStructure);
VARIANT_ENUM_CAST(BulletInterface::ItemDataStructure);
VARIANT_ENUM_CAST(BulletInterface::LaserDataStructure);
VARIANT_ENUM_CAST(BulletInterface::WallSides);
// VARIANT_ENUM_CAST(godot::TransformTriggers);
VARIANT_ENUM_CAST(BulletInterface::SheetOrientation);
VARIANT_ENUM_CAST(BulletInterface::TransformProperty);
VARIANT_ENUM_CAST(BulletInterface::TransformTrigger);

#endif