/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_RENDERERS_CALCULATE_HPP
#define SPROUT_DARKROOM_RENDERERS_CALCULATE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace darkroom {
		namespace renderers {
			//
			// default_depth
			//
			SPROUT_STATIC_CONSTEXPR std::size_t default_depth = 4;

			//
			// calculate_result
			//
			template<typename Color, typename Renderer, typename Camera, typename Objects, typename Lights, typename Ray, typename Refractions = double>
			struct calculate_result
				: public sprout::identity<Color>
			{};
			template<typename Color, typename Renderer, typename Camera, typename Objects, typename Lights, typename Ray, typename Refractions>
			struct calculate_result<Color, Renderer const, Camera, Objects, Lights, Ray, Refractions>
				: public sprout::darkroom::renderers::calculate_result<Color, Renderer, Camera, Objects, Lights, Ray, Refractions>
			{};
			template<typename Color, typename Renderer, typename Camera, typename Objects, typename Lights, typename Ray, typename Refractions>
			struct calculate_result<Color, Renderer volatile, Camera, Objects, Lights, Ray, Refractions>
				: public sprout::darkroom::renderers::calculate_result<Color, Renderer, Camera, Objects, Lights, Ray, Refractions>
			{};
			template<typename Color, typename Renderer, typename Camera, typename Objects, typename Lights, typename Ray, typename Refractions>
			struct calculate_result<Color, Renderer const volatile, Camera, Objects, Lights, Ray, Refractions>
				: public sprout::darkroom::renderers::calculate_result<Color, Renderer, Camera, Objects, Lights, Ray, Refractions>
			{};

			//
			// calculate
			//
			template<typename Color, typename Renderer, typename Camera, typename Objects, typename Lights, typename Ray, typename Refractions>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::renderers::calculate_result<Color, Renderer, Camera, Objects, Lights, Ray, Refractions>::type
			calculate(
				Renderer const& renderer,
				Camera const& camera, Objects const& objs, Lights const& lights,
				Ray const& ray, std::size_t depth_max, Refractions const& refracs
				)
			{
				return renderer.template operator()<Color>(camera, objs, lights, ray, depth_max, refracs);
			}
			template<typename Color, typename Renderer, typename Camera, typename Objects, typename Lights, typename Ray>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::renderers::calculate_result<Color, Renderer, Camera, Objects, Lights, Ray>::type
			calculate(
				Renderer const& renderer,
				Camera const& camera, Objects const& objs, Lights const& lights,
				Ray const& ray, std::size_t depth_max
				)
			{
				return renderer.template operator()<Color>(camera, objs, lights, ray, depth_max);
			}
		}	// namespace renderers
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_RENDERERS_CALCULATE_HPP
