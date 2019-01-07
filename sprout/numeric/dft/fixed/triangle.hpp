/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_DFT_FIXED_TRINAGLE_HPP
#define SPROUT_NUMERIC_DFT_FIXED_TRINAGLE_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/detail/container_complate.hpp>
#include <sprout/numeric/dft/detail/triangle.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
			triangle_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::value_type const& frequency,
				typename sprout::container_traits<Container>::value_type const& amplitude,
				typename sprout::container_traits<Container>::value_type const& phase,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Container>::difference_type offset,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				return sprout::remake<Container>(
					cont, size,
					(Indexes >= offset && Indexes < offset + size
						? sprout::detail::triangle_value(frequency, amplitude, phase, Indexes)
						: *sprout::next(sprout::internal_begin(cont), Indexes)
						)...
					);
			}
			template<typename Container>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
			triangle(
				Container const& cont,
				typename sprout::container_traits<Container>::value_type const& frequency,
				typename sprout::container_traits<Container>::value_type const& amplitude,
				typename sprout::container_traits<Container>::value_type const& phase
				)
			{
				return sprout::fixed::detail::triangle_impl(
					cont,
					frequency,
					amplitude,
					phase,
					sprout::container_indexes<Container>::make(),
					sprout::internal_begin_offset(cont),
					sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// triangle
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		triangle(
			Container const& cont,
			typename sprout::container_traits<Container>::value_type const& frequency = 1,
			typename sprout::container_traits<Container>::value_type const& amplitude = 1,
			typename sprout::container_traits<Container>::value_type const& phase = 0
			)
		{
			return sprout::fixed::detail::triangle(cont, frequency, amplitude, phase);
		}

		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Container>::type
		triangle(
			typename sprout::container_traits<Container>::value_type const& frequency = 1,
			typename sprout::container_traits<Container>::value_type const& amplitude = 1,
			typename sprout::container_traits<Container>::value_type const& phase = 0
			)
		{
			return sprout::fixed::triangle(sprout::pit<Container>(), frequency, amplitude, phase);
		}
	}	// namespace fixed

	using sprout::fixed::triangle;
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIXED_TRINAGLE_HPP
