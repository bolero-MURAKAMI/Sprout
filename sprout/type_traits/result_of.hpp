/*=============================================================================
	Copyright (c) 2011-2015 Bolero MURAKAMI
	https://github.com/bolero-MURAKAMI/Sprout

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_RESULT_OF_HPP
#define SPROUT_TYPE_TRAITS_RESULT_OF_HPP

#if defined(_MSC_VER) && (_MSC_VER <= 1900)
#	include <functional>
#endif
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/detail/nil_base.hpp>
#include <sprout/type/type_tuple.hpp>

namespace sprout {
#if defined(_MSC_VER) && (_MSC_VER <= 1900)
	//
	// result_of
	//
	using std::result_of;
#else
	//
	// result_of
	//
	namespace detail {
		struct result_of_memfun_ref_helper {
		public:
			template<typename F, typename T, typename... Args>
			static sprout::identity<decltype((std::declval<T>().*std::declval<F>())(std::declval<Args>()...))> test(int);
			template<typename...>
			static sprout::detail::nil_base test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<
			typename MemPtr, typename Arg, typename... Args,
			typename Base_ = sprout::identity<decltype(sprout::detail::result_of_memfun_ref_helper::test<MemPtr, Arg, Args...>(0))>::type
		>
		struct result_of_memfun_ref
			: public Base_
		{};
#else
		template<typename MemPtr, typename Arg, typename... Args>
		struct result_of_memfun_ref
			: public sprout::identity<decltype(sprout::detail::result_of_memfun_ref_helper::test<MemPtr, Arg, Args...>(0))>::type
		{};
#endif

		struct result_of_memfun_deref_helper {
		public:
			template<typename F, typename T, typename... Args>
			static sprout::identity<decltype(((*std::declval<T>()).*std::declval<F>())(std::declval<Args>()...))> test(int);
			template<typename...>
			static sprout::detail::nil_base test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<
			typename MemPtr, typename Arg, typename... Args,
			typename Base_ = sprout::identity<decltype(sprout::detail::result_of_memfun_deref_helper::test<MemPtr, Arg, Args...>(0))>::type
		>
		struct result_of_memfun_deref
			: public Base_
		{};
#else
		template<typename MemPtr, typename Arg, typename... Args>
		struct result_of_memfun_deref
			: public sprout::identity<decltype(sprout::detail::result_of_memfun_deref_helper::test<MemPtr, Arg, Args...>(0))>::type
		{};
#endif

		struct result_of_memobj_ref_helper {
		public:
			template<typename F, typename T>
			static sprout::identity<decltype(std::declval<T>().*std::declval<F>())> test(int);
			template<typename, typename>
			static sprout::detail::nil_base test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<
			typename MemPtr, typename Arg,
			typename Base_ = sprout::identity<decltype(sprout::detail::result_of_memobj_ref_helper::test<MemPtr, Arg>(0))>::type
		>
		struct result_of_memobj_ref
			: public Base_
		{};
#else
		template<typename MemPtr, typename Arg>
		struct result_of_memobj_ref
			: public sprout::identity<decltype(sprout::detail::result_of_memobj_ref_helper::test<MemPtr, Arg>(0))>::type
		{};
#endif

		struct result_of_memobj_deref_helper {
		public:
			template<typename F, typename T>
			static sprout::identity<decltype((*std::declval<T>()).*std::declval<F>())> test(int);
			template<typename, typename>
			static sprout::detail::nil_base test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<
			typename MemPtr, typename Arg,
			typename Base_ = sprout::identity<decltype(sprout::detail::result_of_memobj_deref_helper::test<MemPtr, Arg>(0))>::type
		>
		struct result_of_memobj_deref
			: public Base_
		{};
#else
		template<typename MemPtr, typename Arg>
		struct result_of_memobj_deref
			: public sprout::identity<decltype(sprout::detail::result_of_memobj_deref_helper::test<MemPtr, Arg>(0))>::type
		{};
#endif

		template<typename MemPtr, typename Arg>
		struct result_of_memobj_impl;
		template<typename R, typename Class, typename Arg>
		struct result_of_memobj_impl<R Class::*, Arg> {
		public:
			typedef typename std::remove_cv<typename std::remove_reference<Arg>::type>::type argval_type;
			typedef R Class::* mem_ptr_type;
			typedef typename std::conditional<
				std::is_same<argval_type, Class>::value || std::is_base_of<Class, argval_type>::value,
				sprout::detail::result_of_memobj_ref<mem_ptr_type, Arg>,
				sprout::detail::result_of_memobj_deref<mem_ptr_type, Arg>
			>::type type;
		};
		template<typename MemPtr, typename Arg>
		struct result_of_memobj
			: public sprout::detail::result_of_memobj_impl<MemPtr, Arg>::type
		{};

		template<typename MemPtr, typename Arg, typename... Args>
		struct result_of_memfun_impl;
		template<typename R, typename Class, typename Arg, typename... Args>
		struct result_of_memfun_impl<R Class::*, Arg, Args...> {
		public:
			typedef typename std::remove_cv<typename std::remove_reference<Arg>::type>::type argval_type;
			typedef R Class::* mem_ptr_type;
			typedef typename std::conditional<
				std::is_same<argval_type, Class>::value || std::is_base_of<Class, argval_type>::value,
				result_of_memfun_ref<mem_ptr_type, Arg, Args...>,
				result_of_memfun_deref<mem_ptr_type, Arg, Args...>
			>::type type;
		};
		template<typename MemPtr, typename Arg, typename... Args>
		struct result_of_memfun
			: public sprout::detail::result_of_memfun_impl<MemPtr, Arg, Args...>::type
		{};

		struct result_of_other_impl {
		public:
			template<typename F, typename... Args>
			static sprout::identity<decltype(std::declval<F>()(std::declval<Args>()...))> test(int);
			template<typename, typename...>
			static sprout::detail::nil_base test(...);
		};
#if defined(_MSC_VER)
		template<typename Functor, typename... Args>
		struct result_of_other_base {
		public:
			typedef sprout::identity<decltype(sprout::detail::result_of_other_impl::test<Functor, Args...>(0))>::type type;
		};
		template<typename Functor, typename... Args>
		struct result_of_other
			: public sprout::detail::result_of_other_base<Functor, Args...>::type
		{};
#else
		template<typename Functor, typename... Args>
		struct result_of_other
			: public sprout::identity<decltype(sprout::detail::result_of_other_impl::test<Functor, Args...>(0))>::type
		{};
#endif

		template<bool, bool, typename Functor, typename... Args>
		struct result_of_impl
			: public sprout::identity<sprout::detail::nil_base>::type
		{};
		template<typename MemPtr, typename Arg>
		struct result_of_impl<true, false, MemPtr, Arg>
			: public sprout::detail::result_of_memobj<typename std::decay<MemPtr>::type, Arg>
		{};
		template<typename MemPtr, typename Arg, typename... Args>
		struct result_of_impl<false, true, MemPtr, Arg, Args...>
			: public sprout::detail::result_of_memfun<typename std::decay<MemPtr>::type, Arg, Args...>
		{};
		template<typename Functor, typename... Args>
		struct result_of_impl<false, false, Functor, Args...>
			: public sprout::detail::result_of_other<Functor, Args...>
		{};
	}	//namespace detail
	template<typename Signature>
	struct result_of;
	template<typename Functor, typename... Args>
	struct result_of<Functor(Args...)>
		: public sprout::detail::result_of_impl<
			std::is_member_object_pointer<typename std::remove_reference<Functor>::type>::value,
			std::is_member_function_pointer<typename std::remove_reference<Functor>::type>::value,
			Functor, Args...
		>
	{};
#endif

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename F, typename... ArgTypes>
	using result_of_t = typename sprout::result_of<F(ArgTypes...)>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_RESULT_OF_HPP
