extends Node2D
class_name Player
## Base Player class. Has most important implementation and can be extended from
## with minimal changes.
## 
## The base Player class. Handles basic functions with movement, collisions,
## life management, and basic sprite rendering. 
## [br][br]
## Shooting should be handled by a child [ShooterManager] with the Player holding
## a [NodePath] to the node.
## [br][br]
## When making a custom Player, create a new script that extends from [Player] 
## and make any necessary overrides to functions if the modifiable parameters
## from the editor sidebar is not enough. [br]
## For example: 
## [codeblock]
## extends Player
## class_name RobbiePlayer
## 
## # Override of default implementation to support the new item types
## func collect_items(items: Array[PackedInt64Array]) ->:
##     # New implementation goes here.
## [/codeblock]
## [br][br]
## Designed to work with the default system. Changes to the system may
## necessitate changes to your player.
## @experimental

# =============================================================================
#   ┏━━┓  ┏━━┓   ┏━━━━━━━┓  ┏━━┓  ┏━━┓   ┏━━┓
#   ┃  ┃  ┃  ┃   ┃  ┏━━━━┛  ┃  ┃  ┃  ┃   ┃  ┃
#   ┃  ┗━━┛  ┃   ┃  ┗━━━┓   ┃  ┗━━┛  ┃   ┃  ┃
#   ┃  ┏━━┓  ┃   ┃  ┏━━━┛   ┗━━┓  ┏━━┛   ┗━━┛
#   ┃  ┃  ┃  ┃   ┃  ┗━━━━┓     ┃  ┃      ┏━━┓
#   ┗━━┛  ┗━━┛   ┗━━━━━━━┛     ┗━━┛      ┗━━┛
#
# You can collapse these regions to make the code significantly easier to read.
# Seriously, this script is pretty long and messy.
# =============================================================================


#region Enums

## Style of input handling.
## [br][br]
## [b]PRIORITY[/b][br]
## Priority inputs simply has either left/right and up/down take priority over 
## the opposite. By default set to left and up.
## down inputs. 
## [br][br]
## [b]ZERO[/b][br]
## Zero inputs has opposite direction inputs cancel out to zero.
## [br][br]
## [b]NULL_CANCEL[/b][br]
## Null cancelled inputs are a style of input handling where the more recent 
## input direction is used over older ones. If the player
## presses the opposite direction without letting go of the first, the player
## instnatly starts moving in the new direction.
## This makes the input generally feel snappier than the other style of inputs.
## [br][br]
## For example, if the player is holding left currently and presses right 
## without letting go of left, the player will instantly start to move right.[br]
## Letting go of right while still holding left will have the player instantly 
## start moving left again.
## [br][br]
## 
enum INPUT_STYLE { 
	PRIORITY, ## Have one input direction always take priority over the other.
	ZERO, ## Have opposite inputs cancel out to zero.
	NULL_CANCEL ## Have opposite inputs favour more recent inputs.
}

## Enum for horizontal priority for NULL_CANCEL style inputs.
enum H_PRIORITY { 
	LEFT, ## Left inputs have priority.
	RIGHT ## Right inputs have priority.
}
## Enum for vertical priority for NULL_CANCEL style inputs.
enum V_PRIORITY { 
	UP,  ## Up inputs have priority.
	DOWN ## Down inputs have priority.
}

## Structure of spritesheet. Currently only 2 styles of spritesheet structures
## are supported. If your spritesheet dose not fit one of these structures you
## will either have to modify your spritesheet or override [method Player.animation].
## [br][br]
## [b]STAND_RIGHT[/b][br]
## Used for simple spritesheets with direction mirroring.[br]
## Assumes all frames are right-orientated with the first row
## of sprites being for idle and the second row being for moving right. [br]
## Leftwards movement will have the player sprite mirrored.
## [br][br]
## [b]STAND_LEFT_RIGHT[/b][br]
## Used for more advanced spritesheets where the player sprite may not be mirrored.[br]
## Assumes that the a new row of sprites for moving left is added at the end.[br]
## The sprites will not be mirrored  regardless of player movement.
enum SPRITESHEET_FORMAT {
	IDLE_RIGHT, 	  ## Format with idle and right-moving sprites.
	IDLE_RIGHT_LEFT, ## Format with idle, right-moving, and left-moving sprites.
}

## Current state of animation. 
enum ANIMATION_STATE {
	IDLE,
	RIGHT,
	LEFT
}

## Style of player power
enum POWER_STYLE {
	NONE, ## No power system. The player is always at maximum power.
	INT, ## Player power is one large bar with user set values for transitions.
	DECIMAL ## Player power spikes are separated by integer values. Internal power is still stored like the INT system. 
}

## The style of resource fragments required for the next amount.
enum FRAGMENT_REQUIREMENT {
	CONSTANT, ## The resource always requires the same number of fragments each time.
	VARIABLE ## The fragments requirement changes each time one is completed.
}

#endregion

#region Constants

## Array for the input StringNames for horizontal inputs.
const H_PRIORITY_INPUT_NAMES := [&"player_left", &"player_right"]
## Array for the input StringNames for vertical inputs.
const V_PRIORITY_INPUT_NAMES := [&"player_up", &"player_down"]

#endregion

#region Export Variables

@export_node_path("ShooterManager") var shooter_manager_path : NodePath = NodePath()


@export_group("Vitality")
## Default starting lives. Game over occurs when you die with 0 lives.
@export_range(0, 16, 1, "or_greater") var starting_lives := 2
## How many bombs you start with per life.
@export_range(0, 16, 1, "or_greater") var starting_bombs := 3
## How many lives the player can hold onto at once. [br]
## Set to -1 for no limit.
@export_range(-1, 16, 1, "or_greater") var max_lives := -1
## How many bombs the player can hold onto at once. [br]
## Set to -1 for no limit.
@export_range(-1, 16, 1, "or_greater") var max_bombs := -1
## Style of life fragment requirements.
@export var life_fragment_style := FRAGMENT_REQUIREMENT.CONSTANT
## Style of bomb fragment requirements.
@export var bomb_fragment_style := FRAGMENT_REQUIREMENT.CONSTANT
## How many life fragments are required to complete a life. [br]
## If [member Player.life_fragment_style] is set to VARIABLE and we've already
## reached the end of [member Player.life_fragment_requirement_array] this value
## will be used for further lives.
@export_range(1, 12, 1, "or_greater") var life_fragment_requirement := 5
## How many bomb fragments are required to complete a bomb. [br]
## If [member Player.bomb_fragment_style] is set to VARIABLE and we've already
## reached the end of [member Player.bomb_fragment_requirement_array] this value
## will be used for further bombs.
@export_range(1, 12, 1, "or_greater") var bomb_fragment_requirement := 5
## Array of values for the required amount of life fragments for a life if  
## [member Player.life_fragment_style] is set to VARIABLE. 
@export var life_fragment_requirement_array : Array[int]
## Array of values for the required amount of bomb fragments for a bomb if  
## [member Player.bomb_fragment_style] is set to VARIABLE. 
@export var bomb_fragment_requirement_array : Array[int]
## Enabling this makes death reset bomb count even if above default.
@export var reset_bombs_on_death := true
## Enabling this resets the required bomb fragment count back to the start. [br]
## If the number of fragments exceeds the requirement upon respawning, the player
## will be granted a bomb and the fragment count reset to 0.
@export var reset_bomb_requirement_on_death := true
## How many ticks we have to bomb to deathbomb.
@export_range(0, 60, 1, "or_greater") var deathbomb_window := 8
## Enables a more restrictive style of  deathbombs where the deathbomb window 
## does not reset until death and makes subsequent deathbombs in one life harder. 
@export var diminishing_deathbomb_window := false
## If we respawn or just gain i-frames on death. If false, uses respawn_i_frames for i-frames.
@export var respawn_on_death := true
## How many ticks it takes to die.
@export_range(0, 300, 1, "or_greater") var death_time := 60
## How many ticks to respawn before control is returned to the player.
@export_range(0, 120, 1, "or_greater") var respawn_time := 60
## Position on screen to have the player spawn at.
@export var respawn_position := Vector2(500, 900)
## How much the player moves while respawning to reach [member Player.respawn_position].
@export var respawn_travel := Vector2(0, -200)
## How many ticks of invulnerability the player has after respawning.
@export_range(0, 600, 1, "or_greater") var respawn_i_frames := 240.0
## Whether to start the player with i-frames or not.
@export var spawn_with_invulnerability := true

@export_group("Movement")
## Unfocused (fast) movement speed of the player in pixels per tick.
@export_range(0, 16, 0.1, "or_greater") var unfocus_speed := 6.0
## Focused (slow) movement speed of the player in pixels per tick.
@export_range(0, 16, 0.1, "or_greater") var focus_speed := 3.0

@export_subgroup("Margins", "margin_")
## Minimum distance between the left wall and the player.
@export_range(0, 128, 0.1, "or_greater") var margin_left := 24.0
## Minimum distance between the ceiling and the player.
@export_range(0, 128, 0.1, "or_greater") var margin_top := 48.0
## Minimum distance between the right wall and the player.
@export_range(0, 128, 0.1, "or_greater") var margin_right := 24.0
## Minimum distance between the floor and the player.
@export_range(0, 128, 0.1, "or_greater") var margin_bottom:= 24.0


