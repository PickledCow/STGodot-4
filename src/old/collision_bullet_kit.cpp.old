#include <collision_bullet_kit.hpp>

using namespace godot;


Rect2 CollisionBulletKit::get_active_rect() {
    return active_rect;
}

void CollisionBulletKit::set_active_rect(Rect2 value) {
    active_rect = value;
}


void CollisionBulletKit::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_active_rect"), &CollisionBulletKit::get_active_rect);
    ClassDB::bind_method(D_METHOD("set_active_rect", "p_active_rect"), &CollisionBulletKit::set_active_rect);
    ADD_PROPERTY(PropertyInfo(Variant::RECT2, "active_rect"), "set_active_rect", "get_active_rect");

}

