/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VARIANT_VISITOR_RESULT_HPP
#define SPROUT_VARIANT_VISITOR_RESULT_HPP

#include <sprout/config.hpp>
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
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_VISITOR_RESULT_HPP
