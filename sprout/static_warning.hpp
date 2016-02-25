/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
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
#define SPROUT_STATIC_WARNING_IMPL_2(COND, MSG, LINE) \
	struct sprout_static_warning_line_ ## LINE { \
		struct MSG {}; \
		sprout_static_warning_line_ ## LINE() { \
			::sprout::static_warning<(COND)>:: \
				warn<void***** (MSG::*****)()>(); \
		} \
	}
#define SPROUT_STATIC_WARNING_IMPL(COND, MSG) \
	SPROUT_STATIC_WARNING_IMPL_2(COND, MSG, __LINE__)
#define SPROUT_STATIC_WARNING(COND) \
	SPROUT_STATIC_WARNING_IMPL(COND, static_warning_failed)

#endif	// #ifndef SPROUT_STATIC_WARNING_HPP
