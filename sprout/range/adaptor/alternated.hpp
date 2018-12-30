/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_ALTERNATED_HPP
#define SPROUT_RANGE_ADAPTOR_ALTERNATED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/alternate_iterator.hpp>
#include <sprout/range/adaptor/detail/jointed_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace adaptors {
		//
		// alternated_range
		//
		template<typename LRange, typename RRange>
		class alternated_range
			: public sprout::adaptors::detail::jointed_range_default<
				LRange, RRange,
				sprout::alternate_iterator<
					typename sprout::container_traits<LRange>::iterator,
					typename sprout::container_traits<RRange>::iterator
				>
			>
		{
		public:
			typedef sprout::adaptors::detail::jointed_range_default<
				LRange, RRange,
				sprout::alternate_iterator<
					typename sprout::container_traits<LRange>::iterator,
					typename sprout::container_traits<RRange>::iterator
				>
			> base_type;
			typedef typename base_type::range1_type range1_type;
			typedef typename base_type::range2_type range2_type;
			typedef typename base_type::iterator iterator;
		public:
			SPROUT_CONSTEXPR alternated_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			alternated_range(alternated_range const&) = default;
			SPROUT_CONSTEXPR alternated_range(range1_type& range1, range2_type& range2)
				: base_type(
					iterator(sprout::begin(range1), sprout::begin(range2)),
					iterator(
						sprout::next(sprout::begin(range1), NS_SSCRISK_CEL_OR_SPROUT::min(sprout::size(range1), sprout::size(range2))),
						sprout::next(sprout::begin(range2), NS_SSCRISK_CEL_OR_SPROUT::min(sprout::size(range1), sprout::size(range2)))
						)
					)
			{}
		};

		//
		// alternate_holder
		//
		template<typename RRange>
		class alternate_holder {
		public:
			typedef RRange range2_type;
		private:
			sprout::value_holder<range2_type&> range_;
		public:
			SPROUT_CONSTEXPR alternate_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			alternate_holder(alternate_holder const&) = default;
			explicit SPROUT_CONSTEXPR alternate_holder(range2_type& range)
				: range_(range)
			{}
			SPROUT_CONSTEXPR range2_type& range() const {
				return range_;
			}
		};

		//
		// alternated_forwarder
		//
		class alternated_forwarder {
		public:
			template<typename RRange>
			SPROUT_CONSTEXPR sprout::adaptors::alternate_holder<
				typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
			>
			operator()(RRange&& range) const {
				return sprout::adaptors::alternate_holder<
					typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
				>(
					sprout::lvalue_forward<RRange>(range)
					);
			}
		};

		//
		// alternated
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::alternated_forwarder alternated = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename LRange, typename RRange>
		inline SPROUT_CONSTEXPR sprout::adaptors::alternated_range<
			typename std::remove_reference<typename sprout::lvalue_reference<LRange>::type>::type,
			RRange
		>
		operator|(LRange&& lhs, sprout::adaptors::alternate_holder<RRange> const& rhs) {
			return sprout::adaptors::alternated_range<
				typename std::remove_reference<typename sprout::lvalue_reference<LRange>::type>::type,
				RRange
			>(
				sprout::lvalue_forward<LRange>(lhs),
				rhs.range()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename LRange, typename RRange>
	struct container_construct_traits<sprout::adaptors::alternated_range<LRange, RRange> >
		: public sprout::container_construct_traits<typename sprout::adaptors::alternated_range<LRange, RRange>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_ALTERNATED_HPP
