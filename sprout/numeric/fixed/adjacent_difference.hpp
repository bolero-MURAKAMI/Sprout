/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_FIXED_ADJACENT_DIFFERENCE_HPP
#define SPROUT_NUMERIC_FIXED_ADJACENT_DIFFERENCE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			adjacent_difference_impl_1(
				InputIterator, InputIterator, Result const& result,
				typename sprout::container_traits<Result>::size_type,
				typename sprout::container_traits<Result>::value_type const&,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			adjacent_difference_impl_1(
				InputIterator first, InputIterator last, Result const& result,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::value_type const& value,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? adjacent_difference_impl_1(sprout::next(first), last, result, size, *first, args..., *first - value)
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == 0,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			adjacent_difference_impl(
				InputIterator, InputIterator, Result const& result,
				typename sprout::container_traits<Result>::size_type
				)
			{
				return sprout::remake<Result>(result, sprout::size(result));
			}
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != 0,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			adjacent_difference_impl_1(
				InputIterator first, InputIterator last, Result const& result,
				typename sprout::container_traits<Result>::size_type size
				)
			{
				return first != last
					? adjacent_difference_impl_1(sprout::next(first), last, result, size, *first, *first)
					: sprout::detail::container_complate(result)
					;
			}
		}	// namespace detail
		//
		// adjacent_difference
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		adjacent_difference(InputIterator first, InputIterator last, Result const& result) {
			return sprout::fixed::detail::adjacent_difference_impl(first, last, result, sprout::size(result));
		}
		template<typename Result, typename InputIterator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		adjacent_difference(InputIterator first, InputIterator last) {
			return sprout::fixed::adjacent_difference(first, last, sprout::pit<Result>());
		}

		namespace detail {
			template<typename InputIterator, typename Result, typename BinaryOperation, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			adjacent_difference_impl_1(
				InputIterator, InputIterator, Result const& result, BinaryOperation,
				typename sprout::container_traits<Result>::size_type,
				typename sprout::container_traits<Result>::value_type const&,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename BinaryOperation, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			adjacent_difference_impl_1(
				InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::value_type const& value,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? adjacent_difference_impl_1(sprout::next(first), last, result, binary_op, size, *first, args..., binary_op(*first, value))
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == 0,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			adjacent_difference_impl(
				InputIterator, InputIterator, Result const& result, BinaryOperation,
				typename sprout::container_traits<Result>::size_type
				)
			{
				return sprout::remake<Result>(result, sprout::size(result));
			}
			template<typename InputIterator, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != 0,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			adjacent_difference_impl_1(
				InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op,
				typename sprout::container_traits<Result>::size_type size
				)
			{
				return first != last
					? adjacent_difference_impl_1(sprout::next(first), last, result, binary_op, size, *first, *first)
					: sprout::detail::container_complate(result)
					;
			}
		}	// namespace detail
		//
		// adjacent_difference
		//
		template<typename InputIterator, typename Result, typename BinaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		adjacent_difference(InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op) {
			return sprout::fixed::detail::adjacent_difference_impl(first, last, result, binary_op, sprout::size(result));
		}
		template<typename Result, typename InputIterator, typename BinaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		adjacent_difference(InputIterator first, InputIterator last, BinaryOperation binary_op) {
			return sprout::fixed::adjacent_difference(first, last, sprout::pit<Result>(), binary_op);
		}
	}	// namespace fixed

	template<
		typename InputIterator, typename Result,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	adjacent_difference(InputIterator first, InputIterator last, Result const& result) {
		return sprout::fixed::adjacent_difference(first, last, result);
	}
	template<typename Result, typename InputIterator>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	adjacent_difference(InputIterator first, InputIterator last) {
		return sprout::fixed::adjacent_difference<Result>(first, last);
	}

	template<
		typename InputIterator, typename Result, typename BinaryOperation,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	adjacent_difference(InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op) {
		return sprout::fixed::adjacent_difference(first, last, result, binary_op);
	}
	template<typename Result, typename InputIterator, typename BinaryOperation>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	adjacent_difference(InputIterator first, InputIterator last, BinaryOperation binary_op) {
		return sprout::fixed::adjacent_difference<Result>(first, last, binary_op);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FIXED_ADJACENT_DIFFERENCE_HPP
