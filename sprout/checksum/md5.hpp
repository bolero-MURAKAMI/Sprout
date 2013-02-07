#ifndef SPROUT_CHECKSUM_MD5_HPP
#define SPROUT_CHECKSUM_MD5_HPP

#include <cstddef>
#include <cstdint>
#include <climits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/array/array.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/bytes_iterator.hpp>
#include <sprout/operation/fixed/set.hpp>
#include <sprout/bit/rotate.hpp>

namespace sprout {
	static_assert(CHAR_BIT == 8, "CHAR_BIT == 8");

	namespace md5_detail {
		inline SPROUT_CONSTEXPR std::uint32_t
		func_f(std::uint32_t x, std::uint32_t y, std::uint32_t z) {
			return (x & y) | (~x & z);
		}
		inline SPROUT_CONSTEXPR std::uint32_t
		func_g(std::uint32_t x, std::uint32_t y, std::uint32_t z) {
			return (x & z) | (y & ~z);
		}
		inline SPROUT_CONSTEXPR std::uint32_t
		func_h(std::uint32_t x, std::uint32_t y, std::uint32_t z) {
			return x ^ y ^ z;
		}
		inline SPROUT_CONSTEXPR std::uint32_t
		func_i(std::uint32_t x, std::uint32_t y, std::uint32_t z) {
			return y ^ (x | ~z);
		}

		struct round1_op {
		public:
			SPROUT_CONSTEXPR std::uint32_t
			operator()(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::uint32_t x, std::uint32_t t, std::uint32_t s) const {
				return b + sprout::left_rotate(a + sprout::md5_detail::func_f(b, c, d) + x + t, s);
			}
		};
		struct round2_op {
		public:
			inline SPROUT_CONSTEXPR std::uint32_t
			operator()(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::uint32_t x, std::uint32_t t, std::uint32_t s) const {
				return b + sprout::left_rotate(a + sprout::md5_detail::func_g(b, c, d) + x + t, s);
			}
		};
		struct round3_op {
		public:
			inline SPROUT_CONSTEXPR std::uint32_t
			operator()(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::uint32_t x, std::uint32_t t, std::uint32_t s) const {
				return b + sprout::left_rotate(a + sprout::md5_detail::func_h(b, c, d) + x + t, s);
			}
		};
		struct round4_op {
		public:
			inline SPROUT_CONSTEXPR std::uint32_t
			operator()(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::uint32_t x, std::uint32_t t, std::uint32_t s) const {
				return b + sprout::left_rotate(a + sprout::md5_detail::func_i(b, c, d) + x + t, s);
			}
		};

		template<typename RoundOp>
		inline SPROUT_CONSTEXPR sprout::array<std::uint32_t, 4>
		round_x_impl(
			std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d, sprout::array<std::uint32_t, 16> const& x, RoundOp round_op,
			sprout::array<std::size_t, 16> const& xis, sprout::array<std::uint32_t, 16> const& ts, sprout::array<std::uint32_t, 16> const& ss,
			std::size_t i = 0
			)
		{
			return i == 16 ? sprout::array<std::uint32_t, 4>{{a, b, c, d}}
				: i % 4 == 0 ? sprout::md5_detail::round_x_impl(round_op(a, b, c, d, x[xis[i]], ts[i], ss[i]), b, c, d, x, round_op, xis, ts, ss, i + 1)
				: i % 4 == 1 ? sprout::md5_detail::round_x_impl(a, b, c, round_op(d, a, b, c, x[xis[i]], ts[i], ss[i]), x, round_op, xis, ts, ss, i + 1)
				: i % 4 == 2 ? sprout::md5_detail::round_x_impl(a, b, round_op(c, d, a, b, x[xis[i]], ts[i], ss[i]), d, x, round_op, xis, ts, ss, i + 1)
				: sprout::md5_detail::round_x_impl(a, round_op(b, c, d, a, x[xis[i]], ts[i], ss[i]), c, d, x, round_op, xis, ts, ss, i + 1)
				;
		}
		template<typename RoundOp>
		inline SPROUT_CONSTEXPR sprout::array<std::uint32_t, 4>
		round_x(
			sprout::array<std::uint32_t, 4> const& k, sprout::array<std::uint32_t, 16> const& x, RoundOp round_op,
			sprout::array<std::size_t, 16> const& xis, sprout::array<std::uint32_t, 16> const& ts, sprout::array<std::uint32_t, 16> const& ss
			)
		{
			return sprout::md5_detail::round_x_impl(k[0], k[1], k[2], k[3], x, round_op, xis, ts, ss);
		}

