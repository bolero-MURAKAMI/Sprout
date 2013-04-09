#ifndef SPROUT_ALGORITHM_STRING_FIT_TO_LOWER_COPY_HPP
#define SPROUT_ALGORITHM_STRING_FIT_TO_LOWER_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/string/fixed/to_lower_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/iterator/type_traits/category.hpp>

namespace sprout {
	namespace algorithm {
		namespace fit {
			namespace detail {
				template<typename InputIterator, typename Result>
				inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
				to_lower_copy_impl(
					InputIterator first, InputIterator last, Result const& result,
					typename sprout::container_traits<Result>::difference_type offset
					)
				{
					return sprout::sub_copy(
						sprout::get_internal(sprout::algorithm::fixed::to_lower_copy(first, last, result)),
						offset,
						offset + sprout::fit_size(result, sprout::distance(first, last))
						);
				}
			}	// namespace detail
			//
			// to_lower_copy
			//
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			to_lower_copy(InputIterator first, InputIterator last, Result const& result) {
				static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
				return sprout::algorithm::fit::detail::to_lower_copy_impl(first, last, result, sprout::internal_begin_offset(result));
			}
		}	// namespace fit
	}	// namespace algorithm

	namespace fit {
		using sprout::algorithm::fit::to_lower_copy;
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_STRING_FIT_TO_LOWER_COPY_HPP
