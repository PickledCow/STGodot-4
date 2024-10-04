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
    // ClassDB::bind_method(D_METHOD("get_NO_CHANGE"), &BulletInterface::get_NO_CHANGE);
    // ClassDB::bind_method(D_METHOD("set_NO_CHANGE", "p_NO_CHANGE"), &BulletInterface::set_constant);
    // ADD_PROPERTY(PropertyInfo(Variant::INT, 
	// 	"NO_CHANGE"
	// ),
	// "set_NO_CHANGE", "get_NO_CHANGE");

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

	ClassDB::bind_method(D_METHOD("mount", "bullets_environment"), &BulletInterface::mount);
	ClassDB::bind_method(D_METHOD("unmount"), &BulletInterface::unmount);
	ClassDB::bind_method(D_METHOD("get_bullets_environment"), &BulletInterface::get_bullets_environment);


	ClassDB::bind_method(D_METHOD(
		"get_total_active_bullets"), &BulletInterface::get_total_active_bullets);
	

	ClassDB::bind_method(D_METHOD(
		"collide_and_graze_kit",
		"bullet_kit",
		"position",
		"hitbox_radius",
		"graze_radius"), 
		&BulletInterface::collide_and_graze_kit
	);
	
	ClassDB::bind_method(D_METHOD(
		"collide_and_graze_player",
		"position",
		"hitbox_radius",
		"graze_radius"), 
		&BulletInterface::collide_and_graze_player
	);

	ClassDB::bind_method(D_METHOD(
		"collide_and_graze_enemy",
		"position",
		"hitbox_radius",
		"graze_radius"), 
		&BulletInterface::collide_and_graze_enemy
	);

	ClassDB::bind_method(D_METHOD(
		"collect_and_magnet_kit",
		"item_kit",
		"target_node",
		"position",
		"collection_radius",
		"magnet_radius"), 
		&BulletInterface::collect_and_magnet_kit
	);

	ClassDB::bind_method(D_METHOD(
		"collect_and_magnet_all",
		"target_node",
		"position",
		"collection_radius",
		"magnet_radius"), 
		&BulletInterface::collect_and_magnet_all
	);
		
	ClassDB::bind_method(D_METHOD(
		"magnet_all_kit",
		"item_kit",
		"target_node"), 
		&BulletInterface::magnet_all_kit
	);

	ClassDB::bind_method(D_METHOD(
		"magnet_all",
		"target_node"), 
		&BulletInterface::magnet_all
	);
		
	ClassDB::bind_method(D_METHOD(
		"create_item",
		"item_kit",
		"position",
		"speed",
		"angle",
		"spin",
		"item_data"
		), 
		&BulletInterface::create_item
	);
	
	ClassDB::bind_method(D_METHOD(
		"create_particle",
		"particle_kit",
		"position",
		"drift",
		"rotation",
		"size",
		"color"
		), 
		&BulletInterface::create_particle
	);

	ClassDB::bind_method(D_METHOD(
		"create_shot_a1",
		"bullet_kit",
		"position",
		"speed",
		"angle",
		"bullet_data",
		"fade"), 
		&BulletInterface::create_shot_a1
	);

	ClassDB::bind_method(D_METHOD(
		"create_shot_a2",
		"bullet_kit",
		"position",
		"speed",
		"angle",
		"accel",
		"max_speed",
		"bullet_data",
		"fade"), 
		&BulletInterface::create_shot_a2
	);
	
	ClassDB::bind_method(D_METHOD(
		"get_position",
		"id"), 
		&BulletInterface::get_position
	);
	
	ClassDB::bind_method(D_METHOD(
		"set_position",
		"id",
		"position"), 
		&BulletInterface::set_position
	);

	
	ClassDB::bind_method(D_METHOD(
		"get_damage",
		"id"), 
		&BulletInterface::get_damage
	);
	
	ClassDB::bind_method(D_METHOD(
		"set_damage",
		"id",
		"damage"), 
		&BulletInterface::set_damage
	);
		
		
	ClassDB::bind_method(D_METHOD(
		"get_is_auto_collected",
		"item_id"), 
		&BulletInterface::get_is_auto_collected
	);
}

BulletInterface::BulletInterface() { }

BulletInterface::~BulletInterface() {
	_clear_rids();
}

