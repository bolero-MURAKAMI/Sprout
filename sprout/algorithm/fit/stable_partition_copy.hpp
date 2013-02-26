#ifndef SPROUT_ALGORITHM_FIT_STABLE_PARTITION_COPY_HPP
#define SPROUT_ALGORITHM_FIT_STABLE_PARTITION_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/count_if.hpp>
#include <sprout/algorithm/fixed/stable_partition_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/iterator/type_traits/category.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			stable_partition_copy_impl(
				InputIterator first, InputIterator last, Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::stable_partition_copy(first, last, result, pred)),
					offset,
					offset + sprout::fit_size(result, sprout::count_if(first, last, pred))
					);
			}
		}	// namespace detail
		//
		// stable_partition_copy
		//
		template<typename InputIterator, typename Result, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		stable_partition_copy(InputIterator first, InputIterator last, Result const& result, Predicate pred) {
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::stable_partition_copy_impl(first, last, result, pred, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_STABLE_PARTITION_COPY_HPP
