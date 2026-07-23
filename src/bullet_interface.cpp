#include <cstdlib>

#include "bullet_interface.hpp"

#include "godot_cpp/classes/engine.hpp"
#include "godot_cpp/classes/world2d.hpp"
#include "godot_cpp/variant/utility_functions.hpp"


using namespace godot;

int BulletInterface::get_NO_CHANGE() { return NO_CHANGE; }

// TODO: Spin is borked
// TODO: Shader vertical offset might have issues when negative, check on that


void BulletInterface::set_constant(float value) {
	// Constant
}

// I hate you
void BulletInterface::_bind_methods() {

	/* #region Enums */

	BIND_CONSTANT(NO_CHANGE);

	// SET ENUMS
	{
	BIND_ENUM_CONSTANT(DATA_SRC_X);
	BIND_ENUM_CONSTANT(DATA_SRC_Y);
	BIND_ENUM_CONSTANT(DATA_SRC_W);
	BIND_ENUM_CONSTANT(DATA_SRC_H);
	BIND_ENUM_CONSTANT(DATA_SIZE);
	BIND_ENUM_CONSTANT(DATA_HITBOX_RATIO);
	BIND_ENUM_CONSTANT(DATA_SPRITE_OFFSET);
	BIND_ENUM_CONSTANT(DATA_ANIM_FRAMES);
	BIND_ENUM_CONSTANT(DATA_SPIN);
	BIND_ENUM_CONSTANT(DATA_LAYER);
	BIND_ENUM_CONSTANT(DATA_CLEAR_R);
	BIND_ENUM_CONSTANT(DATA_CLEAR_G);
	BIND_ENUM_CONSTANT(DATA_CLEAR_B);
	BIND_ENUM_CONSTANT(DATA_DAMAGE_TYPE);
	BIND_ENUM_CONSTANT(DATA_DAMAGE_AMOUNT);
	
	BIND_ENUM_CONSTANT(ITEM_DATA_SRC_X); 
	BIND_ENUM_CONSTANT(ITEM_DATA_SRC_Y); 
	BIND_ENUM_CONSTANT(ITEM_DATA_SRC_W); 
	BIND_ENUM_CONSTANT(ITEM_DATA_SRC_H); 
	BIND_ENUM_CONSTANT(ITEM_DATA_SIZE); 
	BIND_ENUM_CONSTANT(ITEM_DATA_HITBOX_RATIO); 
	BIND_ENUM_CONSTANT(ITEM_DATA_SPRITE_OFFSET); 
	BIND_ENUM_CONSTANT(ITEM_DATA_ANIM_FRAMES); 
	BIND_ENUM_CONSTANT(ITEM_DATA_LAYER); 
	BIND_ENUM_CONSTANT(ITEM_DATA_DAMAGE_TYPE); 
	BIND_ENUM_CONSTANT(ITEM_DATA_DAMAGE_AMOUNT);

	BIND_ENUM_CONSTANT(LASER_DATA_SRC_X); 
	BIND_ENUM_CONSTANT(LASER_DATA_SRC_Y); 
	BIND_ENUM_CONSTANT(LASER_DATA_SRC_W); 
	BIND_ENUM_CONSTANT(LASER_DATA_SRC_H); 
	BIND_ENUM_CONSTANT(LASER_DATA_HITBOX_RATIO); 
	BIND_ENUM_CONSTANT(LASER_DATA_ANIM_FRAMES); 
	BIND_ENUM_CONSTANT(LASER_DATA_LAYER); 
	BIND_ENUM_CONSTANT(LASER_DATA_SPAWN_SRC_X);
	BIND_ENUM_CONSTANT(LASER_DATA_SPAWN_SRC_Y);
	BIND_ENUM_CONSTANT(LASER_DATA_SPAWN_SRC_W);
	BIND_ENUM_CONSTANT(LASER_DATA_SPAWN_SRC_H);
	BIND_ENUM_CONSTANT(LASER_DATA_CLEAR_R); 
	BIND_ENUM_CONSTANT(LASER_DATA_CLEAR_G); 
	BIND_ENUM_CONSTANT(LASER_DATA_CLEAR_B); 
	BIND_ENUM_CONSTANT(LASER_DATA_DAMAGE_TYPE); 
	BIND_ENUM_CONSTANT(LASER_DATA_DAMAGE_AMOUNT);

	BIND_ENUM_CONSTANT(WALLS_NONE);
	BIND_ENUM_CONSTANT(WALLS_TOP);
	BIND_ENUM_CONSTANT(WALLS_BOTTOM);
	BIND_ENUM_CONSTANT(WALLS_VERTICALS);
	BIND_ENUM_CONSTANT(WALLS_LEFT);
	BIND_ENUM_CONSTANT(WALLS_RIGHT);
	BIND_ENUM_CONSTANT(WALLS_SIDES);
	BIND_ENUM_CONSTANT(WALLS_DOME);
	BIND_ENUM_CONSTANT(WALLS_CUP);
	BIND_ENUM_CONSTANT(WALLS_ALL);
	
	BIND_ENUM_CONSTANT(TRIGGER_TIME);
	// BIND_ENUM_CONSTANT(TRIGGER_BOUNCE);
	// BIND_ENUM_CONSTANT(TRIGGER_GRAZE);


	BIND_ENUM_CONSTANT(TRANSFORM_ACCEL);
	BIND_ENUM_CONSTANT(TRANSFORM_MAX_SPEED);
	BIND_ENUM_CONSTANT(TRANSFORM_WVEL);
	
	// BIND_ENUM_CONSTANT(BULLET_ID_INDEX);
	// BIND_ENUM_CONSTANT(BULLET_ID_POOL);
	// BIND_ENUM_CONSTANT(BULLET_ID_CYCLE);
	}

	/* #endregion */
	
	/* #region Setup Setters/Getters */
	
    ClassDB::bind_method(D_METHOD("get_bounce_rect"), &BulletInterface::get_bounce_rect);
	ClassDB::bind_method(D_METHOD("set_bounce_rect", "p_bounce_rect"), &BulletInterface::set_bounce_rect);
	ADD_PROPERTY(PropertyInfo(Variant::RECT2, "Field/Bounce Rect"), "set_bounce_rect", "get_bounce_rect");
	
    ClassDB::bind_method(D_METHOD("get_bullet_active_rect"), &BulletInterface::get_bullet_active_rect);
	ClassDB::bind_method(D_METHOD("set_bullet_active_rect", "p_bullet_active_rect"), &BulletInterface::set_bullet_active_rect);
	ADD_PROPERTY(PropertyInfo(Variant::RECT2, "Field/Bullet Active Rect"), "set_bullet_active_rect", "get_bullet_active_rect");
	
    ClassDB::bind_method(D_METHOD("get_shot_active_rect"), &BulletInterface::get_shot_active_rect);
	ClassDB::bind_method(D_METHOD("set_shot_active_rect", "p_shot_active_rect"), &BulletInterface::set_shot_active_rect);
	ADD_PROPERTY(PropertyInfo(Variant::RECT2, "Field/Shot Active Rect"), "set_shot_active_rect", "get_shot_active_rect");
	
    ClassDB::bind_method(D_METHOD("get_time_scale"), &BulletInterface::get_time_scale);
	ClassDB::bind_method(D_METHOD("set_time_scale", "p_time_scale"), &BulletInterface::set_time_scale);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Field/Time Scale"), "set_time_scale", "get_time_scale");

    ClassDB::bind_method(D_METHOD("get_bullets_z_index"), &BulletInterface::get_bullets_z_index);
	ClassDB::bind_method(D_METHOD("set_bullets_z_index", "p_bullets_z_index"), &BulletInterface::set_bullets_z_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Bullets/Z Layer"), "set_bullets_z_index", "get_bullets_z_index");

    ClassDB::bind_method(D_METHOD("get_shots_z_index"), &BulletInterface::get_shots_z_index);
	ClassDB::bind_method(D_METHOD("set_shots_z_index", "p_shots_z_index"), &BulletInterface::set_shots_z_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Shots/Z Layer"), "set_shots_z_index", "get_shots_z_index");

    ClassDB::bind_method(D_METHOD("get_items_z_index"), &BulletInterface::get_items_z_index);
	ClassDB::bind_method(D_METHOD("set_items_z_index", "p_items_z_index"), &BulletInterface::set_items_z_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Items/Z Layer"), "set_items_z_index", "get_items_z_index");

    ClassDB::bind_method(D_METHOD("get_particles_z_index"), &BulletInterface::get_particles_z_index);
	ClassDB::bind_method(D_METHOD("set_particles_z_index", "p_particles_z_index"), &BulletInterface::set_particles_z_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Particles/Z Layer"), "set_particles_z_index", "get_particles_z_index");
	
    ClassDB::bind_method(D_METHOD("get_lasers_z_index"), &BulletInterface::get_lasers_z_index);
	ClassDB::bind_method(D_METHOD("set_lasers_z_index", "p_lasers_z_index"), &BulletInterface::set_lasers_z_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Lasers/Z Layer"), "set_lasers_z_index", "get_lasers_z_index");
	

    ClassDB::bind_method(D_METHOD("get_total_bullets"), &BulletInterface::get_total_bullets);
	ClassDB::bind_method(D_METHOD("set_total_bullets", "p_total_bullets"), &BulletInterface::set_total_bullets);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Bullets/Pool Size"), "set_total_bullets", "get_total_bullets");
	
    ClassDB::bind_method(D_METHOD("get_total_shots"), &BulletInterface::get_total_shots);
	ClassDB::bind_method(D_METHOD("set_total_shots", "p_total_shots"), &BulletInterface::set_total_shots);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Shots/Pool Size"), "set_total_shots", "get_total_shots");
	
    ClassDB::bind_method(D_METHOD("get_total_items"), &BulletInterface::get_total_items);
	ClassDB::bind_method(D_METHOD("set_total_items", "p_total_items"), &BulletInterface::set_total_items);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Items/Pool Size"), "set_total_items", "get_total_items");
	
    ClassDB::bind_method(D_METHOD("get_total_particles"), &BulletInterface::get_total_particles);
	ClassDB::bind_method(D_METHOD("set_total_particles", "p_total_particles"), &BulletInterface::set_total_particles);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Particles/Pool Size"), "set_total_particles", "get_total_particles");
	
    ClassDB::bind_method(D_METHOD("get_total_enemies"), &BulletInterface::get_total_enemies);
	ClassDB::bind_method(D_METHOD("set_total_enemies", "p_total_enemies"), &BulletInterface::set_total_enemies);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Enemies/Pool Size"), "set_total_enemies", "get_total_enemies");
	
    ClassDB::bind_method(D_METHOD("get_total_lasers"), &BulletInterface::get_total_lasers);
	ClassDB::bind_method(D_METHOD("set_total_lasers", "p_total_lasers"), &BulletInterface::set_total_lasers);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Lasers/Pool Size (Regular)"), "set_total_lasers", "get_total_lasers");
	
    ClassDB::bind_method(D_METHOD("get_total_curve_lasers"), &BulletInterface::get_total_curve_lasers);
	ClassDB::bind_method(D_METHOD("set_total_curve_lasers", "p_total_curve_lasers"), &BulletInterface::set_total_curve_lasers);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Lasers/Pool Size (Curve)", PROPERTY_HINT_RANGE, "0,256"), "set_total_curve_lasers", "get_total_curve_lasers"); // 256 is surface max
	

    ClassDB::bind_method(D_METHOD("get_bullets_texture"), &BulletInterface::get_bullets_texture);
	ClassDB::bind_method(D_METHOD("set_bullets_texture", "p_bullets_texture"), &BulletInterface::set_bullets_texture);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Bullets/Texture", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "Texture2D"
        ), "set_bullets_texture", "get_bullets_texture");
	
    ClassDB::bind_method(D_METHOD("get_bullets_material"), &BulletInterface::get_bullets_material);
	ClassDB::bind_method(D_METHOD("set_bullets_material", "p_bullets_material"), &BulletInterface::set_bullets_material);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Bullets/Material", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_bullets_material", "get_bullets_material");
	
    ClassDB::bind_method(D_METHOD("get_bullets_material_add"), &BulletInterface::get_bullets_material_add);
	ClassDB::bind_method(D_METHOD("set_bullets_material_add", "p_bullets_material_add"), &BulletInterface::set_bullets_material_add);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Bullets/Material (Add)", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_bullets_material_add", "get_bullets_material_add");
	
// ---
    ClassDB::bind_method(D_METHOD("get_shots_texture"), &BulletInterface::get_shots_texture);
	ClassDB::bind_method(D_METHOD("set_shots_texture", "p_shots_texture"), &BulletInterface::set_shots_texture);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Shots/Texture", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "Texture2D"
        ), "set_shots_texture", "get_shots_texture");
	
    ClassDB::bind_method(D_METHOD("get_shots_material"), &BulletInterface::get_shots_material);
	ClassDB::bind_method(D_METHOD("set_shots_material", "p_shots_material"), &BulletInterface::set_shots_material);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Shots/Material", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_shots_material", "get_shots_material");
	
    ClassDB::bind_method(D_METHOD("get_shots_material_add"), &BulletInterface::get_shots_material_add);
	ClassDB::bind_method(D_METHOD("set_shots_material_add", "p_shots_material_add"), &BulletInterface::set_shots_material_add);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Shots/Material (Add)", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_shots_material_add", "get_shots_material_add");

// ---
    ClassDB::bind_method(D_METHOD("get_items_texture"), &BulletInterface::get_items_texture);
	ClassDB::bind_method(D_METHOD("set_items_texture", "p_items_texture"), &BulletInterface::set_items_texture);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Items/Texture", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "Texture2D"
        ), "set_items_texture", "get_items_texture");
	
    ClassDB::bind_method(D_METHOD("get_items_material"), &BulletInterface::get_items_material);
	ClassDB::bind_method(D_METHOD("set_items_material", "p_items_material"), &BulletInterface::set_items_material);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Items/Material", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_items_material", "get_items_material");
	
    ClassDB::bind_method(D_METHOD("get_items_material_add"), &BulletInterface::get_items_material_add);
	ClassDB::bind_method(D_METHOD("set_items_material_add", "p_items_material_add"), &BulletInterface::set_items_material_add);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Items/Material (Add)", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_items_material_add", "get_items_material_add");
		
// ---
    ClassDB::bind_method(D_METHOD("get_particles_texture"), &BulletInterface::get_particles_texture);
	ClassDB::bind_method(D_METHOD("set_particles_texture", "p_particles_texture"), &BulletInterface::set_particles_texture);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Particles/Texture", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "Texture2D"
        ), "set_particles_texture", "get_particles_texture");
	
    ClassDB::bind_method(D_METHOD("get_particles_material"), &BulletInterface::get_particles_material);
	ClassDB::bind_method(D_METHOD("set_particles_material", "p_particles_material"), &BulletInterface::set_particles_material);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Particles/Material", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_particles_material", "get_particles_material");
	
    ClassDB::bind_method(D_METHOD("get_particles_material_add"), &BulletInterface::get_particles_material_add);
	ClassDB::bind_method(D_METHOD("set_particles_material_add", "p_particles_material_add"), &BulletInterface::set_particles_material_add);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Particles/Material (Add)", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_particles_material_add", "get_particles_material_add");

// ---
    ClassDB::bind_method(D_METHOD("get_lasers_texture"), &BulletInterface::get_lasers_texture);
	ClassDB::bind_method(D_METHOD("set_lasers_texture", "p_lasers_texture"), &BulletInterface::set_lasers_texture);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Lasers/Texture", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "Texture2D"
        ), "set_lasers_texture", "get_lasers_texture");
	
    ClassDB::bind_method(D_METHOD("get_lasers_material"), &BulletInterface::get_lasers_material);
	ClassDB::bind_method(D_METHOD("set_lasers_material", "p_lasers_material"), &BulletInterface::set_lasers_material);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Lasers/Material", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_lasers_material", "get_lasers_material");
	
    ClassDB::bind_method(D_METHOD("get_lasers_material_add"), &BulletInterface::get_lasers_material_add);
	ClassDB::bind_method(D_METHOD("set_lasers_material_add", "p_lasers_material_add"), &BulletInterface::set_lasers_material_add);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Lasers/Material (Add)", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_lasers_material_add", "get_lasers_material_add");
		
    ClassDB::bind_method(D_METHOD("get_curve_lasers_material"), &BulletInterface::get_curve_lasers_material);
	ClassDB::bind_method(D_METHOD("set_curve_lasers_material", "p_curve_lasers_material"), &BulletInterface::set_curve_lasers_material);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Lasers/Curve Laser Material", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_curve_lasers_material", "get_curve_lasers_material");
	
    ClassDB::bind_method(D_METHOD("get_curve_lasers_material_add"), &BulletInterface::get_curve_lasers_material_add);
	ClassDB::bind_method(D_METHOD("set_curve_lasers_material_add", "p_curve_lasers_material_add"), &BulletInterface::set_curve_lasers_material_add);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Lasers/Curve Laser Material (Add)", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_curve_lasers_material_add", "get_curve_lasers_material_add");

