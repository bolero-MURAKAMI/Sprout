#ifndef SPROUT_NUMERIC_FIXED_IOTA_HPP
#define SPROUT_NUMERIC_FIXED_IOTA_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename T, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type iota_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				T value,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				return sprout::remake<Container>(
					cont,
					sprout::size(cont),
					(Indexes >= offset && Indexes < offset + size
						? value + (Indexes - offset)
						: *sprout::next(sprout::internal_begin(cont), Indexes)
						)...
					);
			}
		}	// namespace detail
		//
		// iota
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type iota(
			Container const& cont,
			T value
			)
		{
			return sprout::fixed::detail::iota_impl(
				cont,
				sprout::index_range<0, sprout::container_traits<Container>::static_size>::make(),
				value,
				sprout::internal_begin_offset(cont),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::iota;
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FIXED_IOTA_HPP
