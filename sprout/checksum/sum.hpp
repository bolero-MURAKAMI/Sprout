/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CHECKSUM_SUM_HPP
#define SPROUT_CHECKSUM_SUM_HPP

#include <cstdint>
#include <climits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/string/char_traits.hpp>
#include <sprout/string/string.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/bytes_iterator.hpp>
#include <sprout/numeric/accumulate.hpp>
#include <sprout/detail/integer.hpp>
#include <sprout/detail/udl_namespace.hpp>

namespace sprout {
	static_assert(CHAR_BIT == 8, "CHAR_BIT == 8");

	//
	// sum_basic
	//
	template<std::size_t Bits = 8>
	class sum_basic {
		static_assert(Bits % 8 == 0, "Bits % 8 == 0");
	public:
		typedef typename sprout::detail::uint_t<Bits>::least value_type;
		typedef sum_basic const const_type;
		typedef typename std::conditional<
			sizeof(std::size_t) < sizeof(value_type),
			value_type,
			std::size_t
		>::type sum_type;
	private:
		sum_type sum_;
	private:
		template<typename InputIterator>
		SPROUT_CONSTEXPR sum_type calc_sum(InputIterator const& first, InputIterator const& last) const {
			return sprout::accumulate(
				sprout::make_bytes_iterator(first),
				sprout::make_bytes_iterator(last),
				sum_
				);
		}
	public:
		SPROUT_CONSTEXPR sum_basic()
			: sum_()
		{}
		sum_basic(sum_basic const&) = default;
		explicit SPROUT_CONSTEXPR sum_basic(sum_type sum)
			: sum_(sum)
		{}
		SPROUT_CXX14_CONSTEXPR void reset(sum_type new_sum = 0) {
			sum_ = new_sum;
		}

		SPROUT_CONSTEXPR sum_basic const process_byte(std::uint8_t byte) const {
			return c_process_byte(byte);
		}
		template<typename InputIterator>
		SPROUT_CONSTEXPR sum_basic const process_block(InputIterator bytes_begin, InputIterator bytes_end) const {
			return c_process_block(bytes_begin, bytes_end);
		}
		template<typename InputIterator>
		SPROUT_CONSTEXPR sum_basic const process_bytes(InputIterator buffer, std::size_t byte_count) const {
			return c_process_bytes(buffer, byte_count);
		}
		template<typename InputRange>
		SPROUT_CONSTEXPR sum_basic const process_range(InputRange const& bytes_range) const {
			return c_process_range(bytes_range);
		}
		SPROUT_CONSTEXPR sum_basic const c_process_byte(std::uint8_t byte) const {
			return sum_basic(sum_ + byte);
		}
		template<typename InputIterator>
		SPROUT_CONSTEXPR sum_basic const c_process_block(InputIterator bytes_begin, InputIterator bytes_end) const {
			return sum_basic(calc_sum(bytes_begin, bytes_end));
		}
		template<typename InputIterator>
		SPROUT_CONSTEXPR sum_basic const c_process_bytes(InputIterator buffer, std::size_t byte_count) const {
			return c_process_block(buffer, sprout::next(buffer, byte_count));
		}
		template<typename InputRange>
		SPROUT_CONSTEXPR sum_basic const c_process_range(InputRange const& bytes_range) const {
			return c_process_block(sprout::begin(bytes_range), sprout::end(bytes_range));
		}

		SPROUT_CXX14_CONSTEXPR void process_byte(std::uint8_t byte) {
			sum_ += byte;
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
			return static_cast<value_type>(sum_ & sprout::numeric_limits<value_type>::max());
		}
		SPROUT_CONSTEXPR value_type operator()() const {
			return checksum();
		}
	};

	//
	// sum8
	// sum16
	// sum32
	//
	typedef sprout::sum_basic<8> sum8;
	typedef sprout::sum_basic<16> sum16;
	typedef sprout::sum_basic<32> sum32;

