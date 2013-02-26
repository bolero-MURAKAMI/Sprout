#ifndef SPROUT_ALGORITHM_FIT_REMOVE_COPY_IF_HPP
#define SPROUT_ALGORITHM_FIT_REMOVE_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/count_if.hpp>
#include <sprout/algorithm/fixed/remove_copy_if.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/iterator/type_traits/category.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			remove_copy_if_impl(
				InputIterator first, InputIterator last, Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::remove_copy_if(first, last, result, pred)),
					offset,
					offset + sprout::fit_size(result, sprout::distance(first, last) - sprout::count_if(first, last, pred))
					);
			}
		}	// namespace detail
		//
		// remove_copy_if
		//
		template<typename InputIterator, typename Result, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		remove_copy_if(InputIterator first, InputIterator last, Result const& result, Predicate pred) {
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::remove_copy_if_impl(first, last, result, pred, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REMOVE_COPY_IF_HPP