@export_group("Power")
## Style of player power system to use.
@export var power_style := POWER_STYLE.DECIMAL
## The minimum power value.
@export_range(0, 1024, 1, "or_greater") var min_power := 20
## The power value the player starts with.
## The maximum power value.
@export_range(0, 1024, 1, "or_greater") var max_power := 80
## The power value the player starts with. Usually should equal [member Player.min_power].
@export_range(0, 1024, 1, "or_greater") var starting_power := 20
## The milestones for changes to the shottype for INT style, excluding starting power.
## Values below [member Player.min_power] and above [member Player.max_power] will
## render some power levels inaccessible.
@export var int_power_transitions: Array = [0] as Array[int] 
## How many small power items is needed to get 1 full power for the DECIMAL system.
## Unused with other power systems.
@export_range(1, 100, 1, "or_greater") var decimal_power_subdivision := 20
## How many small power items one large power item is equivalent to. For the DECIMAL system this value
## should usually be equal to [member Player.decimal_power_subdivision]
@export_range(1, 100, 1, "or_greater") var large_power_item_value := 20
## How much power the player loses on death. Will not lower power below [member Player.min_power].
@export_range(1, 100, 1, "or_greater") var power_loss_on_death := 10
## Whether to trigger a screen-clear when reaching full power.
@export var full_power_screen_clear := false

@export_subgroup("Item Drops")
## How many power items the player should drop on death.
@export_range(0, 32, 1, "or_greater") var death_item_drop_amount := 7
## How spread out the items dropped on death are in degrees.
@export_range(0, 180.0, 0.1) var death_item_drop_spread_degrees := 30.0
## How far away the dropped items will be from the player in pixels.
@export_range(0, 256, 0.1, "or_greater") var death_item_drop_distance := 96.0
## Drops a full power item when dying with 1 life left.
@export var last_life_death_drop_full_power_item := false
## Drops a full power item when using a continue.
@export var continue_drop_full_power_item := false

@export_group("Input")
## See [enum Player.INPUT_STYLE] for a more in-depth explanation.
@export var input_style := INPUT_STYLE.NULL_CANCEL
## Horizontal priority for PRIORITY and NULL_CANCEL style inputs.
@export var horizontal_input_priority := H_PRIORITY.LEFT
## Vertical priority for PRIORITY and NULL_CANCEL style inputs.
@export var vertical_input_priority := V_PRIORITY.UP


@export_group("Collision")
## Radius of the player hitbox in pixels.
@export_range(0, 16, 0.1, "or_greater") var hitbox_radius := 3.0
## Radius of the bullet graze hitbox in pixels.
@export_range(0, 64, 0.1, "or_greater") var graze_radius := 16.0
## Radius of the hitbox for collecting items in pixels.
@export_range(0, 32, 0.1, "or_greater") var item_collect_radius := 8.0
## Radius of the hitbox for magneting items while unfocused in pixels.
@export_range(0, 128, 0.1, "or_greater") var unfocus_item_magnet_radius := 64.0
## Radius of the hitbox for magneting items while focused in pixels.
@export_range(0, 128, 0.1, "or_greater") var focus_item_magnet_radius := 64.0
## Height the player needs to be to autocollect
@export_range(0, 2048, 1, "or_greater") var autocollect_height := 500.0
## Whether the player needs to be at max power to perform autocollection.
@export var autocollect_require_full_power := false


@export_group("Animation")
## Layout of the spritsheet. See [enum Player.SPRITESHEET_FORMAT] for details.
@export var spritesheet_format := SPRITESHEET_FORMAT.IDLE_RIGHT:
	set(sf):
		spritesheet_format = sf
		# TODO: Borked why 
		#$Sprite.set_vframes(2 if sf == SPRITESHEET_FORMAT.IDLE_RIGHT else 3)

## How many frames of animation is in one loop of the idle animation.
@export_range(1, 16, 1, "or_greater") var idle_animation_frame_count := 4:
	set(fc):
		idle_animation_frame_count = fc
		$Sprite._update_hframes()
## How many frames of animation is in one loop of the movement animation
## including the transition frames.
@export_range(1, 16, 1, "or_greater") var move_animation_frame_count := 4:
	set(fc):
		move_animation_frame_count = fc
		$Sprite._update_hframes()
## How many frames of turning transition animations there are in the spritesheet.
## Transition animations are not repeated once the animation loops. [br]
## Transition animations are only present in the turning animations and not in 
## the idle stance.
@export_range(0, 16, 1, "or_greater") var transition_frame_count := 0
## How long each frame of animation should last in seconds.
@export_range(0.01, 2.0, 0.1, "or_greater") var animation_speed := 0.1
## The flash cycle duration for i-frames in seconds.
@export_range(0.1, 2, 0.1, "or_greater") var i_frame_flash_cycle_duration := 1.0

@export_group("", "")
#endregion

#region On-Ready Variables

var shooter_manager: ShooterManager

@onready var focus_under := $Focus/FocusUnder
@onready var focus_over := $Focus/FocusOver
@onready var sprite := $Sprite

#endregion

#region Player State Variables > Basic States

## If the player is currently in the focus state.
var is_focused := false
## Velocity of the player
var velocity : Vector2
## Desired movement direction of the player, normalised
var desired_direction : Vector2

#endregion

#region Player State Variables > Vitality States

var is_alive := true

@onready var current_lives := starting_lives
@onready var current_bombs := starting_bombs

## How many times we've gotten lives through fragments. Lives gotten through 
## full life items do not increase this.
var life_extend_count := 0
## How many times we've gotten bombs through fragments. Bombs gotten through 
## full bomb items do not increase this.
var bomb_extend_count := 0

## How many life fragments we have currently
var life_fragment_count := 0
## How many bomb fragments we have currently
var bomb_fragment_count := 0

var deathbomb_timer := 0.0
var death_timer := 0.0
var respawn_timer := 0.0

var current_i_frames := 0.0

#endregion

#region Player State Variables > Power States

@onready var current_power := starting_power

#endregion

#region Player State Variables > Input Priority states

## Dynamic horizontal input priority for NULL_CANCEL style inputs.
var current_horizontal_input_priority := H_PRIORITY.LEFT
## Dynamic vertical input priority for NULL_CANCEL style inputs.
var current_vertical_input_priority := V_PRIORITY.UP

#endregion

#region Player State Variables > Animation States

## Timer for changing animation frames.
var animation_timer := 0.0
## Current frame of animation.
var animation_frame := 0
## Current state of animation.
var animation_state := ANIMATION_STATE.IDLE
## I-frame flash timer
var i_frame_animation_timer := 0.0

#endregion

#region Game Specific Behaviour

#region Normal and more
var suction_collision : PackedFloat64Array
var spit_attack : PackedFloat64Array
var super_spit_attack : PackedFloat64Array

var double_star_animation_timer := 0.0

var forced_slowdown := false

enum PLAYER_ABILITY { NORMAL, BOOMER, FREEZE, PARASOL, SPARK, BOMB, SNIPER, SWORD, GHOST, STARROD }
const ABILITY_STRINGS : Array[String] = ["Yuuma", "Boomer", "Freeze", "Parasol", "Spark", "Bomb", "Sniper", "Sword", "Ghost", "Hyper"]
var ability_in_mouth : PLAYER_ABILITY = PLAYER_ABILITY.NORMAL # Normal notates no ability, can't get Normal from an item
var player_ability : PLAYER_ABILITY = PLAYER_ABILITY.NORMAL
var player_attacking := false
var forced_sucking := false
var item_in_mouth := false
var fire_released_since_suck_or_spit := true
var is_swallowing := false

var suck_endlag_time := 20
var suck_endlag_timer := 0
var spit_endlag_time := 20
var spit_endlag_timer := 0
var minimum_suck_time := 15
var minimum_suck_timer := 0
var swallow_time := 15
var swallow_timer := 0

var attack_power := 0


#endregion

#region Boomer

var boomer_fire_timer := 0.0
var boomer_fire_rate := 50.0

var boomer_initial_velocity := 30.0
var boomer_max_velocity := 36.0
var boomer_travel_time := 24.0

var boomer_angle := -PI * 0.5
var boomer_bullet : PackedFloat64Array
var boomer_return_bullet : PackedFloat64Array

var outgoing_boomerang_positions : Array[Vector2] = [] 
var outgoing_boomerang_angles : Array[float] = [] 
var outgoing_timers : Array[float]

#endregion


#region Parasol

var parasol_animation_frame := 0.0

var droplet : PackedFloat64Array
var canopy_damage : PackedFloat64Array
@onready var canopy : Sprite2D = $Parasol/Shield

enum PARASOL_STATE { DEPLOYING, FORCE_DEPLOYED, DEPLOYED, HOLSTERING, HOLSTERED }
var parasol_deploy_min_time := 20.0
var parasol_shield_frame := 8.0
var parasol_holster_min_time := 20.0
var parasol_timer := 0.0
var parasol_state : PARASOL_STATE = PARASOL_STATE.HOLSTERED

#endregion

#region Spark

var spark_input_buffer := 0
var spark_input_buffer_max := 5
var spark_graze_buffer := 0
var spark_graze_buffer_max := 10
var spark_graze_transfer_rate := 3.0
var spark_graze_transfer_timer := 0.0
var spark_transfer_rate := 6.0
var spark_transfer_timer := 0.0

var spark_transfer_buffer := 0

var spark_charge_level := 0
var spark_charge_level_thresholds : Array[int] = [12, 40]
var spark_charge_sfx : Array[StringName] = [&"plasma_shot_s", &"plasma_shot_m", &"plasma_shot_l"]

var spark_decay_rate := 20.0
var spark_decay_timer := 0.0

var spark_fire_rate := 12.0
var spark_fire_timer := 0.0

var spark_shoot_released := true

var spark_bullets : Array[PackedFloat64Array] = []
var spark_lifespans : Array[float] = [8, INF, INF]
var spark_speeds : Array[float] = [45.0, 36.0, 30.0]
var spark_pierce : Array[bool] = [false, true, true]

var spark_animation_timer := 0.0
var spark_shield_bullet : PackedFloat64Array

#endregion

#region Bomb

var bomb_prefab := preload("res://prefab/player/yuuma/bomb.tscn")

var bomb_charge_time := 60.0
var bomb_charge_timer := 0.0
var last_bomb_released := false
var bomb_cooldown_time := 40.0
var bomb_cooldown_timer := 0.0

enum BOMB_STATE { IDLE, CHARGING }
var bomb_state : BOMB_STATE = BOMB_STATE.IDLE

