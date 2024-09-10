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


#ifndef BULLET_POOL_H
#define BULLET_POOL_H

#include <bullet.hpp>
// #include <bullet_kit.hpp>
#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/rendering_server.hpp>

namespace godot {

class BulletKit;

class BulletPool {
    
    public:
	int pool_size = 0;
	int set_index = -1;

	BulletPool();
	virtual ~BulletPool();

	virtual void _init(CanvasItem* canvas_parent, 
		int set_index, Ref<BulletKit> kit, int pool_size, int z_index, Vector2 origin) = 0;
	
	int get_available_bullets();
	int get_active_bullets();

	virtual int _process(double delta) = 0;

	virtual void spawn_bullet(Dictionary properties) = 0;
	virtual BulletID obtain_bullet() = 0;
	virtual bool release_bullet(BulletID id) = 0;
	virtual bool is_bullet_valid(BulletID id) = 0;

	virtual bool is_bullet_existing(int shape_index) = 0;

	virtual void set_bullet_property(BulletID id, String property, Variant value) = 0;
	virtual Variant get_bullet_property(BulletID id, String property) = 0;
    
	virtual int collide_and_graze(Vector2 pos, double hitbox_radius, double graze_radius) = 0;

    void do_nothing() {pool_size++;};

    protected:

	int available_bullets = 0;
	int active_bullets = 0;
	int bullets_to_handle = 0;

	CanvasItem* canvas_parent;
	RID canvas_item;
	// RID shared_area;
	// int starting_shape_index;

	Rect2 active_rect;
	Rect2 bounce_rect;
	Rect2 warp_rect;
    float rotation_offset;

    RenderingServer* rendering_server;
    PhysicsServer2D* physics_server;

	template<typename T>
	void _swap(T &a, T &b) {
		T t = a;
		a = b;
		b = t;
	}

	int draw_index = 0;
};

template <class Kit, class BulletType>
class AbstractBulletPool : public BulletPool {

    public:
	AbstractBulletPool() {}
	virtual ~AbstractBulletPool();

	virtual void _init(CanvasItem* canvas_parent, 
		int set_index, Ref<BulletKit> kit, int pool_size, int z_index, Vector2 origin) override;

	virtual int _process(double delta) override;
    

    
	virtual int collide_and_graze(Vector2 pos, double hitbox_radius, double graze_radius) override;

	virtual void spawn_bullet(Dictionary properties) override;
	virtual BulletID obtain_bullet() override;
	virtual bool release_bullet(BulletID id) override;
	virtual bool is_bullet_valid(BulletID id) override;

	virtual bool is_bullet_existing(int shape_index) override;

	virtual void set_bullet_property(BulletID id, String property, Variant value) override;
	virtual Variant get_bullet_property(BulletID id, String property) override;

    protected:
	Ref<Kit> kit;
	BulletType** bullets = nullptr;

	virtual inline void _init_bullet(BulletType* bullet);
	virtual inline void _enable_bullet(BulletType* bullet);

	virtual inline void _disable_bullet(BulletType* bullet);
	virtual inline bool _process_bullet(BulletType* bullet, double delta);
	// virtual inline void _process_A1(BulletType* bullet, double delta) override;
	// virtual inline void _process_A2(BulletType* bullet, double delta) override;
	// virtual inline void _process_A3(BulletType* bullet, double delta, double rotation_offset, Rect2 bounce_rect, Rect2 warp_rect) override;

	inline void _release_bullet(int index);
};

}

#include "bullet_pool.inl"

#endif