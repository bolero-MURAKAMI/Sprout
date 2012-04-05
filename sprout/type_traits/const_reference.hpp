#ifndef SPROUT_TYPE_TRAITS_CONST_REFERENCE_HPP
#define SPROUT_TYPE_TRAITS_CONST_REFERENCE_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/as_const.hpp>

namespace sprout {
	//
	// const_reference
	//
	template<typename T>
	struct const_reference {
	public:
		typedef decltype(sprout::as_const(std::declval<T&&>())) type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_CONST_REFERENCE_HPP