#endregion


#region Sniper
var active_reload_timer := 0
var active_reload_repress := true
var scope_time := 20
var scope_timer := 0
var noscope_move_speed := 60.0
var scope_move_speed := 30.0
var scope_start_zoom = 6.0
var scope_final_opacity := 0.9
var scope_minimum_start := 5
var scope_position : Vector2
var active_reload_attempted := false
var active_reload_minimum := 60
var active_reload_maximum := 108
var active_reload_duration := 120
var snipe_bullet : PackedFloat64Array
@onready var scope : Sprite2D = $Sniper/Scope
@onready var reload_bar : Node2D = $Sniper/ReloadBar
@onready var active_reload_region : ColorRect = $Sniper/ReloadBar/Active
@onready var reload_bar_progress : TextureProgressBar = $Sniper/ReloadBar/Progress
#endregion

#region Sword

var slash_prefab := preload("res://prefab/player/yuuma/slash.tscn")
var stab_prefab := preload("res://prefab/player/yuuma/stab.tscn")
var slash_lr := 1.0

var sword_timer := 0.0
var slash_cooldown := 10.0
var stab_cooldown := 30.0

var parry_timer := 0.0
var parry_duration := 45.0
var parry_cooldown := 180.0
var parry_success_cooldown := 60.0
var parry_cooldown_timer := 0.0
var parry_success := false


#endregion

#region Freeze 

var frost_breath : PackedFloat64Array

var freeze_timer := 0.0
var freeze_cooldown := 3.0

#endregion

#region Star rod

var star_rod_timer := 0.0
var star_rod_fire_rate := 10.0

#endregion

#endregion

#region State Functions

func can_move():
	if not is_alive: return false
	
	# Can have additional states
	
	return true

#endregion

#region Sub-Routinse

## Subroutine for updating the animation state depending on what direction we're
## moving. Called by [method Player.movement] by default and will need to be 
## called manually if overriding.
func update_animation_state(dir: float) -> void:
	# If we stopped moving horizontally we have a very simple case.
	if dir == 0.0:
		animation_state = ANIMATION_STATE.IDLE
		return
	
	var prev_animation_state := animation_state
	
	# Moving right
	if dir > 0.0:
		animation_state = ANIMATION_STATE.RIGHT
		# Make the sprite face the right way.
		if spritesheet_format == SPRITESHEET_FORMAT.IDLE_RIGHT:
			scale.x = abs(scale.x)
	# Moving left
	else:
		# Make the sprite face the right way. (left)
		if spritesheet_format == SPRITESHEET_FORMAT.IDLE_RIGHT:
			animation_state = ANIMATION_STATE.RIGHT
			scale.x = -abs(scale.x)
		elif spritesheet_format == SPRITESHEET_FORMAT.IDLE_RIGHT_LEFT:
			animation_state = ANIMATION_STATE.LEFT
			
	# Reset frames if we have transition frames.
	if prev_animation_state != animation_state and transition_frame_count > 0:
		animation_frame = 0
	
func hit():
	SFX.play("death")
	die()
	#if player_ability != PLAYER_ABILITY.SWORD:
		#die()
	#else:
		#deathbomb_timer = deathbomb_window

func die():
	$DeathRing/AnimationPlayer.play("death")
	$DeathRing.rotation = randf()*TAU
	System.warp_player(position)
	current_lives -= 1
	System.ui.set_health(current_lives)
	if respawn_on_death:
		pass
	else:
		current_i_frames = respawn_i_frames
		i_frame_animation_timer = 0.0
		#System.warp_player(position)

## Goes through the list of items we've collected and performs the appropriate
## actions for them. 
func collect_items(items: Array) -> void:
	if len(items) > 0:
		#SFX.play("item")
		pass
		
	var categorized_items : Array[Array] = []
	
	for i in System.ITEM_TYPE.size():
		categorized_items.append([])

	for item in items:
		categorized_items[Bullets.get_item_type(item)].append(item)
	#print(items)
	if categorized_items[System.ITEM_TYPE.STAR].size() > 0 and spit_endlag_timer <= 0:
		item_in_mouth = true
		forced_sucking = false
		minimum_suck_timer = 0
		# Assumption you can only have one type of ability in your mouth
		ability_in_mouth = int(Bullets.get_damage(categorized_items[0][0])) as PLAYER_ABILITY
		#if attack_power == 0:
		SFX.play("inmouth")
		attack_power += categorized_items[System.ITEM_TYPE.STAR].size()
		
		$TrailingStarAnimation.play("add")
		
		if attack_power > 1:
			$TrailingStar/Single.hide()
			$TrailingStar/Double.show()
		else:
			$TrailingStar/Single.show()
			$TrailingStar/Double.hide()
	
	#process_collected_point_items(
		#categorized_items[System.ITEM_TYPE.POINT], 
		#categorized_items[System.ITEM_TYPE.CLEAR]
	#)
	#
	#process_collected_power(
		#categorized_items[System.ITEM_TYPE.POWER], 
		#categorized_items[System.ITEM_TYPE.LARGE_POWER], 
		#categorized_items[System.ITEM_TYPE.FULL_POWER]
	#)
	#
	#process_collected_bomb_items(
		#categorized_items[System.ITEM_TYPE.BOMB_FRAGMENT], 
		#categorized_items[System.ITEM_TYPE.BOMB]
	#)
	#
	#process_collected_life_items(
		#categorized_items[System.ITEM_TYPE.LIFE_FRAGMENT], 
		#categorized_items[System.ITEM_TYPE.LIFE]
	#)

## Subroutine to process collected power items.
func process_collected_power(small_power_items: Array, large_power_items: Array, full_power_items: Array) -> void:
	current_power += len(small_power_items) + len(large_power_items) * large_power_item_value
	
	if len(full_power_items) > 0 or current_power > max_power:
		current_power = max_power
	

## Subroutine to process collected point items.
func process_collected_point_items(point_items: Array, clear_items: Array) -> void:
	System.collect_piv_items(len(clear_items))
	System.collect_point_items(len(point_items))

## Subroutine to process collected life items.
func process_collected_life_items(life_fragment_items: Array, life_items: Array) -> void:
	update_life_count(len(life_fragment_items), len(life_items))

## Subroutine to process collected bomb items.
func process_collected_bomb_items(bomb_fragment_items: Array, bomb_items: Array) -> void:
	update_bomb_count(len(bomb_fragment_items), len(bomb_items))


## Updates lives and fragment count.
func update_life_count(fragment_count: int, whole_count: int) -> void:
	
	# ------------------------------
	# Process fragments 
	# ------------------------------
	life_fragment_count += fragment_count
	
	var variable_fragment := life_fragment_style == FRAGMENT_REQUIREMENT.VARIABLE
	
	var requirement: int
	if variable_fragment and life_extend_count < len(life_fragment_requirement_array):
		requirement = life_fragment_requirement_array[life_extend_count]
	else:
		requirement = life_fragment_requirement
		
	while (life_fragment_count >= requirement):
		life_fragment_count -= requirement
		current_lives += 1
		life_extend_count += 1
		
		if variable_fragment and life_extend_count < len(life_fragment_requirement_array):
			requirement = life_fragment_requirement_array[life_extend_count]
		else:
			requirement = life_fragment_count
			
	# ------------------------------
	# Process full items
	# ------------------------------
	
	current_lives += whole_count
	
	# ------------------------------
	# Cap lives
	# ------------------------------
	
	if max_lives != -1 and current_lives > max_lives:
		current_lives = max_lives
		
## Updates bombs and fragment count.
func update_bomb_count(fragment_count: int, whole_count: int) -> void:
	
	# ------------------------------
	# Process fragments 
	# ------------------------------
	bomb_fragment_count += fragment_count
	
	var variable_fragment := bomb_fragment_style == FRAGMENT_REQUIREMENT.VARIABLE
	
	var requirement: int
	if variable_fragment and bomb_extend_count < len(bomb_fragment_requirement_array):
		requirement = bomb_fragment_requirement_array[bomb_extend_count]
	else:
		requirement = bomb_fragment_requirement
		
	while (bomb_fragment_count >= requirement):
		bomb_fragment_count -= requirement
		current_bombs += 1
		bomb_extend_count += 1
		
		if variable_fragment and bomb_extend_count < len(bomb_fragment_requirement_array):
			requirement = bomb_fragment_requirement_array[bomb_extend_count]
		else:
			requirement = bomb_fragment_count
			
	# ------------------------------
	# Process full items
	# ------------------------------
	
	current_bombs += whole_count
	
	# ------------------------------
	# Cap bombs
	# ------------------------------
	
	if max_bombs != -1 and current_bombs > max_bombs:
		current_bombs = max_bombs
	

#endregion

