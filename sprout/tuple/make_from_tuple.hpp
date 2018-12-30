/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_MAKE_FROM_TUPLE_HPP
#define SPROUT_TUPLE_MAKE_FROM_TUPLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace tuples {
		//
		// make_from_tuple
		//
		namespace detail {
			template<typename T, typename Tuple, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR T
			make_from_tuple_impl(Tuple&& t, sprout::index_tuple<Indexes...>) {
				return T(sprout::get<Indexes>(SPROUT_FORWARD(Tuple, t))...);
			}
		}	// namespace detail
		template<typename T, typename Tuple>
		inline SPROUT_CONSTEXPR T
		make_from_tuple(Tuple&& t) {
			return sprout::tuples::detail::make_from_tuple_impl<T>(
				SPROUT_FORWARD(Tuple, t),
				sprout::tuple_indexes<typename std::remove_reference<Tuple>::type>::make()
				);
		}
	}	// namespace tuples

	using sprout::tuples::make_from_tuple;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_MAKE_FROM_TUPLE_HPP
