#ifndef SPROUT_CTYPE_ASCII_HPP
#define SPROUT_CTYPE_ASCII_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	namespace ascii {
		// Copyright (C) 2011 RiSK (sscrisk)

		namespace detail {
			SPROUT_STATIC_CONSTEXPR std::size_t alpha = 1 << 0;
			SPROUT_STATIC_CONSTEXPR std::size_t blank = 1 << 1;
			SPROUT_STATIC_CONSTEXPR std::size_t cntrl = 1 << 2;
			SPROUT_STATIC_CONSTEXPR std::size_t digit = 1 << 3;
			SPROUT_STATIC_CONSTEXPR std::size_t graph = 1 << 4;
			SPROUT_STATIC_CONSTEXPR std::size_t lower = 1 << 5;
			SPROUT_STATIC_CONSTEXPR std::size_t print = 1 << 6;
			SPROUT_STATIC_CONSTEXPR std::size_t punct = 1 << 7;
			SPROUT_STATIC_CONSTEXPR std::size_t space = 1 << 8;
			SPROUT_STATIC_CONSTEXPR std::size_t upper = 1 << 9;
			SPROUT_STATIC_CONSTEXPR std::size_t xdigit = 1 << 10;
			SPROUT_STATIC_CONSTEXPR std::size_t table_size = 0x80;
			SPROUT_STATIC_CONSTEXPR std::size_t table[sprout::ascii::detail::table_size] = {
				/* 0x0  NUL */ sprout::ascii::detail::cntrl,
				/* 0x1  SOH */ sprout::ascii::detail::cntrl,
				/* 0x2  STX */ sprout::ascii::detail::cntrl,
				/* 0x3  ETX */ sprout::ascii::detail::cntrl,
				/* 0x4  EOT */ sprout::ascii::detail::cntrl,
				/* 0x5  ENQ */ sprout::ascii::detail::cntrl,
				/* 0x6  ACK */ sprout::ascii::detail::cntrl,
				/* 0x7  BEL */ sprout::ascii::detail::cntrl,
				/* 0x8  BS  */ sprout::ascii::detail::cntrl,
				/* 0x9  HT  */ sprout::ascii::detail::blank | sprout::ascii::detail::cntrl | sprout::ascii::detail::space,
				/* 0xA  LF  */ sprout::ascii::detail::cntrl | sprout::ascii::detail::space,
				/* 0xB  VT  */ sprout::ascii::detail::cntrl | sprout::ascii::detail::space,
				/* 0xC  FF  */ sprout::ascii::detail::cntrl | sprout::ascii::detail::space,
				/* 0xD  CR  */ sprout::ascii::detail::cntrl | sprout::ascii::detail::space,
				/* 0xE  SO  */ sprout::ascii::detail::cntrl,
				/* 0xF  SI  */ sprout::ascii::detail::cntrl,
				/* 0x10 DLE */ sprout::ascii::detail::cntrl,
				/* 0x11 DC1 */ sprout::ascii::detail::cntrl,
				/* 0x12 DC2 */ sprout::ascii::detail::cntrl,
				/* 0x13 DC3 */ sprout::ascii::detail::cntrl,
				/* 0x14 DC4 */ sprout::ascii::detail::cntrl,
				/* 0x15 NAK */ sprout::ascii::detail::cntrl,
				/* 0x16 SYN */ sprout::ascii::detail::cntrl,
				/* 0x17 ETB */ sprout::ascii::detail::cntrl,
				/* 0x18 CAN */ sprout::ascii::detail::cntrl,
				/* 0x19 EM  */ sprout::ascii::detail::cntrl,
				/* 0x1A SUB */ sprout::ascii::detail::cntrl,
				/* 0x1B ESC */ sprout::ascii::detail::cntrl,
				/* 0x1C FS  */ sprout::ascii::detail::cntrl,
				/* 0x1D GS  */ sprout::ascii::detail::cntrl,
				/* 0x1E RS  */ sprout::ascii::detail::cntrl,
				/* 0x1F US  */ sprout::ascii::detail::cntrl,
				/* 0x20 ' ' */ sprout::ascii::detail::blank | sprout::ascii::detail::print | sprout::ascii::detail::space,
				/* 0x21 '!' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x22 '"' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x23 '#' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x24 '$' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x25 '%' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x26 '&' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x27 ''' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x28 '(' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x29 ')' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x2A '*' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x2B '+' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x2C ',' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x2D '-' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x2E '.' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x2F '/' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x30 '0' */ sprout::ascii::detail::digit | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x31 '1' */ sprout::ascii::detail::digit | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x32 '2' */ sprout::ascii::detail::digit | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x33 '3' */ sprout::ascii::detail::digit | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x34 '4' */ sprout::ascii::detail::digit | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x35 '5' */ sprout::ascii::detail::digit | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x36 '6' */ sprout::ascii::detail::digit | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x37 '7' */ sprout::ascii::detail::digit | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x38 '8' */ sprout::ascii::detail::digit | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x39 '9' */ sprout::ascii::detail::digit | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x3A ':' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x3B ';' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x3C '<' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x3D '=' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x3E '>' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x3F '?' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x40 '@' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x41 'A' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper | sprout::ascii::detail::xdigit,
				/* 0x42 'B' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper | sprout::ascii::detail::xdigit,
				/* 0x43 'C' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper | sprout::ascii::detail::xdigit,
				/* 0x44 'D' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper | sprout::ascii::detail::xdigit,
				/* 0x45 'E' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper | sprout::ascii::detail::xdigit,
				/* 0x46 'F' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper | sprout::ascii::detail::xdigit,
				/* 0x47 'G' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x48 'H' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x49 'I' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x4A 'J' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x4B 'K' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x4C 'L' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x4D 'M' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x4E 'N' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x4F 'O' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x50 'P' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x51 'Q' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x52 'R' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x53 'S' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x54 'T' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x55 'U' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x56 'V' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x57 'W' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x58 'X' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x59 'Y' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x5A 'Z' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::upper,
				/* 0x5B '[' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x5C '\' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x5D ']' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x5E '^' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x5F '_' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x60 '`' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x61 'a' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x62 'b' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x63 'c' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x64 'd' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x65 'e' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x66 'f' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print | sprout::ascii::detail::xdigit,
				/* 0x67 'g' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x68 'h' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x69 'i' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x6A 'j' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x6B 'k' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x6C 'l' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x6D 'm' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x6E 'n' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x6F 'o' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x70 'p' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x71 'q' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x72 'r' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x73 's' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x74 't' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x75 'u' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x76 'v' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x77 'w' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x78 'x' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x79 'y' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x7A 'z' */ sprout::ascii::detail::alpha | sprout::ascii::detail::graph | sprout::ascii::detail::lower | sprout::ascii::detail::print,
				/* 0x7B '{' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x7C '|' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x7D '}' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x7E '~' */ sprout::ascii::detail::graph | sprout::ascii::detail::print | sprout::ascii::detail::punct,
				/* 0x7F DEL */ sprout::ascii::detail::cntrl
			};
			SPROUT_CONSTEXPR std::size_t get_value(char c) {
				return static_cast<std::size_t>(c) < sprout::ascii::detail::table_size
					? sprout::ascii::detail::table[static_cast<std::size_t>(c)]
					: 0
					;
			}
			SPROUT_CONSTEXPR std::size_t get_value(wchar_t c) {
				return static_cast<std::size_t>(c) < sprout::ascii::detail::table_size
					? sprout::ascii::detail::table[static_cast<std::size_t>(c)]
					: 0
					;
			}
			SPROUT_CONSTEXPR std::size_t get_value(char16_t c) {
				return static_cast<std::size_t>(c) < sprout::ascii::detail::table_size
					? sprout::ascii::detail::table[static_cast<std::size_t>(c)]
					: 0
					;
			}
			SPROUT_CONSTEXPR std::size_t get_value(char32_t c) {
				return static_cast<std::size_t>(c) < sprout::ascii::detail::table_size
					? sprout::ascii::detail::table[static_cast<std::size_t>(c)]
					: 0
					;
			}
		}	// namespace detail

