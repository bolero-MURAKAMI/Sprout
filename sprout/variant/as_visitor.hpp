#ifndef SPROUT_VARIANT_AS_VISITOR_HPP
#define SPROUT_VARIANT_AS_VISITOR_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/utility/value_holder.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/variant/static_visitor.hpp>
#include <sprout/functional/type_traits/has_type.hpp>
#include <sprout/functional/type_traits/weak_result_type.hpp>

namespace sprout {
	namespace detail {
		template<typename T, typename = void>
		struct result_type_or_void;
		template<typename T>
		struct result_type_or_void<
			T,
			typename std::enable_if<sprout::has_result_type<sprout::weak_result_type<T> >::value>::type
		> {
		public:
			typedef typename sprout::weak_result_type<T>::result_type type;
		};
		template<typename T>
		struct result_type_or_void<
			T,
			typename std::enable_if<!sprout::has_result_type<sprout::weak_result_type<T> >::value>::type
		> {
		public:
			typedef void type;
		};
	}	// namespace detail

	//
	// visitor_wrapper
	//
	template<
		typename Visitor,
		typename R = typename sprout::detail::result_type_or_void<Visitor>::type
	>
	class visitor_wrapper
		: public sprout::static_visitor<R>
	{
	public:
		typedef Visitor visitor_type;
		typedef sprout::value_holder<visitor_type&> holder_type;
	private:
		holder_type v_;
	public:
		SPROUT_CONSTEXPR explicit visitor_wrapper(typename holder_type::param_type v)
			: v_(v)
		{}
		template<typename T>
		SPROUT_CONSTEXPR auto operator()(T&& t)
		-> decltype(std::declval<holder_type const>().get()(sprout::forward<T>(t))) const
		{
			return v_.get()(sprout::forward<T>(t));
		}
	};

	//
	// as_visitor
	//
	template<typename Visitor>
	inline SPROUT_CONSTEXPR sprout::visitor_wrapper<typename std::remove_reference<typename sprout::lvalue_reference<Visitor>::type>::type>
	as_visitor(Visitor&& visitor) {
		typedef sprout::visitor_wrapper<typename std::remove_reference<typename sprout::lvalue_reference<Visitor>::type>::type> type;
		return type(sprout::lvalue_forward<Visitor>(visitor));
	}

	template<typename R, typename Visitor>
	inline SPROUT_CONSTEXPR sprout::visitor_wrapper<typename std::remove_reference<typename sprout::lvalue_reference<Visitor>::type>::type, R>
	as_visitor(Visitor&& visitor) {
		typedef sprout::visitor_wrapper<typename std::remove_reference<typename sprout::lvalue_reference<Visitor>::type>::type, R> type;
		return type(sprout::lvalue_forward<Visitor>(visitor));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_AS_VISITOR_HPP
