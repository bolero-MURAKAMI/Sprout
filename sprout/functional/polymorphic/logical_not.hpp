#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_LOGICAL_NOT_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_LOGICAL_NOT_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// logical_not_t
	// logical_not_
	//
	struct logical_not_t {
	public:
		template<typename T>
		SPROUT_CONSTEXPR decltype(!std::declval<T>())
		operator()(T&& x)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(!std::declval<T>()))
		{
			return !sprout::forward<T>(x);
		}
	};
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::logical_not_t logical_not_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_LOGICAL_NOT_HPP
