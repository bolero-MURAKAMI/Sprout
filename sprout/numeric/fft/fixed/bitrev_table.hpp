/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_FFT_FIXED_BITREV_TABLE_HPP
#define SPROUT_NUMERIC_FFT_FIXED_BITREV_TABLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/bit/bit_reverse.hpp>
#include <sprout/bit/bit_length.hpp>

namespace sprout {
		namespace fixed {
			namespace detail {
			template<typename Container, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
			bitrev_table_impl(
				Container const& cont, sprout::index_tuple<Indexes...>,
				std::size_t bit_length,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				return sprout::remake<Container>(
					cont,
					sprout::size(cont),
					(Indexes >= offset && Indexes < offset + size
						? sprout::bit_reverse_in(
							static_cast<typename sprout::container_traits<Container>::value_type>(Indexes - offset),
							bit_length
							)
						: *sprout::next(sprout::internal_begin(cont), Indexes)
						)...
					);
			}
		}	// namespace detail
		//
		// bitrev_table
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		bitrev_table(Container const& cont) {
			return sprout::fixed::detail::bitrev_table_impl(
				cont,
				sprout::container_indexes<Container>::make(),
				sprout::empty(cont) ? 0
					: sprout::bit_length(sprout::size(cont) - 1)
					,
				sprout::internal_begin_offset(cont),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::bitrev_table;
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FFT_FIXED_BITREV_TABLE_HPP
