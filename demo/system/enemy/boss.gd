extends Enemy
class_name Boss

@export var attack_type_list : Array[System.ATTACK_TYPE] = []
@export var attack_name_list : Array[String] = []
@export var boss_name : String
@export var starting_position : Vector2 = Vector2(500, 300)
@export var tlb := false
@export var item_drop : System.ITEM_TYPE

var current_attack := -1
var next_attack := 0

var fucking_jank_frame := false

var death_explosion_time = 60.0
var death_explosion_timer = 0.0
var death_exploded := false

var attack_timer := 60 * 60


var fucking_shit_cunt_t := -1

func _ready() -> void:
	super()
	is_boss = true
	
	spark_effect = spark_prefab.instantiate()
	add_child(spark_effect)
	
	System.current_boss = self
	System.bg.set_boss_texture($Sprite.texture)
	System.ui.update_boss_data(boss_name, attack_type_list, attack_name_list)
	
	# Remove once dialogue
	t = -30
	t_float = -30.0
	invincibility_timer = -60.0
	System.ui.fade_in_timer()

func _process(delta) -> void:
	if hurt_timer > 0.0:
		hurt_timer -= System.time_scale
		if hurt_timer <= 0.0:
			hurt_timer = 0.0
			hurt_flicker_timer = 0.0
			$Sprite.modulate = Color.WHITE
		else:
			hurt_flicker_timer -= System.time_scale
			while hurt_flicker_timer < 0.0:
				hurt_flicker_timer += hurt_flicker_cycle
			$Sprite.modulate = Color.WHITE if hurt_flicker_timer < hurt_flicker_cycle * 0.5 else Color(0.1, 0.1, 1.0)
			
			
	if attack_timer <= 0:
		health = 0
	
	if death_explosion_timer > 0.0:
		death_explosion_timer -= System.time_scale
		if death_explosion_timer <= 0.0:
			death_exploded = true
			_on_death()
			SFX.play("boss_death")
			if tlb:
				System.time_scale = 1.0
				Bullets.set_time_scale(1.0)
				Engine.time_scale = 1.0
			else:
				System.warp_rect.warp_invert(position)
		_movement()
	
	else:
		if not System.in_dialogue:
			super(delta)
			if invincibility_timer <= 0.0:
				System.ui.set_boss_health(max(0.0, health / max_health))

			if t >= -1 and current_attack < next_attack and not fucking_jank_frame:
				current_attack = next_attack
				t = -120
				t_float = -120.0
				invincibility_timer = 120.0
				System.ui.increment_attack()
				System.warp_rect.warp_boss(position)
				SFX.play("blast")
		else:
			_movement()
			
	if fucking_shit_cunt_t < t:
		attack_timer -= 1
		fucking_shit_cunt_t = t
		System.ui.set_timer(attack_timer / 60.0)
	
	if fucking_jank_frame:
		fucking_jank_frame = false
	
func _on_death() -> void:
	#print(current_attack)
	_pre_death()
	#print(current_attack)
	
	next_attack += 1
	if System.in_dialogue:
		System.boss_manager.increment_boss()
		set_destination(starting_position, 60)
	elif next_attack >= attack_name_list.size():
		if death_exploded:
			super()
			System.boss_manager.increment_boss(tlb)
		else:
			var type : System.ITEM_TYPE = item_drop
			if type == System.ITEM_TYPE.RANDOM:
				@warning_ignore("int_as_enum_without_cast")
				type = randi_range(System.ITEM_TYPE.DUBIOUS, System.ITEM_TYPE.TEA)
			var item_data = System.get_item_data(type)
			Bullets.create_item(position, 8.0, PI * -0.5, 1.0, item_data, false)
			System.ui.slide_in_top_bar(true)
			SFX.play("boss_death")
			System.warp_rect.warp_boss(position, true)
			death_explosion_timer = death_explosion_time
			if tlb:
				System.time_scale = 0.5
				Bullets.set_time_scale(0.5)
				Engine.time_scale = 0.5
			
			set_destination(position + Vector2(randf_range(32, 64), 0.0).rotated(randf()*TAU), 60)
	else:
		
		var type : System.ITEM_TYPE = item_drop
		if type == System.ITEM_TYPE.RANDOM:
			@warning_ignore("int_as_enum_without_cast")
			type = randi_range(System.ITEM_TYPE.DUBIOUS, System.ITEM_TYPE.TEA)
		var item_data = System.get_item_data(type)
		Bullets.create_item(position, 0.0, 0.0, 0.0, item_data, false)
		
		
		_post_death()
		health = max_health
		t = -1
		t_float = -1
		fucking_shit_cunt_t = -1
		attack_timer = 60 * 60
		System.ui.set_timer(60)
		set_destination(starting_position, 60)
		System.ui.fill_healthbar()
