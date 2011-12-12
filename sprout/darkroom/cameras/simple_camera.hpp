#ifndef SPROUT_DARKROOM_CAMERAS_SIMPLE_CAMERA_HPP
#define SPROUT_DARKROOM_CAMERAS_SIMPLE_CAMERA_HPP

#include <cmath>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/darkroom/coords/vector.hpp>
#include <sprout/darkroom/cameras/angle_of_view.hpp>

namespace sprout {
	namespace darkroom {
		namespace cameras {
			//
			// basic_simple_camera
			//
			template<typename Unit = double, typename Position = sprout::tuples::tuple<Unit, Unit, Unit> >
			class basic_simple_camera {
			public:
				typedef Unit unit_type;
				typedef Position position_type;
				typedef sprout::tuples::tuple<position_type, position_type> ray_type;
				typedef sprout::darkroom::cameras::angle_of_view_reference angle_of_view_reference;
			private:
				unit_type far_plane_;
				angle_of_view_reference::values reference_value_;
				position_type position_;
				position_type fixation_point_;
				unit_type rotate_;
			private:
				SPROUT_CONSTEXPR position_type transform_1(
					position_type const& c,
					unit_type const& u,
					unit_type const& v,
					unit_type const& l
					) const
				{
					return sprout::darkroom::coords::add(
						c,
						position_type(
							sprout::darkroom::coords::z(c) * u / l,
							v,
							-sprout::darkroom::coords::x(c) * u / l
							)
						);
				}
				SPROUT_CONSTEXPR position_type transform(
					position_type const& c,
					unit_type const& u,
					unit_type const& v
					) const
				{
					using std::sqrt;
					using std::sin;
					using std::cos;
					return transform_1(
						c,
						u * cos(rotate_) - v * sin(rotate_),
						u * sin(rotate_) + v * cos(rotate_),
						sqrt(
							sprout::darkroom::coords::x(c) * sprout::darkroom::coords::x(c)
								+ sprout::darkroom::coords::z(c) * sprout::darkroom::coords::z(c)
							)
						);
				}
				template<typename Unit2D>
				SPROUT_CONSTEXPR position_type reference_width(
					Unit2D const& x,
					Unit2D const& y,
					Unit2D const& width,
					Unit2D const& height,
					unit_type const& rate
					) const
				{
					return transform(
						sprout::darkroom::coords::resize(
							sprout::darkroom::coords::sub(fixation_point_, position_),
							far_plane_
							),
						static_cast<unit_type>(x) / width - 0.5,
						-((static_cast<unit_type>(y) / height - 0.5) * rate)
						);
				}
				template<typename Unit2D>
				SPROUT_CONSTEXPR position_type reference_height(
					Unit2D const& x,
					Unit2D const& y,
					Unit2D const& width,
					Unit2D const& height,
					unit_type const& rate
					) const
				{
					return transform(
						sprout::darkroom::coords::resize(
							sprout::darkroom::coords::sub(fixation_point_, position_),
							far_plane_
							),
						(static_cast<unit_type>(x) / width - 0.5) * rate,
						-(static_cast<unit_type>(y) / height - 0.5)
						);
				}
			public:
				SPROUT_CONSTEXPR explicit basic_simple_camera(
					unit_type const& far_plane,
					angle_of_view_reference::values reference_value = angle_of_view_reference::long_side,
					position_type const& position = position_type(0, 0, -1),
					position_type const& fixation_point = position_type(0, 0, 0),
					unit_type const& rotate = 0
					)
					: far_plane_(far_plane)
					, reference_value_(reference_value)
					, position_(position)
					, fixation_point_(fixation_point)
					, rotate_(rotate)
				{}
				template<typename Unit2D>
				SPROUT_CONSTEXPR ray_type operator()(
					Unit2D const& x,
					Unit2D const& y,
					Unit2D const& width,
					Unit2D const& height
					) const
				{
					return ray_type(
						position_,
						sprout::darkroom::coords::normalize(
							(reference_value_ == angle_of_view_reference::long_side && width >= height)
								|| (reference_value_ == angle_of_view_reference::short_side && width < height)
								|| reference_value_ == angle_of_view_reference::width
								? reference_width(x, y, width, height, static_cast<unit_type>(height) / width)
								: reference_height(x, y, width, height, static_cast<unit_type>(width) / height)
							)
						);
				}
			};
			//
			// make_simple_camera
			//
			template<typename Unit>
			SPROUT_CONSTEXPR inline sprout::darkroom::cameras::basic_simple_camera<Unit>
			make_simple_camera(
				Unit const& far_plane,
				typename sprout::darkroom::cameras::basic_simple_camera<Unit>::angle_of_view_reference::values reference_value
					= sprout::darkroom::cameras::basic_simple_camera<Unit>::angle_of_view_reference::long_side
					,
				typename sprout::darkroom::cameras::basic_simple_camera<Unit>::position_type const& position
					= typename sprout::darkroom::cameras::basic_simple_camera<Unit>::position_type(0, 0, -1)
					,
				typename sprout::darkroom::cameras::basic_simple_camera<Unit>::position_type const& fixation_point
					= typename sprout::darkroom::cameras::basic_simple_camera<Unit>::position_type(0, 0, 0)
					,
				Unit const& rotate = 0
				)
			{
				return sprout::darkroom::cameras::basic_simple_camera<Unit>(
					far_plane,
					reference_value,
					position,
					fixation_point,
					rotate
					);
			}
		}	// namespace cameras
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_CAMERAS_SIMPLE_CAMERA_HPP
