extends Node
class_name RNGWrapper
## A wrapper for managing a unique [RandomNumberGenerator] object and seed for 
## gameplay calls.
##
## Creates and houses a [RandomNumberGenerator] object that can be accessed 
## from the wrapper functions. This lets the gameplay RNG calls be fully
## deterministic and unaffected by inconsistent visual RNG calls from effects, 
## and the starting seed can be set for use in replays.

## The [RandomNumberGenerator] object to be used for all gameplay calls.
var gameplay_rng : RandomNumberGenerator


## Wrapper for [@GlobalScope.randi] using [RNGWrapper.gameplay_rng].
func randi() -> int:
	return gameplay_rng.randi()

## Wrapper for [@GlobalScope.randi_range] using [RNGWrapper.gameplay_rng].
func randi_range(from: int, to: int) -> int:
	return gameplay_rng.randi_range(from, to)

## Wrapper for [@GlobalScope.randf] using [RNGWrapper.gameplay_rng].
func randf() -> float:
	return gameplay_rng.randf()

## Wrapper for [@GlobalScope.randf_range] using [RNGWrapper.gameplay_rng].
func randf_range(from: float, to: float) -> float:
	return gameplay_rng.randf_range(from, to)
	
## Wrapper for [@GlobalScope.randfn] using [RNGWrapper.gameplay_rng].
func randfn(mean: float, deviation: float) -> float:
	return gameplay_rng.randfn(mean, deviation)

## Wrapper for [@GlobalScope.rand_weighted] using [RNGWrapper.gameplay_rng].
func rand_weighted(weights: PackedFloat32Array) -> int:
	return gameplay_rng.rand_weighted(weights)

## Sets the seed for [RNGWrapper.gameplay_rng].
func set_seed(new_seed: int) -> void:
	gameplay_rng.seed = new_seed

## Sets the seed for [RNGWrapper.gameplay_rng].
func get_seed() -> int:
	return gameplay_rng.seed

## Sets the seed for [RNGWrapper.gameplay_rng] and returns the seed.
func randomize_seed() -> int:
	gameplay_rng.randomize()
	return gameplay_rng.state


func _ready():
	gameplay_rng = RandomNumberGenerator.new()
