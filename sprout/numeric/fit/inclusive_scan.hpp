/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_FIT_INCLUSIVE_SCAN_HPP
#define SPROUT_NUMERIC_FIT_INCLUSIVE_SCAN_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/numeric/fixed/inclusive_scan.hpp>
#include <sprout/algorithm/fit/results.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/iterator/type_traits/category.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			inclusive_scan_impl(
				InputIterator const& first, InputIterator const& last, Result const& result,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::inclusive_scan(first, last, result)),
					offset,
					offset + sprout::fit_size(result, sprout::distance(first, last))
					);
			}
		}	// namespace detail
		//
		// inclusive_scan
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
		inclusive_scan(InputIterator first, InputIterator last, Result const& result) {
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::inclusive_scan_impl(first, last, result, sprout::internal_begin_offset(result));
		}

		namespace detail {
			template<typename InputIterator, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			inclusive_scan_impl(
				InputIterator const& first, InputIterator const& last, Result const& result, BinaryOperation binary_op,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				typedef typename std::iterator_traits<InputIterator>::difference_type diff_type;
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::inclusive_scan(first, last, result, binary_op)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min<diff_type>(sprout::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// inclusive_scan
		//
		template<typename InputIterator, typename Result, typename BinaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
		inclusive_scan(InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op) {
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::inclusive_scan_impl(first, last, result, binary_op, sprout::internal_begin_offset(result));
		}

		namespace detail {
			template<typename InputIterator, typename Result, typename BinaryOperation, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
			inclusive_scan_impl(
				InputIterator const& first, InputIterator const& last, Result const& result, BinaryOperation binary_op, T init,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				typedef typename std::iterator_traits<InputIterator>::difference_type diff_type;
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::inclusive_scan(first, last, result, binary_op, init)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min<diff_type>(sprout::distance(first, last) + 1, sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// inclusive_scan
		//
		template<typename InputIterator, typename Result, typename BinaryOperation, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fit::results::algorithm<Result>::type
		inclusive_scan(InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op, T init) {
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::inclusive_scan_impl(first, last, result, binary_op, init, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FIT_INCLUSIVE_SCAN_HPP
