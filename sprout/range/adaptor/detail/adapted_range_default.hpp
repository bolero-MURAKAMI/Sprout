/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_DETAIL_ADAPTED_RANGE_DEFAULT_HPP
#define SPROUT_RANGE_ADAPTOR_DETAIL_ADAPTED_RANGE_DEFAULT_HPP

#include <sprout/config.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/algorithm/fixed/copy.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace adaptors {
		namespace detail {
			template<typename Range, typename Iterator = typename sprout::container_traits<Range>::iterator>
			class adapted_range_default
				: public sprout::range::range_container<Iterator>
				, public sprout::detail::container_nosy_static_size<Range>
				, public sprout::detail::container_nosy_fixed_size<Range>
			{
			public:
				typedef Range range_type;
				typedef sprout::range::range_container<Iterator> base_type;
				typedef typename base_type::iterator iterator;
			public:
				SPROUT_CONSTEXPR adapted_range_default() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
				adapted_range_default(adapted_range_default const&) = default;
				explicit SPROUT_CONSTEXPR adapted_range_default(iterator const& first, iterator const& last)
					: base_type(first, last)
				{}
			};
		}	// namespace detail
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range, typename Iterator>
	struct container_construct_traits<sprout::adaptors::detail::adapted_range_default<Range, Iterator> > {
	public:
		typedef typename sprout::container_construct_traits<Range>::copied_type copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type deep_copy(Cont&& cont) {
			return sprout::range::fixed::copy(SPROUT_FORWARD(Cont, cont), sprout::pit<copied_type>());
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
			return sprout::make<copied_type>(SPROUT_FORWARD(Args, args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type remake(
			Cont&& cont,
			typename sprout::container_traits<sprout::adaptors::detail::adapted_range_default<Range> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(SPROUT_FORWARD(Cont, cont), size, SPROUT_FORWARD(Args, args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_DETAIL_ADAPTED_RANGE_DEFAULT_HPP
