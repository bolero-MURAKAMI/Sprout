/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_BIND2ND_HPP
#define SPROUT_FUNCTIONAL_BIND2ND_HPP

#include <type_traits>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/functional/base.hpp>
#include <sprout/functional/type_traits/is_strict_function.hpp>

namespace sprout {

	// D.9.3 Class template binder2nd
	namespace detail {
		template<typename Fn, typename T = void, typename = void>
		class binder2nd;
		template<typename Fn, typename T>
		class binder2nd<
			Fn, T,
			typename std::enable_if<sprout::is_strict_binary_function<Fn>::value>::type
		>
			: public sprout::unary_function<typename Fn::first_argument_type, typename Fn::result_type>
		{
		public:
			typedef typename std::conditional<
				std::is_void<T>::value,
				typename Fn::second_argument_type,
				T
			>::type value_type;
		protected:
			Fn op;
			value_type value;
		public:
			SPROUT_CONSTEXPR binder2nd(Fn const& x, value_type const& y)
				: op(x), value(y)
			{}
			SPROUT_CONSTEXPR typename Fn::result_type
			operator()(typename Fn::first_argument_type const& x) const {
				return op(x, value);
			}
		};
		template<typename Fn, typename T>
		class binder2nd<
			Fn, T,
			typename std::enable_if<!sprout::is_strict_binary_function<Fn>::value>::type
		> {
		public:
			typedef T value_type;
		protected:
			Fn op;
			value_type value;
		public:
			SPROUT_CONSTEXPR binder2nd(Fn const& x, value_type const& y)
				: op(x), value(y)
			{}
			template<typename U>
			SPROUT_CONSTEXPR decltype(std::declval<Fn const&>()(std::declval<U const&>(), std::declval<value_type const&>()))
			operator()(U const& x) const {
				return op(x, value);
			}
		};
	}	// namespace detail
	template<typename Fn, typename T = void>
	class binder2nd
		: public sprout::detail::binder2nd<Fn, T>
	{
	public:
		typedef typename sprout::detail::binder2nd<Fn, T>::value_type value_type;
	public:
		SPROUT_CONSTEXPR binder2nd(Fn const& x, value_type const& y)
			: sprout::detail::binder2nd<Fn, T>(x, y)
		{}
	};

	// D.9.3 bind2nd
	template<typename Fn, typename T>
	inline SPROUT_CONSTEXPR sprout::binder2nd<Fn, T>
	bind2nd(Fn const& fn, T const& x) {
		return sprout::binder2nd<Fn, T>(fn, typename sprout::binder2nd<Fn, T>::value_type(x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_BIND2ND_HPP
