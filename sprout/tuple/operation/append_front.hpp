/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_OPERATION_APPEND_FRONT_HPP
#define SPROUT_TUPLE_OPERATION_APPEND_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/type/operation/append_front.hpp>

namespace sprout {
	namespace tuples {
		namespace results {
			//
			// append_front
			//
			template<typename Tuple, typename InputTuple>
			struct append_front
				: public sprout::types::append_front<Tuple, InputTuple>
			{};
		}	// namespace results

		namespace detail {
			template<typename Result, typename Tuple, typename InputTuple, sprout::index_t... Indexes1, sprout::index_t... Indexes2>
			inline SPROUT_CONSTEXPR Result
			append_front_impl(
				Tuple const& t, InputTuple const& input,
				sprout::index_tuple<Indexes1...>, sprout::index_tuple<Indexes2...>
				)
			{
				return sprout::tuples::remake<Result>(
					t,
					sprout::tuples::get<Indexes2>(input)...,
					sprout::tuples::get<Indexes1>(t)...
					);
			}
		}	// namespace detail
		//
		// append_front
		//
		template<typename Tuple, typename InputTuple>
		inline SPROUT_CONSTEXPR typename sprout::tuples::results::append_front<Tuple, InputTuple>::type
		append_front(Tuple const& t, InputTuple const& input) {
			return sprout::tuples::detail::append_front_impl<typename sprout::tuples::results::append_front<Tuple, InputTuple>::type>(
				t, input,
				sprout::tuple_indexes<Tuple>::make(),
				sprout::tuple_indexes<InputTuple>::make()
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_OPERATION_APPEND_FRONT_HPP
