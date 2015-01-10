/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_SIZE_ENUMED_HPP
#define SPROUT_RANGE_ADAPTOR_SIZE_ENUMED_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/size_enum_iterator.hpp>
#include <sprout/range/adaptor/detail/adapted_range_default.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>

namespace sprout {
	namespace adaptors {
		//
		// size_enumed_range
		//
		template<typename Range, bool Separated = false>
		class size_enumed_range
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::size_enum_iterator<
					typename sprout::container_traits<Range>::iterator
				>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::size_enum_iterator<
					typename sprout::container_traits<Range>::iterator
				>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
		public:
			SPROUT_CONSTEXPR size_enumed_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			size_enumed_range(size_enumed_range const&) = default;
			explicit SPROUT_CONSTEXPR size_enumed_range(range_type& range)
				: base_type(
					iterator(sprout::begin(range)),
					iterator(sprout::end(range))
					)
			{}
		};

		template<typename Range>
		class size_enumed_range<Range, true>
			: public sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::size_enum_iterator<
					typename sprout::container_traits<Range>::iterator, true
				>
			>
		{
		public:
			typedef sprout::adaptors::detail::adapted_range_default<
				Range,
				sprout::size_enum_iterator<
					typename sprout::container_traits<Range>::iterator, true
				>
			> base_type;
			typedef typename base_type::range_type range_type;
			typedef typename base_type::iterator iterator;
			typedef typename base_type::value_type value_type;
		public:
			SPROUT_CONSTEXPR size_enumed_range() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			size_enumed_range(size_enumed_range const&) = default;
			explicit SPROUT_CONSTEXPR size_enumed_range(
				range_type& range,
				value_type sep_size = 0,
				bool omit_last = false
				)
				: base_type(
					iterator(sprout::begin(range), sep_size),
					omit_last
						? sprout::empty(range)
							? iterator(sprout::end(range), sep_size)
							: iterator(sprout::prev(sprout::end(range)), sep_size, true)
						: iterator(sprout::end(range), sep_size)
					)
			{}
		};

		//
		// size_enum_holder
		//
		template<typename Size>
		class size_enum_holder {
		public:
			typedef Size size_type;
		private:
			size_type sep_size_;
			bool omit_last_;
		public:
			SPROUT_CONSTEXPR size_enum_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			size_enum_holder(size_enum_holder const&) = default;
			explicit SPROUT_CONSTEXPR size_enum_holder(size_type size, bool omit_last = false)
				: sep_size_(size)
				, omit_last_(omit_last)
			{}
			SPROUT_CONSTEXPR size_type separator_size() const {
				return sep_size_;
			}
			SPROUT_CONSTEXPR bool omit_last() const {
				return omit_last_;
			}
		};

		//
		// size_enumed_forwarder
		//
		class size_enumed_forwarder {
		public:
			template<typename Size>
			SPROUT_CONSTEXPR typename sprout::adaptors::size_enum_holder<Size>
			operator()(Size size, bool omit_last = false) const {
				return typename sprout::adaptors::size_enum_holder<Size>(size, omit_last);
			}
		};

		//
		// size_enumed
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::size_enumed_forwarder size_enumed = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Size>
		inline SPROUT_CONSTEXPR sprout::adaptors::size_enumed_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
			true
		>
		operator|(Range&& lhs, sprout::adaptors::size_enum_holder<Size> const& rhs) {
			return sprout::adaptors::size_enumed_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type,
				true
			>(
				sprout::lvalue_forward<Range>(lhs),
				rhs.separator_size(),
				rhs.omit_last()
				);
		}
		template<typename Range>
		inline SPROUT_CONSTEXPR sprout::adaptors::size_enumed_range<
			typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
		>
		operator|(Range&& lhs, sprout::adaptors::size_enumed_forwarder const&) {
			return sprout::adaptors::size_enumed_range<
				typename std::remove_reference<typename sprout::lvalue_reference<Range>::type>::type
			>(
				sprout::lvalue_forward<Range>(lhs)
				);
		}
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range, bool Separated>
	struct container_construct_traits<sprout::adaptors::size_enumed_range<Range, Separated> >
		: public sprout::container_construct_traits<typename sprout::adaptors::size_enumed_range<Range, Separated>::base_type>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_SIZE_ENUMED_HPP
