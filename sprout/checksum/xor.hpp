#ifndef SPROUT_CHECKSUM_XOR_HPP
#define SPROUT_CHECKSUM_XOR_HPP

#include <cstddef>
#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/bytes_iterator.hpp>
#include <sprout/numeric/accumulate.hpp>
#include <sprout/functional/polymorphic/bit_xor.hpp>

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
		template<typename Iterator>
		SPROUT_CONSTEXPR sum_type calc_sum(Iterator first, Iterator last) const {
			return sprout::accumulate(
				sprout::make_bytes_iterator(first),
				sprout::make_bytes_iterator(last),
				sum_,
				sprout::bit_xor_
				);
		}
	public:
		SPROUT_CONSTEXPR xor8(xor8 const&) = default;
		explicit SPROUT_CONSTEXPR xor8(sum_type sum)
			: sum_(sum)
		{}
		void reset(sum_type new_sum = 0) {
			sum_ = new_sum;
		}

		SPROUT_CONSTEXPR xor8 const process_byte(std::uint8_t byte) const {
			return xor8(sum_ ^ byte);
		}
		template<typename Iterator>
		SPROUT_CONSTEXPR xor8 const process_block(Iterator bytes_begin, Iterator bytes_end) const {
			return xor8(calc_sum(bytes_begin, bytes_end));
		}
		template<typename Iterator>
		SPROUT_CONSTEXPR xor8 const process_bytes(Iterator buffer, std::size_t byte_count) const {
			return process_block(buffer, sprout::next(buffer, byte_count));
		}
		template<typename Range>
		SPROUT_CONSTEXPR xor8 const process_range(Range const& bytes_range) const {
			return process_block(sprout::begin(bytes_range), sprout::end(bytes_range));
		}

		void process_byte(std::uint8_t byte) {
			sum_ ^= byte;
		}
		template<typename Iterator>
		void process_block(Iterator bytes_begin, Iterator bytes_end) {
			sum_ = calc_sum(bytes_begin, bytes_end);
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
			return static_cast<value_type>(sum_ & 0xFF);
		}
		SPROUT_CONSTEXPR value_type operator()() const {
			return checksum();
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CHECKSUM_XOR_HPP
