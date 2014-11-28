/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MEMORY_POINTER_CAST_HPP
#define SPROUT_MEMORY_POINTER_CAST_HPP

#include <memory>
#include <sprout/config.hpp>
#include <sprout/utility/dyn_cast.hpp>
#include <sprout/utility/reinter_cast.hpp>

namespace sprout {
	//
	// static_pointer_cast
	// const_pointer_cast
	// dynamic_pointer_cast
	// reinterpret_pointer_cast
	//
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR T*
	static_pointer_cast(U* p) {
		return static_cast<T*>(p);
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR T*
	const_pointer_cast(U* p) {
		return const_cast<T*>(p);
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR T*
	dynamic_pointer_cast(U* p) {
		return sprout::dyn_cast<T*>(p);
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR T*
	reinterpret_pointer_cast(U* p) {
		return sprout::reinter_cast<T*>(p);
	}

#if !defined(SPROUT_NO_CXX11_SMART_PTR)
	template<typename T, typename U>
	inline SPROUT_NON_CONSTEXPR std::shared_ptr<T>
	static_pointer_cast(std::shared_ptr<U> const& p) {
		return std::static_pointer_cast<T>(p);
	}
	template<typename T, typename U>
	inline SPROUT_NON_CONSTEXPR std::shared_ptr<T>
	const_pointer_cast(std::shared_ptr<U> const& p) {
		return std::const_pointer_cast<T>(p);
	}
	template<typename T, typename U>
	inline SPROUT_NON_CONSTEXPR std::shared_ptr<T>
	dynamic_pointer_cast(std::shared_ptr<U> const& p) {
		return std::dynamic_pointer_cast<T>(p);
	}
	template<typename T, typename U>
	inline SPROUT_NON_CONSTEXPR std::shared_ptr<T>
	reinterpret_pointer_cast(std::shared_ptr<U> const& p) {
		typedef typename std::shared_ptr<T>::element_type element_type;
		return std::shared_ptr<T>(p, reinterpret_cast<element_type*>(p.get()));
	}
#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_MEMORY_POINTER_CAST_HPP
