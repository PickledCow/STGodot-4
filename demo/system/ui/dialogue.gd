extends Control

var dialogue : Array

var dialogue_timer := 0.0
var dialogue_expire_time := 300.0
var dialogue_index := -1
var dialogue_section := 0
var last_side := '0'
var mash_cooldown_timer := 120.0
var mash_cooldown := 5.0
var left_dialogue := true

func _ready() -> void:
	var file := FileAccess.open("res://dialogue.txt", FileAccess.READ)
	var raw_dialogue := file.get_as_text()
	var sectioned_dialoge := raw_dialogue.split("\n\n")
	
	for section in sectioned_dialoge:
		var this_dialogue : Array
		var split_dialogue := section.split("\n")
		for line in split_dialogue:
			var split_line := line.split("|")
			this_dialogue.append(split_line)
		dialogue.append(this_dialogue)
	#print(dialogue[0][0][2])

func _process(_delta: float) -> void:
	if System.in_dialogue and dialogue_section < dialogue.size():
		if left_dialogue:
			left_dialogue = false
			$AnimationPlayer.play_backwards("leave")
		
		
		dialogue_timer -= System.time_scale
		mash_cooldown_timer -= System.time_scale
		if (
			(
				GameInput.is_action_just_pressed("player_shoot") or
				GameInput.is_action_just_pressed("player_bomb")
			) and 
			mash_cooldown_timer <= 0.0
		):
			dialogue_timer = 0.0
			mash_cooldown_timer = mash_cooldown
		if dialogue_timer <= 0.0:
			dialogue_index += 1
			dialogue_timer = dialogue_expire_time
			if dialogue_index < dialogue[dialogue_section].size():
				# Set text and shit
				var side : String = dialogue[dialogue_section][dialogue_index][0]
				var character : String = dialogue[dialogue_section][dialogue_index][1]
				var text : String = dialogue[dialogue_section][dialogue_index][2]
				if side == '0':
					$PlayerBox.text = text
					$PlayerBox.show()
					$Control/EnemyBox.hide()
				else:
					$Control/EnemyBox.text = text
					$Control/EnemyBox.show()
					$PlayerBox.hide()
				for child in $Enemy.get_children():
					child.hide()
				$Enemy.get_child(int(character)).show()
					
				if last_side != side:
					if side == '0':
						$AnimationPlayer2.play("enemy2player")
					else:
						$AnimationPlayer2.play_backwards("enemy2player")
					last_side = side
			
			else:
				System.in_dialogue = false
				$AnimationPlayer.play("leave")
				dialogue_section += 1
				dialogue_index = -1
				dialogue_timer = 0.0
