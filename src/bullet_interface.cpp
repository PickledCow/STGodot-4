// #include <VisualServer.hpp>
// #include <PhysicsServer2D.hpp>
// #include <World2D.hpp>
// #include <Viewport.hpp>
// #include <OS.hpp>
// #include <Engine.hpp>
// #include <Font.hpp>
// #include <RegExMatch.hpp>
// #include <Node2D.hpp>
// #include <Transform2D.hpp>
// #include <Array.hpp>
#include <cstdlib>

#include <bullet_interface.hpp>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/world2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

int BulletInterface::get_NO_CHANGE() { return NO_CHANGE; }



void BulletInterface::set_constant(float value) {
	// Constant
}


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
	BIND_ENUM_CONSTANT(TRIGGER_BOUNCE);
	BIND_ENUM_CONSTANT(TRIGGER_GRAZE);
	}

	/* #endregion */
	
	/* #region Setup Setters/Getters */

    ClassDB::bind_method(D_METHOD("get_total_bullets"), &BulletInterface::get_total_bullets);
	ClassDB::bind_method(D_METHOD("set_total_bullets", "p_total_bullets"), &BulletInterface::set_total_bullets);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Max Bullets"), "set_total_bullets", "get_total_bullets");
	
    ClassDB::bind_method(D_METHOD("get_total_shots"), &BulletInterface::get_total_shots);
	ClassDB::bind_method(D_METHOD("set_total_shots", "p_total_shots"), &BulletInterface::set_total_shots);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Max Shots"), "set_total_shots", "get_total_shots");
	
    ClassDB::bind_method(D_METHOD("get_total_items"), &BulletInterface::get_total_items);
	ClassDB::bind_method(D_METHOD("set_total_items", "p_total_items"), &BulletInterface::set_total_items);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Max Items"), "set_total_items", "get_total_items");
	
    ClassDB::bind_method(D_METHOD("get_total_particles"), &BulletInterface::get_total_particles);
	ClassDB::bind_method(D_METHOD("set_total_particles", "p_total_particles"), &BulletInterface::set_total_particles);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Max Particles"), "set_total_particles", "get_total_particles");
	
    ClassDB::bind_method(D_METHOD("get_bounce_rect"), &BulletInterface::get_bounce_rect);
	ClassDB::bind_method(D_METHOD("set_bounce_rect", "p_bounce)rect"), &BulletInterface::set_bounce_rect);
	ADD_PROPERTY(PropertyInfo(Variant::RECT2, "Bounce Rect"), "set_bounce_rect", "get_bounce_rect");
	
    ClassDB::bind_method(D_METHOD("get_active_rect"), &BulletInterface::get_active_rect);
	ClassDB::bind_method(D_METHOD("set_active_rect", "p_active)rect"), &BulletInterface::set_active_rect);
	ADD_PROPERTY(PropertyInfo(Variant::RECT2, "Activve Rect"), "set_active_rect", "get_active_rect");
	
    ClassDB::bind_method(D_METHOD("get_time_scale"), &BulletInterface::get_time_scale);
	ClassDB::bind_method(D_METHOD("set_time_scale", "p_time_scale)rect"), &BulletInterface::set_time_scale);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Time Scale"), "set_time_scale", "get_time_scale");
	
    ClassDB::bind_method(D_METHOD("get_origin"), &BulletInterface::get_origin);
	ClassDB::bind_method(D_METHOD("set_origin", "p_origin)rect"), &BulletInterface::set_origin);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "Origin"), "set_origin", "get_origin");
	/* #endregion */
	
	/* #region Textures and Material Setters/Getters */
    ClassDB::bind_method(D_METHOD("get_bullets_texture"), &BulletInterface::get_bullets_texture);
	ClassDB::bind_method(D_METHOD("set_bullets_texture", "p_bullets_texture"), &BulletInterface::set_bullets_texture);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Bullet Texture", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "Texture2D"
        ), "set_bullets_texture", "get_bullets_texture");
	
    ClassDB::bind_method(D_METHOD("get_bullets_material"), &BulletInterface::get_bullets_material);
	ClassDB::bind_method(D_METHOD("set_bullets_material", "p_bullets_material"), &BulletInterface::set_bullets_material);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Bullet Material", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_bullets_material", "get_bullets_material");
	
    ClassDB::bind_method(D_METHOD("get_bullets_material_add"), &BulletInterface::get_bullets_material_add);
	ClassDB::bind_method(D_METHOD("set_bullets_material_add", "p_bullets_material_add"), &BulletInterface::set_bullets_material_add);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Bullet Material (Add)", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_bullets_material_add", "get_bullets_material_add");
	
