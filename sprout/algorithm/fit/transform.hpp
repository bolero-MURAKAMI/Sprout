#ifndef SPROUT_ALGORITHM_FIT_TRANSFORM_HPP
#define SPROUT_ALGORITHM_FIT_TRANSFORM_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/transform.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include <sprout/iterator/type_traits/is_iterator.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result, typename UnaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			transform_impl(
				InputIterator first, InputIterator last, Result const& result, UnaryOperation op,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::transform(first, last, result, op)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(sprout::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// transform
		//
		template<typename InputIterator, typename Result, typename UnaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		transform(InputIterator first, InputIterator last, Result const& result, UnaryOperation op) {
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::transform_impl(first, last, result, op, sprout::internal_begin_offset(result));
		}

		namespace detail {
			template<typename InputIterator1, typename InputIterator2, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			transform_impl(
				InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, Result const& result, BinaryOperation op,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::transform(first1, last1, first2, result, op)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(sprout::distance(first1, last1), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// transform
		//
		template<typename InputIterator1, typename InputIterator2, typename Result, typename BinaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, Result const& result, BinaryOperation op) {
			static_assert(sprout::is_forward_iterator<InputIterator1>::value, "Sorry, not implemented.");
			return sprout::fit::detail::transform_impl(first1, last1, first2, result, op, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_TRANSFORM_HPP
