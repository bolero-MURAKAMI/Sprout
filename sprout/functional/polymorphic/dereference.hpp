#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_DEREFERENCE_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_DEREFERENCE_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// dereference_t
	// dereference_
	//
	struct dereference_t {
	public:
		template<typename T>
		SPROUT_CONSTEXPR decltype(*std::declval<T>())
		operator()(T&& x)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(*std::declval<T>()))
		{
			return *sprout::forward<T>(x);
		}
	};
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::dereference_t dereference_{};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_DEREFERENCE_HPP
