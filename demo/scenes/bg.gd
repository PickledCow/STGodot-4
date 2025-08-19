extends Node3D
class_name BGHandler

var scroll := true
var time := 0.0

func _ready() -> void:
	System.bg = self

func stop_scroll() -> void:
	scroll = false
	$ScrollingStairs.mesh.material.set_shader_parameter("time", 0.0)
	$LeftRail.mesh.material.set_shader_parameter("time", 0.0)

func set_boss_texture(texture: Texture2D):
	$ShadowPlane/BossSprite.texture = texture

func _process(delta: float) -> void:
	var player : Player = System.player
	if player:
		$ShadowPlane/Sprite.position = Vector3(
			-player.position.y / System.playfield_size.x, 
			0.0, player.position.x / System.playfield_size.y
		)
		$ShadowPlane/Sprite.frame = player.sprite.frame
	
	if System.current_boss:
		var boss : Boss = System.current_boss
		$ShadowPlane/BossSprite.position = Vector3(
			-boss.position.y / System.playfield_size.x, 0.0, 
			boss.position.x / System.playfield_size.y
		)
		

	# Scroll stairs
	if scroll:
		$ScrollingStairs.mesh.material.set_shader_parameter("time", time)
		$LeftRail.mesh.material.set_shader_parameter("time", time)
		
		time += delta