#region Main Routines
## Base movement code. Calls [method Player.update_animation_state] by default 
## and will need to call it if overriding this function.
func movement(time_scale) -> void:
	
	if not can_move():
		return
	
	# ------------------------------
	# Update focus state
	# ------------------------------
	is_focused = GameInput.is_action_pressed(&"player_focus")
	
	# ------------------------------
	# Handle movement 
	# ------------------------------
	velocity = Vector2()
	
	# Handle input according to the desired input style.
	match input_style:
		# Yeah it's pretty gross...
		INPUT_STYLE.PRIORITY:
			if GameInput.is_action_pressed( H_PRIORITY_INPUT_NAMES[ horizontal_input_priority ] ):
				velocity.x = horizontal_input_priority * 2.0 - 1.0
			elif GameInput.is_action_pressed( H_PRIORITY_INPUT_NAMES[ 1 - horizontal_input_priority ] ):
				velocity.x = (1 - horizontal_input_priority) * 2.0 - 1.0
				
			if GameInput.is_action_pressed( V_PRIORITY_INPUT_NAMES[ vertical_input_priority ] ):
				velocity.y = vertical_input_priority * 2.0 - 1.0
			elif GameInput.is_action_pressed( V_PRIORITY_INPUT_NAMES[ 1 - vertical_input_priority ] ):
				velocity.y = (1 - vertical_input_priority) * 2.0 - 1.0
		
		# Oh hey how simple!
		INPUT_STYLE.ZERO:
			if GameInput.is_action_pressed(&"player_left"):
				velocity.x -= 1.0
			if GameInput.is_action_pressed(&"player_right"):
				velocity.x += 1.0
			if GameInput.is_action_pressed(&"player_up"):
				velocity.y -= 1.0
			if GameInput.is_action_pressed(&"player_down"):
				velocity.y += 1.0
				
		# ...it's really gross...
		INPUT_STYLE.NULL_CANCEL:
			if GameInput.is_action_just_pressed( H_PRIORITY_INPUT_NAMES[ horizontal_input_priority ] ):
				current_horizontal_input_priority = horizontal_input_priority
			elif GameInput.is_action_just_pressed( H_PRIORITY_INPUT_NAMES[ 1 - horizontal_input_priority ] ):
				@warning_ignore("int_as_enum_without_cast")
				current_horizontal_input_priority = 1 - horizontal_input_priority
				
			if GameInput.is_action_just_pressed( V_PRIORITY_INPUT_NAMES[ vertical_input_priority ] ):
				current_vertical_input_priority = vertical_input_priority
			elif GameInput.is_action_just_pressed( V_PRIORITY_INPUT_NAMES[ 1 - vertical_input_priority ] ):
				@warning_ignore("int_as_enum_without_cast")
				current_vertical_input_priority = 1 - vertical_input_priority
				
			if (GameInput.is_action_pressed( H_PRIORITY_INPUT_NAMES[ horizontal_input_priority ] ) 
				and not(current_horizontal_input_priority == 1 - horizontal_input_priority and 
				GameInput.is_action_pressed( H_PRIORITY_INPUT_NAMES[ 1 - horizontal_input_priority ]))
			):
				velocity.x = horizontal_input_priority * 2.0 - 1.0
				
			elif (GameInput.is_action_pressed( H_PRIORITY_INPUT_NAMES[ 1 - horizontal_input_priority ] ) 
				and not(current_horizontal_input_priority == horizontal_input_priority and 
				GameInput.is_action_pressed( H_PRIORITY_INPUT_NAMES[ horizontal_input_priority ]))
			):
				velocity.x = (1 - horizontal_input_priority) * 2.0 - 1.0
				

			if (GameInput.is_action_pressed( V_PRIORITY_INPUT_NAMES[ vertical_input_priority ] ) 
				and not(current_vertical_input_priority == 1 - vertical_input_priority and 
				GameInput.is_action_pressed( V_PRIORITY_INPUT_NAMES[ 1 - vertical_input_priority ]))
			):
				velocity.y = vertical_input_priority * 2.0 - 1.0
				
			elif (GameInput.is_action_pressed( V_PRIORITY_INPUT_NAMES[ 1 - vertical_input_priority ] ) 
				and not(current_vertical_input_priority == vertical_input_priority and 
				GameInput.is_action_pressed( V_PRIORITY_INPUT_NAMES[ vertical_input_priority ]))
			):
				velocity.y = (1 - vertical_input_priority) * 2.0 - 1.0
				
			
	# If non-zero input, normalize direction and multiply by speed.
	
	var movement_speed : float = unfocus_speed
	if is_focused:
		movement_speed = focus_speed
	if forced_slowdown:
		movement_speed = focus_speed
	
	if (velocity.length_squared() > 0):
		velocity = velocity.normalized() * movement_speed * time_scale
	
	desired_direction = velocity.normalized()
	
	# Prevents player from moving during snipng
	if (
		not (player_ability == PLAYER_ABILITY.SNIPER and scope_timer > 0.0) and
		not (player_ability == PLAYER_ABILITY.SWORD and parry_timer > 8.0)
	):
		position += velocity
	
	# ------------------------------
	# Clamp player movement to bounds.
	# ------------------------------
	position = Vector2(
		clamp(position.x, margin_left, System.playfield_size.x - margin_right),
		clamp(position.y, margin_top, System.playfield_size.y - margin_bottom)
	)
	
	# ------------------------------
	# Update sprite direction with direction moved.
	# ------------------------------
	update_animation_state(sign(velocity.x))
		

## Updates the player sprite according to elapsed real tiem.
func animation(delta) -> void:
	animation_timer += delta
	
	# Increment as many frames needed. Usually this should be just 1 at most but
	# in a major lag spike could roll over multiple frames.
	while (animation_timer > animation_speed):
		animation_timer -= animation_speed
		animation_frame += 1
	
	# Wrap-around animation frame.
	if animation_state == ANIMATION_STATE.IDLE:
		animation_frame = animation_frame % idle_animation_frame_count
	else:
		animation_frame = (animation_frame - transition_frame_count) % move_animation_frame_count + transition_frame_count
		
	sprite.frame = animation_frame + sprite.hframes * animation_state
	
	# Focus spin
	focus_under.rotation += delta
	focus_over.rotation -= delta
	
	if GameInput.is_action_just_pressed("player_focus"):
		$FocusAnimation.play("focus")
	if GameInput.is_action_just_released("player_focus"):
		$FocusAnimation.play_backwards("focus")
	
	if current_i_frames > 0.0:
		i_frame_animation_timer += delta
		while i_frame_animation_timer >= i_frame_flash_cycle_duration:
			i_frame_animation_timer -= i_frame_flash_cycle_duration
	
		sprite.modulate = Color.WHITE if i_frame_animation_timer > i_frame_flash_cycle_duration * 0.5 else Color.BLUE
	
	# blarg
	match player_ability:
		PLAYER_ABILITY.NORMAL:
			$TrailingStar.rotation += 1.5 * delta
			double_star_animation_timer += delta * 5.0
			while double_star_animation_timer >= 4.0:
				double_star_animation_timer -= 4.0
			$TrailingStar/Double.frame = int(double_star_animation_timer)
		PLAYER_ABILITY.PARASOL:
			parasol_animation_frame += delta * 30.0
			if parasol_animation_frame >= 4.0:
				parasol_animation_frame -= 4.0
			$Parasol/Shield.frame = int(parasol_animation_frame)
		PLAYER_ABILITY.SPARK:
			var shield_visible := spark_charge_level >= spark_charge_level_thresholds[1]
			$Plasma/ShieldUnder.visible = shield_visible
			$Plasma/ShieldOver.visible = shield_visible
			var spark_visible := spark_charge_level >= spark_charge_level_thresholds[0] and not shield_visible
			$Plasma/Spark.visible = spark_visible
			var last_frame := int(spark_animation_timer)
			spark_animation_timer += delta * 10.0
			while spark_animation_timer >= 2.0:
				spark_animation_timer -= 2.0
			var current_frame := int(spark_animation_timer)
			if last_frame != current_frame:
				var shield_angle := randf()*TAU
				$Plasma/ShieldUnder.frame = current_frame
				$Plasma/ShieldOver.frame = current_frame
				$Plasma/Spark.frame = current_frame
				$Plasma/ShieldUnder.rotation = shield_angle
				$Plasma/ShieldOver.rotation = shield_angle
				$Plasma/Spark.rotation = shield_angle
		PLAYER_ABILITY.BOOMER:
			$Boomer/AimRotator/Front.rotate(delta * 1.5)
			$Boomer/AimRotator/Back.rotate(delta * 1.5)
			
func reset_sprite_modulation() -> void:
	sprite.modulate = Color.WHITE


## Checks collisions for bullets and items and acts accordingly,
func collision(time_scale) -> void:
	if current_i_frames > 0.0:
		current_i_frames -= time_scale
	if current_i_frames <= 0.0:
		current_i_frames = 0.0
		reset_sprite_modulation()
		
	#if current_i_frames == 0.0:
	var hitbox_size := hitbox_radius if parry_timer <= 0.0 else graze_radius * 0.25
	var collisions = Bullets.collide_and_graze_player(position, hitbox_size, graze_radius)

	if position.y < autocollect_height:
		Bullets.magnet_all_items(self)
		pass
	
	#var should_magnet := true if magnet_while_unfocused else is_focused
	
	var items : Array = Bullets.collect_and_magnet_items(
		position, 
		self, 
		item_collect_radius, 
		focus_item_magnet_radius if is_focused else unfocus_item_magnet_radius
	)
	
	collect_items(items)
	
	
	
	if len(collisions[0]) > 0:
		
		if player_ability == PLAYER_ABILITY.SWORD and parry_timer >= 0.0:
			SFX.play("parry_success")
			parry_timer = -1.0
			parry_cooldown_timer = parry_success_cooldown
			parry_success = true
			current_i_frames = 60.0
			$Sword/Parry.hide()
			$Sword/ParryAnimator.stop()
			
			Bullets.clear_bullets(position, 128.0, false)
		elif current_i_frames <= 0.0:
			hit()
		
	if len(collisions[1]) > 0:
		SFX.play("graze")
		if player_ability == PLAYER_ABILITY.SPARK:
			SFX.play("plasma_charge")
			spark_graze_buffer = min(spark_graze_buffer_max, len(collisions[1]))
			#spark_transfer_buffer += len(collisions[1])
	


