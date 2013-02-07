#ifndef SPROUT_RANDOM_MERSENNE_TWISTER_HPP
#define SPROUT_RANDOM_MERSENNE_TWISTER_HPP

#include <cstddef>
#include <cstdint>
#include <ios>
#include <type_traits>
#include <sprout/config.hpp>
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
			struct private_constructor_tag {};
		public:
			SPROUT_STATIC_CONSTEXPR std::size_t word_size = w;
			SPROUT_STATIC_CONSTEXPR std::size_t state_size = n;
			SPROUT_STATIC_CONSTEXPR std::size_t shift_size = m;
			SPROUT_STATIC_CONSTEXPR std::size_t mask_bits = r;
			SPROUT_STATIC_CONSTEXPR UIntType xor_mask = a;
			SPROUT_STATIC_CONSTEXPR std::size_t tempering_u = u;
			SPROUT_STATIC_CONSTEXPR UIntType tempering_d = d;
			SPROUT_STATIC_CONSTEXPR std::size_t tempering_s = s;
			SPROUT_STATIC_CONSTEXPR UIntType tempering_b = b;
			SPROUT_STATIC_CONSTEXPR std::size_t tempering_t = t;
			SPROUT_STATIC_CONSTEXPR UIntType tempering_c = c;
			SPROUT_STATIC_CONSTEXPR std::size_t tempering_l = l;
			SPROUT_STATIC_CONSTEXPR UIntType initialization_multiplier = f;
			SPROUT_STATIC_CONSTEXPR UIntType default_seed = 5489u;
		private:
			SPROUT_STATIC_CONSTEXPR UIntType upper_mask = (~static_cast<UIntType>(0)) << r;
			SPROUT_STATIC_CONSTEXPR UIntType lower_mask = ~upper_mask;
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
				sprout::array<UIntType, n>
			>::type init_seed_1(UIntType const& value, Args const&... args) {
				return sprout::array<UIntType, n>{{args..., value}};
			}
			template<typename... Args>
			static SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) + 1 < n,
				sprout::array<UIntType, n>
			>::type init_seed_1(UIntType const& value, Args const&... args) {
				return init_seed_1(
					(f * (value ^ (value >> (w - 2))) + (sizeof...(Args) + 1)) & static_max(),
					args...,
					value
					);
			}
			static SPROUT_CONSTEXPR sprout::array<UIntType, n> init_seed(UIntType const& value) {
				return init_seed_1(value & static_max());
			}
		private:
			sprout::array<UIntType, n> x_;
			std::size_t i_;
		private:
			SPROUT_CONSTEXPR mersenne_twister_engine(sprout::array<UIntType, n> const& x, std::size_t i, private_constructor_tag)
				: x_(x)
				, i_(i)
			{}
			SPROUT_CONSTEXPR UIntType
			rewind_find_1(UIntType const* last, std::size_t size, std::size_t index) const {
				return index < n - size
					? x_[index]
					: *(last - (n - 1 - index))
					;
			}
			SPROUT_CONSTEXPR UIntType
			rewind_find(UIntType const* last, std::size_t size, std::size_t i) const {
				return rewind_find_1(last, size, (i + n - size + n - 1) % n);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == n,
				sprout::array<UIntType, n>
			>::type
			rewind_finish_1(sprout::array<UIntType, n> const& data, Args const&... args) const {
				return sprout::array<UIntType, n>{{args...}};
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < n,
				sprout::array<UIntType, n>
			>::type
			rewind_finish_1(sprout::array<UIntType, n> const& data, Args const&... args) const {
				return rewind_finish_1(data, args..., data[sizeof...(args)]);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == n,
				sprout::array<UIntType, n>
			>::type
			rewind_finish(
				sprout::array<UIntType, n> const& data, UIntType const* last, std::size_t z, std::size_t i,
				Args const&... args
				) const
			{
				return sprout::array<UIntType, n>{{args...}};
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < n,
				sprout::array<UIntType, n>
			>::type
			rewind_finish(
				sprout::array<UIntType, n> const& data, UIntType const* last, std::size_t z, std::size_t i,
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
				sprout::array<UIntType, n>
			>::type
			rewind_4(
				sprout::array<UIntType, n> const& data, UIntType const* last, std::size_t z, UIntType y0, UIntType y1, std::size_t i,
				Args const&... args
				) const
			{
				return sprout::array<UIntType, n>{{args...}};
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < n,
				sprout::array<UIntType, n>
			>::type
			rewind_4(
				sprout::array<UIntType, n> const& data, UIntType const* last, std::size_t z, UIntType y0, UIntType y1, std::size_t i,
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
				sprout::array<UIntType, n>
			>::type
			rewind_3(
				sprout::array<UIntType, n> const& data, UIntType const* last, std::size_t z, UIntType y0, UIntType y1, std::size_t i,
				Args const&... args
				) const
			{
				return sprout::array<UIntType, n>{{args...}};
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < n,
				sprout::array<UIntType, n>
			>::type
			rewind_3(
				sprout::array<UIntType, n> const& data, UIntType const* last, std::size_t z, UIntType y0, UIntType y1, std::size_t i,
				Args const&... args
				) const
			{
				return rewind_4(
					data, last, z, y0,
					y1 & (static_cast<UIntType>(1) << (w - 1))
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
				sprout::array<UIntType, n>
			>::type
			rewind_2(
				sprout::array<UIntType, n> const& data, UIntType const* last, std::size_t z, UIntType y0, std::size_t i,
				Args const&... args
				) const
			{
				return sprout::array<UIntType, n>{{args...}};
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < n,
				sprout::array<UIntType, n>
			>::type
			rewind_2(
				sprout::array<UIntType, n> const& data, UIntType const* last, std::size_t z, UIntType y0, std::size_t i,
				Args const&... args
				) const
			{
				return i < z
					? rewind_3(data, last, z, y0, rewind_find(last, i, m - 1) ^ rewind_find(last, i, n - 1), i, args...)
					: rewind_finish(data, last, z, 0, args...)
					;
			}
			SPROUT_CONSTEXPR sprout::array<UIntType, n>
			rewind_1(sprout::array<UIntType, n> const& data, UIntType const* last, std::size_t z, UIntType y0) const {
				return rewind_2(
					data,
					last,
					z,
					y0 & (static_cast<UIntType>(1) << (w - 1))
						? ((y0 ^ a) << 1) | 1
						: y0 << 1
						,
					0
					);
			}
			SPROUT_CONSTEXPR sprout::array<UIntType, n>
			rewind(sprout::array<UIntType, n> const& data, UIntType const* last, std::size_t z) const {
				return rewind_1(data, last, z, x_[m - 1] ^ x_[n - 1]);
			}
			SPROUT_CONSTEXPR bool
			equal_impl_2(mersenne_twister_engine const& other, sprout::array<UIntType, n> back, std::size_t offset, std::size_t i = 0) const {
				return i < offset
					? back[i + n - offset] != other.x_[i]
						? false
						: equal_impl_2(other, back, offset, i + 1)
					: true
					;
			}
			SPROUT_CONSTEXPR bool
			equal_impl_1(mersenne_twister_engine const& other, sprout::array<UIntType, n> back, std::size_t offset, std::size_t i = 0) const {
				return i + offset < n
					? x_[i] != other.x_[i + offset]
						? false
						: equal_impl_1(other, back, offset, i + 1)
					: equal_impl_2(other, rewind(back, &back[n - 1], offset), offset)
					;
			}
			SPROUT_CONSTEXPR bool
			equal_impl(mersenne_twister_engine const& other) const {
				return equal_impl_1(other, sprout::array<UIntType, n>(), other.i_ - i_);
			}
			SPROUT_CONSTEXPR UIntType generate_impl_4(UIntType z) const {
				return z ^ (z >> l);
			}
			SPROUT_CONSTEXPR UIntType generate_impl_3(UIntType z) const {
				return z ^ generate_impl_4((z << t) & c);
			}
			SPROUT_CONSTEXPR UIntType generate_impl_2(UIntType z) const {
				return z ^ generate_impl_3((z << s) & b);
			}
			SPROUT_CONSTEXPR UIntType generate_impl_1(UIntType z) const {
				return z ^ generate_impl_2((z >> u) & d);
			}
			SPROUT_CONSTEXPR UIntType generate_impl() const {
				return generate_impl_1(x_[i_]);
			}
			SPROUT_CONSTEXPR sprout::random::random_result<mersenne_twister_engine> generate() const {
				return sprout::random::random_result<mersenne_twister_engine>(
					generate_impl(),
					mersenne_twister_engine(
						x_,
						i_ + 1,
						private_constructor_tag()
						)
					);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR mersenne_twister_engine twist_5(Args const&... args) const {
				return mersenne_twister_engine(
					sprout::array<UIntType, n>{{
						args..., x_[m - 1] ^ ((x_[n - 1] & upper_mask) | (x_[0] & lower_mask) >> 1) ^ ((x_[0] & 1) * a)
						}},
					0,
					private_constructor_tag()
					);
			}
			template<typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == n - 1,
				mersenne_twister_engine
			>::type twist_4(std::size_t i, Args const&... args) const {
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
			>::type twist_3(std::size_t i, Args const&... args) const {
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
			>::type twist_2(std::size_t i, Args const&... args) const {
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
			>::type twist_1(std::size_t i, Args const&... args) const {
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
		public:
			SPROUT_CONSTEXPR mersenne_twister_engine()
				: x_(init_seed(default_seed))
				, i_(n)
			{}
			explicit SPROUT_CONSTEXPR mersenne_twister_engine(UIntType const& value)
				: x_(init_seed(value))
				, i_(n)
			{}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return static_min();
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return static_max();
			}
			SPROUT_CONSTEXPR sprout::random::random_result<mersenne_twister_engine> operator()() const {
				return i_ == n
					? twist().generate()
					: generate()
					;
			}
			friend SPROUT_CONSTEXPR bool operator==(mersenne_twister_engine const& lhs, mersenne_twister_engine const& rhs) SPROUT_NOEXCEPT {
				return lhs.i_ < rhs.i_
					? lhs.equal_impl(rhs)
					: rhs.equal_impl(lhs)
					;
			}
			friend SPROUT_CONSTEXPR bool operator!=(mersenne_twister_engine const& lhs, mersenne_twister_engine const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
			template<typename Elem, typename Traits>
			friend std::basic_istream<Elem, Traits>& operator>>(
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
			friend std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				mersenne_twister_engine const& rhs
				)
			{
				sprout::array<UIntType, n> data;
				for(std::size_t i = 0; i < rhs.i_; ++i) {
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
			std::uint32_t,
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
			std::uint32_t,
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
			std::uint64_t,
			64,
			312,
			156,
			31,
			UINT64_C(0xb5026f5aa96619e9),
			29,
			UINT64_C(0x5555555555555555),
			17,
			UINT64_C(0x71d67fffeda60000),
			37,
			UINT64_C(0xfff7eee000000000),
			43,
			UINT64_C(6364136223846793005)
		> mt19937_64;
	}	// namespace random

	using sprout::random::mersenne_twister_engine;
	using sprout::random::mt11213b;
	using sprout::random::mt19937;
	using sprout::random::mt19937_64;
}	// namespace sprout

#endif // #ifndef SPROUT_RANDOM_MERSENNE_TWISTER_HPP
