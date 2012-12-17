#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_ADDRESS_OF_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_ADDRESS_OF_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// address_of_t
	// address_of_
	//
	struct address_of_t {
	public:
		template<typename T>
		SPROUT_CONSTEXPR decltype(&std::declval<T>())
		operator()(T&& x)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(&std::declval<T>()))
		{
			return &sprout::forward<T>(x);
		}
	};
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::address_of_t address_of_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_ADDRESS_OF_HPP
