/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CHECKSUM_XOR_HPP
#define SPROUT_CHECKSUM_XOR_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/string/char_traits.hpp>
#include <sprout/string/string.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/bytes_iterator.hpp>
#include <sprout/numeric/accumulate.hpp>
#include <sprout/functional/polymorphic/bit_xor.hpp>
#include <sprout/detail/udl_namespace.hpp>

namespace sprout {
	//
	// xor8
	//
	class xor8 {
	public:
		typedef std::uint8_t value_type;
		typedef xor8 const const_type;
		typedef std::size_t sum_type;
	private:
		sum_type sum_;
	private:
		template<typename InputIterator>
		SPROUT_CONSTEXPR sum_type calc_sum(InputIterator const& first, InputIterator const& last) const {
			return sprout::accumulate(
				sprout::make_bytes_iterator(first),
				sprout::make_bytes_iterator(last),
				sum_,
				sprout::bit_xor_
				);
		}
	public:
		SPROUT_CONSTEXPR xor8()
			: sum_()
		{}
		xor8(xor8 const&) = default;
		explicit SPROUT_CONSTEXPR xor8(sum_type sum)
			: sum_(sum)
		{}
		SPROUT_CXX14_CONSTEXPR void reset(sum_type new_sum = 0) {
			sum_ = new_sum;
		}

		SPROUT_CONSTEXPR xor8 const process_byte(std::uint8_t byte) const {
			return c_process_byte(byte);
		}
		template<typename InputIterator>
		SPROUT_CONSTEXPR xor8 const process_block(InputIterator bytes_begin, InputIterator bytes_end) const {
			return c_process_block(bytes_begin, bytes_end);
		}
		template<typename InputIterator>
		SPROUT_CONSTEXPR xor8 const process_bytes(InputIterator buffer, std::size_t byte_count) const {
			return c_process_bytes(buffer, byte_count);
		}
		template<typename InputRange>
		SPROUT_CONSTEXPR xor8 const process_range(InputRange const& bytes_range) const {
			return c_process_range(bytes_range);
		}
		SPROUT_CONSTEXPR xor8 const c_process_byte(std::uint8_t byte) const {
			return xor8(sum_ ^ byte);
		}
		template<typename InputIterator>
		SPROUT_CONSTEXPR xor8 const c_process_block(InputIterator bytes_begin, InputIterator bytes_end) const {
			return xor8(calc_sum(bytes_begin, bytes_end));
		}
		template<typename InputIterator>
		SPROUT_CONSTEXPR xor8 const c_process_bytes(InputIterator buffer, std::size_t byte_count) const {
			return c_process_block(buffer, sprout::next(buffer, byte_count));
		}
		template<typename InputRange>
		SPROUT_CONSTEXPR xor8 const c_process_range(InputRange const& bytes_range) const {
			return c_process_block(sprout::begin(bytes_range), sprout::end(bytes_range));
		}

		SPROUT_CXX14_CONSTEXPR void process_byte(std::uint8_t byte) {
			sum_ ^= byte;
		}
		template<typename InputIterator>
		SPROUT_CXX14_CONSTEXPR void process_block(InputIterator bytes_begin, InputIterator bytes_end) {
			sum_ = calc_sum(bytes_begin, bytes_end);
		}
		template<typename InputIterator>
		SPROUT_CXX14_CONSTEXPR void process_bytes(InputIterator buffer, std::size_t byte_count) {
			process_block(buffer, sprout::next(buffer, byte_count));
		}
		template<typename InputRange>
		SPROUT_CXX14_CONSTEXPR void process_range(InputRange const& bytes_range) {
			process_block(sprout::begin(bytes_range), sprout::end(bytes_range));
		}

		SPROUT_CONSTEXPR value_type checksum() const {
			return static_cast<value_type>(sum_ & 0xFF);
		}
		SPROUT_CONSTEXPR value_type operator()() const {
			return checksum();
		}
	};

	//
	// make_xor8
	//
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR sprout::xor8::value_type
	make_xor8(ForwardIterator first, ForwardIterator last) {
		return sprout::xor8().c_process_block(first, last)();
	}
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::xor8::value_type
	make_xor8(sprout::basic_string<Elem, N, Traits> const& s) {
		return sprout::xor8().c_process_range(s)();
	}
	inline SPROUT_CONSTEXPR sprout::xor8::value_type
	make_xor8(char const* s) {
		return sprout::xor8().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
	inline SPROUT_CONSTEXPR sprout::xor8::value_type
	make_xor8(wchar_t const* s) {
		return sprout::xor8().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
#if SPROUT_USE_UNICODE_LITERALS
	inline SPROUT_CONSTEXPR sprout::xor8::value_type
	make_xor8(char16_t const* s) {
		return sprout::xor8().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
	inline SPROUT_CONSTEXPR sprout::xor8::value_type
	make_xor8(char32_t const* s) {
		return sprout::xor8().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
#endif
}	// namespace sprout

#if SPROUT_USE_USER_DEFINED_LITERALS

namespace sprout {
	namespace literals {
		namespace checksum {
			//
			// _xor8
			//
			inline SPROUT_CONSTEXPR sprout::xor8::value_type
			operator"" _xor8(char const* s, std::size_t size) {
				return sprout::xor8().c_process_bytes(s, size)();
			}
			inline SPROUT_CONSTEXPR sprout::xor8::value_type
			operator"" _xor8(wchar_t const* s, std::size_t size) {
				return sprout::xor8().c_process_bytes(s, size)();
			}
#if SPROUT_USE_UNICODE_LITERALS
			inline SPROUT_CONSTEXPR sprout::xor8::value_type
			operator"" _xor8(char16_t const* s, std::size_t size) {
				return sprout::xor8().c_process_bytes(s, size)();
			}
			inline SPROUT_CONSTEXPR sprout::xor8::value_type
			operator"" _xor8(char32_t const* s, std::size_t size) {
				return sprout::xor8().c_process_bytes(s, size)();
			}
#endif
		}	// namespace checksum

		using sprout::literals::checksum::operator"" _xor8;
	}	// namespace literals

	using sprout::literals::checksum::operator"" _xor8;
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_CHECKSUM_XOR_HPP