// ---
    ClassDB::bind_method(D_METHOD("get_laser_spawns_texture"), &BulletInterface::get_laser_spawns_texture);
	ClassDB::bind_method(D_METHOD("set_laser_spawns_texture", "p_laser_spawns_texture"), &BulletInterface::set_laser_spawns_texture);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Lasers/Spawn Texture", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "Texture2D"
        ), "set_laser_spawns_texture", "get_laser_spawns_texture");
	
    ClassDB::bind_method(D_METHOD("get_laser_spawns_material_add"), &BulletInterface::get_laser_spawns_material_add);
	ClassDB::bind_method(D_METHOD("set_laser_spawns_material_add", "p_laser_spawns_material_add"), &BulletInterface::set_laser_spawns_material_add);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Lasers/Spawn Material (Add)", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_laser_spawns_material_add", "get_laser_spawns_material_add");

	ClassDB::bind_method(D_METHOD("get_bullets_fade_time"), &BulletInterface::get_bullets_fade_time);
	ClassDB::bind_method(D_METHOD("set_bullets_fade_time", "p_bullets_fade_time"), &BulletInterface::set_bullets_fade_time);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Bullets/Fade-in Time"), "set_bullets_fade_time", "get_bullets_fade_time");
	
	ClassDB::bind_method(D_METHOD("get_shots_fade_time"), &BulletInterface::get_shots_fade_time);
	ClassDB::bind_method(D_METHOD("set_shots_fade_time", "p_shots_fade_time"), &BulletInterface::set_shots_fade_time);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Shots/Fade-in Time"), "set_shots_fade_time", "get_shots_fade_time");
	
	ClassDB::bind_method(D_METHOD("get_items_fade_time"), &BulletInterface::get_items_fade_time);
	ClassDB::bind_method(D_METHOD("set_items_fade_time", "p_items_fade_time"), &BulletInterface::set_items_fade_time);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Items/Spin-in Time"), "set_items_fade_time", "get_items_fade_time");
	
    ClassDB::bind_method(D_METHOD("get_items_gravity"), &BulletInterface::get_items_gravity);
	ClassDB::bind_method(D_METHOD("set_items_gravity", "p_items_gravity"), &BulletInterface::set_items_gravity);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "Items/Gravity"), "set_items_gravity", "get_items_gravity");
	
    ClassDB::bind_method(D_METHOD("get_items_damp"), &BulletInterface::get_items_damp);
	ClassDB::bind_method(D_METHOD("set_items_damp", "p_items_damp"), &BulletInterface::set_items_damp);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Items/Dampening"), "set_items_damp", "get_items_damp");
	
    ClassDB::bind_method(D_METHOD("get_items_magnet_strength"), &BulletInterface::get_items_magnet_strength);
	ClassDB::bind_method(D_METHOD("set_items_magnet_strength", "p_items_magnet_strength"), &BulletInterface::set_items_magnet_strength);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Items/Magnet Strength"), "set_items_magnet_strength", "get_items_magnet_strength");

	ClassDB::bind_method(D_METHOD("get_bullet_sheet_orientation"), &BulletInterface::get_bullet_sheet_orientation);
	ClassDB::bind_method(D_METHOD("set_bullet_sheet_orientation", "p_bullet_sheet_orientation"), &BulletInterface::set_bullet_sheet_orientation);
	ADD_PROPERTY(PropertyInfo(
		Variant::INT, 
		"Bullets/Spritesheet Rotation Offset",
		PROPERTY_HINT_ENUM,
		"Up,Right,Down,Left"
	), "set_bullet_sheet_orientation", "get_bullet_sheet_orientation");
	
	ClassDB::bind_method(D_METHOD("get_shot_sheet_orientation"), &BulletInterface::get_shot_sheet_orientation);
	ClassDB::bind_method(D_METHOD("set_shot_sheet_orientation", "p_shot_sheet_orientation"), &BulletInterface::set_shot_sheet_orientation);
	ADD_PROPERTY(PropertyInfo(
		Variant::INT, 
		"Shots/Spritesheet Rotation Offset",
		PROPERTY_HINT_ENUM,
		"Up,Right,Down,Left"
	), "set_shot_sheet_orientation", "get_shot_sheet_orientation");

	ClassDB::bind_method(D_METHOD("get_laser_sheet_orientation"), &BulletInterface::get_laser_sheet_orientation);
	ClassDB::bind_method(D_METHOD("set_laser_sheet_orientation", "p_laser_sheet_orientation"), &BulletInterface::set_laser_sheet_orientation);
	ADD_PROPERTY(PropertyInfo(
		Variant::INT, 
		"Lasers/Spritesheet Rotation Offset",
		PROPERTY_HINT_ENUM,
		"Up,Right,Down,Left"
	), "set_laser_sheet_orientation", "get_laser_sheet_orientation");
	

	/* #endregion */
	
	/* #region Misc Getters */
	ClassDB::bind_method(D_METHOD(
		"get_active_bullets"), 
		&BulletInterface::get_active_bullets
	);
	ClassDB::bind_method(D_METHOD(
		"get_active_shots"), 
		&BulletInterface::get_active_shots
	);
	ClassDB::bind_method(D_METHOD(
		"get_active_items"), 
		&BulletInterface::get_active_items
	);
	ClassDB::bind_method(D_METHOD(
		"get_active_particles"), 
		&BulletInterface::get_active_particles
	);
	ClassDB::bind_method(D_METHOD(
		"get_active_enemies"), 
		&BulletInterface::get_active_enemies
	);
	ClassDB::bind_method(D_METHOD(
		"get_active_lasers"), 
		&BulletInterface::get_active_lasers
	);
	ClassDB::bind_method(D_METHOD(
		"get_active_curve_lasers"), 
		&BulletInterface::get_active_curve_lasers
	);

	/* #endregion */

	/* #region Create Functions */

	ClassDB::bind_method(D_METHOD(
		"init",
		"root"), 
		&BulletInterface::init
	);

	ClassDB::bind_method(D_METHOD(
		"unmount"), 
		&BulletInterface::unmount
	);

	ClassDB::bind_method(D_METHOD(
		"create_bullet_a1",
		"position",
		"speed",
		"angle",
		"bullet_data",
		"glow"), 
		&BulletInterface::create_bullet_a1
	);

	ClassDB::bind_method(D_METHOD(
		"create_bullet_a2",
		"position",
		"speed",
		"angle",
		"accel",
		"max_speed",
		"w_vel",
		"bullet_data",
		"glow"), 
		&BulletInterface::create_bullet_a2
	);

	ClassDB::bind_method(D_METHOD(
		"create_bullet_b1",
		"position",
		"velocity",
		"accel",
		"max_velocity",
		"rotation_follows_movement",
		"shot_data",
		"glow"), 
		&BulletInterface::create_bullet_b1
	);


	ClassDB::bind_method(D_METHOD(
		"create_shot_a1",
		"position",
		"speed",
		"angle",
		"shot_data",
		"glow"), 
		&BulletInterface::create_shot_a1
	);

	ClassDB::bind_method(D_METHOD(
		"create_shot_a2",
		"position",
		"speed",
		"angle",
		"accel",
		"max_speed",
		"w_vel",
		"shot_data",
		"glow"), 
		&BulletInterface::create_shot_a2
	);


	ClassDB::bind_method(D_METHOD(
		"create_item",
		"position",
		"speed",
		"angle",
		"spin",
		"item_data",
		"glow"), 
		&BulletInterface::create_item
	);

	ClassDB::bind_method(D_METHOD(
		"create_enemy",
		"hitbox_size",
		"hurtbox_size",
		"deletes_bullets"), 
		&BulletInterface::create_enemy
	);
	
	ClassDB::bind_method(D_METHOD(
		"create_straight_laser",
		"position",
		"angle",
		"length",
		"width",
		"start_margin",
		"end_margin",
		"delay",
		"duration",
		"laser_data",
		"glow"), 
		&BulletInterface::create_straight_laser
	);
	
	// PackedInt64Array create_curve_laser(Vector2 pos, double speed, double angle, int length, double width, int start_margin, int end_margin, PackedFloat64Array laser_data, bool glow);
	
	ClassDB::bind_method(D_METHOD(
		"create_curve_laser",
		"position",
		"speed",
		"angle",
		"length",
		"width",
		"start_margin",
		"end_margin",
		"laser_data",
		"glow"), 
		&BulletInterface::create_curve_laser
	);
	/* #endregion */
	
	/* #region Set/Get Property Functions */

	ClassDB::bind_method(D_METHOD(
		"get_damage",
		"bullet_id"), 
		&BulletInterface::get_damage
	);
	// ---
	ClassDB::bind_method(D_METHOD(
		"set_damage",
		"bullet_id",
		"damage"), 
		&BulletInterface::set_damage
	);
	// ---
	ClassDB::bind_method(D_METHOD(
		"get_damage_type",
		"bullet_id"), 
		&BulletInterface::get_damage_type
	);

	// ---
	ClassDB::bind_method(D_METHOD(
		"get_lifetime",
		"bullet_id"), 
		&BulletInterface::get_lifetime
	);
	ClassDB::bind_method(D_METHOD(
		"set_lifetime",
		"bullet_id",
		"lifetime"), 
		&BulletInterface::set_lifetime
	);
	// ---
	ClassDB::bind_method(D_METHOD(
		"get_lifespan",
		"bullet_id"), 
		&BulletInterface::get_lifespan
	);
	ClassDB::bind_method(D_METHOD(
		"set_lifespan",
		"bullet_id",
		"lifespan"), 
		&BulletInterface::set_lifespan
	);
	// ---
	ClassDB::bind_method(D_METHOD(
		"get_pierce",
		"bullet_id"), 
		&BulletInterface::get_pierce
	);
	ClassDB::bind_method(D_METHOD(
		"set_pierce",
		"bullet_id",
		"pierce"), 
		&BulletInterface::set_pierce
	);
	// ---
	ClassDB::bind_method(D_METHOD(
		"get_item_type",
		"item_id"), 
		&BulletInterface::get_item_type
	);
	
	// ---
	ClassDB::bind_method(D_METHOD(
		"set_item_magnet",
		"item_id",
		"target"), 
		&BulletInterface::set_item_magnet
	);
	// ---
	ClassDB::bind_method(D_METHOD(
		"get_position",
		"bullet_id"), 
		&BulletInterface::get_position
	);
	ClassDB::bind_method(D_METHOD(
		"set_position",
		"bullet_id",
		"position"), 
		&BulletInterface::set_position
	);
	// ---
	ClassDB::bind_method(D_METHOD(
		"get_spin",
		"bullet_id"), 
		&BulletInterface::get_spin
	);
	ClassDB::bind_method(D_METHOD(
		"set_spin",
		"bullet_id",
		"spin"), 
		&BulletInterface::set_spin
	);
	// ---
	ClassDB::bind_method(D_METHOD(
		"get_rotation",
		"bullet_id"), 
		&BulletInterface::get_rotation
	);
	ClassDB::bind_method(D_METHOD(
		"set_rotation",
		"bullet_id",
		"rotation"), 
		&BulletInterface::set_rotation
	);
	// ---
	ClassDB::bind_method(D_METHOD(
		"get_wvel",
		"bullet_id"), 
		&BulletInterface::get_wvel
	);
	ClassDB::bind_method(D_METHOD(
		"set_wvel",
		"bullet_id",
		"wvel"), 
		&BulletInterface::set_wvel
	);
	// ---
	ClassDB::bind_method(D_METHOD(
		"get_layer",
		"bullet_id"), 
		&BulletInterface::get_layer
	);
	// ---
	ClassDB::bind_method(D_METHOD(
		"set_layer",
		"bullet_id",
		"layer"), 
		&BulletInterface::set_layer
	);
	// ---

	/* #endregion */

	/* #region Actions */

	ClassDB::bind_method(D_METHOD(
		"clear_entity",
		"id"), 
		&BulletInterface::clear_entity
	);

	ClassDB::bind_method(D_METHOD(
		"collide_and_graze_player",
		"position",
		"hitbox_radius",
		"graze_radius"), 
		&BulletInterface::collide_and_graze_player
	);
	
	ClassDB::bind_method(D_METHOD(
		"clear_bullets",
		"position",
		"radius",
		"ignore_pierce"), 
		&BulletInterface::clear_bullets
	);

	ClassDB::bind_method(D_METHOD(
		"collide_enemy",
		"position",
		"hitbox_radius"), 
		&BulletInterface::collide_enemy
	);

	ClassDB::bind_method(D_METHOD(
		"collect_and_magnet_items",
		"position",
		"target_node",
		"collection_radius",
		"magnet_radius"), 
		&BulletInterface::collect_and_magnet_items
	);
		
	ClassDB::bind_method(D_METHOD(
		"magnet_all_items",
		"target_node"), 
		&BulletInterface::magnet_all_items
	);
	
	ClassDB::bind_method(D_METHOD(
		"get_enemy_collisions",
		"enemy_id"), 
		&BulletInterface::get_enemy_collisions
	);

	ClassDB::bind_method(D_METHOD(
		"skip_fade",
		"id"), 
		&BulletInterface::skip_fade
	);

// ------------------------

//add_bullet_transform_a2(PackedInt64Array bullet_id, TransformTrigger trigger, int trigger_value, double speed, double angle, double accel, double max_speed, double w_vel) {

	ClassDB::bind_method(D_METHOD(
		"add_bullet_transform_a2",
		"bullet_id",
		"trigger",
		"trigger_value",
		"speed",
		"angle",
		"accel",
		"max_speed",
		"w_vel"
	), 
		&BulletInterface::add_bullet_transform_a2
	);
	


	/* #endregion */

	/* #region Query Functions */
	ClassDB::bind_method(D_METHOD(
		"get_enemies_in_range",
		"position",
		"radius"
	), &BulletInterface::get_enemies_in_range
	);

	ClassDB::bind_method(D_METHOD(
		"is_valid",
		"id"
	), &BulletInterface::is_valid
	);

	/* #endregion */
}

/* #region GetSetters */
// Property getters and setters

int BulletInterface::get_total_bullets() {
	return total_bullets;
}
void BulletInterface::set_total_bullets(int bullets) {
	total_bullets = bullets;
}

int BulletInterface::get_total_shots() {
	return total_shots;
}
void BulletInterface::set_total_shots(int shots) {
	total_shots = shots;
}

int BulletInterface::get_total_items() {
	return total_items;
}
void BulletInterface::set_total_items(int items) {
	total_items = items;
}

int BulletInterface::get_total_particles() {
	return total_particles;
}

void BulletInterface::set_total_particles(int particles) {
	total_particles = particles;
}

int BulletInterface::get_total_enemies() {
	return total_enemies;
}

void BulletInterface::set_total_enemies(int enemies) {
	total_enemies = enemies;
}

int BulletInterface::get_total_lasers() {
	return total_lasers;
}

void BulletInterface::set_total_lasers(int lasers) {
	total_lasers = lasers;
}

int BulletInterface::get_total_curve_lasers() {
	return total_curve_lasers;
}

void BulletInterface::set_total_curve_lasers(int lasers) {
	total_curve_lasers = lasers;
}

int BulletInterface::get_bullets_z_index() {
	return bullets_z_index;
}
void BulletInterface::set_bullets_z_index(int index) {
	bullets_z_index = index;
}

int BulletInterface::get_shots_z_index() {
	return shots_z_index;
}
void BulletInterface::set_shots_z_index(int index) {
	shots_z_index = index;
}

int BulletInterface::get_items_z_index() {
	return items_z_index;
}
void BulletInterface::set_items_z_index(int index) {
	items_z_index = index;
}

int BulletInterface::get_particles_z_index() {
	return particles_z_index;
}
void BulletInterface::set_particles_z_index(int index) {
	particles_z_index = index;
}

int BulletInterface::get_lasers_z_index() {
	return lasers_z_index;
}
void BulletInterface::set_lasers_z_index(int index) {
	lasers_z_index = index;
}



Ref<Texture2D> BulletInterface::get_bullets_texture() {
	return bullets_texture;
}
void BulletInterface::set_bullets_texture(Ref<Texture2D> texture) {
	bullets_texture = texture;
}
Ref<Material> BulletInterface::get_bullets_material() {
	return bullets_material;
}
void BulletInterface::set_bullets_material(Ref<Material> material) {
	bullets_material = material;
}
Ref<Material> BulletInterface::get_bullets_material_add() {
	return bullets_material_add;
}
void BulletInterface::set_bullets_material_add(Ref<Material> material) {
	bullets_material_add = material;
}



Ref<Texture2D> BulletInterface::get_shots_texture() {
	return shots_texture;
}
void BulletInterface::set_shots_texture(Ref<Texture2D> texture) {
	shots_texture = texture;
}
Ref<Material> BulletInterface::get_shots_material() {
	return shots_material;
}
void BulletInterface::set_shots_material(Ref<Material> material) {
	shots_material = material;
}
Ref<Material> BulletInterface::get_shots_material_add() {
	return shots_material_add;
}
void BulletInterface::set_shots_material_add(Ref<Material> material) {
	shots_material_add = material;
}

Ref<Texture2D> BulletInterface::get_items_texture() {
	return items_texture;
}
void BulletInterface::set_items_texture(Ref<Texture2D> texture) {
	items_texture = texture;
}
Ref<Material> BulletInterface::get_items_material() {
	return items_material;
}
void BulletInterface::set_items_material(Ref<Material> material) {
	items_material = material;
}
Ref<Material> BulletInterface::get_items_material_add() {
	return items_material_add;
}
void BulletInterface::set_items_material_add(Ref<Material> material) {
	items_material_add = material;
}


Ref<Texture2D> BulletInterface::get_particles_texture() {
	return particles_texture;
}
void BulletInterface::set_particles_texture(Ref<Texture2D> texture) {
	particles_texture = texture;
}
Ref<Material> BulletInterface::get_particles_material() {
	return particles_material;
}
void BulletInterface::set_particles_material(Ref<Material> material) {
	particles_material = material;
}
Ref<Material> BulletInterface::get_particles_material_add() {
	return particles_material_add;
}
void BulletInterface::set_particles_material_add(Ref<Material> material) {
	particles_material_add = material;
}


Ref<Texture2D> BulletInterface::get_lasers_texture() {
	return lasers_texture;
}
void BulletInterface::set_lasers_texture(Ref<Texture2D> texture) {
	lasers_texture = texture;
}
Ref<Material> BulletInterface::get_lasers_material() {
	return lasers_material;
}
void BulletInterface::set_lasers_material(Ref<Material> material) {
	lasers_material = material;
}
Ref<Material> BulletInterface::get_lasers_material_add() {
	return lasers_material_add;
}
void BulletInterface::set_lasers_material_add(Ref<Material> material) {
	lasers_material_add = material;
}

Ref<Material> BulletInterface::get_curve_lasers_material() {
	return curve_lasers_material;
}
void BulletInterface::set_curve_lasers_material(Ref<Material> material) {
	curve_lasers_material = material;
}
Ref<Material> BulletInterface::get_curve_lasers_material_add() {
	return curve_lasers_material_add;
}
void BulletInterface::set_curve_lasers_material_add(Ref<Material> material) {
	curve_lasers_material_add = material;
}


Ref<Texture2D> BulletInterface::get_laser_spawns_texture() {
	return laser_spawns_texture;
}
void BulletInterface::set_laser_spawns_texture(Ref<Texture2D> texture) {
	laser_spawns_texture = texture;
}
// Ref<Material> BulletInterface::get_laser_spawns_material() {
// 	return laser_spawns_material;
// }
// void BulletInterface::set_laser_spawns_material(Ref<Material> material) {
// 	laser_spawns_material = material;
// }
Ref<Material> BulletInterface::get_laser_spawns_material_add() {
	return laser_spawns_material_add;
}
void BulletInterface::set_laser_spawns_material_add(Ref<Material> material) {
	laser_spawns_material_add = material;
}


Rect2 BulletInterface::get_bounce_rect() {
	return bounce_rect;
}
void BulletInterface::set_bounce_rect(Rect2 rect) {
	bounce_rect = rect;
}

Rect2 BulletInterface::get_bullet_active_rect() {
	return bullet_active_rect;
}
void BulletInterface::set_bullet_active_rect(Rect2 rect) {
	bullet_active_rect = rect;
}

Rect2 BulletInterface::get_shot_active_rect() {
	return shot_active_rect;
}
void BulletInterface::set_shot_active_rect(Rect2 rect) {
	shot_active_rect = rect;
}

double BulletInterface::get_time_scale() {
	return time_scale;
}
void BulletInterface::set_time_scale(double ts) {
	time_scale = ts;
}

double BulletInterface::get_bullets_fade_time() {
	return bullets_fade_time;	
}
void BulletInterface::set_bullets_fade_time(double time) {
	bullets_fade_time = time;
}

double BulletInterface::get_shots_fade_time() {
	return shots_fade_time;
}
void BulletInterface::set_shots_fade_time(double time) {
	shots_fade_time = time;
}

double BulletInterface::get_items_fade_time() {
	return items_fade_time;
}
void BulletInterface::set_items_fade_time(double time) {
	items_fade_time = time;
}

double BulletInterface::get_lasers_fade_time() {
	return lasers_fade_time;
}
void BulletInterface::set_lasers_fade_time(double time) {
	lasers_fade_time = time;
}


Vector2 BulletInterface::get_items_gravity() {
	return items_gravity;
}
void BulletInterface::set_items_gravity(Vector2 gravity) {
	items_gravity = gravity;
}


double BulletInterface::get_items_damp() {
	return items_damp;
}
void BulletInterface::set_items_damp(double damp) {
	items_damp = damp;
}
double BulletInterface::get_items_magnet_strength() {
	return items_magnet_strength;
}
void BulletInterface::set_items_magnet_strength(double magnet_strength) {
	items_magnet_strength = magnet_strength;
}


int BulletInterface::get_bullet_sheet_orientation() {
	return bullet_sheet_orientation;
}
void BulletInterface::set_bullet_sheet_orientation(int orientation) {
	bullet_sheet_orientation = (SheetOrientation)orientation;
}

int BulletInterface::get_shot_sheet_orientation() {
	return shot_sheet_orientation;
}
void BulletInterface::set_shot_sheet_orientation(int orientation) {
	shot_sheet_orientation = (SheetOrientation)orientation;
}

int BulletInterface::get_laser_sheet_orientation() {
	return laser_sheet_orientation;
}
void BulletInterface::set_laser_sheet_orientation(int orientation) {
	laser_sheet_orientation = (SheetOrientation)orientation;
}


/* #endregion */

/* #region Getters w/o setters */

int BulletInterface::get_active_bullets() {
	return active_bullets;
}
int BulletInterface::get_active_shots() {
	return active_shots;
}
int BulletInterface::get_active_items() {
	return active_items;
}
int BulletInterface::get_active_particles() {
	return active_particles;
}
int BulletInterface::get_active_enemies() {
	return active_enemies;
}
int BulletInterface::get_active_lasers() {
	return active_lasers;
}
int BulletInterface::get_active_curve_lasers() {
	return active_curve_lasers;
}

/* #endregion */


