class_name Enemy
extends Node2D

@export var hitbox_radius := 16.0

@export var max_health := 100.0

var health: float

var velocity := Vector2()
var acceleration := Vector2()

var despawned := false

var enemy_hitbox : PackedInt64Array

var t := 0
var t_float := 0.0

func get_damage_taken() -> Array[PackedInt64Array]:
	return Bullets.get_enemy_collisions(enemy_hitbox)

func _ready() -> void:
	health = max_health
	enemy_hitbox = Bullets.create_enemy(hitbox_radius, hitbox_radius)
	_post_ready()
	
func _process(_delta) -> void:
	var new_frame := false
	t_float += System.time_scale
	var new_t := int(t_float)
	if new_t > t:
		new_frame = true
		t = new_t
	
	if new_frame:
		_pre_process(System.time_scale)
	
	velocity += acceleration
	position += velocity
	
	if !System.enemy_active_rect.has_point(position):
		despawned = true
		_on_death()
		Bullets.clear_entity(enemy_hitbox)
		queue_free()
		return
	
	Bullets.set_position(enemy_hitbox, position)
		
	if new_frame:
		#var collisions : Array = Bullets.collide_enemy(position, hitbox_radius)
		var collisions : Array = Bullets.get_enemy_collisions(enemy_hitbox)
		
		for bullet in collisions:
			var _damage_type : int = Bullets.get_damage_type(bullet)
			var damage : float = Bullets.get_damage(bullet)
			health -= damage
			
			if health <= 0.0:
				_on_death()
				Bullets.clear_entity(enemy_hitbox)
				queue_free()
				return
				
		_post_process(System.time_scale)

func _post_ready() -> void:
	pass

@warning_ignore("unused_parameter")
func _pre_process(time_scale: float) -> void:
	pass
	
@warning_ignore("unused_parameter")
func _post_process(time_scale: float) -> void:
	pass

func _on_death() -> void:
	pass
