/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Copyright (c) 2014 Chris KAY
  https://github.com/cjkay-cpp-utils/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NET_NET_HPP
#define SPROUT_NET_NET_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <boost/detail/endian.hpp>

namespace sprout {
    namespace net {
        namespace detail {
            template<typename T>
            SPROUT_CONSTEXPR T lshift(T val, uint_fast8_t byte) {
                return val << (byte * 8);
            }

            template<typename T>
            SPROUT_CONSTEXPR T rshift(T val, uint_fast8_t byte) {
                return val >> (byte * 8);
            }

            template<typename T>
            SPROUT_CONSTEXPR T mask(uint_fast8_t byte) {
                return lshift(T(0xFF), byte);
            }

            template<typename T>
            SPROUT_CONSTEXPR T byte_at(T val, uint_fast8_t byte) {
                return rshift((val & mask<T>(byte)), byte);
            }

            template<typename T>
            SPROUT_CONSTEXPR T overwrite(T val, uint8_t byte_val, uint_fast8_t to) {
                return (val & ~mask<T>(to)) | lshift(T(byte_val), to);
            }

            template<typename T>
            SPROUT_CONSTEXPR T move(T val, uint_fast8_t from, uint_fast8_t to) {
                return overwrite(val, byte_at(val, from), to);
            }

            template<typename T>
            SPROUT_CONSTEXPR T swap(T val, uint_fast8_t byte1, uint_fast8_t byte2) {
                return overwrite(move(val, byte1, byte2), byte_at(val, byte2), byte1);
            }

            template<typename T>
            SPROUT_CONSTEXPR T reverse_impl(T val, uint_fast8_t byte1, uint_fast8_t byte2) {
                return byte1 > byte2 ? val : reverse_impl(swap(val, byte1, byte2), byte1 + 1, byte2 - 1);
            }

            template<typename T>
            SPROUT_CONSTEXPR T reverse(T val) {
                return reverse_impl(val, 0, sizeof(T) - 1);
            }

            template<typename T>
            SPROUT_CONSTEXPR T reverse_words_impl(T val, uint_fast8_t byte) {
                return byte == 0 ? val : reverse_words_impl(swap(val, byte - 1, byte - 2), byte - 2);
            }

            template<typename T>
            SPROUT_CONSTEXPR T reverse_words(T val) {
                return reverse_words_impl(val, sizeof(T));
            }
        }

        template<typename T>
        SPROUT_CONSTEXPR T hton(T host) {
#if defined(BOOST_BIG_ENDIAN)
            return host;
#elif defined(BOOST_LITTLE_ENDIAN)
            return detail::reverse(host);
#elif defined(BOOST_PDP_ENDIAN)
            return detail::reverse_words(host);
#endif
        }

        template<typename T>
        SPROUT_CONSTEXPR T ntoh(T net) {
#if defined(BOOST_BIG_ENDIAN)
            return net;
#elif defined(BOOST_LITTLE_ENDIAN)
            return detail::reverse(net);
#elif defined(BOOST_PDP_ENDIAN)
            return detail::reverse_words(host);
#endif
        }

        SPROUT_CONSTEXPR uint32_t htonl(uint32_t host32) {
            return hton(host32);
        }

        SPROUT_CONSTEXPR uint16_t htons(uint16_t host16) {
            return hton(host16);
        }

        SPROUT_CONSTEXPR uint32_t ntohl(uint32_t net32) {
            return ntoh(net32);
        }

        SPROUT_CONSTEXPR uint16_t ntohs(uint16_t net16) {
            return ntoh(net16);
        }
    }   //namespace net
}	// namespace sprout

#endif	// #ifndef SPROUT_NET_NET_HPP
