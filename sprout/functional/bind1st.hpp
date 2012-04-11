#ifndef SPROUT_FUNCTIONAL_BIND1ST_HPP
#define SPROUT_FUNCTIONAL_BIND1ST_HPP

#include <sprout/config.hpp>
#include <sprout/functional/base.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// D.9.1 Class template binder1st
	template<typename Fn>
	class binder1st
		: public sprout::unary_function<typename Fn::second_argument_type, typename Fn::result_type>
	{
	protected:
		Fn op;
		typename Fn::first_argument_type value;
	public:
		SPROUT_CONSTEXPR binder1st(Fn const& x, typename Fn::first_argument_type const& y)
			: op(x), value(y)
		{}
		SPROUT_CONSTEXPR typename Fn::result_type operator()(typename Fn::second_argument_type const& x) const {
			return op(value, x);
		}
	};

	// D.9.2 bind1st
	template<typename Fn, typename T>
	SPROUT_CONSTEXPR sprout::binder1st<Fn> bind1st(Fn const& fn, T const& x) {
		return sprout::binder1st<Fn>(fn, typename Fn::first_argument_type(x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_BIND1ST_HPP
