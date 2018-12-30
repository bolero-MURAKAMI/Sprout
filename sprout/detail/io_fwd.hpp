/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_IO_FWD_HPP
#define SPROUT_DETAIL_IO_FWD_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		namespace io {
			class ios_flags_saver;
			class ios_precision_saver;
			class ios_width_saver;
			class ios_base_all_saver;

			template<typename Elem, typename Traits = std::char_traits<Elem> >
			class basic_ios_iostate_saver;
			template<typename Elem, typename Traits = std::char_traits<Elem> >
			class basic_ios_exception_saver;
			template<typename Elem, typename Traits = std::char_traits<Elem> >
			class basic_ios_tie_saver;
			template<typename Elem, typename Traits = std::char_traits<Elem> >
			class basic_ios_rdbuf_saver;
			template<typename Elem, typename Traits = std::char_traits<Elem> >
			class basic_ios_fill_saver;
			template<typename Elem, typename Traits = std::char_traits<Elem> >
			class basic_ios_locale_saver;
			template<typename Elem, typename Traits = std::char_traits<Elem> >
			class basic_ios_all_saver;

			typedef sprout::detail::io::basic_ios_iostate_saver<char> ios_iostate_saver;
			typedef sprout::detail::io::basic_ios_iostate_saver<wchar_t> wios_iostate_saver;
#if SPROUT_USE_UNICODE_LITERALS
			typedef sprout::detail::io::basic_ios_iostate_saver<char16_t> u16ios_iostate_saver;
			typedef sprout::detail::io::basic_ios_iostate_saver<char32_t> u32ios_iostate_saver;
#endif

			typedef sprout::detail::io::basic_ios_exception_saver<char> ios_exception_saver;
			typedef sprout::detail::io::basic_ios_exception_saver<wchar_t> wios_exception_saver;
#if SPROUT_USE_UNICODE_LITERALS
			typedef sprout::detail::io::basic_ios_exception_saver<char16_t> u16ios_exception_saver;
			typedef sprout::detail::io::basic_ios_exception_saver<char32_t> u32ios_exception_saver;
#endif

			typedef sprout::detail::io::basic_ios_tie_saver<char> ios_tie_saver;
			typedef sprout::detail::io::basic_ios_tie_saver<wchar_t> wios_tie_saver;
#if SPROUT_USE_UNICODE_LITERALS
			typedef sprout::detail::io::basic_ios_tie_saver<char16_t> u16ios_tie_saver;
			typedef sprout::detail::io::basic_ios_tie_saver<char32_t> u32ios_tie_saver;
#endif

			typedef sprout::detail::io::basic_ios_rdbuf_saver<char> ios_rdbuf_saver;
			typedef sprout::detail::io::basic_ios_rdbuf_saver<wchar_t> wios_rdbuf_saver;
#if SPROUT_USE_UNICODE_LITERALS
			typedef sprout::detail::io::basic_ios_rdbuf_saver<char16_t> u16ios_rdbuf_saver;
			typedef sprout::detail::io::basic_ios_rdbuf_saver<char32_t> u32ios_rdbuf_saver;
#endif

			typedef sprout::detail::io::basic_ios_fill_saver<char> ios_fill_saver;
			typedef sprout::detail::io::basic_ios_fill_saver<wchar_t> wios_fill_saver;
#if SPROUT_USE_UNICODE_LITERALS
			typedef sprout::detail::io::basic_ios_fill_saver<char16_t> u16ios_fill_saver;
			typedef sprout::detail::io::basic_ios_fill_saver<char32_t> u32ios_fill_saver;
#endif

			typedef sprout::detail::io::basic_ios_locale_saver<char> ios_locale_saver;
			typedef sprout::detail::io::basic_ios_locale_saver<wchar_t> wios_locale_saver;
#if SPROUT_USE_UNICODE_LITERALS
			typedef sprout::detail::io::basic_ios_locale_saver<char16_t> u16ios_locale_saver;
			typedef sprout::detail::io::basic_ios_locale_saver<char32_t> u32ios_locale_saver;
#endif

			typedef sprout::detail::io::basic_ios_all_saver<char> ios_all_saver;
			typedef sprout::detail::io::basic_ios_all_saver<wchar_t> wios_all_saver;
#if SPROUT_USE_UNICODE_LITERALS
			typedef sprout::detail::io::basic_ios_all_saver<char16_t> u16ios_all_saver;
			typedef sprout::detail::io::basic_ios_all_saver<char32_t> u32ios_all_saver;
#endif

			class ios_iword_saver;
			class ios_pword_saver;
			class ios_all_word_saver;
		}	// namespace io
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_IO_FWD_HPP
