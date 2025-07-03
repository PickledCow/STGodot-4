extends Node2D

func _ready():
	for i in get_child_count():
		var item: BaseItem = get_child(i)
		item._upgrade_to_level(1)
	

func process_items(time_scale: float):
	for i in get_child_count():
		var item: BaseItem = get_child(i)
		item.process_item(time_scale, get_parent().position)
