/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Copyright (c) 2015 Chris KAY
  https://github.com/cjkay-cpp-utils/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NET_ENDIAN_HPP
#define SPROUT_NET_ENDIAN_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/assert.hpp>
#include <sprout/predef/detail/endian_compat.hpp>

namespace sprout {
	namespace net {
		namespace detail {
			/*
			 * lshift_by
			 * Left shift 'val' by 'n' bytes
			 */
			template<typename T>
			inline SPROUT_CONSTEXPR T
			lshift_by(T val, std::uint_fast8_t n) {
				return val << (n * 8);
			}

			/*
			 * rshift_by
			 * Right shift 'val' by 'n' bytes
			 */
			template<typename T>
			inline SPROUT_CONSTEXPR T
			rshift_by(T val, std::uint_fast8_t n) {
				return val >> (n * 8);
			}

			/*
			 * mask_t
			 * Mask 'n'th byte
			 */
			template<typename T>
			inline SPROUT_CONSTEXPR T
			mask_at(std::uint_fast8_t n) {
				return sprout::net::detail::lshift_by(T(0xFF), n);
			}

			/*
			 * byte_at
			 * Get 'n'th byte from 'val'
			 */
			template<typename T>
			inline SPROUT_CONSTEXPR std::uint_fast8_t
			byte_at(T val, std::uint_fast8_t n) {
				return static_cast<std::uint_fast8_t>(
					sprout::net::detail::rshift_by((val & sprout::net::detail::mask_at<T>(n)), n)
					);
			}

			/*
			 * replace_at
			 * Replace, in 'val', 'n'th byte with 'byte_val'
			 */
			template<typename T>
			inline SPROUT_CONSTEXPR T
			replace_at(T val, std::uint8_t byte_val, std::uint_fast8_t n) {
				return (val & ~sprout::net::detail::mask_at<T>(n)) | sprout::net::detail::lshift_by(T(byte_val), n);
			}

			/*
			 * copy
			 * Copy, in 'val', byte at index 'from' to byte at index 'to'
			 */
			template<typename T>
			inline SPROUT_CONSTEXPR T
			copy(T val, std::uint_fast8_t from, std::uint_fast8_t to) {
				return sprout::net::detail::replace_at(val, sprout::net::detail::byte_at(val, from), to);
			}

			/*
			 * swap
			 * Swap, in 'val', byte at index 'n1' with byte at index 'n2'
			 */
			template<typename T>
			inline SPROUT_CONSTEXPR T
			swap(T val, std::uint_fast8_t n1, std::uint_fast8_t n2) {
				return sprout::net::detail::replace_at(sprout::net::detail::copy(val, n1, n2), sprout::net::detail::byte_at(val, n2), n1);
			}

			/*
			 * reverse_impl
			 * Swap, in 'val', byte at index 'n1' with byte at index 'n2' in 'val', increment n1, decrement n2 until n1 > n2
			 */
			template<typename T>
			inline SPROUT_CONSTEXPR T
			reverse_impl(T val, std::uint_fast8_t n1, std::uint_fast8_t n2) {
				return n1 > n2 ? val : sprout::net::detail::reverse_impl(sprout::net::detail::swap(val, n1, n2), n1 + 1, n2 - 1);
			}

			/*
			 * reverse
			 * Reverse 'val'
			 */
			template<typename T>
			inline SPROUT_CONSTEXPR T
			reverse(T val) {
				return sprout::net::detail::reverse_impl(val, 0, sizeof(T) - 1);
			}

			/*
			 * reverse_words_impl
			 * Swap, in 'val', byte at index 'n' - 1 with byte at index 'n' - 2, decrement n by 2 until n == 0
			 */
			template<typename T>
			inline SPROUT_CONSTEXPR T
			reverse_words_impl(T val, std::uint_fast8_t n) {
				return n == 0 ? val : sprout::net::detail::reverse_words_impl(swap(val, n - 1, n - 2), n - 2);
			}

			/*
			 * reverse_words
			 * Reverse each word in 'val'
			 */
			template<typename T>
			inline SPROUT_CONSTEXPR T
			reverse_words(T val) {
				return sprout::net::detail::reverse_words_impl(val, sizeof(T));
			}
		}	// namespace detail

		// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3620.pdf
		// template<>
		// constexpr unsigned-integral hton(unsigned-integral host)
		template<typename T>
		inline SPROUT_CONSTEXPR T
		hton SPROUT_PREVENT_MACRO_SUBSTITUTION (T host) {
#if defined(SPROUT_BIG_ENDIAN)
			return host;
#elif defined(SPROUT_LITTLE_ENDIAN)
			return sprout::net::detail::reverse(host);
#elif defined(SPROUT_PDP_ENDIAN)
			return sprout::net::detail::reverse_words(host);
#else
			return SPROUT_ASSERT_MSG(0, "hton: unsupported endian"), host;
#endif
		}

		// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3620.pdf
		// template<>
		// constexpr unsigned-integral ntoh(unsigned-integral net)
		template<typename T>
		inline SPROUT_CONSTEXPR T
		ntoh SPROUT_PREVENT_MACRO_SUBSTITUTION (T net) {
#if defined(SPROUT_BIG_ENDIAN)
			return net;
#elif defined(SPROUT_LITTLE_ENDIAN)
			return sprout::net::detail::reverse(net);
#elif defined(SPROUT_PDP_ENDIAN)
			return sprout::net::detail::reverse_words(host);
#else
			return SPROUT_ASSERT_MSG(0, "ntoh: unsupported endian"), net;
#endif
		}

		// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3620.pdf
		// uint32_t htonl(uint32_t host32)
		inline SPROUT_CONSTEXPR std::uint32_t
		htonl SPROUT_PREVENT_MACRO_SUBSTITUTION (std::uint32_t host32) {
			return sprout::net::hton SPROUT_PREVENT_MACRO_SUBSTITUTION (host32);
		}

		// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3620.pdf
		// uint16_t htons(uint16_t host16)
		inline SPROUT_CONSTEXPR std::uint16_t
		htons SPROUT_PREVENT_MACRO_SUBSTITUTION (std::uint16_t host16) {
			return sprout::net::hton SPROUT_PREVENT_MACRO_SUBSTITUTION (host16);
		}

		// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3620.pdf
		// uint32_t ntohl(uint32_t net32)
		inline SPROUT_CONSTEXPR std::uint32_t
		ntohl SPROUT_PREVENT_MACRO_SUBSTITUTION (std::uint32_t net32) {
			return sprout::net::ntoh SPROUT_PREVENT_MACRO_SUBSTITUTION (net32);
		}

		// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3620.pdf
		// uint16_t ntohs(uint32_t net16)
		inline SPROUT_CONSTEXPR std::uint16_t
		ntohs SPROUT_PREVENT_MACRO_SUBSTITUTION (std::uint16_t net16) {
			return sprout::net::ntoh SPROUT_PREVENT_MACRO_SUBSTITUTION (net16);
		}
	}	//namespace net
}	// namespace sprout

#endif	// #ifndef SPROUT_NET_ENDIAN_HPP
