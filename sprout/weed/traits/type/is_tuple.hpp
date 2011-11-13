#ifndef SPROUT_WEED_TRAITS_TYPE_IS_TUPLE_HPP
#define SPROUT_WEED_TRAITS_TYPE_IS_TUPLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// is_tuple
			//
			template<typename T>
			struct is_tuple
				: public std::false_type
			{};
			template<typename T>
			struct is_tuple<T const>
				: public sprout::weed::traits::is_tuple<T>
			{};
			template<typename... Types>
			struct is_tuple<sprout::tuples::tuple<Types...> >
				: public std::true_type
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_TYPE_IS_TUPLE_HPP
