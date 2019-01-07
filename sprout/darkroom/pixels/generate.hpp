/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_PIXELS_GENERATE_HPP
#define SPROUT_DARKROOM_PIXELS_GENERATE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/array.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/darkroom/colors/rgb.hpp>
#include <sprout/darkroom/renderers/calculate.hpp>
#include <sprout/darkroom/tracers/calculate.hpp>

namespace sprout {
	namespace darkroom {
		namespace pixels {
			//
			// generate
			//
			namespace detail {
				template<
					typename Pixels,
					typename RayTracer, typename Renderer, typename Camera,
					typename Objects, typename Lights,
					sprout::index_t... XIndexes
				>
				inline SPROUT_CONSTEXPR typename sprout::container_traits<Pixels>::value_type
				generate_impl_line(
					RayTracer const& raytracer, Renderer const& renderer, Camera const& camera,
					Objects const& objs, Lights const& lights,
					typename sprout::container_traits<
						typename sprout::container_traits<Pixels>::value_type
						>::size_type x,
					typename sprout::container_traits<Pixels>::size_type y,
					typename sprout::container_traits<
						typename sprout::container_traits<Pixels>::value_type
						>::size_type width,
					typename sprout::container_traits<Pixels>::size_type height,
					std::size_t depth_max,
					sprout::index_tuple<XIndexes...>
					)
				{
					typedef typename sprout::container_traits<Pixels>::value_type pixel_line_type;
					typedef typename sprout::container_traits<pixel_line_type>::value_type pixel_type;
					return sprout::make<pixel_line_type>(
						sprout::darkroom::colors::rgb_f_to_rgb<pixel_type>(
							sprout::darkroom::tracers::calculate(
								raytracer,
								renderer, camera, objs, lights,
								x + XIndexes, y, width, height, depth_max
								)
							)...
						);
				}
				template<
					typename Pixels,
					typename RayTracer, typename Renderer, typename Camera,
					typename Objects, typename Lights,
					sprout::index_t... YIndexes
				>
				inline SPROUT_CONSTEXPR Pixels
				generate_impl(
					RayTracer const& raytracer, Renderer const& renderer, Camera const& camera,
					Objects const& objs, Lights const& lights,
					typename sprout::container_traits<
						typename sprout::container_traits<Pixels>::value_type
						>::size_type x
						,
					typename sprout::container_traits<Pixels>::size_type y,
					typename sprout::container_traits<
						typename sprout::container_traits<Pixels>::value_type
						>::size_type width
						,
					typename sprout::container_traits<Pixels>::size_type height,
					std::size_t depth_max,
					sprout::index_tuple<YIndexes...>
					)
				{
					return sprout::make<Pixels>(
						sprout::darkroom::pixels::detail::generate_impl_line<Pixels>(
							raytracer, renderer, camera, objs, lights,
							x, y + YIndexes, width, height, depth_max,
							sprout::container_indexes<typename sprout::container_traits<Pixels>::value_type>::make()
							)...
						);
				}
			}	// namespace detail
			template<
				typename Pixels,
				typename RayTracer, typename Renderer, typename Camera,
				typename Objects, typename Lights
			>
			inline SPROUT_CONSTEXPR Pixels generate(
				RayTracer const& raytracer, Renderer const& renderer, Camera const& camera,
				Objects const& objs, Lights const& lights,
				typename sprout::container_traits<
					typename sprout::container_traits<Pixels>::value_type
					>::size_type x
					= 0,
				typename sprout::container_traits<Pixels>::size_type y
					= 0,
				typename sprout::container_traits<
					typename sprout::container_traits<Pixels>::value_type
					>::size_type width
					= sprout::container_traits<
						typename sprout::container_traits<Pixels>::value_type
						>::static_size,
				typename sprout::container_traits<Pixels>::size_type height
					= sprout::container_traits<Pixels>::static_size,
				std::size_t depth_max = sprout::darkroom::renderers::default_depth
				)
			{
				return sprout::darkroom::pixels::detail::generate_impl<Pixels>(
					raytracer, renderer, camera, objs, lights,
					x, y, width, height, depth_max,
					sprout::container_indexes<Pixels>::make()
					);
			}

			//
			// color_pixels
			//
			template<std::size_t Width, std::size_t Height, typename Color = sprout::darkroom::colors::rgb_t>
			struct color_pixels {
			public:
				typedef sprout::array<sprout::array<Color, Width>, Height> type;
			};
		}	// namespace pixels
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_PIXELS_GENERATE_HPP
