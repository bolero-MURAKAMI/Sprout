#ifndef SPROUT_TUPLE_OPERATION_PUSH_BACK_HPP
#define SPROUT_TUPLE_OPERATION_PUSH_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/type/operation/push_back.hpp>

namespace sprout {
	namespace tuples {
		namespace result_of {
			//
			// push_back
			//
			template<typename Tuple, typename T>
			struct push_back
				: public sprout::types::push_back<Tuple, T>
			{};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Tuple, typename T, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR inline Result push_back_impl(
				Tuple const& t,
				T const& v,
				sprout::index_tuple<Indexes...>
				)
			{
				return sprout::tuples::remake_clone<Result>(
					t,
					sprout::tuples::get<Indexes>(t)...,
					v
					);
			}
		}	// namespace detail
		//
		// push_back
		//
		template<typename Tuple, typename T>
		SPROUT_CONSTEXPR inline typename sprout::tuples::result_of::push_back<Tuple, T>::type push_back(
			Tuple const& t,
			T const& v
			)
		{
			return sprout::tuples::detail::push_back_impl<typename sprout::tuples::result_of::push_back<Tuple, T>::type>(
				t,
				v,
				typename sprout::index_range<0, sprout::tuples::tuple_size<Tuple>::value>::type()
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_OPERATION_PUSH_BACK_HPP
