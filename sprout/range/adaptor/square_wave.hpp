/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_SQUARE_WAVE_HPP
#define SPROUT_RANGE_ADAPTOR_SQUARE_WAVE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/square_iterator.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
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
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::square_iterator<Value>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::square_iterator<Value>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
		public:
			SPROUT_CONSTEXPR square_wave_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
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
			SPROUT_CONSTEXPR square_wave_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			square_wave_range(square_wave_range const&) = default;
			explicit SPROUT_CONSTEXPR square_wave_range(
				value_type const& frequency = 1,
				value_type const& amplitude = 1,
				value_type const& phase = 0,
				value_type const& duty = 0.5
				)
				: base_type(
					iterator(0, frequency, amplitude, phase, duty),
					iterator(sprout::numeric_limits<difference_type>::max(), frequency, amplitude, phase, duty)
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
				) const
			{
				return sprout::adaptors::square_wave_range<Value>(frequency, amplitude, phase, duty);
			}
		};

		//
		// square_wave
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::square_wave_forwarder square_wave = {};
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
	template<typename Range, typename Value>
	struct container_construct_traits<sprout::adaptors::square_wave_range<Value, Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::square_wave_range<Value, Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_SQUARE_WAVE_HPP
