/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_FIXED_EXCLUSIVE_SCAN_HPP
#define SPROUT_NUMERIC_FIXED_EXCLUSIVE_SCAN_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
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
				sprout::container_traits<Result>::static_size == sizeof...(Args) + 1,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			exclusive_scan_impl_1(
				InputIterator const&, InputIterator const&, Result const& result,
				typename sprout::container_traits<Result>::size_type,
				typename sprout::container_traits<Result>::value_type const& value,
				typename sprout::container_traits<Result>::value_type const& temp,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args..., value);
			}
			template<typename InputIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args) + 1,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			exclusive_scan_impl_1(
				InputIterator const& first, InputIterator const& last, Result const& result,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::value_type const& value,
				typename sprout::container_traits<Result>::value_type const& temp,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) + 1 < size
					? exclusive_scan_impl_1(sprout::next(first), last, result, size, value + temp, *first, args..., value)
					: sprout::detail::container_complate(result, args..., value)
					;
			}
			template<typename InputIterator, typename Result, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == 0,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			exclusive_scan_impl(
				InputIterator const&, InputIterator const&, Result const& result, T,
				typename sprout::container_traits<Result>::size_type
				)
			{
				return sprout::detail::container_complate(result);
			}
			template<typename InputIterator, typename Result, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == 1,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			exclusive_scan_impl(
				InputIterator const&, InputIterator const&, Result const& result, T init,
				typename sprout::container_traits<Result>::size_type
				)
			{
				return sprout::detail::container_complate(result, init);
			}
			template<typename InputIterator, typename Result, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				(sprout::container_traits<Result>::static_size > 1),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			exclusive_scan_impl(
				InputIterator const& first, InputIterator const& last, Result const& result, T init,
				typename sprout::container_traits<Result>::size_type size
				)
			{
				return first != last
					? exclusive_scan_impl_1(sprout::next(first), last, result, size, init, *first)
					: sprout::detail::container_complate(result, init)
					;
			}
		}	// namespace detail
		//
		// exclusive_scan
		//
		template<typename InputIterator, typename Result, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		exclusive_scan(InputIterator first, InputIterator last, Result const& result, T init) {
			return sprout::fixed::detail::exclusive_scan_impl(first, last, result, init, sprout::size(result));
		}
		template<typename Result, typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		exclusive_scan(InputIterator first, InputIterator last, T init) {
			return sprout::fixed::exclusive_scan<Result>(first, last, sprout::pit<Result>(), init);
		}

		namespace detail {
			template<typename InputIterator, typename Result, typename BinaryOperation, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args) + 1,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			exclusive_scan_impl_1(
				InputIterator const&, InputIterator const&, Result const& result, BinaryOperation,
				typename sprout::container_traits<Result>::size_type,
				typename sprout::container_traits<Result>::value_type const& value,
				typename sprout::container_traits<Result>::value_type const& temp,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args..., value);
			}
			template<typename InputIterator, typename Result, typename BinaryOperation, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args) + 1,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			exclusive_scan_impl_1(
				InputIterator const& first, InputIterator const& last, Result const& result, BinaryOperation binary_op,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::value_type const& value,
				typename sprout::container_traits<Result>::value_type const& temp,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) + 1 < size
					? exclusive_scan_impl_1(sprout::next(first), last, result, binary_op, size, binary_op(value, temp), *first, args..., value)
					: sprout::detail::container_complate(result, args..., value)
					;
			}
			template<typename InputIterator, typename Result, typename T, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == 0,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			exclusive_scan_impl(
				InputIterator const&, InputIterator const&, Result const& result, T, BinaryOperation,
				typename sprout::container_traits<Result>::size_type
				)
			{
				return sprout::detail::container_complate(result);
			}
			template<typename InputIterator, typename Result, typename T, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == 1,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			exclusive_scan_impl(
				InputIterator const&, InputIterator const&, Result const& result, T init, BinaryOperation,
				typename sprout::container_traits<Result>::size_type
				)
			{
				return sprout::detail::container_complate(result, init);
			}
			template<typename InputIterator, typename Result, typename T, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				(sprout::container_traits<Result>::static_size > 1),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			exclusive_scan_impl(
				InputIterator const& first, InputIterator const& last, Result const& result, T init, BinaryOperation binary_op,
				typename sprout::container_traits<Result>::size_type size
				)
			{
				return first != last
					? exclusive_scan_impl_1(sprout::next(first), last, result, binary_op, size, init, *first)
					: sprout::detail::container_complate(result, init)
					;
			}
		}	// namespace detail
		//
		// exclusive_scan
		//
		template<typename InputIterator, typename Result, typename T, typename BinaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		exclusive_scan(InputIterator first, InputIterator last, Result const& result, T init, BinaryOperation binary_op) {
			return sprout::fixed::detail::exclusive_scan_impl(first, last, result, init, binary_op, sprout::size(result));
		}
		template<typename Result, typename InputIterator, typename T, typename BinaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		exclusive_scan(InputIterator first, InputIterator last, T init, BinaryOperation binary_op) {
			return sprout::fixed::exclusive_scan(first, last, sprout::pit<Result>(), init, binary_op);
		}
	}	// namespace fixed

	template<
		typename InputIterator, typename Result, typename T,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	exclusive_scan(InputIterator first, InputIterator last, Result const& result, T init) {
		return sprout::fixed::exclusive_scan(first, last, result, init);
	}
	template<typename Result, typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	exclusive_scan(InputIterator first, InputIterator last, T init) {
		return sprout::fixed::exclusive_scan<Result>(first, last, init);
	}

	template<
		typename InputIterator, typename Result, typename T, typename BinaryOperation,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	exclusive_scan(InputIterator first, InputIterator last, Result const& result, T init, BinaryOperation binary_op) {
		return sprout::fixed::exclusive_scan(first, last, result, init, binary_op);
	}
	template<typename Result, typename InputIterator, typename T, typename BinaryOperation>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	exclusive_scan(InputIterator first, InputIterator last, T init, BinaryOperation binary_op) {
		return sprout::fixed::exclusive_scan<Result>(first, last, init, binary_op);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FIXED_EXCLUSIVE_SCAN_HPP
