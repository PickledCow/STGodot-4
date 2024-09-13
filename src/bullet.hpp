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

// A stripped down reference to a Bullet mainly for use within Godot
struct BulletID {
	int cycle;
	int set;
    int index;

	BulletID(int cycle, int set, int index): 
		cycle(cycle), set(set), index(index) {}
};

// A basic bullet class. Holds onto information about the bullet that then a BulletKit is able to act upon.
// The base bullet is able to keep track of general rendering properties along with other critical behaviour
struct Bullet {

    public:
    // ----------------------------------------
    // Critical internal varaibles.
    // ----------------------------------------

    // Resource ID for the bullet sprite.
    RID item_rid;
    // The reuse count of the bullet. Used to check if the bullet has despawned and is being recycled.
    int cycle = 0;
    // The index of the bullet in the pool
    int pool_index = -1;
    // Transform of the bullet, also used for rendering
    Transform2D transform = Transform2D();
    // Normalised direction vector for faster computation.
    Vector2 direction = Vector2();
    // Order at which the bullet is drawn in among bullets with the same layer, lowest to highest.
    int draw_index = 0;
    // The position of the bullet in the playfield.
    Vector2 position = Vector2();
    // Internal flag for tracking if the bullet is currently fading
    bool fading = false;
    // The center-to-edge length in in-game units to draw at,
    double scale = 16.0;
    // Layer at which to draw bullets in. Useful for example having larger bullets be drawn under smaller bullets by default.
    int layer = 0;
    // How many ticks the bullet has existed for in its current life.
    double lifetime = 0.0;
    // How many ticks the bullet can exist for before being deleted. By default infinite.
    double lifespan = INFINITY;

    // Internal data that is sent to the rendering shader.
    Color bullet_data;

    // Mode of operation for which movement procedure to use
    processMode process_mode = A1;

    // The vertical offset of the bullet in texture pixels (positive moves sprite upwards).
    // Horizontal offset is unsupported
    double texture_offset = 0.0;
    // The color that fade effects should be shaded in. 
    Color fade_color = Color();
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
    // If true, automatically deletes the bullet if outside the playfield bounds.
    bool auto_delete = true;
    // Whether or not to render the bullet upright. Is indifferent to orientation of other bullets on the spritesheet.
    bool upright = false;

    // ----------------------------------------
    // Common movement variables
    // Also used for A1 BasicBullet movement type variables.
    // ----------------------------------------

    // The angle of the bullet.
    double angle = 0.0;
    // The speed the bullet travels in units per tick.
    double speed = 0.0;

    // How much damage the bullets should do. Mainly used for player bullets but also for item values.
    double damage = 0.0;
    // Custom variable that can be used for elemental types for example.
    int damage_type = 0;
};

struct BasicParticle : Bullet {

};


struct CollisionBullet : Bullet {
    // Ratio of the visual sprite and collision box.
    double hitbox_scale = 0.5;

    // Flag for if the bullet has already been grazed. TODO: Add graze time for multi graze
    bool grazed = false;

};


struct BasicBullet : CollisionBullet {
    // Internal Array for keeping track of bullet transforms.
    Array patterns;

    // ----------------------------------------
    // A2 movement type variables.
    // ----------------------------------------

    // Speed limit for accelerating bullets in units per tick.
    double max_speed = 0.0;
    // Acceleration of the bullet in units per tick per tick.
    double accel = 0.0;

    // ----------------------------------------
    // A3 movement type variables
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


};

struct BasicItem : CollisionBullet {
    // Flag for if the item is currently being magneted.
	bool magneted;
    // Reference to the target Node2D to get position off.
	Node2D *magnet_target;  

};

};


#endif