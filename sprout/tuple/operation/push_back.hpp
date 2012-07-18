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
			template<typename Tuple, typename... Args>
			struct push_back
				: public sprout::types::push_back<Tuple, Args...>
			{};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Tuple, typename... Args, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result push_back_impl(
				Tuple const& t,
				sprout::index_tuple<Indexes...>,
				Args const&... args
				)
			{
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
		inline SPROUT_CONSTEXPR typename sprout::tuples::result_of::push_back<Tuple, Args...>::type push_back(
			Tuple const& t,
			Args const&... args
			)
		{
			return sprout::tuples::detail::push_back_impl<typename sprout::tuples::result_of::push_back<Tuple, Args...>::type>(
				t,
				sprout::index_range<0, sprout::tuples::tuple_size<Tuple>::value>::make(),
				args...
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_OPERATION_PUSH_BACK_HPP
