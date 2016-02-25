/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_MERSENNE_TWISTER_HPP
#define SPROUT_RANDOM_MERSENNE_TWISTER_HPP

#include <istream>
#include <ostream>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/cstdint.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/array/array.hpp>
#include <sprout/detail/integer/integer_mask.hpp>

namespace sprout {
	namespace random {
		//
		// mersenne_twister_engine
		//
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		class mersenne_twister_engine {
		public:
			typedef UIntType result_type;
		private:
			struct private_construct_t {};
		public:
			SPROUT_STATIC_CONSTEXPR std::size_t word_size = w;
			SPROUT_STATIC_CONSTEXPR std::size_t state_size = n;
			SPROUT_STATIC_CONSTEXPR std::size_t shift_size = m;
			SPROUT_STATIC_CONSTEXPR std::size_t mask_bits = r;
			SPROUT_STATIC_CONSTEXPR result_type xor_mask = a;
			SPROUT_STATIC_CONSTEXPR std::size_t tempering_u = u;
			SPROUT_STATIC_CONSTEXPR result_type tempering_d = d;
			SPROUT_STATIC_CONSTEXPR std::size_t tempering_s = s;
			SPROUT_STATIC_CONSTEXPR result_type tempering_b = b;
			SPROUT_STATIC_CONSTEXPR std::size_t tempering_t = t;
			SPROUT_STATIC_CONSTEXPR result_type tempering_c = c;
			SPROUT_STATIC_CONSTEXPR std::size_t tempering_l = l;
			SPROUT_STATIC_CONSTEXPR result_type initialization_multiplier = f;
			SPROUT_STATIC_CONSTEXPR result_type default_seed = 5489u;
		private:
			SPROUT_STATIC_CONSTEXPR result_type upper_mask = (~static_cast<result_type>(0)) << r;
			SPROUT_STATIC_CONSTEXPR result_type lower_mask = ~upper_mask;
			SPROUT_STATIC_CONSTEXPR std::size_t unroll_factor = 6;
			SPROUT_STATIC_CONSTEXPR std::size_t unroll_extra1 = (n - m) % unroll_factor;
			SPROUT_STATIC_CONSTEXPR std::size_t unroll_extra2 = (m - 1) % unroll_factor;
		public:
			static SPROUT_CONSTEXPR result_type static_min() SPROUT_NOEXCEPT {
				return 0;
			}
			static SPROUT_CONSTEXPR result_type static_max() SPROUT_NOEXCEPT {
				return sprout::detail::low_bits_mask_t<w>::sig_bits;
			}
		private:
			template<typename... Args>
			static SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) + 1 == n,
				sprout::array<result_type, n>
			>::type init_seed_1(result_type value, Args const&... args) {
				return sprout::array<result_type, n>{{args..., value}};
			}
			template<typename... Args>
			static SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) + 1 < n,
				sprout::array<result_type, n>
			>::type init_seed_1(result_type value, Args const&... args) {
				return init_seed_1(
					(f * (value ^ (value >> (w - 2))) + (sizeof...(Args) + 1)) & static_max(),
					args...,
					value
					);
			}
			static SPROUT_CONSTEXPR sprout::array<result_type, n> init_seed(result_type value = default_seed) {
				return init_seed_1(value & static_max());
			}
		private:
			sprout::array<result_type, n> x_;
			std::size_t i_;
		private:
			SPROUT_CONSTEXPR mersenne_twister_engine(sprout::array<result_type, n> const& x, std::size_t i, private_construct_t)
				: x_(x)
				, i_(i)
			{}
			SPROUT_CONSTEXPR result_type
			rewind_find_1(result_type const* last, std::size_t size, std::size_t index) const {
				return index < n - size
					? x_[index]
					: *(last - (n - 1 - index))
					;
			}
			SPROUT_CONSTEXPR result_type
			rewind_find(result_type const* last, std::size_t size, std::size_t i) const {
				return rewind_find_1(last, size, (i + n - size + n - 1) % n);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == n,
				sprout::array<result_type, n>
			>::type
			rewind_finish_1(sprout::array<result_type, n> const&, Args const&... args) const {
				return sprout::array<result_type, n>{{args...}};
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < n,
				sprout::array<result_type, n>
			>::type
			rewind_finish_1(sprout::array<result_type, n> const& data, Args const&... args) const {
				return rewind_finish_1(data, args..., data[sizeof...(args)]);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == n,
				sprout::array<result_type, n>
			>::type
			rewind_finish(
				sprout::array<result_type, n> const&, result_type const*, std::size_t, std::size_t,
				Args const&... args
				) const
			{
				return sprout::array<result_type, n>{{args...}};
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < n,
				sprout::array<result_type, n>
			>::type
			rewind_finish(
				sprout::array<result_type, n> const& data, result_type const* last, std::size_t z, std::size_t i,
				Args const&... args
				) const
			{
				return &data[0] + i == last - z
					? rewind_finish_1(data, data[i], args...)
					: rewind_finish(data, last, z, i + 1, data[i], args...)
					;
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == n,
				sprout::array<result_type, n>
			>::type
			rewind_4(
				sprout::array<result_type, n> const&, result_type const*, std::size_t, result_type, result_type, std::size_t,
				Args const&... args
				) const
			{
				return sprout::array<result_type, n>{{args...}};
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < n,
				sprout::array<result_type, n>
			>::type
			rewind_4(
				sprout::array<result_type, n> const& data, result_type const* last, std::size_t z, result_type y0, result_type y1, std::size_t i,
				Args const&... args
				) const
			{
				return rewind_2(
					data, last, z, y1, i, (y0 & upper_mask) | (y1 & lower_mask),
					args...
					);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == n,
				sprout::array<result_type, n>
			>::type
			rewind_3(
				sprout::array<result_type, n> const&, result_type const*, std::size_t, result_type, result_type, std::size_t,
				Args const&... args
				) const
			{
				return sprout::array<result_type, n>{{args...}};
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < n,
				sprout::array<result_type, n>
			>::type
			rewind_3(
				sprout::array<result_type, n> const& data, result_type const* last, std::size_t z, result_type y0, result_type y1, std::size_t i,
				Args const&... args
				) const
			{
				return rewind_4(
					data, last, z, y0,
					y1 & (static_cast<result_type>(1) << (w - 1))
						? ((y1 ^ a) << 1) | 1
						: y1 << 1
						,
					i,
					args...
					);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == n,
				sprout::array<result_type, n>
			>::type
			rewind_2(
				sprout::array<result_type, n> const&, result_type const*, std::size_t, result_type, std::size_t,
				Args const&... args
				) const
			{
				return sprout::array<result_type, n>{{args...}};
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < n,
				sprout::array<result_type, n>
			>::type
			rewind_2(
				sprout::array<result_type, n> const& data, result_type const* last, std::size_t z, result_type y0, std::size_t i,
				Args const&... args
				) const
			{
				return i < z
					? rewind_3(data, last, z, y0, rewind_find(last, i, m - 1) ^ rewind_find(last, i, n - 1), i, args...)
					: rewind_finish(data, last, z, 0, args...)
					;
			}
			SPROUT_CONSTEXPR sprout::array<result_type, n>
			rewind_1(sprout::array<result_type, n> const& data, result_type const* last, std::size_t z, result_type y0) const {
				return rewind_2(
					data,
					last,
					z,
					y0 & (static_cast<result_type>(1) << (w - 1))
						? ((y0 ^ a) << 1) | 1
						: y0 << 1
						,
					0
					);
			}
			SPROUT_CONSTEXPR sprout::array<result_type, n>
			rewind(sprout::array<result_type, n> const& data, result_type const* last, std::size_t z) const {
				return rewind_1(data, last, z, x_[m - 1] ^ x_[n - 1]);
			}
			SPROUT_CONSTEXPR bool
			equal_impl_2(mersenne_twister_engine const& other, sprout::array<result_type, n> const& back, std::size_t offset, std::size_t i = 0) const {
				return i < offset
					? back[i + n - offset] != other.x_[i]
						? false
						: equal_impl_2(other, back, offset, i + 1)
					: true
					;
			}
			SPROUT_CONSTEXPR bool
			equal_impl_1(mersenne_twister_engine const& other, sprout::array<result_type, n> const& back, std::size_t offset, std::size_t i = 0) const {
				return i + offset < n
					? x_[i] != other.x_[i + offset]
						? false
						: equal_impl_1(other, back, offset, i + 1)
					: equal_impl_2(other, rewind(back, &back[n - 1], offset), offset)
					;
			}
			SPROUT_CONSTEXPR bool
			equal_impl(mersenne_twister_engine const& other) const {
				return equal_impl_1(other, sprout::array<result_type, n>(), other.i_ - i_);
			}
			SPROUT_CONSTEXPR result_type generate_impl_4(result_type z) const {
				return z ^ (z >> l);
			}
			SPROUT_CONSTEXPR result_type generate_impl_3(result_type z) const {
				return z ^ generate_impl_4((z << t) & c);
			}
			SPROUT_CONSTEXPR result_type generate_impl_2(result_type z) const {
				return z ^ generate_impl_3((z << s) & b);
			}
			SPROUT_CONSTEXPR result_type generate_impl_1(result_type z) const {
				return z ^ generate_impl_2((z >> u) & d);
			}
			SPROUT_CONSTEXPR result_type generate_impl() const {
				return generate_impl_1(x_[i_]);
			}
			SPROUT_CONSTEXPR sprout::random::random_result<mersenne_twister_engine> generate() const {
				return sprout::random::random_result<mersenne_twister_engine>(
					generate_impl(),
					mersenne_twister_engine(
						x_,
						i_ + 1,
						private_construct_t()
						)
					);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR mersenne_twister_engine twist_5(Args const&... args) const {
				return mersenne_twister_engine(
					sprout::array<result_type, n>{{
						args..., x_[m - 1] ^ ((x_[n - 1] & upper_mask) | (x_[0] & lower_mask) >> 1) ^ ((x_[0] & 1) * a)
						}},
					0,
					private_construct_t()
					);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == n - 1,
				mersenne_twister_engine
			>::type twist_4(std::size_t, Args const&... args) const {
				return twist_5(args...);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < n - 1,
				mersenne_twister_engine
			>::type twist_4(std::size_t i, Args const&... args) const {
				return twist_4(
					i + 1, args..., x_[i - (n - m)] ^ ((x_[i] & upper_mask) | (x_[i + 1] & lower_mask) >> 1) ^ ((x_[i + 1] & 1) * a)
					);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == n - 1 - unroll_extra2,
				mersenne_twister_engine
			>::type twist_3(std::size_t, Args const&... args) const {
				return twist_4(n - 1 - unroll_extra2, args...);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < n - 1 - unroll_extra2,
				mersenne_twister_engine
			>::type twist_3(std::size_t i, Args const&... args) const {
				return twist_3(
					i + 1, args..., x_[i - (n - m)] ^ ((x_[i] & upper_mask) | (x_[i + 1] & lower_mask) >> 1) ^ ((x_[i + 1] & 1) * a)
					);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == n - m,
				mersenne_twister_engine
			>::type twist_2(std::size_t, Args const&... args) const {
				return twist_3(n - m, args...);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < n - m,
				mersenne_twister_engine
			>::type twist_2(std::size_t i, Args const&... args) const {
				return twist_2(
					i + 1, args..., x_[i + m] ^ ((x_[i] & upper_mask) | (x_[i + 1] & lower_mask) >> 1) ^ ((x_[i + 1] & 1) * a)
					);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == n - m - unroll_extra1,
				mersenne_twister_engine
			>::type twist_1(std::size_t, Args const&... args) const {
				return twist_2(n - m - unroll_extra1, args...);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < n - m - unroll_extra1,
				mersenne_twister_engine
			>::type twist_1(std::size_t i, Args const&... args) const {
				return twist_1(
					i + 1, args..., x_[i + m] ^ ((x_[i] & upper_mask) | (x_[i + 1] & lower_mask) >> 1) ^ ((x_[i + 1] & 1) * a)
					);
			}
			SPROUT_CONSTEXPR mersenne_twister_engine twist() const {
				return twist_1(0);
			}
			SPROUT_CXX14_CONSTEXPR void do_twist() {
				UIntType const upper_mask = (~static_cast<UIntType>(0)) << r;
				UIntType const lower_mask = ~upper_mask;
				std::size_t const unroll_factor = 6;
				std::size_t const unroll_extra1 = (n - m) % unroll_factor;
				std::size_t const unroll_extra2 = (m - 1) % unroll_factor;
				for (std::size_t j = 0; j < n - m - unroll_extra1; ++j) {
					UIntType y = (x_[j] & upper_mask) | (x_[j + 1] & lower_mask);
					x_[j] = x_[j+m] ^ (y >> 1) ^ ((x_[j + 1] & 1) * a);
				}
				for (std::size_t j = n - m - unroll_extra1; j < n-m; ++j) {
					UIntType y = (x_[j] & upper_mask) | (x_[j + 1] & lower_mask);
					x_[j] = x_[j + m] ^ (y >> 1) ^ ((x_[j + 1] & 1) * a);
				}
				for (std::size_t j = n - m; j < n - 1 - unroll_extra2; ++j) {
					UIntType y = (x_[j] & upper_mask) | (x_[j + 1] & lower_mask);
					x_[j] = x_[j - (n - m)] ^ (y >> 1) ^ ((x_[j + 1] & 1) * a);
				}
				for (std::size_t j = n - 1 - unroll_extra2; j < n - 1; ++j) {
					UIntType y = (x_[j] & upper_mask) | (x_[j + 1] & lower_mask);
					x_[j] = x_[j - (n - m)] ^ (y >> 1) ^ ((x_[j + 1] & 1) * a);
				}
				{
					UIntType y = (x_[n - 1] & upper_mask) | (x_[0] & lower_mask);
					x_[n - 1] = x_[m - 1] ^ (y >> 1) ^ ((x_[0] & 1) * a);
				}
				i_ = 0;
			}
			SPROUT_CXX14_CONSTEXPR void do_rewind(UIntType* last, std::size_t z) const {
				UIntType const upper_mask = (~static_cast<UIntType>(0)) << r;
				UIntType const lower_mask = ~upper_mask;
				UIntType y0 = x_[m - 1] ^ x_[n - 1];
				if (y0 & (static_cast<UIntType>(1) << (w - 1))) {
					y0 = ((y0 ^ a) << 1) | 1;
				} else {
					y0 = y0 << 1;
				}
				for (std::size_t sz = 0; sz < z; ++sz) {
					UIntType y1 = rewind_find(last, sz, m - 1) ^ rewind_find(last, sz, n - 1);
					if (y1 & (static_cast<UIntType>(1) << (w - 1))) {
						y1 = ((y1 ^ a) << 1) | 1;
					} else {
						y1 = y1 << 1;
					}
					*(last - sz) = (y0 & upper_mask) | (y1 & lower_mask);
					y0 = y1;
				}
			}
			SPROUT_CXX14_CONSTEXPR bool do_equal_impl(mersenne_twister_engine const& other) const {
				UIntType back[n] = {};
				std::size_t offset = other.i_ - i_;
				for (std::size_t j = 0; j + offset < n; ++j) {
					if (x_[j] != other.x_[j + offset]) {
						return false;
					}
				}
				do_rewind(&back[n - 1], offset);
				for (std::size_t j = 0; j < offset; ++j) {
					if (back[j + n - offset] != other.x_[j]) {
						return false;
					}
				}
				return true;
			}
		public:
			SPROUT_CONSTEXPR mersenne_twister_engine()
				: x_(init_seed(default_seed))
				, i_(n)
			{}
			mersenne_twister_engine(mersenne_twister_engine const&) = default;
			explicit SPROUT_CONSTEXPR mersenne_twister_engine(result_type value)
				: x_(init_seed(value))
				, i_(n)
			{}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return static_min();
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return static_max();
			}
			SPROUT_CXX14_CONSTEXPR result_type operator()() {
				if (i_ == n) {
					do_twist();
				}
				UIntType z = x_[i_];
				++i_;
				z ^= ((z >> u) & d);
				z ^= ((z << s) & b);
				z ^= ((z << t) & c);
				z ^= (z >> l);
				return z;
			}
#ifndef SPROUT_CONFIG_DISABLE_CXX14_CONSTEXPR
			SPROUT_CXX14_CONSTEXPR sprout::random::random_result<mersenne_twister_engine> const operator()() const {
				mersenne_twister_engine eng(*this);
				result_type value = eng();
				return sprout::random::random_result<mersenne_twister_engine>(value, eng);
			}
#else	// #ifndef SPROUT_CONFIG_DISABLE_CXX14_CONSTEXPR
			SPROUT_CONSTEXPR sprout::random::random_result<mersenne_twister_engine> const operator()() const {
				return i_ == n
					? twist().generate()
					: generate()
					;
			}
#endif	// #ifndef SPROUT_CONFIG_DISABLE_CXX14_CONSTEXPR
#ifndef SPROUT_CONFIG_DISABLE_CXX14_CONSTEXPR
			friend SPROUT_CXX14_CONSTEXPR bool operator==(mersenne_twister_engine const& lhs, mersenne_twister_engine const& rhs) SPROUT_NOEXCEPT {
				return lhs.i_ < rhs.i_
					? lhs.do_equal_impl(rhs)
					: rhs.do_equal_impl(lhs)
					;
			}
			friend SPROUT_CXX14_CONSTEXPR bool operator!=(mersenne_twister_engine const& lhs, mersenne_twister_engine const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
#else	// #ifndef SPROUT_CONFIG_DISABLE_CXX14_CONSTEXPR
			friend SPROUT_CONSTEXPR bool operator==(mersenne_twister_engine const& lhs, mersenne_twister_engine const& rhs) SPROUT_NOEXCEPT {
				return lhs.i_ < rhs.i_
					? lhs.equal_impl(rhs)
					: rhs.equal_impl(lhs)
					;
			}
			friend SPROUT_CONSTEXPR bool operator!=(mersenne_twister_engine const& lhs, mersenne_twister_engine const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
#endif	// #ifndef SPROUT_CONFIG_DISABLE_CXX14_CONSTEXPR
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				mersenne_twister_engine& rhs
				)
			{
				for (std::size_t i = 0; i < state_size; ++i) {
					lhs >> rhs.x_[i] >> std::ws;
				}
				rhs.i_ = state_size;
				return lhs;
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				mersenne_twister_engine const& rhs
				)
			{
				sprout::array<result_type, n> data;
				for (std::size_t i = 0; i < rhs.i_; ++i) {
					data[i + n - rhs.i_] = rhs.x_[i];
				}
				if (rhs.i_ != n) {
					data = rhs.rewind(data, &data[n - rhs.i_ - 1], n - rhs.i_);
				}
				lhs << data[0];
				for (std::size_t i = 0; i < rhs.i_; ++i) {
					lhs << ' ' << data[i];
				}
				return lhs;
			}
		};
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		SPROUT_CONSTEXPR_OR_CONST std::size_t
			sprout::random::mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>::word_size
			;
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		SPROUT_CONSTEXPR_OR_CONST std::size_t
			sprout::random::mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>::state_size
			;
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		SPROUT_CONSTEXPR_OR_CONST std::size_t
			sprout::random::mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>::shift_size
			;
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		SPROUT_CONSTEXPR_OR_CONST std::size_t
			sprout::random::mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>::mask_bits
			;
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		SPROUT_CONSTEXPR_OR_CONST UIntType
			sprout::random::mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>::xor_mask
			;
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		SPROUT_CONSTEXPR_OR_CONST std::size_t
			sprout::random::mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>::tempering_u
			;
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		SPROUT_CONSTEXPR_OR_CONST UIntType
			sprout::random::mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>::tempering_d
			;
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		SPROUT_CONSTEXPR_OR_CONST std::size_t
			sprout::random::mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>::tempering_s
			;
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		SPROUT_CONSTEXPR_OR_CONST UIntType
			sprout::random::mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>::tempering_b
			;
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		SPROUT_CONSTEXPR_OR_CONST std::size_t
			sprout::random::mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>::tempering_t
			;
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		SPROUT_CONSTEXPR_OR_CONST UIntType
			sprout::random::mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>::tempering_c
			;
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		SPROUT_CONSTEXPR_OR_CONST std::size_t
			sprout::random::mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>::tempering_l
			;
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		SPROUT_CONSTEXPR_OR_CONST UIntType
			sprout::random::mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>::initialization_multiplier
			;
		template<
			typename UIntType,
			std::size_t w, std::size_t n, std::size_t m, std::size_t r, UIntType a, std::size_t u, UIntType d,
			std::size_t s, UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f
		>
		SPROUT_CONSTEXPR_OR_CONST UIntType
			sprout::random::mersenne_twister_engine<UIntType, w, n, m, r, a, u, d, s, b, t, c, l, f>::default_seed
			;

		//
		// mt11213b
		//
		typedef sprout::random::mersenne_twister_engine<
			std::uint_fast32_t,
			32,
			351,
			175,
			19,
			0xccab8ee7,
			11,
			0xffffffff,
			7,
			0x31b6ab00,
			15,
			0xffe50000,
			17,
			1812433253
		> mt11213b;
		//
		// mt19937
		//
		typedef sprout::random::mersenne_twister_engine<
			std::uint_fast32_t,
			32,
			624,
			397,
			31,
			0x9908b0df,
			11,
			0xffffffff,
			7,
			0x9d2c5680,
			15,
			0xefc60000,
			18,
			1812433253
		> mt19937;
		//
		// mt19937_64
		//
		typedef sprout::random::mersenne_twister_engine<
			std::uint_fast64_t,
			64,
			312,
			156,
			31,
			SPROUT_UINT64_C(0xb5026f5aa96619e9),
			29,
			SPROUT_UINT64_C(0x5555555555555555),
			17,
			SPROUT_UINT64_C(0x71d67fffeda60000),
			37,
			SPROUT_UINT64_C(0xfff7eee000000000),
			43,
			SPROUT_UINT64_C(6364136223846793005)
		> mt19937_64;
	}	// namespace random

	using sprout::random::mersenne_twister_engine;
	using sprout::random::mt11213b;
	using sprout::random::mt19937;
	using sprout::random::mt19937_64;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_MERSENNE_TWISTER_HPP