#define SPROUT_CTYPE_DEFINE_ASCII(CHAR_TYPE) \
		SPROUT_CONSTEXPR bool isalnum(CHAR_TYPE c) { \
			return sprout::ascii::detail::get_value(c) & (sprout::ascii::detail::alpha | sprout::ascii::detail::digit); \
		} \
		SPROUT_CONSTEXPR bool isalpha(CHAR_TYPE c) { \
			return sprout::ascii::detail::get_value(c) & sprout::ascii::detail::alpha; \
		} \
		SPROUT_CONSTEXPR bool isblank(CHAR_TYPE c) { \
			return sprout::ascii::detail::get_value(c) & sprout::ascii::detail::blank; \
		} \
		SPROUT_CONSTEXPR bool iscntrl(CHAR_TYPE c) { \
			return sprout::ascii::detail::get_value(c) & sprout::ascii::detail::cntrl; \
		} \
		SPROUT_CONSTEXPR bool isdigit(CHAR_TYPE c) { \
			return sprout::ascii::detail::get_value(c) & sprout::ascii::detail::digit; \
		} \
		SPROUT_CONSTEXPR bool isgraph(CHAR_TYPE c) { \
			return sprout::ascii::detail::get_value(c) & sprout::ascii::detail::graph; \
		} \
		SPROUT_CONSTEXPR bool islower(CHAR_TYPE c) { \
			return sprout::ascii::detail::get_value(c) & sprout::ascii::detail::lower; \
		} \
		SPROUT_CONSTEXPR bool isprint(CHAR_TYPE c) { \
			return sprout::ascii::detail::get_value(c) & sprout::ascii::detail::print; \
		} \
		SPROUT_CONSTEXPR bool ispunct(CHAR_TYPE c) { \
			return sprout::ascii::detail::get_value(c) & sprout::ascii::detail::punct; \
		} \
		SPROUT_CONSTEXPR bool isspace(CHAR_TYPE c) { \
			return sprout::ascii::detail::get_value(c) & sprout::ascii::detail::space; \
		} \
		SPROUT_CONSTEXPR bool isupper(CHAR_TYPE c) { \
			return sprout::ascii::detail::get_value(c) & sprout::ascii::detail::upper; \
		} \
		SPROUT_CONSTEXPR bool isxdigit(CHAR_TYPE c) { \
			return sprout::ascii::detail::get_value(c) & sprout::ascii::detail::xdigit; \
		} \
		SPROUT_CONSTEXPR CHAR_TYPE tolower(CHAR_TYPE c) { \
			return sprout::ascii::isupper(c) ? c + (0x61 - 0x41) : c; \
		} \
		SPROUT_CONSTEXPR CHAR_TYPE toupper(CHAR_TYPE c) { \
			return sprout::ascii::islower(c) ? c - (0x61 - 0x41) : c; \
		}

		//
		// isalnum
		// isalpha
		// isblank
		// iscntrl
		// isdigit
		// isgraph
		// islower
		// isprint
		// ispunct
		// isspace
		// isupper
		// isxdigit
		// tolower
		// toupper
		//
		SPROUT_CTYPE_DEFINE_ASCII(char);
		SPROUT_CTYPE_DEFINE_ASCII(wchar_t);
		SPROUT_CTYPE_DEFINE_ASCII(char16_t);
		SPROUT_CTYPE_DEFINE_ASCII(char32_t);

#undef SPROUT_CTYPE_DEFINE_ASCII
	}	// namespace ascii

	using sprout::ascii::isalnum;
	using sprout::ascii::isalpha;
	using sprout::ascii::isblank;
	using sprout::ascii::iscntrl;
	using sprout::ascii::isdigit;
	using sprout::ascii::isgraph;
	using sprout::ascii::islower;
	using sprout::ascii::isprint;
	using sprout::ascii::ispunct;
	using sprout::ascii::isspace;
	using sprout::ascii::isupper;
	using sprout::ascii::isxdigit;
	using sprout::ascii::tolower;
	using sprout::ascii::toupper;
}	// namespace sprout

#endif	// #ifndef SPROUT_CTYPE_ASCII_HPP
