/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_UNIQUED_HPP
#define SPROUT_RANGE_ADAPTOR_UNIQUED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/adjacent_filter_iterator.hpp>
#include <sprout/iterator/unique_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/functional/equal_to.hpp>

namespace sprout {
	namespace adaptors {
		//
		// uniqued_range
		//
		template<typename Predicate, typename Range>
		class uniqued_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::adjacent_filter_iterator<
					sprout::unique_filter<Predicate>,
					typename sprout::container_traits<Range>::iterator
				>
			>
		{
		public:
			typedef Predicate predicate_type;
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::adjacent_filter_iterator<
					sprout::unique_filter<Predicate>,
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
		public:
			SPROUT_CONSTEXPR uniqued_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			uniqued_range(uniqued_range const&) = default;
			SPROUT_CONSTEXPR uniqued_range(range_type& range, Predicate pred)
				: base_type(
					iterator(typename iterator::predicate_type(pred), sprout::begin(range), sprout::end(range)),
					iterator(typename iterator::predicate_type(pred), sprout::end(range), sprout::end(range))
					)
			{}
		};

		//
		// unique_holder
		//
		template<typename Predicate = sprout::equal_to<> >
		class unique_holder {
		public:
			typedef Predicate predicate_type;
		private:
			Predicate pred_;
		public:
			SPROUT_CONSTEXPR unique_holder()
				: pred_()
			{}
			explicit SPROUT_CONSTEXPR unique_holder(Predicate pred)
				: pred_(pred)
			{}
			SPROUT_CONSTEXPR Predicate const& predicate() const {
				return pred_;
			}
		};

		//
		// uniqued_forwarder
		//
		class uniqued_forwarder {
		public:
			template<typename Predicate>
			SPROUT_CONSTEXPR sprout::adaptors::unique_holder<Predicate>
			operator()(Predicate pred) const {
				return sprout::adaptors::unique_holder<Predicate>(pred);
			}
		};

		//
		// uniqued
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::uniqued_forwarder uniqued = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Predicate>
		inline SPROUT_CONSTEXPR sprout::adaptors::uniqued_range<
			Predicate,
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::unique_holder<Predicate> const& rhs) {
			return sprout::adaptors::uniqued_range<
				Predicate,
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs),
				rhs.predicate()
				);
		}
		template<typename Range>
		inline SPROUT_CONSTEXPR sprout::adaptors::uniqued_range<
			sprout::equal_to<>,
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::uniqued_forwarder const&) {
			return sprout::adaptors::uniqued_range<
				sprout::equal_to<>,
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs),
				sprout::equal_to<>()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Predicate, typename Range>
	struct container_construct_traits<sprout::adaptors::uniqued_range<Predicate, Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::uniqued_range<Predicate, Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_UNIQUED_HPP
