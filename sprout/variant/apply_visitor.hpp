#ifndef SPROUT_VARIANT_APPLY_VISITOR_HPP
#define SPROUT_VARIANT_APPLY_VISITOR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/has_xxx.hpp>

namespace sprout {
	//
	// has_visitor_result
	//
	SPROUT_HAS_XXX_TEMPLATE_DEF_LAZY(visitor_result);

	namespace detail {
		template<typename Visitor, typename Visitable, typename = void>
		struct visitor_result_impl;
		template<typename Visitor, typename Visitable>
		struct visitor_result_impl<
			Visitor, Visitable,
			typename std::enable_if<sprout::has_visitor_result<Visitable>::value>::type
		>
			: public Visitable::template visitor_result<Visitor, Visitable>
		{};
		template<typename Visitor, typename Visitable>
		struct visitor_result_impl<
			Visitor, Visitable,
			typename std::enable_if<!sprout::has_visitor_result<Visitable>::value>::type
		> {
		public:
			typedef typename Visitor::result_type type;
		};
	}	// namespace detail
	//
	// visitor_result
	//
	template<typename Visitor, typename Visitable>
	struct visitor_result
		: public sprout::detail::visitor_result_impl<Visitor, Visitable>
	{};

	//
	// apply_visitor
	//
	template<typename Visitor, typename Visitable>
	inline SPROUT_CONSTEXPR typename sprout::visitor_result<
		typename std::remove_reference<Visitor>::type,
		typename std::remove_reference<Visitable>::type
	>::type
	apply_visitor(Visitor&& visitor, Visitable&& visitable) {
		return sprout::forward<Visitable>(visitable).apply_visitor(sprout::forward<Visitor>(visitor));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_APPLY_VISITOR_HPP
