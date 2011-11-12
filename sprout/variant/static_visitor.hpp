#ifndef SPROUT_VARIANT_STATIC_VISITOR_HPP
#define SPROUT_VARIANT_STATIC_VISITOR_HPP

#include <sprout/config.hpp>

namespace sprout {
	template<typename R = void>
	class static_visitor {
	public:
		typedef R result_type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_STATIC_VISITOR_HPP
