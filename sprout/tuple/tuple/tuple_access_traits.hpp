/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_TUPLE_ACCESS_TRAITS_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_ACCESS_TRAITS_HPP

#include <tuple>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple/tuple_element.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_access_traits
		//
		template<typename Tuple>
		struct tuple_access_traits {
		public:
			template<std::size_t I>
			static SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, Tuple>::type&
			tuple_get(Tuple& t) SPROUT_NOEXCEPT {
				return std::get<I>(t);
			}
			template<std::size_t I>
			static SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, Tuple>::type&&
			tuple_get(Tuple&& t) SPROUT_NOEXCEPT {
				return sprout::move(std::get<I>(t));
			}
			template<std::size_t I>
			static SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, Tuple>::type const&
			tuple_get(Tuple const& t) SPROUT_NOEXCEPT {
				return std::get<I>(t);
			}
		};
		template<typename Tuple>
		struct tuple_access_traits<Tuple const> {
		public:
			template<std::size_t I>
			static SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, Tuple>::type const&
			tuple_get(Tuple const& t) SPROUT_NOEXCEPT {
				return sprout::tuples::tuple_access_traits<Tuple>::template tuple_get<I>(t);
			}
		};
	}	// namespace tuples

	using sprout::tuples::tuple_access_traits;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_ACCESS_TRAITS_HPP
