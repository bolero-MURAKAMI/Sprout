#ifndef SPROUT_UUID_DETAIL_TABLE_HPP
#define SPROUT_UUID_DETAIL_TABLE_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/array.hpp>
#include <sprout/string.hpp>

namespace sprout {
	namespace uuids {
		namespace detail {
			template<typename Elem>
			struct digits {};

			template<>
			struct digits<char> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char, 22> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string("0123456789abcdefABCDEF"))
					;
				SPROUT_STATIC_CONSTEXPR char dash = '-';
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<char, 22> sprout::uuids::detail::digits<char>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string("0123456789abcdefABCDEF"))
				;
			SPROUT_CONSTEXPR_OR_CONST char sprout::uuids::detail::digits<char>::dash;

			template<>
			struct digits<wchar_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<wchar_t, 22> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string(L"0123456789abcdefABCDEF"))
					;
				SPROUT_STATIC_CONSTEXPR wchar_t dash = L'-';
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<wchar_t, 22> sprout::uuids::detail::digits<wchar_t>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string(L"0123456789abcdefABCDEF"))
				;
			SPROUT_CONSTEXPR_OR_CONST wchar_t sprout::uuids::detail::digits<wchar_t>::dash;

			template<>
			struct digits<char16_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char16_t, 22> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string(u"0123456789abcdefABCDEF"))
					;
				SPROUT_STATIC_CONSTEXPR char16_t dash = u'-';
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<char16_t, 22> sprout::uuids::detail::digits<char16_t>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string(u"0123456789abcdefABCDEF"))
				;
			SPROUT_CONSTEXPR_OR_CONST char16_t sprout::uuids::detail::digits<char16_t>::dash;

			template<>
			struct digits<char32_t> {
			public:
				SPROUT_STATIC_CONSTEXPR sprout::basic_string<char32_t, 22> table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(sprout::to_string(U"0123456789abcdefABCDEF"))
					;
				SPROUT_STATIC_CONSTEXPR char32_t dash = U'-';
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::basic_string<char32_t, 22> sprout::uuids::detail::digits<char32_t>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(sprout::to_string(U"0123456789abcdefABCDEF"))
				;
			SPROUT_CONSTEXPR_OR_CONST char32_t sprout::uuids::detail::digits<char32_t>::dash;

			template<typename Dummy>
			struct values;

#		define SPROUT_UUID_TABLE_DEF \
			table_type{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 10, 11, 12, 13, 14, 15}}

			template<>
			struct values<void> {
			public:
				typedef sprout::array<std::uint8_t, 22> table_type;
			public:
				SPROUT_STATIC_CONSTEXPR table_type table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(SPROUT_UUID_TABLE_DEF)
					;
			};
			SPROUT_CONSTEXPR_OR_CONST sprout::uuids::detail::values<void>::table_type
			sprout::uuids::detail::values<void>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(SPROUT_UUID_TABLE_DEF)
				;

#		undef SPROUT_UUID_TABLE_DEF
		}	// namespace detail
	}	// namespace uuids
}	// namespace sprout

#endif	// #ifndef SPROUT_UUID_DETAIL_TABLE_HPP
