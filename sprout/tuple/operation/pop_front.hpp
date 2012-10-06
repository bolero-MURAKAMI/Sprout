#ifndef SPROUT_TUPLE_OPERATION_POP_FRONT_HPP
#define SPROUT_TUPLE_OPERATION_POP_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/type/operation/pop_front.hpp>

namespace sprout {
	namespace tuples {
		namespace result_of {
			//
			// pop_front
			//
			template<typename Tuple>
			struct pop_front
				: public sprout::types::pop_front<Tuple>
			{};
		}	// namespace result_of

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
		inline SPROUT_CONSTEXPR typename sprout::tuples::result_of::pop_front<Tuple>::type
		pop_front(Tuple const& t) {
			return sprout::tuples::detail::pop_front_impl<typename sprout::tuples::result_of::pop_front<Tuple>::type>(
				t,
				sprout::index_range<1, sprout::tuples::tuple_size<Tuple>::value>::make()
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_OPERATION_POP_FRONT_HPP
