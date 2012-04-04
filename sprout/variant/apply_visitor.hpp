#ifndef SPROUT_VARIANT_APPLY_VISITOR_HPP
#define SPROUT_VARIANT_APPLY_VISITOR_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	template<typename Visitor, typename Visitable>
	inline SPROUT_CONSTEXPR typename Visitor::result_type apply_visitor(
		Visitor&& visitor,
		Visitable&& visitable
		)
	{
		return sprout::forward<Visitable>(visitable).apply_visitor(sprout::forward<Visitor>(visitor));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_APPLY_VISITOR_HPP
