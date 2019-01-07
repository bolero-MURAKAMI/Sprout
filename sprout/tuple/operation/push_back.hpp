/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_OPERATION_PUSH_BACK_HPP
#define SPROUT_TUPLE_OPERATION_PUSH_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/type/operation/push_back.hpp>

namespace sprout {
	namespace tuples {
		namespace results {
			//
			// push_back
			//
			template<typename Tuple, typename... Args>
			struct push_back
				: public sprout::types::push_back<Tuple, Args...>
			{};
		}	// namespace results

		namespace detail {
			template<typename Result, typename Tuple, typename... Args, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result
			push_back_impl(Tuple const& t, sprout::index_tuple<Indexes...>, Args const&... args) {
				return sprout::tuples::remake<Result>(
					t,
					sprout::tuples::get<Indexes>(t)...,
					args...
					);
			}
		}	// namespace detail
		//
		// push_back
		//
		template<typename Tuple, typename... Args>
		inline SPROUT_CONSTEXPR typename sprout::tuples::results::push_back<Tuple, Args...>::type
		push_back(Tuple const& t, Args const&... args) {
			return sprout::tuples::detail::push_back_impl<typename sprout::tuples::results::push_back<Tuple, Args...>::type>(
				t,
				sprout::tuple_indexes<Tuple>::make(),
				args...
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_OPERATION_PUSH_BACK_HPP
