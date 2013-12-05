/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_RAYS_RAY_HPP
#define SPROUT_DARKROOM_RAYS_RAY_HPP

#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/coords/vector.hpp>

namespace sprout {
	namespace darkroom {
		namespace rays {
			//
			// position
			// direction
			//
			template<typename T>
			inline SPROUT_CONSTEXPR auto
			position(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<0>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<0>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<0>(sprout::forward<T>(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR auto
			direction(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<1>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<1>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<1>(sprout::forward<T>(t));
			}

			//
			// make_ray
			//
			template<typename Position, typename Direction>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<Position, Direction>
			make_ray(Position const& pos, Direction const& dir) {
				return sprout::tuples::make_tuple(pos, dir);
			}

			//
			// ray
			//
			typedef sprout::tuples::tuple<sprout::darkroom::coords::vector3d_t, sprout::darkroom::coords::vector3d_t> ray;

			//
			// point_of_intersection
			//
			template<typename Ray, typename Distance>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::access::unit<Ray>::type
			point_of_intersection(Ray const& ray, Distance const& dist) {
				return sprout::darkroom::coords::add(
					sprout::darkroom::rays::position(ray),
					sprout::darkroom::coords::scale(sprout::darkroom::rays::direction(ray), dist)
					);
			}

			//
			// detach_position
			//
			template<typename Position, typename Direction>
			inline SPROUT_CONSTEXPR Position
			detach_position(Position const& pos, Direction const& dir) {
				return sprout::darkroom::coords::add(
					pos,
					sprout::darkroom::coords::resize(
						dir,
						sprout::numeric_limits<typename sprout::darkroom::access::unit<Direction>::type>::epsilon() * 256
						)
					);
			}
			//
			// make_detached_ray
			//
			template<typename Position, typename Direction>
			inline SPROUT_CONSTEXPR sprout::tuples::tuple<Position, Direction>
			make_detached_ray(Position const& pos, Direction const& dir) {
				return sprout::darkroom::rays::make_ray(
					sprout::darkroom::rays::detach_position(pos, dir),
					dir
					);
			}
		}	// namespace rays
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_RAYS_RAY_HPP
