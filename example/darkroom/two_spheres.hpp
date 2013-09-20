/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef EXAMPLE_DARKROOM_TWO_SPHERES_HPP
#define EXAMPLE_DARKROOM_TWO_SPHERES_HPP

#include <sprout/darkroom.hpp>
#include <sprout/math/constants.hpp>

namespace darkcult {
	using namespace sprout::darkroom;
	//
	// object
	//
	SPROUT_STATIC_CONSTEXPR auto object = sprout::make_tuple(
		objects::make_aa_plane(
			objects::aa_plane_direction::y,
			-2.0,
			materials::make_plaid_material_image(
				colors::rgb_f(1.0, 0.0, 0.0),
				colors::rgb_f(1.0, 1.0, 0.0),
				0.0,
				0.0
				)
			),
		objects::make_sphere(
			coords::vector3d(-1.0, 0.5, 7.5),
			2.5,
			materials::make_uniform_material_image(
				colors::rgb_f(0.0, 0.0, 1.0),
				0.2
				)
			),
		objects::make_sphere(
			coords::vector3d(1.0, -1.0, 4.0),
			1.0,
			materials::make_uniform_material_image(
				colors::rgb_f(0.0, 1.0, 0.0),
				0.2
				)
			)
		);
	//
	// light
	//
	SPROUT_STATIC_CONSTEXPR auto light = lights::make_light_list(
		lights::make_point_light(
			coords::vector3d(-3.0, 5.0, 0.0),
			colors::rgb_f(7.0, 7.0, 7.0)
			),
		lights::make_parallel_light(
			coords::vector3d(0.0, 1.0, 0.0),
			colors::rgb_f(0.1, 0.1, 0.1)
			),
		lights::make_parallel_light(
			coords::vector3d(1.0, 0.5, 0.0),
			colors::rgb_f(0.1, 0.1, 0.1)
			),
		lights::make_parallel_light(
			coords::vector3d(-1.0, 0.5, 0.0),
			colors::rgb_f(0.1, 0.1, 0.1)
			),
		lights::make_parallel_light(
			coords::vector3d(0.0, 0.5, 1.0),
			colors::rgb_f(0.1, 0.1, 0.1)
			),
		lights::make_parallel_light(
			coords::vector3d(0.0, 0.5, -1.0),
			colors::rgb_f(0.1, 0.1, 0.1)
			)
		);
	//
	// camera
	//
	SPROUT_STATIC_CONSTEXPR auto camera = cameras::make_simple_camera(
		sprout::math::root_three<double>() / 2
		);
	//
	// renderer
	//
	SPROUT_STATIC_CONSTEXPR auto renderer = renderers::make_whitted_style(
		renderers::make_uniform_color(colors::rgb_f(0.0, 0.0, 0.0))
		);
	//
	// raytracer
	//
	SPROUT_STATIC_CONSTEXPR auto raytracer = tracers::make_raytracer();
}	// namespace darkcult

#endif	// #ifndef EXAMPLE_DARKROOM_TWO_SPHERES_HPP
