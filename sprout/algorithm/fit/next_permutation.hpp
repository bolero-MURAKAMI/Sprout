/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_FIT_NEXT_PERMUTATION_HPP
#define SPROUT_ALGORITHM_FIT_NEXT_PERMUTATION_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/next_permutation.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Permutation>
			inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fit::results::algorithm<Container>::type, bool>
			next_permutation_impl_1(
				Container const& cont,
				Permutation const& perm,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::pair<typename sprout::fit::results::algorithm<Container>::type, bool>(
					sprout::sub_copy(
						sprout::get_internal(perm.first),
						offset,
						offset + sprout::size(cont)
						),
					perm.second
					);
			}

			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fit::results::algorithm<Container>::type, bool>
			next_permutation_impl(
				Container const& cont, Compare comp,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return next_permutation_impl_1(cont, sprout::fixed::next_permutation(cont, comp), offset);
			}
		}	// namespace detail
		//
		// next_permutation
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fit::results::algorithm<Container>::type, bool>
		next_permutation(Container const& cont, Compare comp) {
			return sprout::fit::detail::next_permutation_impl(cont, comp, sprout::internal_begin_offset(cont));
		}

		namespace detail {
			template<typename Container>
			inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fit::results::algorithm<Container>::type, bool>
			next_permutation_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return next_permutation_impl_1(cont, sprout::fixed::next_permutation(cont), offset);
			}
		}	// namespace detail
		//
		// next_permutation
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fit::results::algorithm<Container>::type, bool>
		next_permutation(Container const& cont) {
			return sprout::fit::detail::next_permutation_impl(cont, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_NEXT_PERMUTATION_HPP
