#ifndef SPROUT_RANGE_ADAPTOR_TRIANGLE_WAVE_HPP
#define SPROUT_RANGE_ADAPTOR_TRIANGLE_WAVE_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/triangle_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// triangle_wave_range
		//
		template<typename Value, typename Range = void>
		class triangle_wave_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::triangle_iterator<Value>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::triangle_iterator<Value>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
		public:
			triangle_wave_range() = default;
			triangle_wave_range(triangle_wave_range const&) = default;
			explicit SPROUT_CONSTEXPR triangle_wave_range(
				range_type& range,
				value_type const& frequency = 1,
				value_type const& amplitude = 1,
				value_type const& phase = 0
				)
				: base_type(
					iterator(0, frequency, amplitude, phase),
					iterator(sprout::size(range), frequency, amplitude, phase)
					)
			{}
			SPROUT_CONSTEXPR value_type frequency() const {
				return base_type::begin().frequency();
			}
			SPROUT_CONSTEXPR value_type amplitude() const {
				return base_type::begin().amplitude();
			}
			SPROUT_CONSTEXPR value_type phase() const {
				return base_type::begin().phase();
			}
		};

		template<typename Value>
		class triangle_wave_range<Value, void>
			: public sprout::range::range_container<
				sprout::triangle_iterator<Value>
			>
		{
		public:
			typedef sprout::range::range_container<
				sprout::triangle_iterator<Value>
			> base_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
			typedef typename base_type::difference_type difference_type;
		public:
			triangle_wave_range() = default;
			triangle_wave_range(triangle_wave_range const&) = default;
			explicit SPROUT_CONSTEXPR triangle_wave_range(
				value_type const& frequency = 1,
				value_type const& amplitude = 1,
				value_type const& phase = 0
				)
				: base_type(
					iterator(0, frequency, amplitude, phase),
					iterator(std::numeric_limits<difference_type>::max(), frequency, amplitude, phase)
					)
			{}
			SPROUT_CONSTEXPR value_type frequency() const {
				return base_type::begin().frequency();
			}
			SPROUT_CONSTEXPR value_type amplitude() const {
				return base_type::begin().amplitude();
			}
			SPROUT_CONSTEXPR value_type phase() const {
				return base_type::begin().phase();
			}
		};

		//
		// triangle_wave_forwarder
		//
		class triangle_wave_forwarder {
		public:
			template<typename Value>
			SPROUT_CONSTEXPR sprout::adaptors::triangle_wave_range<Value>
			operator()(
				Value const& frequency = 1,
				Value const& amplitude = 1,
				Value const& phase = 0
				) const
			{
				return sprout::adaptors::triangle_wave_range<Value>(frequency, amplitude, phase);
			}
		};

		//
		// triangle_wave
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::triangle_wave_forwarder triangle_wave = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Value>
		inline SPROUT_CONSTEXPR sprout::adaptors::triangle_wave_range<
			Value,
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::triangle_wave_range<Value> const& rhs) {
			return sprout::adaptors::triangle_wave_range<
				Value,
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs),
				rhs.frequency(),
				rhs.amplitude(),
				rhs.phase()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range, typename Value>
	struct container_construct_traits<sprout::adaptors::triangle_wave_range<Value, Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::triangle_wave_range<Value, Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_TRIANGLE_WAVE_HPP
