#pragma once
#include <wayfire/render-manager.hpp>
#include "deco-button.hpp"
#include "deco-icontheme.hpp"

namespace wf {
namespace windecor {
/**
 * A  class which manages the outlook of decorations.
 * It is responsible for determining the background colors, sizes, etc.
 */
class decoration_theme_t {
    public:
        /** Create a new theme with the default parameters */
        decoration_theme_t( std::string app_id );
        ~decoration_theme_t();

        /** @return The available height for displaying the title */
        int get_title_height() const;
        /** @return The available border for resizing */
        int get_border_size() const;

        /**
         * Fill the given rectange with the background color(s).
         *
         * @param fb The target framebuffer, must have been bound already.
         * @param rectangle The rectangle to redraw.
         * @param scissor The GL scissor rectangle to use.
         * @param active Whether to use active or inactive colors
         */
        void render_background(const wf::framebuffer_t& fb, wf::geometry_t rectangle,
            const wf::geometry_t& scissor, int state) const;

        /**
         * Render the given text on a cairo_surface_t with the given size.
         * The caller is responsible for freeing the memory afterwards.
         */
        cairo_surface_t *render_text(std::string text, int width, int height) const;

        struct button_state_t {
            int width;              /** Button width */
            int height;             /** Button height */
            int border;             /** Button outline size */
            double hover_progress;  /** Progress of button hover, in range [-1, 1].
                            Negative numbers are usually used for pressed state. */
        };

        /**
         * Get the icon for the given button.
         * The caller is responsible for freeing the memory afterwards.
         *
         * @param button The button type.
         * @param state The button state.
        */
        cairo_surface_t *get_button_surface( button_type_t button, const button_state_t& state ) const;

    private:
        wf::option_wrapper_t<std::string> font{ "windecor/font" };
        wf::option_wrapper_t<std::string> iconTheme{ "windecor/icon_theme" };
        wf::option_wrapper_t<int>         title_height{ "windecor/title_height" };
        wf::option_wrapper_t<int>         border_size{ "windecor/border_size" };
        wf::option_wrapper_t<wf::color_t> active_color{ "windecor/active_color" };
        wf::option_wrapper_t<wf::color_t> attn_color{ "windecor/attn_color" };
        wf::option_wrapper_t<wf::color_t> inactive_color{ "windecor/inactive_color" };
        wf::option_wrapper_t<wf::color_t> close_color{ "windecor/close_color" };
        wf::option_wrapper_t<wf::color_t> maximize_color{ "windecor/maximize_color" };
        wf::option_wrapper_t<wf::color_t> minimize_color{ "windecor/minimize_color" };

        std::string mAppId;
        windecor::IconThemeManager *themeMgr;
};

}       /* windecor */
}
