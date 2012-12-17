#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_CALL_FUN_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_CALL_FUN_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// call_fun_t
	// call_fun_
	//
	struct call_fun_t {
	public:
		template<typename F, typename... As>
		SPROUT_CONSTEXPR decltype(std::declval<F>()(std::declval<As>()...))
		operator()(F&& f, As&&... as)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::declval<F>()(std::declval<As>()...)))
		{
			return sprout::forward<F>(f)(sprout::forward<As>(as)...);
		}
	};
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::call_fun_t call_fun_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_CALL_FUN_HPP
