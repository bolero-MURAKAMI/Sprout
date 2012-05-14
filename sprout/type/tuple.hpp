#ifndef SPROUT_TYPE_TUPLE_HPP
#define SPROUT_TYPE_TUPLE_HPP

#include <cstddef>
#include <tuple>
#include <sprout/config.hpp>

namespace sprout {
	namespace types {
		//
		// begin
		//
		template<typename T, typename Enable = void>
		struct begin {
			typedef typename T::begin type;
		};
		//
		// end
		//
		template<typename T, typename Enable = void>
		struct end {
			typedef typename T::end type;
		};

		//
		// tuple_size
		//
		template<typename T, typename Enable = void>
		class tuple_size
			: public std::tuple_size<T>
		{};
		//
		// tuple_element
		//
		template<std::size_t I, typename T, typename Enable = void>
		class tuple_element
			: public std::tuple_element<I, T>
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TUPLE_HPP