BulletInterface::BulletInterface() { }

// TODO: fix crash when quit to selection
BulletInterface::~BulletInterface() {
	// Free memory

	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}

	unmount();
}

// Currently bugged, crashes when run
void BulletInterface::unmount() {
	mounted = false;

	// UtilityFunctions::print("Bullets delete start");
	if (bullets_created) {
		for (int i = total_bullets-1; i >= 0; --i) {
			rendering_server->free_rid(bullet_pool[i]->item_rid);
			memdelete(bullet_pool[i]);
		}
		// memdelete_arr(bullet_pool);
		memdelete_arr(persistent_bullet_index);
		if (bullets_canvas_item.is_valid()) rendering_server->free_rid(bullets_canvas_item);
		bullets_created = false;
	}
	// UtilityFunctions::print("Bullets delete end");

	// UtilityFunctions::print("Shots delete start");
	if (shots_created) {
		for (int i = total_shots-1; i >= 0; --i) {
			rendering_server->free_rid(shot_pool[i]->item_rid);
			memdelete(shot_pool[i]);
		}
		memdelete_arr(shot_pool);
		memdelete_arr(persistent_shot_index);
		if (shots_canvas_item.is_valid()) rendering_server->free_rid(shots_canvas_item);
		shots_created = false;
	}
	// UtilityFunctions::print("Shots delete end");

	// UtilityFunctions::print("Items delete start");
	if (items_created) {
		for (int i = total_items-1; i >= 0; --i) {
			rendering_server->free_rid(item_pool[i]->item_rid);
			memdelete(item_pool[i]);
		}
		memdelete_arr(item_pool);
		memdelete_arr(persistent_item_index);
		if (items_canvas_item.is_valid()) rendering_server->free_rid(items_canvas_item);
		items_created = false;
	}
	// UtilityFunctions::print("Items delete end");

	// UtilityFunctions::print("Particles delete start");
	if (particles_created) {
		for (int i = total_particles-1; i >= 0; --i) {
			rendering_server->free_rid(particle_pool[i]->item_rid);
			memdelete(particle_pool[i]);
		}
		memdelete_arr(particle_pool);
		memdelete_arr(persistent_particle_index);
		if (particles_canvas_item.is_valid()) rendering_server->free_rid(particles_canvas_item);
		particles_created = false;
	}
	// UtilityFunctions::print("Particles delete end");

	if (enemies_created) {
		for (int i = total_enemies-1; i >= 0; --i) {
			memdelete(enemy_pool[i]);
		}

		memdelete_arr(enemy_pool);
		memdelete_arr(persistent_enemy_index);
		enemies_created = false;
	}

	// UtilityFunctions::print("Lasers delete start");
	if (lasers_created) {
		for (int i = total_lasers-1; i >= 0; --i) {
			rendering_server->free_rid(laser_pool[i]->item_rid);
			rendering_server->free_rid(laser_pool[i]->spawn_item_rid);
			memdelete(laser_pool[i]);
		}

		memdelete_arr(laser_pool);
		memdelete_arr(persistent_laser_index);
		if (lasers_canvas_item.is_valid()) rendering_server->free_rid(lasers_canvas_item);
		lasers_created = false;
	}
	// UtilityFunctions::print("Lasers delete end");
	
	// UtilityFunctions::print("Curve delete start");
	if (curve_lasers_created) {
		for (int i = total_curve_lasers-1; i >= 0; --i) {
			rendering_server->free_rid(curve_laser_pool[i]->item_rid);
			// rendering_server->free_rid(curve_laser_pool[i]->spawn_item_rid);
			// rendering_server->free_rid(curve_laser_pool[i]->mesh_rid);
			memdelete(curve_laser_pool[i]);
		}
		memdelete_arr(curve_laser_pool);
		memdelete_arr(persistent_curve_laser_index);
		if (curve_lasers_canvas_item.is_valid()) rendering_server->free_rid(curve_lasers_canvas_item);
		curve_lasers_created = false;
	}
	// UtilityFunctions::print("Curve delete end");

}


void BulletInterface::init(Node2D* root) {
	mounted = true;
	rendering_server = RenderingServer::get_singleton();
	canvas_parent = root->get_canvas_item();

	active_bullets = 0;
	active_shots = 0;
	active_items = 0;
	active_particles = 0;
	active_enemies = 0;
	active_lasers = 0;
	active_curve_lasers = 0;

	if (bullet_sheet_orientation == SHEET_UP) {
		bullet_rotation_offset = M_PI_2;
	} else if (bullet_sheet_orientation == SHEET_LEFT) {
		bullet_rotation_offset = M_PI;
	} else if (bullet_sheet_orientation == SHEET_DOWN) {
		bullet_rotation_offset = -M_PI_2;
	} else {
		bullet_rotation_offset = 0.0;
	}

	if (shot_sheet_orientation == SHEET_UP) {
		shot_rotation_offset = M_PI_2;
	} else if (shot_sheet_orientation == SHEET_LEFT) {
		shot_rotation_offset = M_PI;
	} else if (shot_sheet_orientation == SHEET_DOWN) {
		shot_rotation_offset = -M_PI_2;
	} else {
		shot_rotation_offset = 0.0;
	}

	if (laser_sheet_orientation == SHEET_UP) {
		laser_rotation_offset = M_PI_2;
	} else if (laser_sheet_orientation == SHEET_LEFT) {
		laser_rotation_offset = M_PI;
	} else if (laser_sheet_orientation == SHEET_DOWN) {
		laser_rotation_offset = -M_PI_2;
	} else {
		laser_rotation_offset = 0.0;
	}


	if (bullet_active_rect.size.x <= 0.0 || bullet_active_rect.size.y <= 0.0) {
		godot::UtilityFunctions::push_warning("Bullet active rect has one or more bounds less than or equal to zero; bullets will instantly be despawned.");
	}
	if (shot_active_rect.size.x <= 0.0 || shot_active_rect.size.y <= 0.0) {
		godot::UtilityFunctions::push_warning("Shot active rect has one or more bounds less than or equal to zero; bullets will instantly be despawned.");
	}
	

	if (bounce_rect.size.x <= 0.0 || bounce_rect.size.y <= 0.0) {
		godot::UtilityFunctions::push_warning("Bounce rect has one or more bounds less than or equal to zero; bullets will not bounce properly.");
	}

	// --------------------

	if (bullets_texture.is_null()) {
		godot::UtilityFunctions::push_error("Bullet texture is missing; bullets will be disabled until fixed.");
		total_bullets = 0;		// Remove bullets entirely
		available_bullets = 0;
	} else if (bullets_material.is_null() || bullets_material_add.is_null()) {
		godot::UtilityFunctions::push_error("Bullet material is missing; bullets will be disabled until fixed.");
		total_bullets = 0;		// Remove bullets entirely
		available_bullets = 0;
	} else if (total_bullets == 0) {
		godot::UtilityFunctions::push_error("Bullet pool size is 0!");
		available_bullets = 0;
	} else {
		bullets_texture_rid = bullets_texture->get_rid();
		bullets_material_rid = bullets_material->get_rid();
		bullets_material_add_rid = bullets_material_add->get_rid();
		bullets_texture_width = bullets_texture->get_size().x;
		available_bullets = total_bullets;
		bullet_pool = memnew_arr(Bullet*, total_bullets);
		persistent_bullet_index = memnew_arr(int, total_bullets);
		bullets_created = true;
		_init_bullets();
	}
	
	if (shots_texture.is_null()) {
		godot::UtilityFunctions::push_error("Shot texture is missing; shots will be disabled until fixed.");
		total_shots = 0;		// Remove shots entirely
		available_shots = 0;
	} else if (shots_material.is_null() || shots_material_add.is_null()) {
		godot::UtilityFunctions::push_error("Shot material is missing; shots will be disabled until fixed.");
		total_shots = 0;		// Remove shots entirely
		available_shots = 0;
	} else if (total_shots == 0) {
		godot::UtilityFunctions::push_error("Shot pool size is 0!");
		available_shots = 0;
	} else {
		shots_texture_rid = shots_texture->get_rid();
		shots_material_rid = shots_material->get_rid();
		shots_material_add_rid = shots_material_add->get_rid();
		shots_texture_width = shots_texture->get_size().x;
		available_shots = total_shots;
		shot_pool = memnew_arr(Bullet*, total_shots);
		persistent_shot_index = memnew_arr(int, total_shots);
		shots_created = true;
		_init_shots();
	}

	if (items_texture.is_null()) {
		godot::UtilityFunctions::push_error("Item texture is missing; items will be disabled until fixed.");
		total_items = 0;		// Remove items entirely
		available_items = 0;
	} else if (items_material.is_null() || items_material_add.is_null()) {
		godot::UtilityFunctions::push_error("Item material is missing; items will be disabled until fixed.");
		total_items = 0;		// Remove items entirely
		available_items = 0;
	
	} else if (total_items == 0) {
		godot::UtilityFunctions::push_error("Item pool size is 0!");
		available_items = 0;
	} else {
		items_texture_rid = items_texture->get_rid();
		items_material_rid = items_material->get_rid();
		items_material_add_rid = items_material_add->get_rid();
		items_texture_width = items_texture->get_size().x;
		available_items = total_items;
		item_pool = memnew_arr(Item*, total_items);
		persistent_item_index = memnew_arr(int, total_items);
		items_created = true;
		_init_items();
	}

	if (particles_texture.is_null()) {
		godot::UtilityFunctions::push_error("Particle texture is missing; particles will be disabled until fixed.");
		total_particles = 0;		// Remove particles entirely
		available_particles = 0;
	} else if (particles_material.is_null() || particles_material_add.is_null()) {
		godot::UtilityFunctions::push_error("Particle material is missing; particles will be disabled until fixed.");
		total_particles = 0;		// Remove particles entirely
		available_particles = 0;
	
	} else if (total_particles == 0) {
		godot::UtilityFunctions::push_error("Particle pool size is 0!");
		available_particles = 0;
	} else {
		particles_texture_rid = particles_texture->get_rid();
		particles_material_rid = particles_material->get_rid();
		particles_material_add_rid = particles_material_add->get_rid();
		particles_texture_width = particles_texture->get_size().x;
		available_particles = total_particles;
		particle_pool = memnew_arr(Particle*, total_particles);
		persistent_particle_index = memnew_arr(int, total_particles);
		particles_created = true;
		_init_particles();
	}

	if (total_enemies == 0) {
		godot::UtilityFunctions::push_error("Enemy pool size is 0!");
		available_enemies = 0;
	} else {
		available_enemies = total_enemies;
		enemy_pool = memnew_arr(Enemy*, total_enemies);
		persistent_enemy_index = memnew_arr(int, total_enemies);
		enemies_created = true;
		_init_enemies();
	}

	if (lasers_texture.is_null() || laser_spawns_texture.is_null()) {
		godot::UtilityFunctions::push_error("Laser texture is missing; lasers will be disabled until fixed.");
		total_lasers = 0;		// Remove bullets entirely
		available_lasers = 0;
	} else if (lasers_material.is_null() || lasers_material_add.is_null() || laser_spawns_material_add.is_null() || curve_lasers_material.is_null() || curve_lasers_material_add.is_null() ) { // || laser_spawns_material.is_null()
		godot::UtilityFunctions::push_error("Laser material is missing; lasers will be disabled until fixed.");
		total_lasers = 0;		// Remove bullets entirely
		available_lasers = 0;
	} else if (total_lasers >= 0 || total_curve_lasers >= 0) {
		lasers_texture_rid = lasers_texture->get_rid();
		lasers_material_rid = lasers_material->get_rid();
		lasers_material_add_rid = lasers_material_add->get_rid();
		curve_lasers_material_rid = curve_lasers_material->get_rid();
		curve_lasers_material_add_rid = curve_lasers_material_add->get_rid();

		laser_spawns_texture_rid = laser_spawns_texture->get_rid();
		// laser_spawns_material_rid = laser_spawns_material->get_rid();
		laser_spawns_material_add_rid = laser_spawns_material_add->get_rid();
		
		lasers_texture_width = lasers_texture->get_size().x;
		laser_spawns_texture_width = laser_spawns_texture->get_size().x;
		
		if (total_lasers >= 0) {
			available_lasers = total_lasers;
			laser_pool = memnew_arr(Laser*, total_lasers);
			persistent_laser_index = memnew_arr(int, total_lasers);
			lasers_created = true;
			_init_lasers();
		} else {
			godot::UtilityFunctions::push_error("Laser pool size is 0!");
			available_lasers = 0;
		}
		
		if (total_curve_lasers >= 0) {
			available_curve_lasers = total_curve_lasers;
			curve_laser_pool = memnew_arr(CurveLaser*, total_curve_lasers);
			persistent_curve_laser_index = memnew_arr(int, total_curve_lasers);
			curve_lasers_created = true;
			_init_curve_lasers();
		} else {
			godot::UtilityFunctions::push_error("Curve laser pool size is 0!");
			available_curve_lasers = 0;
		}
	} else {
			godot::UtilityFunctions::push_error("Laser pool sizes are 0!");
			available_lasers = 0;
			available_curve_lasers = 0;

	}
	

	// Set invalid ids

	invalid_id = PackedInt64Array();
	invalid_id.resize(3);
	invalid_id.set(0, -1);
	invalid_id.set(1, -1);
	invalid_id.set(2, -1);
	
	invalid_collide_and_graze_array = Array();
	invalid_collide_and_graze_array.append(Array());
	invalid_collide_and_graze_array.append(Array());
}

void BulletInterface::_init_bullets() {
	bullets_canvas_item = rendering_server->canvas_item_create();
	
	rendering_server->canvas_item_set_parent(bullets_canvas_item, canvas_parent);
	rendering_server->canvas_item_set_z_index(bullets_canvas_item, bullets_z_index);

	// Create each bullet
	for (int i = 0; i < total_bullets; ++i) {
		Bullet* bullet = memnew(Bullet);

		bullet_pool[i] = bullet;
		bullet->item_rid = rendering_server->canvas_item_create();
		rendering_server->canvas_item_set_parent(bullet->item_rid, bullets_canvas_item);
		rendering_server->canvas_item_set_material(bullet->item_rid, bullets_material_rid);

		bullet->pool_index = i;
		bullet->persistent_index = i;
		persistent_bullet_index[i] = i;
	}
}

void BulletInterface::_init_shots() {
	shots_canvas_item = rendering_server->canvas_item_create();
	
	rendering_server->canvas_item_set_parent(shots_canvas_item, canvas_parent);
	rendering_server->canvas_item_set_z_index(shots_canvas_item, shots_z_index);

	// Create each bullet
	for (int i = 0; i < total_shots; ++i) {
		Bullet* bullet = memnew(Bullet);

		shot_pool[i] = bullet;
		bullet->item_rid = rendering_server->canvas_item_create();
		rendering_server->canvas_item_set_parent(bullet->item_rid, shots_canvas_item);
		rendering_server->canvas_item_set_material(bullet->item_rid, shots_material_rid);

		bullet->pool_index = i;
		bullet->persistent_index = i;
		persistent_shot_index[i] = i;
	}
}

void BulletInterface::_init_items() {
	items_canvas_item = rendering_server->canvas_item_create();
	
	rendering_server->canvas_item_set_parent(items_canvas_item, canvas_parent);
	rendering_server->canvas_item_set_z_index(items_canvas_item, items_z_index);

	// Create each bullet
	for (int i = 0; i < total_items; ++i) {
		Item* item = memnew(Item);

		item_pool[i] = item;
		item->item_rid = rendering_server->canvas_item_create();
		rendering_server->canvas_item_set_parent(item->item_rid, items_canvas_item);
		rendering_server->canvas_item_set_material(item->item_rid, items_material_rid);

		item->pool_index = i;
		item->persistent_index = i;
		persistent_item_index[i] = i;
	}
}

void BulletInterface::_init_particles() {
	particles_canvas_item = rendering_server->canvas_item_create();
	
	rendering_server->canvas_item_set_parent(particles_canvas_item, canvas_parent);
	rendering_server->canvas_item_set_z_index(particles_canvas_item, particles_z_index);

	// Create each bullet
	for (int i = 0; i < total_particles; ++i) {
		Particle* particle = memnew(Particle);

		particle_pool[i] = particle;
		particle->item_rid = rendering_server->canvas_item_create();
		rendering_server->canvas_item_set_parent(particle->item_rid, particles_canvas_item);
		rendering_server->canvas_item_set_material(particle->item_rid, particles_material_rid);

		particle->pool_index = i;
		particle->persistent_index = i;
		persistent_particle_index[i] = i;

	}
}

void BulletInterface::_init_enemies() {
	// Create each enemy
	for (int i = 0; i < total_enemies; ++i) {
		Enemy* enemy = memnew(Enemy);
		enemy->collided_bullets = Array();

		enemy_pool[i] = enemy;

		enemy->pool_index = i;
		enemy->persistent_index = i;
		persistent_enemy_index[i] = i;
	}
}

void BulletInterface::_init_lasers() {
	lasers_canvas_item = rendering_server->canvas_item_create();
	
	rendering_server->canvas_item_set_parent(lasers_canvas_item, canvas_parent);
	rendering_server->canvas_item_set_z_index(lasers_canvas_item, lasers_z_index);

	// Create each laser
	for (int i = 0; i < total_lasers; ++i) {
		Laser* laser = memnew(Laser);

		laser_pool[i] = laser;
		laser->item_rid = rendering_server->canvas_item_create();
		rendering_server->canvas_item_set_parent(laser->item_rid, lasers_canvas_item);
		rendering_server->canvas_item_set_material(laser->item_rid, lasers_material_rid);
		
		laser->spawn_item_rid = rendering_server->canvas_item_create();
		rendering_server->canvas_item_set_parent(laser->spawn_item_rid, lasers_canvas_item);
		rendering_server->canvas_item_set_material(laser->spawn_item_rid, laser_spawns_material_add_rid);

		laser->pool_index = i;
		laser->persistent_index = i;
		persistent_laser_index[i] = i;
	}
}

void BulletInterface::_init_curve_lasers() {
	if (!lasers_canvas_item.is_valid()) {
		lasers_canvas_item = rendering_server->canvas_item_create();
		
		rendering_server->canvas_item_set_parent(lasers_canvas_item, canvas_parent);
		rendering_server->canvas_item_set_z_index(lasers_canvas_item, lasers_z_index);
	}

	curve_lasers_canvas_item = rendering_server->canvas_item_create();
	curve_lasers_add_canvas_item = rendering_server->canvas_item_create();
	curve_lasers_mesh_item = rendering_server->mesh_create();
	curve_lasers_add_mesh_item = rendering_server->mesh_create();
	
	rendering_server->canvas_item_set_parent(curve_lasers_canvas_item, canvas_parent);
	rendering_server->canvas_item_set_parent(curve_lasers_add_canvas_item, canvas_parent);
	rendering_server->canvas_item_set_z_index(curve_lasers_canvas_item, lasers_z_index);
	rendering_server->canvas_item_set_z_index(curve_lasers_add_canvas_item, lasers_z_index);
	rendering_server->canvas_item_set_transform(curve_lasers_canvas_item, Transform2D());
	rendering_server->canvas_item_set_transform(curve_lasers_add_canvas_item, Transform2D());

	rendering_server->canvas_item_add_mesh(curve_lasers_canvas_item, curve_lasers_mesh_item, Transform2D(), Color(1.0, 1.0, 1.0, 1.0), lasers_texture_rid);
	rendering_server->canvas_item_add_mesh(curve_lasers_add_canvas_item, curve_lasers_add_mesh_item, Transform2D(), Color(1.0, 1.0, 1.0, 1.0), lasers_texture_rid);

	rendering_server->canvas_item_set_material(curve_lasers_canvas_item, curve_lasers_material_rid);
	rendering_server->canvas_item_set_material(curve_lasers_add_canvas_item, curve_lasers_material_add_rid);


	// Create each curve laser
	for (int i = 0; i < total_curve_lasers; ++i) {
		CurveLaser* laser = memnew(CurveLaser);

		curve_laser_pool[i] = laser;
		laser->item_rid = rendering_server->canvas_item_create();
		rendering_server->canvas_item_set_parent(laser->item_rid, lasers_canvas_item);
		rendering_server->canvas_item_set_material(laser->item_rid, laser_spawns_material_add_rid);
		rendering_server->canvas_item_set_transform(laser->item_rid, Transform2D());
		
		// laser->spawn_item_rid = rendering_server->canvas_item_create();
		// rendering_server->canvas_item_set_parent(laser->spawn_item_rid, lasers_canvas_item);
		// rendering_server->canvas_item_set_material(laser->spawn_item_rid, laser_spawns_material_add_rid);
		
		// laser->mesh_rid = rendering_server->mesh_create();

		laser->pool_index = i;
		laser->persistent_index = i;
		persistent_curve_laser_index[i] = i;
	}
}

