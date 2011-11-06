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
		template<typename T>
		struct begin {
			typedef typename T::begin type;
		};
		//
		// end
		//
		template<typename T>
		struct end {
			typedef typename T::end type;
		};

		//
		// tuple_size
		//
		template<typename T>
		struct tuple_size
			: public std::tuple_size<T>
		{};
		//
		// tuple_element
		//
		template<std::size_t I, typename T>
		struct tuple_element
			: public std::tuple_element<I, T>
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TUPLE_HPP
