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

#ifndef BULLET_POOL_H
#define BULLET_POOL_H

#include <bullet.hpp>

namespace godot {

// Abstract pool for the other pools to base themseles off

class BasePool {
    public:

    int* persistent_index;

    virtual Vector2 get_position(BulletID id) = 0;
    virtual void set_position(BulletID id, Vector2 position) = 0;
};


template <class BulletType>
class AbstractPool : BasePool {
    public:

    BulletType** pool;

    virtual Vector2 get_position(BulletID id) override;
    virtual void set_position(BulletID id, Vector2 position) override;

};

class EnemyPool : AbstractPool<Enemy> {

    Vector2 get_position(BulletID id) = 0;
    void set_position(BulletID id, Vector2 position) = 0;

};

class BulletPool : AbstractPool<Bullet> {

};




}
#endif