/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_BITSET_BITSET_HPP
#define SPROUT_BITSET_BITSET_HPP

#include <climits>
#include <string>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/assert.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/detail/sizeof.hpp>
#include <sprout/detail/char_literal.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/iterator/index_iterator.hpp>
#include <sprout/functional/hash.hpp>
#include <sprout/algorithm/all_of.hpp>
#include <sprout/algorithm/any_of.hpp>
#include <sprout/algorithm/find_if.hpp>
#include <sprout/algorithm/equal.hpp>
#include <sprout/algorithm/fixed/transform.hpp>
#include <sprout/algorithm/fixed/fill.hpp>
#include <sprout/algorithm/cxx14/copy.hpp>
#include <sprout/algorithm/cxx14/move.hpp>
#include <sprout/algorithm/cxx14/fill.hpp>
#include <sprout/numeric/accumulate.hpp>
#include <sprout/operation/fixed/set.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/bit/operation.hpp>
#include <sprout/math/comparisons.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		struct base_bitset_from_words_construct_tag {};

		template<std::size_t N>
		class base_bitset {
		public:
			typedef unsigned long word_type;
			typedef word_type value_type;
			typedef sprout::index_iterator<base_bitset&, true> iterator;
			typedef sprout::index_iterator<base_bitset const&, true> const_iterator;
			typedef value_type& reference;
			typedef value_type const& const_reference;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			SPROUT_STATIC_CONSTEXPR std::size_t static_size = N;
		public:
			struct are_all_pred {
			public:
				SPROUT_CONSTEXPR bool
				operator()(word_type t) const SPROUT_NOEXCEPT {
					return t == ~static_cast<word_type>(0);
				}
			};
			struct is_any_pred {
			public:
				SPROUT_CONSTEXPR bool
				operator()(word_type t) const SPROUT_NOEXCEPT {
					return t != static_cast<word_type>(0);
				}
			};
			struct to_ulong_pred {
			public:
				SPROUT_CONSTEXPR bool
				operator()(word_type t) const SPROUT_NOEXCEPT {
					return t != 0;
				}
			};
			struct count_op {
			public:
				SPROUT_CONSTEXPR size_type
				operator()(size_type lhs, size_type rhs) const SPROUT_NOEXCEPT {
					return lhs + sprout::popcount(rhs);
				}
			};
		public:
			static SPROUT_CONSTEXPR size_type
			whichword(size_type pos) SPROUT_NOEXCEPT {
				return pos / (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value);
			}
			static SPROUT_CONSTEXPR size_type
			whichbyte(size_type pos) SPROUT_NOEXCEPT {
				return (pos % (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value)) / CHAR_BIT;
			}
			static SPROUT_CONSTEXPR size_type
			whichbit(size_type pos) SPROUT_NOEXCEPT {
				return pos % (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value);
			}
			static SPROUT_CONSTEXPR word_type
			maskbit(size_type pos) SPROUT_NOEXCEPT {
				return (static_cast<word_type>(1)) << whichbit(pos);
			}
		private:
			word_type w_[N];
		private:
			SPROUT_CONSTEXPR size_type
			find_first_impl(
				size_type not_found, const_iterator first, const_iterator last,
				size_type i = 0
				) const SPROUT_NOEXCEPT
			{
				return first == last ? not_found
					: *first != static_cast<word_type>(0)
						? i * (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) + sprout::ctz(*first)
					: find_first_impl(not_found, first + 1, last, i + 1)
					;
			}
			SPROUT_CONSTEXPR size_type
			find_next_impl_2(
				size_type not_found, const_iterator first, const_iterator last,
				size_type i
				) const SPROUT_NOEXCEPT
			{
				return first == last ? not_found
					: *first != static_cast<word_type>(0)
						? i * (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) + sprout::ctz(*first)
					: find_next_impl_2(not_found, first + 1, last)
					;
			}
			SPROUT_CONSTEXPR size_type
			find_next_impl_1(size_type not_found, size_type i, word_type thisword) const SPROUT_NOEXCEPT {
				return thisword != static_cast<word_type>(0)
					? i * (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) + sprout::ctz(thisword)
					: find_next_impl_2(not_found, begin() + (i + 1), end(), i + 1)
					;
			}
			SPROUT_CONSTEXPR size_type
			find_next_impl(size_type prev, size_type not_found, size_type i) const SPROUT_NOEXCEPT {
				return find_next_impl_1(not_found, i, w_[i] & ~static_cast<word_type>(0) << whichbit(prev));
			}
			template<sprout::index_t... Indexes>
			SPROUT_CONSTEXPR base_bitset<N>
			do_left_shift_impl_2(
				size_type wshift, size_type offset, size_type sub_offset,
				sprout::index_tuple<Indexes...>
				) const SPROUT_NOEXCEPT
			{
				return base_bitset(
					sprout::detail::base_bitset_from_words_construct_tag(),
					(sprout::math::greater(Indexes, wshift)
							? (w_[Indexes - wshift] << offset) | (w_[Indexes - wshift - 1] >> sub_offset)
						: Indexes == wshift ? w_[0] << offset
						: static_cast<word_type>(0)
						)...
					);
			}
			template<sprout::index_t... Indexes>
			SPROUT_CONSTEXPR base_bitset<N>
			do_left_shift_impl_1(
				size_type wshift, size_type,
				sprout::index_tuple<Indexes...>
				) const SPROUT_NOEXCEPT
			{
				return base_bitset(
					sprout::detail::base_bitset_from_words_construct_tag(),
					(sprout::math::greater_equal(Indexes, wshift) ? w_[Indexes - wshift]
						: static_cast<word_type>(0)
						)...
					);
			}
			SPROUT_CONSTEXPR base_bitset<N>
			do_left_shift_impl(size_type wshift, size_type offset) const SPROUT_NOEXCEPT {
				return offset == 0
					? do_left_shift_impl_1(
						wshift, offset,
						sprout::make_index_tuple<N>::make()
						)
					: do_left_shift_impl_2(
						wshift, offset, (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) - offset,
						sprout::make_index_tuple<N>::make()
						)
					;
			}
			template<sprout::index_t... Indexes>
			SPROUT_CONSTEXPR base_bitset<N>
			do_right_shift_impl_2(
				size_type wshift, size_type offset, size_type limit, size_type sub_offset,
				sprout::index_tuple<Indexes...>
				) const SPROUT_NOEXCEPT
			{
				return base_bitset(
					sprout::detail::base_bitset_from_words_construct_tag(),
					(sprout::math::less(Indexes, limit)
							? (w_[Indexes + wshift] >> offset) | (w_[Indexes + wshift + 1] << sub_offset)
						: Indexes == limit ? w_[N-1] >> offset
						: static_cast<word_type>(0)
						)...
					);
			}
			template<sprout::index_t... Indexes>
			SPROUT_CONSTEXPR base_bitset<N>
			do_right_shift_impl_1(
				size_type wshift, size_type, size_type limit,
				sprout::index_tuple<Indexes...>
				) const SPROUT_NOEXCEPT
			{
				return base_bitset(
					sprout::detail::base_bitset_from_words_construct_tag(),
					(sprout::math::less_equal(Indexes, limit) ? w_[Indexes + wshift]
						: static_cast<word_type>(0)
						)...
					)
					;
			}
			SPROUT_CONSTEXPR base_bitset<N>
			do_right_shift_impl(size_type wshift, size_type offset, size_type limit) const SPROUT_NOEXCEPT {
				return offset == 0
					? do_right_shift_impl_1(
						wshift, offset, limit,
						sprout::make_index_tuple<N>::make()
						)
					: do_right_shift_impl_2(
						wshift, offset, limit, (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) - offset,
						sprout::make_index_tuple<N>::make()
						)
					;
			}
		public:
			SPROUT_CONSTEXPR base_bitset() SPROUT_NOEXCEPT
				: w_()
			{}
			base_bitset(base_bitset<N> const&) = default;
			SPROUT_CONSTEXPR base_bitset(unsigned long long val) SPROUT_NOEXCEPT
				: w_{word_type(val), word_type(val >> (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value))}
			{}
			template<typename... Words>
			SPROUT_CONSTEXPR base_bitset(sprout::detail::base_bitset_from_words_construct_tag, Words... words)
				: w_{words...}
			{}
			SPROUT_CXX14_CONSTEXPR base_bitset<N>& operator=(base_bitset<N> const& rhs) {
				sprout::copy(rhs.w_ + 0, rhs.w_ + N, w_ + 0);
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR base_bitset<N>& operator=(base_bitset<N>&& rhs) {
				sprout::move(rhs.w_ + 0, rhs.w_ + N, w_ + 0);
				return *this;
			}

			SPROUT_CXX14_CONSTEXPR void
			setword(size_type pos, word_type word) SPROUT_NOEXCEPT {
				w_[whichword(pos)] = word;
			}
			SPROUT_CONSTEXPR base_bitset<N>
			setword(size_type pos, word_type word) const SPROUT_NOEXCEPT {
				return sprout::fixed::set(*this, whichword(pos), word);
			}
			SPROUT_CONSTEXPR base_bitset<N>
			hiword(word_type word) const SPROUT_NOEXCEPT {
				return sprout::fixed::set(*this, N - 1, word);
			}

			SPROUT_CXX14_CONSTEXPR word_type&
			getword(size_type pos) SPROUT_NOEXCEPT {
				return w_[whichword(pos)];
			}
			SPROUT_CONSTEXPR word_type
			getword(size_type pos) const SPROUT_NOEXCEPT {
				return w_[whichword(pos)];
			}
			SPROUT_CONSTEXPR word_type const*
			getdata() const SPROUT_NOEXCEPT {
				return w_;
			}
			SPROUT_CXX14_CONSTEXPR word_type&
			hiword() SPROUT_NOEXCEPT {
				return w_[N - 1];
			}
			SPROUT_CONSTEXPR word_type
			hiword() const SPROUT_NOEXCEPT {
				return w_[N - 1];
			}

			SPROUT_CXX14_CONSTEXPR void
			do_and(base_bitset<N> const& x) SPROUT_NOEXCEPT {
				for (size_type i = 0; i < N; i++) {
					w_[i] &= x.w_[i];
				}
			}
			SPROUT_CONSTEXPR base_bitset<N>
			do_and(base_bitset<N> const& x) const SPROUT_NOEXCEPT {
				return sprout::fixed::transform(
					begin(), end(), x.begin(), *this, NS_SSCRISK_CEL_OR_SPROUT::bit_and<word_type>()
					);
			}
			SPROUT_CXX14_CONSTEXPR void
			do_or(base_bitset<N> const& x) SPROUT_NOEXCEPT {
				for (size_type i = 0; i < N; i++) {
					w_[i] |= x.w_[i];
				}
			}
			SPROUT_CONSTEXPR base_bitset<N>
			do_or(base_bitset<N> const& x) const SPROUT_NOEXCEPT {
				return sprout::fixed::transform(
					begin(), end(), x.begin(), *this, NS_SSCRISK_CEL_OR_SPROUT::bit_or<word_type>()
					);
			}
			SPROUT_CXX14_CONSTEXPR void
			do_xor(base_bitset<N> const& x) SPROUT_NOEXCEPT {
				for (size_type i = 0; i < N; i++) {
					w_[i] ^= x.w_[i];
				}
			}
			SPROUT_CONSTEXPR base_bitset<N>
			do_xor(base_bitset<N> const& x) const SPROUT_NOEXCEPT {
				return sprout::fixed::transform(
					begin(), end(), x.begin(), *this, NS_SSCRISK_CEL_OR_SPROUT::bit_xor<word_type>()
					);
			}
			SPROUT_CXX14_CONSTEXPR void
			do_left_shift(size_type shift) SPROUT_NOEXCEPT {
				if (shift != 0) {
					size_type const wshift = shift / (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value);
					size_type const offset = shift % (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value);
					if (offset == 0) {
						for (size_type n = N - 1; n >= wshift; --n) {
							w_[n] = w_[n - wshift];
						}
					} else {
						size_type const sub_offset = (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) - offset;
						for (size_type n = N - 1; n > wshift; --n) {
							w_[n] = (w_[n - wshift] << offset) | (w_[n - wshift - 1] >> sub_offset);
						}
						w_[wshift] = w_[0] << offset;
					}
					sprout::fill(w_ + 0, w_ + wshift, static_cast<word_type>(0));
				}
			}
			SPROUT_CONSTEXPR base_bitset<N>
			do_left_shift(size_type shift) const SPROUT_NOEXCEPT {
				return shift != 0 ? do_left_shift_impl(
						shift / (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value),
						shift % (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value)
						)
					: *this
					;
			}
			SPROUT_CXX14_CONSTEXPR void
			do_right_shift(size_type shift) SPROUT_NOEXCEPT {
				if (shift != 0) {
					size_type const wshift = shift / (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value);
					size_type const offset = shift % (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value);
					size_type const limit = N - wshift - 1;
					if (offset == 0) {
						for (size_type n = 0; n <= limit; ++n) {
							w_[n] = w_[n + wshift];
						}
					} else {
						size_type const sub_offset = (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) - offset;
						for (size_type n = 0; n < limit; ++n) {
							w_[n] = (w_[n + wshift] >> offset) | (w_[n + wshift + 1] << sub_offset);
						}
						w_[limit] = w_[N-1] >> offset;
					}
					sprout::fill(w_ + limit + 1, w_ + N, static_cast<word_type>(0));
				}
			}
			SPROUT_CONSTEXPR base_bitset<N>
			do_right_shift(size_type shift) const SPROUT_NOEXCEPT {
				return shift != 0 ? do_right_shift_impl(
						shift / (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value),
						shift % (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value),
						N - shift / (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) - 1
						)
					: *this
					;
			}
			SPROUT_CXX14_CONSTEXPR void
			do_flip() SPROUT_NOEXCEPT {
				for (size_type i = 0; i < N; i++) {
					w_[i] = ~w_[i];
				}
			}
			SPROUT_CONSTEXPR base_bitset<N>
			do_flip() const SPROUT_NOEXCEPT {
				return sprout::fixed::transform(
					begin(), end(), *this, NS_SSCRISK_CEL_OR_SPROUT::bit_not<word_type>()
					);
			}
			SPROUT_CONSTEXPR base_bitset<N>
			do_set() const SPROUT_NOEXCEPT {
				return sprout::fixed::fill(*this, ~static_cast<word_type>(0));
			}
			SPROUT_CXX14_CONSTEXPR void
			do_set() SPROUT_NOEXCEPT {
				for (size_type i = 0; i < N; i++) {
					w_[i] = ~static_cast<word_type>(0);
				}
			}
			SPROUT_CONSTEXPR base_bitset<N>
			do_reset() const SPROUT_NOEXCEPT {
				return base_bitset();
			}
			SPROUT_CXX14_CONSTEXPR void
			do_reset() SPROUT_NOEXCEPT {
				sprout::fill(w_ + 0, w_ + N, static_cast<word_type>(0));
			}

			SPROUT_CONSTEXPR bool
			is_equal(base_bitset<N> const& x) const SPROUT_NOEXCEPT {
				return sprout::equal(begin(), end(), x.begin());
			}
			template<size_type N2>
			SPROUT_CONSTEXPR bool
			are_all() const SPROUT_NOEXCEPT {
				return sprout::all_of(begin(), end() - 1, are_all_pred())
					&& hiword() == (~static_cast<word_type>(0) >> (N * (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) - N2))
					;
			}
			SPROUT_CONSTEXPR bool
			is_any() const SPROUT_NOEXCEPT {
				return sprout::any_of(begin(), end(), is_any_pred());
			}
			SPROUT_CONSTEXPR size_type
			do_count() const SPROUT_NOEXCEPT {
				return sprout::accumulate(begin(), end(), static_cast<size_type>(0), count_op());
			}

			SPROUT_CONSTEXPR unsigned long
			do_to_ulong() const {
				return sprout::find_if(begin() + 1, end(), to_ulong_pred()) != end()
					? throw std::overflow_error("base_bitset::do_to_ulong")
					: w_[0]
					;
			}
			SPROUT_CONSTEXPR unsigned long long
			do_to_ullong() const {
				return sprout::find_if(
					sprout::detail::sizeof_<unsigned long long>::value > sprout::detail::sizeof_<unsigned long>::value ? begin() + 2
						: begin() + 1
						,
					end(),
					to_ulong_pred()
					) != end()
					? throw std::overflow_error("base_bitset::to_ullong")
					: sprout::detail::sizeof_<unsigned long long>::value > sprout::detail::sizeof_<unsigned long>::value
						? w_[0] + (static_cast<unsigned long long>(w_[1]) << (CHAR_BIT * sizeof(unsigned long)))
					: w_[0]
					;
			}

			SPROUT_CONSTEXPR size_type
			find_first(size_type not_found) const SPROUT_NOEXCEPT {
				return find_first_impl(not_found, begin(), end());
			}
			SPROUT_CONSTEXPR size_type
			find_next(size_type prev, size_type not_found) const SPROUT_NOEXCEPT {
				return prev + 1 >= N * (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) ? not_found
					: find_next_impl(prev + 1, not_found, whichword(prev + 1));
					;
			}

			SPROUT_CONSTEXPR size_type do_to_hash() const {
				return sprout::hash_range(*this);
			}

			SPROUT_CXX14_CONSTEXPR word_type& operator[](size_type i) {
				return w_[i];
			}
			SPROUT_CONSTEXPR word_type const& operator[](size_type i) const {
				return w_[i];
			}
			SPROUT_CXX14_CONSTEXPR iterator begin() SPROUT_NOEXCEPT {
				return iterator(*this, 0);
			}
			SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT {
				return const_iterator(*this, 0);
			}
			SPROUT_CXX14_CONSTEXPR iterator end() SPROUT_NOEXCEPT {
				return iterator(*this, N);
			}
			SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
				return const_iterator(*this, N);
			}
		};

		template<>
		class base_bitset<1> {
		public:
			typedef unsigned long word_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
		private:
			word_type w_;
		public:
			static SPROUT_CONSTEXPR size_type
			whichword(size_type pos) SPROUT_NOEXCEPT {
				return pos / (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value);
			}
			static SPROUT_CONSTEXPR size_type
			whichbyte(size_type pos) SPROUT_NOEXCEPT {
				return (pos % (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value)) / CHAR_BIT;
			}
			static SPROUT_CONSTEXPR size_type
			whichbit(size_type pos) SPROUT_NOEXCEPT {
				return pos % (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value);
			}
			static SPROUT_CONSTEXPR word_type
			maskbit(size_type pos) SPROUT_NOEXCEPT {
				return (static_cast<word_type>(1)) << whichbit(pos);
			}
		private:
			SPROUT_CONSTEXPR size_type
			find_next_impl(size_type prev, size_type not_found, word_type x) const SPROUT_NOEXCEPT {
				return x != 0 ? sprout::ctz(x) + prev
					: not_found
					;
			}
		public:
			SPROUT_CONSTEXPR base_bitset() SPROUT_NOEXCEPT
				: w_(0)
			{}
			base_bitset(base_bitset<1> const&) = default;
			SPROUT_CONSTEXPR base_bitset(unsigned long long val) SPROUT_NOEXCEPT
				: w_(static_cast<word_type>(val))
			{}
			SPROUT_CONSTEXPR base_bitset(sprout::detail::base_bitset_from_words_construct_tag, word_type word)
				: w_(word)
			{}
			SPROUT_CXX14_CONSTEXPR base_bitset<1>& operator=(base_bitset<1> const& rhs) {
				w_ = rhs.w_;
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR base_bitset<1>& operator=(base_bitset<1>&& rhs) {
				w_ = sprout::move(rhs.w_);
				return *this;
			}

			SPROUT_CXX14_CONSTEXPR void
			setword(size_type, word_type word) SPROUT_NOEXCEPT {
				w_ = word;
			}
			SPROUT_CONSTEXPR base_bitset<1>
			setword(size_type, word_type word) const SPROUT_NOEXCEPT {
				return base_bitset(sprout::detail::base_bitset_from_words_construct_tag(), word);
			}
			SPROUT_CONSTEXPR base_bitset<1>
			hiword(word_type word) const SPROUT_NOEXCEPT {
				return base_bitset(sprout::detail::base_bitset_from_words_construct_tag(), word);
			}

			SPROUT_CXX14_CONSTEXPR word_type&
			getword(size_type) SPROUT_NOEXCEPT {
				return w_;
			}
			SPROUT_CONSTEXPR word_type
			getword(size_type) const SPROUT_NOEXCEPT {
				return w_;
			}
			SPROUT_CONSTEXPR word_type const*
			getdata() const SPROUT_NOEXCEPT {
				return &w_;
			}
			SPROUT_CXX14_CONSTEXPR word_type&
			hiword() SPROUT_NOEXCEPT {
				return w_;
			}
			SPROUT_CONSTEXPR word_type
			hiword() const SPROUT_NOEXCEPT {
				return w_;
			}

			SPROUT_CXX14_CONSTEXPR void
			do_and(base_bitset<1> const& x) SPROUT_NOEXCEPT {
				w_ &= x.w_;
			}
			SPROUT_CONSTEXPR base_bitset<1>
			do_and(base_bitset<1> const& x) const SPROUT_NOEXCEPT {
				return base_bitset<1>(w_ & x.w_);
			}
			SPROUT_CXX14_CONSTEXPR void
			do_or(base_bitset<1> const& x) SPROUT_NOEXCEPT {
				w_ |= x.w_;
			}
			SPROUT_CONSTEXPR base_bitset<1>
			do_or(base_bitset<1> const& x) const SPROUT_NOEXCEPT {
				return base_bitset<1>(w_ | x.w_);
			}
			SPROUT_CXX14_CONSTEXPR void
			do_xor(base_bitset<1> const& x) SPROUT_NOEXCEPT {
				w_ ^= x.w_;
			}
			SPROUT_CONSTEXPR base_bitset<1>
			do_xor(base_bitset<1> const& x) const SPROUT_NOEXCEPT {
				return base_bitset<1>(w_ ^ x.w_);
			}
			SPROUT_CXX14_CONSTEXPR void
			do_left_shift(size_type shift) SPROUT_NOEXCEPT {
				w_ <<= shift;
			}
			SPROUT_CONSTEXPR base_bitset<1>
			do_left_shift(base_bitset<1> const& x) const SPROUT_NOEXCEPT {
				return base_bitset<1>(w_ << x.w_);
			}
			SPROUT_CXX14_CONSTEXPR void
			do_right_shift(size_type shift) SPROUT_NOEXCEPT {
				w_ >>= shift;
			}
			SPROUT_CONSTEXPR base_bitset<1>
			do_right_shift(base_bitset<1> const& x) const SPROUT_NOEXCEPT {
				return base_bitset<1>(w_ >> x.w_);
			}
			SPROUT_CXX14_CONSTEXPR void
			do_flip() SPROUT_NOEXCEPT {
				w_ = ~w_;
			}
			SPROUT_CONSTEXPR base_bitset<1>
			do_flip() const SPROUT_NOEXCEPT {
				return base_bitset<1>(~w_);
			}
			SPROUT_CXX14_CONSTEXPR void
			do_set() SPROUT_NOEXCEPT {
				w_ = ~static_cast<word_type>(0);
			}
			SPROUT_CONSTEXPR base_bitset<1>
			do_set() const SPROUT_NOEXCEPT {
				return base_bitset<1>(~static_cast<word_type>(0));
			}
			SPROUT_CXX14_CONSTEXPR void
			do_reset() SPROUT_NOEXCEPT {
				w_ = 0;
			}
			SPROUT_CONSTEXPR base_bitset<1>
			do_reset() const SPROUT_NOEXCEPT {
				return base_bitset<1>(0);
			}

			SPROUT_CONSTEXPR bool
			is_equal(base_bitset<1> const& x) const SPROUT_NOEXCEPT {
				return w_ == x.w_;
			}
			template<size_type N2>
			SPROUT_CONSTEXPR bool
			are_all() const SPROUT_NOEXCEPT {
				return w_ == ~static_cast<word_type>(0) >> ((CHAR_BIT * sizeof(unsigned long)) - N2);
			}
			SPROUT_CONSTEXPR bool
			is_any() const SPROUT_NOEXCEPT {
				return w_ != 0;
			}
			SPROUT_CONSTEXPR size_type
			do_count() const SPROUT_NOEXCEPT {
				return sprout::popcount(w_);
			}

			SPROUT_CONSTEXPR unsigned long
			do_to_ulong() const SPROUT_NOEXCEPT {
				return w_;
			}
			SPROUT_CONSTEXPR unsigned long long
			do_to_ullong() const SPROUT_NOEXCEPT {
				return w_;
			}

			SPROUT_CONSTEXPR size_type
			find_first(size_type not_found) const SPROUT_NOEXCEPT {
				return w_ != 0 ? sprout::ctz(w_)
					: not_found
					;
			}
			SPROUT_CONSTEXPR size_type
			find_next(size_type prev, size_type not_found) const SPROUT_NOEXCEPT {
				return prev + 1 >= static_cast<size_type>(CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) ? not_found
					: find_next_impl(prev + 1, not_found, w_ >> (prev + 1))
					;
			}

			SPROUT_CONSTEXPR size_type do_to_hash() const {
				return sprout::to_hash(w_);
			}
		};

		template<>
		class base_bitset<0> {
		public:
			typedef unsigned long word_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
		public:
			static SPROUT_CONSTEXPR size_type
			whichword(size_type pos) SPROUT_NOEXCEPT {
				return pos / (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value);
			}

			static SPROUT_CONSTEXPR size_type
			whichbyte(size_type pos) SPROUT_NOEXCEPT {
				return (pos % (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value)) / CHAR_BIT;
			}

			static SPROUT_CONSTEXPR size_type
			whichbit(size_type pos) SPROUT_NOEXCEPT {
				return pos % (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value);
			}

			static SPROUT_CONSTEXPR word_type
			maskbit(size_type pos) SPROUT_NOEXCEPT {
				return (static_cast<word_type>(1)) << whichbit(pos);
			}
		public:
			SPROUT_CONSTEXPR base_bitset() SPROUT_NOEXCEPT {}
			base_bitset(base_bitset<0> const&) = default;
			SPROUT_CONSTEXPR base_bitset(unsigned long long) SPROUT_NOEXCEPT {}
			SPROUT_CONSTEXPR base_bitset(sprout::detail::base_bitset_from_words_construct_tag) {}
			SPROUT_CXX14_CONSTEXPR base_bitset<0>& operator=(base_bitset<0> const&) SPROUT_NOEXCEPT {
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR base_bitset<0>& operator=(base_bitset<0>&&) SPROUT_NOEXCEPT {
				return *this;
			}

			SPROUT_CXX14_CONSTEXPR void
			setword(size_type, word_type) SPROUT_NOEXCEPT {}
			SPROUT_CONSTEXPR base_bitset<0>
			setword(size_type, word_type) const SPROUT_NOEXCEPT {
				return *this;
			}
			SPROUT_CONSTEXPR base_bitset<0>
			hiword(word_type) const SPROUT_NOEXCEPT {
				return *this;
			}

			SPROUT_CXX14_CONSTEXPR word_type
			getword(size_type, bool c = false) SPROUT_NOEXCEPT {
				return SPROUT_ASSERT_MSG(!c, "base_bitset::getword"),
					0
					;
			}
			SPROUT_CONSTEXPR word_type
			getword(size_type) const SPROUT_NOEXCEPT {
				return 0;
			}
			SPROUT_CONSTEXPR word_type
			hiword() const SPROUT_NOEXCEPT {
				return 0;
			}

			SPROUT_CXX14_CONSTEXPR void
			do_and(base_bitset<0> const&) SPROUT_NOEXCEPT {}
			SPROUT_CONSTEXPR base_bitset<0>
			do_and(base_bitset<0> const&) const SPROUT_NOEXCEPT {
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR void
			do_or(base_bitset<0> const&) SPROUT_NOEXCEPT {}
			SPROUT_CONSTEXPR base_bitset<0>
			do_or(base_bitset<0> const&) const SPROUT_NOEXCEPT {
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR void
			do_xor(base_bitset<0> const&) SPROUT_NOEXCEPT {}
			SPROUT_CONSTEXPR base_bitset<0>
			do_xor(base_bitset<0> const&) const SPROUT_NOEXCEPT {
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR void
			do_left_shift(size_type) SPROUT_NOEXCEPT {}
			SPROUT_CONSTEXPR base_bitset<0>
			do_left_shift(base_bitset<0> const&) const SPROUT_NOEXCEPT {
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR void
			do_right_shift(size_type) SPROUT_NOEXCEPT {}
			SPROUT_CONSTEXPR base_bitset<0>
			do_right_shift(base_bitset<0> const&) const SPROUT_NOEXCEPT {
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR void
			do_flip() SPROUT_NOEXCEPT {}
			SPROUT_CONSTEXPR base_bitset<0>
			do_flip() const SPROUT_NOEXCEPT {
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR void
			do_set() SPROUT_NOEXCEPT {}
			SPROUT_CONSTEXPR base_bitset<0>
			do_set() const SPROUT_NOEXCEPT {
				return base_bitset<0>();
			}
			SPROUT_CXX14_CONSTEXPR void
			do_reset() SPROUT_NOEXCEPT {}
			SPROUT_CONSTEXPR base_bitset<0>
			do_reset() const SPROUT_NOEXCEPT {
				return base_bitset<0>();
			}

			SPROUT_CONSTEXPR bool
			is_equal(base_bitset<0> const&) const SPROUT_NOEXCEPT {
				return true;
			}
			template<size_type N2>
			SPROUT_CONSTEXPR bool
			are_all() const SPROUT_NOEXCEPT {
				return true;
			}
			SPROUT_CONSTEXPR bool
			is_any() const SPROUT_NOEXCEPT {
				return false;
			}
			SPROUT_CONSTEXPR size_type
			do_count() const SPROUT_NOEXCEPT {
				return 0;
			}

			SPROUT_CONSTEXPR unsigned long
			do_to_ulong() const SPROUT_NOEXCEPT {
				return 0;
			}
			SPROUT_CONSTEXPR unsigned long long
			do_to_ullong() const SPROUT_NOEXCEPT {
				return 0;
			}

			SPROUT_CONSTEXPR size_type
			find_first(size_type) const SPROUT_NOEXCEPT {
				return 0;
			}
			SPROUT_CONSTEXPR size_type
			find_next(size_type, size_type) const SPROUT_NOEXCEPT {
				return 0;
			}

			SPROUT_CONSTEXPR size_type do_to_hash() const {
				return 0;
			}
		};

		template<std::size_t Extrabits>
		struct sanitize {
		public:
			typedef unsigned long word_type;
		public:
			static SPROUT_CXX14_CONSTEXPR void
			do_sanitize(word_type& val) SPROUT_NOEXCEPT {
				val &= ~(~static_cast<word_type>(0) << Extrabits);
			}
			static SPROUT_CONSTEXPR word_type
			do_sanitize_c(word_type val) SPROUT_NOEXCEPT {
				return val & ~(~static_cast<word_type>(0) << Extrabits);
			}
		};
		template<>
		struct sanitize<0> {
		public:
			typedef unsigned long word_type;
		public:
			static SPROUT_CXX14_CONSTEXPR void
			do_sanitize(word_type) SPROUT_NOEXCEPT {}
			static SPROUT_CONSTEXPR word_type
			do_sanitize_c(word_type val) SPROUT_NOEXCEPT {
				return val;
			}
		};

		template<std::size_t N2, bool = (N2 < (CHAR_BIT * sprout::detail::sizeof_<unsigned long long>::value))>
		struct sanitize_val {
		public:
			static SPROUT_CONSTEXPR unsigned long long
			do_sanitize_val(unsigned long long val) {
				return val;
			}
		};
		template<std::size_t N2>
		struct sanitize_val<N2, true> {
		public:
			static SPROUT_CONSTEXPR unsigned long long
			do_sanitize_val(unsigned long long val) {
				return val & ~((~static_cast<unsigned long long>(0)) << N2);
			}
		};
	}	// namespace detail

	template<std::size_t N>
	struct container_construct_traits<sprout::detail::base_bitset<N> > {
	public:
		typedef sprout::detail::base_bitset<N> copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type deep_copy(Cont&& cont) {
			return SPROUT_FORWARD(Cont, cont);
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
			return copied_type(sprout::detail::base_bitset_from_words_construct_tag(), args...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type remake(
			Cont&&,
			typename sprout::container_traits<sprout::detail::base_bitset<N> >::difference_type,
			Args&&... args
			)
		{
			return make(args...);
		}
	};

	template<std::size_t N>
	class bitset;

	template<std::size_t N>
	inline SPROUT_CONSTEXPR bitset<N>
	operator&(sprout::bitset<N> const& lhs, sprout::bitset<N> const& rhs) SPROUT_NOEXCEPT;
	template<std::size_t N>
	inline SPROUT_CONSTEXPR bitset<N>
	operator|(sprout::bitset<N> const& lhs, sprout::bitset<N> const& rhs) SPROUT_NOEXCEPT;
	template<std::size_t N>
	inline SPROUT_CONSTEXPR bitset<N>
	operator^(sprout::bitset<N> const& lhs, sprout::bitset<N> const& rhs) SPROUT_NOEXCEPT;
	template<typename Char, typename Traits, std::size_t N>
	inline SPROUT_NON_CONSTEXPR std::basic_istream<Char, Traits>&
	operator>>(std::basic_istream<Char, Traits>& lhs, sprout::bitset<N>& rhs);
	template<typename Char, typename Traits, std::size_t N>
	inline SPROUT_NON_CONSTEXPR std::basic_ostream<Char, Traits>&
	operator<<(std::basic_ostream<Char, Traits>& lhs, sprout::bitset<N> const& rhs);

	template<std::size_t N>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::bitset<N> const& v);

	//
	// bitset
	//
	template<std::size_t N>
	class bitset
		: private sprout::detail::base_bitset<
			N / (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) + (N % (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) == 0 ? 0 : 1)
		>
	{
	private:
		typedef sprout::detail::base_bitset<
			N / (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) + (N % (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value) == 0 ? 0 : 1)
		> base_type;
		typedef unsigned long word_type;
	public:
		typedef std::size_t size_type;
		typedef bool value_type;
	public:
		class reference {
			friend class bitset<N>;
		private:
			word_type* wp_;
			size_type bpos_;
		private:
			reference() SPROUT_DELETED_FUNCTION_DECL
		public:
			SPROUT_CONSTEXPR reference(bitset<N>& b, size_type pos) SPROUT_NOEXCEPT
				: wp_(&b.getword(pos))
				, bpos_(base_type::whichbit(pos))
			{}

			SPROUT_CXX14_CONSTEXPR reference&
			operator=(value_type x) SPROUT_NOEXCEPT {
				if (x) {
					*wp_ |= base_type::maskbit(bpos_);
				} else {
					*wp_ &= ~base_type::maskbit(bpos_);
				}
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR reference&
			operator=(const reference& j) SPROUT_NOEXCEPT {
				if ((*(j.wp_) & base_type::maskbit(j.bpos_))) {
					*wp_ |= base_type::maskbit(bpos_);
				} else {
					*wp_ &= ~base_type::maskbit(bpos_);
				}
				return *this;
			}

			SPROUT_CONSTEXPR value_type
			operator~() const SPROUT_NOEXCEPT {
				return (*wp_ & base_type::maskbit(bpos_)) == 0;
			}
			SPROUT_CONSTEXPR
			operator value_type() const SPROUT_NOEXCEPT {
				return (*wp_ & base_type::maskbit(bpos_)) != 0;
			}
			SPROUT_CXX14_CONSTEXPR reference&
			flip() SPROUT_NOEXCEPT {
				*wp_ ^= base_type::maskbit(bpos_);
				return *this;
			}
		};
		friend class reference;
	private:
		explicit SPROUT_CONSTEXPR bitset(base_type const& base) SPROUT_NOEXCEPT
			: base_type(base)
		{}

		SPROUT_CXX14_CONSTEXPR void
		do_sanitize() SPROUT_NOEXCEPT {
			typedef sprout::detail::sanitize<N % (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value)> sanitize_type;
			sanitize_type::do_sanitize(this->hiword());
		}
		SPROUT_CONSTEXPR bitset<N>
		do_sanitize() const SPROUT_NOEXCEPT {
			typedef sprout::detail::sanitize<N % (CHAR_BIT * sprout::detail::sizeof_<unsigned long>::value)> sanitize_type;
			return bitset(this->hiword(sanitize_type::do_sanitize_c(this->hiword())));
		}
		SPROUT_CONSTEXPR bitset<N>
		do_sanitize_c() const SPROUT_NOEXCEPT {
			return do_sanitize();
		}

		SPROUT_CXX14_CONSTEXPR bitset<N>&
		unchecked_set(size_type pos) SPROUT_NOEXCEPT {
			this->getword(pos) |= base_type::maskbit(pos);
			return *this;
		}
		SPROUT_CONSTEXPR bitset<N>
		unchecked_set(size_type pos) const SPROUT_NOEXCEPT {
			return bitset(this->setword(pos, this->getword(pos) | base_type::maskbit(pos)));
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		unchecked_set(size_type pos, int val) SPROUT_NOEXCEPT {
			if (val) {
				this->getword(pos) |= base_type::maskbit(pos);
			} else {
				this->getword(pos) &= ~base_type::maskbit(pos);
			}
			return *this;
		}
		SPROUT_CONSTEXPR bitset<N>
		unchecked_set(size_type pos, int val) const SPROUT_NOEXCEPT {
			return val ? bitset(this->setword(pos, this->getword(pos) | base_type::maskbit(pos)))
				: bitset(this->setword(pos, this->getword(pos) & ~base_type::maskbit(pos)))
				;
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		unchecked_reset(size_type pos) SPROUT_NOEXCEPT {
			this->getword(pos) &= ~base_type::maskbit(pos);
			return *this;
		}
		SPROUT_CONSTEXPR bitset<N>
		unchecked_reset(size_type pos) const SPROUT_NOEXCEPT {
			return bitset<N>(this->setword(pos, this->getword(pos) & ~base_type::maskbit(pos)));
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		unchecked_flip(size_type pos) SPROUT_NOEXCEPT {
			this->getword(pos) ^= base_type::maskbit(pos);
			return *this;
		}
		SPROUT_CONSTEXPR bitset<N>
		unchecked_flip(size_type pos) const SPROUT_NOEXCEPT {
			return bitset<N>(this->setword(pos, this->getword(pos) ^ base_type::maskbit(pos)));
		}
		SPROUT_CONSTEXPR value_type
		unchecked_test(size_type pos) const SPROUT_NOEXCEPT {
			return (this->getword(pos) & base_type::maskbit(pos)) != static_cast<word_type>(0);
		}

		template<typename Char, typename Traits>
		SPROUT_CXX14_CONSTEXPR void
		copy_from_ptr(Char const* s, size_type len, size_type pos, size_type n, Char zero, Char one) {
			reset();
			size_type const nbits = std::min(N, std::min(n, len - pos));
			for (size_type i = nbits; i > 0; --i) {
				Char const c = s[pos + nbits - i];
				if (Traits::eq(c, zero)) {
				} else if (Traits::eq(c, one)) {
					unchecked_set(i - 1);
				} else {
					throw std::invalid_argument("bitset::copy_from_ptr");
				}
			}
		}
		template<typename Char, typename Traits, typename Alloc>
		SPROUT_NON_CONSTEXPR void
		copy_from_string(
			std::basic_string<Char, Traits, Alloc> const& s,
			size_type pos, size_type n, Char zero, Char one
			)
		{
			copy_from_ptr<Char, Traits>(s.data(), s.size(), pos, n, zero, one);
		}
		template<typename Char, typename Traits, typename Alloc>
		SPROUT_NON_CONSTEXPR void
		copy_to_string(std::basic_string<Char, Traits, Alloc>& s, Char zero, Char one) const {
			s.assign(N, zero);
			for (size_type i = N; i > 0; --i) {
				if (unchecked_test(i - 1)) {
					Traits::assign(s[N - i], one);
				}
			}
		}
		template<typename Char, typename Traits, typename Alloc>
		SPROUT_NON_CONSTEXPR void
		copy_from_string(std::basic_string<Char, Traits, Alloc> const& s, size_type pos, size_type n) {
			copy_from_string(s, pos, n, SPROUT_CHAR_LITERAL('0', Char), SPROUT_CHAR_LITERAL('1', Char));
		}
		template<typename Char, typename Traits, typename Alloc>
		SPROUT_NON_CONSTEXPR void
		copy_to_string(std::basic_string<Char, Traits, Alloc>& s) const {
			copy_to_string(s, SPROUT_CHAR_LITERAL('0', Char), SPROUT_CHAR_LITERAL('1', Char));
		}

		SPROUT_CONSTEXPR size_type to_hash() const {
			return this->do_to_hash();
		}
	public:
		// 20.5.1 constructors:
		SPROUT_CONSTEXPR bitset() SPROUT_NOEXCEPT
			: base_type()
		{}
		bitset(bitset<N> const&) = default;
		SPROUT_CONSTEXPR bitset(unsigned long long val) SPROUT_NOEXCEPT
			: base_type(sprout::detail::sanitize_val<N>::do_sanitize_val(val))
		{}
		template<typename Char, typename Traits, typename Alloc>
		explicit SPROUT_NON_CONSTEXPR bitset(std::basic_string<Char, Traits, Alloc> const& s, size_type position = 0)
			: base_type()
		{
			if (position > s.size()) {
				throw std::out_of_range("bitset::bitset initial position not valid");
			}
			copy_from_string(s, position, std::basic_string<Char, Traits, Alloc>::npos, SPROUT_CHAR_LITERAL('0', Char), SPROUT_CHAR_LITERAL('1', Char));
		}
		template<typename Char, typename Traits, typename Alloc>
		SPROUT_NON_CONSTEXPR bitset(std::basic_string<Char, Traits, Alloc> const& s, size_type position, size_type n)
			: base_type()
		{
			if (position > s.size()) {
				throw std::out_of_range("bitset::bitset initial position not valid");
			}
			copy_from_string(s, position, n, SPROUT_CHAR_LITERAL('0', Char), SPROUT_CHAR_LITERAL('1', Char));
		}

		template<typename Char, typename Traits, typename Alloc>
		SPROUT_NON_CONSTEXPR bitset(
			std::basic_string<Char, Traits, Alloc> const& s, size_type position, size_type n,
			Char zero, Char one = SPROUT_CHAR_LITERAL('1', Char)
			)
			: base_type()
		{
			if (position > s.size()) {
				throw std::out_of_range("bitset::bitset initial position not valid");
			}
			copy_from_string(s, position, n, zero, one);
		}
		template<typename Char>
		explicit SPROUT_NON_CONSTEXPR bitset(
			Char const* str, typename std::basic_string<Char>::size_typeype n = std::basic_string<Char>::npos,
			Char zero = SPROUT_CHAR_LITERAL('0', Char), Char one = SPROUT_CHAR_LITERAL('1', Char)
			)
			: base_type()
		{
			if (!str) {
				throw std::out_of_range("bitset::bitset");
			}
			if (n == std::basic_string<Char>::npos) {
				n = std::char_traits<Char>::length(str);
			}
			copy_from_ptr<Char, std::char_traits<Char>>(str, n, 0, n, zero, one);
		}
		// 20.5.2 bitset operations:
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		operator=(bitset<N> const& rhs) {
			base_type::operator=(rhs);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		operator=(bitset<N>&& rhs) {
			base_type::operator=(sprout::move(rhs));
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		operator&=(bitset<N> const& rhs) SPROUT_NOEXCEPT {
			this->do_and(rhs);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		operator|=(bitset<N> const& rhs) SPROUT_NOEXCEPT {
			this->do_or(rhs);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		operator^=(bitset<N> const& rhs) SPROUT_NOEXCEPT {
			this->do_xor(rhs);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		operator<<=(size_type position) SPROUT_NOEXCEPT {
			if (position < N) {
				this->do_left_shift(position);
				this->do_sanitize();
			} else {
				this->do_reset();
			}
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		operator>>=(size_type position) SPROUT_NOEXCEPT {
			if (position < N) {
				this->do_right_shift(position);
				this->do_sanitize();
			} else {
				this->do_reset();
			}
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		set() SPROUT_NOEXCEPT {
			this->do_set();
			this->do_sanitize();
			return *this;
		}
		SPROUT_CONSTEXPR bitset<N>
		set() const SPROUT_NOEXCEPT {
			return bitset(this->do_set()).do_sanitize_c();
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		set(size_type position, value_type val = true) {
			if (position >= N) {
				throw std::out_of_range("bitset::set");
			}
			return unchecked_set(position, val);
		}
		SPROUT_CONSTEXPR bitset<N>
		set(size_type position, value_type val = true) const {
			return position >= N ? throw std::out_of_range("bitset::set")
				: unchecked_set(position, val)
				;
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		reset() SPROUT_NOEXCEPT {
			this->do_reset();
			return *this;
		}
		SPROUT_CONSTEXPR bitset<N>
		reset() const SPROUT_NOEXCEPT {
			return bitset(this->do_reset());
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		reset(size_type position) {
			if (position >= N) {
				throw std::out_of_range("bitset::reset");
			}
			return unchecked_reset(position);
		}
		SPROUT_CONSTEXPR bitset<N>
		reset(size_type position) const {
			return position >= N ? throw std::out_of_range("bitset::reset")
				: unchecked_reset(position)
				;
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		flip() SPROUT_NOEXCEPT {
			this->do_flip();
			this->do_sanitize();
			return *this;
		}
		SPROUT_CONSTEXPR bitset<N>
		flip() const SPROUT_NOEXCEPT {
			return bitset(this->do_flip()).do_sanitize_c();
		}
		SPROUT_CXX14_CONSTEXPR bitset<N>&
		flip(size_type position) {
			if (position >= N) {
				throw std::out_of_range("bitset::flip");
			}
			return unchecked_flip(position);
		}
		SPROUT_CONSTEXPR bitset<N>
		flip(size_type position) const {
			return position >= N ? throw std::out_of_range("bitset::flip")
				: unchecked_flip(position)
				;
		}
		SPROUT_CONSTEXPR bitset<N>
		operator~() const SPROUT_NOEXCEPT {
			return flip();
		}

		// element access:
		SPROUT_CXX14_CONSTEXPR reference
		operator[](size_type position) {
			return reference(*this, position);
		}
		SPROUT_CONSTEXPR value_type
		operator[](size_type position) const {
			return unchecked_test(position);
		}
		SPROUT_CONSTEXPR unsigned long
		to_ulong() const {
			return this->do_to_ulong();
		}
		SPROUT_CONSTEXPR unsigned long long
		to_ullong() const {
			return this->do_to_ullong();
		}
		template<typename Char, typename Traits, typename Alloc>
		SPROUT_NON_CONSTEXPR std::basic_string<Char, Traits, Alloc>
		to_string() const {
			std::basic_string<Char, Traits, Alloc> result;
			copy_to_string(result, SPROUT_CHAR_LITERAL('0', Char), SPROUT_CHAR_LITERAL('1', Char));
			return result;
		}
		template<typename Char, typename Traits, typename Alloc>
		SPROUT_NON_CONSTEXPR std::basic_string<Char, Traits, Alloc>
		to_string(Char zero, Char one = SPROUT_CHAR_LITERAL('1', Char)) const {
			std::basic_string<Char, Traits, Alloc> result;
			copy_to_string(result, zero, one);
			return result;
		}
		template<typename Char, typename Traits>
		SPROUT_NON_CONSTEXPR std::basic_string<Char, Traits, std::allocator<Char> >
		to_string() const {
			return to_string<Char, Traits, std::allocator<Char> >();
		}
		template<typename Char, typename Traits>
		SPROUT_NON_CONSTEXPR std::basic_string<Char, Traits, std::allocator<Char> >
		to_string(Char zero, Char one = SPROUT_CHAR_LITERAL('1', Char)) const {
			return to_string<Char, Traits, std::allocator<Char> >(zero, one);
		}
		template<typename Char>
		SPROUT_NON_CONSTEXPR std::basic_string<Char, std::char_traits<Char>, std::allocator<Char> >
		to_string() const {
			return to_string<Char, std::char_traits<Char>, std::allocator<Char> >();
		}
		template<typename Char>
		SPROUT_NON_CONSTEXPR std::basic_string<Char, std::char_traits<Char>, std::allocator<Char> >
		to_string(Char zero, Char one = SPROUT_CHAR_LITERAL('1', Char)) const {
			return to_string<Char, std::char_traits<Char>, std::allocator<Char> >(zero, one);
		}
		SPROUT_NON_CONSTEXPR std::basic_string<char, std::char_traits<char>, std::allocator<char> >
		to_string() const {
			return to_string<char, std::char_traits<char>, std::allocator<char> >();
		}
		SPROUT_NON_CONSTEXPR std::basic_string<char, std::char_traits<char>, std::allocator<char> >
		to_string(char zero, char one = '1') const {
			return to_string<char, std::char_traits<char>, std::allocator<char> >(zero, one);
		}

		SPROUT_CONSTEXPR size_type
		count() const SPROUT_NOEXCEPT {
			return this->do_count();
		}
		SPROUT_CONSTEXPR size_type
		size() const SPROUT_NOEXCEPT {
			return N;
		}
		SPROUT_CONSTEXPR bool
		operator==(bitset<N> const& rhs) const SPROUT_NOEXCEPT {
			return this->is_equal(rhs);
		}
		SPROUT_CONSTEXPR bool
		operator!=(bitset<N> const& rhs) const SPROUT_NOEXCEPT {
			return !this->is_equal(rhs);
		}
		SPROUT_CONSTEXPR value_type
		test(size_type position) const {
			return position >= N ? throw std::out_of_range("bitset::test")
				: unchecked_test(position)
				;
		}
		SPROUT_CONSTEXPR bool
		all() const SPROUT_NOEXCEPT {
			return this->template are_all<N>();
		}
		SPROUT_CONSTEXPR bool
		any() const SPROUT_NOEXCEPT {
			return this->is_any();
		}
		SPROUT_CONSTEXPR bool
		none() const SPROUT_NOEXCEPT {
			return !this->is_any();
		}
		SPROUT_CONSTEXPR bitset<N>
		operator<<(size_type position) const SPROUT_NOEXCEPT {
			return position < N
				? bitset(this->do_left_shift(position)).do_sanitize_c()
				: bitset(this->do_reset())
				;
		}
		SPROUT_CONSTEXPR bitset<N>
		operator>>(size_type position) const SPROUT_NOEXCEPT {
			return position < N
				? bitset(this->do_right_shift(position)).do_sanitize_c()
				: bitset(this->do_reset())
				;
		}

		SPROUT_CONSTEXPR size_type
		find_first() const SPROUT_NOEXCEPT {
			return this->find_first(N);
		}
		SPROUT_CONSTEXPR size_type
		find_next(size_type prev) const SPROUT_NOEXCEPT {
			return this->find_next(prev, N);
		}

	public:
		template<std::size_t M>
		friend SPROUT_CONSTEXPR sprout::bitset<M>
		sprout::operator&(sprout::bitset<M> const& lhs, sprout::bitset<M> const& rhs) SPROUT_NOEXCEPT;
		template<std::size_t M>
		friend SPROUT_CONSTEXPR sprout::bitset<M>
		sprout::operator|(sprout::bitset<M> const& lhs, sprout::bitset<M> const& rhs) SPROUT_NOEXCEPT;
		template<std::size_t M>
		friend SPROUT_CONSTEXPR sprout::bitset<M>
		sprout::operator^(sprout::bitset<M> const& lhs, sprout::bitset<M> const& rhs) SPROUT_NOEXCEPT;
		template<typename Char, typename Traits, std::size_t M>
		friend SPROUT_NON_CONSTEXPR std::basic_istream<Char, Traits>&
		sprout::operator>>(std::basic_istream<Char, Traits>& lhs, sprout::bitset<M>& rhs);
		template<typename Char, typename Traits, std::size_t M>
		friend SPROUT_NON_CONSTEXPR std::basic_ostream<Char, Traits>&
		sprout::operator<<(std::basic_ostream<Char, Traits>& lhs, sprout::bitset<M> const& rhs);

		template<std::size_t M>
		friend SPROUT_CONSTEXPR std::size_t
		hash_value(sprout::bitset<M> const& v);
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_BITSET_BITSET_HPP
