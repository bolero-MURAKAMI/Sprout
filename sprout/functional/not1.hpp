#ifndef SPROUT_FUNCTIONAL_NOT1_HPP
#define SPROUT_FUNCTIONAL_NOT1_HPP

#include <functional>
#include <sprout/config.hpp>

namespace sprout {
	// 20.8.8 negators
	template<typename Predicate>
	class unary_negate {
	public:
		typedef typename Predicate::argument_type argument_type;
		typedef bool result_type;
	protected:
		Predicate fn;
	public:
		explicit SPROUT_CONSTEXPR unary_negate(Predicate const& pred)
			: fn(pred)
		{}
		SPROUT_CONSTEXPR bool operator()(typename Predicate::argument_type const& x) const {
			return !fn(x);
		}
	};

	template<typename Predicate>
	inline SPROUT_CONSTEXPR sprout::unary_negate<Predicate> not1(Predicate const& pred) {
		return sprout::unary_negate<Predicate>(pred);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_NOT1_HPP
