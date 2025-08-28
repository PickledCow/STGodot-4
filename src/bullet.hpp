// MIT License
// 
// Copyright (c) 2021 Samuele Zolfanelli, 2025 Pickled Cow
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in 
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
// DEALINGS IN THE SOFTWARE.

#ifndef BULLET_H
#define BULLET_H

#include <godot_cpp/classes/node2d.hpp>

namespace godot {

// Mode of process for BasicBullet. Higher number classes also run the process
// of lower types. A types act with angles and B types act with x-y velocities.
enum ProcessMode { A1, A2, A3, B1, B2, B3 };
enum BounceMode { BOUNCE, WARP };
// enum TransformTriggers {TRIGGER_TIME, TRIGGER_BOUNCE, TRIGGER_GRAZE};
// enum EnemyHitboxType { CIRCLE_HITBOX, RECT_HITBOX };

enum BULLET_ID_STRUCTURE {
    BULLET_ID_CYCLE,
    BULLET_ID_POOL,
    BULLET_ID_INDEX
};


const int NO_CHANGE = -256*256*256;

// A stripped down reference to a Bullet mainly for use within Godot.
struct BulletID {
	int cycle;
	int set;
    int index;

	BulletID(int cycle, int set, int index): 
		cycle(cycle), set(set), index(index) {}
};

struct AbstractPoolItem {
    // The reuse count of the enemy. Used to check if the enemy has despawned and is being recycled.
    int cycle = 0;
    // The index of the enemy in the pool. This value changes as its position in the pool is shuffled around.
    int pool_index = 0;
    // The initial index of the enemy in the pool. This value does not change if the enemy changes positions in the pool.
    int persistent_index = -1;

    // Position of the enemy in the world.
    Vector2 position = Vector2();
};

// A super basic struct for the enemy hitbox and damage reports.
// Automatically tracks damage taken the current frame
struct Enemy : AbstractPoolItem {
    // Size of the hitbox (enemy gets hurt).
    double hitbox_size = 16.0;
    // Size of the hurtbox (player gets hurt).
    double hurtbox_size = 8.0;
    // If the bullet should delete non-piercing bullets
    bool deletes_bullets = true;
    // Marked for deleting next frame.
    bool queue_delete = false;
    
    // The list of bullets collided with.
    Array collided_bullets;
    // List of bullets collided with in its lifetime to keep track of pierce.
    Array lifetime_collided_bullets;
};

// A basic bullet struct. Holds onto information about the bullet that then a 
// corresponding BulletKit is able to act upon.
// The base bullet is able to keep track of general rendering properties along 
// with other critical behaviour.
struct AbstractBullet : AbstractPoolItem {
    // ----------------------------------------
    // Critical internal varaibles.  No setter/getter is provided for these.
    // ----------------------------------------

    // Resource ID for the bullet sprite.
    RID item_rid;
    // Order at which the bullet is drawn in among bullets with the same layer, lowest to highest.
    int draw_index = 0;
    // Transform of the bullet, also used for rendering
    Transform2D transform = Transform2D();
    // // Flag for tracking if the bullet is currently fading.
    // bool fading = false;
    // Flag for if using the additive material variant to skip changing materials if no need
    bool additive = false;

    // ----------------------------------------
    // Regular variables. These can be freely set.
    // ----------------------------------------
    
    // Normalised direction vector for faster computation.
    Vector2 direction = Vector2();
    // The position of the bullet in the playfield.
    Vector2 position = Vector2();
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

    // The vertical offset of the bullet in texture pixels (positive moves sprite upwards).
    // Horizontal offset is unsupported and should be aligned within the spritesheet as there is no space left in the shader data structure.
    double texture_offset = 0.0;
    // Variable for holding color data. Intended to be used for creating bullet clear effects but can be used in other ways.
    Color fade_color = Color();
    // The sprite rotation offset compared to angle of travel, measured in radians.
    double rotation = 0.0;
    // Rate at which the bullet sprite should spin at, measured in radians per tick.
    double spin = 0.0;
    // How many ticks left of fade animation the bullet has left to complete.
    double fade_timer = 0.0;
    // How many frames of fade animation the bullet has in total.
    double fade_time = 0.0;
    // // Flag for if the bullet is fading out, the bullet is not deleted until it fades out but does not have collision.
    // bool fading_out = false;
    // Controls if the bullet fades out when it is destroyed.
    bool fade_delete = false;
    // If true, automatically deletes the bullet if outside the playfield bounds.
    bool auto_delete = true;
    // Whether or not to render the bullet upright. Also disables kit rotation settings.
    bool is_upright = false;

    // ----------------------------------------
    // Common movement variables
    // ----------------------------------------

