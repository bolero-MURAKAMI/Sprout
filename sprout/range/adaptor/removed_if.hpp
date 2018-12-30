/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_REMOVED_IF_HPP
#define SPROUT_RANGE_ADAPTOR_REMOVED_IF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/filter_iterator.hpp>
#include <sprout/iterator/remove_if_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// removed_if_range
		//
		template<typename Predicate, typename Range>
		class removed_if_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::filter_iterator<
					sprout::remove_if_filter<Predicate>,
					typename sprout::container_traits<Range>::iterator
				>
			>
		{
		public:
			typedef Predicate predicate_type;
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::filter_iterator<
					sprout::remove_if_filter<Predicate>,
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
		public:
			SPROUT_CONSTEXPR removed_if_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			removed_if_range(removed_if_range const&) = default;
			SPROUT_CONSTEXPR removed_if_range(range_type& range, Predicate pred)
				: base_type(
					iterator(sprout::begin(range), typename iterator::predicate_type(pred)),
					iterator(sprout::end(range), typename iterator::predicate_type(pred))
					)
			{}
		};

		//
		// remove_if_holder
		//
		template<typename Predicate>
		class remove_if_holder {
		public:
			typedef Predicate predicate_type;
		private:
			Predicate pred_;
		public:
			explicit SPROUT_CONSTEXPR remove_if_holder(Predicate pred)
				: pred_(pred)
			{}
			SPROUT_CONSTEXPR Predicate const& predicate() const {
				return pred_;
			}
		};

		//
		// removed_if_forwarder
		//
		class removed_if_forwarder {
		public:
			template<typename Predicate>
			SPROUT_CONSTEXPR sprout::adaptors::remove_if_holder<Predicate>
			operator()(Predicate pred) const {
				return sprout::adaptors::remove_if_holder<Predicate>(pred);
			}
		};

		//
		// removed_if
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::removed_if_forwarder removed_if = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::adaptors::removed_if_range<
			Predicate,
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::remove_if_holder<Predicate> const& rhs) {
			return sprout::adaptors::removed_if_range<
				Predicate,
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs),
				rhs.predicate()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Predicate, typename Range>
	struct container_construct_traits<sprout::adaptors::removed_if_range<Predicate, Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::removed_if_range<Predicate, Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_REMOVED_IF_HPP
