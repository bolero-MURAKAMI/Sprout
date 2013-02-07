#ifndef SPROUT_ALGORITHM_FIXED_FILL_HPP
#define SPROUT_ALGORITHM_FIXED_FILL_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/value_iterator.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/pit/pit.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename T, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
			fill_impl(
				Container const& cont, T const& value,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				return sprout::remake<Container>(
					cont, sprout::size(cont),
					(Indexes >= offset && Indexes < offset + size
						? value
						: *sprout::next(sprout::internal_begin(cont), Indexes)
						)...
					);
			}

			template<typename Container, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Container>::value,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type
			fill(Container const& cont, T const& value) {
				return sprout::fixed::detail::fill_impl(
					cont, value,
					sprout::index_range<0, sprout::container_traits<Container>::static_size>::make(),
					sprout::internal_begin_offset(cont),
					sprout::size(cont)
					);
			}

			template<typename Container, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Container>::value,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type
			fill(Container const& cont, T const& value) {
				return sprout::remake<Container>(
					cont, sprout::size(cont),
					sprout::value_iterator<T const&>(value, sprout::size(cont)),
					sprout::value_iterator<T const&>(value, 0)
					);
			}
		}	// namespace detail
		//
		// fill
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		fill(Container const& cont, T const& value) {
			return sprout::fixed::detail::fill(cont, value);
		}

		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		fill(T const& value) {
			return sprout::fixed::fill(sprout::pit<Container>(), value);
		}
	}	// namespace fixed

	using sprout::fixed::fill;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_FILL_HPP
