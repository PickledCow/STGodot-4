extends Enemy

var wvel := 0.0
var spin := 0.0

var lifespan := 60
var lifetime := 0

func _pre_process(_time_scale: float) -> void:
	velocity = velocity.rotated(wvel)
	
	lifetime += 1
	if lifetime >= lifespan:
		how_i_died = DEATH_TYPE.DESPAWNED
		_on_death()
	
	$Sprite2D.rotate(spin)
