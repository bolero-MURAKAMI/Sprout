/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_MEM_FUN_HPP
#define SPROUT_FUNCTIONAL_MEM_FUN_HPP

#include <sprout/config.hpp>
#include <sprout/functional/base.hpp>

namespace sprout {
	// D.8.2.2 adaptors (deprecated)

	template<typename Ret, typename T>
	class mem_fun_t
		: public sprout::unary_function<T*, Ret>
	{
	private:
		Ret (T::*f_)();
	public:
		explicit SPROUT_CONSTEXPR mem_fun_t(Ret (T::*pf)())
			: f_(pf)
		{}
		SPROUT_CONSTEXPR Ret operator()(T* p) const {
			return (p->*f_)();
		}
	};

	template<typename Ret, typename T>
	class const_mem_fun_t
		: public sprout::unary_function<const T*, Ret>
	{
	private:
		Ret (T::*f_)() const;
	public:
		explicit SPROUT_CONSTEXPR const_mem_fun_t(Ret (T::*pf)() const)
			: f_(pf)
		{}
		SPROUT_CONSTEXPR Ret operator()(const T* p) const {
			return (p->*f_)();
		}
	};

	template<typename Ret, typename T, typename Arg>
	class mem_fun1_t
		: public sprout::binary_function<T*, Arg, Ret>
	{
	private:
		Ret (T::*f_)(Arg);
	public:
		explicit SPROUT_CONSTEXPR mem_fun1_t(Ret (T::*pf)(Arg))
			: f_(pf)
		{}
		SPROUT_CONSTEXPR Ret operator()(T* p, Arg x) const {
			return (p->*f_)(x);
		}
	};

	template<typename Ret, typename T, typename Arg>
	class const_mem_fun1_t
		: public sprout::binary_function<const T*, Arg, Ret>
	{
	private:
		Ret (T::*f_)(Arg) const;
	public:
		explicit SPROUT_CONSTEXPR const_mem_fun1_t(Ret (T::*pf)(Arg) const)
			: f_(pf)
		{}
		SPROUT_CONSTEXPR Ret operator()(const T* p, Arg x) const {
			return (p->*f_)(x);
		}
	};

	template<typename Ret, typename T>
	inline SPROUT_CONSTEXPR sprout::mem_fun_t<Ret, T>
	mem_fun(Ret (T::*f)()) {
		return sprout::mem_fun_t<Ret, T>(f);
	}

	template<typename Ret, typename T>
	inline SPROUT_CONSTEXPR sprout::const_mem_fun_t<Ret, T>
	mem_fun(Ret (T::*f)() const) {
		return sprout::const_mem_fun_t<Ret, T>(f);
	}

	template<typename Ret, typename T, typename Arg>
	inline SPROUT_CONSTEXPR sprout::mem_fun1_t<Ret, T, Arg>
	mem_fun(Ret (T::*f)(Arg)) {
		return sprout::mem_fun1_t<Ret, T, Arg>(f);
	}

	template<typename Ret, typename T, typename Arg>
	inline SPROUT_CONSTEXPR sprout::const_mem_fun1_t<Ret, T, Arg>
	mem_fun(Ret (T::*f)(Arg) const) {
		return sprout::const_mem_fun1_t<Ret, T, Arg>(f);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_MEM_FUN_HPP
