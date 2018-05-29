/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_SWALLOW_HPP
#define SPROUT_UTILITY_SWALLOW_HPP

#include <initializer_list>
#include <sprout/config.hpp>

namespace sprout {
	//
	// swallow_t
	// swallow
	//
	// example:
	//	swallow({(void)pack, 0}...);
	//
	struct swallow_t {
	public:
		template<typename T>
		inline SPROUT_CXX14_CONSTEXPR void
		operator()(std::initializer_list<T>) const SPROUT_NOEXCEPT {}
	};
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::swallow_t swallow = {};
	}	// anonymous-namespace
//	template<typename T>
//	inline SPROUT_CONSTEXPR sprout::swallow_t
//	operator,(sprout::swallow_t, T&&) SPROUT_NOEXCEPT {
//		return sprout::swallow;
//	}
//	template<typename T>
//	inline SPROUT_CONSTEXPR sprout::swallow_t
//	operator,(T&&, sprout::swallow_t) SPROUT_NOEXCEPT {
//		return sprout::swallow;
//	}

	//
	// unused_t
	// unused
	//
	struct unused_t {
	public:
		template<typename... Args>
		SPROUT_CONSTEXPR sprout::unused_t const&
		operator()(Args&&...) const SPROUT_NOEXCEPT {
			return *this;
		}
	};
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::unused_t unused = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_SWALLOW_HPP
