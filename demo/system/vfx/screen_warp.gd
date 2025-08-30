class_name WarpRect
extends Node2D

var player_clear_position : Vector2
var boss_clear_position : Vector2
var player_clear_radius : float = -1.0
var boss_clear_radius : float = -1.0

func _ready() -> void:
	System.register_warp_rect(self)

func _process(_delta: float) -> void:
	if player_clear_radius >= 0.0:
		player_clear_radius += System.time_scale * 1000.0 / 1.2 / 60.0 * sqrt(2.0)
		Bullets.clear_bullets(player_clear_position, player_clear_radius, true)
		if player_clear_radius >= 250.0:
			player_clear_radius = -1.0
	
	if boss_clear_radius >= 0.0:
		boss_clear_radius += System.time_scale * 1000.0 / 1.8 / 60.0 * sqrt(2.0)
		Bullets.clear_bullets(boss_clear_position, boss_clear_radius, true)
		if boss_clear_radius >= 1000.0:
			boss_clear_radius = -1.0

func warp_player(pos: Vector2) -> void:
	var norm_pos : Vector2 = pos / System.playfield_size
	material.set_shader_parameter("player_center", norm_pos)
	$PlayerWarpAnimator.play("warp")
	player_clear_position = pos
	player_clear_radius = 0.0
	
func warp_boss(pos: Vector2, no_warp: bool = false) -> void:
	var norm_pos : Vector2 = pos / System.playfield_size
	material.set_shader_parameter("boss_center", norm_pos)
	if not no_warp:
		$BossWarpAnimator.play("warp")
	boss_clear_position = pos
	boss_clear_radius = 0.0

func warp_invert(pos: Vector2) -> void:
	var norm_pos : Vector2 = pos / System.playfield_size
	material.set_shader_parameter("invert_center", norm_pos)
	$InvertAnimator.play("warp")

func reset_warps() -> void:
	material.set_shader_parameter("boss_force", 0)
	material.set_shader_parameter("boss_size", 0)
	material.set_shader_parameter("player_force", 0)
	material.set_shader_parameter("player_size", 0)
	material.set_shader_parameter("invert_size", 0)
	
