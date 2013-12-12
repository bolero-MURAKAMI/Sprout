/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_TRACERS_CALCULATE_HPP
#define SPROUT_DARKROOM_TRACERS_CALCULATE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/darkroom/renderers/calculate.hpp>

namespace sprout {
	namespace darkroom {
		namespace tracers {
			//
			// calculate_result
			//
			template<typename Tracer, typename Renderer, typename Camera, typename Objects, typename Lights, typename Unit2D>
			struct calculate_result
				: public sprout::identity<typename Tracer::color_type>
			{};
			template<typename Tracer, typename Renderer, typename Camera, typename Objects, typename Lights, typename Unit2D>
			struct calculate_result<Tracer const, Renderer, Camera, Objects, Lights, Unit2D>
				: public sprout::darkroom::tracers::calculate_result<Tracer, Renderer, Camera, Objects, Lights, Unit2D>
			{};
			template<typename Tracer, typename Renderer, typename Camera, typename Objects, typename Lights, typename Unit2D>
			struct calculate_result<Tracer volatile, Renderer, Camera, Objects, Lights, Unit2D>
				: public sprout::darkroom::tracers::calculate_result<Tracer, Renderer, Camera, Objects, Lights, Unit2D>
			{};
			template<typename Tracer, typename Renderer, typename Camera, typename Objects, typename Lights, typename Unit2D>
			struct calculate_result<Tracer const volatile, Renderer, Camera, Objects, Lights, Unit2D>
				: public sprout::darkroom::tracers::calculate_result<Tracer, Renderer, Camera, Objects, Lights, Unit2D>
			{};

			//
			// calculate
			//
			template<typename Tracer, typename Renderer, typename Camera, typename Objects, typename Lights, typename Unit2D, typename Refractions>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::tracers::calculate_result<Tracer, Renderer, Camera, Objects, Lights, Unit2D>::type
			calculate(
				Tracer const& tracer,
				Renderer const& renderer, Camera const& camera, Objects const& objs, Lights const& lights,
				Unit2D const& x, Unit2D const& y, Unit2D const& width, Unit2D const& height,
				std::size_t depth_max, Refractions const& refracs
				)
			{
				return tracer(renderer, camera, objs, lights, x, y, width, height, depth_max, refracs);
			}
			template<typename Tracer, typename Renderer, typename Camera, typename Objects, typename Lights, typename Unit2D>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::tracers::calculate_result<Tracer, Renderer, Camera, Objects, Lights, Unit2D>::type
			calculate(
				Tracer const& tracer,
				Renderer const& renderer, Camera const& camera, Objects const& objs, Lights const& lights,
				Unit2D const& x, Unit2D const& y, Unit2D const& width, Unit2D const& height,
				std::size_t depth_max = sprout::darkroom::renderers::default_depth
				)
			{
				return tracer(renderer, camera, objs, lights, x, y, width, height, depth_max);
			}
		}	// namespace tracers
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_TRACERS_CALCULATE_HPP
