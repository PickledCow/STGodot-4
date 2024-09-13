#include <bullet.hpp>

using namespace godot;

// RID Bullet::get_item_rid() {
//     return item_rid;
// }

// void Bullet::set_item_rid(RID value) {
//     ERR_PRINT("Can't edit the item rid of bullets!");
// }

// int Bullet::get_cycle() {
//     return cycle;
// }

// void Bullet::set_cycle(int value) {
//     ERR_PRINT("Can't edit the cycle of bullets!");
// }

// int Bullet::get_pool_index() {
//     return pool_index;
// }

// void Bullet::set_pool_index(int value) {
//     ERR_PRINT("Can't edit the pool index of bullets!");
// }


// int Bullet::get_process_mode() {
//     return int(process_mode);
// }

// void Bullet::set_process_mode(int value) {
//     ERR_PRINT("Can't edit the process mode of bullets!");
// }


// Node2D* Bullet::get_magnet_target() {
//     return magnet_target;
// }

// bool Bullet::get_magneted() {
//     return magneted;
// }


// void Bullet::set_magnet_target(Node2D* value) {
//     magnet_target = value;
// }

// void Bullet::set_magneted(bool value) {
//     magneted = value;
// }


// Transform2D Bullet::get_transform() {
//     return transform;
// }


// Vector2 Bullet::get_direction() {
//     return direction;
// }

// int Bullet::get_draw_index() {
//     return draw_index;
// }

// bool Bullet::get_fading() {
//     return fading;
// }

// Array Bullet::get_patterns() {
//     return patterns;
// }

// Color Bullet::get_bullet_data() {
//     return bullet_data;
// }

// double Bullet::get_scale() {
//     return scale;
// }

// double Bullet::get_hitbox_scale() {
//     return hitbox_scale;
// }

// double Bullet::get_texture_offset() {
//     return texture_offset;
// }

// int Bullet::get_layer() {
//     return layer;
// }

// Color Bullet::get_fade_color() {
//     return fade_color;
// }

// Vector2 Bullet::get_position() {
//     return position;
// }

// double Bullet::get_rotation() {
//     return rotation;
// }

// double Bullet::get_spin() {
//     return spin;
// }

// double Bullet::get_fade_timer() {
//     return fade_timer;
// }

// double Bullet::get_fade_time() {
//     return fade_time;
// }

// bool Bullet::get_fade_delete() {
//     return fade_delete;
// }

// bool Bullet::get_grazed() {
//     return grazed;
// }

// bool Bullet::get_auto_delete() {
//     return auto_delete;
// }

// double Bullet::get_damage() {
//     return damage;
// }

// int Bullet::get_damage_type() {
//     return damage_type;
// }

// double Bullet::get_lifetime() {
//     return lifetime;
// }

// double Bullet::get_lifespan() {
//     return lifespan;
// }

// bool Bullet::get_upright() {
//     return upright;
// }

// double Bullet::get_angle() {
//     return angle;
// }

// double Bullet::get_speed() {
//     return speed;
// }

// double Bullet::get_max_speed() {
//     return max_speed;
// }

// double Bullet::get_accel() {
//     return accel;
// }

// int Bullet::get_bounce_mode() {
//     return bounce_mode;
// }

// int Bullet::get_bounce_count() {
//     return bounce_count;
// }

// int Bullet::get_bounce_surfaces() {
//     return bounce_surfaces;
// }


// double Bullet::get_wvel() {
//     return wvel;
// }

// double Bullet::get_max_wvel() {
//     return max_wvel;
// }

// double Bullet::get_waccel() {
//     return waccel;
// }

// void Bullet::set_transform(Transform2D value) {
//     transform = value;
// }


// void Bullet::set_direction(Vector2 value) {
//     direction = value;
// }

// void Bullet::set_draw_index(int value) {
//     draw_index = value;
// }

// void Bullet::set_fading(bool value) {
//     fading = value;
// }

