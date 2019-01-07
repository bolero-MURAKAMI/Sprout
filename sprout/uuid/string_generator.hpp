/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UUID_STRING_GENERATOR_HPP
#define SPROUT_UUID_STRING_GENERATOR_HPP

#include <cstdint>
#include <iterator>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/string.hpp>
#include <sprout/uuid/uuid.hpp>
#include <sprout/uuid/detail/table.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/find.hpp>

namespace sprout {
	namespace uuids {
		//
		// string_generator
		//
		class string_generator {
		public:
			typedef sprout::uuids::uuid result_type;
		private:
			template<typename ForwardIterator>
			struct next_char {
			public:
				typedef typename std::iterator_traits<ForwardIterator>::value_type char_type;
			public:
				char_type c;
				ForwardIterator first;
				ForwardIterator last;
			public:
				SPROUT_CONSTEXPR next_char(ForwardIterator f, ForwardIterator l)
					: c(f != l
						? *f
						: throw std::runtime_error("string_generator: invalid uuid string (out of range)")
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
					: throw std::runtime_error("string_generator: invalid uuid string (invalid character)")
					;
			}
			template<typename Elem>
			SPROUT_CONSTEXPR std::uint8_t get_value(Elem c) const {
				return value_at(
					sprout::distance(
						sprout::uuids::detail::digits<Elem>::value.begin(),
						sprout::find(
							sprout::uuids::detail::digits<Elem>::value.begin(),
							sprout::uuids::detail::digits<Elem>::value.end(),
							c
							)
						)
					);
			}
			template<typename Elem>
			static SPROUT_CONSTEXPR bool is_dash(Elem c) {
				return c == sprout::uuids::detail::dash<Elem>::value;
			}
			template<typename Elem>
			static SPROUT_CONSTEXPR bool is_open_brace(Elem c) {
				return c == sprout::uuids::detail::lbrace<Elem>::value;
			}
			template<typename Elem>
			static SPROUT_CONSTEXPR bool is_close_brace(Elem c) {
				return c == sprout::uuids::detail::rbrace<Elem>::value;
			}
			template<typename Elem>
			static SPROUT_CONSTEXPR bool is_close_brace(Elem c, Elem open_brace) {
				return is_open_brace(open_brace) && is_close_brace(c);
			}
			template<typename ForwardIterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR result_type
			generate_2_3(next_char<ForwardIterator> nc, Char open_brace, bool has_dashes, std::uint8_t byte, Args... args) const {
				return generate_2(nc, open_brace, has_dashes, args..., static_cast<std::uint8_t>((byte << 4) | get_value(nc.c)));
			}
			template<typename ForwardIterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR result_type
			generate_2_2(next_char<ForwardIterator> nc, Char open_brace, bool has_dashes, Args... args) const {
				return generate_2_3(nc.next(), open_brace, has_dashes, get_value(nc.c), args...);
			}
			template<typename ForwardIterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == 6 || sizeof...(Args) == 8 || sizeof...(Args) == 10,
				result_type
			>::type
			generate_2_1(next_char<ForwardIterator> nc, Char open_brace, bool has_dashes, Args... args) const {
				return has_dashes
					? is_dash(nc.c)
						? generate_2_2(nc.next(), open_brace, has_dashes, args...)
						: throw std::runtime_error("string_generator: invalid uuid string (dashes not found)")
					: generate_2_2(nc, open_brace, has_dashes, args...)
					;
			}
			template<typename ForwardIterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == 4,
				result_type
			>::type
			generate_2_1(next_char<ForwardIterator> nc, Char open_brace, bool, Args... args) const {
				return is_dash(nc.c)
					? generate_2_2(nc.next(), open_brace, true, args...)
					: generate_2_2(nc, open_brace, false, args...)
					;
			}
			template<typename ForwardIterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) != 4 && sizeof...(Args) != 6 && sizeof...(Args) != 8 && sizeof...(Args) != 10,
				result_type
			>::type
			generate_2_1(next_char<ForwardIterator> nc, Char open_brace, bool has_dashes, Args... args) const {
				return generate_2_2(nc, open_brace, has_dashes, args...);
			}
			template<typename ForwardIterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == 16,
				result_type
			>::type
			generate_2(next_char<ForwardIterator> nc, Char open_brace, bool, Args... args) const {
				return !open_brace || (open_brace && is_close_brace(nc.next().c, open_brace))
					? result_type{{args...}}
					: throw std::runtime_error("string_generator: invalid uuid string (brace not closed)")
					;
			}
			template<typename ForwardIterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == 0,
				result_type
			>::type
			generate_2(next_char<ForwardIterator> nc, Char open_brace, bool has_dashes, Args... args) const {
				return generate_2_2(nc, open_brace, has_dashes, args...);
			}
			template<typename ForwardIterator, typename Char, typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) != 0 && sizeof...(Args) != 16,
				result_type
			>::type
			generate_2(next_char<ForwardIterator> nc, Char open_brace, bool has_dashes, Args... args) const {
				return generate_2_1(nc.next(), open_brace, has_dashes, args...);
			}
			template<typename ForwardIterator>
			SPROUT_CONSTEXPR result_type
			generate_1(next_char<ForwardIterator> nc) const {
				return is_open_brace(nc.c)
					? generate_2(nc.next(), nc.c, false)
					: generate_2(nc, typename next_char<ForwardIterator>::char_type(), false)
					;
			}
		public:
			template<typename ForwardIterator>
			SPROUT_CONSTEXPR result_type operator()(ForwardIterator first, ForwardIterator last) const {
				return generate_1(next_char<ForwardIterator>(first, last));
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
#if SPROUT_USE_UNICODE_LITERALS
			SPROUT_CONSTEXPR result_type operator()(char16_t const* s) const {
				return operator()(s, s + sprout::char_traits<char16_t>::length(s));
			}
			SPROUT_CONSTEXPR result_type operator()(char32_t const* s) const {
				return operator()(s, s + sprout::char_traits<char32_t>::length(s));
			}
#endif
		};

		//
		// make_uuid
		//
		template<typename ForwardIterator>
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid(ForwardIterator first, ForwardIterator last) {
			return sprout::uuids::string_generator()(first, last);
		}
		template<typename Elem, std::size_t N, typename Traits>
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid(sprout::basic_string<Elem, N, Traits> const& s) {
			return sprout::uuids::string_generator()(s);
		}
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid(char const* s) {
			return sprout::uuids::string_generator()(s);
		}
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid(wchar_t const* s) {
			return sprout::uuids::string_generator()(s);
		}
#if SPROUT_USE_UNICODE_LITERALS
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid(char16_t const* s) {
			return sprout::uuids::string_generator()(s);
		}
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid(char32_t const* s) {
			return sprout::uuids::string_generator()(s);
		}
#endif
	}	// namespace uuids
}	// namespace sprout

#endif	// #ifndef SPROUT_UUID_STRING_GENERATOR_HPP
