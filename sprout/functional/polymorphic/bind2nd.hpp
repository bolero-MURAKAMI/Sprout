/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIND2ND_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_BIND2ND_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// binder2nd_
	// bind2nd_
	//
	template<typename Fn, typename T>
	class binder2nd_ {
	protected:
		Fn op;
		T value;
	public:
		SPROUT_CONSTEXPR binder2nd_(Fn&& x, T&& y)
			: op(SPROUT_FORWARD(Fn, x)), value(SPROUT_FORWARD(T, y))
		{}
		template<typename Arg>
		SPROUT_CONSTEXPR decltype(op(std::declval<Arg>(), value))
		operator()(Arg&& x)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(op(std::declval<Arg>(), value)))
		{
			return op(SPROUT_FORWARD(Arg, x), value);
		}
	};
	template<typename Fn, typename T>
	inline SPROUT_CONSTEXPR sprout::binder2nd_<typename std::decay<Fn>::type, typename std::decay<T>::type>
	bind2nd_(Fn&& fn, T&& x) {
		typedef sprout::binder2nd_<typename std::decay<Fn>::type, typename std::decay<T>::type> type;
		return type(SPROUT_FORWARD(Fn, fn), SPROUT_FORWARD(T, x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIND2ND_HPP