		template<int N>
		struct round_table;

#	define SPROUT_MD5_DETAIL_ROUND_TABLE_DEF(N, XIS, TS, SS) \
		template<> \
		struct round_table<N> { \
		public: \
			typedef sprout::array<std::size_t, 16> xis_type; \
			typedef sprout::array<std::uint32_t, 16> ts_type; \
			typedef sprout::array<std::uint32_t, 16> ss_type; \
		public: \
			SPROUT_STATIC_CONSTEXPR xis_type xis \
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(XIS) \
				; \
			SPROUT_STATIC_CONSTEXPR ts_type ts \
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(TS) \
				; \
			SPROUT_STATIC_CONSTEXPR ss_type ss \
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(SS) \
				; \
		}; \
		SPROUT_CONSTEXPR_OR_CONST typename sprout::md5_detail::round_table<N>::xis_type sprout::md5_detail::round_table<N>::xis \
			SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(XIS) \
			; \
		SPROUT_CONSTEXPR_OR_CONST typename sprout::md5_detail::round_table<N>::ts_type sprout::md5_detail::round_table<N>::ts \
			SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(TS) \
			; \
		SPROUT_CONSTEXPR_OR_CONST typename sprout::md5_detail::round_table<N>::ss_type sprout::md5_detail::round_table<N>::ss \
			SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(SS)

		SPROUT_MD5_DETAIL_ROUND_TABLE_DEF( \
			1, \
			(xis_type{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}}), \
			(ts_type{{ \
				0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE, 0xF57C0FAF, 0x4787C62A, 0xA8304613, 0xFD469501, \
				0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE, 0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821 \
				}}), \
			(ss_type{{7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22}}) \
			);
		SPROUT_MD5_DETAIL_ROUND_TABLE_DEF( \
			2, \
			(xis_type{{1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12}}), \
			(ts_type{{ \
				0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA, 0xD62F105D, 0x02441453, 0xD8A1E681, 0xE7D3FBC8, \
				0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED, 0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A \
				}}), \
			(ss_type{{5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20}}) \
			);
		SPROUT_MD5_DETAIL_ROUND_TABLE_DEF( \
			3, \
			(xis_type{{5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2}}), \
			(ts_type{{ \
				0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C, 0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70, \
				0x289B7EC6, 0xEAA127FA, 0xD4EF3085, 0x04881D05, 0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665 \
				}}), \
			(ss_type{{4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23}}) \
			);
		SPROUT_MD5_DETAIL_ROUND_TABLE_DEF( \
			4, \
			(xis_type{{0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9}}), \
			(ts_type{{ \
				0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039, 0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1, \
				0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1, 0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391 \
				}}), \
			(ss_type{{6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21}}) \
			);
#	undef SPROUT_MD5_DETAIL_ROUND_TABLE_DEF

		inline SPROUT_CONSTEXPR sprout::array<std::uint32_t, 4>
		round1(sprout::array<std::uint32_t, 4> const& k, sprout::array<std::uint32_t, 16> const& x) {
			return sprout::md5_detail::round_x(
				k, x, sprout::md5_detail::round1_op(),
				sprout::md5_detail::round_table<1>::xis,
				sprout::md5_detail::round_table<1>::ts,
				sprout::md5_detail::round_table<1>::ss
				);
		}
		inline SPROUT_CONSTEXPR sprout::array<std::uint32_t, 4>
		round2(sprout::array<std::uint32_t, 4> const& k, sprout::array<std::uint32_t, 16> const& x) {
			return sprout::md5_detail::round_x(
				k, x, sprout::md5_detail::round2_op(),
				sprout::md5_detail::round_table<2>::xis,
				sprout::md5_detail::round_table<2>::ts,
				sprout::md5_detail::round_table<2>::ss
				);
		}
		inline SPROUT_CONSTEXPR sprout::array<std::uint32_t, 4>
		round3(sprout::array<std::uint32_t, 4> const& k, sprout::array<std::uint32_t, 16> const& x) {
			return sprout::md5_detail::round_x(
				k, x, sprout::md5_detail::round3_op(),
				sprout::md5_detail::round_table<3>::xis,
				sprout::md5_detail::round_table<3>::ts,
				sprout::md5_detail::round_table<3>::ss
				);
		}
		inline SPROUT_CONSTEXPR sprout::array<std::uint32_t, 4>
		round4(sprout::array<std::uint32_t, 4> const& k, sprout::array<std::uint32_t, 16> const& x) {
			return sprout::md5_detail::round_x(
				k, x, sprout::md5_detail::round4_op(),
				sprout::md5_detail::round_table<4>::xis,
				sprout::md5_detail::round_table<4>::ts,
				sprout::md5_detail::round_table<4>::ss
				);
		}

