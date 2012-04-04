#ifndef SPROUT_ALGORITHM_FIT_UNIQUE_HPP
#define SPROUT_ALGORITHM_FIT_UNIQUE_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/unique.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/detail/overlap_count.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type unique_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::unique(cont)),
					offset,
					offset + sprout::size(cont) - sprout::detail::overlap_count(sprout::begin(cont), sprout::end(cont))
					);
			}
		}	// namespace detail
		//
		// unique
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type unique(
			Container const& cont
			)
		{
			return sprout::fit::detail::unique_impl(cont, sprout::internal_begin_offset(cont));
		}

		namespace detail {
			template<typename Container, typename BinaryPredicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type unique_impl(
				Container const& cont,
				BinaryPredicate pred,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::unique(cont, pred)),
					offset,
					offset + sprout::size(cont) - sprout::detail::overlap_count(sprout::begin(cont), sprout::end(cont), pred)
					);
			}
		}	// namespace detail
		//
		// unique
		//
		template<typename Container, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type unique(
			Container const& cont,
			BinaryPredicate pred
			)
		{
			return sprout::fit::detail::unique_impl(cont, pred, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_UNIQUE_HPP
