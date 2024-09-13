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

#include <bullets_interface.hpp>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/world2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void BulletsInterface::_bind_methods() {
    // ClassDB::bind_method(D_METHOD("get_bullets_environment"), &BulletsInterface::get_bullets_environment);
    // ClassDB::bind_method(D_METHOD("set_bullets_environment", "p_bullets_environment"), &BulletsInterface::mount);
    // ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
	// 	"bullets_environment",
	// 	PROPERTY_HINT_NODE_TYPE,
	// 	"Node"
	// ),
	// "set_bullets_environment", "get_bullets_environment");


	ClassDB::bind_method(D_METHOD("mount", "bullets_environment"), &BulletsInterface::mount);
	ClassDB::bind_method(D_METHOD("unmount"), &BulletsInterface::unmount);
	ClassDB::bind_method(D_METHOD("get_bullets_environment"), &BulletsInterface::get_bullets_environment);


	ClassDB::bind_method(D_METHOD(
		"get_total_active_bullets"), &BulletsInterface::get_total_active_bullets);
	

	ClassDB::bind_method(D_METHOD(
		"collide_and_graze",
		"bullet_kit",
		"position",
		"hitbox_radius",
		"graze_radius"), 
		&BulletsInterface::collide_and_graze
	);

	ClassDB::bind_method(D_METHOD(
		"collect_and_magnet",
		"item_kit",
		"target_node",
		"position",
		"collection_radius",
		"magnet_radius"), 
		&BulletsInterface::collect_and_magnet
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
		&BulletsInterface::create_item
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
		&BulletsInterface::create_particle
	);

	ClassDB::bind_method(D_METHOD(
		"create_shot_a1",
		"bullet_kit",
		"position",
		"speed",
		"angle",
		"bullet_data",
		"fade"), 
		&BulletsInterface::create_shot_a1
	);


	
	ClassDB::bind_method(D_METHOD(
		"get_position",
		"bullet_id"), 
		&BulletsInterface::get_position
	);
	
	ClassDB::bind_method(D_METHOD(
		"set_position",
		"bullet_id",
		"position"), 
		&BulletsInterface::set_position
	);

	
	ClassDB::bind_method(D_METHOD(
		"get_damage",
		"bullet_id"), 
		&BulletsInterface::get_damage
	);
	
	ClassDB::bind_method(D_METHOD(
		"set_damage",
		"bullet_id",
		"damage"), 
		&BulletsInterface::set_damage
	);
		
}

BulletsInterface::BulletsInterface() { }

BulletsInterface::~BulletsInterface() {
	_clear_rids();
}

void BulletsInterface::_init() {
	available_bullets = 0;
	active_bullets = 0;
	total_bullets = 0;
	invalid_id = PackedInt64Array();
	invalid_id.resize(3);
	invalid_id.set(0, -1);
	invalid_id.set(1, -1);
	invalid_id.set(2, -1);
}
void BulletsInterface::_physics_process(double delta) {
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

void BulletsInterface::_clear_rids() {
	// for(int i = 0; i < shared_areas.size(); i++) {
	// 	PhysicsServer2D::get_singleton()->area_clear_shapes(shared_areas[i]);
	// 	PhysicsServer2D::get_singleton()->free_rid(shared_areas[i]);
	// }
}


void BulletsInterface::mount(Node* bullets_environment) {
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
	
	for (int i = 0; i < bullet_kits.size(); ++i) {
		Ref<BulletKit> kit = bullet_kits[i];


		int pool_size = (int)pools_sizes[i];
		int z_index = (int)z_indices[i];

		// Initialise the pool
		pools[i].pool = kit->_create_pool();
		pools[i].bullet_kit = kit;
		pools[i].size = pool_size;
		pools[i].z_index = z_index;

		// Initialise visuals
		int pool_set_available_bullets = 0;
		pools[i].pool->_init(
			(CanvasItem*)bullets_environment->get_parent(), 
			pool_set_available_bullets,
			kit, 
			pool_size, 
			z_index, 
			origin
		);

		// Register the kit/pool-index pair 
		kits_to_pool_index[kit] = i;


		pool_set_available_bullets += pool_size;
		available_bullets += pool_size;
	}

	total_bullets = available_bullets;
}

void BulletsInterface::unmount(Node* bullets_environment) {
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

Node* BulletsInterface::get_bullets_environment() {
	return bullets_environment;
}

bool BulletsInterface::spawn_bullet(Ref<BulletKit> kit, Dictionary properties) {
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

Variant BulletsInterface::obtain_bullet(Ref<BulletKit> kit) {
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

bool BulletsInterface::release_bullet(Variant id) {
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

bool BulletsInterface::is_bullet_valid(Variant id) {
	PackedInt64Array bullet_id = id.operator PackedInt64Array();

	int pool_index = bullet_id[1];
	if(pool_index >= 0) {
		return pools[pool_index].pool->is_bullet_valid(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]));
	}
	return false;
}

bool BulletsInterface::is_kit_valid(Ref<BulletKit> kit) {
	return kits_to_pool_index.has(kit);
}

int BulletsInterface::get_available_bullets(Ref<BulletKit> kit) {
	if(kits_to_pool_index.has(kit)) {
		int pool_index = kits_to_pool_index[kit];
		return pools[pool_index].pool->get_available_bullets();
	}
	return 0;
}

int BulletsInterface::get_active_bullets(Ref<BulletKit> kit) {
	if(kits_to_pool_index.has(kit)) {
		int pool_index = kits_to_pool_index[kit];
		return pools[pool_index].pool->get_active_bullets();
	}
	return 0;
}

int BulletsInterface::get_pool_size(Ref<BulletKit> kit) {
	if(kits_to_pool_index.has(kit)) {
		int pool_index = kits_to_pool_index[kit];
		return pools[pool_index].size;
	}
	return 0;
}

int BulletsInterface::get_z_index(Ref<BulletKit> kit) {
	if(kits_to_pool_index.has(kit)) {
		int pool_index = kits_to_pool_index[kit];
		return pools[pool_index].z_index;
	}
	return 0;
}

int BulletsInterface::get_total_available_bullets() {
	return available_bullets;
}

int BulletsInterface::get_total_active_bullets() {
	return active_bullets;
}

// Prob 
bool BulletsInterface::is_bullet_existing(RID area_rid, int shape_index) {
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


Ref<BulletKit> BulletsInterface::get_kit_from_bullet(Variant id) {
	PackedInt64Array bullet_id = id.operator PackedInt64Array();

	int pool_index = bullet_id[1];
	if (pool_index >= 0 && pools[pool_index].pool->is_bullet_valid(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]))) {
		return pools[pool_index].bullet_kit;
	}
	return Ref<BulletKit>();
}

void BulletsInterface::set_bullet_property(Variant id, String property, Variant value) {
	PackedInt64Array bullet_id = id.operator PackedInt64Array();

	int pool_index = bullet_id[1];
	if (pool_index >= 0) {
		pools[pool_index].pool->set_bullet_property(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]), property, value);
	}
}


