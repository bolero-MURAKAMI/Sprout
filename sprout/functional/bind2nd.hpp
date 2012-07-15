#ifndef SPROUT_FUNCTIONAL_BIND2ND_HPP
#define SPROUT_FUNCTIONAL_BIND2ND_HPP

#include <sprout/config.hpp>
#include <sprout/functional/base.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// D.9.3 Class template binder2nd
	template<typename Fn>
	class binder2nd
		: public sprout::unary_function<typename Fn::first_argument_type, typename Fn::result_type>
	{
	protected:
		Fn op;
		typename Fn::second_argument_type value;
	public:
		SPROUT_CONSTEXPR binder2nd(Fn const& x, typename Fn::second_argument_type const& y)
			: op(x), value(y)
		{}
		SPROUT_CONSTEXPR typename Fn::result_type operator()(typename Fn::first_argument_type const& x) const {
			return op(x, value);
		}
	};

	// D.9.4 bind2nd
	template<typename Fn, typename T>
	inline SPROUT_CONSTEXPR sprout::binder2nd<Fn> bind2nd(Fn const& op, T const& x) {
		return sprout::binder2nd<Fn>(op, typename Fn::second_argument_type(x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_BIND2ND_HPP