    // The angle of the bullet.
    double angle = 0.0;
    // The speed the bullet travels in units per tick.
    double speed = 0.0;

    // How much damage the bullets should do. Mainly used for player bullets but also for item values.
    double damage = 0.0;
    // Custom variable that can be used for elemental types for example.
    int damage_type = 0;

    // Additional custom data if the bullet needs to hold further information.
    Variant custom_data;
};

struct Particle : AbstractBullet {

};

// Abstract struct that bullets with collision inherit from
struct CollisionBullet : AbstractBullet {
    // Ratio of the visual sprite and collision box.
    double hitbox_scale = 0.5;

    // Flag for if the bullet has already been grazed. TODO: Add graze time for multi graze
    bool is_grazed = false;

};

// Basic bullet for general purpose use
struct Bullet : CollisionBullet {
    // Mode of operation for which movement procedure to use
    ProcessMode process_mode = A1;

    // Internal Array for keeping track of bullet transforms.
    Array transforms;



    // ----------------------------------------
    // A2 movement type variables.
    // ----------------------------------------

    // Speed limit for accelerating bullets in units per tick.
    double max_speed = 0.0;
    // Acceleration of the bullet in units per tick per tick.
    double accel = 0.0;

    // ----------------------------------------
    // A3 movement type variables. These are set through external functions and
    // does not have a corresponding create_shot_Ax function.
    // ----------------------------------------

    // Determines if the shot is marked for deletion on contact with enemy, used for piercing shots.
    bool pierce = false;
    // Behaviour for touching the wall
    int bounce_mode = 0;
    // Number of times left for bouncing. Most usecases should keep it at 0 or 1.
    int bounce_count = 0;
    // Stored as bit flags: right left down up from MSB to LSB
    int bounce_surfaces = 0; 
    // Rotation speed in radians per tick.
    double wvel = 0.0;
    // Rotational acceleration in radians per tick per tick.
    double waccel = 0.0;
    // Rotation speed limit for gradual rotating bullets in radians per tick.
    double max_wvel = 0.0;

    // ----------------------------------------
    // B1 movement type variables.
    // ----------------------------------------

    Vector2 b_accel;
    Vector2 b_max_velocity;
    bool rotation_follows_movement;

};

// Lasers, behave similarly to bullets mostly but have different collision
struct Laser : Bullet {
    // How long the laser is.
    double length;
    // The width of the laser
    double width;
    // How much of the length is actually damaging.
    double start_margin = 0.5;
    double end_margin = 0.5;
    // If the laser is flipped or not. Straight lasers have their position at the start rather than their tip.
    bool flipped = false;

    // Resource ID for the spawn sprite.
    RID spawn_item_rid;
    // Transfomr for the spawn sprite.
    Transform2D spawn_transform;
};

// Curve lasers, behave too differently from regular lasers to extend off them. 
// The item_rid of curve lasers are used for the spawn laser instead
struct CurveLaser: Bullet {
    // // RID of the rendered mesh
    // RID mesh_rid;
    // Starting position for the spawn glow
    Vector2 start_position;
    // How long the laser is in frames
    int length;
    // The width of the laser
    double width;
    // The list of points on the laser.
    PackedVector2Array points = PackedVector2Array();
    // List of vertices of the laser mesh.
    PackedVector2Array vertices = PackedVector2Array();
    // List of UVs of the laser mesh. If timescale is 1.0, these values do not need to change.
    PackedVector2Array uvs = PackedVector2Array();
    // List of CUSTOM0 data for shader use, doesn't ever change keep around.
    PackedFloat32Array custom0s = PackedFloat32Array();
    // Used to keep track of what fraction of a frame we are off to adjust moving the UVs by to compensate.
    double timestep_fraction;
    // The first node that has collision.
    int collision_start_node_index;
    // The last node that has collision, exclusive.
    int collision_end_node_index;
    // The start of the texture mesh for when the laser is cut.
    int mesh_start_node_index;
    // The end of the texture mesh for when the laser is cut.
    int mesh_end_node_index;
    // The start tip collision margin. used when resizing the laser from a cut
    int start_margin;
    // The end tip collision margin. used when resizing the laser from a cut
    int end_margin;

    PackedFloat64Array laser_data_copy;

    // // Resource ID for the spawn sprite.
    // RID spawn_item_rid;
    // Transfomr for the spawn sprite.
    Transform2D spawn_transform;
};

// 
struct Item : CollisionBullet {
    // Flag for if the item is currently being magneted.
	bool is_magneted;
    // Flag for if the item was autocollected
	bool is_auto_collected;
    // Reference to the target Node2D to get position off.
	Node2D *magnet_target;  

};

};

#endif