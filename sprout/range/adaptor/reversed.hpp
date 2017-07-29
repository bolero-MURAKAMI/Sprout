/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_REVERSED_HPP
#define SPROUT_RANGE_ADAPTOR_REVERSED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/reverse_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// reversed_range
		//
		template<typename Range>
		class reversed_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::reverse_iterator<typename sprout::container_traits<Range>::iterator>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::reverse_iterator<typename sprout::container_traits<Range>::iterator>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
		public:
			SPROUT_CONSTEXPR reversed_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			reversed_range(reversed_range const&) = default;
			explicit SPROUT_CONSTEXPR reversed_range(range_type& range)
				: base_type(
					iterator(sprout::end(range)),
					iterator(sprout::begin(range))
					)
			{}
		};

		//
		// reversed_forwarder
		//
		class reversed_forwarder {};

		//
		// reversed
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::reversed_forwarder reversed = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range>
		inline SPROUT_CONSTEXPR sprout::adaptors::reversed_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::reversed_forwarder) {
			return sprout::adaptors::reversed_range<
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
	struct container_construct_traits<sprout::adaptors::reversed_range<Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::reversed_range<Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_REVERSED_HPP
