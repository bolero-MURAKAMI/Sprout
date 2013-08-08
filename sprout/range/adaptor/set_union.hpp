/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_SET_UNION_HPP
#define SPROUT_RANGE_ADAPTOR_SET_UNION_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/set_union_iterator.hpp>
#include <sprout/functional/less.hpp>
#include <sprout/range/adaptor/detail/jointed_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>

namespace sprout {
	namespace adaptors {
		//
		// set_union_range
		//
		template<typename LRange, typename RRange, typename Compare = sprout::less<> >
		class set_union_range
			: public sprout::adaptors::detail::jointed_range_default<
				LRange, RRange,
				sprout::set_union_iterator<
					typename sprout::container_traits<LRange>::iterator,
					typename sprout::container_traits<RRange>::iterator,
					Compare
				>
			>
		{
		public:
			typedef sprout::adaptors::detail::jointed_range_default<
				LRange, RRange,
				sprout::set_union_iterator<
					typename sprout::container_traits<LRange>::iterator,
					typename sprout::container_traits<RRange>::iterator,
					Compare
				>
			> base_type;
			typedef typename base_type::range1_type range1_type;
			typedef typename base_type::range2_type range2_type;
			typedef typename base_type::iterator iterator;
		public:
			set_union_range() = default;
			set_union_range(set_union_range const&) = default;
			SPROUT_CONSTEXPR set_union_range(range1_type& range1, range2_type& range2, Compare comp = Compare())
				: base_type(
					iterator(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2), comp),
					iterator(sprout::end(range1), sprout::end(range1), sprout::end(range2), sprout::end(range2), comp)
					)
			{}
		};

		//
		// set_union_holder
		//
		template<typename RRange, typename Compare = sprout::less<> >
		class set_union_holder {
		public:
			typedef RRange range2_type;
			typedef Compare compare_type;
		private:
			sprout::value_holder<range2_type&> range_;
			Compare comp_;
		public:
			set_union_holder() = default;
			set_union_holder(set_union_holder const&) = default;
			explicit SPROUT_CONSTEXPR set_union_holder(range2_type& range, Compare comp = Compare())
				: range_(range)
				, comp_(comp)
			{}
			SPROUT_CONSTEXPR range2_type& range() const {
				return range_;
			}
			SPROUT_CONSTEXPR Compare compare() const {
				return comp_;
			}
		};

		//
		// set_union_forwarder
		//
		class set_union_forwarder {
		public:
			template<typename RRange>
			SPROUT_CONSTEXPR sprout::adaptors::set_union_holder<
				typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
			>
			operator()(RRange&& range) const {
				return sprout::adaptors::set_union_holder<
					typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
				>(
					sprout::lvalue_forward<RRange>(range)
					);
			}
			template<typename RRange, typename Compare>
			SPROUT_CONSTEXPR sprout::adaptors::set_union_holder<
				typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type,
				Compare
			>
			operator()(RRange&& range, Compare comp) const {
				return sprout::adaptors::set_union_holder<
					typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type,
					Compare
				>(
					sprout::lvalue_forward<RRange>(range),
					comp
					);
			}
		};

		//
		// set_union
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::set_union_forwarder set_union = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename LRange, typename RRange, typename Compare>
		inline SPROUT_CONSTEXPR sprout::adaptors::set_union_range<
			typename std::remove_reference<typename sprout::lvalue_reference<LRange>::type>::type,
			RRange,
			Compare
		>
		operator|(LRange&& lhs, sprout::adaptors::set_union_holder<RRange, Compare> const& rhs) {
			return sprout::adaptors::set_union_range<
				typename std::remove_reference<typename sprout::lvalue_reference<LRange>::type>::type,
				RRange,
				Compare
			>(
				sprout::lvalue_forward<LRange>(lhs),
				rhs.range(),
				rhs.compare()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename LRange, typename RRange, typename Compare>
	struct container_construct_traits<sprout::adaptors::set_union_range<LRange, RRange, Compare> >
		: public sprout::container_construct_traits<typename sprout::adaptors::set_union_range<LRange, RRange, Compare>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_SET_UNION_HPP