		inline SPROUT_CONSTEXPR sprout::array<std::uint32_t, 4>
		round_all(sprout::array<std::uint32_t, 4> const& k, sprout::array<std::uint32_t, 16> const& x) {
			return sprout::md5_detail::round4(
				sprout::md5_detail::round3(
					sprout::md5_detail::round2(
						sprout::md5_detail::round1(k, x),
						x
						),
					x
					),
				x
				);
		}
	}	// namespace detail

	//
	// md5
	//
	class md5 {
	public:
		typedef sprout::array<std::uint8_t, 16> value_type;
		typedef md5 const const_type;
	private:
		sprout::array<std::uint32_t, 4> k_;
		sprout::array<std::uint32_t, 16> block_;
		std::uint64_t bit_count_;
	private:
		SPROUT_CONSTEXPR md5(
			sprout::array<std::uint32_t, 4> const& k,
			std::uint64_t bit_count
			)
			: k_(k)
			, block_{{}}
			, bit_count_(bit_count)
		{}
		SPROUT_CONSTEXPR md5(
			sprout::array<std::uint32_t, 4> const& k,
			sprout::array<std::uint32_t, 16> const& block,
			std::uint64_t bit_count
			)
			: k_(k)
			, block_(block)
			, bit_count_(bit_count)
		{}
		SPROUT_CONSTEXPR md5 const process(
			sprout::array<std::uint32_t, 4> const& k,
			sprout::array<std::uint32_t, 16> const& block,
			std::uint64_t bit_count
			) const
		{
			return bit_count % (64 * 8) != 0 ? const_type(k, block, bit_count)
				: const_type(k, block, bit_count).process_block()
				;
		}
		SPROUT_CONSTEXPR md5 const process_block_1(sprout::array<std::uint32_t, 4> const& x) const {
			return md5(
				sprout::array<std::uint32_t, 4>{{k_[0] + x[0], k_[1] + x[1], k_[2] + x[2], k_[3] + x[3]}},
				bit_count_
				);
		}
		SPROUT_CONSTEXPR md5 const process_block() const {
			return process_block_1(sprout::md5_detail::round_all(k_, block_));
		}
		SPROUT_CONSTEXPR md5 const process_bit_impl(bool bit, std::size_t index, std::size_t offset) const {
			return process(
				k_,
				sprout::fixed::set(
					block_,
					block_.begin() + index,
					block_[index] | static_cast<std::uint32_t>(bit) << (offset / 8 * 8 + (7 - offset % 8))
					),
				bit_count_ + 1
				);
		}
		SPROUT_CONSTEXPR md5 const process_bits_impl(std::uint8_t bits, std::size_t i) const {
			return i == 0 ? *this
				: process_bit(((bits >> (i - 1)) & 1) != 0).process_bits_impl(bits, i - 1)
				;
		}
		SPROUT_CONSTEXPR md5 const process_byte_impl(std::uint8_t byte, std::size_t index, std::size_t offset) const {
			return process(
				k_,
				sprout::fixed::set(
					block_,
					block_.begin() + index,
					block_[index]
						| static_cast<std::uint32_t>(((byte >> 7) & 1) != 0) << (offset / 8 * 8 + (7 - offset % 8))
						| static_cast<std::uint32_t>(((byte >> 6) & 1) != 0) << ((offset + 1) / 8 * 8 + (7 - (offset + 1) % 8))
						| static_cast<std::uint32_t>(((byte >> 5) & 1) != 0) << ((offset + 2) / 8 * 8 + (7 - (offset + 2) % 8))
						| static_cast<std::uint32_t>(((byte >> 4) & 1) != 0) << ((offset + 3) / 8 * 8 + (7 - (offset + 3) % 8))
						| static_cast<std::uint32_t>(((byte >> 3) & 1) != 0) << ((offset + 4) / 8 * 8 + (7 - (offset + 4) % 8))
						| static_cast<std::uint32_t>(((byte >> 2) & 1) != 0) << ((offset + 5) / 8 * 8 + (7 - (offset + 5) % 8))
						| static_cast<std::uint32_t>(((byte >> 1) & 1) != 0) << ((offset + 6) / 8 * 8 + (7 - (offset + 6) % 8))
						| static_cast<std::uint32_t>((byte & 1) != 0) << ((offset + 7) / 8 * 8 + (7 - (offset + 7) % 8))
					),
				bit_count_ + 8
				);
		}
		template<typename Iterator>
		SPROUT_CONSTEXPR md5 const process_block_impl(Iterator first, Iterator last) const {
			return first == last ? *this
				: process_byte(*first).process_block_impl(sprout::next(first), last)
				;
		}
		SPROUT_CONSTEXPR std::uint64_t pad_size() const {
			return static_cast<std::size_t>((511 + 448 - bit_count_) % 512);
		}
		SPROUT_CONSTEXPR md5 const process_padding(std::uint64_t pad_size) const {
			return pad_size == 0 ? *this
				: process_bit(false).process_padding(pad_size - 1)
				;
		}
		SPROUT_CONSTEXPR md5 const process_length(std::uint64_t bit_count) const {
			return process_byte(static_cast<std::uint8_t>(bit_count & 0xFF))
				.process_byte(static_cast<std::uint8_t>((bit_count >> 8) & 0xFF))
				.process_byte(static_cast<std::uint8_t>((bit_count >> 16) & 0xFF))
				.process_byte(static_cast<std::uint8_t>((bit_count >> 24) & 0xFF))
				.process_byte(static_cast<std::uint8_t>((bit_count >> 32) & 0xFF))
				.process_byte(static_cast<std::uint8_t>((bit_count >> 40) & 0xFF))
				.process_byte(static_cast<std::uint8_t>((bit_count >> 48) & 0xFF))
				.process_byte(static_cast<std::uint8_t>((bit_count >> 56) & 0xFF))
				;
		}
		SPROUT_CONSTEXPR value_type make_value() const {
			return value_type{{
				static_cast<std::uint8_t>((k_[0]) & 0xFF),
				static_cast<std::uint8_t>((k_[0] >> 8) & 0xFF),
				static_cast<std::uint8_t>((k_[0] >> 16) & 0xFF),
				static_cast<std::uint8_t>((k_[0] >> 24) & 0xFF),
				static_cast<std::uint8_t>((k_[1]) & 0xFF),
				static_cast<std::uint8_t>((k_[1] >> 8) & 0xFF),
				static_cast<std::uint8_t>((k_[1] >> 16) & 0xFF),
				static_cast<std::uint8_t>((k_[1] >> 24) & 0xFF),
				static_cast<std::uint8_t>((k_[2]) & 0xFF),
				static_cast<std::uint8_t>((k_[2] >> 8) & 0xFF),
				static_cast<std::uint8_t>((k_[2] >> 16) & 0xFF),
				static_cast<std::uint8_t>((k_[2] >> 24) & 0xFF),
				static_cast<std::uint8_t>((k_[3]) & 0xFF),
				static_cast<std::uint8_t>((k_[3] >> 8) & 0xFF),
				static_cast<std::uint8_t>((k_[3] >> 16) & 0xFF),
				static_cast<std::uint8_t>((k_[3] >> 24) & 0xFF)
				}};
		}
		void process_block() {
			sprout::array<std::uint32_t, 4> x = sprout::md5_detail::round_all(k_, block_);
			k_[0] += x[0];
			k_[1] += x[1];
			k_[2] += x[2];
			k_[3] += x[3];
			block_.assign(0);
		}
		template<typename Iterator>
		void process_block_impl(Iterator first, Iterator last) {
			for(; first != last; ++first) {
				process_byte(*first);
			}
		}
	public:
		SPROUT_CONSTEXPR md5()
			: k_{{0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476}}
			, block_{{}}
			, bit_count_()
		{}
		void reset() {
			k_[0] = 0x67452301;
			k_[1] = 0xEFCDAB89;
			k_[2] = 0x98BADCFE;
			k_[3] = 0x10325476;
			block_.assign(0);
			bit_count_ = 0;
		}

		SPROUT_CONSTEXPR md5 const process_bit(bool bit) const {
			return process_bit_impl(
				bit,
				static_cast<std::size_t>(bit_count_ % (64 * 8) / 32),
				static_cast<std::size_t>(bit_count_ % 32)
				);
		}
		SPROUT_CONSTEXPR md5 const process_bits(std::uint8_t bits, std::size_t bit_count) {
			return process_bits_impl(bits, bit_count);
		}
		SPROUT_CONSTEXPR md5 const process_byte(std::uint8_t byte) const {
			return bit_count_ % 8 == 0 ? process_byte_impl(
					byte,
					static_cast<std::size_t>(bit_count_ % (64 * 8) / 32),
					static_cast<std::size_t>(bit_count_ % 32)
					)
				: process_bit(((byte >> 7) & 1) != 0)
					.process_bit(((byte >> 6) & 1) != 0)
					.process_bit(((byte >> 5) & 1) != 0)
					.process_bit(((byte >> 4) & 1) != 0)
					.process_bit(((byte >> 3) & 1) != 0)
					.process_bit(((byte >> 2) & 1) != 0)
					.process_bit(((byte >> 1) & 1) != 0)
					.process_bit((byte & 1) != 0)
				;
		}
		template<typename Iterator>
		SPROUT_CONSTEXPR md5 const process_block(Iterator bytes_begin, Iterator bytes_end) const {
			return process_block_impl(
				sprout::make_bytes_iterator(bytes_begin),
				sprout::make_bytes_iterator(bytes_end)
				);
		}
		template<typename Iterator>
		SPROUT_CONSTEXPR md5 const process_bytes(Iterator buffer, std::size_t byte_count) const {
			return process_block(buffer, sprout::next(buffer, byte_count));
		}
		template<typename Range>
		SPROUT_CONSTEXPR md5 const process_range(Range const& bytes_range) const {
			return process_block(sprout::begin(bytes_range), sprout::end(bytes_range));
		}

		void process_bit(bool bit) {
			std::size_t index = static_cast<std::size_t>(bit_count_ % (64 * 8) / 32);
			std::size_t offset = static_cast<std::size_t>(bit_count_ % 32);
			block_[index] |= static_cast<std::uint32_t>(bit) << (offset / 8 * 8 + (7 - offset % 8));
			if (++bit_count_ % 512 == 0) {
				process_block();
			}
		}
		void process_bits(std::uint8_t bits, std::size_t bit_count) {
			while (bit_count--) {
				process_bit(((bits >> bit_count) & 1) != 0);
			}
		}
		void process_byte(std::uint8_t byte) {
			process_bits(byte, 8);
		}
		template<typename Iterator>
		void process_block(Iterator bytes_begin, Iterator bytes_end) {
			process_block_impl(
				sprout::make_bytes_iterator(bytes_begin),
				sprout::make_bytes_iterator(bytes_end)
				);
		}
		template<typename Iterator>
		void process_bytes(Iterator buffer, std::size_t byte_count) {
			process_block(buffer, sprout::next(buffer, byte_count));
		}
		template<typename Range>
		void process_range(Range const& bytes_range) {
			process_block(sprout::begin(bytes_range), sprout::end(bytes_range));
		}

		SPROUT_CONSTEXPR value_type checksum() const {
			return process_bit(true).process_padding(pad_size()).process_length(bit_count_).make_value();
		}
		SPROUT_CONSTEXPR value_type operator()() const {
			return checksum();
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CHECKSUM_MD5_HPP
