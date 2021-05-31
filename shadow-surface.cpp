#include "shadow-surface.hpp"

/* wf::surface_interface_t implementation */
bool shadow_decoration_surface::is_mapped() const {
    return _mapped;
}

wf::point_t shadow_decoration_surface::get_offset() {

    return wf::origin(surface_geometry);
}

wf::dimensions_t shadow_decoration_surface::get_size() const {

    return wf::dimensions(surface_geometry);
}

void shadow_decoration_surface::simple_render( const wf::framebuffer_t& fb, int x, int y, const wf::region_t& damage ) {
    wf::point_t window_origin = wf::origin(view->get_wm_geometry());
    wf::region_t frame = this->shadow_region + window_origin;
    frame &= damage;

    for (const auto& box : frame)
    {
        shadow.render(fb, window_origin, wlr_box_from_pixman_box(box));
    }
}

bool shadow_decoration_surface::accepts_input( int32_t, int32_t )
{
    return false;
}

void shadow_decoration_surface::update_geometry() {
    wf::geometry_t view_geometry = view->get_wm_geometry();
    shadow.resize(view_geometry.width, view_geometry.height);
    
    wf::point_t frame_offset = wf::origin(view->get_wm_geometry()) - wf::origin(view->get_output_geometry());

    if ( view->fullscreen || view->tiled_edges)
    {
        surface_geometry = {0, 0, 0, 0};
        this->shadow_region.clear();
    } else
    {
        surface_geometry = shadow.get_geometry() + frame_offset;
        this->shadow_region = shadow.calculate_region();
    }
}

void shadow_decoration_surface::unmap() {

    _mapped = false;
    wf::emit_map_state_change( this );
}
