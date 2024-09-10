// MIT License
// 
// Copyright (c) 2021 Samuele Zolfanelli, 2024 Pickled Cow
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef BULLET_H
#define BULLET_H

#include <godot_cpp/classes/node2d.hpp>

namespace godot {

enum processMode { A1, A2, A3, B1, B2, B3 };
// enum bounceMode { BOUNCE, WARP };

struct BulletID {
	int cycle;
	int set;
    int index;

	BulletID(int cycle, int set, int index): 
		cycle(cycle), set(set), index(index) {}
};

// A basic bullet class. Holds onto information about the bullet that then a BulletKit is able to act upon.
class Bullet : public Object {
	GDCLASS(Bullet, Object)

    public:
    // ----------------------------------------
    // Critical internal varaibles. Can't be modified from Godot.
    // ----------------------------------------

    // Resource ID for the bullet sprite.
    RID item_rid;
    // The reuse count of the bullet. Used to check if the bullet has despawned and is being recycled.
    int cycle = 0;
    // The index of the bullet in the pool
    int pool_index = -1;
    // Mode of operation for which movement procedure to use
    processMode process_mode = A1;

    // ----------------------------------------
    // Internal varaibles. Can be modified from Godot but is highly discouraged.
    // ----------------------------------------

    // Transform of the bullet, also used for rendering
    Transform2D transform = Transform2D();
    // Normalised direction vector for faster computation.
    Vector2 direction = Vector2();
    // Order at which the bullet is drawn in among bullets with the same layer, lowest to highest.
    int draw_index = 0;
    // Internal flag for tracking if the bullet is currently fading
    bool fading = false;
    // Internal Array for keeping track of bullet transforms.
    Array patterns;
    // Internal data that is sent to the rendering shader.
    Color bullet_data;
    // For use with item autocollect.
	Node2D *magnet_target;  
	int magnet_id;


    // ----------------------------------------
    // User defined variables
    // ----------------------------------------

    // The center-to-edge length in in-game units to draw at,
    double scale = 16.0;
    // Ratio of the visual sprite and collision box.
    double hitbox_scale = 0.5;
    // The vertical offset of the bullet in texture pixels (positive moves sprite upwards).
    // Horizontal offset is unsupported
    double texture_offset = 0.0;
    // Layer at which to draw bullets in. Useful for example having larger bullets be drawn under smaller bullets by default.
    int layer = 0;
    // The color that fade effects should be shaded in. 
    Color fade_color = Color();
    // The position of the bullet in the playfield.
    Vector2 position = Vector2();
    // The sprite rotation offset compared to angle of travel, measured in radians.
    double rotation = 0.0;
    // Rate at which the bullet sprite should spin at, measured in radians per tick.
    double spin = 0.0;
    // How many ticks left of fade animation the bullet has left to complete.
    double fade_timer = 0.0;
    // How many frames of fade animation the bullet has in total. 
    // This variable and the one above can be both modified to have custom fade in time for individual bullets.
    double fade_time = 0.0;
    // Controls if the bullet fades out when it is destroyed.
    bool fade_delete = false;
    // Flag for if the bullet has already been grazed. TODO: Add graze time for multi graze
    bool grazed = false;
    // If true, automatically deletes the bullet if outside the playfield bounds.
    bool auto_delete = true;
    // How much damage the bullets should do. Mainly used for player bullets.
    double damage = 0.0;
    // Custom variable that can be used for elemental types for example.
    int damage_type = 0;
    // How many ticks the bullet has existed for in its current life.
    double lifetime = 0.0;
    // How many ticks the bullet can exist for before being deleted. By default infinite.
    double lifespan = INFINITY;
    // Whether or not to render the bullet upright. Is indifferent to orientation of other bullets on the spritesheet.
    bool upright = false;

    // ----------------------------------------
    // Exposed A1 movement type variables.
    // ----------------------------------------

