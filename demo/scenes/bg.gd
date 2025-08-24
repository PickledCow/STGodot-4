extends Node3D
class_name BGHandler

var scroll := true
var time := 0.0

var test_skip := false

func _ready() -> void:
	System.bg = self
	if test_skip:
		stop_scroll()
		next_section()

func next_section():
	$AnimationPlayer.play("rise")
	

func stop_scroll() -> void:
	scroll = false
	$Prev/ScrollingStairs.mesh.material.set_shader_parameter("time", 0.0)
	$Prev/LeftRail.mesh.material.set_shader_parameter("time", 0.0)
	$Prev/Trees.scroll = false

func set_boss_texture(texture: Texture2D):
	$Prev/ShadowPlane/BossSprite.texture = texture

func _process(delta: float) -> void:
	var player : Player = System.player
	if player:
		$Prev/ShadowPlane/Sprite.position = Vector3(
			-player.position.y / System.playfield_size.x, 
			0.0, player.position.x / System.playfield_size.y
		)
		$Prev/ShadowPlane/Sprite.frame = player.sprite.frame
	
	if System.current_boss:
		var boss : Boss = System.current_boss
		$Prev/ShadowPlane/BossSprite.position = Vector3(
			-boss.position.y / System.playfield_size.x, 0.0, 
			boss.position.x / System.playfield_size.y
		)
		

	# Scroll stairs
	if scroll:
		$Prev/ScrollingStairs.mesh.material.set_shader_parameter("time", time)
		$Prev/LeftRail.mesh.material.set_shader_parameter("time", time)
		
		time += delta
