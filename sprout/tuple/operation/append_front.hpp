#ifndef SPROUT_TUPLE_OPERATION_APPEND_FRONT_HPP
#define SPROUT_TUPLE_OPERATION_APPEND_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/type/operation/append_front.hpp>

namespace sprout {
	namespace tuples {
		namespace result_of {
			//
			// append_front
			//
			template<typename Tuple, typename InputTuple>
			struct append_front
				: public sprout::types::append_front<Tuple, InputTuple>
			{};
		}	// namespace result_of

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
		inline SPROUT_CONSTEXPR typename sprout::tuples::result_of::append_front<Tuple, InputTuple>::type
		append_front(Tuple const& t, InputTuple const& input) {
			return sprout::tuples::detail::append_front_impl<typename sprout::tuples::result_of::append_front<Tuple, InputTuple>::type>(
				t, input,
				sprout::tuple_indexes<Tuple>::make(),
				sprout::tuple_indexes<InputTuple>::make()
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_OPERATION_APPEND_FRONT_HPP
