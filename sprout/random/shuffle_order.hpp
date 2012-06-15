#ifndef SPROUT_RANDOM_SHUFFLE_ORDER_HPP
#define SPROUT_RANDOM_SHUFFLE_ORDER_HPP

#include <cstddef>
#include <cstdint>
#include <limits>
#include <ios>
#include <istream>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/array.hpp>
#include <sprout/operation/fixed/set.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/linear_congruential.hpp>
#include <sprout/random/detail/signed_unsigned_tools.hpp>

namespace sprout {
	namespace random {
		namespace detail {
			template<typename UniformRandomNumberGenerator, std::size_t k>
			class shuffle_order_engine_member {
			protected:
				typedef UniformRandomNumberGenerator base_type;
				typedef typename base_type::result_type result_type;
			public:
				base_type rng_;
				sprout::array<result_type, k> v_;
				result_type y_;
			};
		}	// namespace detail
		//
		// shuffle_order_engine
		//
		template<typename UniformRandomNumberGenerator, std::size_t k>
		class shuffle_order_engine
			: private sprout::random::detail::shuffle_order_engine_member<UniformRandomNumberGenerator, k>
		{
		private:
			typedef sprout::random::detail::shuffle_order_engine_member<UniformRandomNumberGenerator, k> member_type;
		public:
			typedef UniformRandomNumberGenerator base_type;
			typedef typename base_type::result_type result_type;
		private:
			struct private_constructor_tag {};
		public:
			SPROUT_STATIC_CONSTEXPR std::size_t buffer_size = k;
			SPROUT_STATIC_CONSTEXPR std::size_t table_size = k;
		public:
			static_assert(std::numeric_limits<result_type>::is_integer, "std::numeric_limits<result_type>::is_integer");
			static_assert(k > 0, "k > 0");
		private:
			template<typename Random, typename... Args>
			static SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == k,
				member_type
			>::type init_member_1(Random const& rnd, Args const&... args) {
				return member_type{
					rnd.engine(),
					sprout::array<result_type, k>{{args...}},
					rnd.result()
					};
			}
			template<typename Random, typename... Args>
			static SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) < k,
				member_type
			>::type init_member_1(Random const& rnd, Args const&... args) {
				return init_member_1(rnd(), args..., rnd.result());
			}
			static SPROUT_CONSTEXPR member_type init_member(base_type const& rng) {
				return init_member_1(rng());
			}
		private:
			using member_type::rng_;
			using member_type::v_;
			using member_type::y_;
		private:
			SPROUT_CONSTEXPR shuffle_order_engine(
				base_type const& rng,
				sprout::array<result_type, k> const& v,
				result_type const& y,
				private_constructor_tag
				)
				: member_type{rng, v, y}
			{}
			template<typename Random, typename BaseUnsigned>
			SPROUT_CONSTEXPR sprout::random::random_result<shuffle_order_engine> generate_1(Random const& rnd, BaseUnsigned j) const {
				return sprout::random::random_result<shuffle_order_engine>(
					v_[j],
					shuffle_order_engine(
						rnd.engine(),
						sprout::fixed::set(v_, j, rnd.result()),
						v_[j],
						private_constructor_tag()
						)
					);
			}
			template<typename BaseUnsigned>
			SPROUT_CONSTEXPR sprout::random::random_result<shuffle_order_engine> generate(BaseUnsigned brange, BaseUnsigned off) const {
				return generate_1(
					rng_(),
					k == 1 ? BaseUnsigned(0)
						: brange < std::numeric_limits<BaseUnsigned>::max() / k ? BaseUnsigned(k * off / (brange + 1))
						: brange < std::numeric_limits<std::uintmax_t>::max() / k ? static_cast<BaseUnsigned>(static_cast<std::uintmax_t>(off) * k / (static_cast<std::uintmax_t>(brange) + 1))
						//: static_cast<BaseUnsigned>(sprout::random::detail::muldiv(off, k, static_cast<std::uintmax_t>(brange) + 1)) // ???
						: throw std::domain_error("shuffle_order_engine<>: Sorry, not implemented.")
					);
			}
		public:
			SPROUT_CONSTEXPR shuffle_order_engine()
				: member_type(init_member(base_type()))
			{}
			explicit SPROUT_CONSTEXPR shuffle_order_engine(result_type const& s)
				: member_type(init_member(base_type(s)))
			{}
			explicit SPROUT_CONSTEXPR shuffle_order_engine(base_type const& rng)
				: member_type(init_member(rng))
			{}
			SPROUT_CONSTEXPR result_type min() const {
				return rng_.min();
			}
			SPROUT_CONSTEXPR result_type max() const {
				return rng_.max();
			}
			SPROUT_CONSTEXPR sprout::random::random_result<shuffle_order_engine> operator()() const {
				typedef typename std::make_unsigned<result_type>::type base_unsigned;
				return generate(
					base_unsigned(sprout::random::detail::subtract<result_type>()(max(), min())),
					base_unsigned(sprout::random::detail::subtract<result_type>()(y_, min()))
					);
			}
			friend SPROUT_CONSTEXPR bool operator==(shuffle_order_engine const& lhs, shuffle_order_engine const& rhs) {
				return lhs.rng_ == rhs.rng_ && lhs.y_ == rhs.y_ && lhs.v_ == rhs.v_;
			}
			friend SPROUT_CONSTEXPR bool operator!=(shuffle_order_engine const& lhs, shuffle_order_engine const& rhs) {
				return !(lhs == rhs);
			}
			template<typename Elem, typename Traits>
			friend std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				shuffle_order_engine& rhs
				)
			{
				lhs >> rhs.rng_;
				for (std::size_t i = 0; i < k; ++i) {
					lhs >> std::ws >> rhs.v_[i];
				}
				lhs >> std::ws >> rhs.y_;
				return lhs;
			}
			template<typename Elem, typename Traits>
			friend std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				shuffle_order_engine const& rhs
				)
			{
				lhs << rhs.rng_;
				for (std::size_t i = 0; i < k; ++i) {
					lhs << ' ' << rhs.v_[i];
				}
				lhs << ' ' << rhs.y_;
				return lhs;
			}
		};
		template<typename UniformRandomNumberGenerator, std::size_t k>
		SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::random::shuffle_order_engine<UniformRandomNumberGenerator, k>::buffer_size;
		template<typename UniformRandomNumberGenerator, std::size_t k>
		SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::random::shuffle_order_engine<UniformRandomNumberGenerator, k>::table_size;

		//
		// knuth_b
		//
		typedef sprout::random::shuffle_order_engine<sprout::random::minstd_rand0, 256> knuth_b;
		//
		// kreutzer1986
		//
		typedef sprout::random::shuffle_order_engine<sprout::random::linear_congruential_engine<std::uint32_t, 1366, 150889, 714025>, 97> kreutzer1986;
	} // namespace random

	using sprout::random::shuffle_order_engine;
	using sprout::random::knuth_b;
	using sprout::random::kreutzer1986;
} // namespace sprout

#endif // #ifndef SPROUT_RANDOM_SHUFFLE_ORDER_HPP
