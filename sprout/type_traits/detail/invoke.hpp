/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_DETAIL_INVOKE_HPP
#define SPROUT_TYPE_TRAITS_DETAIL_INVOKE_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/voider.hpp>
#include <sprout/detail/nil_base.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace detail {
		template<typename F, typename... Args>
		inline SPROUT_CONSTEXPR decltype(std::declval<F>()(std::declval<Args>()...))
		invoke(F&& f, Args&&... args) SPROUT_NOEXCEPT_IF_EXPR(std::declval<F>()(std::declval<Args>()...)) {
			return SPROUT_FORWARD(F, f)(SPROUT_FORWARD(Args, args)...);
		}

		template<typename Base, typename T, typename Derived>
		inline SPROUT_CONSTEXPR decltype(std::declval<Derived>().*(std::declval<T Base::*>()))
		invoke(T Base::* pm, Derived&& d) SPROUT_NOEXCEPT_IF_EXPR(std::declval<Derived>().*(std::declval<T Base::*>())) {
			return SPROUT_FORWARD(Derived, d).*(pm);
		}

		template<typename PMD, typename Pointer>
		inline SPROUT_CONSTEXPR decltype((*std::declval<Pointer>()).*(std::declval<PMD>()))
		invoke(PMD&& pmd, Pointer&& ptr) SPROUT_NOEXCEPT_IF_EXPR((*std::declval<Pointer>()).*(std::declval<PMD>())) {
			return SPROUT_FORWARD(Pointer, ptr).*(SPROUT_FORWARD(PMD, pmd));
		}

		template<typename Base, typename T, typename Derived, typename... Args>
		inline SPROUT_CONSTEXPR decltype((std::declval<Derived>().*(std::declval<T Base::*>()))(std::declval<Args>()...))
		invoke(T Base::* pm, Derived&& d, Args&&... args) SPROUT_NOEXCEPT_IF_EXPR((std::declval<Derived>().*(std::declval<T Base::*>()))(std::declval<Args>()...)) {
			return (SPROUT_FORWARD(Derived, d).*(pm))(SPROUT_FORWARD(Args, args)...);
		}

		template<typename PMF, typename Pointer, typename... Args>
		inline SPROUT_CONSTEXPR decltype(((*std::declval<Pointer>()).*(std::declval<PMF>()))(std::declval<Args>()...))
		invoke(PMF&& pmf, Pointer&& ptr, Args&&... args) SPROUT_NOEXCEPT_IF_EXPR(((*std::declval<Pointer>()).*(std::declval<PMF>()))(std::declval<Args>()...)) {
			return (SPROUT_FORWARD(Pointer, ptr).*(SPROUT_FORWARD(PMF, pmf)))(SPROUT_FORWARD(Args, args)...);
		}

		template<typename R, typename F, typename... Args>
		inline SPROUT_CONSTEXPR R
		invoke(F&&, Args&&...) SPROUT_NOEXCEPT_IF_EXPR(R(std::declval<F>()(std::declval<Args>()...)));

		template<typename R, typename Base, typename T, typename Derived>
		inline SPROUT_CONSTEXPR decltype(R(std::declval<Derived>().*(std::declval<T Base::*>())))
		invoke(T Base::*, Derived&&) SPROUT_NOEXCEPT_IF_EXPR(R(std::declval<Derived>().*(std::declval<T Base::*>())));

		template<typename R, typename PMD, typename Pointer>
		inline SPROUT_CONSTEXPR decltype(R((*std::declval<Pointer>()).*(std::declval<PMD>())))
		invoke(PMD&&, Pointer&&) SPROUT_NOEXCEPT_IF_EXPR(R((*std::declval<Pointer>()).*(std::declval<PMD>())));

		template<typename R, typename Base, typename T, typename Derived, typename... Args>
		inline SPROUT_CONSTEXPR decltype(R((std::declval<Derived>().*(std::declval<T Base::*>()))(std::declval<Args>()...)))
		invoke(T Base::*, Derived&&, Args&&...) SPROUT_NOEXCEPT_IF_EXPR(R((std::declval<Derived>().*(std::declval<T Base::*>()))(std::declval<Args>()...)));

		template<typename R, typename PMF, typename Pointer, typename... Args>
		inline SPROUT_CONSTEXPR decltype(R(((*std::declval<Pointer>()).*(std::declval<PMF>()))(std::declval<Args>()...)))
		invoke(PMF&&, Pointer&&, Args&&...) SPROUT_NOEXCEPT_IF_EXPR(R(((*std::declval<Pointer>()).*(std::declval<PMF>()))(std::declval<Args>()...)));
	}	// namespace detail

	namespace detail {
		template<typename Void, typename F, typename... Args>
		struct invoke_result
			: public sprout::detail::nil_base
		{};
		template<typename F, typename... Args>
		struct invoke_result<typename sprout::voider<decltype(sprout::detail::invoke(std::declval<F>(), std::declval<Args>()...))>::type, F, Args...>
			: public sprout::identity<decltype(sprout::detail::invoke(std::declval<F>(), std::declval<Args>()...))>
		{};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_DETAIL_INVOKE_HPP
