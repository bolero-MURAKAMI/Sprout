#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_PRE_DEC_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_PRE_DEC_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// pre_dec_t
	// pre_dec_
	//
	struct pre_dec_t {
	public:
		template<typename T>
		SPROUT_CONSTEXPR decltype(--std::declval<T>())
		operator()(T&& x)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(--std::declval<T>()))
		{
			return --sprout::forward<T>(x);
		}
	};
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::pre_dec_t pre_dec_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_PRE_DEC_HPP
