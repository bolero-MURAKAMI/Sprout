/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STATIC_WARNING_HPP
#define SPROUT_STATIC_WARNING_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// static_warning
	//
	template<bool C>
	struct static_warning;
	template<>
	struct static_warning<true> {
		template<typename Message>
		static void warn() {}
	};
	template <>
	struct static_warning<false> {
		template<typename Message>
		static void warn() {
			Message static_warning_failed;
		}
	};
}	// namespace sprout

//
// SPROUT_STATIC_WARNING
//
#define SPROUT_STATIC_WARNING_IMPL_2(cond, msg, line) \
	struct sprout_static_warning_line_ ## line { \
		struct msg {}; \
		sprout_static_warning_line_ ## line() { \
			::sprout::static_warning<(cond)>:: \
				warn<void***** (msg::*****)()>(); \
		} \
	}
#define SPROUT_STATIC_WARNING_IMPL(cond, msg) \
	SPROUT_STATIC_WARNING_IMPL_2(cond, msg, __LINE__)
#define SPROUT_STATIC_WARNING(cond) \
	SPROUT_STATIC_WARNING_IMPL(cond, static_warning_failed)

#endif	// #ifndef SPROUT_STATIC_WARNING_HPP