## Tells the associated [class ShooterManager] to shoot.
func shooting(time_scale: float) -> void:
	if GameInput.is_action_pressed(&"player_custom_0") and not System.in_dialogue and player_ability != PLAYER_ABILITY.NORMAL and player_ability != PLAYER_ABILITY.STARROD:
		SFX.play("discard")
		change_ability(PLAYER_ABILITY.NORMAL)
		return
	
	var shoot_pressed : bool = GameInput.is_action_pressed(&"player_shoot") and not System.in_dialogue
	var bomb_pressed : bool = GameInput.is_action_pressed(&"player_bomb") and not System.in_dialogue
	var shoot_just_pressed : bool = GameInput.is_action_just_pressed(&"player_shoot") and not System.in_dialogue
	var bomb_just_pressed : bool = GameInput.is_action_just_pressed(&"player_bomb") and not System.in_dialogue
	
	match player_ability:
		PLAYER_ABILITY.NORMAL:
			if suck_endlag_timer > 0:
				suck_endlag_timer -= 1
			if spit_endlag_timer > 0:
				spit_endlag_timer -= 1
			if minimum_suck_timer > 0:
				minimum_suck_timer -= 1
			
			# Regular
			if not is_swallowing:
				var prev_player_attacking := player_attacking
				
				# Require the player to let go of shoot to spit or suck
				if not shoot_pressed:
					fire_released_since_suck_or_spit = true
				
				# Check if we tried to swallow
				if bomb_pressed and item_in_mouth and suck_endlag_timer <= 0:
					item_in_mouth = false
					SFX.play(&"gulp")
					spit_endlag_timer = spit_endlag_time
					is_swallowing = true
					attack_power = 0
					swallow_timer = swallow_time
					$TrailingStarAnimation.play("remove")
				# Then check if we tried to spit out
				elif shoot_pressed and item_in_mouth and suck_endlag_timer <= 0 and fire_released_since_suck_or_spit:
					item_in_mouth = false
					fire_released_since_suck_or_spit = false
					var bullet_type := super_spit_attack if attack_power > 1 else spit_attack
					var speed := 20.0 if attack_power > 1 else 16.0
					var b : PackedInt64Array = Bullets.create_shot_a1(position, speed, PI * -0.5, bullet_type, false)
					if attack_power > 1:
						Bullets.set_pierce(b, true)
						#Bullets.set_damage(b, 100 + (attack_power - 1) * 50)
						#Bullets.set_damage(b, 150)
						SFX.play(&"superspit")
					else:
						SFX.play(&"spit")
					spit_endlag_timer = spit_endlag_time
					attack_power = 0
					$TrailingStarAnimation.play("remove")
				# Then deal with sucking logic
				else:
					if shoot_pressed and not item_in_mouth and  not prev_player_attacking and spit_endlag_timer <= 0 and fire_released_since_suck_or_spit:
						player_attacking = true
						#forced_slowdown = true # I don't actually like how this feelns
						minimum_suck_timer = minimum_suck_time
						$tornado/AnimationPlayer.play(&"spawn")
						SFX.play("suck")
					elif (not shoot_pressed or item_in_mouth) and (
						prev_player_attacking and not forced_sucking and minimum_suck_timer <= 0):
						player_attacking = false
						forced_slowdown = false
						fire_released_since_suck_or_spit = false
						$tornado/AnimationPlayer.play_backwards(&"spawn")
						SFX.stop("suck", 0.2)
							
					if player_attacking:
						var b : PackedInt64Array = Bullets.create_shot_a1(
							position + Vector2(0, -128),
							0.0, 0.0, suction_collision, false
						)
						Bullets.set_lifespan(b, 2)
			# Swallow logic
			if is_swallowing:
				if swallow_timer > 0:
					swallow_timer -= 1
				if swallow_timer <= 0:
					swallow_timer = 0
					SFX.play("powerup")
					is_swallowing = false
					# Grant ability
					change_ability(ability_in_mouth)
					ability_in_mouth = PLAYER_ABILITY.NORMAL
		
		PLAYER_ABILITY.FREEZE:
			if freeze_timer > 0.0:
				freeze_timer -= System.time_scale
			if freeze_timer <= 0.0 and shoot_pressed:
				freeze_timer = freeze_cooldown
				var b = Bullets.create_shot_a2(position, randf_range(16, 20), PI * randf_range(-0.55, -0.45), -0.25, 6.0, 0.0, frost_breath, true)
				Bullets.set_rotation(b, randf()*TAU)
				Bullets.set_lifespan(b, 20)
				Bullets.set_spin(b, randf_range(-0.1, 0.1))
		
		PLAYER_ABILITY.BOOMER:
			# Aiming
			if not is_focused and not System.in_dialogue and desired_direction.length_squared() > 0.0:
				# akdasreniotsnan
				var sensitivity : float = 0.1
				var max_angle_change : float = 0.15
				
				var desired_angle := desired_direction.angle() + PI
				# A factor is applied based off how parallel the desired angle and the current angle are.
				# This makes small adjustments snappier as their absolute dot product higher than if perpendicular.
				# Doing this gives us a snappy feel for both smaller adjustments and for 180° turnarounds,
				# while giving some feeling of weight for turn directions in-between.
				# Factor is offset by 1.0 to make it possible to turn at all
				var factor : float = sensitivity + abs(
					Vector2.RIGHT.rotated(boomer_angle).dot(Vector2.RIGHT.rotated(desired_angle))
				)
				# The angle is determined by modelling a "trail" and "lead" that the options try to face towards.
				# This approach is greatly inspired by IN Youmu's shottype which I consider to be the perfect implementation of it.
				var trail_anchor : Vector2 = Vector2.LEFT.rotated(boomer_angle)
				var lead_anchor : Vector2 = Vector2(factor, 0).rotated(desired_angle)
				var target_angle := trail_anchor.angle_to_point(lead_anchor)
				
				var desired_target_angle_difference : float = target_angle - desired_angle
				if desired_target_angle_difference < -PI:
					desired_target_angle_difference += TAU
				if desired_target_angle_difference > PI:
					desired_target_angle_difference -= TAU
				
				
				if abs(desired_target_angle_difference) <= max_angle_change * System.time_scale:
					boomer_angle = target_angle
				else:
					var current_target_angle_difference : float = target_angle - boomer_angle
					# Bound it first
					if current_target_angle_difference < -PI:
						current_target_angle_difference += TAU
					if current_target_angle_difference > PI:
						current_target_angle_difference -= TAU
					# Check direction
					if current_target_angle_difference > 0.0:
						boomer_angle += max_angle_change
					else:
						boomer_angle -= max_angle_change
					# Bring boomer angle back to [-PI, PI]
					if boomer_angle < -PI:
						boomer_angle += TAU
					if boomer_angle > PI:
						boomer_angle -= TAU
				$Boomer/AimRotator.rotation = boomer_angle
			
			
			# Firing
			if boomer_fire_timer > 0.0:
				boomer_fire_timer -= time_scale
			
			if not System.in_dialogue:
				var shots_fired := false
				var invert := 0.0
				var fire_position := position
				
				
				if shoot_pressed:
					shots_fired = true
					fire_position += Vector2(80, 0).rotated(boomer_angle)
				elif bomb_pressed:
					shots_fired = true
					invert = PI
					fire_position += Vector2(-80, 0).rotated(boomer_angle)
				
				var aim_assist_threshold := TAU / 16.0
				
				var angle_to_boss : float = boomer_angle
				if System.current_boss:
					angle_to_boss = position.angle_to_point(System.current_boss.position)
				
				var shoot_angle := boomer_angle + invert
				
				if abs(angle_difference(angle_to_boss, (boomer_angle + invert))) < aim_assist_threshold or abs(angle_difference(angle_to_boss, boomer_angle)) < aim_assist_threshold:
					shoot_angle = angle_to_boss + invert
				
				

				if shots_fired and boomer_fire_timer <= 0.0:
					SFX.play("slash_air")
					boomer_fire_timer = boomer_fire_rate
					var b = Bullets.create_shot_a2(
						fire_position,
						boomer_initial_velocity,
						shoot_angle,
						-boomer_initial_velocity / boomer_travel_time,
						-boomer_max_velocity,
						0.0,
						boomer_bullet,
						false
					)
					Bullets.set_pierce(b, true)
					Bullets.set_lifespan(b, boomer_travel_time)
					# s = ut + 0.5*at^2
					# s = 
					var rebound_position = fire_position + (
						Vector2(boomer_initial_velocity - boomer_initial_velocity / boomer_travel_time * 0.5, 0.0).rotated(shoot_angle) * boomer_travel_time + 
						0.5 * Vector2(-boomer_initial_velocity / boomer_travel_time, 0.0).rotated(shoot_angle) * boomer_travel_time * boomer_travel_time
					)
					outgoing_boomerang_positions.append(rebound_position)
					outgoing_boomerang_angles.append(shoot_angle)
					outgoing_timers.append(boomer_travel_time)
			
			# Rebounding
			var i := outgoing_boomerang_positions.size() - 1
			while i >= 0:
				outgoing_timers[i] -= System.time_scale
				if outgoing_timers[i] <= 0.0:
					SFX.play("slash_air")
					var b = Bullets.create_shot_a2(
						outgoing_boomerang_positions[i],
						0.0,
						outgoing_boomerang_angles[i],
						-boomer_initial_velocity / boomer_travel_time,
						-boomer_max_velocity,
						0.0,
						boomer_return_bullet,
						false
					)
					Bullets.set_pierce(b, true)
					
					outgoing_boomerang_positions.remove_at(i)
					outgoing_boomerang_angles.remove_at(i)
					outgoing_timers.remove_at(i)
				i -= 1
		
		PLAYER_ABILITY.PARASOL:
			match parasol_state:
				PARASOL_STATE.DEPLOYING:
					parasol_timer += time_scale
					if parasol_timer >= parasol_shield_frame:
						parasol_state = PARASOL_STATE.FORCE_DEPLOYED
				PARASOL_STATE.FORCE_DEPLOYED:
					parasol_timer += time_scale
					if parasol_timer >= parasol_deploy_min_time:
						parasol_state = PARASOL_STATE.DEPLOYED
						
					parasol_block_bullets()
					
				PARASOL_STATE.DEPLOYED:
					parasol_timer += time_scale
					if not shoot_pressed:
						parasol_state = PARASOL_STATE.HOLSTERING
						$Parasol/ShieldAnimation.play("holster")
						forced_slowdown = false
						parasol_timer = 0.0
					parasol_block_bullets()
					
				PARASOL_STATE.HOLSTERING:
					parasol_timer += time_scale
					if parasol_timer >= parasol_holster_min_time:
						parasol_state = PARASOL_STATE.HOLSTERED
						parasol_timer = 0.0
				
				PARASOL_STATE.HOLSTERED:
					if shoot_pressed:
						parasol_state = PARASOL_STATE.DEPLOYING
						$Parasol/ShieldAnimation.play("deploy")
						forced_slowdown = true
						Bullets.clear_bullets(position, 64, false) # Instant clear around the player 
						for i in 15:
							var pos_rand : float = randf_range(-1, 1)
							#68, 23
							var pos : Vector2 = position + Vector2(0, -108) + Vector2(48 * pos_rand, 24 * abs(pos_rand))
							var b = Bullets.create_shot_a1(
								pos,
								randf_range(5.0, 20.0),
								-PI * 0.5 + randf_range(-0.25, 0.25) * PI,
								droplet,
								false
							)
							Bullets.set_lifespan(b, randf_range(6, 10))
							SFX.play("shotgun")
						for i in 15:
							var pos_rand : float = randf_range(-1, 1)
							#68, 23
							var pos : Vector2 = position + Vector2(0, -108) + Vector2(48 * pos_rand, 24 * abs(pos_rand))
							var b = Bullets.create_shot_a1(
								pos,
								randf_range(20.0, 40.0),
								-PI * 0.5 + randf_range(-0.1, 0.1) * PI,
								droplet,
								false
							)
							Bullets.set_lifespan(b, randf_range(6, 10))
							SFX.play("shotgun")
						for i in 15:
							var pos_rand : float = randf_range(-1, 1)
							#68, 23
							var pos : Vector2 = position + Vector2(0, -108) + Vector2(48 * pos_rand, 24 * abs(pos_rand))
							var b = Bullets.create_shot_a1(
								pos,
								randf_range(40.0, 50.0),
								-PI * 0.5 + randf_range(-0.05, 0.05) * PI,
								droplet,
								false
							)
							Bullets.set_lifespan(b, randf_range(6, 10))
							SFX.play("shotgun")
			
		PLAYER_ABILITY.SPARK:
			#print(spark_charge_level)?
			if not System.in_dialogue:
				# Buffer 1, limit how much we can mash to charge
				var frame_increase := 0
				if GameInput.is_action_just_pressed("player_left"):
					frame_increase += 1
				elif GameInput.is_action_just_pressed("player_right"):
					frame_increase += 1
				if GameInput.is_action_just_pressed("player_up"):
					frame_increase += 1
				elif GameInput.is_action_just_pressed("player_down"):
					frame_increase += 1
				if frame_increase > 0:
					SFX.play("plasma_charge")
					spark_input_buffer += frame_increase
				
				if spark_input_buffer > spark_input_buffer_max:
					spark_input_buffer = spark_input_buffer_max
				
				if spark_transfer_timer > 0.0:
					spark_transfer_timer -= 1.0
				if spark_transfer_timer <= 0.0 and spark_input_buffer > 0:
					spark_transfer_timer += spark_transfer_rate
					spark_input_buffer -= 1
					spark_transfer_buffer += 2
					
				if spark_graze_transfer_timer > 0.0:
					spark_graze_transfer_timer -= 1.0
				if spark_graze_transfer_timer <= 0.0 and spark_graze_buffer > 0:
					spark_graze_transfer_timer += spark_graze_transfer_rate
					spark_graze_buffer -= 1
					spark_transfer_buffer += 1	
				
				
				# Buffer 3, we only transfer over charge on button press
				if frame_increase > 0:
					var prev_level := spark_charge_level
					spark_charge_level += spark_transfer_buffer
					spark_decay_timer = spark_decay_rate
					spark_transfer_buffer = 0
					if spark_charge_level >= spark_charge_level_thresholds[1] and prev_level < spark_charge_level_thresholds[1]:
						spark_charge_level = spark_charge_level_thresholds[1] + 8
					spark_charge_level = min(spark_charge_level, spark_charge_level_thresholds[1] + 8)
				
				# Decay
				if spark_decay_timer > 0.0:
					spark_decay_timer -= 1.0
					
				if spark_decay_timer <= 0.0:
					spark_decay_timer += spark_decay_rate
					if spark_charge_level > 0:
						spark_charge_level -= 1
				
				# Shooting
				if spark_fire_timer > 0.0:
					spark_fire_timer -= 1.0
					
				if shoot_just_pressed and spark_fire_timer <= 0.0:
					spark_fire_timer = spark_fire_rate
					var i := 0
					for threshold in spark_charge_level_thresholds:
						if spark_charge_level >= threshold:
							i += 1
							continue
						break
					SFX.play(spark_charge_sfx[i])
					var b = Bullets.create_shot_a1(
						position,
						spark_speeds[i],
						PI * -0.5,
						spark_bullets[i],
						true
					)
					Bullets.set_lifespan(b, spark_lifespans[i])
					Bullets.set_pierce(b, spark_pierce[i])
					spark_charge_level = 0
					if spark_charge_level >= spark_charge_level_thresholds[1]:
						Bullets.skip_fade(b)
				
				if spark_charge_level >= spark_charge_level_thresholds[1]:
					var b = Bullets.create_shot_a1(position, 0.0, 0.0, spark_shield_bullet, 0.0)
					Bullets.set_lifespan(b, 2)
					Bullets.set_pierce(b, true)
					
		PLAYER_ABILITY.BOMB:
			match bomb_state:
				BOMB_STATE.IDLE:
					if bomb_cooldown_timer > 0.0:
						bomb_cooldown_timer -= time_scale
					if bomb_cooldown_timer <= 0.0:
						# Start charging bomb
						if shoot_pressed and not last_bomb_released:
							SFX.play("charge_bomb")
							last_bomb_released = true
							$Bomb/ChargeBar.show()
							bomb_state = BOMB_STATE.CHARGING
				BOMB_STATE.CHARGING:
					# Cook Bomb
					if shoot_pressed and last_bomb_released:
						bomb_charge_timer += time_scale
						$Bomb/ChargeBar/Progress.value = bomb_charge_timer / bomb_charge_time
				
					# Throw Bomb
					if not shoot_pressed or bomb_charge_timer > bomb_charge_time:
						SFX.stop("charge_bomb")
						SFX.play("donk")
						bomb_state = BOMB_STATE.IDLE
						$Bomb/ChargeBar.hide()
						var bomb : Node2D = bomb_prefab.instantiate()
						bomb.position = position
						bomb.lifespan = 10.0 + 50.0 * (1.0 - bomb_charge_timer / bomb_charge_time)
						if bomb_charge_timer > bomb_charge_time:
							bomb.lifespan = 0.0
						get_parent().add_child(bomb)
						bomb_charge_timer = 0.0
						last_bomb_released = false
						bomb_cooldown_timer = bomb_cooldown_time
			
		PLAYER_ABILITY.SNIPER:
			# Moving scope around
			var held : bool = shoot_pressed or bomb_pressed
			if held and active_reload_timer == 0 and not active_reload_repress:
				# First frame place scope
				if scope_timer == 0:
					scope_position = position + Vector2(randf_range(50.0, 100.0), 0.0).rotated(randf()*TAU)
					scope.show()
				
				# Control scope
				var scope_progress : float = clamp(float(scope_timer) / float(scope_time), 0.0, 1.0)
				
				var interpolated_scope_move_speed = noscope_move_speed * (1.0 - scope_progress) + scope_move_speed * scope_progress
				scope_position += desired_direction * interpolated_scope_move_speed
				scope_position.x = clamp(scope_position.x, 24, 1000 - 24)
				scope_position.y = clamp(scope_position.y, 24, 1000 - 24)
				
				scope.scale = Vector2.ONE * (1.0 + (scope_start_zoom - 1.0) * (1.0 - scope_progress))
				scope.modulate.a = scope_progress * scope_final_opacity
				scope.rotation = scope_position.angle_to_point(position)
				
				scope_timer += 1
				scope.position = scope_position - position
			# Firing
			elif !held && active_reload_timer == 0:
				# not held enough
				if scope_timer <= scope_minimum_start:
					scope.hide()
					scope_timer = 0
				# helnd enough
				else:
					var b : PackedInt64Array = Bullets.create_shot_a1(
						scope_position,
						0.0, 0.0, snipe_bullet, false
					)
					Bullets.set_lifespan(b, 2)
					Bullets.set_pierce(b, true)
					
					scope_timer = 0
					scope.hide()
					SFX.play("snipe")
					active_reload_timer = 1
					reload_bar.show()
					active_reload_region.show()
					active_reload_attempted = false
				
			if active_reload_timer > 0: # Reloading
				var pressed : bool = shoot_just_pressed or bomb_just_pressed
				
				if pressed and !active_reload_attempted:
					active_reload_attempted = true
					
					active_reload_repress = true
					
					if active_reload_timer >= active_reload_minimum and active_reload_timer <= active_reload_maximum:
						active_reload_timer = 999
						SFX.play("reload")
					else:
						active_reload_region.hide()
						SFX.play("fail")
						
				if active_reload_timer >= active_reload_duration:
					active_reload_timer = 0
					reload_bar.hide()
					
				else:
					reload_bar_progress.value = active_reload_timer
					active_reload_timer += 1
					
			if active_reload_repress: # Prevent instant zoom in after active reload
				if !held:
					active_reload_repress = false
		
		PLAYER_ABILITY.SWORD:
			if sword_timer > 0.0:
				sword_timer -= System.time_scale
			if shoot_pressed and sword_timer <= 0.0:
				slash_lr *= -1.0
				SFX.play("slash_air")
				sword_timer = stab_cooldown if is_focused else slash_cooldown
				var slash := stab_prefab.instantiate() if is_focused else slash_prefab.instantiate()
				slash.position = position + Vector2(0, -128 if is_focused else -96)
				slash.scale.x = slash_lr
				slash.damage = 18 if is_focused else 8
				get_parent().add_child(slash)
			
			if parry_timer >= 0.0: # 1 frame leeway
				parry_timer -= System.time_scale
			if parry_timer < 0.0 and not parry_success:
				parry_cooldown_timer = parry_cooldown
				parry_success = true
				$Sword/ChargeBar.show()
			
			if parry_cooldown_timer > 0.0:
				parry_cooldown_timer -= System.time_scale
				$Sword/ChargeBar/Progress.value = parry_cooldown_timer / parry_cooldown
			if parry_cooldown_timer <= 0.0:
				$Sword/ChargeBar.hide()
				if bomb_just_pressed:
					if deathbomb_timer > 0.0 and false:
						deathbomb_timer = 0.0
						SFX.play("parry_success")
						parry_timer = -1.0
						parry_cooldown_timer = -1.0
						parry_success = true
						current_i_frames = 60.0
						$Sword/Parry.hide()
					else:
						parry_timer = parry_duration
						parry_cooldown_timer = parry_duration + 1.0
						$Sword/Parry.show()
						$Sword/ParryAnimator.play("parry")
						SFX.play("parry")
						parry_success = false
			
			
			
		PLAYER_ABILITY.STARROD:
			if star_rod_timer > 0.0:
				star_rod_timer -= System.time_scale
			if shoot_pressed and star_rod_timer <= 0.0:
				star_rod_timer = star_rod_fire_rate
				var b = Bullets.create_shot_a1(position, 16.0, PI * -0.5, spit_attack, false)
				Bullets.set_damage(b, 10)
				#SFX.play(&"spit") # Too annoynig
					
		
		
