extends MultiMeshInstance3D

@export var incline := 0.8
@export var length := 8.0
@export var clearance := 3.5
@export var time_scale := 1.0

var t := 0.0

var scroll := true

func _ready() -> void:
	show()

func _process(delta: float) -> void:
	if scroll:
		@warning_ignore("integer_division")
		var tree_count := multimesh.instance_count / 2
		
		var spacing := length / float(tree_count)
		
		t = fmod(t + delta * time_scale, 1.0)
		
		for i in tree_count:
			var lr := (i % 2) * 2 - 1
			var lbasis := Basis(Vector3(1, 0, 0), Vector3(0, lr, 0), Vector3(0, 0, lr))
			var rbasis := Basis(Vector3(1, 0, 0), Vector3(0, -lr, 0), Vector3(0, 0, -lr))
			
			var j := i - t*2
			
			multimesh.set_instance_transform(multimesh.instance_count - i * 2 - 1, Transform3D(lbasis, Vector3(j * spacing, (j * spacing) * incline, clearance)))
			multimesh.set_instance_transform(multimesh.instance_count - i * 2 - 2, Transform3D(rbasis, Vector3(j * spacing, (j * spacing) * incline, -clearance)))
