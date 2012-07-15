#ifndef SPROUT_PIT_TYPE_TRAITS_HPP
#define SPROUT_PIT_TYPE_TRAITS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit/pit.hpp>

namespace sprout {
	//
	// is_pit
	//
	template<typename T>
	struct is_pit
		: public std::false_type
	{};
	template<typename T>
	struct is_pit<T const>
		: public sprout::is_pit<T>
	{};
	template<typename T>
	struct is_pit<T const volatile>
		: public sprout::is_pit<T>
	{};
	template<typename Container>
	struct is_pit<sprout::pit<Container> >
		: public std::true_type
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_PIT_TYPE_TRAITS_HPP
