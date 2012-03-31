#ifndef SPROUT_CHECKSUM_SHA1_HPP
#define SPROUT_CHECKSUM_SHA1_HPP

#include <cstddef>
#include <cstdint>
#include <climits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/bytes_iterator.hpp>
#include <sprout/range/algorithm/fixed/copy.hpp>
#include <sprout/operation/fixed/set.hpp>

namespace sprout {
	static_assert(CHAR_BIT == 8, "CHAR_BIT == 8");

	namespace detail {
		SPROUT_CONSTEXPR inline std::uint32_t sha1_left_rotate(std::uint32_t x, std::size_t n) {
			return (x << n) ^ (x >> (32 - n));
		}
	}	// namespace detail

	//
	// sha1
	//
	class sha1 {
	public:
		typedef sprout::array<std::uint8_t, 20> value_type;
	private:
		sprout::array<std::uint32_t, 5> h_;
		sprout::array<std::uint8_t, 64> block_;
		std::size_t block_byte_index_;
		std::size_t byte_count_;
	private:
		SPROUT_CONSTEXPR sha1(
			sprout::array<std::uint32_t, 5> const& h,
			sprout::array<std::uint8_t, 64> const& block,
			std::size_t block_byte_index,
			std::size_t byte_count
			)
			: h_(h)
			, block_(block)
			, block_byte_index_(block_byte_index)
			, byte_count_(byte_count)
		{}
		SPROUT_CONSTEXPR std::uint32_t calc_w(std::size_t i) const {
			return i < 16
				? (block_[i * 4] << 24)
					| (block_[i * 4 + 1] << 16)
					| (block_[i * 4 + 2] << 8)
					| (block_[i * 4 + 3])
				: sprout::detail::sha1_left_rotate(
					calc_w(i - 3) ^ calc_w(i - 8) ^ calc_w(i - 14) ^ calc_w(i - 16),
					1
					)
				;
		}
		SPROUT_CONSTEXPR sha1 process(
			sprout::array<std::uint32_t, 5> const& h,
			sprout::array<std::uint8_t, 64> const& block,
			std::size_t block_byte_index,
			std::size_t byte_count
			) const
		{
			return block_byte_index != 64
				? sha1(
					h,
					block,
					block_byte_index,
					byte_count
					)
				: sha1(
					h,
					block,
					0,
					byte_count
					).process_block()
				;
		}
		SPROUT_CONSTEXPR sha1 process_block_2(
			std::uint32_t a,
			std::uint32_t b,
			std::uint32_t c,
			std::uint32_t d,
			std::uint32_t e,
			std::size_t i,
			std::uint32_t f,
			std::uint32_t k
			) const
		{
			return process_block_1(
				sprout::detail::sha1_left_rotate(a, 5) + f + e + k + calc_w(i),
				a,
				sprout::detail::sha1_left_rotate(b, 30),
				c,
				d,
				i + 1
				);
		}
		SPROUT_CONSTEXPR sha1 process_block_1(
			std::uint32_t a,
			std::uint32_t b,
			std::uint32_t c,
			std::uint32_t d,
			std::uint32_t e,
			std::size_t i = 0
			) const
		{
			return i < 80
				? process_block_2(
					a,
					b,
					c,
					d,
					e,
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
					byte_count_
					)
				;
		}
		SPROUT_CONSTEXPR sha1 process_block() const {
			return process_block_1(h_[0], h_[1], h_[2], h_[3], h_[4]);
		}
		template<typename Iterator, typename... Args>
		SPROUT_CONSTEXPR typename std::enable_if<
			sizeof...(Args) == 64,
			sha1
		>::type process_block_impl(
			Iterator first,
			Iterator last,
			Args... args
			) const
		{
			return first == last ? process(
					h_,
					sprout::make_array<std::uint8_t>(args...),
					64,
					byte_count_ + 64
					)
				: process(
					h_,
					sprout::make_array<std::uint8_t>(args...),
					64,
					byte_count_ + 64
					).process_block_impl(first, last)
				;
		}
		template<typename Iterator, typename... Args>
		SPROUT_CONSTEXPR typename std::enable_if<
			sizeof...(Args) != 64,
			sha1
		>::type process_block_impl(
			Iterator first,
			Iterator last,
			Args... args
			) const
		{
			return first == last ? process(
					h_,
					sprout::get_internal(sprout::range::fixed::copy(sprout::make_array<std::uint8_t>(args...), sprout::sub(block_, block_byte_index_))),
					block_byte_index_ + sizeof...(Args),
					byte_count_ + sizeof...(Args)
					)
				: block_byte_index_ + sizeof...(Args) == 64 ? process(
					h_,
					sprout::get_internal(sprout::range::fixed::copy(sprout::make_array<std::uint8_t>(args...), sprout::sub(block_, block_byte_index_))),
					block_byte_index_ + sizeof...(Args),
					byte_count_ + sizeof...(Args)
					).process_block_impl(first, last)
				: process_block_impl(sprout::next(first), last, args..., *first)
				;
		}
		template<typename... Args>
		SPROUT_CONSTEXPR typename std::enable_if<
			sizeof...(Args) == 64,
			sha1
		>::type process_padding(
			Args... args
			) const
		{
			return process(
					h_,
					sprout::make_array<std::uint8_t>(args...),
					64,
					byte_count_ + 64
					).process_padding()
				;
		}
		template<typename... Args>
		SPROUT_CONSTEXPR typename std::enable_if<
			sizeof...(Args) != 64,
			sha1
		>::type process_padding(
			Args... args
			) const
		{
			return block_byte_index_ + sizeof...(Args) == 56 ? process(
					h_,
					sprout::get_internal(sprout::range::fixed::copy(sprout::make_array<std::uint8_t>(args...), sprout::sub(block_, block_byte_index_))),
					block_byte_index_ + sizeof...(Args),
					byte_count_ + sizeof...(Args)
					)
				: block_byte_index_ + sizeof...(Args) == 64 ? process(
					h_,
					sprout::get_internal(sprout::range::fixed::copy(sprout::make_array<std::uint8_t>(args...), sprout::sub(block_, block_byte_index_))),
					block_byte_index_ + sizeof...(Args),
					byte_count_ + sizeof...(Args)
					).process_padding()
				: process_padding(args..., static_cast<std::uint8_t>(0))
				;
		}
		SPROUT_CONSTEXPR sha1 process_append() const {
			return process(
				h_,
				sprout::get_internal(sprout::range::fixed::copy(
					sprout::array<std::uint8_t, 8>{{
						static_cast<std::uint8_t>(0),
						static_cast<std::uint8_t>(0),
						static_cast<std::uint8_t>(0),
						static_cast<std::uint8_t>(0),
						static_cast<std::uint8_t>((byte_count_ * 8 >> 24) & 0xFF),
						static_cast<std::uint8_t>((byte_count_ * 8 >> 16) & 0xFF),
						static_cast<std::uint8_t>((byte_count_ * 8 >> 8) & 0xFF),
						static_cast<std::uint8_t>((byte_count_ * 8) & 0xFF)
						}},
					sprout::sub(block_, block_byte_index_)
					)),
				block_byte_index_ + 8,
				byte_count_ + 8
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
	public:
		SPROUT_CONSTEXPR sha1()
			: h_{{0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0}}
			, block_{{}}
			, block_byte_index_()
			, byte_count_()
		{}
		SPROUT_CONSTEXPR sha1 process_byte(std::uint8_t byte) const {
			return process(
				h_,
				sprout::fixed::set(block_, block_.begin() + block_byte_index_, byte),
				block_byte_index_ + 1,
				byte_count_ + 1
				);
		}
		template<typename Iterator>
		SPROUT_CONSTEXPR sha1 process_block(Iterator bytes_begin, Iterator bytes_end) const {
			return process_block_impl(
				sprout::make_bytes_iterator(bytes_begin),
				sprout::make_bytes_iterator(bytes_end)
				);
		}
		template<typename Iterator>
		SPROUT_CONSTEXPR sha1 process_bytes(Iterator buffer, std::size_t byte_count) const {
			return process_block(buffer, sprout::next(buffer, byte_count));
		}
		template<typename Range>
		SPROUT_CONSTEXPR sha1 process_range(Range const& bytes_range) const {
			return process_block(sprout::begin(bytes_range), sprout::end(bytes_range));
		}
		SPROUT_CONSTEXPR value_type checksum() const {
			return process_byte(0x80).process_padding().process_append().make_value();
		}
		SPROUT_CONSTEXPR value_type operator()() const {
			return checksum();
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CHECKSUM_SHA1_HPP
