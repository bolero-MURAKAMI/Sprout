#ifndef SPROUT_UUID_UUID_IO_HPP
#define SPROUT_UUID_UUID_IO_HPP

#include <cstddef>
#include <algorithm>
#include <iterator>
#include <ios>
#include <ostream>
#include <istream>
#include <locale>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/uuid/uuid.hpp>
#include <sprout/uuid/detail/table.hpp>
#include <sprout/detail/io/ios_state.hpp>

namespace sprout {
	namespace uuids {
		//
		// operator>>
		//
		template<typename Elem, typename Traits>
		std::basic_istream<Elem, Traits>& operator>>(std::basic_istream<Elem, Traits>& lhs, sprout::uuids::uuid& rhs) {
			typedef typename std::basic_ios<Elem, Traits>::char_type char_type;
			typename std::basic_istream<Elem, Traits>::sentry const ok(lhs);
			typedef std::ctype<Elem> ctype_type;
			if (ok) {
				sprout::uuids::uuid::value_type data[16];
				ctype_type const& ctype = std::use_facet<ctype_type>(lhs.getloc());
				char_type xdigits[16];
				{
					char const szdigits[] = "0123456789ABCDEF";
					ctype.widen(szdigits, szdigits + 16, xdigits);
				}
				char_type const* const xdigits_end = xdigits + 16;
				char_type c;
				for (sprout::uuids::uuid::size_type i = 0, last = rhs.size(); i < last && lhs; ++i) {
					lhs >> c;
					c = ctype.toupper(c);
					char_type const* f = std::find(xdigits, xdigits_end, c);
					if (f == xdigits_end) {
						lhs.setstate(std::ios_base::failbit);
						break;
					}
					sprout::uuids::uuid::value_type byte = static_cast<sprout::uuids::uuid::value_type>(std::distance(&xdigits[0], f));
					lhs >> c;
					c = ctype.toupper(c);
					f = std::find(xdigits, xdigits_end, c);
					if (f == xdigits_end) {
						lhs.setstate(std::ios_base::failbit);
						break;
					}
					byte <<= 4;
					byte |= static_cast<sprout::uuids::uuid::value_type>(std::distance(&xdigits[0], f));
					data[i] = byte;
					if (lhs) {
						if (i == 3 || i == 5 || i == 7 || i == 9) {
							lhs >> c;
							if (c != lhs.widen('-')) {
								lhs.setstate(std::ios_base::failbit);
								break;
							}
						}
					}
				}
				if (lhs) {
					std::copy(data, data + 16, rhs.begin());
				}
			}
			return lhs;
		}
		//
		// operator<<
		//
		template<typename Elem, typename Traits>
		std::basic_ostream<Elem, Traits>& operator<<(std::basic_ostream<Elem, Traits>& lhs, sprout::uuids::uuid const& rhs) {
			sprout::detail::io::ios_flags_saver flags_saver(lhs);
			sprout::detail::io::basic_ios_fill_saver<Elem, Traits> fill_saver(lhs);
			typename std::basic_ostream<Elem, Traits>::sentry const ok(lhs);
			if (ok) {
				std::streamsize const width = lhs.width(0);
				std::streamsize const uuid_width = 36;
				std::ios_base::fmtflags const flags = lhs.flags();
				typename std::basic_ios<Elem, Traits>::char_type const fill = lhs.fill();
				if (flags & (std::ios_base::right | std::ios_base::internal)) {
					for (std::streamsize i = uuid_width; i < width; ++i) {
						lhs << fill;
					}
				}
				lhs << std::hex;
				lhs.fill(lhs.widen('0'));
				std::size_t i = 0;
				for (sprout::uuids::uuid::const_iterator i_data = rhs.begin(), i_last = rhs.end(); i_data != i_last; ++i_data, ++i) {
					lhs.width(2);
					lhs << static_cast<unsigned>(*i_data);
					if (i == 3 || i == 5 || i == 7 || i == 9) {
						lhs << lhs.widen('-');
					}
				}
				if (flags & std::ios_base::left) {
					for (std::streamsize i = uuid_width; i < width; ++i) {
						lhs << fill;
					}
				}
				lhs.width(0);
			}
			return lhs;
		}

		//
		// to_string_of
		//
		template<typename Elem, typename Traits = sprout::char_traits<Elem> >
		SPROUT_CONSTEXPR inline sprout::basic_string<Elem, 36, Traits> to_string_of(sprout::uuids::uuid const& u) {
			return sprout::basic_string<Elem, 36, Traits>{
				{
					sprout::uuids::detail::digits<Elem>::table[(u[0] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[0]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[1] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[1]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[2] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[2]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[3] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[3]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::dash,
					sprout::uuids::detail::digits<Elem>::table[(u[4] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[4]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[5] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[5]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::dash,
					sprout::uuids::detail::digits<Elem>::table[(u[6] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[6]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[7] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[7]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::dash,
					sprout::uuids::detail::digits<Elem>::table[(u[8] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[8]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[9] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[9]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::dash,
					sprout::uuids::detail::digits<Elem>::table[(u[10] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[10]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[11] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[11]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[12] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[12]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[13] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[13]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[14] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[14]) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[15] >> 4) & 0x0F],
					sprout::uuids::detail::digits<Elem>::table[(u[15]) & 0x0F]
					},
				36
				};
		}
		//
		// to_string
		//
		SPROUT_CONSTEXPR inline sprout::basic_string<char, 36> to_string(sprout::uuids::uuid const& u) {
			return sprout::uuids::to_string_of<char>(u);
		}
		//
		// to_wstring
		//
		SPROUT_CONSTEXPR inline sprout::basic_string<wchar_t, 36> to_wstring(sprout::uuids::uuid const& u) {
			return sprout::uuids::to_string_of<wchar_t>(u);
		}
		//
		// to_u16string
		//
		SPROUT_CONSTEXPR inline sprout::basic_string<char16_t, 36> to_u16string(sprout::uuids::uuid const& u) {
			return sprout::uuids::to_string_of<char16_t>(u);
		}
		//
		// to_u32string
		//
		SPROUT_CONSTEXPR inline sprout::basic_string<char32_t, 36> to_u32string(sprout::uuids::uuid const& u) {
			return sprout::uuids::to_string_of<char32_t>(u);
		}
	}	// namespace uuids
}	// namespace sprout

#endif	// #ifndef SPROUT_UUID_UUID_IO_HPP
