/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_DETAIL_JOINTED_RANGE_DEFAULT_HPP
#define SPROUT_RANGE_ADAPTOR_DETAIL_JOINTED_RANGE_DEFAULT_HPP

#include <sprout/config.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/metafunctions.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/arithmetic_promote.hpp>

namespace sprout {
	namespace adaptors {
		namespace detail {
			template<typename LRange, typename RRange, typename = void>
			class jointed_range_size;

			template<typename LRange, typename RRange>
			class jointed_range_size<
				LRange, RRange,
				typename std::enable_if<
					sprout::detail::has_static_size<sprout::container_traits<LRange> >::value
					&& sprout::detail::has_static_size<sprout::container_traits<RRange> >::value
				>::type
			> {
			public:
				typedef typename sprout::arithmetic_promote<
					typename sprout::container_traits<LRange>::size_type,
					typename sprout::container_traits<RRange>::size_type
				>::type size_type;
				SPROUT_STATIC_CONSTEXPR size_type static_size
					= sprout::container_traits<LRange>::static_size + sprout::container_traits<RRange>::static_size
					;
				static SPROUT_CONSTEXPR size_type fixed_size() {
					return static_size;
				}
			};

			template<typename LRange, typename RRange>
			class jointed_range_size<
				LRange, RRange,
				typename std::enable_if<
					sprout::detail::has_static_size<sprout::container_traits<LRange> >::value
					&& !sprout::detail::has_static_size<sprout::container_traits<RRange> >::value
				>::type
			> {
			public:
				typedef typename sprout::container_traits<LRange>::size_type size_type;
				SPROUT_STATIC_CONSTEXPR size_type static_size = sprout::container_traits<LRange>::static_size;
				static SPROUT_CONSTEXPR size_type fixed_size() {
					return static_size;
				}
			};
			template<typename LRange, typename RRange>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::adaptors::detail::jointed_range_size<
				LRange, RRange,
				typename std::enable_if<
					sprout::detail::has_static_size<sprout::container_traits<LRange> >::value
					&& !sprout::detail::has_static_size<sprout::container_traits<RRange> >::value
				>::type
			>::size_type
			sprout::adaptors::detail::jointed_range_size<
				LRange, RRange,
				typename std::enable_if<
					sprout::detail::has_static_size<sprout::container_traits<LRange> >::value
					&& !sprout::detail::has_static_size<sprout::container_traits<RRange> >::value
				>::type
			>::static_size;

			template<typename LRange, typename RRange>
			class jointed_range_size<
				LRange, RRange,
				typename std::enable_if<
					!sprout::detail::has_static_size<sprout::container_traits<LRange> >::value
					&& sprout::detail::has_static_size<sprout::container_traits<RRange> >::value
				>::type
			> {
			public:
				typedef typename sprout::container_traits<RRange>::size_type size_type;
				SPROUT_STATIC_CONSTEXPR size_type static_size = sprout::container_traits<RRange>::static_size;
				static SPROUT_CONSTEXPR size_type fixed_size() {
					return static_size;
				}
			};
			template<typename LRange, typename RRange>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::adaptors::detail::jointed_range_size<
				LRange, RRange,
				typename std::enable_if<
					!sprout::detail::has_static_size<sprout::container_traits<LRange> >::value
					&& sprout::detail::has_static_size<sprout::container_traits<RRange> >::value
				>::type
			>::size_type
			sprout::adaptors::detail::jointed_range_size<
				LRange, RRange,
				typename std::enable_if<
					!sprout::detail::has_static_size<sprout::container_traits<LRange> >::value
					&& sprout::detail::has_static_size<sprout::container_traits<RRange> >::value
				>::type
			>::static_size;

			template<typename LRange, typename RRange>
			class jointed_range_size<
				LRange, RRange,
				typename std::enable_if<
					!sprout::detail::has_static_size<sprout::container_traits<LRange> >::value
					&& !sprout::detail::has_static_size<sprout::container_traits<RRange> >::value
				>::type
			> {};

			template<
				typename LRange, typename RRange,
				typename Iterator = typename sprout::container_traits<LRange>::iterator
			>
			class jointed_range_default
				: public sprout::range::range_container<Iterator>
				, public sprout::adaptors::detail::jointed_range_size<LRange, RRange>
			{
			public:
				typedef LRange range_type;
				typedef LRange range1_type;
				typedef RRange range2_type;
				typedef sprout::range::range_container<Iterator> base_type;
				typedef typename base_type::iterator iterator;
			public:
				jointed_range_default() = default;
				jointed_range_default(jointed_range_default const&) = default;
				explicit SPROUT_CONSTEXPR jointed_range_default(iterator const& first, iterator const& last)
					: base_type(first, last)
				{}
			};

			template<typename LRange, typename RRange, typename = void>
			struct jointed_range_copied_type;
			template<typename LRange, typename RRange>
			struct jointed_range_copied_type<
				LRange, RRange,
				typename std::enable_if<
					sprout::containers::is_rebindable_size<LRange>::value
				>::type
			>
				: public sprout::container_construct_traits<
					typename sprout::containers::weak_rebind_size<
						typename sprout::container_construct_traits<LRange>::copied_type,
						sprout::adaptors::detail::jointed_range_size<LRange, RRange>::static_size
					>::type
				>
			{};
			template<typename LRange, typename RRange>
			struct jointed_range_copied_type<
				LRange, RRange,
				typename std::enable_if<
					!sprout::containers::is_rebindable_size<LRange>::value && sprout::containers::is_rebindable_size<RRange>::value
				>::type
			>
				: public sprout::containers::weak_rebind_size<
					typename sprout::container_construct_traits<RRange>::copied_type,
					sprout::adaptors::detail::jointed_range_size<LRange, RRange>::static_size
				>
			{};
			template<typename LRange, typename RRange>
			struct jointed_range_copied_type<
				LRange, RRange,
				typename std::enable_if<
					!sprout::containers::is_rebindable_size<LRange>::value && !sprout::containers::is_rebindable_size<RRange>::value
				>::type
			> {
			public:
				typedef typename sprout::container_construct_traits<LRange>::copied_type type;
			};
		}	// namespace detail
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename LRange, typename RRange, typename Iterator>
	struct container_construct_traits<sprout::adaptors::detail::jointed_range_default<LRange, RRange, Iterator> > {
	public:
		typedef typename sprout::adaptors::detail::jointed_range_copied_type<LRange, RRange>::type copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type deep_copy(Cont&& cont) {
			return sprout::range::fixed::copy(sprout::forward<Cont>(cont), sprout::pit<copied_type>());
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
			return sprout::make<copied_type>(sprout::forward<Args>(args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type remake(
			Cont&& cont,
			typename sprout::container_traits<sprout::adaptors::detail::jointed_range_default<LRange, RRange, Iterator> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_DETAIL_JOINTED_RANGE_DEFAULT_HPP