// ---
    ClassDB::bind_method(D_METHOD("get_shots_texture"), &BulletInterface::get_shots_texture);
	ClassDB::bind_method(D_METHOD("set_shots_texture", "p_shots_texture"), &BulletInterface::set_shots_texture);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Shot Texture", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "Texture2D"
        ), "set_shots_texture", "get_shots_texture");
	
    ClassDB::bind_method(D_METHOD("get_shots_material"), &BulletInterface::get_shots_material);
	ClassDB::bind_method(D_METHOD("set_shots_material", "p_shots_material"), &BulletInterface::set_shots_material);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Shot Material", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_shots_material", "get_shots_material");
	
    ClassDB::bind_method(D_METHOD("get_shots_material_add"), &BulletInterface::get_shots_material_add);
	ClassDB::bind_method(D_METHOD("set_shots_material_add", "p_shots_material_add"), &BulletInterface::set_shots_material_add);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Shot Material (Add)", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_shots_material_add", "get_shots_material_add");

// ---
    ClassDB::bind_method(D_METHOD("get_items_texture"), &BulletInterface::get_items_texture);
	ClassDB::bind_method(D_METHOD("set_items_texture", "p_items_texture"), &BulletInterface::set_items_texture);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Item Texture", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "Texture2D"
        ), "set_items_texture", "get_items_texture");
	
    ClassDB::bind_method(D_METHOD("get_items_material"), &BulletInterface::get_items_material);
	ClassDB::bind_method(D_METHOD("set_items_material", "p_items_material"), &BulletInterface::set_items_material);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Item Material", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_items_material", "get_items_material");
	
    ClassDB::bind_method(D_METHOD("get_items_material_add"), &BulletInterface::get_items_material_add);
	ClassDB::bind_method(D_METHOD("set_items_material_add", "p_items_material_add"), &BulletInterface::set_items_material_add);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Item Material (Add)", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_items_material_add", "get_items_material_add");
		