void BulletInterface::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	
	if (!mounted) {
		return;
	}

	if (!canvas_parent.is_valid()) {
		return;
	}

	// Increase by golden-ration - 1 to have "maximum" "randomness"
    // Independent from time scale to preserve this effect
	animation_random += 0.61803398874989484820; 
	if (animation_random >= 1.0) animation_random -= 1.0;


	for (int i = total_bullets - 1; i >= available_bullets; --i) {
		Bullet* bullet = bullet_pool[i];
		if (_process_bullet(bullet, time_scale, false, false, bullet_active_rect)) {
			_release_bullet(i);
			i += 1;
			continue;
		}
		rendering_server->canvas_item_set_transform(bullet->item_rid, bullet->transform);

	}
	
	for (int i = total_shots - 1; i >= available_shots; --i) {
		Bullet* shot = shot_pool[i];
		if (_process_bullet(shot, time_scale, false, false, shot_active_rect)) {
			_release_shot(i);
			i += 1;
			continue;
		}
		rendering_server->canvas_item_set_transform(shot->item_rid, shot->transform);
	}
	
	for (int i = total_items - 1; i >= available_items; --i) {
		Item* item = item_pool[i];
		if (_process_item(item, time_scale)) {
			_release_item(i);
			i += 1;
			continue;
		}
		rendering_server->canvas_item_set_transform(item->item_rid, item->transform);
	}
	
	for (int i = total_particles - 1; i >= available_particles; --i) {
		Particle* particle = particle_pool[i];
		if (_process_particle(particle, time_scale)) {
			_release_particle(i);
			i += 1;
			continue;
		}
		// rendering_server->canvas_item_set_transform(particle->item_rid, particle->transform);
	}

	for (int i = total_enemies - 1; i >= available_enemies; --i) {
		Enemy* enemy = enemy_pool[i];
		if (_process_enemy(enemy, time_scale)) {
			_release_enemy(i);
			i += 1;
			continue;
		}
	}

	for (int i = total_lasers - 1; i >= available_lasers; --i) {
		Laser* laser = laser_pool[i];
		if (_process_laser(laser, time_scale)) {
			_release_laser(i);
			i += 1;
			continue;
		}
		rendering_server->canvas_item_set_transform(laser->item_rid, laser->transform);

	}

	// Clear mesh surfaces to redraw them
	rendering_server->mesh_clear(curve_lasers_mesh_item);
	rendering_server->mesh_clear(curve_lasers_add_mesh_item);
	

	for (int i = total_curve_lasers - 1; i >= available_curve_lasers; --i) {
		CurveLaser* laser = curve_laser_pool[i];
		if (_process_curve_laser(laser, time_scale)) {
			_release_curve_laser(i);
			i += 1;
			continue;
		}
	}

}

bool BulletInterface::_process_bullet(Bullet* bullet, double delta, bool skip_fade, bool skip_rect_check, Rect2 active_rect) {
	Vector2 origin = bullet->position;

    int bounce_count = 0;

    if (bullet->process_mode < B1) {
        if (bullet->process_mode == A1) _process_bullet_a1(bullet, delta);
        else if (bullet->process_mode == A2) _process_bullet_a2(bullet, delta);
        else bounce_count = _process_bullet_a3(bullet, delta);
    } else {
        if (bullet->process_mode == B1) _process_bullet_b1(bullet, delta);
	}
    if (bullet->spin) {
        bullet->transform.rotate(bullet->spin * delta);
        bullet->rotation += bullet->spin * delta;
    }

    // Decrease fade-in timer
	if (!skip_fade) _fade_in_bullet(bullet, delta);

    // Auto delete conditions, outside bounds or lifespan depleted
    if (
		(!active_rect.has_point(bullet->position) && bullet->auto_delete && !skip_rect_check) || 
		(bullet->lifetime >= bullet->lifespan && (!bullet->fade_delete || bullet->fade_timer >= bullet->fade_time))
	) {
		return true;
    }


    // Iterate over existing transformations, TODO
    bool transform_applied = false;
    int j = 0;
    for (int i = 0; i < bullet->transforms.size(); i++) {
        Array xform = bullet->transforms[i];
        bool should_apply = false;
        TransformTrigger trigger = (TransformTrigger)(int)xform[TRANSFORM_STRUCTURE_TRIGGER_METHOD];
        
        // Check if the conditions are met and flag if so.
        switch (trigger) {
            case TRIGGER_TIME: // Time
                xform[TRANSFORM_STRUCTURE_TRIGGER_VALUE] = (double)xform[TRANSFORM_STRUCTURE_TRIGGER_VALUE] - delta;
                if ((double)xform[TRANSFORM_STRUCTURE_TRIGGER_VALUE] <= 0.0) {
                    should_apply = true;
                    transform_applied = true;
                    xform[TRANSFORM_STRUCTURE_TRIGGER_VALUE] = 0.0;
                } else {
                    bullet->transforms[j] = xform;
                    j++;
                }
                break;
        }

        if (should_apply) {
			TransformProperty property = (TransformProperty)(int)xform[TRANSFORM_STRUCTURE_PROPERTY];

			switch (property) {
				case TRANSFORM_ACCEL: {
					double accel = (double)xform[TRANSFORM_STRUCTURE_VALUE];
					bullet->accel = accel;
					break;
				}
				case TRANSFORM_MAX_SPEED: {
					double max_speed = (double)xform[TRANSFORM_STRUCTURE_VALUE];
					bullet->max_speed = max_speed;
					break;
				}
				case TRANSFORM_WVEL: {
					double wvel = (double)xform[TRANSFORM_STRUCTURE_VALUE];
					bullet->wvel = wvel;
					break;
				}
			}
        }
    }

    // Update position and other data if a transformation has been made
    if (transform_applied) {
        
        bullet->transforms.resize(j);

        // bullet->direction = Vector2(1.0, 0.0).rotated(bullet->angle);
        // bullet->transform = bullet->transform.scaled((bullet->scale / bullet->transform.get_scale().x) * Vector2(1.0, 1.0)).rotated(
		// 	bullet->angle - bullet->transform.get_rotation() + bullet_rotation_offset + bullet->rotation
		// );
        // // bullet->transform.set_origin(bullet->position);
        // rendering_server->canvas_item_set_draw_index(bullet->item_rid, (bullet->layer << 24) + bullet->draw_index);
    }
	bullet->transform.set_origin(bullet->position);

    // Bullet is still alive, increase its lifetime.
    bullet->lifetime += delta;
    // Return false if the bullet should not be deleted yet.
    return false;

}

void BulletInterface::_process_bullet_a1(Bullet* bullet, double delta) {
    bullet->position += bullet->direction * bullet->speed * delta;
    bullet->transform.set_origin(bullet->position);
}

void BulletInterface::_process_bullet_a2(Bullet* bullet, double delta) {
    if (bullet->wvel) {
        bullet->direction = bullet->direction.rotated(bullet->wvel * delta);
        bullet->angle += bullet->wvel * delta;
        bullet->transform.rotate(bullet->wvel * delta);
    }

    if (bullet->accel && bullet->speed != bullet->max_speed) {
        bullet->speed += bullet->accel * delta;
        if (((bullet->speed - bullet->max_speed) * bullet->accel) > 0.0) bullet->speed = bullet->max_speed;
    }

    _process_bullet_a1(bullet, delta);
}

int BulletInterface::_process_bullet_a3(Bullet* bullet, double delta) {
    if (bullet->waccel && bullet->wvel != bullet->max_wvel) {
        bullet->wvel += bullet->waccel * delta;
        if (((bullet->wvel - bullet->max_wvel) * bullet->waccel) > 0.0) bullet->wvel = bullet->max_wvel;
    }
    _process_bullet_a2(bullet, delta);

    return _process_bullet_a3_after(bullet, delta);
}

int BulletInterface::_process_bullet_a3_after(Bullet* bullet, double delta) {

    int bounce_count = 0;

    int bounce_mode = bullet->bounce_mode;

	bool vertical_bounced = false;
	bool horizontal_bounced = false;

    // Bullet bounce/warp handling 
    // Vertical edges
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
        }
    }
    // Horizontal edges
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
	}

    return bounce_count;
}


void BulletInterface::_process_bullet_b1(Bullet* bullet, double delta) {
	bullet->direction += bullet->b_accel;
	if (bullet->b_accel.x != 0.0 && bullet->direction.x * Math::sign(bullet->b_accel.x) > Math::abs(bullet->b_max_velocity.x)) {
		bullet->direction.x = bullet->b_max_velocity.x;
	}
	if (bullet->b_accel.y != 0.0 && bullet->direction.y * Math::sign(bullet->b_accel.y) > Math::abs(bullet->b_max_velocity.y)) {
		bullet->direction.y = bullet->b_max_velocity.y;
	}
	
	float new_angle = Math::atan2(bullet->direction.y, bullet->direction.x);
	if (bullet->rotation_follows_movement) bullet->transform.rotate(new_angle - bullet->angle);
	bullet->angle = new_angle;

    bullet->position += bullet->direction * delta;
    bullet->transform.set_origin(bullet->position);
}


bool BulletInterface::_process_item(Item* item, double delta) {
	
    Vector2 last_pos = item->position;
    if (item->fade_timer) {
        item->fade_timer -= delta;
        item->position += item->speed * item->direction * delta;
        if (delta == 1.0) {
            item->speed *= items_damp;
        } else {
            item->speed *= powf(items_damp, delta);
        }
        Transform2D xform = item->transform.rotated(item->spin);
        if (item->fade_timer <= 0.0) {
            item->fade_timer = 0.0;
            xform = xform.rotated(-xform.get_rotation());
        }
        xform.set_origin(item->position);
        item->transform = xform;

    } else if (item->is_magneted) {
        if (item->fade_timer) {
            item->fade_timer = 0.0;
            item->transform = item->transform.rotated(-item->transform.get_rotation());
        }
        Node2D *node = item->magnet_target;

        double angle = ((Vector2)node->get_position()).angle_to_point(item->position);
        item->position -= Vector2(items_magnet_strength * delta, 0.0).rotated(angle + item_sheet_orientation);

    } else {
        item->position += items_gravity * delta;

    }

    // If above the top of the screen, show an arrow instead. 
    // This is marked by setting the b channel in the item data to 1
    if (item->position.y < bounce_rect.position.y - item->scale * 0.5) { 
        Vector2 pos = item->position;
        pos.y = item->scale * 0.5;
        item->transform = item->transform.rotated(-item->transform.get_rotation());
        item->transform.set_origin(pos);
        Color color = item->bullet_data;
        color.b = 1.0;
        rendering_server->canvas_item_set_modulate(item->item_rid, color);

    } else { 
        if (last_pos.y < bounce_rect.position.y - item->scale * 0.5) {
            Color color = item->bullet_data;
            rendering_server->canvas_item_set_modulate(item->item_rid, color);
        }
        item->transform.set_origin(item->position);

    }
    
    if(item->position.y > bullet_active_rect.get_end().y + item->scale * 0.5 || item->lifetime >= item->lifespan) {
        return true;
    }

    // Item is still alive, increase its lifetime.
    item->lifetime += delta;
    // Return false if the item should not be deleted yet.
    return false;
}

// TODO
bool BulletInterface::_process_particle(Particle* particle, double delta) {
    // Particle is still alive, increase its lifetime.
    particle->lifetime += delta * 0.25;

	Color color = particle->bullet_data;
	color.a = particle->lifetime / particle->lifespan;

	rendering_server->canvas_item_set_modulate(particle->item_rid, color);
    // Return false if the particle should not be deleted yet.
    return (particle->lifetime >= particle->lifespan);
}


bool BulletInterface::_process_enemy(Enemy* enemy, double delta) {
	if (enemy->queue_delete) return true;
	
	double hitbox_radius = enemy->hitbox_size;
	enemy->collided_bullets.clear();

	// Remove bullets from collided list if the bullet id is no longer valid
	for (int i = enemy->lifetime_collided_bullets.size() - 1; i >= 0; --i) {
		PackedInt64Array id = enemy->lifetime_collided_bullets[i];
		Bullet* bullet = shot_pool[persistent_shot_index[id[BULLET_ID_INDEX]]];
		if (bullet->cycle != id[BULLET_ID_CYCLE]) {
			enemy->lifetime_collided_bullets.remove_at(i);
		}
	}

	for (int i = total_shots - 1; i >= available_shots; --i) {
		Bullet* bullet = shot_pool[i];
		
		double b = bullet->scale * bullet->hitbox_scale;
		double b2 = b * b;
		double dist_sq = (bullet->position - enemy->position).length_squared();

		if (bullet->fade_timer <= 0.0 && (dist_sq < hitbox_radius * hitbox_radius + 2.0 * hitbox_radius * b + b2)) {
			PackedInt64Array bullet_id = PackedInt64Array();
			bullet_id.resize(3);
			bullet_id.set(BULLET_ID_CYCLE, bullet->cycle);
			bullet_id.set(BULLET_ID_POOL, SHOTS_POOL);
			bullet_id.set(BULLET_ID_INDEX, bullet->persistent_index);

			if (bullet->pierce || !enemy->deletes_bullets) {
				// Don't collide with a bullet twice
				if (enemy->lifetime_collided_bullets.has(bullet_id)) continue;
				enemy->lifetime_collided_bullets.append(bullet_id);
			} else {
				bullet->lifespan = -INFINITY;
			}

			enemy->collided_bullets.append(bullet_id);
		}
	}
	return false;
}

bool BulletInterface::_process_laser(Laser* laser, double delta) {
	// Mostly can use bullet logic
	bool to_return = _process_bullet(laser, delta, false, true, bullet_active_rect);

	to_return = to_return || (
		!bullet_active_rect.has_point(laser->position) &&
		!bullet_active_rect.has_point(laser->position + laser->direction * laser->length) && 
		laser->auto_delete
	);

	// Move laser spawn graphics
	// Rotate glow randomly
	// Transform2D xform = laser->spawn_transform.rotated(double(rand()) / double(RAND_MAX) * Math_TAU);
	laser->spawn_transform.rotate(double(rand()) / double(RAND_MAX) * Math_TAU);
	// Reposition back to the middle
	laser->spawn_transform.set_origin(laser->position);
	rendering_server->canvas_item_set_transform(laser->spawn_item_rid, laser->spawn_transform);
	
	return to_return;
}

bool BulletInterface::_process_curve_laser(CurveLaser* laser, double delta) {
	// Mostly can use bullet logic
	bool to_return = _process_bullet(laser, delta, true, true, bullet_active_rect);
	// Check if both first and last points are both offscreen, or if the laser's cut length is non-positive.
	to_return = to_return || (
		!bullet_active_rect.has_point(laser->position) &&
		!bullet_active_rect.has_point(laser->points[laser->length-1]) &&
		laser->auto_delete) || 
	(laser->mesh_end_node_index <= laser->mesh_start_node_index) ||
	(laser->collision_end_node_index <= laser->collision_start_node_index);

	// Deal with the spawn glow
	// if (laser->fading) {
		laser->fade_timer -= delta;
		if (laser->fade_timer > 0.0) {
			// Move laser spawn graphics
			// Rotate glow randomly
			// Transform2D xform = laser->spawn_transform.rotated(double(rand()) / double(RAND_MAX) * Math_TAU);
			laser->spawn_transform.rotate(double(rand()) / double(RAND_MAX) * Math_TAU);
			// Reposition back to the middle
			laser->spawn_transform.set_origin(laser->start_position);
			rendering_server->canvas_item_set_transform(laser->item_rid, laser->spawn_transform);
		} else {
			// laser->fading = false;
			laser->fade_timer = 0.0;
			rendering_server->canvas_item_clear(laser->item_rid);
		}
	// }
	
	// Update the points and verts
	for (int i = laser->length - 1; i > 0; --i) {
		laser->points[i] = laser->points[i-1];
		laser->vertices[2*i] = laser->vertices[2*i-2];
		laser->vertices[2*i+1] = laser->vertices[2*i-1];
	}

	// Set the new leader points and verts
	laser->points[0] = laser->position;

	Vector2 normal = Vector2(0.0, laser->width * 0.5).rotated(laser->angle);
	laser->vertices[0] = laser->position + normal;
	laser->vertices[1] = laser->position - normal;

	// Set up the mesh array to create the mesh surface with
	Array mesh_array = Array();
	mesh_array.resize(rendering_server->ARRAY_MAX);
	mesh_array[rendering_server->ARRAY_VERTEX] = laser->vertices;
	mesh_array[rendering_server->ARRAY_TEX_UV] = laser->uvs;
	mesh_array[rendering_server->ARRAY_CUSTOM0] = laser->custom0s;

	// Add the surface to the mesh depending on glow or not
	RID mesh_item = laser->additive ? curve_lasers_add_mesh_item : curve_lasers_mesh_item;

	rendering_server->mesh_add_surface_from_arrays(
		mesh_item,
		rendering_server->PRIMITIVE_TRIANGLE_STRIP, 
		mesh_array,
		Array(), Dictionary(), 
		(
			rendering_server->ARRAY_FLAG_USE_2D_VERTICES |
			rendering_server->ARRAY_FORMAT_VERTEX |
			rendering_server->ARRAY_FORMAT_TEX_UV |
			rendering_server->ARRAY_FORMAT_CUSTOM0 |
			rendering_server->ARRAY_CUSTOM_RGBA_FLOAT << rendering_server->ARRAY_FORMAT_CUSTOM0_SHIFT

		)

	);

	return to_return;
}


void BulletInterface::_fade_in_bullet(Bullet* bullet, double delta) {
	if (bullet->lifetime < bullet->lifespan) {
		if (bullet->fade_timer > 0.0) {
			bullet->fade_timer -= delta;

			if (bullet->fade_timer <= 0.0) {
				bullet->fade_timer = 0.0;
				bullet->bullet_data.b = bullet->texture_offset;
				rendering_server->canvas_item_set_modulate(bullet->item_rid, bullet->bullet_data);
			} else {
				bullet->bullet_data.b = bullet->texture_offset + (Math::min(1.0, bullet->fade_timer / bullet->fade_time) - 0.001);
				rendering_server->canvas_item_set_modulate(bullet->item_rid, bullet->bullet_data);
			}
		}
	} else if (bullet->fade_delete) {
		bullet->fade_timer += delta;

		bullet->bullet_data.b = bullet->texture_offset + (Math::min(1.0, bullet->fade_timer / bullet->fade_time) - 0.001);
		rendering_server->canvas_item_set_modulate(bullet->item_rid, bullet->bullet_data);
	}
    
}

void BulletInterface::_release_bullet(int index) {
	Bullet* bullet = bullet_pool[index];

	rendering_server->canvas_item_clear(bullet->item_rid);
	bullet->cycle += 1;

	// Swap the now deleted bullet and the lowest active bullet 
	_swap(bullet_pool[index], bullet_pool[available_bullets]);
	_swap(bullet_pool[index]->pool_index, bullet_pool[available_bullets]->pool_index);
	// After the swap, update the persistent indices
	persistent_bullet_index[bullet_pool[index]->persistent_index] = bullet_pool[index]->pool_index;
	persistent_bullet_index[bullet_pool[available_bullets]->persistent_index] = bullet_pool[available_bullets]->pool_index;

	available_bullets += 1;
	active_bullets -= 1;
}