// void Bullet::set_patterns(Array value) {
//     patterns = value;
// }

// void Bullet::set_bullet_data(Color value) {
//     bullet_data = value;
// }

// void Bullet::set_scale(double value) {
//     scale = value;
// }

// void Bullet::set_hitbox_scale(double value) {
//     hitbox_scale = value;
// }

// void Bullet::set_texture_offset(double value) {
//     texture_offset = value;
// }

// void Bullet::set_layer(int value) {
//     layer = value;
// }

// void Bullet::set_fade_color(Color value) {
//     fade_color = value;
// }

// void Bullet::set_position(Vector2 value) {
//     position = value;
// }

// void Bullet::set_rotation(double value) {
//     rotation = value;
// }

// void Bullet::set_spin(double value) {
//     spin = value;
// }

// void Bullet::set_fade_timer(double value) {
//     fade_timer = value;
// }

// void Bullet::set_fade_time(double value) {
//     fade_time = value;
// }

// void Bullet::set_fade_delete(bool value) {
//     fade_delete = value;
// }

// void Bullet::set_grazed(bool value) {
//     grazed = value;
// }

// void Bullet::set_auto_delete(bool value) {
//     auto_delete = value;
// }

// void Bullet::set_damage(double value) {
//     damage = value;
// }

// void Bullet::set_damage_type(int value) {
//     damage_type = value;
// }

// void Bullet::set_lifetime(double value) {
//     lifetime = value;
// }

// void Bullet::set_lifespan(double value) {
//     lifespan = value;
// }

// void Bullet::set_upright(bool value) {
//     upright = value;
// }

// void Bullet::set_angle(double value) {
//     angle = value;
// }

// void Bullet::set_speed(double value) {
//     speed = value;
// }

// void Bullet::set_max_speed(double value) {
//     max_speed = value;
// }

// void Bullet::set_accel(double value) {
//     accel = value;
// }

// void Bullet::set_bounce_mode(int value) {
//     bounce_mode = value;
// }

// void Bullet::set_bounce_count(int value) {
//     bounce_count = value;
// }

// void Bullet::set_bounce_surfaces(int value) {
//     bounce_surfaces = value;
// }

// void Bullet::set_wvel(double value) {
//     wvel = value;
// }

// void Bullet::set_max_wvel(double value) {
//     max_wvel = value;
// }

// void Bullet::set_waccel(double value) {
//     waccel = value;
// }


// void Bullet::_bind_methods() {
    

//     // ClassDB::bind_method(D_METHOD("get_magnet_target"), &Bullet::get_magnet_target);
//     // ClassDB::bind_method(D_METHOD("set_magnet_target", "p_magnet_target"), &Bullet::set_magnet_target);
//     // ADD_PROPERTY(PropertyInfo(Variant::OBJECT, 
//     //         "magnet_target",
//     //         PROPERTY_HINT_NODE_TYPE,
//     //         "Node2D"
//     //     ), 
//     //     "set_magnet_target", "get_magnet_target");
//     if (false) {
//         // ClassDB::bind_method(D_METHOD("get_magneted"), &Bullet::get_magneted);
//         // ClassDB::bind_method(D_METHOD("set_magneted", "p_magneted"), &Bullet::set_magneted);
//         // ADD_PROPERTY(PropertyInfo(Variant::BOOL, "magneted"), "set_magneted", "get_magneted");


//         // ClassDB::bind_method(D_METHOD("get_item_rid"), &Bullet::get_item_rid);
//         // ClassDB::bind_method(D_METHOD("set_item_rid", "p_item_rid"), &Bullet::set_item_rid);
//         // ADD_PROPERTY(PropertyInfo(Variant::RID, "item_rid"), "set_item_rid", "get_item_rid");

//         // ClassDB::bind_method(D_METHOD("get_cycle"), &Bullet::get_cycle);
//         // ClassDB::bind_method(D_METHOD("set_cycle", "p_cycle"), &Bullet::set_cycle);
//         // ADD_PROPERTY(PropertyInfo(Variant::INT, "cycle"), "set_cycle", "get_cycle");
        
