#ifndef SPROUT_TYPE_STRING_HPP
#define SPROUT_TYPE_STRING_HPP

#include <cstddef>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/integral_array.hpp>

namespace sprout {
	namespace types {
		//
		// basic_string
		//
		template<typename T, T... Values>
		struct basic_string
			: public sprout::types::integral_array<T, Values...>
		{};
	}	// namespace types
}	// namespace sprout

namespace std {
	//
	// tuple_size
	//
	template<typename T, T... Values>
	struct tuple_size<sprout::types::basic_string<T, Values...> >
		: public std::tuple_size<sprout::types::integral_array<T, Values...> >
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename T, T... Values>
	struct tuple_element<I, sprout::types::basic_string<T, Values...> >
		: public std::tuple_element<I, sprout::types::integral_array<T, Values...> >
	{};
}	// namespace std

#include <sprout/type/string/to_string_constant.hpp>
#include <sprout/type/string/to_string.hpp>
#include <sprout/type/string/alias.hpp>

#endif	// #ifndef SPROUT_TYPE_STRING_HPP