## Performs tasks involved with the player dying.
func dying(_time_scale: float) -> void:
	if deathbomb_timer > 0.0:
		deathbomb_timer -= System.time_scale
		if deathbomb_timer <= 0.0:
			deathbomb_timer = 0.0
			die()
	

#endregion

#region Tool Functions

func _update_hframes():
	sprite.hframes = max(idle_animation_frame_count, move_animation_frame_count)

#endregion

#region Overrides
func _ready() -> void:
	
	System.register_player(self)
	#
	#player_ability = System.player_starting_ability
	change_ability(System.player_starting_ability)
	
	if spawn_with_invulnerability:
		current_i_frames = respawn_i_frames
	
	if shooter_manager_path:
		shooter_manager = get_node(shooter_manager_path)
	else:
		print("Shooter Manager Path failed, using first child instead.")
		shooter_manager = get_child(0)
	
	RNG.randomize_seed()
	
	# Game specific stuff
	suction_collision = PackedFloat64Array()
	suction_collision.resize(15)
	suction_collision[0] = 0 # source x (integer)
	suction_collision[1] = 0 # source y (integer)
	suction_collision[2] = 0				# source width (integer)
	suction_collision[3] = 0				# source height (integer)
	suction_collision[4] = 96				# bullet size [0, inf)
	suction_collision[5] = 1 				# hitbox ratio [0, 1]
	suction_collision[6] = 0					# Sprite offset y (integer)
	suction_collision[7] = 1					# anim frame, 1 for no animation (integer)
	suction_collision[8] = 0					# spin
	suction_collision[9] = 1	# layer
	suction_collision[10] = 1	# rgb
	suction_collision[11] = 1
	suction_collision[12] = 1
	suction_collision[13] = System.DAMAGE_TYPE.SUCK				# damage type
	suction_collision[14] = 0				# damage amount
	
	spit_attack = PackedFloat64Array()
	spit_attack.resize(15)
	spit_attack[0] = 0 # source x (integer)
	spit_attack[1] = 0 # source y (integer)
	spit_attack[2] = 128				# source width (integer)
	spit_attack[3] = 128				# source height (integer)
	spit_attack[4] = 96				# bullet size [0, inf)
	spit_attack[5] = 0 				# hitbox ratio [0, 1]
	spit_attack[6] = 0					# Sprite offset y (integer)
	spit_attack[7] = 1					# anim frame, 1 for no animation (integer)
	spit_attack[8] = 0.1					# spin
	spit_attack[9] = 1	# layer
	spit_attack[10] = 1	# rgb
	spit_attack[11] = 1
	spit_attack[12] = 1
	spit_attack[13] = System.DAMAGE_TYPE.STAR			# damage type
	spit_attack[14] = 100				# damage amount
	
	super_spit_attack = PackedFloat64Array()
	super_spit_attack.resize(15)
	super_spit_attack[0] = 0 # source x (integer)
	super_spit_attack[1] = 128 # source y (integer)
	super_spit_attack[2] = 128 				# source width (integer)
	super_spit_attack[3] = 128				# source height (integer)
	super_spit_attack[4] = 128 + 32				# bullet size [0, inf)
	super_spit_attack[5] = 0.5 				# hitbox ratio [0, 1]
	super_spit_attack[6] = 0					# Sprite offset y (integer)
	super_spit_attack[7] = 4					# anim frame, 1 for no animation (integer)
	super_spit_attack[8] = 0.1					# spin
	super_spit_attack[9] = 1	# layer
	super_spit_attack[10] = 1	# rgb
	super_spit_attack[11] = 1
	super_spit_attack[12] = 1
	super_spit_attack[13] = System.DAMAGE_TYPE.STAR_STRONG				# damage type
	super_spit_attack[14] = 100				# damage amount
	
	snipe_bullet = PackedFloat64Array()
	snipe_bullet.resize(15)
	snipe_bullet[0] = 0 # source x (integer)
	snipe_bullet[1] = 0 # source y (integer)
	snipe_bullet[2] = 0 				# source width (integer)
	snipe_bullet[3] = 0				# source height (integer)
	snipe_bullet[4] = 36				# bullet size [0, inf)
	snipe_bullet[5] = 1 				# hitbox ratio [0, 1]
	snipe_bullet[6] = 0					# Sprite offset y (integer)
	snipe_bullet[7] = 1					# anim frame, 1 for no animation (integer)
	snipe_bullet[8] = 0.1					# spin
	snipe_bullet[9] = 1	# layer
	snipe_bullet[10] = 1	# rgb
	snipe_bullet[11] = 1
	snipe_bullet[12] = 1
	snipe_bullet[13] = System.DAMAGE_TYPE.CRIT				# damage type
	snipe_bullet[14] = 80				# damage amount
	
	frost_breath = PackedFloat64Array()
	frost_breath.resize(15)
	frost_breath[0] = 0 # source x (integer)
	frost_breath[1] = 128*3 # source y (integer)
	frost_breath[2] = 128 				# source width (integer)
	frost_breath[3] = 128				# source height (integer)
	frost_breath[4] = 96				# bullet size [0, inf)
	frost_breath[5] = 0.75 				# hitbox ratio [0, 1]
	frost_breath[6] = 0					# Sprite offset y (integer)
	frost_breath[7] = 1					# anim frame, 1 for no animation (integer)
	frost_breath[8] = 0					# spin
	frost_breath[9] = 1	# layer
	frost_breath[10] = 1	# rgb
	frost_breath[11] = 1
	frost_breath[12] = 1
	frost_breath[13] = System.DAMAGE_TYPE.CHILL			# damage type
	frost_breath[14] = 5				# damage amount
	
	
	droplet = PackedFloat64Array()
	droplet.resize(15)
	droplet[0] = 128 # source x (integer)
	droplet[1] = 0 # source y (integer)
	droplet[2] = 128				# source width (integer)
	droplet[3] = 128				# source height (integer)
	droplet[4] = 32				# bullet size [0, inf)
	droplet[5] = 0.5 				# hitbox ratio [0, 1]
	droplet[6] = 0					# Sprite offset y (integer)
	droplet[7] = 1					# anim frame, 1 for no animation (integer)
	droplet[8] = 0					# spin
	droplet[9] = 1	# layer
	droplet[10] = 1	# rgb
	droplet[11] = 1
	droplet[12] = 1
	droplet[13] = System.DAMAGE_TYPE.NORMAL			# damage type
	droplet[14] = 1			# damage amount
	
	
	canopy_damage = PackedFloat64Array()
	canopy_damage.resize(15)
	canopy_damage[0] = 0 # source x (integer)
	canopy_damage[1] = 0 # source y (integer)
	canopy_damage[2] = 0				# source width (integer)
	canopy_damage[3] = 0				# source height (integer)
	canopy_damage[4] = 48				# bullet size [0, inf)
	canopy_damage[5] = 1 				# hitbox ratio [0, 1]
	canopy_damage[6] = 0					# Sprite offset y (integer)
	canopy_damage[7] = 1					# anim frame, 1 for no animation (integer)
	canopy_damage[8] = 0					# spin
	canopy_damage[9] = 1	# layer
	canopy_damage[10] = 1	# rgb
	canopy_damage[11] = 1
	canopy_damage[12] = 1
	canopy_damage[13] = System.DAMAGE_TYPE.CANOPY				# damage type
	canopy_damage[14] = 2				# damage amount
	
	spark_bullets.append(PackedFloat64Array())
	spark_bullets[0].resize(15)
	spark_bullets[0][0] = 256 # source x (integer)
	spark_bullets[0][1] = 0 # source y (integer)
	spark_bullets[0][2] = 128				# source width (integer)
	spark_bullets[0][3] = 128				# source height (integer)
	spark_bullets[0][4] = 96				# bullet size [0, inf)
	spark_bullets[0][5] = 0.25 				# hitbox ratio [0, 1]
	spark_bullets[0][6] = 0					# Sprite offset y (integer)
	spark_bullets[0][7] = 1					# anim frame, 1 for no animation (integer)
	spark_bullets[0][8] = 0					# spin
	spark_bullets[0][9] = 1	# layer
	spark_bullets[0][10] = 1	# rgb
	spark_bullets[0][11] = 1
	spark_bullets[0][12] = 1
	spark_bullets[0][13] = System.DAMAGE_TYPE.SHOCK			# damage type
	spark_bullets[0][14] = 8				# damage amount

	spark_bullets.append(PackedFloat64Array())
	spark_bullets[1].resize(15)
	spark_bullets[1][0] = 0 # source x (integer)
	spark_bullets[1][1] = 256 # source y (integer)
	spark_bullets[1][2] = 128				# source width (integer)
	spark_bullets[1][3] = 128				# source height (integer)
	spark_bullets[1][4] = 96 * 2				# bullet size [0, inf)
	spark_bullets[1][5] = 0.33 				# hitbox ratio [0, 1]
	spark_bullets[1][6] = 0					# Sprite offset y (integer)
	spark_bullets[1][7] = 2					# anim frame, 1 for no animation (integer)
	spark_bullets[1][8] = 0					# spin
	spark_bullets[1][9] = 1	# layer
	spark_bullets[1][10] = 1	# rgb
	spark_bullets[1][11] = 1
	spark_bullets[1][12] = 1
	spark_bullets[1][13] = System.DAMAGE_TYPE.SHOCK			# damage type
	spark_bullets[1][14] = 25				# damage amount

	spark_bullets.append(PackedFloat64Array())
	spark_bullets[2].resize(15)
	spark_bullets[2][0] = 256 # source x (integer)
	spark_bullets[2][1] = 256 # source y (integer)
	spark_bullets[2][2] = 128				# source width (integer)
	spark_bullets[2][3] = 128				# source height (integer)
	spark_bullets[2][4] = 256				# bullet size [0, inf)
	spark_bullets[2][5] = 0.5 				# hitbox ratio [0, 1]
	spark_bullets[2][6] = 0					# Sprite offset y (integer)
	spark_bullets[2][7] = 2					# anim frame, 1 for no animation (integer)
	spark_bullets[2][8] = 0				# spin
	spark_bullets[2][9] = 1	# layer
	spark_bullets[2][10] = 1	# rgb
	spark_bullets[2][11] = 1
	spark_bullets[2][12] = 1
	spark_bullets[2][13] = System.DAMAGE_TYPE.SHOCK			# damage type
	spark_bullets[2][14] = 70				# damage amount
	
		
	spark_shield_bullet = PackedFloat64Array()
	spark_shield_bullet.resize(15)
	spark_shield_bullet[0] = 0 # source x (integer)
	spark_shield_bullet[1] = 0 # source y (integer)
	spark_shield_bullet[2] = 0				# source width (integer)
	spark_shield_bullet[3] = 0				# source height (integer)
	spark_shield_bullet[4] = 72				# bullet size [0, inf)
	spark_shield_bullet[5] = 1 				# hitbox ratio [0, 1]
	spark_shield_bullet[6] = 0					# Sprite offset y (integer)
	spark_shield_bullet[7] = 1					# anim frame, 1 for no animation (integer)
	spark_shield_bullet[8] = 0					# spin
	spark_shield_bullet[9] = 1	# layer
	spark_shield_bullet[10] = 1	# rgb
	spark_shield_bullet[11] = 1
	spark_shield_bullet[12] = 1
	spark_shield_bullet[13] = System.DAMAGE_TYPE.SHOCK_SHIELD				# damage type
	spark_shield_bullet[14] = 2				# damage amount
	
	boomer_bullet = PackedFloat64Array()
	boomer_bullet.resize(15)
	boomer_bullet[0] = 128*3 # source x (integer)
	boomer_bullet[1] = 0 # source y (integer)
	boomer_bullet[2] = 128				# source width (integer)
	boomer_bullet[3] = 128				# source height (integer)
	boomer_bullet[4] = 128				# bullet size [0, inf)
	boomer_bullet[5] = 0.75 				# hitbox ratio [0, 1]
	boomer_bullet[6] = 0					# Sprite offset y (integer)
	boomer_bullet[7] = 1					# anim frame, 1 for no animation (integer)
	boomer_bullet[8] = -TAU / boomer_travel_time					# spin
	boomer_bullet[9] = 1	# layer
	boomer_bullet[10] = 1	# rgb
	boomer_bullet[11] = 1
	boomer_bullet[12] = 1
	boomer_bullet[13] = System.DAMAGE_TYPE.SHARP			# damage type
	boomer_bullet[14] = 5				# damage amount	
	
	boomer_return_bullet = PackedFloat64Array()
	boomer_return_bullet.resize(15)
	boomer_return_bullet[0] = 128*3 # source x (integer)
	boomer_return_bullet[1] = 0 # source y (integer)
	boomer_return_bullet[2] = 128				# source width (integer)
	boomer_return_bullet[3] = 128				# source height (integer)
	boomer_return_bullet[4] = 128				# bullet size [0, inf)
	boomer_return_bullet[5] = 0.75 				# hitbox ratio [0, 1]
	boomer_return_bullet[6] = 0					# Sprite offset y (integer)
	boomer_return_bullet[7] = 1					# anim frame, 1 for no animation (integer)
	boomer_return_bullet[8] = -TAU / boomer_travel_time					# spin
	boomer_return_bullet[9] = 1	# layer
	boomer_return_bullet[10] = 1	# rgb
	boomer_return_bullet[11] = 1
	boomer_return_bullet[12] = 1
	boomer_return_bullet[13] = System.DAMAGE_TYPE.SHARP			# damage type
	boomer_return_bullet[14] = 25				# damage amount
	
	
	update_ability_text()

