/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_MEM_FUN_REF_HPP
#define SPROUT_FUNCTIONAL_MEM_FUN_REF_HPP

#include <sprout/config.hpp>
#include <sprout/functional/base.hpp>

namespace sprout {
	// D.8.2.2 adaptors (deprecated)

	template<typename Ret, typename T>
	class mem_fun_ref_t
		: public sprout::unary_function<T, Ret>
	{
	private:
		Ret (T::*f_)();
	public:
		explicit SPROUT_CONSTEXPR mem_fun_ref_t(Ret (T::*pf)())
			: f_(pf)
		{}
		SPROUT_CONSTEXPR Ret operator()(T& r) const {
			return (r.*f_)();
		}
	};

	template<typename Ret, typename T>
	class const_mem_fun_ref_t
		: public sprout::unary_function<T, Ret>
	{
	private:
		Ret (T::*f_)() const;
	public:
		explicit SPROUT_CONSTEXPR const_mem_fun_ref_t(Ret (T::*pf)() const)
			: f_(pf)
		{}
		SPROUT_CONSTEXPR Ret operator()(const T& r) const {
			return (r.*f_)();
		}
	};

	template<typename Ret, typename T, typename Arg>
	class mem_fun1_ref_t
		: public sprout::binary_function<T, Arg, Ret>
	{
	private:
		Ret (T::*f_)(Arg);
	public:
		explicit SPROUT_CONSTEXPR mem_fun1_ref_t(Ret (T::*pf)(Arg))
			: f_(pf)
		{}
		SPROUT_CONSTEXPR Ret operator()(T& r, Arg x) const {
			return (r.*f_)(x);
		}
	};

	template<typename Ret, typename T, typename Arg>
	class const_mem_fun1_ref_t
		: public sprout::binary_function<T, Arg, Ret>
	{
	private:
		Ret (T::*f_)(Arg) const;
	public:
		explicit SPROUT_CONSTEXPR const_mem_fun1_ref_t(Ret (T::*pf)(Arg) const)
			: f_(pf)
		{}
		SPROUT_CONSTEXPR Ret operator()(const T& r, Arg x) const {
			return (r.*f_)(x);
		}
	};

	template<typename Ret, typename T>
	inline SPROUT_CONSTEXPR sprout::mem_fun_ref_t<Ret, T>
	mem_fun_ref(Ret (T::*f)()) {
		return sprout::mem_fun_ref_t<Ret, T>(f);
	}

	template<typename Ret, typename T>
	inline SPROUT_CONSTEXPR sprout::const_mem_fun_ref_t<Ret, T>
	mem_fun_ref(Ret (T::*f)() const) {
		return sprout::const_mem_fun_ref_t<Ret, T>(f);
	}

	template<typename Ret, typename T, typename Arg>
	inline SPROUT_CONSTEXPR sprout::mem_fun1_ref_t<Ret, T, Arg>
	mem_fun_ref(Ret (T::*f)(Arg)) {
		return sprout::mem_fun1_ref_t<Ret, T, Arg>(f);
	}

	template<typename Ret, typename T, typename Arg>
	inline SPROUT_CONSTEXPR sprout::const_mem_fun1_ref_t<Ret, T, Arg>
	mem_fun_ref(Ret (T::*f)(Arg) const) {
		return sprout::const_mem_fun1_ref_t<Ret, T, Arg>(f);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_MEM_FUN_REF_HPP
