#ifndef SPROUT_TPP_ALGORITHM_HPP
#define SPROUT_TPP_ALGORITHM_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace tpp {
		namespace detail {
			template<bool Head, bool... Tail>
			struct all_of_impl;
			template<>
			struct all_of_impl<true>
				: public std::true_type
			{};
			template<>
			struct all_of_impl<false>
				: public std::false_type
			{};
			template<bool... Tail>
			struct all_of_impl<true, Tail...>
				: public std::integral_constant<bool, sprout::tpp::detail::all_of_impl<Tail...>::value>
			{};
			template<bool... Tail>
			struct all_of_impl<false, Tail...>
				: public std::false_type
			{};
		}	// namespace detail
		//
		// all_of
		//
		template<bool... Values>
		struct all_of
			: public sprout::tpp::detail::all_of_impl<Values...>
		{};

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

		namespace detail {
			template<bool Head, bool... Tail>
			struct none_of_impl;
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
		// none_of
		//
		template<bool... Values>
		struct none_of
			: public sprout::tpp::detail::none_of_impl<Values...>
		{};
	}	// namespace tpp
}	// namespace sprout

#endif	// #ifndef SPROUT_TPP_ALGORITHM_HPP
