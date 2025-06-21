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


#ifndef COLLISION_BULLET_KIT_H
#define COLLISION_BULLET_KIT_H

#include <bullet_kit.hpp>																							

namespace godot {
class CollisionBulletKit : public BulletKit {
	GDCLASS(CollisionBulletKit, BulletKit)

    public:
	// Controls where the bullets can live, if a bullet exits this rect, it will be removed.
	Rect2 active_rect = Rect2();
	// The box for where the bullets bounce off of.
	Rect2 bounce_rect = Rect2();
	// The box for where the bullets warp to the other side of the screen.
	Rect2 warp_rect = Rect2();

	Rect2 get_active_rect();

	void set_active_rect(Rect2 value);

    protected:
    static void _bind_methods();

};

}


#endif