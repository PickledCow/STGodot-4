#ifndef ABSTRACT_UNIT_POOL_H
#define ABSTRACT_UNIT_POOL_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <bullet.hpp>

// Man really
#ifndef M_PI_2
    #define M_PI_2 3.14159265358979323846264338327950288 * 2.0
#endif

using namespace godot;

template <typename UnitType>
class AbstractUnitPool {
private:
    UnitType** pool;
    int total_units;
    int available_units;
    int active_units;

    bool pool_initialised;

public:
	AbstractUnitPool();
	~AbstractUnitPool();

    virtual void init(int size) = 0;
    UnitType* get_new_unit();
    virtual void enable_unit(UnitType* unit) = 0;
    virtual void disable_unit(UnitType* unit) = 0;

    virtual void process_units(double time_scale);

    
};




#endif