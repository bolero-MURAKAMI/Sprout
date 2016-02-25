/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIT_PARTIAL_SORT_HPP
#define SPROUT_ALGORITHM_FIT_PARTIAL_SORT_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/partial_sort.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
			partial_sort_impl(
				Container const& cont, typename sprout::container_traits<Container>::const_iterator middle, Compare comp,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::partial_sort(cont, middle, comp)),
					offset,
					offset + sprout::distance(sprout::begin(cont), middle)
					);
			}
		}	// namespace detail
		//
		// partial_sort
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
		partial_sort(Container const& cont, typename sprout::container_traits<Container>::const_iterator middle, Compare comp) {
			return sprout::fit::detail::partial_sort_impl(cont, middle, comp, sprout::internal_begin_offset(cont));
		}

		namespace detail {
			template<typename Container>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
			partial_sort_impl(
				Container const& cont, typename sprout::container_traits<Container>::const_iterator middle,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::partial_sort(cont, middle)),
					offset,
					offset + sprout::distance(sprout::begin(cont), middle)
					);
			}
		}	// namespace detail
		//
		// partial_sort
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Container>::type
		partial_sort(Container const& cont, typename sprout::container_traits<Container>::const_iterator middle) {
			return sprout::fit::detail::partial_sort_impl(cont, middle, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_PARTIAL_SORT_HPP