// ---
    ClassDB::bind_method(D_METHOD("get_particles_texture"), &BulletInterface::get_particles_texture);
	ClassDB::bind_method(D_METHOD("set_particles_texture", "p_particles_texture"), &BulletInterface::set_particles_texture);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Particle Texture", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "Texture2D"
        ), "set_particles_texture", "get_particles_texture");
	
    ClassDB::bind_method(D_METHOD("get_particles_material"), &BulletInterface::get_particles_material);
	ClassDB::bind_method(D_METHOD("set_particles_material", "p_particles_material"), &BulletInterface::set_particles_material);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Particle Material", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_particles_material", "get_particles_material");
	
    ClassDB::bind_method(D_METHOD("get_particles_material_add"), &BulletInterface::get_particles_material_add);
	ClassDB::bind_method(D_METHOD("set_particles_material_add", "p_particles_material_add"), &BulletInterface::set_particles_material_add);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "Particle Material (Add)", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial,CanvasItemMaterial"
        ), "set_particles_material_add", "get_particles_material_add");

	/* #endregion */

	
	

	ClassDB::bind_method(D_METHOD(
		"init",
		"root"), 
		&BulletInterface::init
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

	
	// ClassDB::bind_method(D_METHOD(
	// 	"get_total_active_bullets"), &BulletInterface::get_total_active_bullets);
	

	// ClassDB::bind_method(D_METHOD(
	// 	"collide_and_graze_kit",
	// 	"bullet_kit",
	// 	"position",
	// 	"hitbox_radius",
	// 	"graze_radius"), 
	// 	&BulletInterface::collide_and_graze_kit
	// );
	
	// ClassDB::bind_method(D_METHOD(
	// 	"collide_and_graze_player",
	// 	"position",
	// 	"hitbox_radius",
	// 	"graze_radius"), 
	// 	&BulletInterface::collide_and_graze_player
	// );

	// ClassDB::bind_method(D_METHOD(
	// 	"collide_and_graze_enemy",
	// 	"position",
	// 	"hitbox_radius",
	// 	"graze_radius"), 
	// 	&BulletInterface::collide_and_graze_enemy
	// );

	// ClassDB::bind_method(D_METHOD(
	// 	"collect_and_magnet_kit",
	// 	"item_kit",
	// 	"position",
	// 	"target_node",
	// 	"collection_radius",
	// 	"magnet_radius"), 
	// 	&BulletInterface::collect_and_magnet_kit
	// );

	// ClassDB::bind_method(D_METHOD(
	// 	"collect_and_magnet_all",
	// 	"position",
	// 	"target_node",
	// 	"collection_radius",
	// 	"magnet_radius"), 
	// 	&BulletInterface::collect_and_magnet_all
	// );
		
	// ClassDB::bind_method(D_METHOD(
	// 	"magnet_all_kit",
	// 	"item_kit",
	// 	"target_node"), 
	// 	&BulletInterface::magnet_all_kit
	// );

	// ClassDB::bind_method(D_METHOD(
	// 	"magnet_all",
	// 	"target_node"), 
	// 	&BulletInterface::magnet_all
	// );
		
	// ClassDB::bind_method(D_METHOD(
	// 	"create_item",
	// 	"item_kit",
	// 	"position",
	// 	"speed",
	// 	"angle",
	// 	"spin",
	// 	"item_data"
	// 	), 
	// 	&BulletInterface::create_item
	// );
	
	// ClassDB::bind_method(D_METHOD(
	// 	"create_particle",
	// 	"particle_kit",
	// 	"position",
	// 	"drift",
	// 	"rotation",
	// 	"size",
	// 	"color"
	// 	), 
	// 	&BulletInterface::create_particle
	// );

	// ClassDB::bind_method(D_METHOD(
	// 	"create_shot_a2",
	// 	"bullet_kit",
	// 	"position",
	// 	"speed",
	// 	"angle",
	// 	"accel",
	// 	"max_speed",
	// 	"bullet_data",
	// 	"fade"), 
	// 	&BulletInterface::create_shot_a2
	// );
	
	// ClassDB::bind_method(D_METHOD(
	// 	"get_position",
	// 	"id"), 
	// 	&BulletInterface::get_position
	// );
	
	// ClassDB::bind_method(D_METHOD(
	// 	"set_position",
	// 	"id",
	// 	"position"), 
	// 	&BulletInterface::set_position
	// );

	
	// ClassDB::bind_method(D_METHOD(
	// 	"get_damage",
	// 	"id"), 
	// 	&BulletInterface::get_damage
	// );
	
	// ClassDB::bind_method(D_METHOD(
	// 	"set_damage",
	// 	"id",
	// 	"damage"), 
	// 	&BulletInterface::set_damage
	// );
	
	// ClassDB::bind_method(D_METHOD(
	// 	"get_damage_type",
	// 	"id"), 
	// 	&BulletInterface::get_damage_type
	// );
	
	// ClassDB::bind_method(D_METHOD(
	// 	"set_damage_type",
	// 	"id",
	// 	"damage"), 
	// 	&BulletInterface::set_damage_type
	// );

	// // Redefinitions
	// ClassDB::bind_method(D_METHOD(
	// 	"get_item_type",
	// 	"id"), 
	// 	&BulletInterface::get_damage_type
	// );
	
	// ClassDB::bind_method(D_METHOD(
	// 	"set_item_type",
	// 	"id",
	// 	"damage"), 
	// 	&BulletInterface::set_damage_type
	// );


		
	// ClassDB::bind_method(D_METHOD(
	// 	"get_is_auto_collected",
	// 	"item_id"), 
	// 	&BulletInterface::get_is_auto_collected
	// );
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


Rect2 BulletInterface::get_bounce_rect() {
	return bounce_rect;
}
void BulletInterface::set_bounce_rect(Rect2 rect) {
	bounce_rect = rect;
}

Rect2 BulletInterface::get_active_rect() {
	return active_rect;
}
void BulletInterface::set_active_rect(Rect2 rect) {
	active_rect = rect;
}

double BulletInterface::get_time_scale() {
	return time_scale;
}
void BulletInterface::set_time_scale(double ts) {
	time_scale = ts;
}

Vector2 BulletInterface::get_origin() {
	return origin;
}
void BulletInterface::set_origin(Vector2 o) {
	origin = o;
}


/* #endregion */

BulletInterface::BulletInterface() { }

// TODO, change to regular frees
BulletInterface::~BulletInterface() {
	// // Free memory

	// for (int i = 0; i < total_bullets; ++i) {
	// 	rendering_server->canvas_item_clear(bullet_pool[i]->item_rid);
	// 	memdelete(bullet_pool[i]);
	// }
	// for (int i = 0; i < total_shots; ++i) {
	// 	rendering_server->canvas_item_clear(shot_pool[i]->item_rid);
	// 	memdelete(shot_pool[i]);
	// }
	// for (int i = 0; i < total_items; ++i) {
	// 	rendering_server->canvas_item_clear(item_pool[i]->item_rid);
	// 	memdelete(item_pool[i]);
	// }
	// for (int i = 0; i < total_particles; ++i) {
	// 	rendering_server->canvas_item_clear(particle_pool[i]->item_rid);
	// 	memdelete(particle_pool[i]);
	// }

	// memfree(bullet_pool);
	// memfree(shot_pool);
	// memfree(item_pool);
	// memfree(particle_pool);

	// memfree(persistent_bullet_index);
	// memfree(persistent_shot_index);
	// memfree(persistent_item_index);
	// memfree(persistent_particle_index);
	
}

void BulletInterface::init(Node2D* root) {
	rendering_server = RenderingServer::get_singleton();
	canvas_parent = root->get_canvas_item();

	available_bullets = total_bullets;
	active_bullets = 0;

	available_shots = total_shots;
	active_shots = 0;
	
	available_items = total_items;
	active_items = 0;
	
	available_particles = total_particles;
	active_particles = 0;

	bullet_pool = new Bullet*[total_bullets];
	shot_pool = new Bullet*[total_shots];
	item_pool = new Item*[total_items];
	particle_pool = new Particle*[total_particles];

	persistent_bullet_index = new int[total_bullets];
	persistent_shot_index = new int[total_shots];
	persistent_item_index = new int[total_items];
	persistent_particle_index = new int[total_particles];


	bullets_texture_rid = bullets_texture->get_rid();
	shots_texture_rid = shots_texture->get_rid();
	items_texture_rid = items_texture->get_rid();
	particles_texture_rid = particles_texture->get_rid();

	bullets_texture_width = bullets_texture->get_size().x;
	shots_texture_width = shots_texture->get_size().x;
	items_texture_width = items_texture->get_size().x;
	particles_texture_width = particles_texture->get_size().x;

	_init_bullets();
	_init_shots();
	_init_items();
	_init_particles();

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
	RID canvas_item = rendering_server->canvas_item_create();
	
	rendering_server->canvas_item_set_parent(canvas_item, canvas_parent);
	rendering_server->canvas_item_set_z_index(canvas_item, bullets_z_index);

	Transform2D xform = Transform2D(0.0, Vector2(0.0, 0.0));

	// Create each bullet
	for (int i = 0; i < total_bullets; ++i) {
		Bullet* bullet = new Bullet();

		bullet_pool[i] = bullet;
		bullet->item_rid = rendering_server->canvas_item_create();
		rendering_server->canvas_item_set_parent(bullet->item_rid, canvas_parent);
		rendering_server->canvas_item_set_material(bullet->item_rid, bullets_material->get_rid());

		bullet->pool_index = i;
		bullet->persistent_index = i;
		persistent_bullet_index[i] = i;

		// init the bullet
	}
}

void BulletInterface::_init_shots() {
	RID canvas_item = rendering_server->canvas_item_create();
	
	rendering_server->canvas_item_set_parent(canvas_item, canvas_parent);
	rendering_server->canvas_item_set_z_index(canvas_item, shots_z_index);

	Transform2D xform = Transform2D(0.0, Vector2(0.0, 0.0));

	// Create each bullet
	for (int i = 0; i < total_shots; ++i) {
		Bullet* bullet = new Bullet();

		shot_pool[i] = bullet;
		bullet->item_rid = rendering_server->canvas_item_create();
		rendering_server->canvas_item_set_parent(bullet->item_rid, canvas_item);
		rendering_server->canvas_item_set_material(bullet->item_rid, shots_material->get_rid());

		bullet->pool_index = i;
		bullet->persistent_index = i;
		persistent_shot_index[i] = i;

		// init the bullet
	}
}

void BulletInterface::_init_items() {
	RID canvas_item = rendering_server->canvas_item_create();
	
	rendering_server->canvas_item_set_parent(canvas_item, canvas_parent);
	rendering_server->canvas_item_set_z_index(canvas_item, items_z_index);

	Transform2D xform = Transform2D(0.0, Vector2(0.0, 0.0));

	// Create each bullet
	for (int i = 0; i < total_items; ++i) {
		Item* item = new Item();

		item_pool[i] = item;
		item->item_rid = rendering_server->canvas_item_create();
		rendering_server->canvas_item_set_parent(item->item_rid, canvas_item);
		rendering_server->canvas_item_set_material(item->item_rid, items_material->get_rid());

		// init the item
		item->pool_index = i;
		item->persistent_index = i;
		persistent_item_index[i] = i;

	}
}

void BulletInterface::_init_particles() {
	RID canvas_item = rendering_server->canvas_item_create();
	
	rendering_server->canvas_item_set_parent(canvas_item, canvas_parent);
	rendering_server->canvas_item_set_z_index(canvas_item, particles_z_index);

	Transform2D xform = Transform2D(0.0, Vector2(0.0, 0.0));

	// Create each bullet
	for (int i = 0; i < total_items; ++i) {
		Particle* particle = new Particle();

		particle_pool[i] = particle;
		particle->item_rid = rendering_server->canvas_item_create();
		rendering_server->canvas_item_set_parent(particle->item_rid, canvas_item);
		rendering_server->canvas_item_set_material(particle->item_rid, particles_material->get_rid());

		particle->pool_index = i;
		particle->persistent_index = i;
		persistent_particle_index[i] = i;

		// init the item
	}
}

void BulletInterface::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	
	if (last_origin != origin) {
		last_origin = origin;
	}

	int bullets_variation = 0;

	// Increase by golden-ration - 1 to have "maximum" "randomness"
    // Independent from time scale to preserve this effect
	animation_random += 0.61803398874989484820; 
	if (animation_random >= 1.0) animation_random -= 1.0;


	for (int i = total_bullets - 1; i >= available_bullets; --i) {
		Bullet* bullet = bullet_pool[i];
		if (_process_bullet(bullet, time_scale)) {
			_release_bullet(i);
			i += 1;
			continue;
		}
		rendering_server->canvas_item_set_parent(bullet->item_rid, canvas_parent);
		rendering_server->canvas_item_set_transform(bullet->item_rid, bullet->transform);

	}
	
	for (int i = total_shots - 1; i >= available_shots; --i) {
		Bullet* shot = shot_pool[i];
		if (_process_bullet(shot, time_scale)) {
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
		rendering_server->canvas_item_set_transform(particle->item_rid, particle->transform);
	}

}

bool BulletInterface::_process_bullet(Bullet* bullet, double delta) {
	Vector2 origin = bullet->position;

    int bounce_count = 0;

    if (bullet->process_mode < B1 || true) { // B type is unimplemented currently
        if (bullet->process_mode == A1) _process_bullet_a1(bullet, delta);
        else if (bullet->process_mode == A2) _process_bullet_a2(bullet, delta);
        else bounce_count = _process_bullet_a3(bullet, delta);
    }
    if (bullet->spin) {
        bullet->transform = bullet->transform.rotated(bullet->spin * delta);
        bullet->rotation += bullet->spin * delta;
    }

    // Decrease fade-in timer
    if (bullet->fade_timer) {
        bullet->fade_timer -= delta;

        if (bullet->fading) {
            if (bullet->fade_timer <= 0.0) {
				bullet->fading = false;
                bullet->fade_timer = 0.0;
                bullet->bullet_data.b = bullet->texture_offset;
                rendering_server->canvas_item_set_modulate(bullet->item_rid, bullet->bullet_data);
            } else {
                bullet->bullet_data.b = bullet->texture_offset + (bullet->fade_timer / bullet->fade_time - DBL_EPSILON);
                rendering_server->canvas_item_set_modulate(bullet->item_rid, bullet->bullet_data);
				
            }
        }
    }

    // Auto delete conditions, outside bounds or lifespan depleted
    if((!active_rect.has_point(bullet->position) && bullet->auto_delete) || bullet->lifetime >= bullet->lifespan) {
		return true;
    }


    // Iterate over existing transformations, TODO
    bool transform_applied = false;
    int j = 0;
    for (int i = 0; i < bullet->transforms.size(); i++) {
        Array xform = bullet->transforms[i]; // trigger, type, time, properties
        bool should_apply = false;
        int trigger = xform[0];
        
        // Check if the conditions are met
        switch (trigger) {
            case 0: // Time
                xform[2] = (double)xform[2] - delta;
                if ((double)xform[2] <= 0.0) {
                    should_apply = true;
                    transform_applied = true;
                    xform[2] = 0.0;
                } else {
                    bullet->transforms[j] = xform;
                    j++;
                }
                break;
            case 1: // Bounce
                xform[2] = (int)xform[2] - bounce_count;
                if ((int)xform[2] <= 0) {
                    should_apply = true;
                    transform_applied = true;
                    xform[2] = 0;
                } else {
                    bullet->transforms[j] = xform;
                    j++;
                }
                break;
        }

        if (should_apply) {
            // TODO
        }
    }

    // Update position and other data if a transformation has been made
    if (transform_applied) {
        
        bullet->transforms.resize(j);

        bullet->direction = Vector2(1.0, 0.0).rotated(bullet->angle);
        bullet->transform = bullet->transform.scaled((bullet->scale / bullet->transform.get_scale().x) * Vector2(1.0, 1.0)).rotated(bullet->angle - bullet->transform.get_rotation() + bullet_rotation_offset + bullet->rotation);
        bullet->transform.set_origin(bullet->position);
        rendering_server->canvas_item_set_draw_index(bullet->item_rid, (bullet->layer << 24) + bullet->draw_index);
    }

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
        bullet->transform = bullet->transform.rotated(bullet->wvel * delta);
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

// TODO
bool BulletInterface::_process_item(Item* item, double delta) {
	return false;
}

// TODO
bool BulletInterface::_process_particle(Particle* particle, double delta) {
	return false;

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


void BulletInterface::enable_bullet(Bullet* bullet) {
    bullet->auto_delete = true;
    bullet->is_grazed = false;
    bullet->layer = 0;
    bullet->lifetime = 0.0;
    bullet->lifespan = INFINITY;
    bullet->rotation = 0.0;
    // bullet->fade_delete = false;
    bullet->fading = true;
    bullet->transforms.clear();
    bullet->custom_data.clear();
	// TODO: Add customisation
	bullet->fade_time = 8.0;
	bullet->fade_timer = 8.0;
}

PackedInt64Array BulletInterface::create_bullet_a1(Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool glow) {
	if(available_bullets > 0) {
		available_bullets -= 1;
		active_bullets += 1;


		Bullet* bullet = (Bullet*)bullet_pool[available_bullets];
		RID rid = bullet->item_rid;
		enable_bullet(bullet);

		// Set layering to be above last bullet
		rendering_server->canvas_item_set_draw_index(rid, (bullet->layer << 24) + bullets_draw_index);
		bullet->draw_index = bullets_draw_index++;
		if (bullets_draw_index > 16777215) bullets_draw_index = 0; // 2^24 - 1

		rendering_server->canvas_item_add_texture_rect(bullet->item_rid, Rect2(-0.5, -0.5, 1.0, 1.0), bullets_texture_rid);
		if (bullet->additive != glow || true) {
			rendering_server->canvas_item_set_material(bullet->item_rid, glow ? bullets_material_add->get_rid() : bullets_material->get_rid());
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
		bullet->layer = bullet_data[DATA_LAYER];
		bullet->speed = speed;
		bullet->texture_offset = bullet_data[DATA_SPRITE_OFFSET];

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
		to_return.set(0, bullet->cycle);
		to_return.set(1, BULLETS_POOL);
		to_return.set(2, bullet->persistent_index);
		
		// godot::UtilityFunctions::print(bullet->position);
		

		return to_return;
	}
	return invalid_id;
}
	



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

// 			BulletID bullet_id = pool->obtain_bullet();
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
// 		result = pools[pool_index].pool->release_bullet(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]));
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
// 		return pools[pool_index].pool->is_bullet_valid(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]));
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
// 	if (pool_index >= 0 && pools[pool_index].pool->is_bullet_valid(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]))) {
// 		return pools[pool_index].bullet_kit;
// 	}
// 	return Ref<BulletKit>();
// }

// void BulletInterface::set_bullet_property(Variant id, String property, Variant value) {
// 	PackedInt64Array bullet_id = id.operator PackedInt64Array();

// 	int pool_index = bullet_id[1];
// 	if (pool_index >= 0) {
// 		pools[pool_index].pool->set_bullet_property(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]), property, value);
// 	}
// }


// Variant BulletInterface::get_bullet_property(Variant id, String property) {
// 	PackedInt64Array bullet_id = id.operator PackedInt64Array();

// 	int pool_index = bullet_id[1];
// 	if(pool_index >= 0) {
// 		return pools[pool_index].pool->get_bullet_property(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]), property);
// 	}
// 	return Variant();
// }

// Array BulletInterface::collide_and_graze_kit(Ref<BasicBulletKit> kit, Vector2 pos, double hitbox_radius, double graze_radius) {

// 	int pool_index = kits_to_pool_index[kit];
// 	BasicBulletPool* pool = (BasicBulletPool*)pools[pool_index].pool.get();
// 	return pool->_collide_and_graze(pos, hitbox_radius, graze_radius);
// }

// Array BulletInterface::collide_and_graze_player(Vector2 pos, double hitbox_radius, double graze_radius) {
// 	Array to_return = Array();
// 	to_return.append(Array());
// 	to_return.append(Array());
// 	for (int i = 0; i < enemy_bullet_kit_indices.size(); ++i) {
// 		BasicBulletPool* pool = (BasicBulletPool*)pools[enemy_bullet_kit_indices[i]].pool.get();
// 		Array result = pool->_collide_and_graze(pos, hitbox_radius, graze_radius);
// 		((Array)to_return[0]).append_array((Array)result[0]);
// 		((Array)to_return[1]).append_array((Array)result[1]);
// 	}
// 	return to_return;
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

// Array BulletInterface::collect_and_magnet_kit(Ref<BasicItemKit> kit, Vector2 pos, Node2D* target, double collect_radius, double magnet_radius) {
// 	int pool_index = kits_to_pool_index[kit];
// 	BasicItemPool* pool = (BasicItemPool*)pools[pool_index].pool.get();
// 	return pool->_collect_and_magnet(pos, target, collect_radius, magnet_radius);
// }

// Array BulletInterface::collect_and_magnet_all(Vector2 pos, Node2D* target, double collect_radius, double magnet_radius) {
// 	Array to_return = Array();

// 	for (int i = 0; i < item_kit_indices.size(); ++i) {
// 		BasicItemPool* pool = (BasicItemPool*)pools[item_kit_indices[i]].pool.get();
// 		to_return.append_array((Array)pool->_collect_and_magnet(pos, target, collect_radius, magnet_radius));
// 	}

// 	return to_return;
// }

// void BulletInterface::magnet_all_kit(Ref<BasicItemKit> kit, Node2D* target) {
// 	int pool_index = kits_to_pool_index[kit];
// 	BasicItemPool* pool = (BasicItemPool*)pools[pool_index].pool.get();
// 	pool->_magnet_all(target);
// }


// void BulletInterface::magnet_all(Node2D* target) {
// 	for (int i = 0; i < item_kit_indices.size(); ++i) {
// 		BasicItemPool* pool = (BasicItemPool*)pools[item_kit_indices[i]].pool.get();
// 		pool->_magnet_all(target);
// 	}
// }

// PackedInt64Array BulletInterface::create_shot_a1(Ref<BasicBulletKit> kit, Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool fade_in) {
	
// 	int pool_index = kits_to_pool_index[kit];
// 	BasicBulletPool* pool = (BasicBulletPool*)pools[pool_index].pool.get();

// 	if(pool->get_available_bullets() > 0) {
// 		available_bullets -= 1;
// 		active_bullets += 1;

// 		// Base init
// 		BulletID bullet_id = pool->_create_shot_a1(pos, speed, angle, bullet_data, fade_in);
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
// 		BulletID bullet_id = pool->_create_shot_a2(pos, speed, angle, accel, max_speed, bullet_data, fade_in);
// 		PackedInt64Array to_return = invalid_id;
// 		// to_return.resize(3);
// 		to_return.set(0, bullet_id.cycle);
// 		to_return.set(1, bullet_id.set);
// 		to_return.set(2, bullet_id.index);
		
// 		return to_return;
// 	}
	
// 	return invalid_id;
// }

// PackedInt64Array BulletInterface::create_item(Ref<BasicItemKit> kit, Vector2 pos, double speed, double angle, double spin, PackedFloat64Array item_data) {
// 	int pool_index = kits_to_pool_index[kit];
// 	BasicItemPool* pool = (BasicItemPool*)pools[pool_index].pool.get();

// 	if(pool->get_available_bullets() > 0) {
// 		available_bullets -= 1;
// 		active_bullets += 1;

// 		BulletID bullet_id = pool->_create_item(pos, speed, angle, spin, item_data);
// 		PackedInt64Array to_return = PackedInt64Array();
// 		to_return.resize(3);
// 		to_return.set(0, bullet_id.cycle);
// 		to_return.set(1, bullet_id.set);
// 		to_return.set(2, bullet_id.index);


// 		return to_return;
// 	}



// 	return invalid_id;

// }


// PackedInt64Array BulletInterface::create_particle(Ref<BasicParticleKit> kit, Vector2 pos, Vector2 drift, double rotation, double size, Color color) {


// 	int pool_index = kits_to_pool_index[kit];
// 	BasicParticlePool* pool = (BasicParticlePool*)pools[pool_index].pool.get();

// 	if(pool->get_available_bullets() > 0) {
// 		available_bullets -= 1;
// 		active_bullets += 1;

// 		BulletID bullet_id = pool->_create_particle(pos, drift, rotation, size, color);
// 		PackedInt64Array to_return = PackedInt64Array();
// 		to_return.resize(3);
// 		to_return.set(0, bullet_id.cycle);
// 		to_return.set(1, bullet_id.set);
// 		to_return.set(2, bullet_id.index);

// 		return to_return;
// 	}

// 	return invalid_id;

// }


// Vector2 BulletInterface::get_position(PackedInt64Array bullet_id) {
// 	if (bullet_id[1] >= 0) {
// 		return pools[bullet_id[1]].pool->get_position(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]));
// 	}
// 	return Vector2();

// }

// void BulletInterface::set_position(PackedInt64Array bullet_id, Vector2 position) {
// 	if (bullet_id[1] >= 0) {
// 		pools[bullet_id[1]].pool->set_position(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]), position);
// 	}

// }


// double BulletInterface::get_damage(PackedInt64Array bullet_id) {
// 	if (bullet_id[1] >= 0) {
// 		return pools[bullet_id[1]].pool->get_damage(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]));
// 	}
// 	return 0.0;

// }

// void BulletInterface::set_damage(PackedInt64Array bullet_id, double damage) {
// 	if (bullet_id[1] >= 0) {
// 		pools[bullet_id[1]].pool->set_damage(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]), damage);
// 	}

// }

// int BulletInterface::get_damage_type(PackedInt64Array bullet_id) {
// 	if (bullet_id[1] >= 0) {
// 		return pools[bullet_id[1]].pool->get_damage_type(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]));
// 	}
// 	return 0.0;

// }

// void BulletInterface::set_damage_type(PackedInt64Array bullet_id, int damage_type) {
// 	if (bullet_id[1] >= 0) {
// 		pools[bullet_id[1]].pool->set_damage_type(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]), damage_type);
// 	}

// }


// bool BulletInterface::get_is_auto_collected(PackedInt64Array bullet_id) {
// 	BasicItemPool* pool = (BasicItemPool*)pools[bullet_id[1]].pool.get();
// 	if (bullet_id[1] >= 0) {
// 		return pool->_get_is_auto_collected(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]));
// 	}
// 	return false;
