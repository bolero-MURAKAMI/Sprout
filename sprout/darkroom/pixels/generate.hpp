#ifndef SPROUT_DARKROOM_PIXELS_GENERATE_HPP
#define SPROUT_DARKROOM_PIXELS_GENERATE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/array.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/darkroom/colors/rgb.hpp>

namespace sprout {
	namespace darkroom {
		namespace pixels {
			//
			// generate
			//
			namespace detail {
				template<
					typename Pixels,
					typename RayTracer,
					typename Renderer,
					typename Camera,
					typename Objects,
					typename Lights,
					sprout::index_t... XIndexes
				>
				SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Pixels>::value_type
				generate_impl_line(
					RayTracer const& raytracer,
					Renderer const& renderer,
					Camera const& camera,
					Objects const& objs,
					Lights const& lights,
					typename sprout::fixed_container_traits<
						typename sprout::fixed_container_traits<Pixels>::value_type
						>::size_type x
						,
					typename sprout::fixed_container_traits<Pixels>::size_type y,
					typename sprout::fixed_container_traits<
						typename sprout::fixed_container_traits<Pixels>::value_type
						>::size_type width
						,
					typename sprout::fixed_container_traits<Pixels>::size_type height,
					std::size_t depth_max,
					sprout::index_tuple<XIndexes...>
					)
				{
					typedef typename sprout::fixed_container_traits<Pixels>::value_type pixel_line_type;
					typedef typename sprout::fixed_container_traits<pixel_line_type>::value_type pixel_type;
					return sprout::make_clone<pixel_line_type>(
						sprout::darkroom::colors::rgb_f_to_rgb<pixel_type>(
							raytracer.template operator()(
								renderer,
								camera,
								objs,
								lights,
								x + XIndexes,
								y,
								width,
								height,
								depth_max
								)
							)...
						);
				}
				template<
					typename Pixels,
					typename RayTracer,
					typename Renderer,
					typename Camera,
					typename Objects,
					typename Lights,
					sprout::index_t... YIndexes
				>
				SPROUT_CONSTEXPR inline Pixels
				generate_impl(
					RayTracer const& raytracer,
					Renderer const& renderer,
					Camera const& camera,
					Objects const& objs,
					Lights const& lights,
					typename sprout::fixed_container_traits<
						typename sprout::fixed_container_traits<Pixels>::value_type
						>::size_type x
						,
					typename sprout::fixed_container_traits<Pixels>::size_type y,
					typename sprout::fixed_container_traits<
						typename sprout::fixed_container_traits<Pixels>::value_type
						>::size_type width
						,
					typename sprout::fixed_container_traits<Pixels>::size_type height,
					std::size_t depth_max,
					sprout::index_tuple<YIndexes...>
					)
				{
					return sprout::make_clone<Pixels>(
						sprout::darkroom::pixels::detail::generate_impl_line<Pixels>(
							raytracer,
							renderer,
							camera,
							objs,
							lights,
							x,
							y + YIndexes,
							width,
							height,
							depth_max,
							typename sprout::index_range<
								0,
								sprout::fixed_container_traits<
									typename sprout::fixed_container_traits<Pixels>::value_type
									>::fixed_size
								>::type()
							)...
						);
				}
			}	// namespace detail
			template<
				typename Pixels,
				typename RayTracer,
				typename Renderer,
				typename Camera,
				typename Objects,
				typename Lights
			>
			SPROUT_CONSTEXPR inline Pixels generate(
				RayTracer const& raytracer,
				Renderer const& renderer,
				Camera const& camera,
				Objects const& objs,
				Lights const& lights,
				typename sprout::fixed_container_traits<
					typename sprout::fixed_container_traits<Pixels>::value_type
					>::size_type x
					= 0
					,
				typename sprout::fixed_container_traits<Pixels>::size_type y
					= 0
					,
				typename sprout::fixed_container_traits<
					typename sprout::fixed_container_traits<Pixels>::value_type
					>::size_type width
					= sprout::fixed_container_traits<
						typename sprout::fixed_container_traits<Pixels>::value_type
						>::fixed_size
					,
				typename sprout::fixed_container_traits<Pixels>::size_type height
					= sprout::fixed_container_traits<Pixels>::fixed_size
					,
				std::size_t depth_max = 8
				)
			{
				return sprout::darkroom::pixels::detail::generate_impl<Pixels>(
					raytracer,
					renderer,
					camera,
					objs,
					lights,
					x,
					y,
					width,
					height,
					depth_max,
					typename sprout::index_range<
						0,
						sprout::fixed_container_traits<Pixels>::fixed_size
						>::type()
					);
			}

			//
			// color_pixels
			//
			template<std::size_t Width, std::size_t Height, typename Color = sprout::darkroom::colors::rgb>
			struct color_pixels {
			public:
				typedef sprout::array<
					sprout::array<Color, Width>,
					Height
				> type;
			};
		}	// namespace pixels
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_PIXELS_GENERATE_HPP
