extends Sprite2D
class_name Player
## Base Player class. Has most important implementation and can be extended from
## with minimal changes.
## 
## The base Player class. Handles basic functions with movement, collisions,
## life management, and basic sprite rendering. [br][br]
## Shooting should be handled by a child [ShooterManager] with the Player holding
## a [NodePath] to the node
## @experimental

# =============================================================================
#  ┏━━┓  ┏━━┓   ┏━━━━━━━┓   ┏━━┓  ┏━━┓  ┏━━┓
#  ┃  ┃  ┃  ┃   ┃  ┏━━━━┛   ┃  ┃  ┃  ┃  ┃  ┃
#  ┃  ┗━━┛  ┃   ┃  ┗━━━┓    ┃  ┗━━┛  ┃  ┃  ┃
#  ┃  ┏━━┓  ┃   ┃  ┏━━━┛    ┗━━┓  ┏━━┛  ┗━━┛
#  ┃  ┃  ┃  ┃   ┃  ┗━━━━┓      ┃  ┃     ┏━━┓
#  ┗━━┛  ┗━━┛   ┗━━━━━━━┛      ┗━━┛     ┗━━┛
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

## Array for the input StringNames for horizontal inputs.
const H_PRIORITY_INPUT_NAMES := [&"player_left", &"player_right"]
## Array for the input StringNames for vertical inputs.
const V_PRIORITY_INPUT_NAMES := [&"player_up", &"player_down"]

#endregion

#region Export Variables

@export_node_path("ShooterManager") var shooter_manager_path : NodePath = NodePath()
@export_node_path() var arst : NodePath = NodePath()

@export_group("Vitality")
## Default starting lives. Game over occurs when you die with 0 lives.
@export_range(0, 12, 1, "or_greater") var starting_lives := 2
## How many bombs you start with per life.
@export_range(0, 12, 1, "or_greater") var starting_bombs := 3
## Enabling this makes death reset bomb count even if above default.
@export var reset_bombs_on_death := true
## How many ticks we have to bomb to deathbomb.
@export_range(0, 60, 1, "or_greater") var deathbomb_window := 8
## Enables EoSD Style deathbombs where the deathbomb window does not reset until
## death and makes subsequent deathbombs in one life harder. 
@export var diminishing_deathbomb_window := false
## How many ticks it takes to die.
@export_range(0, 300, 1, "or_greater") var death_time := 60
## How many ticks to respawn before control is returned to the player.
@export_range(0, 120, 1, "or_greater") var respawn_time := 60
## How many ticks of invulnerability the player has after respawning.
@export_range(0, 300, 1, "or_greater") var respawn_i_frames := 180

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
## Radius of the hitbox for magneting items in pixels.
@export_range(0, 64, 0.1, "or_greater") var item_magnet_radius := 24.0

@export_group("Animation")
## Layout of the spritsheet. See [enum Player.SPRITESHEET_FORMAT] for details.
@export var spritesheet_format := SPRITESHEET_FORMAT.IDLE_RIGHT:
	set(sf):
		spritesheet_format = sf
		set_vframes(2 if sf == SPRITESHEET_FORMAT.IDLE_RIGHT else 3)
## How many frames of animation is in one loop of the idle animation.
@export_range(1, 16, 1, "or_greater") var idle_animation_frame_count := 4:
	set(fc):
		idle_animation_frame_count = fc
		_update_hframes()
## How many frames of animation is in one loop of the movement animation
## including the transition frames.
@export_range(1, 16, 1, "or_greater") var move_animation_frame_count := 4:
	set(fc):
		move_animation_frame_count = fc
		_update_hframes()
## How many frames of turning transition animations there are in the spritesheet.
## Transition animations are not repeated once the animation loops. [br]
## Transition animations are only present in the turning animations and not in the 
## idle stance.
@export_range(0, 16, 1, "or_greater") var transition_frame_count := 0
## How long each frame of animation should last in seconds.
@export_range(0.01, 2.0, 0.1, "or_greater") var animation_speed := 0.1


@export_group("", "")
#endregion

#region On-Ready Variables

var shooter_manager: ShooterManager

#endregion

#region Player States
## If the player is currently in the focus state.
var is_focused := false

## Dynamic horizontal input priority for NULL_CANCEL style inputs.
var current_horizontal_input_priority := H_PRIORITY.LEFT
## Dynamic vertical input priority for NULL_CANCEL style inputs.
var current_vertical_input_priority := V_PRIORITY.UP

## Timer for changing animation frames.
var animation_timer := 0.0
## Current frame of animation.
var animation_frame := 0
## Current state of animation.
var animation_state := ANIMATION_STATE.IDLE

#endregion

#region Default Subroutinse

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
	

#endregion

#region Default Routines
## Base movement code. Calls [method Player.update_animation_state] by default 
## and will need to call it if overriding this function.
func movement(time_scale) -> void:
	# ------------------------------
	# Update focus state
	# ------------------------------
	is_focused = GameInput.is_action_pressed(&"player_focus")
	
	# ------------------------------
	# Handle movement 
	# ------------------------------
	var velocity := Vector2()
	
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
	if (velocity.length_squared() > 0):
		velocity = velocity.normalized() * (focus_speed if is_focused else unfocus_speed) * time_scale
	
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
		

## Updates the player sprite according to time.
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
		
	frame = animation_frame + hframes * animation_state
		

## Checks collisions for bullets and items and acts accordingly,
func collision() -> void:
	var collisions = Bullets.collide_and_graze_player(position, hitbox_radius, graze_radius)
	
	if len(collisions[0]) > 0:
		SFX.play("death")
		
	if len(collisions[1]) > 0:
		SFX.play("graze")
	

## Tells the associated [class ShooterManager] to shoot.
func shooting() -> void:
	if shooter_manager:
		shooter_manager.shoot()


#endregion

#region Tool Functions

func _update_hframes():
	hframes = max(idle_animation_frame_count, move_animation_frame_count)

#endregion

#region Overrides
func _ready() -> void:
	if shooter_manager_path:
		shooter_manager = get_node(shooter_manager_path)
	else:
		print("Shooter Manager Path failed, using first child instead.")
		shooter_manager = get_child(0)

func _process(delta: float) -> void:
	animation(delta)

func _physics_process(_delta: float) -> void:
	var time_scale := Engine.time_scale
	movement(time_scale)
	collision()
	shooting()
	
#endregion
