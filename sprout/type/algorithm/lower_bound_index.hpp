#ifndef SPROUT_TYPE_ALGORITHM_LOWER_BOUND_INDEX_HPP
#define SPROUT_TYPE_ALGORITHM_LOWER_BOUND_INDEX_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type/functional/less.hpp>
#include <sprout/type/tuple.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<std::size_t I, typename Tuple, typename T, typename Compare, typename = void>
			struct lower_bound_index_impl
				: public std::integral_constant<std::size_t, I>
			{};
			template<std::size_t I, typename Tuple, typename T, typename Compare>
			struct lower_bound_index_impl<
				I, Tuple, T, Compare,
				typename std::enable_if<(I < sprout::tuples::tuple_size<Tuple>::value)>::type
			>
				: public std::conditional<
					Compare::template apply<typename sprout::tuples::tuple_element<I, Tuple>::type, T>::type::value,
					sprout::types::detail::lower_bound_index_impl<I + 1, Tuple, T, Compare>,
					std::integral_constant<std::size_t, I>
				>::type
			{};
		}	// namespace detail
		//
		// lower_bound_index
		//
		template<typename Tuple, typename T, typename Compare = sprout::types::less_>
		struct lower_bound_index
			: public sprout::types::detail::lower_bound_index_impl<0, Tuple, T, Compare>
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_LOWER_BOUND_INDEX_HPP
