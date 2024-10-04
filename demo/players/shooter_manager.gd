@tool
extends Sprite2D
class_name ShooterManager
## Shoot shoot pew
##
## Aasrt
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

class Shooter:
	pass


#region Export Variables
## Shows/hides 
@export var preview_bullet := false
@export var bullet_kits : Array[BasicBulletKit]

@export_group("Sprites")
@export_range(0, 32, 1) var sprite_count : int = 0:
	set(sc):
		sprite_count = sc
		kit_index_list.resize(sc)
		sprite_data_list.resize(sc)
		for data in sprite_data_list:
			data.resize(15)
		notify_property_list_changed()

@export_group("Shooters")
@export_range(0, 32, 1) var shooter_count : int = 0

@export_group("", "")

#endregion

#region Members

var sprite_data_list := [] as Array[PackedFloat64Array]
var kit_index_list := [] as Array[int]

var spin := 0.0
var hitbox_radius := 0.0

#endregion

#region User-callable functions

func shoot():
	pass

#endregion

#region Tool Functions

func _test_sprite(index: int):
	var sprite_data := sprite_data_list[index]
	var kit := bullet_kits[kit_index_list[index]]
	
	texture = kit.texture
	region_enabled = true
	region_rect = Rect2(sprite_data[0], sprite_data[1], sprite_data[2], sprite_data[3])
	scale = Vector2(sprite_data[4] / sprite_data[2], sprite_data[4] / sprite_data[3])
	offset.y = sprite_data[6]
	
	hitbox_radius = sprite_data[5] * sprite_data[4] * 0.5
	queue_redraw()
	
func _draw():
	var points := PackedVector2Array()
	var colors := PackedColorArray()
	points.resize(16)
	colors.resize(16)
	for i in 16:
		var p = Vector2(hitbox_radius, 0.0).rotated(i * TAU / 16.0)
		p.x /= scale.x
		p.y /= scale.y
		points[i] = p
		colors[i] = Color(0.0, 0.5, 0.8, 0.25)
	draw_polygon(points, colors)
	points.append(Vector2(hitbox_radius / scale.x, 0.0))
	draw_polyline(points, Color(0.0, 0.05, 0.1), scale.x * 0.5)
	#draw_circle(Vector2.ZERO, hitbox_radius, Color(0.0, 0.5, 0.8, 0.25))

func _get(property: StringName) -> Variant:
	if property.get_slice("/", 1).begins_with("sprite_"):
		var index = property.get_slice("/", 1).get_slice("_", 1).to_int()
		if property.get_slice("/", 2).begins_with("source_rect"):
			var sprite_data := sprite_data_list[index]
			@warning_ignore("narrowing_conversion")
			return Rect2i(sprite_data[0], sprite_data[1], sprite_data[2], sprite_data[3])
			
		elif property.get_slice("/", 2).begins_with("bullet_size"):
			return sprite_data_list[index][4]
			
		elif property.get_slice("/", 2).begins_with("hitbox_ratio"):
			return sprite_data_list[index][5]
			
		elif property.get_slice("/", 2).begins_with("sprite_offset"):
			return sprite_data_list[index][6]
			
		elif property.get_slice("/", 2).begins_with("animation_frames"):
			return sprite_data_list[index][7]
			
		elif property.get_slice("/", 2).begins_with("spin"):
			return sprite_data_list[index][8]
			
		elif property.get_slice("/", 2).begins_with("layer"):
			return sprite_data_list[index][9]
			
		elif property.get_slice("/", 2).begins_with("clear_color"):
			var sprite_data := sprite_data_list[index]
			return Color(sprite_data[10], sprite_data[11], sprite_data[12])
			
		elif property.get_slice("/", 2).begins_with("kit_index"):
			return kit_index_list[index]
		
	return null
	

