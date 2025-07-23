#include <cstdlib>

#include <bullet_pool.hpp>

using namespace godot;

template <class BulletType>
Vector2 AbstractPool<BulletType>::get_position(BulletID id) {
    BulletType bullet = pool[persistent_index[id[BULLET_ID_INDEX]]];
    if (bullet->cycle == id[BULLET_ID_CYCLE]) return bullet->position;
    return Vector2();
}

template <class BulletType>
void AbstractPool<BulletType>::set_position(BulletID id, Vector2 position) {
    BulletType bullet = pool[persistent_index[id[BULLET_ID_INDEX]]];
    if (bullet->cycle == id[BULLET_ID_CYCLE]) bullet->position = position;
}