Variant BulletsInterface::get_bullet_property(Variant id, String property) {
	PackedInt64Array bullet_id = id.operator PackedInt64Array();

	int pool_index = bullet_id[1];
	if(pool_index >= 0) {
		return pools[pool_index].pool->get_bullet_property(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]), property);
	}
	return Variant();
}
Array BulletsInterface::collide_and_graze(Ref<BasicBulletKit> kit, Vector2 pos, double hitbox_radius, double graze_radius) {
	int pool_index = kits_to_pool_index[kit];
	BasicBulletPool* pool = (BasicBulletPool*)pools[pool_index].pool.get();
	return pool->_collide_and_graze(pos, hitbox_radius, graze_radius);
}

Array BulletsInterface::collect_and_magnet(Ref<BasicItemKit> kit, Vector2 pos, Node2D* target, double collect_radius, double magnet_radius) {
	int pool_index = kits_to_pool_index[kit];
	BasicItemPool* pool = (BasicItemPool*)pools[pool_index].pool.get();
	return pool->_collect_and_magnet(pos, target, collect_radius, magnet_radius);
}


PackedInt64Array BulletsInterface::create_shot_a1(Ref<BasicBulletKit> kit, Vector2 pos, double speed, double angle, PackedFloat64Array bullet_data, bool fade_in) {

	// UtilityFunctions::print(kits_to_pool_index[kit]);
	// kits_to_pool_index.has(kit) // For some reason checking for it using .has() doesn't make this run
	// Yet, if the print funciton is uncommented out then the check suddenly passes?

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

PackedInt64Array BulletsInterface::create_item(Ref<BasicItemKit> kit, Vector2 pos, double speed, double angle, double spin, PackedFloat64Array item_data) {
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


PackedInt64Array BulletsInterface::create_particle(Ref<BasicParticleKit> kit, Vector2 pos, Vector2 drift, double rotation, double size, Color color) {
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


Vector2 BulletsInterface::get_position(PackedInt64Array bullet_id) {
	// int pool_index = kits_to_pool_index[kit];
	// BasicParticlePool* pool = (BasicParticlePool*)pools[pool_index].pool.get();
	if (bullet_id[1] >= 0) {
		return pools[bullet_id[1]].pool->get_position(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]));
	}
	return Vector2();

}

void BulletsInterface::set_position(PackedInt64Array bullet_id, Vector2 position) {
	// int pool_index = kits_to_pool_index[kit];
	// BasicParticlePool* pool = (BasicParticlePool*)pools[pool_index].pool.get();
	if (bullet_id[1] >= 0) {
		pools[bullet_id[1]].pool->set_position(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]), position);
	}

}


double BulletsInterface::get_damage(PackedInt64Array bullet_id) {
	// int pool_index = kits_to_pool_index[kit];
	// BasicParticlePool* pool = (BasicParticlePool*)pools[pool_index].pool.get();
	if (bullet_id[1] >= 0) {
		return pools[bullet_id[1]].pool->get_damage(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]));
	}
	return 0.0;

}

void BulletsInterface::set_damage(PackedInt64Array bullet_id, double damage) {
	// int pool_index = kits_to_pool_index[kit];
	// BasicParticlePool* pool = (BasicParticlePool*)pools[pool_index].pool.get();
	if (bullet_id[1] >= 0) {
		pools[bullet_id[1]].pool->set_damage(BulletID(bullet_id[0], bullet_id[1], bullet_id[2]), damage);
	}

}

