/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_OPERATION_PUSH_FRONT_HPP
#define SPROUT_TUPLE_OPERATION_PUSH_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/type/operation/push_front.hpp>

namespace sprout {
	namespace tuples {
		namespace result_of {
			//
			// push_front
			//
			template<typename Tuple, typename... Args>
			struct push_front
				: public sprout::types::push_front<Tuple, Args...>
			{};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Tuple, typename... Args, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result
			push_front_impl(Tuple const& t, sprout::index_tuple<Indexes...>, Args const&... args) {
				return sprout::tuples::remake<Result>(
					t,
					args...,
					sprout::tuples::get<Indexes>(t)...
					);
			}
		}	// namespace detail
		//
		// push_front
		//
		template<typename Tuple, typename... Args>
		inline SPROUT_CONSTEXPR typename sprout::tuples::result_of::push_front<Tuple, Args...>::type
		push_front(Tuple const& t, Args const&... args) {
			return sprout::tuples::detail::push_front_impl<typename sprout::tuples::result_of::push_front<Tuple, Args...>::type>(
				t,
				sprout::tuple_indexes<Tuple>::make(),
				args...
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_OPERATION_PUSH_FRONT_HPP
