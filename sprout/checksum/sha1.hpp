/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CHECKSUM_SHA1_HPP
#define SPROUT_CHECKSUM_SHA1_HPP

#include <cstddef>
#include <cstdint>
#include <climits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/array/array.hpp>
#include <sprout/array/make_array.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/bytes_iterator.hpp>
#include <sprout/algorithm/fixed/fill.hpp>
#include <sprout/range/algorithm/fixed/copy.hpp>
#include <sprout/operation/fixed/set.hpp>
#include <sprout/bit/rotate.hpp>
#ifdef SPROUT_WORKAROUND_NOT_TERMINATE_RECURSIVE_CONSTEXPR_FUNCTION_TEMPLATE
#	include <sprout/workaround/recursive_function_template.hpp>
#endif

namespace sprout {
	static_assert(CHAR_BIT == 8, "CHAR_BIT == 8");

	//
	// sha1
	//
	class sha1 {
	public:
		typedef sprout::array<std::uint8_t, 20> value_type;
		typedef sha1 const const_type;
	private:
		sprout::array<std::uint32_t, 5> h_;
		sprout::array<std::uint8_t, 64> block_;
		std::size_t block_byte_index_;
		std::uint64_t bit_count_;
	private:
		SPROUT_CONSTEXPR sha1(
			sprout::array<std::uint32_t, 5> const& h,
			sprout::array<std::uint8_t, 64> const& block,
			std::size_t block_byte_index,
			std::uint64_t bit_count
			)
			: h_(h)
			, block_(block)
			, block_byte_index_(block_byte_index)
			, bit_count_(bit_count)
		{}
		SPROUT_CONSTEXPR std::uint32_t calc_w(std::size_t i) const {
			return i < 16
				? (block_[i * 4] << 24)
					| (block_[i * 4 + 1] << 16)
					| (block_[i * 4 + 2] << 8)
					| (block_[i * 4 + 3])
				: sprout::left_rotate(
					calc_w(i - 3) ^ calc_w(i - 8) ^ calc_w(i - 14) ^ calc_w(i - 16),
					1
					)
				;
		}
#ifdef SPROUT_WORKAROUND_NOT_TERMINATE_RECURSIVE_CONSTEXPR_FUNCTION_TEMPLATE
		template<int D = 16, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
		SPROUT_CONSTEXPR sha1 const process(
			sprout::array<std::uint32_t, 5> const& h,
			sprout::array<std::uint8_t, 64> const& block,
			std::size_t block_byte_index,
			std::uint64_t bit_count
			) const
		{
			return block_byte_index != 64
				? const_type(h, block, block_byte_index, bit_count)
				: const_type(h, block, 0, bit_count).process_block<D + 1>()
				;
		}
		template<int D = 16, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
		SPROUT_CONSTEXPR sha1 const process(
			sprout::array<std::uint32_t, 5> const&,
			sprout::array<std::uint8_t, 64> const&,
			std::size_t,
			std::uint64_t
			) const
		{
			return sprout::throw_recursive_function_template_instantiation_exeeded();
		}
		template<int D, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
		SPROUT_CONSTEXPR sha1 const process_block_2(
			std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::uint32_t e,
			std::size_t i, std::uint32_t f, std::uint32_t k
			) const
		{
			return process_block_1<D + 1>(
				sprout::left_rotate(a, 5) + f + e + k + calc_w(i),
				a,
				sprout::left_rotate(b, 30),
				c,
				d,
				i + 1
				);
		}
		template<int D, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
		SPROUT_CONSTEXPR sha1 const process_block_2(
			std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
			std::size_t, std::uint32_t, std::uint32_t
			) const
		{
			return sprout::throw_recursive_function_template_instantiation_exeeded();
		}
		template<int D, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
		SPROUT_CONSTEXPR sha1 const process_block_1(
			std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::uint32_t e,
			std::size_t i = 0
			) const
		{
			return i < 80
				? process_block_2<D + 1>(
					a, b, c, d, e,
					i,
					i < 20 ? (b & c) | (~b & d)
						: i < 40 ? b ^ c ^ d
						: i < 60 ? (b & c) | (b & d) | (c & d)
						: b ^ c ^ d
						,
					i < 20 ? 0x5A827999
						: i < 40 ? 0x6ED9EBA1
						: i < 60 ? 0x8F1BBCDC
						: 0xCA62C1D6
					)
				: sha1(
					sprout::array<std::uint32_t, 5>{{h_[0] + a, h_[1] + b, h_[2] + c, h_[3] + d, h_[4] + e}},
					block_,
					block_byte_index_,
					bit_count_
					)
				;
		}
		template<int D, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
		SPROUT_CONSTEXPR sha1 const process_block_1(
			std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t,
			std::size_t
			) const
		{
			return sprout::throw_recursive_function_template_instantiation_exeeded();
		}
		template<int D, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
		SPROUT_CONSTEXPR sha1 const process_block() const {
			return process_block_1<D + 1>(h_[0], h_[1], h_[2], h_[3], h_[4]);
		}
		template<int D, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
		SPROUT_CONSTEXPR sha1 const process_block() const {
			return sprout::throw_recursive_function_template_instantiation_exeeded();
		}
		template<int D = 16, typename InputIterator, typename... Args, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
		SPROUT_CONSTEXPR typename std::enable_if<sizeof...(Args) == 64, sha1 const>::type
		process_block_impl(InputIterator first, InputIterator last, Args... args) const {
			return first == last ? process<D + 1>(
					h_,
					sprout::make_array<std::uint8_t>(args...),
					64,
					bit_count_ + 64 * 8
					)
				// !!! TEMP:
//				: process<D + 1>(
//					h_,
//					sprout::make_array<std::uint8_t>(args...),
//					64,
//					bit_count_ + 64 * 8
//					).template process_block_impl<D + 1>(first, last)
				: sprout::throw_recursive_function_template_instantiation_exeeded()
				;
		}
		template<int D = 16, typename InputIterator, typename... Args, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
		SPROUT_CONSTEXPR typename std::enable_if<sizeof...(Args) == 64, sha1 const>::type
		process_block_impl(InputIterator, InputIterator, Args...) const {
			return sprout::throw_recursive_function_template_instantiation_exeeded();
		}
		template<int D = 16, typename InputIterator, typename... Args, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
		SPROUT_CONSTEXPR typename std::enable_if<sizeof...(Args) != 64, sha1 const>::type
		process_block_impl(InputIterator first, InputIterator last, Args... args) const {
			return first == last ? process<D + 1>(
					h_,
					sprout::get_internal(sprout::range::fixed::copy(sprout::make_array<std::uint8_t>(args...), sprout::sub(block_, block_byte_index_))),
					block_byte_index_ + sizeof...(Args),
					bit_count_ + sizeof...(Args) * 8
					)
				: block_byte_index_ + sizeof...(Args) == 64
				// !!! TEMP:
//					? process<D + 1>(
//						h_,
//						sprout::get_internal(sprout::range::fixed::copy(sprout::make_array<std::uint8_t>(args...), sprout::sub(block_, block_byte_index_))),
//						block_byte_index_ + sizeof...(Args),
//						bit_count_ + sizeof...(Args) * 8
//						).template process_block_impl<D + 1>(first, last)
					? sprout::throw_recursive_function_template_instantiation_exeeded()
				: process_block_impl<D + 1>(sprout::next(first), last, args..., *first)
				;
		}
		template<int D = 16, typename InputIterator, typename... Args, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
		SPROUT_CONSTEXPR typename std::enable_if<sizeof...(Args) != 64, sha1 const>::type
		process_block_impl(InputIterator, InputIterator, Args...) const {
			return sprout::throw_recursive_function_template_instantiation_exeeded();
		}
#else
		SPROUT_CONSTEXPR sha1 const process(
			sprout::array<std::uint32_t, 5> const& h,
			sprout::array<std::uint8_t, 64> const& block,
			std::size_t block_byte_index,
			std::uint64_t bit_count
			) const
		{
			return block_byte_index != 64
				? const_type(h, block, block_byte_index, bit_count)
				: const_type(h, block, 0, bit_count).process_block()
				;
		}
		SPROUT_CONSTEXPR sha1 const process_block_2(
			std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::uint32_t e,
			std::size_t i, std::uint32_t f, std::uint32_t k
			) const
		{
			return process_block_1(
				sprout::left_rotate(a, 5) + f + e + k + calc_w(i),
				a,
				sprout::left_rotate(b, 30),
				c,
				d,
				i + 1
				);
		}
		SPROUT_CONSTEXPR sha1 const process_block_1(
			std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::uint32_t e,
			std::size_t i = 0
			) const
		{
			return i < 80
				? process_block_2(
					a, b, c, d, e,
					i,
					i < 20 ? (b & c) | (~b & d)
						: i < 40 ? b ^ c ^ d
						: i < 60 ? (b & c) | (b & d) | (c & d)
						: b ^ c ^ d
						,
					i < 20 ? 0x5A827999
						: i < 40 ? 0x6ED9EBA1
						: i < 60 ? 0x8F1BBCDC
						: 0xCA62C1D6
					)
				: sha1(
					sprout::array<std::uint32_t, 5>{{h_[0] + a, h_[1] + b, h_[2] + c, h_[3] + d, h_[4] + e}},
					block_,
					block_byte_index_,
					bit_count_
					)
				;
		}
		SPROUT_CONSTEXPR sha1 const process_block() const {
			return process_block_1(h_[0], h_[1], h_[2], h_[3], h_[4]);
		}
		template<typename InputIterator, typename... Args>
		SPROUT_CONSTEXPR typename std::enable_if<sizeof...(Args) == 64, sha1 const>::type
		process_block_impl(InputIterator first, InputIterator last, Args... args) const {
			return first == last ? process(
					h_,
					sprout::make_array<std::uint8_t>(args...),
					64,
					bit_count_ + 64 * 8
					)
				: process(
					h_,
					sprout::make_array<std::uint8_t>(args...),
					64,
					bit_count_ + 64 * 8
					).process_block_impl(first, last)
				;
		}
		template<typename InputIterator, typename... Args>
		SPROUT_CONSTEXPR typename std::enable_if<sizeof...(Args) != 64, sha1 const>::type
		process_block_impl(InputIterator first, InputIterator last, Args... args) const {
			return first == last ? process(
					h_,
					sprout::get_internal(sprout::range::fixed::copy(sprout::make_array<std::uint8_t>(args...), sprout::sub(block_, block_byte_index_))),
					block_byte_index_ + sizeof...(Args),
					bit_count_ + sizeof...(Args) * 8
					)
				: block_byte_index_ + sizeof...(Args) == 64 ? process(
					h_,
					sprout::get_internal(sprout::range::fixed::copy(sprout::make_array<std::uint8_t>(args...), sprout::sub(block_, block_byte_index_))),
					block_byte_index_ + sizeof...(Args),
					bit_count_ + sizeof...(Args) * 8
					).process_block_impl(first, last)
				: process_block_impl(sprout::next(first), last, args..., *first)
				;
		}
#endif
		SPROUT_CONSTEXPR sha1 const process_one() const {
			return process(
				h_,
				sprout::fixed::set(block_, block_.begin() + block_byte_index_, static_cast<std::uint8_t>(0x80)),
				block_byte_index_ + 1,
				bit_count_
				);
		}
		template<typename... Args>
		SPROUT_CONSTEXPR sha1 const process_padding_after() const {
			return process(
				h_,
				sprout::array<std::uint8_t, 64>{{}},
				56,
				bit_count_
				);
		}
		template<typename... Args>
		SPROUT_CONSTEXPR sha1 const process_padding() const {
			return block_byte_index_ == 56 ? *this
				: block_byte_index_ > 56 ? process(
					h_,
					sprout::get_internal(sprout::fixed::fill(sprout::sub(block_, block_byte_index_), static_cast<std::uint8_t>(0))),
					64,
					bit_count_
					).process_padding_after()
				: process(
					h_,
					sprout::get_internal(sprout::fixed::fill(sprout::sub(block_, block_byte_index_, 56), static_cast<std::uint8_t>(0))),
					56,
					bit_count_
					)
				;
		}
		SPROUT_CONSTEXPR sha1 const process_length() const {
			return process(
				h_,
				sprout::get_internal(sprout::range::fixed::copy(
					sprout::array<std::uint8_t, 8>{{
						static_cast<std::uint8_t>((bit_count_ >> 56) & 0xFF),
						static_cast<std::uint8_t>((bit_count_ >> 48) & 0xFF),
						static_cast<std::uint8_t>((bit_count_ >> 40) & 0xFF),
						static_cast<std::uint8_t>((bit_count_ >> 32) & 0xFF),
						static_cast<std::uint8_t>((bit_count_ >> 24) & 0xFF),
						static_cast<std::uint8_t>((bit_count_ >> 16) & 0xFF),
						static_cast<std::uint8_t>((bit_count_ >> 8) & 0xFF),
						static_cast<std::uint8_t>(bit_count_ & 0xFF)
						}},
					sprout::sub(block_, block_byte_index_)
					)),
				block_byte_index_ + 8,
				bit_count_
				);
		}
		SPROUT_CONSTEXPR value_type make_value() const {
			return value_type{{
				static_cast<std::uint8_t>((h_[0] >> 24) & 0xFF),
				static_cast<std::uint8_t>((h_[0] >> 16) & 0xFF),
				static_cast<std::uint8_t>((h_[0] >> 8) & 0xFF),
				static_cast<std::uint8_t>((h_[0]) & 0xFF),
				static_cast<std::uint8_t>((h_[1] >> 24) & 0xFF),
				static_cast<std::uint8_t>((h_[1] >> 16) & 0xFF),
				static_cast<std::uint8_t>((h_[1] >> 8) & 0xFF),
				static_cast<std::uint8_t>((h_[1]) & 0xFF),
				static_cast<std::uint8_t>((h_[2] >> 24) & 0xFF),
				static_cast<std::uint8_t>((h_[2] >> 16) & 0xFF),
				static_cast<std::uint8_t>((h_[2] >> 8) & 0xFF),
				static_cast<std::uint8_t>((h_[2]) & 0xFF),
				static_cast<std::uint8_t>((h_[3] >> 24) & 0xFF),
				static_cast<std::uint8_t>((h_[3] >> 16) & 0xFF),
				static_cast<std::uint8_t>((h_[3] >> 8) & 0xFF),
				static_cast<std::uint8_t>((h_[3]) & 0xFF),
				static_cast<std::uint8_t>((h_[4] >> 24) & 0xFF),
				static_cast<std::uint8_t>((h_[4] >> 16) & 0xFF),
				static_cast<std::uint8_t>((h_[4] >> 8) & 0xFF),
				static_cast<std::uint8_t>((h_[4]) & 0xFF)
				}};
		}
		SPROUT_CXX14_CONSTEXPR void process_block() {
			std::uint32_t w[80] = {};
			for (std::size_t i = 0; i < 16; ++i) {
				w[i] = (block_[i * 4 + 0] << 24);
				w[i] |= (block_[i * 4 + 1] << 16);
				w[i] |= (block_[i * 4 + 2] << 8);
				w[i] |= (block_[i * 4 + 3]);
			}
			for (std::size_t i = 16; i < 80; ++i) {
				w[i] = sprout::left_rotate((w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]), 1);
			}
			std::uint32_t a = h_[0];
			std::uint32_t b = h_[1];
			std::uint32_t c = h_[2];
			std::uint32_t d = h_[3];
			std::uint32_t e = h_[4];
			for (std::size_t i = 0; i < 80; ++i) {
				std::uint32_t f = 0;
				std::uint32_t k = 0;
				if (i<20) {
					f = (b & c) | (~b & d);
					k = 0x5A827999;
				} else if (i<40) {
					f = b ^ c ^ d;
					k = 0x6ED9EBA1;
				} else if (i<60) {
					f = (b & c) | (b & d) | (c & d);
					k = 0x8F1BBCDC;
				} else {
					f = b ^ c ^ d;
					k = 0xCA62C1D6;
				}
				unsigned temp = sprout::left_rotate(a, 5) + f + e + k + w[i];
				e = d;
				d = c;
				c = sprout::left_rotate(b, 30);
				b = a;
				a = temp;
			}
			h_[0] += a;
			h_[1] += b;
			h_[2] += c;
			h_[3] += d;
			h_[4] += e;
		}
		SPROUT_CXX14_CONSTEXPR void process_byte_impl(unsigned char byte) {
			block_[block_byte_index_++] = byte;
			if (block_byte_index_ == 64) {
				block_byte_index_ = 0;
				process_block();
			}
		}
		template<typename InputIterator>
		SPROUT_CXX14_CONSTEXPR void process_block_impl(InputIterator first, InputIterator last) {
			for(; first != last; ++first) {
				process_byte(*first);
			}
		}
	public:
		SPROUT_CONSTEXPR sha1()
			: h_{{0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0}}
			, block_{{}}
			, block_byte_index_()
			, bit_count_()
		{}
		SPROUT_CXX14_CONSTEXPR void reset() {
			h_[0] = 0x67452301;
			h_[1] = 0xEFCDAB89;
			h_[2] = 0x98BADCFE;
			h_[3] = 0x10325476;
			h_[4] = 0xC3D2E1F0;
			block_byte_index_ = 0;
			bit_count_ = 0;
		}

