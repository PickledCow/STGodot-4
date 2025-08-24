extends Enemy
class_name Boss

@export var attack_type_list : Array[System.ATTACK_TYPE] = []
@export var attack_name_list : Array[String] = []
@export var boss_name : String
@export var starting_position : Vector2 = Vector2(500, 300)

var current_attack := -1
var next_attack := 0



var death_explosion_time = 60.0
var death_explosion_timer = 0.0
var death_exploded := false

func _ready() -> void:
	super()
	is_boss = true
	System.current_boss = self
	System.bg.set_boss_texture($Sprite.texture)
	System.ui.update_boss_data(boss_name, attack_type_list, attack_name_list)
	
	# Remove once dialogue
	t = -30
	t_float = -30.0

func _process(delta) -> void:
	if death_explosion_timer > 0.0:
		death_explosion_timer -= 1.0
		if death_explosion_timer <= 0.0:
			death_exploded = true
			_on_death()
			System.warp_rect.warp_invert(position)
			SFX.play("boss_death")
		_movement()
	
	else:
		if not System.in_dialogue:
			super(delta)
			System.ui.set_boss_health(max(0.0, health / max_health))

			if t == -1 and current_attack < next_attack:
				current_attack = next_attack
				t = -120
				t_float = -120.0
				System.ui.increment_attack()
				System.warp_rect.warp_boss(position)
				SFX.play("blast")
		else:
			_movement()
	
func _on_death() -> void:
	_pre_death()
	next_attack += 1
	if next_attack >= attack_name_list.size():
		if death_exploded:
			super()
			System.boss_manager.increment_boss()
		else:
			SFX.play("boss_death")
			System.warp_rect.warp_boss(position, true)
			death_explosion_timer = death_explosion_time
			set_destination(position + Vector2(randf_range(32, 64), 0.0).rotated(randf()*TAU), 60)
	else:
		_post_death()
		health = max_health
		t = -1
		t_float = -1
		set_destination(starting_position, 60)
		
