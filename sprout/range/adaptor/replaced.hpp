/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_REPLACED_HPP
#define SPROUT_RANGE_ADAPTOR_REPLACED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/transform_iterator.hpp>
#include <sprout/iterator/replace_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// replaced_range
		//
		template<typename Range>
		class replaced_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::transform_iterator<
					sprout::replace_value<typename sprout::container_traits<Range>::value_type>,
					typename sprout::container_traits<Range>::iterator
				>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::transform_iterator<
					sprout::replace_value<typename sprout::container_traits<Range>::value_type>,
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
		public:
			SPROUT_CONSTEXPR replaced_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			replaced_range(replaced_range const&) = default;
			SPROUT_CONSTEXPR replaced_range(range_type& range, value_type const& old_value, value_type const& new_value)
				: base_type(
					iterator(sprout::begin(range), typename iterator::functor_type(old_value, new_value)),
					iterator(sprout::end(range), typename iterator::functor_type(old_value, new_value))
					)
			{}
		};

		//
		// replace_holder
		//
		template<typename T>
		class replace_holder {
		public:
			typedef T value_type;
		private:
			value_type old_;
			value_type new_;
		public:
			SPROUT_CONSTEXPR replace_holder(value_type const& old_value, value_type const& new_value)
				: old_(old_value)
				, new_(new_value)
			{}
			SPROUT_CONSTEXPR value_type const& old_value() const {
				return old_;
			}
			SPROUT_CONSTEXPR value_type const& new_value() const {
				return new_;
			}
		};

		//
		// replaced_forwarder
		//
		class replaced_forwarder {
		public:
			template<typename T>
			SPROUT_CONSTEXPR sprout::adaptors::replace_holder<T>
			operator()(T const& old_value, T const& new_value) const {
				return sprout::adaptors::replace_holder<T>(old_value, new_value);
			}
		};

		//
		// replaced
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::replaced_forwarder replaced = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename T>
		inline SPROUT_CONSTEXPR sprout::adaptors::replaced_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::replace_holder<T> const& rhs) {
			return sprout::adaptors::replaced_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs),
				rhs.old_value(),
				rhs.new_value()
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range>
	struct container_construct_traits<sprout::adaptors::replaced_range<Range> >
		: public sprout::container_construct_traits<typename sprout::adaptors::replaced_range<Range>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_REPLACED_HPP
