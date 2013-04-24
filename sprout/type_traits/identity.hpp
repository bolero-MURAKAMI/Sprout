#ifndef SPROUT_TYPE_TRAITS_IDENTITY_HPP
#define SPROUT_TYPE_TRAITS_IDENTITY_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// identity
	//
	template<typename T>
	struct identity {
	public:
		typedef T type;
	};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using identity_t = typename sprout::identity<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IDENTITY_HPP
