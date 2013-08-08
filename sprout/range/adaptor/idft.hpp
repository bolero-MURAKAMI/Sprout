/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_IDFT_HPP
#define SPROUT_RANGE_ADAPTOR_IDFT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/idft_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// idft_range
		//
		template<typename Range>
		class idft_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::idft_iterator<typename sprout::container_traits<Range>::iterator>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::idft_iterator<typename sprout::container_traits<Range>::iterator>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
		public:
			idft_range() = default;
			idft_range(idft_range const&) = default;
			explicit SPROUT_CONSTEXPR idft_range(range_type& range)
				: base_type(
					iterator(sprout::begin(range), sprout::end(range)),
					iterator(sprout::begin(range), sprout::end(range), sprout::size(range))
					)
			{}
		};

		//
		// idft_forwarder
		//
		class idft_forwarder {};

		//
		// idft
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::idft_forwarder idft = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range>
		inline SPROUT_CONSTEXPR sprout::adaptors::idft_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::idft_forwarder) {
			return sprout::adaptors::idft_range<
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
	struct container_construct_traits<sprout::adaptors::idft_range<Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::idft_range<Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_IDFT_HPP