	//
	// make_sum8
	//
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR sprout::sum8::value_type
	make_sum8(ForwardIterator first, ForwardIterator last) {
		return sprout::sum8().c_process_block(first, last)();
	}
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::sum8::value_type
	make_sum8(sprout::basic_string<Elem, N, Traits> const& s) {
		return sprout::sum8().c_process_range(s)();
	}
	inline SPROUT_CONSTEXPR sprout::sum8::value_type
	make_sum8(char const* s) {
		return sprout::sum8().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
	inline SPROUT_CONSTEXPR sprout::sum8::value_type
	make_sum8(wchar_t const* s) {
		return sprout::sum8().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
#if SPROUT_USE_UNICODE_LITERALS
	inline SPROUT_CONSTEXPR sprout::sum8::value_type
	make_sum8(char16_t const* s) {
		return sprout::sum8().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
	inline SPROUT_CONSTEXPR sprout::sum8::value_type
	make_sum8(char32_t const* s) {
		return sprout::sum8().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
#endif
	//
	// make_sum16
	//
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR sprout::sum16::value_type
	make_sum16(ForwardIterator first, ForwardIterator last) {
		return sprout::sum16().c_process_block(first, last)();
	}
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::sum16::value_type
	make_sum16(sprout::basic_string<Elem, N, Traits> const& s) {
		return sprout::sum16().c_process_range(s)();
	}
	inline SPROUT_CONSTEXPR sprout::sum16::value_type
	make_sum16(char const* s) {
		return sprout::sum16().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
	inline SPROUT_CONSTEXPR sprout::sum16::value_type
	make_sum16(wchar_t const* s) {
		return sprout::sum16().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
#if SPROUT_USE_UNICODE_LITERALS
	inline SPROUT_CONSTEXPR sprout::sum16::value_type
	make_sum16(char16_t const* s) {
		return sprout::sum16().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
	inline SPROUT_CONSTEXPR sprout::sum16::value_type
	make_sum16(char32_t const* s) {
		return sprout::sum16().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
#endif
	//
	// make_sum32
	//
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR sprout::sum32::value_type
	make_sum32(ForwardIterator first, ForwardIterator last) {
		return sprout::sum32().c_process_block(first, last)();
	}
	template<typename Elem, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::sum32::value_type
	make_sum32(sprout::basic_string<Elem, N, Traits> const& s) {
		return sprout::sum32().c_process_range(s)();
	}
	inline SPROUT_CONSTEXPR sprout::sum32::value_type
	make_sum32(char const* s) {
		return sprout::sum32().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
	inline SPROUT_CONSTEXPR sprout::sum32::value_type
	make_sum32(wchar_t const* s) {
		return sprout::sum32().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
#if SPROUT_USE_UNICODE_LITERALS
	inline SPROUT_CONSTEXPR sprout::sum32::value_type
	make_sum32(char16_t const* s) {
		return sprout::sum32().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
	inline SPROUT_CONSTEXPR sprout::sum32::value_type
	make_sum32(char32_t const* s) {
		return sprout::sum32().c_process_bytes(s, sprout::char_traits<char>::length(s))();
	}
#endif
}	// namespace sprout

#if SPROUT_USE_USER_DEFINED_LITERALS

namespace sprout {
	namespace literals {
		namespace checksum {
			//
			// _sum8
			//
			inline SPROUT_CONSTEXPR sprout::sum8::value_type
			operator"" _sum8(char const* s, std::size_t size) {
				return sprout::sum8().c_process_bytes(s, size)();
			}
			inline SPROUT_CONSTEXPR sprout::sum8::value_type
			operator"" _sum8(wchar_t const* s, std::size_t size) {
				return sprout::sum8().c_process_bytes(s, size)();
			}
#if SPROUT_USE_UNICODE_LITERALS
			inline SPROUT_CONSTEXPR sprout::sum8::value_type
			operator"" _sum8(char16_t const* s, std::size_t size) {
				return sprout::sum8().c_process_bytes(s, size)();
			}
			inline SPROUT_CONSTEXPR sprout::sum8::value_type
			operator"" _sum8(char32_t const* s, std::size_t size) {
				return sprout::sum8().c_process_bytes(s, size)();
			}
#endif
			//
			// _sum16
			//
			inline SPROUT_CONSTEXPR sprout::sum16::value_type
			operator"" _sum16(char const* s, std::size_t size) {
				return sprout::sum16().c_process_bytes(s, size)();
			}
			inline SPROUT_CONSTEXPR sprout::sum16::value_type
			operator"" _sum16(wchar_t const* s, std::size_t size) {
				return sprout::sum16().c_process_bytes(s, size)();
			}
#if SPROUT_USE_UNICODE_LITERALS
			inline SPROUT_CONSTEXPR sprout::sum16::value_type
			operator"" _sum16(char16_t const* s, std::size_t size) {
				return sprout::sum16().c_process_bytes(s, size)();
			}
			inline SPROUT_CONSTEXPR sprout::sum16::value_type
			operator"" _sum16(char32_t const* s, std::size_t size) {
				return sprout::sum16().c_process_bytes(s, size)();
			}
#endif
			//
			// _sum32
			//
			inline SPROUT_CONSTEXPR sprout::sum32::value_type
			operator"" _sum32(char const* s, std::size_t size) {
				return sprout::sum32().c_process_bytes(s, size)();
			}
			inline SPROUT_CONSTEXPR sprout::sum32::value_type
			operator"" _sum32(wchar_t const* s, std::size_t size) {
				return sprout::sum32().c_process_bytes(s, size)();
			}
#if SPROUT_USE_UNICODE_LITERALS
			inline SPROUT_CONSTEXPR sprout::sum32::value_type
			operator"" _sum32(char16_t const* s, std::size_t size) {
				return sprout::sum32().c_process_bytes(s, size)();
			}
			inline SPROUT_CONSTEXPR sprout::sum32::value_type
			operator"" _sum32(char32_t const* s, std::size_t size) {
				return sprout::sum32().c_process_bytes(s, size)();
			}
#endif
		}	// namespace checksum

		using sprout::literals::checksum::operator"" _sum8;
		using sprout::literals::checksum::operator"" _sum16;
		using sprout::literals::checksum::operator"" _sum32;
	}	// namespace literals

	using sprout::literals::checksum::operator"" _sum8;
	using sprout::literals::checksum::operator"" _sum16;
	using sprout::literals::checksum::operator"" _sum32;
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_CHECKSUM_SUM_HPP
