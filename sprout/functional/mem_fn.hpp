/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_MEM_FN_HPP
#define SPROUT_FUNCTIONAL_MEM_FN_HPP

#include <functional>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/functional/base.hpp>

namespace sprout {
	// 20.8.10 member function adaptors

	namespace detail {
		template<typename Res, typename... Args>
		struct maybe_unary_or_binary_function {};
		template<typename Res, typename T1>
		struct maybe_unary_or_binary_function<Res, T1>
			: public sprout::unary_function<T1, Res>
		{};
		template<typename Res, typename T1, typename T2>
		struct maybe_unary_or_binary_function<Res, T1, T2>
			: public sprout::binary_function<T1, T2, Res>
		{};

		template<typename T, bool>
		struct mem_fn_const_or_non {
		public:
			typedef T const& type;
		};
		template<typename T>
		struct mem_fn_const_or_non<T, false> {
		public:
			typedef T& type;
		};
	}	// namespace detail

	//
	// mem_fn_adaptor
	//
	template<typename MemberPointer>
	class mem_fn_adaptor;
	template<typename Res, typename Class, typename... Args>
	class mem_fn_adaptor<Res (Class::*)(Args...)>
		: public sprout::detail::maybe_unary_or_binary_function<Res, Class*, Args...>
	{
	public:
		typedef Res result_type;
	private:
		typedef Res (Class::*functor)(Args...);
	private:
		Res (Class::*pmf_)(Args...);
	private:
		template<typename T>
		Res call(T& object, Class const volatile*, Args... args) const {
			return (object.*pmf_)(sprout::forward<Args>(args)...);
		}
		template<typename T>
		Res call(T& ptr, void const volatile*, Args... args) const {
			return ((*ptr).*pmf_)(sprout::forward<Args>(args)...);
		}
	public:
		explicit SPROUT_CONSTEXPR mem_fn_adaptor(Res (Class::*pmf)(Args...))
			: pmf_(pmf)
		{}
		Res operator()(Class& object, Args... args) const {
			return (object.*pmf_)(sprout::forward<Args>(args)...);
		}
		Res operator()(Class* object, Args... args) const {
			return (object->*pmf_)(sprout::forward<Args>(args)...);
		}
		template<typename T>
		Res operator()(T& object, Args... args) const {
			return call(object, &object, sprout::forward<Args>(args)...);
		}
	};
	template<typename Res, typename Class, typename... Args>
	class mem_fn_adaptor<Res (Class::*)(Args...) const>
		: public sprout::detail::maybe_unary_or_binary_function<Res, Class const*, Args...>
	{
	public:
		typedef Res result_type;
	private:
		typedef Res (Class::*functor)(Args...) const;
	private:
		Res (Class::*pmf_)(Args...) const;
	private:
		template<typename T>
		SPROUT_CONSTEXPR Res call(T const& object, Class const volatile*, Args... args) const {
			return (object.*pmf_)(sprout::forward<Args>(args)...);
		}
		template<typename T>
		SPROUT_CONSTEXPR Res call(T const& ptr, void const volatile*, Args... args) const {
			return ((*ptr).*pmf_)(sprout::forward<Args>(args)...);
		}
	public:
		explicit SPROUT_CONSTEXPR mem_fn_adaptor(Res (Class::*pmf)(Args...) const)
			: pmf_(pmf)
		{}
		SPROUT_CONSTEXPR Res operator()(Class const& object, Args... args) const {
			return (object.*pmf_)(sprout::forward<Args>(args)...);
		}
		SPROUT_CONSTEXPR Res operator()(Class const* object, Args... args) const {
			return (object->*pmf_)(sprout::forward<Args>(args)...);
		}
		template<typename T>
		SPROUT_CONSTEXPR Res operator()(T const& object, Args... args) const {
			return call(object, &object, sprout::forward<Args>(args)...);
		}
	};
	template<typename Res, typename Class, typename... Args>
	class mem_fn_adaptor<Res (Class::*)(Args...) volatile>
		: public sprout::detail::maybe_unary_or_binary_function<Res, Class volatile*, Args...>
	{
	public:
		typedef Res result_type;
	private:
		typedef Res (Class::*functor)(Args...) volatile;
	private:
		Res (Class::*pmf_)(Args...) volatile;
	private:
		template<typename T>
		Res call(T& object, Class const volatile*, Args... args) const {
			return (object.*pmf_)(sprout::forward<Args>(args)...);
		}
		template<typename T>
		Res call(T& ptr, void const volatile*, Args... args) const {
			return ((*ptr).*pmf_)(sprout::forward<Args>(args)...);
		}
	public:
		explicit SPROUT_CONSTEXPR mem_fn_adaptor(Res (Class::*pmf)(Args...) volatile)
			: pmf_(pmf)
		{}
		Res operator()(Class volatile& object, Args... args) const {
			return (object.*pmf_)(sprout::forward<Args>(args)...);
		}
		Res operator()(Class volatile* object, Args... args) const {
			return (object->*pmf_)(sprout::forward<Args>(args)...);
		}
		template<typename T>
		Res operator()(T& object, Args... args) const {
			return call(object, &object, sprout::forward<Args>(args)...);
		}
	};
	template<typename Res, typename Class, typename... Args>
	class mem_fn_adaptor<Res (Class::*)(Args...) const volatile>
		: public sprout::detail::maybe_unary_or_binary_function<Res, Class const volatile*, Args...>
	{
	public:
		typedef Res result_type;
	private:
		typedef Res (Class::*functor)(Args...) const volatile;
	private:
		Res (Class::*pmf_)(Args...) const volatile;
	private:
		template<typename T>
		SPROUT_CONSTEXPR Res call(T const& object, Class const volatile*, Args... args) const {
			return (object.*pmf_)(sprout::forward<Args>(args)...);
		}
		template<typename T>
		SPROUT_CONSTEXPR Res call(T const& ptr, void const volatile*, Args... args) const {
			return ((*ptr).*pmf_)(sprout::forward<Args>(args)...);
		}
	public:
		explicit SPROUT_CONSTEXPR mem_fn_adaptor(Res (Class::*pmf)(Args...) const volatile)
			: pmf_(pmf)
		{}
		SPROUT_CONSTEXPR Res operator()(Class const volatile& object, Args... args) const {
			return (object.*pmf_)(sprout::forward<Args>(args)...);
		}
		SPROUT_CONSTEXPR Res operator()(Class const volatile* object, Args... args) const {
			return (object->*pmf_)(sprout::forward<Args>(args)...);
		}
		template<typename T>
		SPROUT_CONSTEXPR Res operator()(T const& object, Args... args) const {
			return call(object, &object, sprout::forward<Args>(args)...);
		}
	};

