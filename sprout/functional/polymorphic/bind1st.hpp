#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIND1ST_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_BIND1ST_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// binder1st_
	// bind1st_
	//
	template<typename Fn, typename T>
	class binder1st_ {
	protected:
		Fn op;
		T value;
	public:
		SPROUT_CONSTEXPR binder1st_(Fn&& x, T&& y)
			: op(sprout::forward<Fn>(x)), value(sprout::forward<T>(y))
		{}
		template<typename Arg>
		SPROUT_CONSTEXPR decltype(op(value, std::declval<Arg>()))
		operator()(Arg&& x)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(op(value, std::declval<Arg>())))
		{
			return op(value, sprout::forward<Arg>(x));
		}
	};
	template<typename Fn, typename T>
	inline SPROUT_CONSTEXPR sprout::binder1st_<typename std::decay<Fn>::type, typename std::decay<T>::type>
	bind1st_(Fn&& fn, T&& x) {
		typedef sprout::binder1st_<typename std::decay<Fn>::type, typename std::decay<T>::type> type;
		return type(sprout::forward<Fn>(fn), sprout::forward<T>(x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIND1ST_HPP
