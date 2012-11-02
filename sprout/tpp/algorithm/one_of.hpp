#ifndef SPROUT_TPP_ALGORITHM_ONE_OF_HPP
#define SPROUT_TPP_ALGORITHM_ONE_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tpp/algorithm/none_of.hpp>

namespace sprout {
	namespace tpp {
		namespace detail {
			template<bool... Values>
			struct one_of_impl;
			template<>
			struct one_of_impl<>
				: public std::false_type
			{};
			template<>
			struct one_of_impl<true>
				: public std::true_type
			{};
			template<>
			struct one_of_impl<false>
				: public std::false_type
			{};
			template<bool... Tail>
			struct one_of_impl<true, Tail...>
				: public sprout::tpp::none_of_c<Tail...>
			{};
			template<bool... Tail>
			struct one_of_impl<false, Tail...>
				: public std::integral_constant<bool, sprout::tpp::detail::one_of_impl<Tail...>::value>
			{};
		}	// namespace detail
		//
		// one_of_c
		//
		template<bool... Values>
		struct one_of_c
			: public sprout::tpp::detail::one_of_impl<Values...>
		{};
		//
		// one_of
		//
		template<typename... Types>
		struct one_of
			: public sprout::tpp::one_of_c<Types::value...>
		{};
	}	// namespace tpp
}	// namespace sprout

#endif	// #ifndef SPROUT_TPP_ALGORITHM_ONE_OF_HPP
