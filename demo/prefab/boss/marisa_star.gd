extends Enemy

var lifespan := 60
var lifetime := 0

func _pre_process(time_scale: float) -> void:
	$Sprite2D.rotation += 0.05 * time_scale
	
	lifetime += 1
	
	if lifetime > lifespan:
		how_i_died = DEATH_TYPE.DESPAWNED
		_on_death()