## Main logic goes in _process, do not use _physics_process
func _process(delta: float) -> void:
	animation(delta)
	var time_scale : float = System.time_scale
	movement(time_scale)
	collision(time_scale)
	shooting(time_scale)
	dying(time_scale)
	
#endregion

func declare_eated():
	forced_sucking = true
	suck_endlag_timer = suck_endlag_time

func update_ability_text():
	System.ui.update_name(ABILITY_STRINGS[player_ability])

func update_ability_visibility():
	match player_ability:
		PLAYER_ABILITY.NORMAL:
			$Sniper.hide()
			$Bomb.hide()
			$Sword.hide()
			$Parasol.hide()
			$Plasma.hide()
			$Boomer.hide()
		PLAYER_ABILITY.BOOMER:
			$Sniper.hide()
			$Bomb.hide()
			$Sword.hide()
			$Parasol.hide()
			$Plasma.hide()
			$Boomer.show()
		PLAYER_ABILITY.FREEZE:
			$Sniper.hide()
			$Bomb.hide()
			$Sword.hide()
			$Parasol.hide()
			$Plasma.hide()
			$Boomer.hide()
		PLAYER_ABILITY.PARASOL:
			$Sniper.hide()
			$Bomb.hide()
			$Sword.hide()
			$Parasol.show()
			$Plasma.hide()
			$Boomer.hide()
		PLAYER_ABILITY.SPARK:
			$Sniper.hide()
			$Bomb.hide()
			$Sword.hide()
			$Parasol.hide()
			$Plasma.show()
			$Boomer.hide()
		PLAYER_ABILITY.BOMB:
			$Sniper.hide()
			$Bomb.show()
			$Sword.hide()
			$Parasol.hide()
			$Plasma.hide()
			$Boomer.hide()
		PLAYER_ABILITY.SNIPER:
			$Sniper.show()
			$Bomb.hide()
			$Sword.hide()
			$Parasol.hide()
			$Plasma.hide()
			$Boomer.hide()
		PLAYER_ABILITY.SWORD:
			$Sniper.hide()
			$Bomb.hide()
			$Sword.show()
			$Parasol.hide()
			$Plasma.hide()
			$Boomer.hide()
		PLAYER_ABILITY.STARROD:
			$Sniper.hide()
			$Bomb.hide()
			$Sword.hide()
			$Parasol.hide()
			$Plasma.hide()
			$Boomer.hide()

