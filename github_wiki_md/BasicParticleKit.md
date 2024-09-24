### **Inherits:** [BulletKit](https://github.com/PickledCow/STGodot-4/wiki/BulletKit) < [Resource](https://docs.godotengine.org/en/stable/classes/class_resource.html)
**A [BulletKit](https://github.com/PickledCow/STGodot-4/wiki/BulletKit) for basic particles.**
## Description
A [BulletKit](https://github.com/PickledCow/STGodot-4/wiki/BulletKit) for basic particles. BasicParticleKits are a super basic implementation of [BulletKits](https://github.com/PickledCow/STGodot-4/wiki/BulletKit) for use in collisionless, short-lived bullets. Example use-cases are for graze-particles and item collection text.
## Properties
|Type|Name|Default Value|
|-|-|-|
|[bool](https://docs.godotengine.org/en/stable/classes/class_bool.html) | [facing_up](#bool-facing_up) |`true`|
|[float](https://docs.godotengine.org/en/stable/classes/class_float.html) | [fade_time](#float-fade_time) |`8.0`|
|[Material](https://docs.godotengine.org/en/stable/classes/class_material.html) | [material](#Material-material) ||
|[Texture2D](https://docs.godotengine.org/en/stable/classes/class_texture2d.html) | [texture](#Texture2D-texture) ||
|[float](https://docs.godotengine.org/en/stable/classes/class_float.html) | [texture_width](#float-texture_width) |`0.0`|
|[float](https://docs.godotengine.org/en/stable/classes/class_float.html) | [time_scale](#float-time_scale) |`1.0`|
---
## Property Descriptions
### [`bool`](https://docs.godotengine.org/en/stable/classes/class_bool.html) `facing_up`
Flag for if the bullet sprites in the spritesheet are facing up or right. Other configuartions are currently unsupported.
### [`float`](https://docs.godotengine.org/en/stable/classes/class_float.html) `fade_time`
The number of game ticks a bullet takes to finish its spawning animation. This value is ignored if the bullet is set to spawn instantly.
### [`Material`](https://docs.godotengine.org/en/stable/classes/class_material.html) `material`
The [Material](https://docs.godotengine.org/en/stable/classes/class_material.html) used for rendering the bullets. Unless you know what you're doing only use the provided materials.
### [`Texture2D`](https://docs.godotengine.org/en/stable/classes/class_texture2d.html) `texture`
The spritesheet that bullets in this kit use.
### [`float`](https://docs.godotengine.org/en/stable/classes/class_float.html) `texture_width`
The width of the spritesheet. Make sure to set this value or else you will not be able to see any bullets.
### [`float`](https://docs.godotengine.org/en/stable/classes/class_float.html) `time_scale`
The speed multiplier at which the BulletKit operates at. For example, if set to `2.0` the bullets will move twice as fast.
This value is independent between kits so if you want all kits to have the same time scale you must set it for all kits.
