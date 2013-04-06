#ifndef SPROUT_TUPLE_OPERATION_POP_BACK_HPP
#define SPROUT_TUPLE_OPERATION_POP_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/type/operation/pop_back.hpp>

namespace sprout {
	namespace tuples {
		namespace result_of {
			//
			// pop_back
			//
			template<typename Tuple>
			struct pop_back
				: public sprout::types::pop_back<Tuple>
			{};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Tuple, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result
			pop_back_impl(Tuple const& t, sprout::index_tuple<Indexes...>) {
				return sprout::tuples::remake<Result>(
					t,
					sprout::tuples::get<Indexes>(t)...
					);
			}
		}	// namespace detail
		//
		// pop_back
		//
		template<typename Tuple>
		inline SPROUT_CONSTEXPR typename sprout::tuples::result_of::pop_back<Tuple>::type
		pop_back(Tuple const& t) {
			return sprout::tuples::detail::pop_back_impl<typename sprout::tuples::result_of::pop_back<Tuple>::type>(
				t,
				sprout::make_index_tuple<sprout::tuples::tuple_size<Tuple>::value - 1>::make()
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_OPERATION_POP_BACK_HPP
