@tool
extends Node2D
class_name SFXPlayer
## An abstraction layer for easily playing sound effects at a global scope.

## The volume is attenuated over distance with this as an exponent. By default
## there is no attenuation and only panning.
@export_exp_easing("attenuation") var attenuation := 0.0
## The AudioBus for the SFX to play through.
@warning_ignore("enum_variable_without_default") # Can't find a better way...
@export var sfx_bus: AudioBus

var sfx_name_list := [] as Array[StringName]
var audio_stream_list := [] as Array[AudioStream]
var audio_volume_list := [] as Array[float]

var sfx_index_map := {}
var audio_stream_player_nodes_list := [] as Array[AudioStreamPlayer2D]

@export_range(0, 1, 1, "or_greater", "exp") var sfx_count : int = 0:
	set(sc):
		sfx_count = sc
		sfx_name_list.resize(sc)
		audio_stream_list.resize(sc)
		audio_volume_list.resize(sc)
		notify_property_list_changed()


@onready var viewport_size := get_viewport_rect().size
@onready var audio_test_node := $AudioTest

# -----------------------------------------------------------------------------
# User-callable function for playing sfx
# -----------------------------------------------------------------------------

## Play the sfx given its name. Can optionally have panning.
func play(sfx_name: String, pan: float = 0.0) -> void:
	var index: int = sfx_index_map[StringName(sfx_name)]
	var audio_node := audio_stream_player_nodes_list[index]
	
	audio_node.position = viewport_size * clamp(pan * 0.5, -0.5, 0.5)
	audio_node.play()
	
# -----------------------------------------------------------------------------
# Initialise audio stream players
# -----------------------------------------------------------------------------

func _ready() -> void:
	if Engine.is_editor_hint():
		return
		
	viewport_size = get_viewport_rect().size
	
	for i in sfx_count:
		var sfx_player := AudioStreamPlayer2D.new()
		
		sfx_player.attenuation = attenuation
		sfx_player.max_distance = INF
		sfx_player.bus = AudioServer.get_bus_name(sfx_bus)
		sfx_player.stream = audio_stream_list[i]
		sfx_player.volume_db = audio_volume_list[i]

		
		add_child(sfx_player)
		audio_stream_player_nodes_list.append(sfx_player)
	
	position = viewport_size * 0.5
		

# -----------------------------------------------------------------------------
# Audio bus list initialiser
# -----------------------------------------------------------------------------

# hey godot why do I have to do this 
enum AudioBus {}
func _validate_property(property: Dictionary):
	if property.name == "sfx_bus":
		var busNumber = AudioServer.bus_count
		var options = ""
		for i in busNumber:
			if i > 0:
				options += ","
			var busName = AudioServer.get_bus_name(i)
			options += busName
		property.hint_string = options

# -----------------------------------------------------------------------------
# Add neatly structured sfx list to the editor.
# -----------------------------------------------------------------------------

func _test_volume(index: int):
	if Engine.is_editor_hint():
		if audio_test_node:
			audio_test_node.stream = audio_stream_list[index]
			audio_test_node.volume_db = audio_volume_list[index]
			audio_test_node.play()


func _get(property: StringName) -> Variant:
	
	if property.get_slice("/", 1).begins_with("name"):
		var index = property.get_slice("/", 0).get_slice("_", 1).to_int()
		return sfx_name_list[index]
	elif property.get_slice("/", 1).begins_with("stream"):
		var index = property.get_slice("/", 0).get_slice("_", 1).to_int()
		return audio_stream_list[index]
	elif property.get_slice("/", 1).begins_with("volume"):
		var index = property.get_slice("/", 0).get_slice("_", 1).to_int()
		return audio_volume_list[index]
	
	return null

func _set(property: StringName, value) -> bool:
	if property == &"sfx_count":
		sfx_name_list.resize(value)
		audio_stream_list.resize(value)
		audio_volume_list.resize(value)
		notify_property_list_changed()
		return true
	
	elif property.get_slice("/", 1).begins_with("name"):
		var index = property.get_slice("/", 0).get_slice("_", 1).to_int()
		sfx_name_list[index] = value
		sfx_index_map[value] = index
		return true
	elif property.get_slice("/", 1).begins_with("stream"):
		var index = property.get_slice("/", 0).get_slice("_", 1).to_int()
		audio_stream_list[index] = value
		return true
	elif property.get_slice("/", 1).begins_with("volume"):
		var index = property.get_slice("/", 0).get_slice("_", 1).to_int()
		audio_volume_list[index] = value
		_test_volume(index)
		return true
			
	return false

func _get_property_list():
	var properties = []
	
	for i in sfx_count:
		properties.append({
			"name": "sfx_%d/name" % i,
			"type": TYPE_STRING_NAME,
			"hint": PROPERTY_HINT_TYPE_STRING
		})
		properties.append({
			"name": "sfx_%d/stream" % i,
			"type": TYPE_OBJECT,
			"hint": PROPERTY_HINT_RESOURCE_TYPE,
			"hint_string": "AudioStream"
		})
		properties.append({
			"name": "sfx_%d/volume" % i,
			"type": TYPE_FLOAT,
			"hint": PROPERTY_HINT_RANGE,
			"hint_string": "-80,24,0.1,exp,suffix:dB"
		})
	
	return properties