void BulletInterface::_release_shot(int index) {
	Bullet* bullet = shot_pool[index];

	// Disable the bullet
	rendering_server->canvas_item_clear(bullet->item_rid);
	bullet->cycle += 1;

	// Swap the now deleted bullet and the lowest active bullet 
	_swap(shot_pool[index], shot_pool[available_shots]);
	_swap(shot_pool[index]->pool_index, shot_pool[available_shots]->pool_index);
	// After the swap, update the persistent indices
	persistent_shot_index[shot_pool[index]->persistent_index] = shot_pool[index]->pool_index;
	persistent_shot_index[shot_pool[available_shots]->persistent_index] = shot_pool[available_shots]->pool_index;

	available_shots += 1;
	active_shots -= 1;
}

void BulletInterface::_release_item(int index) {
	Item* item = item_pool[index];

	// Disable the item
	rendering_server->canvas_item_clear(item->item_rid);

	item->cycle += 1;

	// Swap the now deleted item and the lowest active item 
	_swap(item_pool[index], item_pool[available_items]);
	_swap(item_pool[index]->pool_index, item_pool[available_items]->pool_index);
	// After the swap, update the persistent indices
	persistent_item_index[item_pool[index]->persistent_index] = item_pool[index]->pool_index;
	persistent_item_index[item_pool[available_items]->persistent_index] = item_pool[available_items]->pool_index;

	available_items += 1;
	active_items -= 1;
}

void BulletInterface::_release_particle(int index) {
	Particle* particle = particle_pool[index];

	// Disable the particle
	rendering_server->canvas_item_clear(particle->item_rid);

	particle->cycle += 1;

	// Swap the now deleted particle and the lowest active particle 
	_swap(particle_pool[index], particle_pool[available_particles]);
	_swap(particle_pool[index]->pool_index, particle_pool[available_particles]->pool_index);
	// After the swap, update the persistent indices
	persistent_particle_index[particle_pool[index]->persistent_index] = particle_pool[index]->pool_index;
	persistent_particle_index[particle_pool[available_particles]->persistent_index] = particle_pool[available_particles]->pool_index;

	available_particles += 1;
	active_particles -= 1;
}

void BulletInterface::_release_enemy(int index) {
	Enemy* enemy = enemy_pool[index];

	enemy->collided_bullets.clear();
	enemy->lifetime_collided_bullets.clear();

	enemy->cycle += 1;

	// Swap the now deleted particle and the lowest active particle 
	_swap(enemy_pool[index], enemy_pool[available_enemies]);
	_swap(enemy_pool[index]->pool_index, enemy_pool[available_enemies]->pool_index);
	// After the swap, update the persistent indices
	persistent_enemy_index[enemy_pool[index]->persistent_index] = enemy_pool[index]->pool_index;
	persistent_enemy_index[enemy_pool[available_enemies]->persistent_index] = enemy_pool[available_enemies]->pool_index;

	available_enemies += 1;
	active_enemies -= 1;
}

void BulletInterface::_release_laser(int index) {
	Laser* laser = laser_pool[index];

	rendering_server->canvas_item_clear(laser->item_rid);
	rendering_server->canvas_item_clear(laser->spawn_item_rid);
	laser->cycle += 1;

	// Swap the now deleted laser and the lowest active laser 
	_swap(laser_pool[index], laser_pool[available_lasers]);
	_swap(laser_pool[index]->pool_index, laser_pool[available_lasers]->pool_index);
	// After the swap, update the persistent indices
	persistent_laser_index[laser_pool[index]->persistent_index] = laser_pool[index]->pool_index;
	persistent_laser_index[laser_pool[available_lasers]->persistent_index] = laser_pool[available_lasers]->pool_index;

	available_lasers += 1;
	active_lasers -= 1;
}

void BulletInterface::_release_curve_laser(int index) {
	CurveLaser* laser = curve_laser_pool[index];

	laser->points.clear();
	laser->vertices.clear();
	laser->uvs.clear();

	// rendering_server->mesh_clear(laser->mesh_rid);
	rendering_server->canvas_item_clear(laser->item_rid);
	// rendering_server->canvas_item_clear(laser->spawn_item_rid);

	laser->cycle += 1;

	// Swap the now deleted laser and the lowest active laser 
	_swap(curve_laser_pool[index], curve_laser_pool[available_curve_lasers]);
	_swap(curve_laser_pool[index]->pool_index, curve_laser_pool[available_curve_lasers]->pool_index);
	// After the swap, update the persistent indices
	persistent_curve_laser_index[curve_laser_pool[index]->persistent_index] = curve_laser_pool[index]->pool_index;
	persistent_curve_laser_index[curve_laser_pool[available_curve_lasers]->persistent_index] = curve_laser_pool[available_curve_lasers]->pool_index;

	available_curve_lasers += 1;
	active_curve_lasers -= 1;
}

// TODO: Rewrite completely, it currently crashes if the return is removed.
void BulletInterface::_cut_curve_laser(CurveLaser* laser, int collision_point) {
	return;
	// godot::UtilityFunctions::print("a");
	// Radius around the collision point to also delete
	int margin = 4;

	// Don't cut the laser if we hit it at the very front
	if (collision_point < laser->mesh_start_node_index + margin) return;
	if (collision_point > laser->mesh_end_node_index - margin) return;

	// Values for multiple use
	int front_laser_mesh_start_index = laser->mesh_start_node_index;
	int front_laser_mesh_end_index = collision_point - margin;
	int back_laser_mesh_start_index = collision_point + margin;
	int back_laser_mesh_end_index = laser->mesh_end_node_index;

	int front_laser_sub_length = front_laser_mesh_end_index - front_laser_mesh_start_index;
	int back_laser_sub_length = back_laser_mesh_end_index - back_laser_mesh_start_index;

	// Adjust the collision margins for the first laser
	laser->collision_start_node_index = laser->mesh_start_node_index + (laser->start_margin * front_laser_sub_length) / (laser->length - 1) + 1;
	laser->collision_end_node_index = laser->mesh_end_node_index - (laser->end_margin * front_laser_sub_length) / (laser->length - 1) + 1;

	// Create a duplicate of the first laser.
	
	int back_laser_start_margin = (laser->start_margin * back_laser_sub_length) / (laser->length - 1) + 1;
	int back_laser_end_margin = (laser->end_margin * back_laser_sub_length) / (laser->length - 1) + 1;

	// New laser
	PackedInt64Array new_id = create_curve_laser(
		laser->start_position, laser->speed, laser->angle, laser->length-1, laser->width, 
		back_laser_start_margin,
		back_laser_end_margin,
		laser->laser_data_copy,
		laser->additive
	);
	
	// godot::UtilityFunctions::print("c");
	// TODO, check new_id is real and act properly on it
	if (new_id == invalid_id) return;

	CurveLaser* new_laser = curve_laser_pool[persistent_curve_laser_index[new_id[BULLET_ID_INDEX]]];
	// Copy over laser specific stuff
	new_laser->position = laser->position;
	new_laser->points = laser->points.duplicate();
	new_laser->vertices = laser->vertices.duplicate();
	new_laser->start_margin = laser->start_margin; // Fix margins for if this laser gets cut again
	new_laser->end_margin = laser->end_margin;
	// godot::UtilityFunctions::print("d");
	
	// Make the back laser have the start glow instead, front laser loses that now.
	if (laser->fade_timer > 0.0) {
		new_laser->fade_timer = laser->fade_timer;
		laser->fade_timer = 0.0;
	} else {
		new_laser->fade_timer = 0.0;
		// new_laser->fading = false;
		rendering_server->canvas_item_clear(new_laser->item_rid);
	}
	// godot::UtilityFunctions::print("e");

	// TODO: will need to hae more data get copied over such as transforms
	new_laser->process_mode = laser->process_mode;
	new_laser->max_speed = laser->max_speed;
	new_laser->accel = laser->accel;
	new_laser->bounce_mode = laser->bounce_mode;
	new_laser->bounce_count = laser->bounce_count;
	new_laser->bounce_surfaces = laser->bounce_surfaces;
	new_laser->wvel = laser->wvel;
	new_laser->waccel = laser->waccel;
	new_laser->max_wvel = laser->max_wvel;

	// Update the start and end of the mesh anchors.
	new_laser->mesh_end_node_index = back_laser_mesh_end_index;
	new_laser->mesh_start_node_index = back_laser_mesh_start_index;
	laser->mesh_end_node_index = front_laser_mesh_end_index;
	
	// godot::UtilityFunctions::print("f");

	// Update UV values of the lasers

	// Front laser we only have to update values from the start node, earlier ones are already 0.0
	double front_laser_length = Math::max(front_laser_sub_length - 1.0, 1.0);
	
	// Pad the head with 0.0s
	for (int i = 0; i < front_laser_mesh_start_index; ++i) {
		new_laser->uvs[2*i] = Vector2(0.0, 0.0);
		new_laser->uvs[2*i+1] = Vector2(1.0, 0.0);
	}
	// Calculate body
	for (int i = front_laser_mesh_start_index; i < front_laser_mesh_end_index; ++i) {
		new_laser->uvs[2*i] = Vector2(0.0, double(i - front_laser_mesh_start_index) / front_laser_length);
		new_laser->uvs[2*i+1] = Vector2(1.0, double(i - front_laser_mesh_start_index) / front_laser_length);
	}
	// Pad the remaining tail with 1.0s
	for (int i = front_laser_mesh_end_index; i < laser->length; ++i) {
		new_laser->uvs[2*i] = Vector2(0.0, 1.0);
		new_laser->uvs[2*i+1] = Vector2(1.0, 1.0);
	}


	// Back laser we only have to update values upto the end note 
	double back_laser_length = Math::max(back_laser_sub_length - 1.0, 1.0);

	// Pad the head with 0.0s
	for (int i = 0; i < back_laser_mesh_start_index; ++i) {
		laser->uvs[2*i] = Vector2(0.0, 0.0);
		laser->uvs[2*i+1] = Vector2(1.0, 0.0);
	}
	// Calculate body
	for (int i = back_laser_mesh_start_index; i < back_laser_mesh_end_index; ++i) {
		laser->uvs[2*i] = Vector2(0.0, double(i - back_laser_mesh_start_index) / back_laser_length);
		laser->uvs[2*i+1] = Vector2(1.0, double(i - back_laser_mesh_start_index) / back_laser_length);
	}
	// Pad the remaining tail with 1.0s
	for (int i = back_laser_mesh_end_index; i < new_laser->length; ++i) {
		laser->uvs[2*i] = Vector2(0.0, 1.0);
		laser->uvs[2*i+1] = Vector2(1.0, 1.0);
	}
	
	// godot::UtilityFunctions::print("---");
}

// ---

void BulletInterface::enable_bullet(Bullet* bullet) {
	bullet->pierce = false;
    bullet->auto_delete = true;
    bullet->is_grazed = false;
    bullet->lifetime = 0.0;
    bullet->lifespan = INFINITY;
    bullet->rotation = 0.0;
	// bullet->fading_out = false;
    bullet->fade_delete = true;
    // bullet->fading = true;
    bullet->transforms.clear();
    bullet->custom_data.clear();
	// TODO: Add customisation
	bullet->fade_time = bullets_fade_time;
	bullet->fade_timer = bullets_fade_time;
}

void BulletInterface::enable_shot(Bullet* shot) {
	shot->pierce = false;
    shot->auto_delete = true;
    shot->is_grazed = false;
    shot->lifetime = 0.0;
    shot->lifespan = INFINITY;
    shot->rotation = 0.0;
    // shot->fading = true;
    shot->transforms.clear();
    shot->custom_data.clear();
	// TODO: Add customisation
	shot->fade_time = shots_fade_time;
	shot->fade_timer = shots_fade_time;
}

void BulletInterface::enable_enemy(Enemy* enemy) {
	enemy->queue_delete = false;
	enemy->collided_bullets.clear();
	enemy->position = Vector2(-100000000.0, -100000000.0); // I hate this but fuck it whatever
}

void BulletInterface::enable_laser(Laser* laser) {
	laser->pierce = true;
    laser->auto_delete = true;
    laser->is_grazed = false;
    laser->lifetime = 0.0;
    laser->lifespan = INFINITY;
    laser->rotation = 0.0;
    // laser->fading = true;
    laser->fade_delete = true;
    laser->transforms.clear();
    laser->custom_data.clear();
	// TODO: Add customisation
	laser->fade_time = lasers_fade_time;
	laser->fade_timer = lasers_fade_time;
}

void BulletInterface::enable_curve_laser(CurveLaser* laser) {
	laser->pierce = true;
    laser->auto_delete = true;
    laser->is_grazed = false;
    laser->lifetime = 0.0;
    laser->lifespan = INFINITY;
    laser->rotation = 0.0;
    // laser->fading = true;
    laser->transforms.clear();
    laser->custom_data.clear();

	// TODO: Add customisation
	laser->fade_time = lasers_fade_time;
	laser->fade_timer = lasers_fade_time;
}

// User facing functions

void BulletInterface::clear_entity(PackedInt64Array bullet_id) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->lifespan = -INFINITY;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->lifespan = -INFINITY;
		}
	} else if (bullet_id[BULLET_ID_POOL] == ITEMS_POOL) {
		Item* bullet = item_pool[persistent_item_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->lifespan = -INFINITY;
		}
	} else if (bullet_id[BULLET_ID_POOL] == PARTICLES_POOL) {
		Particle* bullet = particle_pool[persistent_particle_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->lifespan = -INFINITY;
		}
	} else if (bullet_id[BULLET_ID_POOL] == ENEMIES_POOL) {
		Enemy* enemy = enemy_pool[persistent_enemy_index[bullet_id[BULLET_ID_INDEX]]];
		if (enemy->cycle == bullet_id[BULLET_ID_CYCLE]) {
			enemy->queue_delete = true;
		}
	}
}

PackedInt64Array BulletInterface::create_bullet_a1(Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool glow) {
	if(available_bullets > 0) {
		available_bullets -= 1;
		active_bullets += 1;


		Bullet* bullet = (Bullet*)bullet_pool[available_bullets];
		RID rid = bullet->item_rid;
		enable_bullet(bullet);
		bullet->layer = glow ? 0 : bullet_data[DATA_LAYER];

		// Set layering to be above last bullet
		rendering_server->canvas_item_set_draw_index(rid, (bullet->layer << 24) + bullets_draw_index);
		bullet->draw_index = bullets_draw_index++;
		if (bullets_draw_index > 16777215) bullets_draw_index = 0; // 2^24 - 1

		rendering_server->canvas_item_add_texture_rect(bullet->item_rid, Rect2(-0.5, -0.5, 1.0, 1.0), bullets_texture_rid);
		if (bullet->additive != glow) {
			rendering_server->canvas_item_set_material(bullet->item_rid, glow ? bullets_material_add_rid : bullets_material_rid);
			bullet->additive = glow;
		}

		// A1 type settings
		bullet->process_mode = A1;

		Transform2D xform = Transform2D(0.0, Vector2(0.0, 0.0)).scaled(bullet_data[DATA_SIZE] * Vector2(1.0, 1.0)).rotated(angle + bullet_rotation_offset);
		xform.set_origin(pos);
		bullet->transform = xform;
		bullet->position = pos;
		bullet->scale = bullet_data[DATA_SIZE];
		bullet->angle = angle;
		bullet->direction = Vector2(1.0, 0.0).rotated(angle);

		rendering_server->canvas_item_set_transform(rid, xform);
		
		// Misc data

		bullet->hitbox_scale = bullet_data[DATA_HITBOX_RATIO];
		bullet->spin = bullet_data[DATA_SPIN];
		bullet->speed = speed;
		bullet->texture_offset = bullet_data[DATA_SPRITE_OFFSET];

		
		// Damage data
		bullet->damage = bullet_data[DATA_DAMAGE_AMOUNT];
		bullet->damage_type = int(bullet_data[DATA_DAMAGE_TYPE]);

		// Shader data

		Color compressed_data = Color();
		compressed_data.r = bullet_data[DATA_SRC_Y] + bullet_data[DATA_SRC_X] / bullets_texture_width;
		compressed_data.g = bullet_data[DATA_SRC_H] + bullet_data[DATA_SRC_W] / bullets_texture_width;
		compressed_data.b = bullet_data[DATA_SPRITE_OFFSET] + 0.999; 
		compressed_data.a = bullet_data[DATA_ANIM_FRAMES] + animation_random;

		bullet->bullet_data = compressed_data;

		rendering_server->canvas_item_set_modulate(rid, compressed_data);

		// Bullet clear colour

		Color fade_color = Color(bullet_data[DATA_CLEAR_R], bullet_data[DATA_CLEAR_G], bullet_data[DATA_CLEAR_B], 0.0);
		bullet->fade_color = fade_color;

		// ID return

		PackedInt64Array to_return = invalid_id;
		to_return.set(BULLET_ID_CYCLE, bullet->cycle);
		to_return.set(BULLET_ID_POOL, BULLETS_POOL);
		to_return.set(BULLET_ID_INDEX, bullet->persistent_index);
		
		// godot::UtilityFunctions::print(bullet->position);
		

		return to_return;
	}
	return invalid_id;
}

PackedInt64Array BulletInterface::create_bullet_a2(Vector2 pos, double speed, double angle, double accel, double max_speed, double w_vel, PackedFloat64Array bullet_data, bool glow) {
	PackedInt64Array id = create_bullet_a1(pos, speed, angle, bullet_data, glow);
	if (id == invalid_id) return invalid_id;

	Bullet* bullet = bullet_pool[persistent_bullet_index[id[BULLET_ID_INDEX]]];
	bullet->process_mode = A2;
	bullet->accel = accel;
	bullet->max_speed = max_speed;
	bullet->wvel = w_vel;

	return id;
}

PackedInt64Array BulletInterface::create_bullet_b1(Vector2 pos, Vector2 velocity, Vector2 accel, Vector2 max_velocity, bool rotation_follows_movement, PackedFloat64Array bullet_data, bool glow) {
	if(available_bullets > 0) {
		available_bullets -= 1;
		active_bullets += 1;


		Bullet* bullet = (Bullet*)bullet_pool[available_bullets];
		RID rid = bullet->item_rid;
		enable_bullet(bullet);
		bullet->layer = glow ? 0 : bullet_data[DATA_LAYER];

		// Set layering to be above last bullet
		rendering_server->canvas_item_set_draw_index(rid, (bullet->layer << 24) + bullets_draw_index);
		bullet->draw_index = bullets_draw_index++;
		if (bullets_draw_index > 16777215) bullets_draw_index = 0; // 2^24 - 1

		rendering_server->canvas_item_add_texture_rect(bullet->item_rid, Rect2(-0.5, -0.5, 1.0, 1.0), bullets_texture_rid);
		if (bullet->additive != glow) {
			rendering_server->canvas_item_set_material(bullet->item_rid, glow ? bullets_material_add_rid : bullets_material_rid);
			bullet->additive = glow;
		}

		// A1 type settings
		bullet->process_mode = B1;

		bullet->angle = Math::atan2(velocity.y, velocity.x);
		Transform2D xform = Transform2D(0.0, Vector2(0.0, 0.0)).scaled(bullet_data[DATA_SIZE] * Vector2(1.0, 1.0)).rotated(bullet->angle + bullet_rotation_offset);
		xform.set_origin(pos);
		bullet->transform = xform;
		bullet->position = pos;
		bullet->scale = bullet_data[DATA_SIZE];
		bullet->speed = velocity.length();
		bullet->direction = velocity;

		bullet->rotation_follows_movement = rotation_follows_movement;

		rendering_server->canvas_item_set_transform(rid, xform);
		
		// Misc data

		bullet->hitbox_scale = bullet_data[DATA_HITBOX_RATIO];
		bullet->spin = bullet_data[DATA_SPIN];
		bullet->b_accel = accel;
		bullet->b_max_velocity = max_velocity;
		bullet->texture_offset = bullet_data[DATA_SPRITE_OFFSET];

		
		// Damage data
		bullet->damage = bullet_data[DATA_DAMAGE_AMOUNT];
		bullet->damage_type = int(bullet_data[DATA_DAMAGE_TYPE]);

		// Shader data

		Color compressed_data = Color();
		compressed_data.r = bullet_data[DATA_SRC_Y] + bullet_data[DATA_SRC_X] / bullets_texture_width;
		compressed_data.g = bullet_data[DATA_SRC_H] + bullet_data[DATA_SRC_W] / bullets_texture_width;
		compressed_data.b = bullet_data[DATA_SPRITE_OFFSET] + 0.999; 
		compressed_data.a = bullet_data[DATA_ANIM_FRAMES] + animation_random;

		bullet->bullet_data = compressed_data;

		rendering_server->canvas_item_set_modulate(rid, compressed_data);

		// Bullet clear colour

		Color fade_color = Color(bullet_data[DATA_CLEAR_R], bullet_data[DATA_CLEAR_G], bullet_data[DATA_CLEAR_B]);
		bullet->fade_color = fade_color;

		// ID return

		PackedInt64Array to_return = invalid_id;
		to_return.set(BULLET_ID_CYCLE, bullet->cycle);
		to_return.set(BULLET_ID_POOL, BULLETS_POOL);
		to_return.set(BULLET_ID_INDEX, bullet->persistent_index);
		
		// godot::UtilityFunctions::print(bullet->position);
		

		return to_return;
	}
	return invalid_id;
}


