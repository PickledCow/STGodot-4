@tool
extends Node

@export var number_count = 3:
	set(nc):
		number_count = nc
		numbers.resize(number_count)
		letters.resize(number_count)
		notify_property_list_changed()

var numbers = PackedInt32Array([0, 0, 0])
var letters = PackedInt32Array([0, 0, 0])

func _get_property_list():
	var properties = []

	for i in range(number_count):
		properties.append({
			"name": "number_%d" % i,
			"type": TYPE_INT,
			"hint": PROPERTY_HINT_ENUM,
			"hint_string": "ZERO,ONE,TWO,THREE,FOUR,FIVE",
		})
		properties.append({
			"name": "letter_%d" % i,
			"type": TYPE_INT,
			"hint": PROPERTY_HINT_ENUM,
			"hint_string": "ZERO,ONE,TWO,THREE,FOUR,FIVE",
		})

	return properties

func _get(property):
	if property.begins_with("number_"):
		var index = property.get_slice("_", 1).to_int()
		return numbers[index]

func _set(property, value):
	if property.begins_with("number_"):
		var index = property.get_slice("_", 1).to_int()
		numbers[index] = value
		return true
	return false
