/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_ENABLER_IF_HPP
#define SPROUT_TYPE_TRAITS_ENABLER_IF_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// enabler_t
	// enabler
	//
	typedef void* enabler_t;
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::enabler_t enabler = {};
	}	// anonymous-namespace
#else
	extern enabler_t enabler;
#endif
	//
	// enabler_if
	//
	template<bool C>
	class enabler_if
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
		: public std::enable_if<C, sprout::enabler_t>
#else
		: public std::enable_if<C, sprout::enabler_t&>
#endif
	{};
	//
	// disabler_if
	//
	template<bool C>
	struct disabler_if
		: public sprout::enabler_if<!C>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<bool C>
	using enabler_if_t = typename sprout::enabler_if<C>::type;
	template<bool C>
	using disabler_if_t = typename sprout::disabler_if<C>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_ENABLER_IF_HPP