		SPROUT_CONSTEXPR sha1 const process_byte(std::uint8_t byte) const {
			return process(
				h_,
				sprout::fixed::set(block_, block_.begin() + block_byte_index_, byte),
				block_byte_index_ + 1,
				bit_count_ + 8
				);
		}
		template<typename InputIterator>
		SPROUT_CONSTEXPR sha1 const process_block(InputIterator bytes_begin, InputIterator bytes_end) const {
			return process_block_impl(
				sprout::make_bytes_iterator(bytes_begin),
				sprout::make_bytes_iterator(bytes_end)
				);
		}
		template<typename InputIterator>
		SPROUT_CONSTEXPR sha1 const process_bytes(InputIterator buffer, std::size_t byte_count) const {
			return process_block(buffer, sprout::next(buffer, byte_count));
		}
		template<typename InputRange>
		SPROUT_CONSTEXPR sha1 const process_range(InputRange const& bytes_range) const {
			return process_block(sprout::begin(bytes_range), sprout::end(bytes_range));
		}

		SPROUT_CXX14_CONSTEXPR void process_byte(std::uint8_t byte) {
			process_byte_impl(byte);
			bit_count_ += 8;
		}
		template<typename InputIterator>
		SPROUT_CXX14_CONSTEXPR void process_block(InputIterator bytes_begin, InputIterator bytes_end) {
			process_block_impl(
				sprout::make_bytes_iterator(bytes_begin),
				sprout::make_bytes_iterator(bytes_end)
				);
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
			return process_one().process_padding().process_length().make_value();
		}
		SPROUT_CONSTEXPR value_type operator()() const {
			return checksum();
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CHECKSUM_SHA1_HPP
