/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_TO_UPPER_HPP
#define SPROUT_RANGE_ADAPTOR_TO_UPPER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/transform_iterator.hpp>
#include <sprout/iterator/to_upper_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// to_upper_range
		//
		template<typename Range>
		class to_upper_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::transform_iterator<
					sprout::ctypes::to_upper<typename sprout::container_traits<Range>::value_type>,
					typename sprout::container_traits<Range>::iterator
				>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::transform_iterator<
					sprout::ctypes::to_upper<typename sprout::container_traits<Range>::value_type>,
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
		public:
			to_upper_range() = default;
			to_upper_range(to_upper_range const&) = default;
			explicit SPROUT_CONSTEXPR to_upper_range(range_type& range)
				: base_type(
					iterator(sprout::begin(range), typename iterator::functor_type()),
					iterator(sprout::end(range), typename iterator::functor_type())
					)
			{}
		};

		//
		// to_upper_forwarder
		//
		class to_upper_forwarder {};

		//
		// to_upper
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::to_upper_forwarder to_upper = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range>
		inline SPROUT_CONSTEXPR sprout::adaptors::to_upper_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, to_upper_forwarder) {
			return sprout::adaptors::to_upper_range<
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
	struct container_construct_traits<sprout::adaptors::to_upper_range<Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::to_upper_range<Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_TO_UPPER_HPP