void BulletInterface::add_bullet_transform_a2(PackedInt64Array bullet_id, int trigger, int trigger_value, double speed, double angle, double accel, double max_speed, double w_vel) {
	// Check validity of bullet
	Bullet* bullet;
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle != bullet_id[BULLET_ID_CYCLE]) {
			return;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle != bullet_id[BULLET_ID_CYCLE]) {
			return;
		}
	} else if (bullet_id[BULLET_ID_POOL] == LASERS_POOL) {
		bullet = laser_pool[persistent_laser_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle != bullet_id[BULLET_ID_CYCLE]) {
			return;
		}
	}

	// TODO: Do it for the rest
	

	if (accel != NO_CHANGE) {
		Array transform = Array();
		transform.resize(TRANSFORM_STRUCTURE_MAX);
		transform[TRANSFORM_STRUCTURE_TYPE] = 0;
		transform[TRANSFORM_STRUCTURE_TRIGGER_METHOD] = trigger;
		transform[TRANSFORM_STRUCTURE_TRIGGER_VALUE] = trigger_value;
		transform[TRANSFORM_STRUCTURE_PROPERTY] = TRANSFORM_ACCEL;
		transform[TRANSFORM_STRUCTURE_VALUE] = accel;
		bullet->transforms.append(transform);
	}
	
	if (max_speed != NO_CHANGE) {
		Array transform = Array();
		transform.resize(TRANSFORM_STRUCTURE_MAX);
		transform[TRANSFORM_STRUCTURE_TYPE] = 0;
		transform[TRANSFORM_STRUCTURE_TRIGGER_METHOD] = trigger;
		transform[TRANSFORM_STRUCTURE_TRIGGER_VALUE] = trigger_value;
		transform[TRANSFORM_STRUCTURE_PROPERTY] = TRANSFORM_MAX_SPEED;
		transform[TRANSFORM_STRUCTURE_VALUE] = max_speed;
		bullet->transforms.append(transform);
	}

	if (w_vel != NO_CHANGE) {
		Array transform = Array();
		transform.resize(TRANSFORM_STRUCTURE_MAX);
		transform[TRANSFORM_STRUCTURE_TYPE] = 0;
		transform[TRANSFORM_STRUCTURE_TRIGGER_METHOD] = trigger;
		transform[TRANSFORM_STRUCTURE_TRIGGER_VALUE] = trigger_value;
		transform[TRANSFORM_STRUCTURE_PROPERTY] = TRANSFORM_WVEL;
		transform[TRANSFORM_STRUCTURE_VALUE] = w_vel;
		bullet->transforms.append(transform);
	}
	


}

PackedInt64Array BulletInterface::create_item(Vector2 pos, double speed, double angle, double spin, PackedFloat64Array item_data, bool glow) {
	if (available_items > 0) {
		available_items -= 1;
		active_items += 1;
		
		Item* item = (Item*)item_pool[available_items];
		RID rid = item->item_rid;
		item->is_grazed = false;
		item->is_magneted = false;
		item->is_auto_collected = false;
		// item->fading = false;
		item->layer = 0;
		item->lifetime = 0.0;
		item->lifespan = INFINITY;
		item->hitbox_scale = 1.0;
		item->custom_data.clear();

		item->fade_time = items_fade_time;
		item->fade_timer = items_fade_time;

		rendering_server->canvas_item_set_draw_index(rid, (item->layer << 24) + items_draw_index);
		item->draw_index = items_draw_index++;
		if (items_draw_index > 16777215) items_draw_index = 0; // 2^24 - 1

		rendering_server->canvas_item_add_texture_rect(item->item_rid, Rect2(-0.5, -0.5, 1.0, 1.0), items_texture_rid);
		if (item->additive != glow) {
			rendering_server->canvas_item_set_material(item->item_rid, glow ? items_material_add_rid : items_material_rid);
			item->additive = glow;
		}
		
		Transform2D xform = Transform2D(0.0, Vector2(0.0, 0.0)).scaled(item_data[4] * Vector2(1.0, 1.0));
		if (speed != 0.0) {
			xform = xform.rotated(Math_TAU * (float)rand() / (float)RAND_MAX);
		} else {
			item->fade_timer = -1.0;
		}
		xform.set_origin(pos);

		item->transform = xform;
		item->position = pos;
		item->scale = item_data[ITEM_DATA_SIZE];
		item->angle = angle;
		item->direction = Vector2(1.0, 0.0).rotated(angle);

		rendering_server->canvas_item_set_transform(rid, xform);

		item->speed = speed;
		item->spin = spin;
		
		Color compressed_data = Color();
		compressed_data.r = item_data[ITEM_DATA_SRC_Y] + item_data[ITEM_DATA_SRC_X] / items_texture_width;
		compressed_data.g = item_data[ITEM_DATA_SRC_H] + item_data[ITEM_DATA_SRC_W] / items_texture_width;
		// compressed_data.r = int(item_data[ITEM_DATA_SRC_Y]) << 16 + item_data[ITEM_DATA_SRC_H];
		// compressed_data.g = item_data[ITEM_DATA_SRC_X] + item_data[ITEM_DATA_SRC_W] / items_texture_width;
		compressed_data.b = 0.0;
		compressed_data.a = floor(item_data[ITEM_DATA_ANIM_FRAMES]) + animation_random;

		item->bullet_data = compressed_data;
		item->hitbox_scale = item_data[ITEM_DATA_HITBOX_RATIO];

		item->damage_type = item_data[ITEM_DATA_DAMAGE_TYPE];
		item->damage = item_data[ITEM_DATA_DAMAGE_AMOUNT];

		item->layer = item_data[ITEM_DATA_LAYER];

		rendering_server->canvas_item_set_modulate(item->item_rid, compressed_data);

		PackedInt64Array to_return = PackedInt64Array();
		to_return.resize(3);
		to_return.set(BULLET_ID_CYCLE, item->cycle);
		to_return.set(BULLET_ID_POOL, ITEMS_POOL);
		to_return.set(BULLET_ID_INDEX, item->persistent_index);

		return to_return;

	}

	return invalid_id;
}


// TODO: Complete rewrite
PackedInt64Array BulletInterface::create_particle(Vector2 pos, double speed, double angle, double size, Color color, bool glow) {
	if(available_particles > 0) {
		available_particles -= 1;
		active_particles += 1;


		Particle* particle = (Particle*)particle_pool[available_particles];
		RID rid = particle->item_rid;
		particle->lifetime = 0.0;
		particle->lifespan = 8.0;
		// enable_bullet(bullet);
		particle->layer = 0;// glow ? 0 : particle_data[DATA_LAYER];

		// Set layering to be above last bullet
		rendering_server->canvas_item_set_draw_index(rid, (particle->layer << 24) + particles_draw_index);
		particle->draw_index = bullets_draw_index++;
		if (particles_draw_index > 16777215) particles_draw_index = 0; // 2^24 - 1

		rendering_server->canvas_item_add_texture_rect(particle->item_rid, Rect2(-0.5, -0.5, 1.0, 1.0), particles_texture_rid);
		// if (particle->additive != glow) {
		// 	rendering_server->canvas_item_set_material(particle->item_rid, glow ? particles_material_rid : particles_material_rid);
		// 	particle->additive = glow;
		// }

		Transform2D xform = Transform2D(0.0, Vector2(0.0, 0.0)).scaled(size * Vector2(1.0, 1.0)).rotated(angle + particle_rotation_offset);
		xform.set_origin(pos);
		particle->transform = xform;
		particle->position = pos;
		// particle->scale = particle_data[DATA_SIZE];
		particle->rotation = angle;
		particle->direction = Vector2(1.0, 0.0).rotated(angle);

		rendering_server->canvas_item_set_transform(rid, xform);
		
		// Misc data

		// particle->spin = particle_data[DATA_SPIN];
		// particle->texture_offset = particle_data[DATA_SPRITE_OFFSET];

		// Shader data

		// Color compressed_data = Color();
		// compressed_data.r = particle_data[DATA_SRC_Y] + particle_data[DATA_SRC_X] / particles_texture_width;
		// compressed_data.g = particle_data[DATA_SRC_H] + particle_data[DATA_SRC_W] / particles_texture_width;
		// compressed_data.b = particle_data[DATA_SPRITE_OFFSET] + 0.999; 
		// compressed_data.a = particle_data[DATA_ANIM_FRAMES] + animation_random;

		particle->bullet_data = color;

		rendering_server->canvas_item_set_modulate(rid, color);

		// ID return

		PackedInt64Array to_return = invalid_id;
		to_return.set(BULLET_ID_CYCLE, particle->cycle);
		to_return.set(BULLET_ID_POOL, PARTICLES_POOL);
		to_return.set(BULLET_ID_INDEX, particle->persistent_index);
		

		return to_return;
	}
	return invalid_id;
}


void BulletInterface::create_bullet_clear(Vector2 pos, double size, Color clear_color) {
	create_particle(pos, 0.0, double(rand()) / double(RAND_MAX), size, clear_color, true);
}


Array BulletInterface::collide_and_graze_player(Vector2 pos, double hitbox_radius, double graze_radius) {
	Array to_return = Array();
	to_return.append(Array());
	to_return.append(Array());


	// Bullets
	for (int i = total_bullets - 1; i >= available_bullets; --i) {
		Bullet* bullet = bullet_pool[i];
		
		double b = bullet->scale * bullet->hitbox_scale;
		double b2 = b * b;
		double dist_sq = (bullet->position - pos).length_squared();

		if (bullet->lifespan > 0.0 && bullet->fade_timer <= 0.0 && dist_sq <= graze_radius * graze_radius + 2.0 * graze_radius * b + b2) {
			PackedInt64Array bullet_id = PackedInt64Array();
			bullet_id.resize(3);
			bullet_id.set(BULLET_ID_CYCLE, bullet->cycle);
			bullet_id.set(BULLET_ID_POOL, BULLETS_POOL);
			bullet_id.set(BULLET_ID_INDEX, bullet->persistent_index);

			if (!bullet->is_grazed) {
				bullet->is_grazed = true;
				((Array)(to_return[1])).append(bullet_id);
			}
			
			if (dist_sq < hitbox_radius * hitbox_radius + 2.0 * hitbox_radius * b + b2) {
				if (!bullet->pierce) {
					bullet->lifespan = -INFINITY;
					create_bullet_clear(bullet->position, bullet->scale, bullet->fade_color);
				}
				((Array)(to_return[0])).append(bullet_id);
			}

		}
	}

	// Lasers TODO add logic for loose lasers
	for (int i = total_lasers - 1; i >= available_lasers; --i) {
		Laser* laser = laser_pool[i];

		// Skip if the laser hasn't spawned in yet.
		if (laser->fade_timer > 0.0) continue;


		// Calculate how much margin to move the start and end by for collision checks.
		// e.g. If 90% collision, 5% each side for a value of 0.05.
		// double margin = laser->length * (1.0 - laser->length_hitbox_scale) * 0.5;
		Vector2 dir = laser->direction;
		// If we have a "loose laser", the laser is not flipped and the direction should be reversed.
		if (!laser->flipped) dir *= -1.0;

		// This algorithm gets the player position relative to the laser and then performs AABB.
		// The laser after the operation is assumed to be at (0,0) extending right.

		// Get the coordinates of the laser start and end.
		Vector2 p1 = laser->position; //laser->position + dir * margin;
		Vector2 p2 = laser->position + dir * laser->length; // laser->position + dir * (laser->length - margin);
		
		// Get line x,y,h lenghts
		Vector2 d = Vector2(p2.x - p1.x, p2.y - p1.y);
		double l = d.length();

		// Derive sin and cos for rotation of player position
		double sin = d.y / l;
		double cos = d.x / l;

		// Offset position back to the origin
		Vector2 pos_offset = pos - p1;
		// Get the rotated position
		Vector2 pos_rot = Vector2(
			pos_offset.x * cos  + pos_offset.y * sin, 
			pos_offset.x * -sin + pos_offset.y * cos
		);

		// Finally, check for collision.
		// Check if we're within the length of the laser, with some extra margin for graze checks.
		if (pos_rot.x > -graze_radius && pos_rot.x < l + graze_radius) {
			double player_distance = abs(pos_rot.y);
			double laser_width = laser->scale * laser->hitbox_scale * 0.5;
			// If we're close enough to graze, we can start preparing to return data.
			if (player_distance < graze_radius + laser_width) {
				PackedInt64Array laser_id = PackedInt64Array();
				laser_id.resize(3);
				laser_id.set(BULLET_ID_CYCLE, laser->cycle);
				laser_id.set(BULLET_ID_POOL, LASERS_POOL);
				laser_id.set(BULLET_ID_INDEX, laser->persistent_index);
				
				((Array)(to_return[1])).append(laser_id);
				
				// For collision, reduce both check distances.
				if (player_distance < hitbox_radius + laser_width && pos_rot.x > 0.0 && pos_rot.x < l) {
					((Array)(to_return[0])).append(laser_id);
				}
			}
		}
	}

	// Curve lasers
	for (int i = total_curve_lasers - 1; i >= available_curve_lasers; --i) {
		CurveLaser* laser = curve_laser_pool[i];

		bool laser_grazed = false;

		PackedInt64Array laser_id = PackedInt64Array();
		laser_id.resize(3);
		laser_id.set(BULLET_ID_CYCLE, laser->cycle);
		laser_id.set(BULLET_ID_POOL, CURVE_LASERS_POOL);
		laser_id.set(BULLET_ID_INDEX, laser->persistent_index);

		// Go through each node and see if we collide with any of the segments, same algorithm as laser
		for (int j = laser->collision_start_node_index; j < laser->collision_end_node_index; ++j) {
			// Get the coordinates of the laser start and end.
			Vector2 p1 = laser->points[j];
			Vector2 p2 = laser->points[j+1];

			// Get line x,y,h lenghts
			Vector2 d = Vector2(p2.x - p1.x, p2.y - p1.y);
			double l = d.length();

			// Derive sin and cos for rotation of player position
			double sin = d.y / l;
			double cos = d.x / l;

			// Offset position back to the origin
			Vector2 pos_offset = pos - p1;
			// Get the rotated position
			Vector2 pos_rot = Vector2(
				pos_offset.x * cos  + pos_offset.y * sin, 
				pos_offset.x * -sin + pos_offset.y * cos
			);

			if (pos_rot.x > -graze_radius && pos_rot.x < l + graze_radius) {
				double player_distance = abs(pos_rot.y);
				double laser_width = laser->scale * laser->hitbox_scale * 0.5;
				// If we're close enough to graze, we can start preparing to return data.
				if (player_distance < graze_radius + laser_width) {
					if (!laser_grazed) {
						((Array)(to_return[1])).append(laser_id);
						laser_grazed = true;
					}
					// For collision, reduce both check distances.
					if (player_distance < hitbox_radius + laser_width && pos_rot.x > 0.0 && pos_rot.x < l) {
						((Array)(to_return[0])).append(laser_id);
						// Fancy behaviour to "cut" curve lasers.
						_cut_curve_laser(laser, j);
						// Break out of checking each node as we found one node we collided with and for sure grazed with.
						break;
					}
				}
			}

		}
		
	}

	// Enemies
	for (int i = total_enemies - 1; i >= available_enemies; --i) {
		Enemy* enemy = enemy_pool[i];
		
		double b = enemy->hurtbox_size;

		if (b < 0.0) continue;

		double b2 = b * b;
		double dist_sq = (enemy->position - pos).length_squared();

		// if (dist_sq <= graze_radius * graze_radius + 2.0 * graze_radius * b + b2) {
		if (dist_sq < hitbox_radius * hitbox_radius + 2.0 * hitbox_radius * b + b2) {
			PackedInt64Array bullet_id = PackedInt64Array();
			bullet_id.resize(3);
			bullet_id.set(BULLET_ID_CYCLE, enemy->cycle);
			bullet_id.set(BULLET_ID_POOL, ENEMIES_POOL);
			bullet_id.set(BULLET_ID_INDEX, enemy->persistent_index);

			// if (!bullet->is_grazed) {
			// 	bullet->is_grazed = true;
			// 	((Array)(to_return[1])).append(bullet_id);
			// }
			
			// if (dist_sq < hitbox_radius * hitbox_radius + 2.0 * hitbox_radius * b + b2) {
				// if (!enemyenemy->pierce) bullet->lifespan = -INFINITY;
				((Array)(to_return[0])).append(bullet_id);
			// }
		}
	}




	return to_return;
}


Array BulletInterface::clear_bullets(Vector2 pos, double radius, bool ignore_pierce) {
	Array to_return = Array();

	// Bullets
	for (int i = total_bullets - 1; i >= available_bullets; --i) {
		Bullet* bullet = bullet_pool[i];
		
		double b = bullet->scale * bullet->hitbox_scale;
		double b2 = b * b;
		double dist_sq = (bullet->position - pos).length_squared();

		if (bullet->lifespan > 0.0 && dist_sq <= radius * radius + 2.0 * radius * b + b2) {
			PackedInt64Array bullet_id = PackedInt64Array();
			bullet_id.resize(3);
			bullet_id.set(BULLET_ID_CYCLE, bullet->cycle);
			bullet_id.set(BULLET_ID_POOL, BULLETS_POOL);
			bullet_id.set(BULLET_ID_INDEX, bullet->persistent_index);
			
			if (!bullet->pierce || ignore_pierce) {
				bullet->lifespan = -INFINITY;
				create_bullet_clear(bullet->position, bullet->scale, bullet->fade_color);
			}
			((Array)(to_return)).append(bullet_id);
		}
	}

	// Lasers TODO proper
	for (int i = total_lasers - 1; i >= available_lasers; --i) {
		Bullet* bullet = laser_pool[i];
		
		double b = bullet->scale * bullet->hitbox_scale;
		double b2 = b * b;
		double dist_sq = (bullet->position - pos).length_squared();

		if (dist_sq <= radius * radius + 2.0 * radius * b + b2) {
			PackedInt64Array bullet_id = PackedInt64Array();
			bullet_id.resize(3);
			bullet_id.set(BULLET_ID_CYCLE, bullet->cycle);
			bullet_id.set(BULLET_ID_POOL, LASERS_POOL);
			bullet_id.set(BULLET_ID_INDEX, bullet->persistent_index);
			
			if (!bullet->pierce || ignore_pierce) bullet->lifespan = -INFINITY;
			((Array)(to_return)).append(bullet_id);
		}
	}

	return to_return;
}


