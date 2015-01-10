/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIND1ST_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_BIND1ST_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// binder1st_
	// bind1st_
	//
	template<typename Fn, typename T>
	class binder1st_ {
	protected:
		Fn op;
		T value;
	public:
		SPROUT_CONSTEXPR binder1st_(Fn&& x, T&& y)
			: op(SPROUT_FORWARD(Fn, x)), value(SPROUT_FORWARD(T, y))
		{}
		template<typename Arg>
		SPROUT_CONSTEXPR decltype(op(value, std::declval<Arg>()))
		operator()(Arg&& x)
		const SPROUT_NOEXCEPT_IF_EXPR(op(value, std::declval<Arg>()))
		{
			return op(value, SPROUT_FORWARD(Arg, x));
		}
	};
	template<typename Fn, typename T>
	inline SPROUT_CONSTEXPR sprout::binder1st_<typename std::decay<Fn>::type, typename std::decay<T>::type>
	bind1st_(Fn&& fn, T&& x) {
		typedef sprout::binder1st_<typename std::decay<Fn>::type, typename std::decay<T>::type> type;
		return type(SPROUT_FORWARD(Fn, fn), SPROUT_FORWARD(T, x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIND1ST_HPP