void BulletInterface::_init() {
	available_bullets = 0;
	active_bullets = 0;
	total_bullets = 0;
	invalid_id = PackedInt64Array();
	invalid_id.resize(3);
	invalid_id.set(0, -1);
	invalid_id.set(1, -1);
	invalid_id.set(2, -1);
}
void BulletInterface::_physics_process(double delta) {
	if(Engine::get_singleton()->is_editor_hint() || bullets_environment == nullptr) {
		return;
	}
	
	
	Vector2 origin = parent->get_global_position();
	if (last_origin != origin) {
		last_origin = origin;
	}
	int bullets_variation = 0;

	// Increase by golden-ration - 1 to have "maximum" "randomness"
    // Independent from time scale to preserve this effect
	animation_random += 0.61803398874989484820; 
	if (animation_random >= 1.0) animation_random -= 1.0;

	for(int i = 0; i < pools.size(); i++) {
		double time_scale = pools[i].bullet_kit->time_scale;
		bullets_variation = pools[i].pool->_process(time_scale);
		available_bullets -= bullets_variation;
		active_bullets += bullets_variation;

		pools[i].pool->animation_random = animation_random;
	}

}

void BulletInterface::_clear_rids() {
	// for(int i = 0; i < shared_areas.size(); i++) {
	// 	PhysicsServer2D::get_singleton()->area_clear_shapes(shared_areas[i]);
	// 	PhysicsServer2D::get_singleton()->free_rid(shared_areas[i]);
	// }
}


void BulletInterface::mount(Node* bullets_environment) {
	_init();
	// UtilityFunctions::print("Starting mounting");
	if(bullets_environment == nullptr || this->bullets_environment == bullets_environment) {
		return;
	}
	if(this->bullets_environment != nullptr) {
		this->bullets_environment->set("current", false);
	}
	
	this->bullets_environment = bullets_environment;
	this->bullets_environment->set("current", true);

	Array bullet_kits = bullets_environment->get("bullet_kits");
	Array pools_sizes = bullets_environment->get("pools_sizes");
	Array z_indices = bullets_environment->get("z_indices");
	parent = (Node2D*)bullets_environment->get_parent();
	Vector2 origin = parent->get_global_position();
	last_origin = origin;

	pools.clear();
	pools.resize(bullet_kits.size());

	kits_to_pool_index.clear();
	
	_clear_rids();

	available_bullets = 0;
	active_bullets = 0;
	
	enemy_bullet_kit_indices = Array();
	player_bullet_kit_indices = Array();
	item_kit_indices = Array();

	for (int i = 0; i < bullet_kits.size(); ++i) {
		Ref<BulletKit> kit = bullet_kits[i];


		int pool_size = (int)pools_sizes[i];
		int z_index = (int)z_indices[i];

		// Initialise the pool
		pools[i].pool = kit->_create_pool();
		pools[i].bullet_kit = kit;
		pools[i].size = pool_size;
		pools[i].z_index = z_index;
		pools[i].pool->texture_width = kit->texture->get_width();

		// Initialise 
		int pool_set_available_bullets = 0;
		pools[i].pool->_init(
			(CanvasItem*)bullets_environment->get_parent(), 
			i,
			kit, 
			pool_size, 
			z_index, 
			origin
		);

		// Register the kit/pool-index pair 
		kits_to_pool_index[kit] = i;
		
		if (kit->kit_type == KIT_TYPE_BULLET) {
			Ref<BasicBulletKit> bullet_kit = bullet_kits[i];
			if (bullet_kit->affiliation == BasicBulletKit::ENEMY) {
				enemy_bullet_kit_indices.append(i);
			} else if (bullet_kit->affiliation == BasicBulletKit::PLAYER) {
				player_bullet_kit_indices.append(i);
			}
		} else if (kit->kit_type == KIT_TYPE_ITEM) {
			item_kit_indices.append(i);
		} 

		pool_set_available_bullets += pool_size;
		available_bullets += pool_size;
	}

	total_bullets = available_bullets;
}

void BulletInterface::unmount(Node* bullets_environment) {
	if(this->bullets_environment == bullets_environment) {
		pools.clear();
		kits_to_pool_index.clear();
		_clear_rids();
		// shared_areas.clear();

		available_bullets = 0;
		active_bullets = 0;
		total_bullets = 0;

		this->bullets_environment = nullptr;
	}
	if(bullets_environment != nullptr) {
		bullets_environment->set("current", false);
	}
}

