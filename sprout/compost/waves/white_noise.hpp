#ifndef SPROUT_COMPOST_WAVES_WHITE_NOISE_HPP
#define SPROUT_COMPOST_WAVES_WHITE_NOISE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/generator_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/random/normal_distribution.hpp>
#include <sprout/random/random_result.hpp>

namespace sprout {
	namespace compost {
		namespace waves {
			//
			// white_noise_range
			//
			template<typename Value, typename UniformRandomNumberGenerator, typename Range = void>
			class white_noise_range
				: public sprout::adaptors::detail::adapted_range_default<
					Range,
					sprout::generator_iterator<
						sprout::random::random_result<UniformRandomNumberGenerator, sprout::random::normal_distribution<Value> >
					>
				>
			{
			public:
				typedef sprout::adaptors::detail::adapted_range_default<
					Range,
					sprout::generator_iterator<
						sprout::random::random_result<UniformRandomNumberGenerator, sprout::random::normal_distribution<Value> >
					>
				> base_type;
				typedef typename base_type::range_type range_type;
				typedef typename base_type::iterator iterator;
				typedef typename base_type::value_type value_type;
				typedef typename iterator::generator_type generator_type;
				typedef typename generator_type::engine_type engine_type;
				typedef typename generator_type::distribution_type distribution_type;
			public:
				white_noise_range() = default;
				white_noise_range(white_noise_range const&) = default;
				explicit SPROUT_CONSTEXPR white_noise_range(
					range_type& range,
					engine_type const& gen,
					value_type const& sigma = 1
					)
					: base_type(
						iterator(distribution_type(0, sigma)(gen), sprout::size(range)),
						iterator()
						)
				{}
				SPROUT_CONSTEXPR engine_type engine() const {
					return base_type::begin().generator().engine();
				}
				SPROUT_CONSTEXPR value_type sigma() const {
					return base_type::begin().generator().distribution().sigma();
				}
			};

			template<typename Value, typename UniformRandomNumberGenerator>
			class white_noise_range<Value, UniformRandomNumberGenerator, void>
				: public sprout::range::range_container<
					sprout::generator_iterator<
						sprout::random::random_result<UniformRandomNumberGenerator, sprout::random::normal_distribution<Value> >
					>
				>
			{
			public:
				typedef sprout::range::range_container<
					sprout::generator_iterator<
						sprout::random::random_result<UniformRandomNumberGenerator, sprout::random::normal_distribution<Value> >
					>
				> base_type;
				typedef typename base_type::iterator iterator;
				typedef typename base_type::value_type value_type;
				typedef typename iterator::generator_type generator_type;
				typedef typename generator_type::engine_type engine_type;
				typedef typename generator_type::distribution_type distribution_type;
			public:
				white_noise_range() = default;
				white_noise_range(white_noise_range const&) = default;
				explicit SPROUT_CONSTEXPR white_noise_range(
					engine_type const& gen,
					value_type const& sigma = 1
					)
					: base_type(
						iterator(distribution_type(0, sigma)(gen)),
						iterator()
						)
				{}
				SPROUT_CONSTEXPR engine_type engine() const {
					return base_type::begin().generator().engine();
				}
				SPROUT_CONSTEXPR value_type sigma() const {
					return base_type::begin().generator().distribution().sigma();
				}
			};

			//
			// white_noise_forwarder
			//
			class white_noise_forwarder {
			public:
				template<typename UniformRandomNumberGenerator, typename Value = double>
				SPROUT_CONSTEXPR sprout::compost::waves::white_noise_range<Value, UniformRandomNumberGenerator>
				operator()(
					UniformRandomNumberGenerator const& gen,
					Value const& sigma = 1
					) const
				{
					return sprout::compost::waves::white_noise_range<Value, UniformRandomNumberGenerator>(gen, sigma);
				}
			};

			//
			// white_noise
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::waves::white_noise_forwarder white_noise{};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename Value, typename UniformRandomNumberGenerator>
			inline SPROUT_CONSTEXPR sprout::compost::waves::white_noise_range<
				Value, UniformRandomNumberGenerator,
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>
			operator|(Range&& lhs, sprout::compost::waves::white_noise_range<Value, UniformRandomNumberGenerator> const& rhs) {
				return sprout::compost::waves::white_noise_range<
					Value, UniformRandomNumberGenerator,
					typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
				>(
					sprout::lvalue_forward<Range>(lhs),
					rhs.engine(), rhs.sigma()
					);
			}
		}	// namespace waves

		using sprout::compost::waves::white_noise;
	}	// namespace compost

	//
	// container_construct_traits
	//
	template<typename Value, typename UniformRandomNumberGenerator, typename Range>
	struct container_construct_traits<sprout::compost::waves::white_noise_range<Value, UniformRandomNumberGenerator, Range> >
		: public sprout::container_construct_traits<typename sprout::compost::waves::white_noise_range<Value, UniformRandomNumberGenerator, Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_WAVES_WHITE_NOISE_HPP
