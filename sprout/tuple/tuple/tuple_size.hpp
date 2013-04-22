#ifndef SPROUT_TUPLE_TUPLE_TUPLE_SIZE_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_SIZE_HPP

#include <tuple>
#include <sprout/config.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_size
		//
		template<typename T>
		struct tuple_size
			: public std::tuple_size<T>
		{};
		template<typename T>
		struct tuple_size<T const>
			: public sprout::tuples::tuple_size<T>
		{};
		template<typename T>
		struct tuple_size<T volatile>
			: public sprout::tuples::tuple_size<T>
		{};
		template<typename T>
		struct tuple_size<T const volatile>
			: public sprout::tuples::tuple_size<T>
		{};
	}	// namespace tuples

	using sprout::tuples::tuple_size;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_SIZE_HPP