Node* BulletInterface::get_bullets_environment() {
	return bullets_environment;
}

// DO NOT USE
bool BulletInterface::spawn_bullet(Ref<BulletKit> kit, Dictionary properties) {
	if(available_bullets > 0 && kits_to_pool_index.has(kit)) {
		PackedInt64Array pool_index = kits_to_pool_index[kit].operator PackedInt64Array();
		BulletPool* pool = pools[kits_to_pool_index[kit]].pool.get();

		if(pool->get_available_bullets() > 0) {
			available_bullets -= 1;
			active_bullets += 1;

			pool->spawn_bullet(properties);
			return true;
		}
	}
	return false;
}

Variant BulletInterface::obtain_bullet(Ref<BulletKit> kit) {
	if(available_bullets > 0 && kits_to_pool_index.has(kit)) {
		int pool_index = kits_to_pool_index[kit];
		BulletPool* pool = pools[pool_index].pool.get();

		if(pool->get_available_bullets() > 0) {
			available_bullets -= 1;
			active_bullets += 1;

			BulletID bullet_id = pool->obtain_bullet();
			PackedInt64Array to_return = invalid_id;
			to_return.set(0, bullet_id.cycle);
			to_return.set(1, bullet_id.set);
			to_return.set(2, bullet_id.index);
			return to_return;
		}
	}
	return invalid_id;
}

bool BulletInterface::release_bullet(Variant id) {
	PackedInt64Array bullet_id = id.operator PackedInt64Array();
	bool result = false;

	int pool_index = bullet_id[1];
	if (pool_index >= 0) {
		result = pools[pool_index].pool->release_bullet(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]));
		if(result) {
			available_bullets += 1;
			active_bullets -= 1;
		}
	}
	return result;
}

bool BulletInterface::is_bullet_valid(Variant id) {
	PackedInt64Array bullet_id = id.operator PackedInt64Array();

	int pool_index = bullet_id[1];
	if(pool_index >= 0) {
		return pools[pool_index].pool->is_bullet_valid(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]));
	}
	return false;
}

bool BulletInterface::is_kit_valid(Ref<BulletKit> kit) {
	return kits_to_pool_index.has(kit);
}

int BulletInterface::get_available_bullets(Ref<BulletKit> kit) {
	if(kits_to_pool_index.has(kit)) {
		int pool_index = kits_to_pool_index[kit];
		return pools[pool_index].pool->get_available_bullets();
	}
	return 0;
}

int BulletInterface::get_active_bullets(Ref<BulletKit> kit) {
	if(kits_to_pool_index.has(kit)) {
		int pool_index = kits_to_pool_index[kit];
		return pools[pool_index].pool->get_active_bullets();
	}
	return 0;
}

int BulletInterface::get_pool_size(Ref<BulletKit> kit) {
	if(kits_to_pool_index.has(kit)) {
		int pool_index = kits_to_pool_index[kit];
		return pools[pool_index].size;
	}
	return 0;
}

int BulletInterface::get_z_index(Ref<BulletKit> kit) {
	if(kits_to_pool_index.has(kit)) {
		int pool_index = kits_to_pool_index[kit];
		return pools[pool_index].z_index;
	}
	return 0;
}

int BulletInterface::get_total_available_bullets() {
	return available_bullets;
}

int BulletInterface::get_total_active_bullets() {
	return active_bullets;
}

// Prob 
bool BulletInterface::is_bullet_existing(RID area_rid, int shape_index) {
	// if(!areas_to_pool_set_indices.has(area_rid)) {
	// 	return false;
	// }
	// int set_index = areas_to_pool_set_indices[area_rid];
	// int pool_index = _get_pool_index(set_index, shape_index);
	// if(pool_index >= 0) {
	// 	return pool_sets[set_index].pools[pool_index].pool->is_bullet_existing(shape_index);
	// }
	return false;
}


Ref<BulletKit> BulletInterface::get_kit_from_bullet(Variant id) {
	PackedInt64Array bullet_id = id.operator PackedInt64Array();

	int pool_index = bullet_id[1];
	if (pool_index >= 0 && pools[pool_index].pool->is_bullet_valid(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]))) {
		return pools[pool_index].bullet_kit;
	}
	return Ref<BulletKit>();
}