Array BulletInterface::collide_enemy(Vector2 pos, double hitbox_radius) {
	Array to_return = Array();

	for (int i = total_shots - 1; i >= available_shots; --i) {
		Bullet* bullet = shot_pool[i];
		
		double b = bullet->scale * bullet->hitbox_scale;
		double b2 = b * b;
		double dist_sq = (bullet->position - pos).length_squared();

		if (bullet->fade_timer <= 0.0) {
			PackedInt64Array bullet_id = PackedInt64Array();
			bullet_id.resize(3);
			bullet_id.set(BULLET_ID_CYCLE, bullet->cycle);
			bullet_id.set(BULLET_ID_POOL, SHOTS_POOL);
			bullet_id.set(BULLET_ID_INDEX, bullet->persistent_index);

			if (dist_sq < hitbox_radius * hitbox_radius + 2.0 * hitbox_radius * b + b2) {
				if (!bullet->pierce) bullet->lifespan = -INFINITY;
				to_return.append(bullet_id);
			}
		}
	}
	return to_return;
}

Array BulletInterface::collect_and_magnet_items(Vector2 pos, Node2D* target, double collect_radius, double magnet_radius) {
    Array collected_items = Array();

	double collect_radius_squared = collect_radius * collect_radius;
	double magnet_radius_squared = magnet_radius * magnet_radius;

	for (int i = total_items - 1; i >= available_items; i--) {
		Item* item = item_pool[i];

		double b = item->scale * item->hitbox_scale;
		double b2 = b * b;

	 	double dist_sq = (item->position - pos).length_squared();
		
		if (dist_sq <= magnet_radius_squared + 2.0 * magnet_radius * b + b2) {
			if (!item->is_grazed) {
				item->is_grazed = true;
				item->is_magneted = true;
				item->magnet_target = target;
			}

			if (dist_sq <= collect_radius_squared + 2.0 * collect_radius * b + b2) {
				item->lifespan = -INFINITY;
                PackedInt64Array bullet_id = PackedInt64Array();
                bullet_id.resize(3);
                bullet_id.set(BULLET_ID_CYCLE, item->cycle);
                bullet_id.set(BULLET_ID_POOL, ITEMS_POOL);
                bullet_id.set(BULLET_ID_INDEX, item->persistent_index);
                collected_items.append(bullet_id);
			}
		}
	}
	return collected_items;
}

void BulletInterface::magnet_all_items(Node2D* target) {
    for (int i = total_items - 1; i >= available_items; i--) {
		Item* item = item_pool[i];
        item->is_grazed = true;
        item->is_magneted = true;
        item->is_auto_collected = true;
        item->magnet_target = target;
    }
}

Array BulletInterface::get_enemy_collisions(PackedInt64Array enemy_id) {
	if (enemy_id[BULLET_ID_POOL] == ENEMIES_POOL) return enemy_pool[persistent_enemy_index[enemy_id[BULLET_ID_INDEX]]]->collided_bullets;
	else return Array();
}


Array BulletInterface::get_enemies_in_range(Vector2 pos, float radius) {
	Array to_return = Array();
	for (int i = total_enemies - 1; i >= available_enemies; --i) {
		Enemy* enemy = enemy_pool[i];
		
		double b = enemy->hurtbox_size;

		if (b < 0.0) continue;

		double b2 = b * b;
		double dist_sq = (enemy->position - pos).length_squared();

		// if (dist_sq <= graze_radius * graze_radius + 2.0 * graze_radius * b + b2) {
		if (dist_sq < radius * radius + 2.0 * radius * b + b2) {
			PackedInt64Array bullet_id = PackedInt64Array();
			bullet_id.resize(3);
			bullet_id.set(BULLET_ID_CYCLE, enemy->cycle);
			bullet_id.set(BULLET_ID_POOL, ENEMIES_POOL);
			bullet_id.set(BULLET_ID_INDEX, enemy->persistent_index);

			to_return.append(bullet_id);
		}
	}

	return to_return;
}


bool BulletInterface::is_valid(PackedInt64Array id) {
	AbstractPoolItem **pool;
	int *persistent_index;
	switch (id[BULLET_ID_POOL]) {
		case BULLETS_POOL:
			pool = (AbstractPoolItem**)bullet_pool;
			persistent_index = persistent_bullet_index;
			break;
		case SHOTS_POOL:
			pool = (AbstractPoolItem**)shot_pool;
			persistent_index = persistent_shot_index;
			break;
		case ITEMS_POOL:
			pool = (AbstractPoolItem**)item_pool;
			persistent_index = persistent_item_index;
			break;
		case LASERS_POOL:
			pool = (AbstractPoolItem**)laser_pool;
			persistent_index = persistent_laser_index;
			break;
		case CURVE_LASERS_POOL:
			pool = (AbstractPoolItem**)curve_laser_pool;
			persistent_index = persistent_curve_laser_index;
			break;
		case ENEMIES_POOL:
			pool = (AbstractPoolItem**)enemy_pool;
			persistent_index = persistent_enemy_index;
			break;
		default:
			return false;
	}
	int index = id[BULLET_ID_INDEX];
	int cycle = id[BULLET_ID_CYCLE];
	
	return (pool[persistent_index[index]]->cycle == cycle);
}

// --------------------

PackedInt64Array BulletInterface::create_shot_a1(Vector2 pos, double speed, double angle, PackedFloat64Array shot_data, bool glow) {
	if(available_shots > 0) {
		available_shots -= 1;
		active_shots += 1;


		Bullet* shot = (Bullet*)shot_pool[available_shots];
		RID rid = shot->item_rid;
		enable_shot(shot);

		shot->layer = glow ? 0 : shot_data[DATA_LAYER];
		// Set layering to be above last bullet
		rendering_server->canvas_item_set_draw_index(rid, (shot->layer << 24) + shots_draw_index);
		shot->draw_index = shots_draw_index++;
		if (shots_draw_index > 16777215) shots_draw_index = 0; // 2^24 - 1

		rendering_server->canvas_item_add_texture_rect(shot->item_rid, Rect2(-0.5, -0.5, 1.0, 1.0), shots_texture_rid);
		if (shot->additive != glow) {
			rendering_server->canvas_item_set_material(shot->item_rid, glow ? shots_material_add_rid : shots_material_rid);
			shot->additive = glow;
		}

		// A1 type settings
		shot->process_mode = A1;

		Transform2D xform = Transform2D(0.0, Vector2(0.0, 0.0)).scaled(shot_data[DATA_SIZE] * Vector2(1.0, 1.0)).rotated(angle + shot_rotation_offset);
		xform.set_origin(pos);
		shot->transform = xform;
		shot->position = pos;
		shot->scale = shot_data[DATA_SIZE];
		shot->angle = angle;
		shot->direction = Vector2(1.0, 0.0).rotated(angle);

		rendering_server->canvas_item_set_transform(rid, xform);
		
		// Misc data
		shot->hitbox_scale = shot_data[DATA_HITBOX_RATIO];
		shot->spin = shot_data[DATA_SPIN];
		shot->speed = speed;
		shot->texture_offset = shot_data[DATA_SPRITE_OFFSET];

		// Damage data
		shot->damage = shot_data[DATA_DAMAGE_AMOUNT];
		shot->damage_type = int(shot_data[DATA_DAMAGE_TYPE]);

		// Shader data
		Color compressed_data = Color();
		compressed_data.r = shot_data[DATA_SRC_Y] + shot_data[DATA_SRC_X] / shots_texture_width;
		compressed_data.g = shot_data[DATA_SRC_H] + shot_data[DATA_SRC_W] / shots_texture_width;
		compressed_data.b = shot_data[DATA_SPRITE_OFFSET] + 0.999; 
		compressed_data.a = shot_data[DATA_ANIM_FRAMES] + animation_random;

		shot->bullet_data = compressed_data;

		rendering_server->canvas_item_set_modulate(rid, compressed_data);

		// Bullet clear colour
		Color fade_color = Color(shot_data[DATA_CLEAR_R], shot_data[DATA_CLEAR_G], shot_data[DATA_CLEAR_B]);
		shot->fade_color = fade_color;

		// ID return
		PackedInt64Array to_return = invalid_id;
		to_return.set(BULLET_ID_CYCLE, shot->cycle);
		to_return.set(BULLET_ID_POOL, SHOTS_POOL);
		to_return.set(BULLET_ID_INDEX, shot->persistent_index);
		
		return to_return;
	}
	return invalid_id;
}

PackedInt64Array BulletInterface::create_shot_a2(Vector2 pos, double speed, double angle, double accel, double max_speed, double w_vel, PackedFloat64Array shot_data, bool glow) {
	PackedInt64Array id = create_shot_a1(pos, speed, angle, shot_data, glow);
	if (id == invalid_id) return invalid_id;

	Bullet* shot = shot_pool[persistent_shot_index[id[BULLET_ID_INDEX]]];
	shot->process_mode = A2;
	shot->accel = accel;
	shot->max_speed = max_speed;
	shot->wvel = w_vel;

	return id;
}

PackedInt64Array BulletInterface::create_enemy(double hitbox_size, double hurtbox_size, bool deletes_bullets) {
	if(available_enemies > 0) {
		available_enemies -= 1;
		active_enemies += 1;

		Enemy* enemy = (Enemy*)enemy_pool[available_enemies];
		enable_enemy(enemy);
		enemy->hitbox_size = hitbox_size;
		enemy->hurtbox_size = hurtbox_size;
		enemy->deletes_bullets = deletes_bullets;

		// ID return
		PackedInt64Array to_return = invalid_id;
		to_return.set(BULLET_ID_CYCLE, enemy->cycle);
		to_return.set(BULLET_ID_POOL, ENEMIES_POOL);
		to_return.set(BULLET_ID_INDEX, enemy->persistent_index);
		
		return to_return;

	}
	return invalid_id;
}

PackedInt64Array BulletInterface::create_straight_laser(Vector2 pos, double angle, double length, double width, double start_margin, double end_margin, double delay, double duration, PackedFloat64Array laser_data, bool glow) {
	if(available_lasers > 0) {
		available_lasers -= 1;
		active_lasers += 1;

		

		Laser* laser = (Laser*)laser_pool[available_lasers];
		RID rid = laser->item_rid;
		enable_laser(laser);
		laser->layer = glow ? 0 : laser_data[LASER_DATA_LAYER];

		laser->width = width;
		laser->length = length;
		laser->start_margin = start_margin;
		laser->end_margin = end_margin;
		laser->flipped = true;

		laser->lifetime = -delay;
		laser->lifespan = duration;
		laser->fade_timer += delay;

		// Set layering to be above last laser
		int draw_index = (laser->layer << 24) + lasers_draw_index;
		rendering_server->canvas_item_set_draw_index(rid, draw_index);
		laser->draw_index = lasers_draw_index++;
		if (lasers_draw_index > 16777215) lasers_draw_index = 0; // 2^24 - 1

		// TODO: Make this customisable for x axis
		// Moves laser start and end point graphically to line up with hitbox
		rendering_server->canvas_item_add_texture_rect(rid, Rect2(-0.5, -1.0 - end_margin, 1.0, 1.0 + start_margin + end_margin), lasers_texture_rid);
		if (laser->additive != glow) {
			rendering_server->canvas_item_set_material(rid, glow ? lasers_material_add_rid : lasers_material_rid);
			laser->additive = glow;
		}

		// Create source graphic
		RID spawn_rid = laser->spawn_item_rid;
		rendering_server->canvas_item_set_draw_index(spawn_rid, draw_index);
		rendering_server->canvas_item_add_texture_rect(spawn_rid, Rect2(-0.5, -0.5, 1.0, 1.0), laser_spawns_texture_rid);


		// A1 type settings
		laser->process_mode = A1;
		
		// Laser transform
		Transform2D xform = Transform2D(0.0, Vector2(0.0, 0.0)).scaled(Vector2(width, length)).rotated(angle + laser_rotation_offset);
		xform.set_origin(pos);
		laser->transform = xform;
		laser->position = pos;
		laser->scale = width;
		laser->angle = angle;
		laser->direction = Vector2(1.0, 0.0).rotated(angle);

		rendering_server->canvas_item_set_transform(rid, xform);
		// Spawn graphic transform

		xform = Transform2D(0.0, Vector2(0.0, 0.0)).scaled(Vector2(1.0, 1.0) * width);//Wat
		xform.set_origin(pos);

		rendering_server->canvas_item_set_transform(spawn_rid, xform);
		laser->spawn_transform = xform;
		
		// Misc data

		laser->hitbox_scale = laser_data[LASER_DATA_HITBOX_RATIO];

		// Damage data
		laser->damage = laser_data[LASER_DATA_DAMAGE_AMOUNT];
		laser->damage_type = int(laser_data[DATA_DAMAGE_TYPE]);

		// Shader data

		Color compressed_data = Color();
		compressed_data.r = laser_data[LASER_DATA_SRC_Y] + laser_data[LASER_DATA_SRC_X] / lasers_texture_width;
		compressed_data.g = laser_data[LASER_DATA_SRC_H] + laser_data[LASER_DATA_SRC_W] / lasers_texture_width;
		compressed_data.b = 0.999; 
		compressed_data.a = laser_data[LASER_DATA_ANIM_FRAMES] + animation_random;

		laser->bullet_data = compressed_data;

		rendering_server->canvas_item_set_modulate(rid, compressed_data);

		// Set spawn laser graphic
		compressed_data.r = laser_data[LASER_DATA_SPAWN_SRC_Y] + laser_data[LASER_DATA_SPAWN_SRC_X] / laser_spawns_texture_width;
		compressed_data.g = laser_data[LASER_DATA_SPAWN_SRC_H] + laser_data[LASER_DATA_SPAWN_SRC_W] / laser_spawns_texture_width;
		compressed_data.b = 0.0; 
		compressed_data.a = 1.0;
		rendering_server->canvas_item_set_modulate(spawn_rid, compressed_data);

		// Bullet clear colour

		Color fade_color = Color(laser_data[LASER_DATA_CLEAR_R], laser_data[LASER_DATA_CLEAR_G], laser_data[LASER_DATA_CLEAR_B]);
		laser->fade_color = fade_color;

		// ID return

		PackedInt64Array to_return = invalid_id;
		to_return.set(BULLET_ID_CYCLE, laser->cycle);
		to_return.set(BULLET_ID_POOL, LASERS_POOL);
		to_return.set(BULLET_ID_INDEX, laser->persistent_index);
		

		return to_return;
	}
	return invalid_id;
}

PackedInt64Array BulletInterface::create_loose_laser(Vector2 pos, double speed, double angle, double length, double width, double start_margin, double end_margin, PackedFloat64Array laser_data, bool glow) {

	return invalid_id;
}

PackedInt64Array BulletInterface::create_curve_laser(Vector2 pos, double speed, double angle, int length, double width, int start_margin, int end_margin, PackedFloat64Array laser_data, bool glow) {
	if (length <= 0) {
		godot::UtilityFunctions::push_warning("Tried to spawn CurveLaser of length 0 or lesser, this is not supported!");
	} else if (available_curve_lasers > 0) {
		available_curve_lasers -= 1;
		active_curve_lasers += 1;


		CurveLaser* laser = (CurveLaser*)curve_laser_pool[available_curve_lasers];
		RID rid = laser->item_rid;
		enable_curve_laser(laser);
		laser->layer = glow ? 0 : laser_data[LASER_DATA_LAYER];

		laser->laser_data_copy = laser_data;

		// A1 type settings
		laser->process_mode = A1;

		laser->position = pos;
		laser->start_position = pos;
		laser->direction = Vector2(1.0, 0.0).rotated(angle);
		laser->angle = angle;
		laser->speed = speed;

		laser->additive = glow;

		laser->width = width;
		laser->length = length + 1;
		laser->scale = width;
		laser->hitbox_scale = laser_data[LASER_DATA_HITBOX_RATIO];
		laser->collision_start_node_index = start_margin;
		laser->collision_end_node_index = laser->length - end_margin;
		laser->mesh_start_node_index = 0;
		laser->mesh_end_node_index = laser->length;
		laser->start_margin = start_margin;
		laser->end_margin = end_margin;

		laser->lifespan = INFINITY;
		laser->fade_timer = length; // Time the source glow lasts for

		// Set layering to be above last laser
		int draw_index = (laser->layer << 24) + lasers_draw_index;
		rendering_server->canvas_item_set_draw_index(rid, draw_index);
		laser->draw_index = lasers_draw_index++;
		if (lasers_draw_index > 16777215) lasers_draw_index = 0; // 2^24 - 1


		Vector2 normal = Vector2(0.0, width * 0.5).rotated(angle);

		// Create the arrays of the points
		laser->points.resize(length + 1);
		// laser->vertices = PackedVector2Array();
		// laser->uvs = PackedVector2Array();
		laser->vertices.resize((length + 1) * 2);
		laser->uvs.resize((length + 1) * 2);
		// Initialise the vertices and uvs arrays
		// TODO: Make this customisable for x axis
		for (int i = 0; i < length + 1; ++i) {
			laser->points[i] = pos;
			laser->vertices[2*i] = pos + normal;
			laser->vertices[2*i+1] = pos - normal;
			laser->uvs[2*i] = Vector2(0.0, double(i) / double(length));
			laser->uvs[2*i+1] = Vector2(1.0, double(i) / double(length));
		}

		// Set up the mesh array to create the mesh surface with
		Array mesh_array = Array();
		mesh_array.resize(rendering_server->ARRAY_MAX);
		mesh_array[rendering_server->ARRAY_VERTEX] = laser->vertices;
		mesh_array[rendering_server->ARRAY_TEX_UV] = laser->uvs;


		// TODO: Enable this again; not done for now for debugging

		// // Add the surface to the mesh depending on glow or not
		// rendering_server->mesh_add_surface_from_arrays(
		// 	glow ? curve_lasers_add_mesh_item : curve_lasers_mesh_item, 
		// 	rendering_server->PRIMITIVE_TRIANGLE_STRIP, 
		// 	mesh_array,
		// 	Array(), Dictionary(), 
		// 	rendering_server->ARRAY_FLAG_USE_2D_VERTICES
		// );

		// // Set laser transform to identity as we won't be moving it at all.
		// rendering_server->canvas_item_set_transform(rid, Transform2D());

		// Create source graphic
		// RID spawn_rid = laser->item_rid;
		rendering_server->canvas_item_set_draw_index(rid, draw_index);
		rendering_server->canvas_item_add_texture_rect(rid, Rect2(-0.5, -0.5, 1.0, 1.0), laser_spawns_texture_rid);
		
		// Spawn graphic transform
		Transform2D xform = Transform2D(0.0, Vector2(0.0, 0.0)).scaled(Vector2(1.0, 1.0) * width);
		xform.set_origin(pos);

		rendering_server->canvas_item_set_transform(rid, xform);
		laser->spawn_transform = xform;

		// Damage data
		laser->damage = laser_data[LASER_DATA_DAMAGE_AMOUNT];
		laser->damage_type = int(laser_data[DATA_DAMAGE_TYPE]);
		
		// Shader data

		// Set regular laser graphic
		Color compressed_data = Color();
		compressed_data.r = laser_data[LASER_DATA_SRC_Y] + laser_data[LASER_DATA_SRC_X] / lasers_texture_width;
		compressed_data.g = laser_data[LASER_DATA_SRC_H] + laser_data[LASER_DATA_SRC_W] / lasers_texture_width;
		compressed_data.b = 0.0; 
		compressed_data.a = laser_data[LASER_DATA_ANIM_FRAMES] + animation_random;

		laser->bullet_data = compressed_data;
		
		// Set the bullet data into the custom0s
		laser->custom0s.resize((length + 1) * 8);
		// uv2_array.resize(laser->length * 2);
		for (int i = 0; i < laser->length; ++i) {
			laser->custom0s[8*i] = compressed_data.r;
			laser->custom0s[8*i+1] = compressed_data.g;
			laser->custom0s[8*i+2] = compressed_data.b;
			laser->custom0s[8*i+3] = compressed_data.a;
			laser->custom0s[8*i+4] = compressed_data.r;
			laser->custom0s[8*i+5] = compressed_data.g;
			laser->custom0s[8*i+6] = compressed_data.b;
			laser->custom0s[8*i+7] = compressed_data.a;
		}

		// Set spawn laser graphic
		compressed_data.r = laser_data[LASER_DATA_SPAWN_SRC_Y] + laser_data[LASER_DATA_SPAWN_SRC_X] / laser_spawns_texture_width;
		compressed_data.g = laser_data[LASER_DATA_SPAWN_SRC_H] + laser_data[LASER_DATA_SPAWN_SRC_W] / laser_spawns_texture_width;
		compressed_data.b = 0.0; 
		compressed_data.a = 1.0;
		rendering_server->canvas_item_set_modulate(rid, compressed_data);

		// Bullet clear colour
		Color fade_color = Color(laser_data[LASER_DATA_CLEAR_R], laser_data[LASER_DATA_CLEAR_G], laser_data[LASER_DATA_CLEAR_B]);
		laser->fade_color = fade_color;

		// ID return
		PackedInt64Array to_return = invalid_id;
		to_return.set(BULLET_ID_CYCLE, laser->cycle);
		to_return.set(BULLET_ID_POOL, CURVE_LASERS_POOL);
		to_return.set(BULLET_ID_INDEX, laser->persistent_index);
		

		return to_return;
	}
	return invalid_id;
}


