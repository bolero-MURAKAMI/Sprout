#ifndef SPROUT_TPP_ALGORITHM_NONE_OF_HPP
#define SPROUT_TPP_ALGORITHM_NONE_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace tpp {
		namespace detail {
			template<bool... Values>
			struct none_of_impl;
			template<>
			struct none_of_impl<>
				: public std::true_type
			{};
			template<>
			struct none_of_impl<true>
				: public std::false_type
			{};
			template<>
			struct none_of_impl<false>
				: public std::true_type
			{};
			template<bool... Tail>
			struct none_of_impl<true, Tail...>
				: public std::false_type
			{};
			template<bool... Tail>
			struct none_of_impl<false, Tail...>
				: public std::integral_constant<bool, sprout::tpp::detail::none_of_impl<Tail...>::value>
			{};
		}	// namespace detail
		//
		// none_of_c
		//
		template<bool... Values>
		struct none_of_c
			: public sprout::tpp::detail::none_of_impl<Values...>
		{};
		//
		// none_of
		//
		template<typename... Types>
		struct none_of
			: public sprout::tpp::none_of_c<Types::value...>
		{};
	}	// namespace tpp
}	// namespace sprout

#endif	// #ifndef SPROUT_TPP_ALGORITHM_NONE_OF_HPP
