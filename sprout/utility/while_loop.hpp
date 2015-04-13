/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_WHILE_LOOP_HPP
#define SPROUT_UTILITY_WHILE_LOOP_HPP

#include <sprout/config.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
#ifdef SPROUT_CONFIG_DISABLE_CXX14_CONSTEXPR
	namespace detail {
		template<typename T, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::pair<T, bool>
		while_loop_check(T const& init, Predicate pred) {
			return sprout::pair<T, bool>(init, !pred(init));
		}
		template<typename T, typename UnaryOperation, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::pair<T, bool>
		while_loop_impl_1(sprout::pair<T, bool> const& current, UnaryOperation unary_op, Predicate pred, std::size_t n) {
			return current.second || !pred(current.first) ? current
				: n == 1 ? sprout::detail::while_loop_check<T>(unary_op(current.first), pred)
				: sprout::detail::while_loop_impl_1(
					sprout::detail::while_loop_impl_1(
						current,
						unary_op, pred, n / 2
						),
					unary_op, pred, n - n / 2
					)
				;
		}
		template<typename T, typename UnaryOperation, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::pair<T, bool>
		while_loop_impl(sprout::pair<T, bool> const& current, UnaryOperation unary_op, Predicate pred, std::size_t n) {
			return current.second || !pred(current.first) ? current
				: sprout::detail::while_loop_impl(
					sprout::detail::while_loop_impl_1(
						current,
						unary_op, pred, n
						),
					unary_op, pred, n * 2
					)
				;
		}
	}	// namespace detail

	//
	// while_loop
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename T, typename UnaryOperation, typename Predicate>
	inline SPROUT_CONSTEXPR T
	while_loop(T init, UnaryOperation unary_op, Predicate pred) {
		typedef sprout::pair<T, bool> type;
		return sprout::detail::while_loop_impl(type(init, false), unary_op, pred, 1).second;
	}
#else
	//
	// while_loop
	//
	//	recursion depth:
	//		0
	//
	template<typename T, typename UnaryOperation, typename Predicate>
	inline SPROUT_CXX14_CONSTEXPR T
	while_loop(T init, UnaryOperation unary_op, Predicate pred) {
		while (pred(init)) {
			init = unary_op(init);
		}
		return init;
	}
#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_WHILE_LOOP_HPP
