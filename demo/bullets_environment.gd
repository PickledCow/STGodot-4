@tool
@icon("res://core/icons/bullets_environment.svg")
class_name BulletsEnvironment
extends Node
## Holds onto bullet kits and its corresponding pools; with definitions on the size and layer of each kit.
##
## The description of the script, what it can do,
## and any further detail.

#  "icons/icon_bullets_environment.svg
## Flag for if this BulletEnvironments is the current one to be used in the tree.
## Generally you should try to only ever have one BuletsEnvironment in the tree at once.
@export var current: bool = true

## Signal emitted when the 
#signal tree_entering(node)

## For use in the editor. Denotes how many bullet kits there should be and how many fields to show to the user.
@export var bullet_types_amount: int = 0:
	set(bc):
		bullet_types_amount = bc
		bullet_kits.resize(bc)
		pools_sizes.resize(bc)
		z_indices.resize(bc)
		notify_property_list_changed()

## arst
var bullet_kits: Array = [] # (Array, Resource)
## arstarts
var pools_sizes: Array = [] # (Array, int)
## arsarst
var z_indices: Array = [] # (Array, int)


## aarstars
func _enter_tree():
	if Engine.is_editor_hint():
		return
	#emit_signal("tree_entering", self)
	if current and is_instance_valid(Bullets):
		pass
		Bullets.mount(self)

## arstars
func _exit_tree():
	if Engine.is_editor_hint():
		return
	if is_instance_valid(Bullets):
		pass
		## TODO: MAKE NOT LEAK MEMORY 
		#Bullets.unmount(self)

## rastpar
func reload():
	_set_current(false)
	_set_current(true)


#func set_speed_scale(scale: float):
	#for kit in bullet_kits:
		#kit.time_scale = scale
#
#func set_extend_bounds(extend: bool):
	#var reg : Rect2
	#if extend:
		#reg = Rect2(-1000.0, -64.0, 3000.0, 1128.0)
	#else:
		#reg = Rect2(-64.0, -64.0, 1128.0, 1128.0)
	#
	#for kit in bullet_kits:
		#kit.active_rect = reg

## ardarst
func _set_current(value):
	if Engine.is_editor_hint():
		current = value
		return
	if current != value:
		current = value
		if Bullets != null and is_instance_valid(Bullets):
			if current:
				Bullets.bullets_environment = self
			else:
				pass
				## TODO: MAKE NOT LEAK MEMORY 
				#Bullets.unmount(self)

## tart
func _get(property: StringName) -> Variant:
	if property == &"bullet_types_amount":
		return bullet_kits.size()
	
	elif property.get_slice("/", 1).begins_with("bullet_kit"):
		var index = property.get_slice("/", 0).get_slice("_", 2).to_int()
		return bullet_kits[index]
	elif property.get_slice("/", 1).begins_with("pool_size"):
		var index = property.get_slice("/", 0).get_slice("_", 2).to_int()
		return pools_sizes[index]
	elif property.get_slice("/", 1).begins_with("z_index"):
		var index = property.get_slice("/", 0).get_slice("_", 2).to_int()
		return z_indices[index]
	
	return null

## tafrt
func _set(property: StringName, value) -> bool:
	if property == &"bullet_types_amount":
		bullet_kits.resize(value)
		pools_sizes.resize(value)
		z_indices.resize(value)
		notify_property_list_changed()
		return true
	
	elif property.get_slice("/", 1).begins_with("bullet_kit"):
		var index = property.get_slice("/", 0).get_slice("_", 2).to_int()
		bullet_kits[index] = value
		return true
	elif property.get_slice("/", 1).begins_with("pool_size"):
		var index = property.get_slice("/", 0).get_slice("_", 2).to_int()
		pools_sizes[index] = value
		return true
	elif property.get_slice("/", 1).begins_with("z_index"):
		var index = property.get_slice("/", 0).get_slice("_", 2).to_int()
		z_indices[index] = value
		return true
			
	return false

## arst
func _get_property_list():
	var properties = []
	
	for i in range(bullet_kits.size()):
		properties.append({
			"name": "bullet_type_%d/bullet_kit" % i,
			"type": TYPE_OBJECT,
			"hint": PROPERTY_HINT_RESOURCE_TYPE,
			"hint_string": "BulletKit"
		})
		properties.append({
			"name": "bullet_type_%d/pool_size" % i,
			"type": TYPE_INT,
			"hint": PROPERTY_HINT_RANGE,
			"hint_string": "1,65536"
		})
		properties.append({
			"name": "bullet_type_%d/z_index" % i,
			"type": TYPE_INT,
			"hint": PROPERTY_HINT_RANGE,
			"hint_string": "-2048,2048"
		})
		#properties.append({
			#"name": "controls_%d" % i,
			#"type": TYPE_NIL,
			#"usage": PROPERTY_USAGE_EDITOR,
			#"hint": PROPERTY_HINT_NONE
		#})
	return properties