func cleanup_ability(ability: PLAYER_ABILITY):
	match ability:
		PLAYER_ABILITY.BOOMER:
			boomer_fire_timer = 0.0
			boomer_angle = -PI * 0.5
		PLAYER_ABILITY.FREEZE:
			freeze_timer = 0.0
		PLAYER_ABILITY.PARASOL:
			parasol_timer = 0.0
			parasol_state = PARASOL_STATE.HOLSTERED
		PLAYER_ABILITY.SPARK:
			spark_input_buffer = 0
			spark_graze_buffer = 0
			spark_graze_transfer_timer = 0.0
			spark_transfer_timer = 0.0
			spark_charge_level = 0
		PLAYER_ABILITY.BOMB:
			bomb_charge_timer = 0.0
			last_bomb_released = false
			bomb_cooldown_timer = 0.0
			bomb_state = BOMB_STATE.IDLE
		PLAYER_ABILITY.SNIPER:
			active_reload_timer = 0
			active_reload_repress = true
			scope_timer = 0
			active_reload_attempted = false
		PLAYER_ABILITY.SWORD:
			slash_lr = 1.0
			sword_timer = 0.0
			parry_timer = 0.0
			parry_cooldown_timer = 0.0
			parry_success = true

			

func change_ability(ability: PLAYER_ABILITY):
	cleanup_ability(player_ability)
	player_ability = ability
	update_ability_text()
	update_ability_visibility()

func parasol_block_bullets() -> void:
	Bullets.clear_bullets(position + Vector2(0, -108.0), 24, false)
	Bullets.clear_bullets(position + Vector2(38, -98.0), 14, false)
	Bullets.clear_bullets(position + Vector2(-38, -98.0), 14, false)
	Bullets.clear_bullets(position + Vector2(61, -92.0), 8, false)
	Bullets.clear_bullets(position + Vector2(-61, -92.0), 8, false)
	var b = Bullets.create_shot_a1(
		position + Vector2(0, -108.0),
		0,
		0,
		canopy_damage,
		false
	)
	Bullets.set_lifespan(b, 2)

func bestow_star_rod():
	SFX.play("powerup")
	# Grant ability
	change_ability(PLAYER_ABILITY.STARROD)
	
