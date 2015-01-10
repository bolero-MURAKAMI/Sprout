/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_AMPLITUDE_SPECTRUM_HPP
#define SPROUT_RANGE_ADAPTOR_AMPLITUDE_SPECTRUM_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/transform_iterator.hpp>
#include <sprout/iterator/amplitude_spectrum_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/numeric/dft/amplitude_spectrum_value.hpp>

namespace sprout {
	namespace adaptors {
		//
		// amplitude_spectrum_range
		//
		template<typename Range>
		class amplitude_spectrum_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::transform_iterator<
					sprout::amplitude_value<typename sprout::container_traits<Range>::value_type>,
					typename sprout::container_traits<Range>::iterator
				>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::transform_iterator<
					sprout::amplitude_value<typename sprout::container_traits<Range>::value_type>,
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
		public:
			SPROUT_CONSTEXPR amplitude_spectrum_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			amplitude_spectrum_range(amplitude_spectrum_range const&) = default;
			explicit SPROUT_CONSTEXPR amplitude_spectrum_range(range_type& range)
				: base_type(
					iterator(sprout::begin(range), typename iterator::functor_type()),
					iterator(sprout::end(range), typename iterator::functor_type())
					)
			{}
		};

		//
		// amplitude_spectrum_forwarder
		//
		class amplitude_spectrum_forwarder {};

		//
		// amplitude_spectrum
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::amplitude_spectrum_forwarder amplitude_spectrum = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range>
		inline SPROUT_CONSTEXPR sprout::adaptors::amplitude_spectrum_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, amplitude_spectrum_forwarder) {
			return sprout::adaptors::amplitude_spectrum_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs)
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range>
	struct container_construct_traits<sprout::adaptors::amplitude_spectrum_range<Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::amplitude_spectrum_range<Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_AMPLITUDE_SPECTRUM_HPP
