/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_REMOVED_HPP
#define SPROUT_RANGE_ADAPTOR_REMOVED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/filter_iterator.hpp>
#include <sprout/iterator/remove_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// removed_range
		//
		template<typename Range>
		class removed_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::filter_iterator<
					sprout::remove_filter<typename sprout::container_traits<Range>::value_type>,
					typename sprout::container_traits<Range>::iterator
				>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::filter_iterator<
					sprout::remove_filter<typename sprout::container_traits<Range>::value_type>,
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
		public:
			SPROUT_CONSTEXPR removed_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			removed_range(removed_range const&) = default;
			SPROUT_CONSTEXPR removed_range(range_type& range, value_type const& value)
				: base_type(
					iterator(sprout::begin(range), typename iterator::predicate_type(value)),
					iterator(sprout::end(range), typename iterator::predicate_type(value))
					)
			{}
		};

		//
		// remove_holder
		//
		template<typename T>
		class remove_holder {
		public:
			typedef T value_type;
		private:
			value_type value_;
		public:
			explicit SPROUT_CONSTEXPR remove_holder(value_type const& value)
				: value_(value)
			{}
			SPROUT_CONSTEXPR value_type const& value() const {
				return value_;
			}
		};

		//
		// removed_forwarder
		//
		class removed_forwarder {
		public:
			template<typename T>
			SPROUT_CONSTEXPR sprout::adaptors::remove_holder<T>
			operator()(T const& value) const {
				return sprout::adaptors::remove_holder<T>(value);
			}
		};

		//
		// removed
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::removed_forwarder removed = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename T>
		inline SPROUT_CONSTEXPR sprout::adaptors::removed_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::remove_holder<T> const& rhs) {
			return sprout::adaptors::removed_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs),
				rhs.value()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range>
	struct container_construct_traits<sprout::adaptors::removed_range<Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::removed_range<Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_REMOVED_HPP