	template<typename Res, typename Class>
	class mem_fn_adaptor<Res Class::*> {
	private:
		typedef char one;
		struct two { char v[2]; };
	private:
		template<typename T>
		static T& get_ref();
		template<typename T>
		static one check_const(T&, Class*);
		template<typename T, typename Up>
		static one check_const(T&, Up* const*);
		template<typename T, typename Up>
		static two check_const(T&, Up const* const*);
		template<typename T>
		static two check_const(T&, Class const*);
		template<typename T>
		static two check_const(T&, const volatile void*);
	public:
		template<typename T>
		struct result_type
			: public sprout::detail::mem_fn_const_or_non<
				Res,
				(sizeof(two) == sizeof(check_const<T>(get_ref<T>(), (T*)0)))
			>
		{};
		template<typename Signature>
		struct result;
		template<typename CVMem, typename T>
		struct result<CVMem(T)>
			: public result_type<T>
		{};
		template<typename CVMem, typename T>
		struct result<CVMem(T&)>
			: public result_type<T>
		{};
	private:
		Res Class::* pm_;
	private:
		template<typename T>
		Res& call(T& object, Class*) const {
			return object.*pm_;
		}
		template<typename T, typename Up>
		Res& call(T& object, Up* const*) const {
			return (*object).*pm_;
		}
		template<typename T, typename Up>
		const Res& call(T& object, Up const* const*) const {
			return (*object).*pm_;
		}
		template<typename T>
		Res const& call(T& object, Class const*) const {
			return object.*pm_;
		}
		template<typename T>
		const Res& call(T& ptr, void const volatile*) const {
			return (*ptr).*pm_;
		}
	public:
		explicit SPROUT_CONSTEXPR mem_fn_adaptor(Res Class::* pm)
			: pm_(pm)
		{}
		Res& operator()(Class& object) const {
			return object.*pm_;
		}
		SPROUT_CONSTEXPR Res const& operator()(Class const& object) const {
			return object.*pm_;
		}
		Res& operator()(Class* object) const {
			return object->*pm_;
		}
		SPROUT_CONSTEXPR Res const& operator()(Class const* object) const {
			return object->*pm_;
		}
		template<typename T>
		typename result_type<T>::type operator()(T& unknown) const {
			return call(unknown, &unknown);
		}
	};

	//
	// mem_fn
	//
	template<typename T, typename Class>
	inline SPROUT_CONSTEXPR sprout::mem_fn_adaptor<T Class::*>
	mem_fn(T Class::* pm) {
		return sprout::mem_fn_adaptor<T Class::*>(pm);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_MEM_FN_HPP
