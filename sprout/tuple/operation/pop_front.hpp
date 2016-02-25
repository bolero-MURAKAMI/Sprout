/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_OPERATION_POP_FRONT_HPP
#define SPROUT_TUPLE_OPERATION_POP_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/type/operation/pop_front.hpp>

namespace sprout {
	namespace tuples {
		namespace results {
			//
			// pop_front
			//
			template<typename Tuple>
			struct pop_front
				: public sprout::types::pop_front<Tuple>
			{};
		}	// namespace results

		namespace detail {
			template<typename Result, typename Tuple, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result
			pop_front_impl(Tuple const& t, sprout::index_tuple<Indexes...>) {
				return sprout::tuples::remake<Result>(
					t,
					sprout::tuples::get<Indexes>(t)...
					);
			}
		}	// namespace detail
		//
		// pop_front
		//
		template<typename Tuple>
		inline SPROUT_CONSTEXPR typename sprout::tuples::results::pop_front<Tuple>::type
		pop_front(Tuple const& t) {
			return sprout::tuples::detail::pop_front_impl<typename sprout::tuples::results::pop_front<Tuple>::type>(
				t,
				sprout::index_range<1, sprout::tuples::tuple_size<Tuple>::value>::make()
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_OPERATION_POP_FRONT_HPP