void BulletInterface::set_bullet_property(Variant id, String property, Variant value) {
	PackedInt64Array bullet_id = id.operator PackedInt64Array();

	int pool_index = bullet_id[1];
	if (pool_index >= 0) {
		pools[pool_index].pool->set_bullet_property(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]), property, value);
	}
}


Variant BulletInterface::get_bullet_property(Variant id, String property) {
	PackedInt64Array bullet_id = id.operator PackedInt64Array();

	int pool_index = bullet_id[1];
	if(pool_index >= 0) {
		return pools[pool_index].pool->get_bullet_property(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]), property);
	}
	return Variant();
}

Array BulletInterface::collide_and_graze_kit(Ref<BasicBulletKit> kit, Vector2 pos, double hitbox_radius, double graze_radius) {
	if (kit->kit_type != KIT_TYPE_BULLET) {
		Array invalid_array = Array();
		invalid_array.append(Array());
		invalid_array.append(Array());
		return invalid_array;
	}
	int pool_index = kits_to_pool_index[kit];
	BasicBulletPool* pool = (BasicBulletPool*)pools[pool_index].pool.get();
	return pool->_collide_and_graze(pos, hitbox_radius, graze_radius);
}

Array BulletInterface::collide_and_graze_player(Vector2 pos, double hitbox_radius, double graze_radius) {
	Array to_return = Array();
	to_return.append(Array());
	to_return.append(Array());
	for (int i = 0; i < enemy_bullet_kit_indices.size(); ++i) {
		BasicBulletPool* pool = (BasicBulletPool*)pools[enemy_bullet_kit_indices[i]].pool.get();
		Array result = pool->_collide_and_graze(pos, hitbox_radius, graze_radius);
		((Array)to_return[0]).append_array((Array)result[0]);
		((Array)to_return[1]).append_array((Array)result[1]);
	}
	return to_return;
}
Array BulletInterface::collide_and_graze_enemy(Vector2 pos, double hitbox_radius, double graze_radius) {
	Array to_return = Array();
	to_return.append(Array());
	to_return.append(Array());
	for (int i = 0; i < player_bullet_kit_indices.size(); ++i) {
		BasicBulletPool* pool = (BasicBulletPool*)pools[player_bullet_kit_indices[i]].pool.get();
		Array result = pool->_collide_and_graze(pos, hitbox_radius, graze_radius);
		((Array)to_return[0]).append_array((Array)result[0]);
		((Array)to_return[1]).append_array((Array)result[1]);
	}
	return to_return;
}

Array BulletInterface::collect_and_magnet_kit(Ref<BasicItemKit> kit, Vector2 pos, Node2D* target, double collect_radius, double magnet_radius) {
	if (kit->kit_type != KIT_TYPE_ITEM) return Array();
	int pool_index = kits_to_pool_index[kit];
	BasicItemPool* pool = (BasicItemPool*)pools[pool_index].pool.get();
	return pool->_collect_and_magnet(pos, target, collect_radius, magnet_radius);
}

Array BulletInterface::collect_and_magnet_all(Vector2 pos, Node2D* target, double collect_radius, double magnet_radius) {
	Array to_return = Array();

	for (int i = 0; i < item_kit_indices.size(); ++i) {
		BasicItemPool* pool = (BasicItemPool*)pools[item_kit_indices[i]].pool.get();
		to_return.append_array((Array)pool->_collect_and_magnet(pos, target, collect_radius, magnet_radius));
	}

	return to_return;
}

void BulletInterface::magnet_all_kit(Ref<BasicItemKit> kit, Node2D* target) {
	if (kit->kit_type != KIT_TYPE_ITEM) return;
	int pool_index = kits_to_pool_index[kit];
	BasicItemPool* pool = (BasicItemPool*)pools[pool_index].pool.get();
	pool->_magnet_all(target);
}


void BulletInterface::magnet_all(Node2D* target) {
	for (int i = 0; i < item_kit_indices.size(); ++i) {
		BasicItemPool* pool = (BasicItemPool*)pools[item_kit_indices[i]].pool.get();
		pool->_magnet_all(target);
	}
}

