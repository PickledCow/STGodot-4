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


// I'm not gonna lie, I have no clue what's going on in this 

#include <godot_cpp/variant/utility_functions.hpp>
#include <bullet_pool.hpp>


namespace godot {
    
//-- START Default "standard" implementations.

template <class Kit, class BulletType>
void AbstractBulletPool<Kit, BulletType>::_init_bullet(BulletType* bullet) {}

template <class Kit, class BulletType>
void AbstractBulletPool<Kit, BulletType>::_enable_bullet(BulletType* bullet) {
	bullet->lifetime = 0.0;

	Rect2 texture_rect = Rect2(-0.5f, -0.5f, 1.0, 1.0);
	RID texture_rid = kit->texture->get_rid();
	
	rendering_server->canvas_item_add_texture_rect(bullet->item_rid,
		texture_rect,
		texture_rid);
}

template <class Kit, class BulletType>
void AbstractBulletPool<Kit, BulletType>::_disable_bullet(BulletType* bullet) {
	rendering_server->canvas_item_clear(bullet->item_rid);
}

template <class Kit, class BulletType>
bool AbstractBulletPool<Kit, BulletType>::_process_bullet(BulletType* bullet, double delta) {
    
    // if (bullet->process_mode < B1) {
    //     if (bullet->process_mode >= A2) _process_A2(bullet, delta);
    //     if (bullet->process_mode == A3) _process_A3(bullet, delta, rotation_offset, bounce_rect, warp_rect);

    //     _process_A1(bullet, delta);
    // }

	// if(!active_rect.has_point(bullet->transform.get_origin())) {
	// 	return true;
	// }

	bullet->lifetime += delta;
	return false;
}

//-- END Default "standard" implementation.


template <class Kit, class BulletType>
AbstractBulletPool<Kit, BulletType>::~AbstractBulletPool() {
	// Bullets node is responsible for clearing all the area and area shapes
	for(int i = 0; i < pool_size; i++) {
		rendering_server->free_rid(bullets[i]->item_rid);
        // TODO: MEMORY LEAK, TOO BAD
		//bullets[i]->free();
	}
	rendering_server->free_rid(canvas_item);

	delete[] bullets;
}

template <class Kit, class BulletType>
void AbstractBulletPool<Kit, BulletType>::_init(CanvasItem* canvas_parent, 
		int set_index, Ref<BulletKit> kit, int pool_size, int z_index, Vector2 origin) {
	
	// Check if collisions are enabled and if layer or mask are != 0, 
	// otherwise the bullets would not collide with anything anyways.
	this->canvas_parent = canvas_parent;
	this->kit = kit;
	this->pool_size = pool_size;
	this->set_index = set_index;

	available_bullets = pool_size;
	active_bullets = 0;

	bullets = new BulletType*[pool_size];

	rendering_server = RenderingServer::get_singleton();
	// physics_server = PhysicsServer2D::get_singleton();

	canvas_item = rendering_server->canvas_item_create();
	rendering_server->canvas_item_set_parent(canvas_item, canvas_parent->get_canvas_item());
	rendering_server->canvas_item_set_z_index(canvas_item, z_index);

	Transform2D xform = Transform2D(0.0, origin);

	for(int i = 0; i < pool_size; i++) {
		BulletType* bullet = memnew(BulletType());
		
		bullets[i] = bullet;
		bullet->item_rid = rendering_server->canvas_item_create();
		rendering_server->canvas_item_set_parent(bullet->item_rid, canvas_item);
		rendering_server->canvas_item_set_material(bullet->item_rid, kit->material->get_rid());


		Color color = Color(1.0, 1.0, 1.0, 0.0);
		rendering_server->canvas_item_set_modulate(bullet->item_rid, color);

		bullet->pool_index = i;

		_init_bullet(bullet);

    }
}

template <class Kit, class BulletType>
int AbstractBulletPool<Kit, BulletType>::_process(double delta) {
	active_rect = kit->active_rect;
	bounce_rect = kit->bounce_rect;
	warp_rect = kit->warp_rect;
    rotation_offset = kit->rotation_offset;

	int amount_variation = 0;

	for(int i = pool_size - 1; i >= available_bullets; i--) {
		BulletType* bullet = bullets[i];

		if(_process_bullet(bullet, delta)) {
			_release_bullet(i);
			amount_variation -= 1;
			i += 1;
			continue;
		}
		
		rendering_server->canvas_item_set_transform(bullet->item_rid, bullet->transform);
	}
	return amount_variation;
}




template <class Kit, class BulletType>
void AbstractBulletPool<Kit, BulletType>::spawn_bullet(Dictionary properties) {
	if(available_bullets > 0) {
		available_bullets -= 1;
		active_bullets += 1;

		BulletType* bullet = bullets[available_bullets];

		Array keys = properties.keys();
		for(int i = 0; i < keys.size(); i++) {
			bullet->set(keys[i], properties[keys[i]]);
		}

		rendering_server->canvas_item_set_transform(bullet->item_rid, bullet->transform);

		_enable_bullet(bullet);
	}
}

template <class Kit, class BulletType>
BulletID AbstractBulletPool<Kit, BulletType>::obtain_bullet() {
	if(available_bullets > 0) {
		available_bullets -= 1;
		active_bullets += 1;

		BulletType* bullet = bullets[available_bullets];

		rendering_server->canvas_item_set_draw_index(bullet->item_rid, (draw_index++));
		bullet->draw_index = draw_index++;
		if (draw_index > 16777215) draw_index = 0; // 2^24
		
		_enable_bullet(bullet);

		return BulletID(bullet->cycle, set_index, bullet->pool_index);
	}
	return BulletID(-1, -1, -1);
}

// TODO: Add a failsafe 
template <class Kit, class BulletType>
bool AbstractBulletPool<Kit, BulletType>::release_bullet(BulletID id) {
	// if(id.index >= starting_shape_index && id.index < starting_shape_index + pool_size && id.set == set_index) {
	// 	int bullet_index = shapes_to_indices[id.index - starting_shape_index];
	// 	if(bullet_index >= available_bullets && bullet_index < pool_size && id.cycle == bullets[bullet_index]->cycle) {
	// 		_release_bullet(bullet_index);
	// 		return true;
	// 	}
	// }

	int bullet_index = id.index;
	_release_bullet(bullet_index);
	return true;

	return false;
}

template <class Kit, class BulletType>
void AbstractBulletPool<Kit, BulletType>::_release_bullet(int index) {
	BulletType* bullet = bullets[index];

	_disable_bullet(bullet);
	bullet->cycle += 1;

	// _swap(shapes_to_indices[bullet->shape_index - starting_shape_index], shapes_to_indices[bullets[available_bullets]->shape_index - starting_shape_index]);
	_swap(bullets[index], bullets[available_bullets]);
	_swap(bullets[index]->pool_index, bullets[available_bullets]->pool_index);

	available_bullets += 1;
	active_bullets -= 1;
}

template <class Kit, class BulletType>
bool AbstractBulletPool<Kit, BulletType>::is_bullet_valid(BulletID id) {
	if (id.index >= 0) { //  && id.index < available_bullets
		return bullets[id.index]->cycle == id.cycle;
	}
	return false;
}


template <class Kit, class BulletType>
bool AbstractBulletPool<Kit, BulletType>::is_bullet_existing(int index) {
	if (index >= 0 && index < available_bullets) {
		return true;
	}
	return false;
}


template <class Kit, class BulletType>
int AbstractBulletPool<Kit, BulletType>::collide_and_graze(Vector2 pos, double hitbox_radius, double graze_radius) {
	int graze_count = 0;

	double hitbox_radius_squared = hitbox_radius * hitbox_radius;
	double graze_radius_squared = graze_radius * graze_radius;

	for (int i = pool_size - 1; i >= available_bullets; i--) {
		BulletType* bullet = bullets[i];

		double b = bullet->scale * bullet->hitbox_scale;
		double b2 = b * b;

	 	double dist_sq = (bullet->position - pos).length_squared();
		
		if (bullet->fade_timer <= 0.0 && dist_sq <= graze_radius_squared + 2.0 * graze_radius * b + b2) {
			if (!bullets[i]->grazed) {
				bullets[i]->grazed = true;
				graze_count++;
			}

			if (dist_sq <= hitbox_radius_squared + 2.0 * hitbox_radius * b + b2) {
				bullets[i]->lifespan = -INFINITY;
				// _release_bullet(i);
				// amount_variation -= 1;
				// i += 1;
				// continue;
			}
		}
	}
	return graze_count;
}



// TODO
template <class Kit, class BulletType>
void AbstractBulletPool<Kit, BulletType>::set_bullet_property(BulletID id, String property, Variant value) {
	
	// UtilityFunctions::print(id.cycle);
	// UtilityFunctions::print(id.index);
	// UtilityFunctions::print(bullets[id.index]->cycle);


	if(is_bullet_valid(id)) {
		// int bullet_index = shapes_to_indices[id.index - starting_shape_index];
		// bullets[bullet_index]->set(property, value);
		int bullet_index = id.index;
		bullets[bullet_index]->set(property, value);

		// Additional operations

		switch (property.hash()) { // find a better way to do this 
			case (596893057): { // transform
				BulletType* bullet = bullets[bullet_index];
				rendering_server->canvas_item_set_transform(bullet->item_rid, bullet->transform);
				Transform2D xform = bullet->transform;
				Vector2 origin = xform.get_origin();
				bullets[bullet_index]->set("position", origin);
				break;
			}
			case (1290762938): { // position
				BulletType* bullet = bullets[bullet_index];
				Transform2D xform = get_bullet_property(id, "transform");
				xform.set_origin((Vector2)value);
				set_bullet_property(id, "transform", xform);
				break;
			}
			case (657950997): { // rotation
				BulletType* bullet = bullets[bullet_index];
				Transform2D xform = get_bullet_property(id, "transform");
				Vector2 origin = xform.get_origin();
				xform = xform.rotated(bullet->angle - xform.get_rotation() + 1.57079632679f + (double)value);
				xform.set_origin(origin);
				set_bullet_property(id, "transform", xform);
				break;
			}
			case (253255468): { // angle
				BulletType* bullet = bullets[bullet_index];
				Transform2D xform = get_bullet_property(id, "transform");
				Vector2 origin = xform.get_origin();
				xform = xform.rotated((double)value - xform.get_rotation() + 1.57079632679f + bullet->rotation);
				xform.set_origin(origin);
				set_bullet_property(id, "transform", xform);
				set_bullet_property(id, "direction", Vector2(1.0, 0.0).rotated((double)value));
				break;
			}
			case (373355782): { // bullet_data
				BulletType* bullet = bullets[bullet_index];
				Color color = bullet->bullet_data;
				rendering_server->canvas_item_set_modulate(bullet->item_rid, color);
				break;
			}
			case (265852802): { // layer
				BulletType* bullet = bullets[bullet_index];
				rendering_server->canvas_item_set_draw_index(bullet->item_rid, (bullet->layer << 24) + bullet->draw_index);
				break;
			}
			case (274200205): { // scale
				BulletType* bullet = bullets[bullet_index];
				Transform2D xform = get_bullet_property(id, "transform");
				Vector2 origin = xform.get_origin();
				xform = xform.scaled((bullet->scale / xform.get_scale().x) * Vector2(1.0, 1.0));
				xform.set_origin(origin);
				set_bullet_property(id, "transform", xform);
				break;
			}
			default:
				break;
		}
	}
}

// TODO
template <class Kit, class BulletType>
Variant AbstractBulletPool<Kit, BulletType>::get_bullet_property(BulletID id, String property) {
	if(is_bullet_valid(id)) {
		int bullet_index = id.index;

		return bullets[bullet_index]->get(property);
	}
	return Variant();
}





}
