@tool
extends Sprite2D
class_name ShooterManager

class Shooter:
	pass


#
#data.resize(15)
#data[0] = bubble_offsets[j].x # source x (integer)
#data[1] = bubble_offsets[j].y # source y (integer)
#data[2] = 256				# source width (integer)
#data[3] = 256				# source height (integer)
#data[4] = 128.0				# bullet size [0, inf)
#data[5] = BULLET_SIZES[BULLET_TYPE.BUBBLE] # hitbox ratio [0, 1]
#data[6] = 0					# Sprite offset y (integer)
#data[7] = 1					# anim frame, 1 for no animation (integer)
#data[8] = 2.39996322972865332# spin
#data[9] = LAYERS.BUBBLE		# layer
#data[10] = LARGE_RGB[j].x	# rgb
#data[11] = LARGE_RGB[j].y
#data[12] = LARGE_RGB[j].z
#data[13] = 0				# damage type
#data[14] = 0				# damage amount


@export var bullet_kits : Array[BasicBulletKit]

@export_group("Sprites")
@export_range(0, 32, 1) var sprite_count : int = 0:
	set(sc):
		sprite_count = sc
		sprite_data_list.resize(sc)
		for data in sprite_data_list:
			data.resize(15)

@export_group("Shooters")


var sprite_data_list := [] as Array[PackedFloat64Array]

func shoot():
	pass

func _test_sprite(index: int):
	pass


func _get_property_list():
	var properties = []
	
	
	for i in sprite_count:
		properties.append({
			"name": "Sprites/Sprite_%d/name" % i,
			"type": TYPE_STRING_NAME,
			"hint": PROPERTY_HINT_TYPE_STRING
		})
	
	return properties




func _ready():
	if Engine.is_editor_hint():
		return
	hide()

func _process(delta):
	if Engine.is_editor_hint():
		return
