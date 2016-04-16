/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_STRING_VIEW_UDL_HPP
#define SPROUT_UTILITY_STRING_VIEW_UDL_HPP

#include <sprout/config.hpp>
#include <sprout/utility/string_view/string_view.hpp>

#if SPROUT_USE_USER_DEFINED_LITERALS

#include <sprout/workaround/std/cstddef.hpp>

namespace sprout {
	namespace udl {
		namespace strings {
			//
			// _sv
			//
			inline SPROUT_CONSTEXPR sprout::basic_string_view<char>
			operator"" _sv(char const* s, std::size_t size) {
				return sprout::basic_string_view<char>(s, size);
			}
			inline SPROUT_CONSTEXPR sprout::basic_string_view<wchar_t>
			operator"" _sv(wchar_t const* s, std::size_t size) {
				return sprout::basic_string_view<wchar_t>(s, size);
			}
#if SPROUT_USE_UNICODE_LITERALS
			inline SPROUT_CONSTEXPR sprout::basic_string_view<char16_t>
			operator"" _sv(char16_t const* s, std::size_t size) {
				return sprout::basic_string_view<char16_t>(s, size);
			}
			inline SPROUT_CONSTEXPR sprout::basic_string_view<char32_t>
			operator"" _sv(char32_t const* s, std::size_t size) {
				return sprout::basic_string_view<char32_t>(s, size);
			}
#endif
		}	// namespace strings

		using sprout::udl::strings::operator"" _sv;
	}	// namespace udl

	using sprout::udl::strings::operator"" _sv;
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_UTILITY_STRING_VIEW_UDL_HPP
