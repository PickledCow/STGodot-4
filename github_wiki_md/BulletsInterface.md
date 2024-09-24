### **Inherits:** [Node2D](https://docs.godotengine.org/en/stable/classes/class_node2d.html)
**An interface between Godot and the STGodot GDExtension module.**
## Description
An interface between Godot and the STGodot GDExtension module. BulletsInterface exposes methods for creating, manipulating, and interacting with bullets.
## Properties
|Type|Name|Default Value|
|-|-|-|
|[int](https://docs.godotengine.org/en/stable/classes/class_int.html) | [NO_CHANGE](#int-NO_CHANGE) |`-16777216`|
## Methods
|Return Type|Name|
|-|-|
|[Array](https://docs.godotengine.org/en/stable/classes/class_array.html)|[collect_and_magnet](#array-collect_and_magnetitem_kit-basicitemkit-target_node-vector2-position-node2d-collection_radius-float-magnet_radius-float)(item_kit: [BasicItemKit](https://github.com/PickledCow/STGodot-4/wiki/BasicItemKit), target_node: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html), position: [Node2D](https://docs.godotengine.org/en/stable/classes/class_node2d.html), collection_radius: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), magnet_radius: [float](https://docs.godotengine.org/en/stable/classes/class_float.html))|
|[Array](https://docs.godotengine.org/en/stable/classes/class_array.html)|[collide_and_graze](#array-collide_and_grazebullet_kit-basicbulletkit-position-vector2-hitbox_radius-float-graze_radius-float)(bullet_kit: [BasicBulletKit](https://github.com/PickledCow/STGodot-4/wiki/BasicBulletKit), position: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html), hitbox_radius: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), graze_radius: [float](https://docs.godotengine.org/en/stable/classes/class_float.html))|
|[PackedInt64Array](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html)|[create_item](#packedint64array-create_itemitem_kit-basicitemkit-position-vector2-speed-float-angle-float-spin-float-item_data-packedfloat64array)(item_kit: [BasicItemKit](https://github.com/PickledCow/STGodot-4/wiki/BasicItemKit), position: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html), speed: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), angle: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), spin: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), item_data: [PackedFloat64Array](https://docs.godotengine.org/en/stable/classes/class_packedfloat64array.html))|
|[PackedInt64Array](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html)|[create_particle](#packedint64array-create_particleparticle_kit-basicparticlekit-position-vector2-drift-vector2-rotation-float-size-float-color-color)(particle_kit: [BasicParticleKit](https://github.com/PickledCow/STGodot-4/wiki/BasicParticleKit), position: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html), drift: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html), rotation: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), size: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), color: [Color](https://docs.godotengine.org/en/stable/classes/class_color.html))|
|[PackedInt64Array](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html)|[create_shot_a1](#packedint64array-create_shot_a1bullet_kit-basicbulletkit-position-vector2-speed-float-angle-float-bullet_data-packedfloat64array-fade-bool)(bullet_kit: [BasicBulletKit](https://github.com/PickledCow/STGodot-4/wiki/BasicBulletKit), position: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html), speed: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), angle: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), bullet_data: [PackedFloat64Array](https://docs.godotengine.org/en/stable/classes/class_packedfloat64array.html), fade: [bool](https://docs.godotengine.org/en/stable/classes/class_bool.html))|
|[PackedInt64Array](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html)|[create_shot_a2](#packedint64array-create_shot_a2bullet_kit-basicbulletkit-position-vector2-speed-float-angle-float-accel-float-max_speed-float-bullet_data-packedfloat64array-fade-bool)(bullet_kit: [BasicBulletKit](https://github.com/PickledCow/STGodot-4/wiki/BasicBulletKit), position: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html), speed: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), angle: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), accel: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), max_speed: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), bullet_data: [PackedFloat64Array](https://docs.godotengine.org/en/stable/classes/class_packedfloat64array.html), fade: [bool](https://docs.godotengine.org/en/stable/classes/class_bool.html))|
|[Node](https://docs.godotengine.org/en/stable/classes/class_node.html)|[get_bullets_environment](#node-get_bullets_environment)()|
|[float](https://docs.godotengine.org/en/stable/classes/class_float.html)|[get_damage](#float-get_damageid-packedint64array)(id: [PackedInt64Array](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html))|
|[bool](https://docs.godotengine.org/en/stable/classes/class_bool.html)|[get_is_auto_collected](#bool-get_is_auto_collecteditem_id-packedint64array)(item_id: [PackedInt64Array](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html))|
|[Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html)|[get_position](#vector2-get_positionid-packedint64array)(id: [PackedInt64Array](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html))|
|[int](https://docs.godotengine.org/en/stable/classes/class_int.html)|[get_total_active_bullets](#int-get_total_active_bullets)()|
|void|[magnet_all](#void-magnet_allitem_kit-basicitemkit-target_node-node2d)(item_kit: [BasicItemKit](https://github.com/PickledCow/STGodot-4/wiki/BasicItemKit), target_node: [Node2D](https://docs.godotengine.org/en/stable/classes/class_node2d.html))|
|void|[mount](#void-mountbullets_environment-node)(bullets_environment: [Node](https://docs.godotengine.org/en/stable/classes/class_node.html))|
|void|[set_damage](#void-set_damageid-packedint64array-damage-float)(id: [PackedInt64Array](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html), damage: [float](https://docs.godotengine.org/en/stable/classes/class_float.html))|
|void|[set_position](#void-set_positionid-packedint64array-position-vector2)(id: [PackedInt64Array](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html), position: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html))|
|void|[unmount](#void-unmount_unnamed_arg0-node)(_unnamed_arg0: [Node](https://docs.godotengine.org/en/stable/classes/class_node.html))|
---
## Property Descriptions
### [`int`](https://docs.godotengine.org/en/stable/classes/class_int.html) `NO_CHANGE`
Value for bullet transform functions to tell the BulletsInterface to not modify this parameter.
## Method Descriptions
### [`Array`](https://docs.godotengine.org/en/stable/classes/class_array.html) <tt>collect_and_magnet(item_kit: [BasicItemKit](https://github.com/PickledCow/STGodot-4/wiki/BasicItemKit), target_node: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html), position: [Node2D](https://docs.godotengine.org/en/stable/classes/class_node2d.html), collection_radius: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), magnet_radius: [float](https://docs.godotengine.org/en/stable/classes/class_float.html))</tt>  
Marks items within the collection_radius as collected and marks items within the magnet_radius as "magnetised" to the given target node.
The list of the two are returned in an [Array](https://docs.godotengine.org/en/stable/classes/class_array.html) in the structure `[ [List of collected items], [List of magnetised items] ]`
Magnetised bullets move directly towards the target node each tick.


---
### [`Array`](https://docs.godotengine.org/en/stable/classes/class_array.html) <tt>collide_and_graze(bullet_kit: [BasicBulletKit](https://github.com/PickledCow/STGodot-4/wiki/BasicBulletKit), position: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html), hitbox_radius: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), graze_radius: [float](https://docs.godotengine.org/en/stable/classes/class_float.html))</tt>  
Marks bullets within the hitbox_radius as collided and marks bullets within the graze_radius as grazed.
The list of the two are returned in an Array in the structure `[ [List of collided bullets], [List of grazed bullets] ]`


---
### [`PackedInt64Array`](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html) <tt>create_item(item_kit: [BasicItemKit](https://github.com/PickledCow/STGodot-4/wiki/BasicItemKit), position: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html), speed: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), angle: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), spin: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), item_data: [PackedFloat64Array](https://docs.godotengine.org/en/stable/classes/class_packedfloat64array.html))</tt>  
Creates an item according to the provided specifications.
Only accepts [BasicItemKits](https://github.com/PickledCow/STGodot-4/wiki/BasicItemKit).


---
### [`PackedInt64Array`](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html) <tt>create_particle(particle_kit: [BasicParticleKit](https://github.com/PickledCow/STGodot-4/wiki/BasicParticleKit), position: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html), drift: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html), rotation: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), size: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), color: [Color](https://docs.godotengine.org/en/stable/classes/class_color.html))</tt>  
Creates a particle according to the provided specifications.


---
### [`PackedInt64Array`](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html) <tt>create_shot_a1(bullet_kit: [BasicBulletKit](https://github.com/PickledCow/STGodot-4/wiki/BasicBulletKit), position: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html), speed: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), angle: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), bullet_data: [PackedFloat64Array](https://docs.godotengine.org/en/stable/classes/class_packedfloat64array.html), fade: [bool](https://docs.godotengine.org/en/stable/classes/class_bool.html))</tt>  
Creates a bullet according to the provided specifications.
`A1` type bullets are the most basic with barebones functionality. Automatically converts to higher types if properties of those types are set.
Only accepts [BasicBulletKits](https://github.com/PickledCow/STGodot-4/wiki/BasicBulletKit).


---
### [`PackedInt64Array`](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html) <tt>create_shot_a2(bullet_kit: [BasicBulletKit](https://github.com/PickledCow/STGodot-4/wiki/BasicBulletKit), position: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html), speed: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), angle: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), accel: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), max_speed: [float](https://docs.godotengine.org/en/stable/classes/class_float.html), bullet_data: [PackedFloat64Array](https://docs.godotengine.org/en/stable/classes/class_packedfloat64array.html), fade: [bool](https://docs.godotengine.org/en/stable/classes/class_bool.html))</tt>  
Creates a bullet according to the provided specifications.
`A2` type bullets add onto `A1` type bullets some additional common functionality. Automatically converts to higher types if properties of those types are set.
Only accepts [BasicBulletKits](https://github.com/PickledCow/STGodot-4/wiki/BasicBulletKit).


---
### [`Node`](https://docs.godotengine.org/en/stable/classes/class_node.html) <tt>get_bullets_environment()</tt>  
Returns the current active BulletsEnvironment Node.


---
### [`float`](https://docs.godotengine.org/en/stable/classes/class_float.html) <tt>get_damage(id: [PackedInt64Array](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html))</tt>  
Returns the `damage` property of the bullet. 
Accepts any type of bullet.


---
### [`bool`](https://docs.godotengine.org/en/stable/classes/class_bool.html) <tt>get_is_auto_collected(item_id: [PackedInt64Array](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html))</tt>  
Returns the `auto_collected` property of the item. 
Only accepts bullets from [BasicItemKits](https://github.com/PickledCow/STGodot-4/wiki/BasicItemKit).


---
### [`Vector2`](https://docs.godotengine.org/en/stable/classes/class_vector2.html) <tt>get_position(id: [PackedInt64Array](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html))</tt>  
Returns the `position` property of the bullet. 
Accepts any type of bullet.


---
### [`int`](https://docs.godotengine.org/en/stable/classes/class_int.html) <tt>get_total_active_bullets()</tt>  
Returns the total number of bullets on-screen across all kits.


---
### `void` <tt>magnet_all(item_kit: [BasicItemKit](https://github.com/PickledCow/STGodot-4/wiki/BasicItemKit), target_node: [Node2D](https://docs.godotengine.org/en/stable/classes/class_node2d.html))</tt>  
Marks all currently active items as "magneted" to the provided target node.
Only accepts [BasicItemKits](https://github.com/PickledCow/STGodot-4/wiki/BasicItemKit).


---
### `void` <tt>mount(bullets_environment: [Node](https://docs.godotengine.org/en/stable/classes/class_node.html))</tt>  
Sets the given BulletsEnvironment as the current active one.


---
### `void` <tt>set_damage(id: [PackedInt64Array](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html), damage: [float](https://docs.godotengine.org/en/stable/classes/class_float.html))</tt>  
Sets the `damage` property of the bullet to the provided value.
Accepts any type of bullet.


---
### `void` <tt>set_position(id: [PackedInt64Array](https://docs.godotengine.org/en/stable/classes/class_packedint64array.html), position: [Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html))</tt>  
Sets the `damage` property of the bullet to the provided value.
Accepts any type of bullet.


---
### `void` <tt>unmount(_unnamed_arg0: [Node](https://docs.godotengine.org/en/stable/classes/class_node.html))</tt>  
Cleans up the [BulletKits](https://github.com/PickledCow/STGodot-4/wiki/BulletKit) and BulletPools of the provided BulletsEnvironment.


---