PackedInt64Array BulletInterface::create_shot_a1(Ref<BasicBulletKit> kit, Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool fade_in) {
	int pool_index = kits_to_pool_index[kit];
	BasicBulletPool* pool = (BasicBulletPool*)pools[pool_index].pool.get();

	if(pool->get_available_bullets() > 0) {
		available_bullets -= 1;
		active_bullets += 1;

		// Base init
		BulletID bullet_id = pool->_create_shot_a1(pos, speed, angle, bullet_data, fade_in);
		PackedInt64Array to_return = invalid_id;
		// to_return.resize(3);
		to_return.set(0, bullet_id.cycle);
		to_return.set(1, bullet_id.set);
		to_return.set(2, bullet_id.index);
		
		return to_return;
	}
	
	return invalid_id;
}

PackedInt64Array BulletInterface::create_shot_a2(Ref<BasicBulletKit> kit, Vector2 pos, double speed, double angle, double accel, double max_speed, PackedFloat64Array bullet_data, bool fade_in) {
	int pool_index = kits_to_pool_index[kit];
	BasicBulletPool* pool = (BasicBulletPool*)pools[pool_index].pool.get();

	if(pool->get_available_bullets() > 0) {
		available_bullets -= 1;
		active_bullets += 1;

		// Base init
		BulletID bullet_id = pool->_create_shot_a2(pos, speed, angle, accel, max_speed, bullet_data, fade_in);
		PackedInt64Array to_return = invalid_id;
		// to_return.resize(3);
		to_return.set(0, bullet_id.cycle);
		to_return.set(1, bullet_id.set);
		to_return.set(2, bullet_id.index);
		
		return to_return;
	}
	
	return invalid_id;
}

PackedInt64Array BulletInterface::create_item(Ref<BasicItemKit> kit, Vector2 pos, double speed, double angle, double spin, PackedFloat64Array item_data) {
	int pool_index = kits_to_pool_index[kit];
	BasicItemPool* pool = (BasicItemPool*)pools[pool_index].pool.get();

	if(pool->get_available_bullets() > 0) {
		available_bullets -= 1;
		active_bullets += 1;

		BulletID bullet_id = pool->_create_item(pos, speed, angle, spin, item_data);
		PackedInt64Array to_return = PackedInt64Array();
		to_return.resize(3);
		to_return.set(0, bullet_id.cycle);
		to_return.set(1, bullet_id.set);
		to_return.set(2, bullet_id.index);


		return to_return;
	}



	return invalid_id;

}


PackedInt64Array BulletInterface::create_particle(Ref<BasicParticleKit> kit, Vector2 pos, Vector2 drift, double rotation, double size, Color color) {
	int pool_index = kits_to_pool_index[kit];
	BasicParticlePool* pool = (BasicParticlePool*)pools[pool_index].pool.get();

	if(pool->get_available_bullets() > 0) {
		available_bullets -= 1;
		active_bullets += 1;

		BulletID bullet_id = pool->_create_particle(pos, drift, rotation, size, color);
		PackedInt64Array to_return = PackedInt64Array();
		to_return.resize(3);
		to_return.set(0, bullet_id.cycle);
		to_return.set(1, bullet_id.set);
		to_return.set(2, bullet_id.index);

		return to_return;
	}

	return invalid_id;

}


Vector2 BulletInterface::get_position(PackedInt64Array bullet_id) {
	if (bullet_id[1] >= 0) {
		return pools[bullet_id[1]].pool->get_position(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]));
	}
	return Vector2();

}

void BulletInterface::set_position(PackedInt64Array bullet_id, Vector2 position) {
	if (bullet_id[1] >= 0) {
		pools[bullet_id[1]].pool->set_position(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]), position);
	}

}


double BulletInterface::get_damage(PackedInt64Array bullet_id) {
	if (bullet_id[1] >= 0) {
		return pools[bullet_id[1]].pool->get_damage(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]));
	}
	return 0.0;

}

void BulletInterface::set_damage(PackedInt64Array bullet_id, double damage) {
	if (bullet_id[1] >= 0) {
		pools[bullet_id[1]].pool->set_damage(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]), damage);
	}

}


bool BulletInterface::get_is_auto_collected(PackedInt64Array bullet_id) {
	BasicItemPool* pool = (BasicItemPool*)pools[bullet_id[1]].pool.get();
	if (bullet_id[1] >= 0) {
		return pool->_get_is_auto_collected(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]));
	}
	return false;
}