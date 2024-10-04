#include "register_types.h"

#include "gdexample.hpp"

// #include "bullet.hpp"
#include "bullet_kit.hpp"
#include "bullet_interface.hpp"

#include "collision_bullet_kit.hpp"

#include "basic_bullet_kit.hpp"
#include "basic_item_kit.hpp"
#include "basic_particle_kit.hpp"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_stgodot_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(GDExample);
	// GDREGISTER_CLASS(Bullet);
	GDREGISTER_ABSTRACT_CLASS(BulletKit);
	GDREGISTER_ABSTRACT_CLASS(CollisionBulletKit);
	GDREGISTER_CLASS(BulletInterface);

	GDREGISTER_CLASS(BasicBulletKit);
	GDREGISTER_CLASS(BasicItemKit);
	GDREGISTER_CLASS(BasicParticleKit);
}

void uninitialize_stgodot_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT stgodot_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_stgodot_module);
	init_obj.register_terminator(uninitialize_stgodot_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
