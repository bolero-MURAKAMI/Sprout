#ifndef SPROUT_DARKROOM_CAMERAS_SIMPLE_CAMERA_HPP
#define SPROUT_DARKROOM_CAMERAS_SIMPLE_CAMERA_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/darkroom/coords/vector.hpp>

namespace sprout {
	namespace darkroom {
		namespace cameras {
			template<typename Unit = double>
			class basic_simple_camera {
			public:
				typedef Unit unit_type;
				typedef sprout::tuples::tuple<unit_type, unit_type, unit_type> position_type;
				typedef sprout::tuples::tuple<position_type, position_type> ray_type;
			private:
				unit_type far_plane_;
			public:
				SPROUT_CONSTEXPR explicit basic_simple_camera(
					unit_type const& far_plane
					)
					: far_plane_(far_plane)
				{}
				SPROUT_CONSTEXPR ray_type operator()(unit_type const& u, unit_type const& v) const {
					return ray_type(
						position_type(0, 0, 0),
						sprout::darkroom::coords::normalize(position_type(u, v, far_plane_))
						);
				}
			};
			//
			// make_simple_camera
			//
			template<typename Unit>
			SPROUT_CONSTEXPR inline sprout::darkroom::cameras::basic_simple_camera<Unit>
			make_simple_camera(Unit const& far_plane) {
				return sprout::darkroom::cameras::basic_simple_camera<Unit>(far_plane);
			}
		}	// namespace cameras
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_CAMERAS_SIMPLE_CAMERA_HPP
