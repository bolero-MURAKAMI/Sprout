#ifndef SPROUT_TUPLE_OPERATION_PUSH_FRONT_HPP
#define SPROUT_TUPLE_OPERATION_PUSH_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/type/operation/push_front.hpp>

namespace sprout {
	namespace tuples {
		namespace result_of {
			//
			// push_front
			//
			template<typename Tuple, typename T>
			struct push_front
				: public sprout::types::push_front<Tuple, T>
			{};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Tuple, typename T, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result push_front_impl(
				Tuple const& t,
				T const& v,
				sprout::index_tuple<Indexes...>
				)
			{
				return sprout::tuples::remake<Result>(
					t,
					v,
					sprout::tuples::get<Indexes>(t)...
					);
			}
		}	// namespace detail
		//
		// push_front
		//
		template<typename Tuple, typename T>
		inline SPROUT_CONSTEXPR typename sprout::tuples::result_of::push_front<Tuple, T>::type push_front(
			Tuple const& t,
			T const& v
			)
		{
			return sprout::tuples::detail::push_front_impl<typename sprout::tuples::result_of::push_front<Tuple, T>::type>(
				t,
				v,
				sprout::index_range<0, sprout::tuples::tuple_size<Tuple>::value>::make()
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_OPERATION_PUSH_FRONT_HPP
