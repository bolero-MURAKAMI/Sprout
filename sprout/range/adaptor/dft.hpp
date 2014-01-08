/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_DFT_HPP
#define SPROUT_RANGE_ADAPTOR_DFT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/dft_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// dft_range
		//
		template<typename Range>
		class dft_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::dft_iterator<typename sprout::container_traits<Range>::iterator>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::dft_iterator<typename sprout::container_traits<Range>::iterator>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
		public:
			dft_range() = default;
			dft_range(dft_range const&) = default;
			explicit SPROUT_CONSTEXPR dft_range(range_type& range)
				: base_type(
					iterator(sprout::begin(range), sprout::end(range)),
					iterator(sprout::begin(range), sprout::end(range), sprout::size(range))
					)
			{}
		};

		//
		// dft_forwarder
		//
		class dft_forwarder {};

		//
		// dft
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::dft_forwarder dft = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range>
		inline SPROUT_CONSTEXPR sprout::adaptors::dft_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::dft_forwarder) {
			return sprout::adaptors::dft_range<
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
	struct container_construct_traits<sprout::adaptors::dft_range<Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::dft_range<Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_DFT_HPP
