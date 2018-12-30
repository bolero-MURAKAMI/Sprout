/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_EQUIV_HPP
#define SPROUT_FUNCTIONAL_EQUIV_HPP

#include <functional>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/functional/type_traits/is_strict_function.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace detail {
		template<typename Compare, bool IsStrict = sprout::is_strict_binary_function<Compare>::value>
		class equiv_adaptor_impl;

		template<typename Compare>
		class equiv_adaptor_impl<Compare, true> {
		public:
			typedef typename Compare::first_argument_type first_argument_type;
			typedef typename Compare::second_argument_type second_argument_type;
			typedef bool result_type;
		protected:
			Compare fn;
		public:
			explicit SPROUT_CONSTEXPR equiv_adaptor_impl(Compare const& comp)
				: fn(comp)
			{}
			SPROUT_CONSTEXPR bool operator()(typename Compare::first_argument_type const& x, typename Compare::second_argument_type const& y) const {
				return !fn(x, y) && !fn(y, x);
			}
		};

		template<typename Compare>
		class equiv_adaptor_impl<Compare, false> {
		protected:
			Compare fn;
		public:
			explicit SPROUT_CONSTEXPR equiv_adaptor_impl(Compare const& comp)
				: fn(comp)
			{}
			template<typename T, typename U>
			SPROUT_CONSTEXPR decltype(!std::declval<Compare const&>()(std::declval<T>(), std::declval<U>()) && !std::declval<Compare const&>()(std::declval<U>(), std::declval<T>()))
			operator()(T&& x, U&& y) const {
				return !fn(SPROUT_FORWARD(T, x), SPROUT_FORWARD(U, y)) && !fn(SPROUT_FORWARD(U, y), SPROUT_FORWARD(T, x));
			}
		};
	}	// namespace detail

	//
	// equiv_adaptor
	//
	template<typename Compare = void>
	class equiv_adaptor
		: public sprout::detail::equiv_adaptor_impl<Compare>
	{
	public:
		explicit SPROUT_CONSTEXPR equiv_adaptor(Compare const& comp)
			: sprout::detail::equiv_adaptor_impl<Compare>(comp)
		{}
	};
	template<>
	class equiv_adaptor<void>
		: public sprout::detail::equiv_adaptor_impl<sprout::less<> >
	{
	public:
		SPROUT_CONSTEXPR equiv_adaptor()
			: sprout::detail::equiv_adaptor_impl<sprout::less<> >(sprout::less<>())
		{}
		explicit SPROUT_CONSTEXPR equiv_adaptor(sprout::less<> const& comp)
			: sprout::detail::equiv_adaptor_impl<sprout::less<> >(comp)
		{}
	};

	//
	// equiv
	//
	template<typename Compare>
	inline SPROUT_CONSTEXPR sprout::equiv_adaptor<Compare>
	equiv(Compare const& comp) {
		return sprout::equiv_adaptor<Compare>(comp);
	}
	inline SPROUT_CONSTEXPR sprout::equiv_adaptor<>
	equiv() {
		return sprout::equiv_adaptor<>();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_EQUIV_HPP
