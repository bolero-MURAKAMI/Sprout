#ifndef SPROUT_OPERATION_FIXED_PUSH_FRONT_HPP
#define SPROUT_OPERATION_FIXED_PUSH_FRONT_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/operation/fixed/insert.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// push_front
			//
			template<typename Container, typename T, typename... Values>
			struct push_front
				: public insert<Container, T, Values...>
			{};
		}	// namespace result_of

		//
		// push_front
		//
		template<typename Container, typename T, typename... Values>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::push_front<Container, T, Values...>::type push_front(
			Container const& cont,
			T const& v,
			Values const&... values
			)
		{
			return sprout::fixed::detail::insert_impl<typename sprout::fixed::result_of::push_front<Container, T, Values...>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::push_front<Container, T, Values...>::type>::fixed_size>::type(),
				sprout::fixed_begin_offset(cont),
				v,
				values...
				);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_PUSH_FRONT_HPP