/* #region Bullet setters and getters */
// This is kinda gross but I don't want to bother with moving stuff to pools and templates so it'll do for now.

double BulletInterface::get_damage(PackedInt64Array bullet_id) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->damage;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->damage;
		}
	} else if (bullet_id[BULLET_ID_POOL] == ITEMS_POOL) {
		Item* item = item_pool[persistent_item_index[bullet_id[BULLET_ID_INDEX]]];
		if (item->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return item->damage;
		}
	}
	return 0.0;
}

void BulletInterface::set_damage(PackedInt64Array bullet_id, double damage) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->damage = damage;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->damage = damage;
		}
	} else if (bullet_id[BULLET_ID_POOL] == ITEMS_POOL) {
		Item* item = item_pool[persistent_item_index[bullet_id[BULLET_ID_INDEX]]];
		if (item->cycle == bullet_id[BULLET_ID_CYCLE]) {
			item->damage = damage;
		}
	}

}

int BulletInterface::get_damage_type(PackedInt64Array bullet_id) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) return bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]]->damage_type;
	else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) return shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]]->damage_type;
	return -1;
}


Vector2 BulletInterface::get_position(PackedInt64Array bullet_id) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) return bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]]->position;
	else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) return shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]]->position;
	else if (bullet_id[BULLET_ID_POOL] == ENEMIES_POOL) return enemy_pool[persistent_enemy_index[bullet_id[BULLET_ID_INDEX]]]->position;
	return Vector2();
}

void BulletInterface::set_position(PackedInt64Array bullet_id, Vector2 position) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]]->position = position;
	else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]]->position = position;
	else if (bullet_id[BULLET_ID_POOL] == ENEMIES_POOL) enemy_pool[persistent_enemy_index[bullet_id[BULLET_ID_INDEX]]]->position = position;
}


double BulletInterface::get_lifetime(PackedInt64Array bullet_id) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->lifetime;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->lifetime;
		}
	} else if (bullet_id[BULLET_ID_POOL] == ITEMS_POOL) {
		Item* bullet = item_pool[persistent_item_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->lifetime;
		}
	} else if (bullet_id[BULLET_ID_POOL] == PARTICLES_POOL) {
		Particle* bullet = particle_pool[persistent_particle_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->lifetime;
		}
	}
	return -INFINITY;
}

void BulletInterface::set_lifetime(PackedInt64Array bullet_id, double lifetime) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->lifetime = lifetime;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->lifetime = lifetime;
		}
	} else if (bullet_id[BULLET_ID_POOL] == ITEMS_POOL) {
		Item* bullet = item_pool[persistent_item_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->lifetime = lifetime;
		}
	} else if (bullet_id[BULLET_ID_POOL] == PARTICLES_POOL) {
		Particle* bullet = particle_pool[persistent_particle_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->lifetime = lifetime;
		}
	}
}


double BulletInterface::get_lifespan(PackedInt64Array bullet_id) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->lifespan;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->lifespan;
		}
	} else if (bullet_id[BULLET_ID_POOL] == ITEMS_POOL) {
		Item* bullet = item_pool[persistent_item_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->lifespan;
		}
	} else if (bullet_id[BULLET_ID_POOL] == PARTICLES_POOL) {
		Particle* bullet = particle_pool[persistent_particle_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->lifespan;
		}
	}
	return -INFINITY;
}

void BulletInterface::set_lifespan(PackedInt64Array bullet_id, double lifespan) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->lifespan = lifespan;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->lifespan = lifespan;
		}
	} else if (bullet_id[BULLET_ID_POOL] == ITEMS_POOL) {
		Item* bullet = item_pool[persistent_item_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->lifespan = lifespan;
		}
	} else if (bullet_id[BULLET_ID_POOL] == PARTICLES_POOL) {
		Particle* bullet = particle_pool[persistent_particle_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->lifespan = lifespan;
		}
	}
}


bool BulletInterface::get_pierce(PackedInt64Array bullet_id) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->pierce;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->pierce;
		}
	}
	return false;
}

void BulletInterface::set_pierce(PackedInt64Array bullet_id, bool pierce) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->pierce = pierce;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->pierce = pierce;
		}
	}
}


int BulletInterface::get_layer(PackedInt64Array bullet_id) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->layer;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->layer;
		}
	}
	return -1;

}
void BulletInterface::set_layer(PackedInt64Array bullet_id, int layer) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->layer = layer;
			rendering_server->canvas_item_set_draw_index(bullet->item_rid, (bullet->layer << 24) + bullet->draw_index);
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->layer = layer;
			rendering_server->canvas_item_set_draw_index(bullet->item_rid, (bullet->layer << 24) + bullet->draw_index);
		}
	}

}


int BulletInterface::get_item_type(PackedInt64Array item_id) {
	if (item_id[BULLET_ID_POOL] != ITEMS_POOL) return - 1;
	Item* item = item_pool[persistent_item_index[item_id[BULLET_ID_INDEX]]];
	if (item->cycle == item_id[BULLET_ID_CYCLE]) {
		return item->damage_type;
	}
	return -1;
}

void BulletInterface::set_item_magnet(PackedInt64Array item_id, Node2D* target) {
	if (item_id[BULLET_ID_POOL] != ITEMS_POOL) return;
	Item* item = item_pool[persistent_item_index[item_id[BULLET_ID_INDEX]]];
	if (item->cycle == item_id[BULLET_ID_CYCLE]) {
		item->magnet_target = target;
		item->is_magneted = true;
	}
}




void BulletInterface::skip_fade(PackedInt64Array bullet_id) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->fade_timer = 0.0;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->fade_timer = 0.0;
		}
	} else if (bullet_id[BULLET_ID_POOL] == ITEMS_POOL) {
		Item* bullet = item_pool[persistent_item_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->fade_timer = 0.0;
		}
	// } else if (bullet_id[BULLET_ID_POOL] == PARTICLES_POOL) {
	// 	Particle* bullet = particle_pool[persistent_particle_index[bullet_id[BULLET_ID_INDEX]]];
	// 	if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
	// 		bullet->fade_timer = 0.0;
	// 	}
	}
	
}

double BulletInterface::get_spin(PackedInt64Array bullet_id) {	
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->spin;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->spin;
		}
	}

	return 0.0;
}

void BulletInterface::set_spin(PackedInt64Array bullet_id, double spin) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->spin = spin;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->spin = spin;
		}
	}
}


double BulletInterface::get_rotation(PackedInt64Array bullet_id) {	
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->rotation;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			return bullet->rotation;
		}
	}

	return 0.0;
}

void BulletInterface::set_rotation(PackedInt64Array bullet_id, double rotation) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
       		bullet->transform.rotate(rotation - bullet->rotation);
			bullet->transform.set_origin(bullet->position);
			bullet->rotation = rotation;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
       		bullet->transform.rotate(rotation - bullet->rotation);
			bullet->transform.set_origin(bullet->position);
			bullet->rotation = rotation;
		}
	}
}


double BulletInterface::get_accel(PackedInt64Array bullet_id) {

	return -1.0;
}

void BulletInterface::set_accel(PackedInt64Array bullet_id, double accel) {

}


double BulletInterface::get_max_speed(PackedInt64Array bullet_id) {

	return -1.0;
}

void BulletInterface::set_max_speed(PackedInt64Array bullet_id, double max_speed) {

}


double BulletInterface::get_wvel(PackedInt64Array bullet_id) {
	return -1.0;
}

void BulletInterface::set_wvel(PackedInt64Array bullet_id, double wvel) {
	if (bullet_id[BULLET_ID_POOL] == BULLETS_POOL) {
		Bullet* bullet = bullet_pool[persistent_bullet_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->process_mode = Math::max(A2, bullet->process_mode);
			bullet->wvel = wvel;
		}
	} else if (bullet_id[BULLET_ID_POOL] == SHOTS_POOL) {
		Bullet* bullet = shot_pool[persistent_shot_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->process_mode = Math::max(A2, bullet->process_mode);
			bullet->wvel = wvel;
		}
	} else if (bullet_id[BULLET_ID_POOL] == LASERS_POOL) {
		Bullet* bullet = laser_pool[persistent_laser_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->process_mode = Math::max(A2, bullet->process_mode);
			bullet->wvel = wvel;
		}
	} else if (bullet_id[BULLET_ID_POOL] == CURVE_LASERS_POOL) {
		Bullet* bullet = curve_laser_pool[persistent_curve_laser_index[bullet_id[BULLET_ID_INDEX]]];
		if (bullet->cycle == bullet_id[BULLET_ID_CYCLE]) {
			bullet->process_mode = Math::max(A2, bullet->process_mode);
			bullet->wvel = wvel;
		}
	}
}

/* #endregion */

/* #region Old stuff 

// // DO NOT USE
// bool BulletInterface::spawn_bullet(Ref<BulletKit> kit, Dictionary properties) {
// 	if(available_bullets > 0 && kits_to_pool_index.has(kit)) {
// 		PackedInt64Array pool_index = kits_to_pool_index[kit].operator PackedInt64Array();
// 		BulletPool* pool = pools[kits_to_pool_index[kit]].pool.get();

// 		if(pool->get_available_bullets() > 0) {
// 			available_bullets -= 1;
// 			active_bullets += 1;

// 			pool->spawn_bullet(properties);
// 			return true;
// 		}
// 	}
// 	return false;
// }


// Variant BulletInterface::obtain_bullet(Ref<BulletKit> kit) {
// 	if(available_bullets > 0 && kits_to_pool_index.has(kit)) {
// 		int pool_index = kits_to_pool_index[kit];
// 		BulletPool* pool = pools[pool_index].pool.get();

// 		if(pool->get_available_bullets() > 0) {
// 			available_bullets -= 1;
// 			active_bullets += 1;

// 			UnitID bullet_id = pool->obtain_bullet();
// 			PackedInt64Array to_return = invalid_id;
// 			to_return.set(0, bullet_id.cycle);
// 			to_return.set(1, bullet_id.set);
// 			to_return.set(2, bullet_id.index);
// 			return to_return;
// 		}
// 	}
// 	return invalid_id;
// }

// bool BulletInterface::release_bullet(Variant id) {
// 	PackedInt64Array bullet_id = id.operator PackedInt64Array();
// 	bool result = false;

// 	int pool_index = bullet_id[1];
// 	if (pool_index >= 0) {
// 		result = pools[pool_index].pool->release_bullet(UnitID(bullet_id[0], bullet_id[1], bullet_id[2]));
// 		if(result) {
// 			available_bullets += 1;
// 			active_bullets -= 1;
// 		}
// 	}
// 	return result;
// }

// bool BulletInterface::is_bullet_valid(Variant id) {
// 	PackedInt64Array bullet_id = id.operator PackedInt64Array();

// 	int pool_index = bullet_id[1];
// 	if(pool_index >= 0) {
// 		return pools[pool_index].pool->is_bullet_valid(UnitID(bullet_id[0], bullet_id[1], bullet_id[2]));
// 	}
// 	return false;
// }

// bool BulletInterface::is_kit_valid(Ref<BulletKit> kit) {
// 	return kits_to_pool_index.has(kit);
// }

// int BulletInterface::get_available_bullets(Ref<BulletKit> kit) {
// 	if(kits_to_pool_index.has(kit)) {
// 		int pool_index = kits_to_pool_index[kit];
// 		return pools[pool_index].pool->get_available_bullets();
// 	}
// 	return 0;
// }

// int BulletInterface::get_active_bullets(Ref<BulletKit> kit) {
// 	if(kits_to_pool_index.has(kit)) {
// 		int pool_index = kits_to_pool_index[kit];
// 		return pools[pool_index].pool->get_active_bullets();
// 	}
// 	return 0;
// }

// int BulletInterface::get_pool_size(Ref<BulletKit> kit) {
// 	if(kits_to_pool_index.has(kit)) {
// 		int pool_index = kits_to_pool_index[kit];
// 		return pools[pool_index].size;
// 	}
// 	return 0;
// }

// int BulletInterface::get_z_index(Ref<BulletKit> kit) {
// 	if(kits_to_pool_index.has(kit)) {
// 		int pool_index = kits_to_pool_index[kit];
// 		return pools[pool_index].z_index;
// 	}
// 	return 0;
// }

// int BulletInterface::get_total_available_bullets() {
// 	return available_bullets;
// }

// int BulletInterface::get_total_active_bullets() {
// 	return active_bullets;
// }

// // Prob 
// bool BulletInterface::is_bullet_existing(RID area_rid, int shape_index) {
// 	// if(!areas_to_pool_set_indices.has(area_rid)) {
// 	// 	return false;
// 	// }
// 	// int set_index = areas_to_pool_set_indices[area_rid];
// 	// int pool_index = _get_pool_index(set_index, shape_index);
// 	// if(pool_index >= 0) {
// 	// 	return pool_sets[set_index].pools[pool_index].pool->is_bullet_existing(shape_index);
// 	// }
// 	return false;
// }


// Ref<BulletKit> BulletInterface::get_kit_from_bullet(Variant id) {
// 	PackedInt64Array bullet_id = id.operator PackedInt64Array();

// 	int pool_index = bullet_id[1];
// 	if (pool_index >= 0 && pools[pool_index].pool->is_bullet_valid(UnitID(bullet_id[0], bullet_id[1], bullet_id[2]))) {
// 		return pools[pool_index].bullet_kit;
// 	}
// 	return Ref<BulletKit>();
// }

// void BulletInterface::set_bullet_property(Variant id, String property, Variant value) {
// 	PackedInt64Array bullet_id = id.operator PackedInt64Array();

// 	int pool_index = bullet_id[1];
// 	if (pool_index >= 0) {
// 		pools[pool_index].pool->set_bullet_property(UnitID(bullet_id[0], bullet_id[1], bullet_id[2]), property, value);
// 	}
// }


// Variant BulletInterface::get_bullet_property(Variant id, String property) {
// 	PackedInt64Array bullet_id = id.operator PackedInt64Array();

// 	int pool_index = bullet_id[1];
// 	if(pool_index >= 0) {
// 		return pools[pool_index].pool->get_bullet_property(UnitID(bullet_id[0], bullet_id[1], bullet_id[2]), property);
// 	}
// 	return Variant();
// }

// Array BulletInterface::collide_and_graze_enemy(Vector2 pos, double hitbox_radius, double graze_radius) {
// 	Array to_return = Array();
// 	to_return.append(Array());
// 	to_return.append(Array());
// 	for (int i = 0; i < player_bullet_kit_indices.size(); ++i) {
// 		BasicBulletPool* pool = (BasicBulletPool*)pools[player_bullet_kit_indices[i]].pool.get();
// 		Array result = pool->_collide_and_graze(pos, hitbox_radius, graze_radius);
// 		((Array)to_return[0]).append_array((Array)result[0]);
// 		((Array)to_return[1]).append_array((Array)result[1]);
// 	}
// 	return to_return;
// }

// PackedInt64Array BulletInterface::create_shot_a1(Ref<BasicBulletKit> kit, Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool fade_in) {
	
// 	int pool_index = kits_to_pool_index[kit];
// 	BasicBulletPool* pool = (BasicBulletPool*)pools[pool_index].pool.get();

// 	if(pool->get_available_bullets() > 0) {
// 		available_bullets -= 1;
// 		active_bullets += 1;

// 		// Base init
// 		UnitID bullet_id = pool->_create_shot_a1(pos, speed, angle, bullet_data, fade_in);
// 		PackedInt64Array to_return = invalid_id;
// 		// to_return.resize(3);
// 		to_return.set(0, bullet_id.cycle);
// 		to_return.set(1, bullet_id.set);
// 		to_return.set(2, bullet_id.index);
		
// 		return to_return;
// 	}
	
// 	return invalid_id;
// }

// PackedInt64Array BulletInterface::create_shot_a2(Ref<BasicBulletKit> kit, Vector2 pos, double speed, double angle, double accel, double max_speed, PackedFloat64Array bullet_data, bool fade_in) {
	
// 	int pool_index = kits_to_pool_index[kit];
// 	BasicBulletPool* pool = (BasicBulletPool*)pools[pool_index].pool.get();

// 	if(pool->get_available_bullets() > 0) {
// 		available_bullets -= 1;
// 		active_bullets += 1;

// 		// Base init
// 		UnitID bullet_id = pool->_create_shot_a2(pos, speed, angle, accel, max_speed, bullet_data, fade_in);
// 		PackedInt64Array to_return = invalid_id;
// 		// to_return.resize(3);
// 		to_return.set(0, bullet_id.cycle);
// 		to_return.set(1, bullet_id.set);
// 		to_return.set(2, bullet_id.index);
		
// 		return to_return;
// 	}
	
// 	return invalid_id;
// }




// 	return invalid_id;

// }


// PackedInt64Array BulletInterface::create_particle(Ref<BasicParticleKit> kit, Vector2 pos, Vector2 drift, double rotation, double size, Color color) {


// 	int pool_index = kits_to_pool_index[kit];
// 	BasicParticlePool* pool = (BasicParticlePool*)pools[pool_index].pool.get();

// 	if(pool->get_available_bullets() > 0) {
// 		available_bullets -= 1;
// 		active_bullets += 1;

// 		UnitID bullet_id = pool->_create_particle(pos, drift, rotation, size, color);
// 		PackedInt64Array to_return = PackedInt64Array();
// 		to_return.resize(3);
// 		to_return.set(0, bullet_id.cycle);
// 		to_return.set(1, bullet_id.set);
// 		to_return.set(2, bullet_id.index);

// 		return to_return;
// 	}

// 	return invalid_id;

// }



// double BulletInterface::get_damage(PackedInt64Array bullet_id) {
// 	if (bullet_id[1] >= 0) {
// 		return pools[bullet_id[1]].pool->get_damage(UnitID(bullet_id[0], bullet_id[1], bullet_id[2]));
// 	}
// 	return 0.0;

// }

// void BulletInterface::set_damage(PackedInt64Array bullet_id, double damage) {
// 	if (bullet_id[1] >= 0) {
// 		pools[bullet_id[1]].pool->set_damage(UnitID(bullet_id[0], bullet_id[1], bullet_id[2]), damage);
// 	}

// }

// int BulletInterface::get_damage_type(PackedInt64Array bullet_id) {
// 	if (bullet_id[1] >= 0) {
// 		return pools[bullet_id[1]].pool->get_damage_type(UnitID(bullet_id[0], bullet_id[1], bullet_id[2]));
// 	}
// 	return 0.0;

// }

// void BulletInterface::set_damage_type(PackedInt64Array bullet_id, int damage_type) {
// 	if (bullet_id[1] >= 0) {
// 		pools[bullet_id[1]].pool->set_damage_type(UnitID(bullet_id[0], bullet_id[1], bullet_id[2]), damage_type);
// 	}

// }


// bool BulletInterface::get_is_auto_collected(PackedInt64Array bullet_id) {
// 	BasicItemPool* pool = (BasicItemPool*)pools[bullet_id[1]].pool.get();
// 	if (bullet_id[1] >= 0) {
// 		return pool->_get_is_auto_collected(UnitID(bullet_id[0], bullet_id[1], bullet_id[2]));
// 	}
// 	return false;

/* #endregion */