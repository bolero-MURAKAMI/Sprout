#ifndef SPROUT_UUID_STRING_GENERATOR_HPP
#define SPROUT_UUID_STRING_GENERATOR_HPP

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/uuid/uuid.hpp>
#include <sprout/uuid/detail/table.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace uuids {
		//
		// string_generator
		//
		class string_generator {
		public:
			typedef sprout::uuids::uuid result_type;
		private:
			template<typename Iterator>
			struct next_char {
			public:
				typedef typename std::iterator_traits<Iterator>::value_type char_type;
			public:
				char_type c;
				Iterator first;
				Iterator last;
			public:
				SPROUT_CONSTEXPR next_char(Iterator f, Iterator l)
					: c(f != l
						? *f
						: throw std::domain_error("string_generator: invalid uuid string (out of range)")
						)
					, first(sprout::next(f))
					, last(l)
				{}
				SPROUT_CONSTEXPR next_char next() const {
					return next_char(first, last);
				}
			};
		private:
			SPROUT_CONSTEXPR std::uint8_t value_at(std::size_t i) const {
				return i < 22
					? sprout::uuids::detail::values<void>::table[i]
					: throw std::domain_error("string_generator: invalid uuid string (invalid character)")
					;
			}
			template<typename Elem>
			SPROUT_CONSTEXPR std::uint8_t get_value(Elem c) const {
				return value_at(
					sprout::distance(
						sprout::uuids::detail::digits<Elem>::table.begin(),
						NS_SSCRISK_CEL_OR_SPROUT::find(
							sprout::uuids::detail::digits<Elem>::table.begin(),
							sprout::uuids::detail::digits<Elem>::table.end(),
							c
							)
						)
					);
			}
			static SPROUT_CONSTEXPR bool is_dash(char c) {
				return c == '-';
			}
			static SPROUT_CONSTEXPR bool is_dash(wchar_t c) {
				return c == L'-';
			}
			static SPROUT_CONSTEXPR bool is_dash(char16_t c) {
				return c == u'-';
			}
			static SPROUT_CONSTEXPR bool is_dash(char32_t c) {
				return c == U'-';
			}
			static SPROUT_CONSTEXPR bool is_open_brace(char c) {
				return c == '{';
			}
			static SPROUT_CONSTEXPR bool is_open_brace(wchar_t c) {
				return c == L'{';
			}
			static SPROUT_CONSTEXPR bool is_open_brace(char16_t c) {
				return c == u'{';
			}
			static SPROUT_CONSTEXPR bool is_open_brace(char32_t c) {
				return c == U'{';
			}
			static SPROUT_CONSTEXPR bool is_close_brace(char c, char open_brace) {
				return open_brace == '{' && c == '}';
			}
			static SPROUT_CONSTEXPR bool is_close_brace(wchar_t c, char open_brace) {
				return open_brace == L'{' && c == L'}';
			}
			static SPROUT_CONSTEXPR bool is_close_brace(char16_t c, char open_brace) {
				return open_brace == u'{' && c == u'}';
			}
			static SPROUT_CONSTEXPR bool is_close_brace(char32_t c, char open_brace) {
				return open_brace == U'{' && c == U'}';
			}
			template<typename Iterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR result_type
			generate_2_3(next_char<Iterator> nc, Char open_brace, bool has_dashes, std::uint8_t byte, Args... args) const {
				return generate_2(nc, open_brace, has_dashes, args..., static_cast<std::uint8_t>((byte << 4) | get_value(nc.c)));
			}
			template<typename Iterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR result_type
			generate_2_2(next_char<Iterator> nc, Char open_brace, bool has_dashes, Args... args) const {
				return generate_2_3(nc.next(), open_brace, has_dashes, get_value(nc.c), args...);
			}
			template<typename Iterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == 6 || sizeof...(Args) == 8 || sizeof...(Args) == 10,
				result_type
			>::type
			generate_2_1(next_char<Iterator> nc, Char open_brace, bool has_dashes, Args... args) const {
				return has_dashes
					? is_dash(nc.c)
						? generate_2_2(nc.next(), open_brace, has_dashes, args...)
						: throw std::domain_error("string_generator: invalid uuid string (dashes not found)")
					: generate_2_2(nc, open_brace, has_dashes, args...)
					;
			}
			template<typename Iterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == 4,
				result_type
			>::type
			generate_2_1(next_char<Iterator> nc, Char open_brace, bool has_dashes, Args... args) const {
				return is_dash(nc.c)
					? generate_2_2(nc.next(), open_brace, true, args...)
					: generate_2_2(nc, open_brace, false, args...)
					;
			}
			template<typename Iterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) != 4 && sizeof...(Args) != 6 && sizeof...(Args) != 8 && sizeof...(Args) != 10,
				result_type
			>::type
			generate_2_1(next_char<Iterator> nc, Char open_brace, bool has_dashes, Args... args) const {
				return generate_2_2(nc, open_brace, has_dashes, args...);
			}
			template<typename Iterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == 16,
				result_type
			>::type
			generate_2(next_char<Iterator> nc, Char open_brace, bool has_dashes, Args... args) const {
				return !open_brace || (open_brace && is_close_brace(nc.next().c, open_brace))
					? result_type{{args...}}
					: throw std::domain_error("string_generator: invalid uuid string (brace not closed)")
					;
			}
			template<typename Iterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == 0,
				result_type
			>::type
			generate_2(next_char<Iterator> nc, Char open_brace, bool has_dashes, Args... args) const {
				return generate_2_2(nc, open_brace, has_dashes, args...);
			}
			template<typename Iterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) != 0 && sizeof...(Args) != 16,
				result_type
			>::type
			generate_2(next_char<Iterator> nc, Char open_brace, bool has_dashes, Args... args) const {
				return generate_2_1(nc.next(), open_brace, has_dashes, args...);
			}
			template<typename Iterator>
			SPROUT_CONSTEXPR result_type
			generate_1(next_char<Iterator> nc) const {
				return is_open_brace(nc.c)
					? generate_2(nc.next(), nc.c, false)
					: generate_2(nc, typename next_char<Iterator>::char_type(), false)
					;
			}
		public:
			template<typename Iterator>
			SPROUT_CONSTEXPR result_type operator()(Iterator first, Iterator last) const {
				return generate_1(next_char<Iterator>(first, last));
			}
			template<typename Elem, std::size_t N, typename Traits>
			SPROUT_CONSTEXPR result_type operator()(sprout::basic_string<Elem, N, Traits> const& s) const {
				return operator()(s.begin(), s.end());
			}
			SPROUT_CONSTEXPR result_type operator()(char const* s) const {
				return operator()(s, s + sprout::char_traits<char>::length(s));
			}
			SPROUT_CONSTEXPR result_type operator()(wchar_t const* s) const {
				return operator()(s, s + sprout::char_traits<wchar_t>::length(s));
			}
			SPROUT_CONSTEXPR result_type operator()(char16_t const* s) const {
				return operator()(s, s + sprout::char_traits<char16_t>::length(s));
			}
			SPROUT_CONSTEXPR result_type operator()(char32_t const* s) const {
				return operator()(s, s + sprout::char_traits<char32_t>::length(s));
			}
		};
	}	// namespace uuids
}	// namespace sprout

#endif	// #ifndef SPROUT_UUID_STRING_GENERATOR_HPP
