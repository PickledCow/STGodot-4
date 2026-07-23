#ifndef GRAPHICAL_UNIT_POOL_H
#define GRAPHICAL_UNIT_POOL_H

#include "abstract_unit_pool.hpp"
#include "godot_cpp/classes/texture2d.hpp"
#include "godot_cpp/classes/material.hpp"

using namespace godot;

template <typename UnitType>
class GraphicalUnitPool : AbstractUnitPool {

public:
	enum SheetOrientation { SHEET_UP, SHEET_RIGHT, SHEET_DOWN, SHEET_LEFT };
    enum MaterialTypes { MATERIAL_TYPE_MIX = 1, MATERIAL_TYPE_ADD = 2, MATERIAL_TYPE_SUB = 4, MATERIAL_TYPE_ALL = 7, MATERIAL_TYPES_SIZE = 8 };

private:
    int z_index = 0;
    int draw_index = 0;
    Ref<Texture2D> texture;
    SheetOrientation sheet_orientation;
    double rotation_offset = M_PI_2;
    int texture_width;
    RID texture_rid;

    MaterialTypes enabled_materials = MATERIAL_TYPE_ALL;
	Ref<Material> mix_material;
	Ref<Material> add_material;
	Ref<Material> sub_material;
    RID mix_material_rid;
    RID add_material_rid;
    RID sub_material_rid;

    double fade_in_time = 8.0;
    double fade_out_time = 8.0;

public:
    void set_z_index(int idx);
    int get_z_index();
    
    void set_texture(Ref<Texture2D> tex);
    Ref<Texture2D> get_texture();

    void set_sheet_orientation(SheetOrientation orientation);
    SheetOrientation get_sheet_orientation();

    void set_mix_material(Ref<Material> material);
    Ref<Material> get_mix_material();
    void set_add_material(Ref<Material> material);
    Ref<Material> get_add_material();
    void set_sub_material(Ref<Material> material);
    Ref<Material> get_sub_material();

    void set_fade_in_time(double time);
    double get_fade_in_time();
    void set_fade_out_time(double time);
    double get_fade_out_time();

};
#endif