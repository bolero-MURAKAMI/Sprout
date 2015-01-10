/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_NOT2_HPP
#define SPROUT_FUNCTIONAL_NOT2_HPP

#include <functional>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/functional/type_traits/is_strict_function.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace detail {
		template<typename Predicate, bool IsStrict = sprout::is_strict_binary_function<Predicate>::value>
		class binary_negate_impl;

		template<typename Predicate>
		class binary_negate_impl<Predicate, true> {
		public:
			typedef typename Predicate::first_argument_type first_argument_type;
			typedef typename Predicate::second_argument_type second_argument_type;
			typedef bool result_type;
		protected:
			Predicate fn;
		public:
			explicit SPROUT_CONSTEXPR binary_negate_impl(Predicate const& pred)
				: fn(pred)
			{}
			SPROUT_CONSTEXPR bool operator()(typename Predicate::first_argument_type const& x, typename Predicate::second_argument_type const& y) const {
				return !fn(x, y);
			}
		};

		template<typename Predicate>
		class binary_negate_impl<Predicate, false> {
		protected:
			Predicate fn;
		public:
			explicit SPROUT_CONSTEXPR binary_negate_impl(Predicate const& pred)
				: fn(pred)
			{}
			template<typename T, typename U>
			SPROUT_CONSTEXPR decltype(!std::declval<Predicate const&>()(std::declval<T>(), std::declval<U>()))
			operator()(T&& x, U&& y) const {
				return !fn(SPROUT_FORWARD(T, x), SPROUT_FORWARD(U, y));
			}
		};
	}	// namespace detail

	// 20.8.8 negators
	template<typename Predicate>
	class binary_negate
		: public sprout::detail::binary_negate_impl<Predicate>
	{
	public:
		explicit SPROUT_CONSTEXPR binary_negate(Predicate const& pred)
			: sprout::detail::binary_negate_impl<Predicate>(pred)
		{}
	};

	template<typename Predicate>
	inline SPROUT_CONSTEXPR sprout::binary_negate<Predicate>
	not2(Predicate const& pred) {
		return sprout::binary_negate<Predicate>(pred);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_NOT2_HPP
