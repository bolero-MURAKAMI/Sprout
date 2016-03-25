/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_STRING_REF_UDL_HPP
#define SPROUT_UTILITY_STRING_REF_UDL_HPP

#include <sprout/config.hpp>
#include <sprout/utility/string_ref/string_ref.hpp>

#if SPROUT_USE_USER_DEFINED_LITERALS

#include <sprout/workaround/std/cstddef.hpp>

namespace sprout {
	namespace udl {
		//
		// _sr
		//
		inline SPROUT_CONSTEXPR sprout::basic_string_ref<char>
		operator"" _sr(char const* s, std::size_t size) {
			return sprout::basic_string_ref<char>(s, size);
		}
		inline SPROUT_CONSTEXPR sprout::basic_string_ref<wchar_t>
		operator"" _sr(wchar_t const* s, std::size_t size) {
			return sprout::basic_string_ref<wchar_t>(s, size);
		}
#if SPROUT_USE_UNICODE_LITERALS
		inline SPROUT_CONSTEXPR sprout::basic_string_ref<char16_t>
		operator"" _sr(char16_t const* s, std::size_t size) {
			return sprout::basic_string_ref<char16_t>(s, size);
		}
		inline SPROUT_CONSTEXPR sprout::basic_string_ref<char32_t>
		operator"" _sr(char32_t const* s, std::size_t size) {
			return sprout::basic_string_ref<char32_t>(s, size);
		}
#endif
	}	// namespace udl

	using sprout::udl::operator"" _sr;
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_UTILITY_STRING_REF_UDL_HPP
