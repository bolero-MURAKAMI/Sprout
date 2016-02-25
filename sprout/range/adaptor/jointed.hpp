/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_JOINTED_HPP
#define SPROUT_RANGE_ADAPTOR_JOINTED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/joint_iterator.hpp>
#include <sprout/range/adaptor/detail/jointed_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>

namespace sprout {
	namespace adaptors {
		//
		// jointed_range
		//
		template<typename LRange, typename RRange>
		class jointed_range
			: public sprout::adaptors::detail::jointed_range_default<
				LRange, RRange,
				sprout::joint_iterator<
					typename sprout::container_traits<LRange>::iterator,
					typename sprout::container_traits<RRange>::iterator
				>
			>
		{
		public:
			typedef sprout::adaptors::detail::jointed_range_default<
				LRange, RRange,
				sprout::joint_iterator<
					typename sprout::container_traits<LRange>::iterator,
					typename sprout::container_traits<RRange>::iterator
				>
			> base_type;
			typedef typename base_type::range1_type range1_type;
			typedef typename base_type::range2_type range2_type;
			typedef typename base_type::iterator iterator;
		public:
			SPROUT_CONSTEXPR jointed_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			jointed_range(jointed_range const&) = default;
			SPROUT_CONSTEXPR jointed_range(range1_type& range1, range2_type& range2)
				: base_type(
					iterator(sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::begin(range2)),
					iterator(sprout::end(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2))
					)
			{}
		};

		//
		// joint_holder
		//
		template<typename RRange>
		class joint_holder {
		public:
			typedef RRange range2_type;
		private:
			sprout::value_holder<range2_type&> range_;
		public:
			SPROUT_CONSTEXPR joint_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			joint_holder(joint_holder const&) = default;
			explicit SPROUT_CONSTEXPR joint_holder(range2_type& range)
				: range_(range)
			{}
			SPROUT_CONSTEXPR range2_type& range() const {
				return range_;
			}
		};

		//
		// jointed_forwarder
		//
		class jointed_forwarder {
		public:
			template<typename RRange>
			SPROUT_CONSTEXPR sprout::adaptors::joint_holder<
				typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
			>
			operator()(RRange&& range) const {
				return sprout::adaptors::joint_holder<
					typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
				>(
					sprout::lvalue_forward<RRange>(range)
					);
			}
		};

		//
		// jointed
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::jointed_forwarder jointed = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename LRange, typename RRange>
		inline SPROUT_CONSTEXPR sprout::adaptors::jointed_range<
			typename std::remove_reference<typename sprout::lvalue_reference<LRange>::type>::type,
			RRange
		>
		operator|(LRange&& lhs, sprout::adaptors::joint_holder<RRange> const& rhs) {
			return sprout::adaptors::jointed_range<
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
	struct container_construct_traits<sprout::adaptors::jointed_range<LRange, RRange> >
		: public sprout::container_construct_traits<typename sprout::adaptors::jointed_range<LRange, RRange>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_JOINTED_HPP
