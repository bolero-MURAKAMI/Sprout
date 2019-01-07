/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_HASH_HPP
#define SPROUT_MATH_QUATERNION_HASH_HPP

#include <functional>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/math/quaternion/quaternion.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	namespace math {
		//
		// hash_value
		//
		template<typename T>
		inline SPROUT_CONSTEXPR std::size_t
		hash_value(sprout::math::quaternion<T> const& v) {
			return sprout::hash_values(v[0], v[1], v[2], v[3]);
		}
	}	// namespace math
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// hash
	//
	template<typename T>
	struct hash<sprout::math::quaternion<T> >
		: public sprout::hash<sprout::math::quaternion<T> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_MATH_QUATERNION_HASH_HPP
