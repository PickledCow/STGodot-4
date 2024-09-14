#include <collision_bullet_kit.hpp>

using namespace godot;


Rect2 CollisionBulletKit::get_active_rect() {
    return active_rect;
}

Rect2 CollisionBulletKit::get_bounce_rect() {
    return bounce_rect;
}

Rect2 CollisionBulletKit::get_warp_rect() {
    return warp_rect;
}

void CollisionBulletKit::set_active_rect(Rect2 value) {
    active_rect = value;
}

void CollisionBulletKit::set_bounce_rect(Rect2 value) {
    bounce_rect = value;
}

void CollisionBulletKit::set_warp_rect(Rect2 value) {
    warp_rect = value;
}

void CollisionBulletKit::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_active_rect"), &CollisionBulletKit::get_active_rect);
    ClassDB::bind_method(D_METHOD("set_active_rect", "p_active_rect"), &CollisionBulletKit::set_active_rect);
    ADD_PROPERTY(PropertyInfo(Variant::RECT2, "active_rect"), "set_active_rect", "get_active_rect");
    ClassDB::bind_method(D_METHOD("get_bounce_rect"), &CollisionBulletKit::get_bounce_rect);
    ClassDB::bind_method(D_METHOD("set_bounce_rect", "p_bounce_rect"), &CollisionBulletKit::set_bounce_rect);
    ADD_PROPERTY(PropertyInfo(Variant::RECT2, "bounce_rect"), "set_bounce_rect", "get_bounce_rect");
    ClassDB::bind_method(D_METHOD("get_warp_rect"), &CollisionBulletKit::get_warp_rect);
    ClassDB::bind_method(D_METHOD("set_warp_rect", "p_warp_rect"), &CollisionBulletKit::set_warp_rect);
    ADD_PROPERTY(PropertyInfo(Variant::RECT2, "warp_rect"), "set_warp_rect", "get_warp_rect");
}

