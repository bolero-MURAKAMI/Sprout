#ifndef SPROUT_RANGE_ADAPTOR_SQUARE_WAVE_HPP
#define SPROUT_RANGE_ADAPTOR_SQUARE_WAVE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/square_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// square_wave_range
		//
		template<typename Value, typename Range = void>
		class square_wave_range
			: public sprout::range::range_container<
				sprout::square_iterator<Value>
			>
			, public sprout::detail::container_nosy_static_size<Range>
			, public sprout::detail::container_nosy_fixed_size<Range>
		{
		public:
			typedef Range range_type;
			typedef sprout::range::range_container<
				sprout::square_iterator<Value>
			> base_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
			typedef typename base_type::difference_type difference_type;
		public:
			square_wave_range() = default;
			square_wave_range(square_wave_range const&) = default;
			explicit SPROUT_CONSTEXPR square_wave_range(
				range_type& range,
				value_type const& frequency = 1,
				value_type const& amplitude = 1,
				value_type const& phase = 0,
				value_type const& duty = 0.5
				)
				: base_type(
					iterator(0, frequency, amplitude, phase, duty),
					iterator(sprout::size(range), frequency, amplitude, phase, duty)
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
			SPROUT_CONSTEXPR value_type duty() const {
				return base_type::begin().duty();
			}
		};

		template<typename Value>
		class square_wave_range<Value, void>
			: public sprout::range::range_container<
				sprout::square_iterator<Value>
			>
		{
		public:
			typedef sprout::range::range_container<
				sprout::square_iterator<Value>
			> base_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
			typedef typename base_type::difference_type difference_type;
		public:
			square_wave_range() = default;
			square_wave_range(square_wave_range const&) = default;
			explicit SPROUT_CONSTEXPR square_wave_range(
				value_type const& frequency = 1,
				value_type const& amplitude = 1,
				value_type const& phase = 0,
				value_type const& duty = 0.5
				)
				: base_type(
					iterator(0, frequency, amplitude, phase, duty),
					iterator(-1, frequency, amplitude, phase, duty)
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
			SPROUT_CONSTEXPR value_type duty() const {
				return base_type::begin().duty();
			}
		};

		//
		// square_wave_forwarder
		//
		class square_wave_forwarder {
		public:
			template<typename Value>
			SPROUT_CONSTEXPR sprout::adaptors::square_wave_range<Value>
			operator()(
				Value const& frequency = 1,
				Value const& amplitude = 1,
				Value const& phase = 0,
				Value const& duty = 0.5
				)
			{
				return sprout::adaptors::square_wave_range<Value>(frequency, amplitude, phase, duty);
			}
		};

		//
		// square_wave
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::square_wave_forwarder square_wave{};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Value>
		inline SPROUT_CONSTEXPR sprout::adaptors::square_wave_range<
			Value,
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::square_wave_range<Value> const& rhs) {
			return sprout::adaptors::square_wave_range<
				Value,
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs),
				rhs.frequency(),
				rhs.amplitude(),
				rhs.phase(),
				rhs.duty()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Value, typename Range>
	struct container_construct_traits<sprout::adaptors::square_wave_range<Value, Range> > {
	public:
		typedef typename sprout::container_construct_traits<Range>::copied_type copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type deep_copy(Cont&& cont) {
			return sprout::range::fixed::copy(sprout::forward<Cont>(cont), sprout::pit<copied_type>());
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
			return sprout::make<copied_type>(sprout::forward<Args>(args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type remake(
			Cont&& cont,
			typename sprout::container_traits<sprout::adaptors::square_wave_range<Value, Range> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_SQUARE_WAVE_HPP
