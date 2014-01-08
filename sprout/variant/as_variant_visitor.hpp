/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VARIANT_AS_VARIANT_VISITOR_HPP
#define SPROUT_VARIANT_AS_VARIANT_VISITOR_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/variant/static_variant_visitor.hpp>

namespace sprout {
	//
	// variant_visitor_wrapper
	//
	template<typename Visitor>
	class variant_visitor_wrapper
		: public sprout::static_variant_visitor
	{
	public:
		typedef Visitor visitor_type;
		typedef sprout::value_holder<visitor_type&> holder_type;
	private:
		holder_type v_;
	public:
		SPROUT_CONSTEXPR explicit variant_visitor_wrapper(typename holder_type::param_type v)
			: v_(v)
		{}
		template<typename T>
		SPROUT_CONSTEXPR auto operator()(T&& t) const
		-> decltype(std::declval<holder_type const>().get()(sprout::forward<T>(t)))
		{
			return v_.get()(sprout::forward<T>(t));
		}
	};

	//
	// as_variant_visitor
	//
	template<typename Visitor>
	inline SPROUT_CONSTEXPR sprout::variant_visitor_wrapper<typename std::remove_reference<typename sprout::lvalue_reference<Visitor>::type>::type>
	as_variant_visitor(Visitor&& visitor) {
		typedef sprout::variant_visitor_wrapper<typename std::remove_reference<typename sprout::lvalue_reference<Visitor>::type>::type> type;
		return type(sprout::lvalue_forward<Visitor>(visitor));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_AS_VARIANT_VISITOR_HPP
