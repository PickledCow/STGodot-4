#ifndef BASIC_PARTICLE_KIT_H
#define BASIC_PARTICLE_KIT_H

#include <bullet_kit.hpp>

#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/rendering_server.hpp>

namespace godot {

class BasicParticleKit;

// Bullet pool definition.
class BasicParticlePool : public AbstractBulletPool<BasicParticleKit, BasicParticle> {

	// void _init_bullet(Bullet* bullet); Use default implementation.
    public:

	void _enable_bullet(BasicParticle* bullet);
	// void _disable_bullet(Bullet* bullet); Use default implementation.
	bool _process_bullet(BasicParticle* bullet, double delta);

    BulletID _create_particle(Vector2 pos, Vector2 drift, double rotation, double size, Color color);
};


// Bullet kit definition.
class BasicParticleKit : public BulletKit {
	GDCLASS(BasicParticleKit, BulletKit)
    public:

	std::unique_ptr<BulletPool> _create_pool() override;


    static void _bind_methods();

};

};



#endif