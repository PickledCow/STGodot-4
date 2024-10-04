### **Inherits:** [CollisionBulletKit](https://github.com/PickledCow/STGodot-4/wiki/CollisionBulletKit) < [BulletKit](https://github.com/PickledCow/STGodot-4/wiki/BulletKit) < [Resource](https://docs.godotengine.org/en/stable/classes/class_resource.html)
### **Inherited By: **
**A [BulletKit](https://github.com/PickledCow/STGodot-4/wiki/BulletKit) for general purpose items.**
## Description
A [BulletKit](https://github.com/PickledCow/STGodot-4/wiki/BulletKit) for general purpose items. BasicItemKits add parameters for common behaviour of items such as their fall speed and speed at which items move towards the player when collected.
## Properties
|Type|Name|Default Value|
|-|-|-|
|[Rect2](https://docs.godotengine.org/en/stable/classes/class_rect2.html) | [active_rect](#Rect2-active_rect) |`Rect2(0, 0, 0, 0)`|
|[float](https://docs.godotengine.org/en/stable/classes/class_float.html) | [damp](#float-damp) |`0.95`|
|[bool](https://docs.godotengine.org/en/stable/classes/class_bool.html) | [facing_up](#bool-facing_up) |`true`|
|[float](https://docs.godotengine.org/en/stable/classes/class_float.html) | [fade_time](#float-fade_time) |`8.0`|
|[Vector2](https://docs.godotengine.org/en/stable/classes/class_vector2.html) | [gravity](#Vector2-gravity) |`Vector2(0, 0)`|
|[float](https://docs.godotengine.org/en/stable/classes/class_float.html) | [magnet_strength](#float-magnet_strength) |`10.0`|
|[Material](https://docs.godotengine.org/en/stable/classes/class_material.html) | [material](#Material-material) ||
|[Texture2D](https://docs.godotengine.org/en/stable/classes/class_texture2d.html) | [texture](#Texture2D-texture) ||
|[float](https://docs.godotengine.org/en/stable/classes/class_float.html) | [texture_width](#float-texture_width) |`0.0`|
|[float](https://docs.godotengine.org/en/stable/classes/class_float.html) | [time_scale](#float-time_scale) |`1.0`|
---
## Property Descriptions
### [`Rect2`](https://docs.godotengine.org/en/stable/classes/class_rect2.html) `active_rect`
The [Rect2](https://docs.godotengine.org/en/stable/classes/class_rect2.html) at which bullets can exist in. If a bullet leaves this space and is set to be automatically deleted (which is by default), the bullet will be marked for removal and be deleted the following frame.
The [Rect2](https://docs.godotengine.org/en/stable/classes/class_rect2.html) should generally be slightly bigger than the visible playfield to not have bullets vanish while still partially visible.
### [`float`](https://docs.godotengine.org/en/stable/classes/class_float.html) `damp`
How much the initial speed of the item decreases per tick.
### [`bool`](https://docs.godotengine.org/en/stable/classes/class_bool.html) `facing_up`
Flag for if the bullet sprites in the spritesheet are facing up or right. Other configuartions are currently unsupported.
### [`float`](https://docs.godotengine.org/en/stable/classes/class_float.html) `fade_time`
The number of game ticks a bullet takes to finish its spawning animation. This value is ignored if the bullet is set to spawn instantly.
### [`Vector2`](https://docs.godotengine.org/en/stable/classes/class_vector2.html) `gravity`
Velocity vector of the item's movement after the scatter animation in pixels per tick.
### [`float`](https://docs.godotengine.org/en/stable/classes/class_float.html) `magnet_strength`
The speed at which items move towards the player when collected in pixels per tick.
### [`Material`](https://docs.godotengine.org/en/stable/classes/class_material.html) `material`
The [Material](https://docs.godotengine.org/en/stable/classes/class_material.html) used for rendering the bullets. Unless you know what you're doing only use the provided materials.
### [`Texture2D`](https://docs.godotengine.org/en/stable/classes/class_texture2d.html) `texture`
The spritesheet that bullets in this kit use.
### [`float`](https://docs.godotengine.org/en/stable/classes/class_float.html) `texture_width`
The width of the spritesheet. Make sure to set this value or else you will not be able to see any bullets.
### [`float`](https://docs.godotengine.org/en/stable/classes/class_float.html) `time_scale`
The speed multiplier at which the BulletKit operates at. For example, if set to `2.0` the bullets will move twice as fast.
			This value is independent between kits so if you want all kits to have the same time scale you must set it for all kits.
