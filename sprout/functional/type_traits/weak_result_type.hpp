/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_WEAK_RESULT_TYPE_HPP
#define SPROUT_FUNCTIONAL_TYPE_TRAITS_WEAK_RESULT_TYPE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/functional/type_traits/inherit_if_type.hpp>
#include <sprout/workaround/base_class_construct.hpp>
#include <sprout/detail/predef.hpp>

namespace sprout {
	namespace detail {
		template<typename F>
		struct weak_result_type_impl
			: public sprout::inherit_if_result_type<F>
		{};
		template<typename F>
		struct weak_result_type_impl<F const>
			: public sprout::detail::weak_result_type_impl<F>
		{};
		template<typename F>
		struct weak_result_type_impl<F volatile>
			: public sprout::detail::weak_result_type_impl<F>
		{};
		template<typename F>
		struct weak_result_type_impl<F const volatile>
			: public sprout::detail::weak_result_type_impl<F>
		{};
#if SPROUT_CLANG_OR_LATER(3, 6, 0)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wambiguous-ellipsis"
#endif
		template<typename R, typename... Args>
		struct weak_result_type_impl<R (Args...)> {
		public:
			typedef R result_type;
		};
		template<typename R, typename... Args>
		struct weak_result_type_impl<R (Args......)> {
		public:
			typedef R result_type;
		};
		template<typename R, typename... Args>
		struct weak_result_type_impl<R (&)(Args...)> {
		public:
			typedef R result_type;
		};
		template<typename R, typename... Args>
		struct weak_result_type_impl<R (&)(Args......)> {
		public:
			typedef R result_type;
		};
		template<typename R, typename... Args>
		struct weak_result_type_impl<R (*)(Args...)> {
		public:
			typedef R result_type;
		};
		template<typename R, typename... Args>
		struct weak_result_type_impl<R (*)(Args......)> {
		public:
			typedef R result_type;
		};
		template<typename R, typename Class, typename... Args>
		struct weak_result_type_impl<R (Class::*)(Args...)> {
		public:
			typedef R result_type;
		};
		template<typename R, typename Class, typename... Args>
		struct weak_result_type_impl<R (Class::*)(Args......)> {
		public:
			typedef R result_type;
		};
#if SPROUT_CLANG_OR_LATER(3, 6, 0)
#	pragma clang diagnostic pop
#endif
	}	// namespace detail

	//
	// weak_result_type
	//
	template<typename F>
	struct weak_result_type
		: public sprout::detail::weak_result_type_impl<typename std::remove_cv<F>::type>
	{
#ifdef SPROUT_WORKAROUND_NEEDS_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT
	public:
		SPROUT_CONSTEXPR weak_result_type()
			SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT(sprout::detail::weak_result_type_impl<typename std::remove_cv<F>::type>)
		SPROUT_EXPLICIT_EMPTY_BASE_CLASS_CONSTRUCT_BODY
#endif
	};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using weak_result_type_t = typename sprout::weak_result_type<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_WEAK_RESULT_TYPE_HPP
