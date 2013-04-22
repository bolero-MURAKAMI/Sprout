#ifndef SPROUT_TUPLE_TUPLE_TUPLE_ELEMENT_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_ELEMENT_HPP

#include <cstddef>
#include <type_traits>
#include <tuple>
#include <sprout/config.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_element
		//
		template<std::size_t I, typename T>
		struct tuple_element
			: public std::tuple_element<I, T>
		{};
		template<std::size_t I, typename T>
		struct tuple_element<I, T const>
			: public std::add_const<
				typename sprout::tuples::tuple_element<I, T>::type
			>
		{};
		template<std::size_t I, typename T>
		struct tuple_element<I, T volatile>
			: public std::add_volatile<
				typename sprout::tuples::tuple_element<I, T>::type
			>
		{};
		template<std::size_t I, typename T>
		struct tuple_element<I, T const volatile>
			: public std::add_cv<
				typename sprout::tuples::tuple_element<I, T>::type
			>
		{};
	}	// namespace tuples

	using sprout::tuples::tuple_element;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_ELEMENT_HPP
