#ifndef SPROUT_TPP_ALGORITHM_ANY_OF_HPP
#define SPROUT_TPP_ALGORITHM_ANY_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace tpp {
		namespace detail {
			template<bool Head, bool... Tail>
			struct any_of_impl;
			template<>
			struct any_of_impl<true>
				: public std::true_type
			{};
			template<>
			struct any_of_impl<false>
				: public std::false_type
			{};
			template<bool... Tail>
			struct any_of_impl<true, Tail...>
				: public std::true_type
			{};
			template<bool... Tail>
			struct any_of_impl<false, Tail...>
				: public std::integral_constant<bool, sprout::tpp::detail::any_of_impl<Tail...>::value>
			{};
		}	// namespace detail
		//
		// any_of
		//
		template<bool... Values>
		struct any_of
			: public sprout::tpp::detail::any_of_impl<Values...>
		{};
	}	// namespace tpp
}	// namespace sprout

#endif	// #ifndef SPROUT_TPP_ALGORITHM_ANY_OF_HPP
