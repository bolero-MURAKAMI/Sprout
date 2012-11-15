#ifndef SPROUT_TYPE_INTEGRAL_ARRAY_HPP
#define SPROUT_TYPE_INTEGRAL_ARRAY_HPP

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/type_tuple.hpp>

namespace sprout {
	namespace types {
		//
		// integral_array
		//
		template<typename T, T... Values>
		struct integral_array
			: public sprout::types::type_tuple<std::integral_constant<T, Values>...>
		{
		public:
			typedef T value_type;
		};
	}	// namespace types
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// tuple_size
	//
	template<typename T, T... Values>
	struct tuple_size<sprout::types::integral_array<T, Values...> >
		: public std::tuple_size<sprout::types::type_tuple<std::integral_constant<T, Values>...> >
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename T, T... Values>
	struct tuple_element<I, sprout::types::integral_array<T, Values...> >
		: public std::tuple_element<I, sprout::types::type_tuple<std::integral_constant<T, Values>...> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_TYPE_INTEGRAL_ARRAY_HPP
