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


#ifndef BULLET_KIT_H
#define BULLET_KIT_H

// #include <memory>

// #include <bullet.hpp>
#include <bullet_pool.hpp>

#include <godot_cpp/classes/shape2d.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/material.hpp>																								

namespace godot {

class BulletPool; 

class BulletKit : public Resource {
	GDCLASS(BulletKit, Resource)

    public:

	// Internal only
	double rotation_offset = Math_PI * 0.5;		

    // std::unique_ptr<BulletPool> _create_pool();

	// Public to Godot

	// The spritesheet used to render each bullet.
	Ref<Texture2D> texture;
	// The material used to render each bullet.
	Ref<Material> material;
    // Width of the texture sheet in pixels.
	double texture_width = 0.0;
	// Flag for if the bullets face upwards (true) or right (false)
	bool facing_up = true;
	// Time it takes for bullets and items to fully fade in
	double fade_time = 8.0;
	// // Which layer(s) bullets from this kit are of. In most cases only one should be active.
	// int collision_layer = 0;
	
	// // Controls where the bullets can live, if a bullet exits this rect, it will be removed.
	// Rect2 active_rect = Rect2();
	// // The box for where the bullets bounce off of.
	// Rect2 bounce_rect = Rect2();
	// // The box for where the bullets warp to the other side of the screen.
	// Rect2 warp_rect = Rect2();
	// The scale at which physics operates at for this kit. Useful for slowdown effect.
	double time_scale = 1.0;

	void _init() {}

	// void _property_setter(String value) {}
	// String _property_getter() { return ""; }

	Ref<Texture2D> get_texture();
	Ref<Material> get_material();
	double get_texture_width();
	bool get_facing_up();
	double get_fade_time();
	double get_time_scale();
    
	void set_texture(Ref<Texture2D> value);
	void set_material(Ref<Material> value);
	void set_texture_width(double value);
	void set_facing_up(bool value);
	void set_fade_time(double value);
	
	void set_time_scale(double value);

	
	virtual bool is_valid() { return material.is_valid(); }
	virtual std::unique_ptr<BulletPool> _create_pool() { return std::unique_ptr<BulletPool>(); };

    protected:
    static void _bind_methods();
};


}


#endif