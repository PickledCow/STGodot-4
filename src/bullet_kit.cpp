#include <bullet_kit.hpp>

using namespace godot;

Ref<Texture2D> BulletKit::get_texture() {
    return texture;
}

Ref<Material> BulletKit::get_material() {
    return material;
}

double BulletKit::get_texture_width() {
    return texture_width;
}

bool BulletKit::get_facing_up() {
    return facing_up;
}

double BulletKit::get_fade_time() {
    return fade_time;
}

Rect2 BulletKit::get_active_rect() {
    return active_rect;
}

Rect2 BulletKit::get_bounce_rect() {
    return bounce_rect;
}

Rect2 BulletKit::get_warp_rect() {
    return warp_rect;
}

double BulletKit::get_time_scale() {
    return time_scale;
}

void BulletKit::set_texture(Ref<Texture2D> value) {
    texture = value;
}
void BulletKit::set_material(Ref<Material> value) {
    material = value;
}

void BulletKit::set_texture_width(double value) {
    texture_width = value;
}

void BulletKit::set_facing_up(bool value) {
    facing_up = value;
}

void BulletKit::set_fade_time(double value) {
    fade_time = value;
}

void BulletKit::set_active_rect(Rect2 value) {
    active_rect = value;
}

void BulletKit::set_bounce_rect(Rect2 value) {
    bounce_rect = value;
}

void BulletKit::set_warp_rect(Rect2 value) {
    warp_rect = value;
}

void BulletKit::set_time_scale(double value) {
    time_scale = value;
}


void BulletKit::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("get_texture"), &BulletKit::get_texture);
    ClassDB::bind_method(D_METHOD("set_texture", "p_texture"), &BulletKit::set_texture);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "texture", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "Texture2D"
        ), 
        "set_texture", "get_texture");
    ClassDB::bind_method(D_METHOD("get_material"), &BulletKit::get_material);
    ClassDB::bind_method(D_METHOD("set_material", "p_material"), &BulletKit::set_material);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
            "material", 
            PROPERTY_HINT_RESOURCE_TYPE,
            "ShaderMaterial"
        ), 
        "set_material", "get_material");
    ClassDB::bind_method(D_METHOD("get_texture_width"), &BulletKit::get_texture_width);
    ClassDB::bind_method(D_METHOD("set_texture_width", "p_texture_width"), &BulletKit::set_texture_width);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "texture_width"), "set_texture_width", "get_texture_width");
    ClassDB::bind_method(D_METHOD("get_facing_up"), &BulletKit::get_facing_up);
    ClassDB::bind_method(D_METHOD("set_facing_up", "p_facing_up"), &BulletKit::set_facing_up);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "facing_up"), "set_facing_up", "get_facing_up");
    ClassDB::bind_method(D_METHOD("get_fade_time"), &BulletKit::get_fade_time);
    ClassDB::bind_method(D_METHOD("set_fade_time", "p_fade_time"), &BulletKit::set_fade_time);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fade_time"), "set_fade_time", "get_fade_time");
    ClassDB::bind_method(D_METHOD("get_active_rect"), &BulletKit::get_active_rect);
    ClassDB::bind_method(D_METHOD("set_active_rect", "p_active_rect"), &BulletKit::set_active_rect);
    ADD_PROPERTY(PropertyInfo(Variant::RECT2, "active_rect"), "set_active_rect", "get_active_rect");
    ClassDB::bind_method(D_METHOD("get_bounce_rect"), &BulletKit::get_bounce_rect);
    ClassDB::bind_method(D_METHOD("set_bounce_rect", "p_bounce_rect"), &BulletKit::set_bounce_rect);
    ADD_PROPERTY(PropertyInfo(Variant::RECT2, "bounce_rect"), "set_bounce_rect", "get_bounce_rect");
    ClassDB::bind_method(D_METHOD("get_warp_rect"), &BulletKit::get_warp_rect);
    ClassDB::bind_method(D_METHOD("set_warp_rect", "p_warp_rect"), &BulletKit::set_warp_rect);
    ADD_PROPERTY(PropertyInfo(Variant::RECT2, "warp_rect"), "set_warp_rect", "get_warp_rect");
    ClassDB::bind_method(D_METHOD("get_time_scale"), &BulletKit::get_time_scale);
    ClassDB::bind_method(D_METHOD("set_time_scale", "p_time_scale"), &BulletKit::set_time_scale);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, 
            "time_scale",
            PROPERTY_HINT_RANGE,
            "0,2,0.001,or_greater"
        ),
        "set_time_scale", "get_time_scale");
    


    // ClassDB::bind_method(D_METHOD("get_amplitude"), &GDExample::get_amplitude);
	// ClassDB::bind_method(D_METHOD("set_amplitude", "p_amplitude"), &GDExample::set_amplitude);
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "amplitude"), "set_amplitude", "get_amplitude");

}
