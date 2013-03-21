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
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IDENTITY_HPP
