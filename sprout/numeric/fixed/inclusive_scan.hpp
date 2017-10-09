/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_FIXED_INCLUSIVE_SCAN_HPP
#define SPROUT_NUMERIC_FIXED_INCLUSIVE_SCAN_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/detail/container_complate.hpp>
#include <sprout/numeric/fixed/partial_sum.hpp>

namespace sprout {
	namespace fixed {
		//
		// inclusive_scan
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		inclusive_scan(InputIterator first, InputIterator last, Result const& result) {
			return sprout::fixed::partial_sum(first, last, result);
		}
		template<typename Result, typename InputIterator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		inclusive_scan(InputIterator first, InputIterator last) {
			return sprout::fixed::partial_sum<Result>(first, last);
		}

		template<typename InputIterator, typename Result, typename BinaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		inclusive_scan(InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op) {
			return sprout::fixed::partial_sum(first, last, result, binary_op);
		}
		template<typename Result, typename InputIterator, typename BinaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		inclusive_scan(InputIterator first, InputIterator last, BinaryOperation binary_op) {
			return sprout::fixed::partial_sum<Result>(first, last, binary_op);
		}

		namespace detail {
			template<typename InputIterator, typename Result, typename BinaryOperation, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == 0,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			inclusive_scan_impl(
				InputIterator, InputIterator, Result const& result, BinaryOperation, T,
				typename sprout::container_traits<Result>::size_type
				)
			{
				return sprout::remake<Result>(result, sprout::size(result));
			}
			template<typename InputIterator, typename Result, typename BinaryOperation, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == 1,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			inclusive_scan_impl(
				InputIterator, InputIterator, Result const& result, BinaryOperation, T init,
				typename sprout::container_traits<Result>::size_type
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), init);
			}
			template<typename InputIterator, typename Result, typename BinaryOperation, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				(sprout::container_traits<Result>::static_size > 1),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			inclusive_scan_impl(
				InputIterator const& first, InputIterator const& last, Result const& result, BinaryOperation binary_op, T init,
				typename sprout::container_traits<Result>::size_type size
				)
			{
				return first != last
					? partial_sum_impl_1(first, last, result, binary_op, size, init)
					: sprout::detail::container_complate(result, init)
					;
			}
		}	// namespace detail
		//
		// inclusive_scan
		//
		template<typename InputIterator, typename Result, typename BinaryOperation, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		inclusive_scan(InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op, T init) {
			return sprout::fixed::detail::inclusive_scan_impl(first, last, result, binary_op, init, sprout::size(result));
		}
		template<typename Result, typename InputIterator, typename BinaryOperation, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		inclusive_scan(InputIterator first, InputIterator last, BinaryOperation binary_op, T init) {
			return sprout::fixed::inclusive_scan(first, last, sprout::pit<Result>(), binary_op, init);
		}
	}	// namespace fixed

	template<
		typename InputIterator, typename Result,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	inclusive_scan(InputIterator first, InputIterator last, Result const& result) {
		return sprout::fixed::inclusive_scan(first, last, result);
	}
	template<typename Result, typename InputIterator>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	inclusive_scan(InputIterator first, InputIterator last) {
		return sprout::fixed::inclusive_scan<Result>(first, last);
	}

	template<
		typename InputIterator, typename Result, typename BinaryOperation,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	inclusive_scan(InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op) {
		return sprout::fixed::inclusive_scan(first, last, result, binary_op);
	}
	template<typename Result, typename InputIterator, typename BinaryOperation>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	inclusive_scan(InputIterator first, InputIterator last, BinaryOperation binary_op) {
		return sprout::fixed::inclusive_scan<Result>(first, last, binary_op);
	}

	template<
		typename InputIterator, typename Result, typename BinaryOperation, typename T,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	inclusive_scan(InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op, T init) {
		return sprout::fixed::inclusive_scan(first, last, result, binary_op, init);
	}
	template<typename Result, typename InputIterator, typename BinaryOperation, typename T>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	inclusive_scan(InputIterator first, InputIterator last, BinaryOperation binary_op, T init) {
		return sprout::fixed::inclusive_scan<Result>(first, last, binary_op, init);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FIXED_INCLUSIVE_SCAN_HPP
