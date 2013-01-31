#ifndef SPROUT_ALGORITHM_FIT_CLAMP_RANGE_COPY_HPP
#define SPROUT_ALGORITHM_FIT_CLAMP_RANGE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/clamp_range_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include <sprout/iterator/type_traits/is_iterator.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result, typename Compare>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			clamp_range_copy_impl(
				InputIterator first, InputIterator last, Result const& result,
				typename std::iterator_traits<InputIterator>::value_type const& low,
				typename std::iterator_traits<InputIterator>::value_type const& high,
				Compare comp,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::clamp_range_copy(first, last, result, low, high, comp)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(sprout::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// clamp_range_copy
		//
		template<typename InputIterator, typename Result, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		clamp_range_copy(
			InputIterator first, InputIterator last, Result const& result,
			typename std::iterator_traits<InputIterator>::value_type const& low,
			typename std::iterator_traits<InputIterator>::value_type const& high,
			Compare comp
			)
		{
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::clamp_range_copy_impl(first, last, result, low, high, comp, sprout::internal_begin_offset(result));
		}

		namespace detail {
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			clamp_range_copy_impl(
				InputIterator first, InputIterator last, Result const& result,
				typename std::iterator_traits<InputIterator>::value_type const& low,
				typename std::iterator_traits<InputIterator>::value_type const& high,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::clamp_range_copy(first, last, result, low, high)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(sprout::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// clamp_range_copy
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		clamp_range_copy(
			InputIterator first, InputIterator last, Result const& result,
			typename std::iterator_traits<InputIterator>::value_type const& low,
			typename std::iterator_traits<InputIterator>::value_type const& high
			)
		{
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::clamp_range_copy_impl(first, last, result, low, high, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_CLAMP_RANGE_COPY_HPP