    // The angle of the bullet.
    double angle = 0.0;
    // The speed the bullet travels in units per tick.
    double speed = 0.0;

    // ----------------------------------------
    // Exposed A2 movement type variables.
    // ----------------------------------------

    // Speed limit for accelerating bullets in units per tick.
    double max_speed = 0.0;
    // Acceleration of the bullet in units per tick per tick.
    double accel = 0.0;

    // ----------------------------------------
    // Exposed A3 movement type variables
    // ----------------------------------------

    // Behaviour for touching the wall
    int bounce_mode = 0;
    // Number of times left for bouncing. Most usecases should keep it at 0 or 1.
    int bounce_count = 0;
    // Stored as bit flags: right left down up from MSB to LSB
    int bounce_surfaces = 0; 
    // Rotation speed in radians per tick.
    double wvel = 0.0;
    // Rotation speed limit for gradual rotating bullets in radians per tick.
    double max_wvel = 0.0;
    // Rotational acceleration in radians per tick per tick.
    double waccel = 0.0;
    
    // ========================================
    //
    //      Functions
    //
    // ========================================

    void _init() {}
    
    // ----------------------------------------
    // Criticals
    // ----------------------------------------

    RID get_item_rid();
    void set_item_rid(RID value);
    
    int get_cycle();
    void set_cycle(int value);
    
    int get_pool_index();
    void set_pool_index(int value);
    
    int get_process_mode();
    void set_process_mode(int value);

    // ----------------------------------------
    // Getters
    // ----------------------------------------

    Node2D* get_magnet_target();
    int get_magnet_id();
    Transform2D get_transform();
    // Transform2D get_hitbox_transform();
    Vector2 get_direction();
    int get_draw_index();
    bool get_fading();
    Array get_patterns();
    Color get_bullet_data();
    double get_scale();
    double get_hitbox_scale();
    double get_texture_offset();
    int get_layer();
    Color get_fade_color();
    Vector2 get_position();
    double get_rotation();
    double get_spin();
    double get_fade_timer();
    double get_fade_time();
    bool get_fade_delete();
    bool get_grazed();
    bool get_auto_delete();
    double get_damage();
    int get_damage_type();
    double get_lifetime();
    double get_lifespan();
    bool get_upright();
    double get_angle();
    double get_speed();
    double get_max_speed();
    double get_accel();
    int get_bounce_mode();
    int get_bounce_count();
    int get_bounce_surfaces();
    double get_wvel();
    double get_max_wvel();
    double get_waccel();

    // ----------------------------------------
    // Setters
    // ----------------------------------------

    void set_magnet_target(Node2D* value);
    void set_magnet_id(int value);

    void set_transform(Transform2D value);
    // void set_hitbox_transform(Transform2D value);
    void set_direction(Vector2 value);
    void set_draw_index(int value);
    void set_fading(bool value);
    void set_patterns(Array value);
    void set_bullet_data(Color value);

    void set_scale(double value);
    void set_hitbox_scale(double value);
    void set_texture_offset(double value);
    void set_layer(int value);
    void set_fade_color(Color value);
    void set_position(Vector2 value);
    void set_rotation(double value);
    void set_spin(double value);
    void set_fade_timer(double value);
    void set_fade_time(double value);
    void set_fade_delete(bool value);
    void set_grazed(bool value);
    void set_auto_delete(bool value);
    void set_damage(double value);
    void set_damage_type(int value);
    void set_lifetime(double value);
    void set_lifespan(double value);
    void set_upright(bool value);

    void set_angle(double value);
    void set_speed(double value);

    void set_max_speed(double value);
    void set_accel(double value);
    
    void set_bounce_mode(int value);
    void set_bounce_count(int value);
    void set_bounce_surfaces(int value);
    void set_wvel(double value);
    void set_max_wvel(double value);
    void set_waccel(double value);

    protected:
    static void _bind_methods();

};
}

#endif