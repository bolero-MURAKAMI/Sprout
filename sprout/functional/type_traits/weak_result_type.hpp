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
	}	// namespace detail

	//
	// weak_result_type
	//
	template<typename F>
	struct weak_result_type
		: public sprout::detail::weak_result_type_impl<typename std::remove_cv<F>::type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_WEAK_RESULT_TYPE_HPP