//         // ClassDB::bind_method(D_METHOD("get_pool_index"), &Bullet::get_pool_index);
//         // ClassDB::bind_method(D_METHOD("set_pool_index", "p_shape_index"), &Bullet::set_pool_index);
//         // ADD_PROPERTY(PropertyInfo(Variant::INT, "pool_index"), "set_pool_index", "get_pool_index");
        
//         // ClassDB::bind_method(D_METHOD("get_process_mode"), &Bullet::get_process_mode);
//         // ClassDB::bind_method(D_METHOD("set_process_mode", "p_process_mode"), &Bullet::set_process_mode);
//         // ADD_PROPERTY(PropertyInfo(Variant::INT, "process_mode"), "set_process_mode", "get_process_mode");

//         // ClassDB::bind_method(D_METHOD("get_transform"), &Bullet::get_transform);
//         // ClassDB::bind_method(D_METHOD("set_transform", "p_transform"), &Bullet::set_transform);
//         // ADD_PROPERTY(PropertyInfo(Variant::TRANSFORM2D, "transform"), "set_transform", "get_transform");
//         // ClassDB::bind_method(D_METHOD("get_direction"), &Bullet::get_direction);
//         // ClassDB::bind_method(D_METHOD("set_direction", "p_direction"), &Bullet::set_direction);
//         // ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "direction"), "set_direction", "get_direction");
//         // ClassDB::bind_method(D_METHOD("get_draw_index"), &Bullet::get_draw_index);
//         // ClassDB::bind_method(D_METHOD("set_draw_index", "p_draw_index"), &Bullet::set_draw_index);
//         // ADD_PROPERTY(PropertyInfo(Variant::INT, "draw_index"), "set_draw_index", "get_draw_index");
//         // ClassDB::bind_method(D_METHOD("get_fading"), &Bullet::get_fading);
//         // ClassDB::bind_method(D_METHOD("set_fading", "p_fading"), &Bullet::set_fading);
//         // ADD_PROPERTY(PropertyInfo(Variant::BOOL, "fading"), "set_fading", "get_fading");
//         // ClassDB::bind_method(D_METHOD("get_patterns"), &Bullet::get_patterns);
//         // ClassDB::bind_method(D_METHOD("set_patterns", "p_patterns"), &Bullet::set_patterns);
//         // ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "patterns"), "set_patterns", "get_patterns");
//         // ClassDB::bind_method(D_METHOD("get_bullet_data"), &Bullet::get_bullet_data);
//         // ClassDB::bind_method(D_METHOD("set_bullet_data", "p_bullet_data"), &Bullet::set_bullet_data);
//         // ADD_PROPERTY(PropertyInfo(Variant::COLOR, "bullet_data"), "set_bullet_data", "get_bullet_data");
//         // ClassDB::bind_method(D_METHOD("get_scale"), &Bullet::get_scale);
//         // ClassDB::bind_method(D_METHOD("set_scale", "p_scale"), &Bullet::set_scale);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "scale"), "set_scale", "get_scale");
//         // ClassDB::bind_method(D_METHOD("get_hitbox_scale"), &Bullet::get_hitbox_scale);
//         // ClassDB::bind_method(D_METHOD("set_hitbox_scale", "p_hitbox_scale"), &Bullet::set_hitbox_scale);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "hitbox_scale"), "set_hitbox_scale", "get_hitbox_scale");
//         // ClassDB::bind_method(D_METHOD("get_texture_offset"), &Bullet::get_texture_offset);
//         // ClassDB::bind_method(D_METHOD("set_texture_offset", "p_texture_offset"), &Bullet::set_texture_offset);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "texture_offset"), "set_texture_offset", "get_texture_offset");
//         // ClassDB::bind_method(D_METHOD("get_layer"), &Bullet::get_layer);
//         // ClassDB::bind_method(D_METHOD("set_layer", "p_layer"), &Bullet::set_layer);
//         // ADD_PROPERTY(PropertyInfo(Variant::INT, "layer"), "set_layer", "get_layer");
//         // ClassDB::bind_method(D_METHOD("get_fade_color"), &Bullet::get_fade_color);
//         // ClassDB::bind_method(D_METHOD("set_fade_color", "p_fade_color"), &Bullet::set_fade_color);
//         // ADD_PROPERTY(PropertyInfo(Variant::COLOR, "fade_color"), "set_fade_color", "get_fade_color");
//         // ClassDB::bind_method(D_METHOD("get_position"), &Bullet::get_position);
//         // ClassDB::bind_method(D_METHOD("set_position", "p_position"), &Bullet::set_position);
//         // ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "position"), "set_position", "get_position");
//         // ClassDB::bind_method(D_METHOD("get_rotation"), &Bullet::get_rotation);
//         // ClassDB::bind_method(D_METHOD("set_rotation", "p_rotation"), &Bullet::set_rotation);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotation"), "set_rotation", "get_rotation");
//         // ClassDB::bind_method(D_METHOD("get_spin"), &Bullet::get_spin);
//         // ClassDB::bind_method(D_METHOD("set_spin", "p_spin"), &Bullet::set_spin);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spin"), "set_spin", "get_spin");
//         // ClassDB::bind_method(D_METHOD("get_fade_timer"), &Bullet::get_fade_timer);
//         // ClassDB::bind_method(D_METHOD("set_fade_timer", "p_fade_timer"), &Bullet::set_fade_timer);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fade_timer"), "set_fade_timer", "get_fade_timer");
//         // ClassDB::bind_method(D_METHOD("get_fade_time"), &Bullet::get_fade_time);
//         // ClassDB::bind_method(D_METHOD("set_fade_time", "p_fade_time"), &Bullet::set_fade_time);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fade_time"), "set_fade_time", "get_fade_time");
//         // ClassDB::bind_method(D_METHOD("get_fade_delete"), &Bullet::get_fade_delete);
//         // ClassDB::bind_method(D_METHOD("set_fade_delete", "p_fade_delete"), &Bullet::set_fade_delete);
//         // ADD_PROPERTY(PropertyInfo(Variant::BOOL, "fade_delete"), "set_fade_delete", "get_fade_delete");
//         // ClassDB::bind_method(D_METHOD("get_grazed"), &Bullet::get_grazed);
//         // ClassDB::bind_method(D_METHOD("set_grazed", "p_grazed"), &Bullet::set_grazed);
//         // ADD_PROPERTY(PropertyInfo(Variant::BOOL, "grazed"), "set_grazed", "get_grazed");
//         // ClassDB::bind_method(D_METHOD("get_auto_delete"), &Bullet::get_auto_delete);
//         // ClassDB::bind_method(D_METHOD("set_auto_delete", "p_auto_delete"), &Bullet::set_auto_delete);
//         // ADD_PROPERTY(PropertyInfo(Variant::BOOL, "auto_delete"), "set_auto_delete", "get_auto_delete");
//         // ClassDB::bind_method(D_METHOD("get_damage"), &Bullet::get_damage);
//         // ClassDB::bind_method(D_METHOD("set_damage", "p_damage"), &Bullet::set_damage);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "damage"), "set_damage", "get_damage");
//         // ClassDB::bind_method(D_METHOD("get_damage_type"), &Bullet::get_damage_type);
//         // ClassDB::bind_method(D_METHOD("set_damage_type", "p_damage_type"), &Bullet::set_damage_type);
//         // ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_type"), "set_damage_type", "get_damage_type");
//         // ClassDB::bind_method(D_METHOD("get_lifetime"), &Bullet::get_lifetime);
//         // ClassDB::bind_method(D_METHOD("set_lifetime", "p_lifetime"), &Bullet::set_lifetime);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "lifetime"), "set_lifetime", "get_lifetime");
//         // ClassDB::bind_method(D_METHOD("get_lifespan"), &Bullet::get_lifespan);
//         // ClassDB::bind_method(D_METHOD("set_lifespan", "p_lifespan"), &Bullet::set_lifespan);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "lifespan"), "set_lifespan", "get_lifespan");
//         // ClassDB::bind_method(D_METHOD("get_upright"), &Bullet::get_upright);
//         // ClassDB::bind_method(D_METHOD("set_upright", "p_upright"), &Bullet::set_upright);
//         // ADD_PROPERTY(PropertyInfo(Variant::BOOL, "upright"), "set_upright", "get_upright");
//         // ClassDB::bind_method(D_METHOD("get_angle"), &Bullet::get_angle);
//         // ClassDB::bind_method(D_METHOD("set_angle", "p_angle"), &Bullet::set_angle);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angle"), "set_angle", "get_angle");
//         // ClassDB::bind_method(D_METHOD("get_speed"), &Bullet::get_speed);
//         // ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Bullet::set_speed);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
//         // ClassDB::bind_method(D_METHOD("get_max_speed"), &Bullet::get_max_speed);
//         // ClassDB::bind_method(D_METHOD("set_max_speed", "p_max_speed"), &Bullet::set_max_speed);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_speed"), "set_max_speed", "get_max_speed");
//         // ClassDB::bind_method(D_METHOD("get_accel"), &Bullet::get_accel);
//         // ClassDB::bind_method(D_METHOD("set_accel", "p_accel"), &Bullet::set_accel);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "accel"), "set_accel", "get_accel");
//         // ClassDB::bind_method(D_METHOD("get_bounce_mode"), &Bullet::get_bounce_mode);
//         // ClassDB::bind_method(D_METHOD("set_bounce_mode", "p_bounce_mode"), &Bullet::set_bounce_mode);
//         // ADD_PROPERTY(PropertyInfo(Variant::INT, 
//         //         "bounce_mode",
//         //         PROPERTY_HINT_ENUM,
//         //         "Bounce,Warp"
//         //     ), 
//         //     "set_bounce_mode", "get_bounce_mode");
//         // ClassDB::bind_method(D_METHOD("get_bounce_count"), &Bullet::get_bounce_count);
//         // ClassDB::bind_method(D_METHOD("set_bounce_count", "p_bounce_count"), &Bullet::set_bounce_count);
//         // ADD_PROPERTY(PropertyInfo(Variant::INT, "bounce_count"), "set_bounce_count", "get_bounce_count");
//         // ClassDB::bind_method(D_METHOD("get_bounce_surfaces"), &Bullet::get_bounce_surfaces);
//         // ClassDB::bind_method(D_METHOD("set_bounce_surfaces", "p_bounce_surfaces"), &Bullet::set_bounce_surfaces);
//         // ADD_PROPERTY(PropertyInfo(Variant::INT, "bounce_surfaces"), "set_bounce_surfaces", "get_bounce_surfaces");
//         // ClassDB::bind_method(D_METHOD("get_wvel"), &Bullet::get_wvel);
//         // ClassDB::bind_method(D_METHOD("set_wvel", "p_wvel"), &Bullet::set_wvel);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "wvel"), "set_wvel", "get_wvel");
//         // ClassDB::bind_method(D_METHOD("get_max_wvel"), &Bullet::get_max_wvel);
//         // ClassDB::bind_method(D_METHOD("set_max_wvel", "p_max_wvel"), &Bullet::set_max_wvel);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_wvel"), "set_max_wvel", "get_max_wvel");
//         // ClassDB::bind_method(D_METHOD("get_waccel"), &Bullet::get_waccel);
//         // ClassDB::bind_method(D_METHOD("set_waccel", "p_waccel"), &Bullet::set_waccel);
//         // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "waccel"), "set_waccel", "get_waccel");
//     }
// }

