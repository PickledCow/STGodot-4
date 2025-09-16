#include <abstract_unit_pool.hpp>

using namespace godot;

template <typename UnitType>
UnitType* AbstractUnitPool<UnitType>::get_new_unit() {
    if (available_units > 0) {
        available_units--;
        active_units++;

        UnitType* unit = (UnitType*)pool[available_units];
        enable_unit(unit);

        return unit;
    }
    return nullptr;