func _set(property: StringName, value) -> bool:
	if property.get_slice("/", 1).begins_with("sprite_"):
		var index = property.get_slice("/", 1).get_slice("_", 1).to_int()
		if property.get_slice("/", 2).begins_with("source_rect"):
			var rect : Rect2i = value
			sprite_data_list[index][0] = rect.position.x
			sprite_data_list[index][1] = rect.position.y
			sprite_data_list[index][2] = rect.size.x
			sprite_data_list[index][3] = rect.size.y
			
			_test_sprite(index)
			return true
		elif property.get_slice("/", 2).begins_with("bullet_size"):
			sprite_data_list[index][4] = value
			
			_test_sprite(index)
			return true
		
		elif property.get_slice("/", 2).begins_with("hitbox_ratio"):
			sprite_data_list[index][5] = value
			_test_sprite(index)
			return true
			
		elif property.get_slice("/", 2).begins_with("sprite_offset"):
			sprite_data_list[index][6] = value
			_test_sprite(index)
			return true
			
		elif property.get_slice("/", 2).begins_with("animation_frames"):
			sprite_data_list[index][7] = value
			_test_sprite(index)
			return true
			
		elif property.get_slice("/", 2).begins_with("spin"):
			sprite_data_list[index][8] = value
			if value:
				spin = value
			else:
				spin = 0.0
			if spin == 0.0: rotation = 0.0
			return true
			
		elif property.get_slice("/", 2).begins_with("layer"):
			sprite_data_list[index][9] = value
			return true
			
		elif property.get_slice("/", 2).begins_with("clear_color"):
			var color: Color = value
			sprite_data_list[index][10] = color.r
			sprite_data_list[index][11] = color.g
			sprite_data_list[index][12] = color.b
			return true
			
		elif property.get_slice("/", 2).begins_with("kit_index"):
			kit_index_list[index] = value
			return true
	
	return false

func _get_property_list():
	var properties = []
	
#data.resize(15)

	for i in sprite_count:
		
		properties.append({
			"name": "Sprites/sprite_%d/kit_index" % i,
			"type": TYPE_INT,
			"hint": PROPERTY_HINT_RANGE,
			"hint_string": "0,32,1,or_greater"
		})
		properties.append({
			"name": "Sprites/sprite_%d/source_rect" % i,
			"type": TYPE_RECT2I
		})
		properties.append({
			"name": "Sprites/sprite_%d/bullet_size" % i,
			"type": TYPE_FLOAT,
			"hint": PROPERTY_HINT_RANGE,
			"hint_string": "0,512,0.01,or_greater"
		})
		properties.append({
			"name": "Sprites/sprite_%d/hitbox_ratio" % i,
			"type": TYPE_FLOAT,
			"hint": PROPERTY_HINT_RANGE,
			"hint_string": "0,2,0.01,or_greater"
		})
		properties.append({
			"name": "Sprites/sprite_%d/sprite_offset" % i,
			"type": TYPE_FLOAT,
			"hint": PROPERTY_HINT_RANGE,
			"hint_string": "-64,64,0.5,or_greater,or_lesser"
		})
		properties.append({
			"name": "Sprites/sprite_%d/animation_frames" % i,
			"type": TYPE_INT,
			"hint": PROPERTY_HINT_RANGE,
			"hint_string": "1,8,or_greater"
		})
		properties.append({
			"name": "Sprites/sprite_%d/spin" % i,
			"type": TYPE_FLOAT,
			"hint": PROPERTY_HINT_RANGE,
			"hint_string": "-3.142,3.142,0.001"
		})
		properties.append({
			"name": "Sprites/sprite_%d/layer" % i,
			"type": TYPE_INT,
			"hint": PROPERTY_HINT_RANGE,
			"hint_string": "0,64"
		})
		properties.append({
			"name": "Sprites/sprite_%d/clear_color" % i,
			"type": TYPE_COLOR,
			"hint": PROPERTY_HINT_COLOR_NO_ALPHA
		})
	
	
	return properties

#endregion

#region Overrides

func _ready():
	if Engine.is_editor_hint():
		return
	hide()

func _process(delta):
	if Engine.is_editor_hint():
		rotation += Engine.physics_ticks_per_second * delta * spin

#endregion
