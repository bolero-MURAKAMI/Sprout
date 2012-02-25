#ifndef SPROUT_FUNCTIONAL_FFT_FIXED_BITREV_TABLE_HPP
#define SPROUT_FUNCTIONAL_FFT_FIXED_BITREV_TABLE_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/integer/bit_reverse.hpp>
#include <sprout/integer/bit_length.hpp>

namespace sprout {
	 namespace fixed {
		 namespace detail {
			template<typename Container, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type bitrev_table_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				std::size_t bit_length,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::size_type size
				)
			{
				return sprout::remake_clone<Container>(
					cont,
					sprout::size(cont),
					(Indexes >= offset && Indexes < offset + size
						? sprout::bit_reverse_in(
							static_cast<typename sprout::fixed_container_traits<Container>::value_type>(Indexes - offset),
							bit_length
							)
						: *sprout::next(sprout::fixed_begin(cont), Indexes)
						)...
					);
			}
		}	// namespace detail
		//
		// bitrev_table
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type bitrev_table(
			Container const& cont
			)
		{
			return sprout::fixed::detail::bitrev_table_impl(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<Container>::fixed_size>::type(),
				sprout::empty(cont)
					? 0
					: sprout::bit_length(sprout::size(cont) - 1)
					,
				sprout::fixed_begin_offset(cont),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::bitrev_table;
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_FFT_FIXED_BITREV_TABLE_HPP
