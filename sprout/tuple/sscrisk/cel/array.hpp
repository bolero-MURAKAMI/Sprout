/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_SSCRISK_CEL_ARRAY_HPP
#define SPROUT_TUPLE_SSCRISK_CEL_ARRAY_HPP

#include <type_traits>
#include <sscrisk/cel/array.hpp>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple/tuple_access_traits.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_access_traits
		//
		template<typename T, std::size_t N>
		struct tuple_access_traits<sscrisk::cel::array<T, N> > {
		public:
			template<std::size_t I>
			static SPROUT_CONSTEXPR T&
			tuple_get(sscrisk::cel::array<T, N>& t) SPROUT_NOEXCEPT {
				static_assert(I < N, "tuple_get: index out of range");
				return t[I];
			}
			template<std::size_t I>
			static SPROUT_CONSTEXPR T const&
			tuple_get(sscrisk::cel::array<T, N> const& t) SPROUT_NOEXCEPT {
				static_assert(I < N, "tuple_get: index out of range");
				return t[I];
			}
			template<std::size_t I>
			static SPROUT_CONSTEXPR T&&
			tuple_get(sscrisk::cel::array<T, N>&& t) SPROUT_NOEXCEPT {
				return sprout::move(tuple_get<I>(t));
			}
		};
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_SSCRISK_CEL_ARRAY_HPP
