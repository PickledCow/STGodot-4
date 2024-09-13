#include <basic_particle_kit.hpp>

using namespace godot;


void BasicParticleKit::_bind_methods() {
};



std::unique_ptr<BulletPool> BasicParticleKit::_create_pool() {						
	return std::unique_ptr<BulletPool> (new BasicParticlePool());					
}

BulletID BasicParticlePool::_create_particle(Vector2 pos, Vector2 drift, double rotation, double size, Color color) {
    available_bullets -= 1;
    active_bullets += 1;

    BasicParticle* bullet = (BasicParticle*)bullets[available_bullets];

    RID rid = bullet->item_rid;

    rendering_server->canvas_item_set_draw_index(rid, (draw_index++));
    bullet->draw_index = draw_index++;
    if (draw_index > 16777215) draw_index = 0; // 2^24
    
    _enable_bullet(bullet);
    Transform2D xform = Transform2D(0.0, Vector2(0.0, 0.0)).scaled(size * Vector2(1.0, 1.0));
    xform.rotate(rotation);
    xform.set_origin(pos);
    

    bullet->transform = xform;
    bullet->position = pos;
    bullet->bullet_data = color;
    bullet->direction = drift;

    rendering_server->canvas_item_set_transform(rid, xform);

    rendering_server->canvas_item_set_draw_index(rid, (bullet->layer << 24) + bullet->draw_index);
    rendering_server->canvas_item_set_modulate(bullet->item_rid, color);

    return BulletID(bullet->cycle, set_index, bullet->pool_index);

}

void BasicParticlePool::_enable_bullet(BasicParticle* bullet) {
    // Reset some bullet variables that are not set by the create_bullet functions
    bullet->fading = false;
    bullet->layer = 0;
    bullet->lifetime = 0.0;
    bullet->lifespan = kit->fade_time;

    Rect2 texture_rect = Rect2(-0.5, -0.5, 1.0, 1.0);
    RID texture_rid = kit->texture->get_rid();

    // Configure the bullet to draw the kit texture each frame.
    rendering_server->canvas_item_add_texture_rect(bullet->item_rid,
        texture_rect,
        texture_rid);
}



bool BasicParticlePool::_process_bullet(BasicParticle* bullet, double delta) {
    Color c = bullet->bullet_data;
    c.a = bullet->lifetime / bullet->lifespan;
    rendering_server->canvas_item_set_modulate(bullet->item_rid, c);
    // bullet->transform.translate_local(bullet->direction);
    bullet->transform = bullet->transform.translated(bullet->direction);
    if (bullet->lifetime >= bullet->lifespan) {
        return true;
    }
    bullet->lifetime += delta;

    return false;
}