/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_DETAIL_SIZED_RANGE_DEFAULT_HPP
#define SPROUT_RANGE_ADAPTOR_DETAIL_SIZED_RANGE_DEFAULT_HPP

#include <sprout/config.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/metafunctions.hpp>
#include <sprout/range/range_container.hpp>
#include <sprout/range/algorithm/copy.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace adaptors {
		namespace detail {
			template<typename Range, typename sprout::container_traits<Range>::size_type Size, typename = void>
			class sized_range_size;

			template<typename Range, typename sprout::container_traits<Range>::size_type Size>
			class sized_range_size<
				Range, Size,
				typename std::enable_if<sprout::detail::has_static_size<sprout::container_traits<Range> >::value>::type
			> {
			public:
				SPROUT_STATIC_CONSTEXPR typename sprout::container_traits<Range>::size_type static_size
					= Size < sprout::container_traits<Range>::static_size ? Size
						: sprout::container_traits<Range>::static_size
					;
				static SPROUT_CONSTEXPR typename sprout::container_traits<Range>::size_type fixed_size() {
					return static_size;
				}
			};
			template<typename Range, typename sprout::container_traits<Range>::size_type Size>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::container_traits<Range>::size_type
			sprout::adaptors::detail::sized_range_size<
				Range, Size,
				typename std::enable_if<sprout::detail::has_static_size<sprout::container_traits<Range> >::value>::type
			>::static_size;

			template<typename Range, typename sprout::container_traits<Range>::size_type Size>
			class sized_range_size<
				Range, Size,
				typename std::enable_if<!sprout::detail::has_static_size<sprout::container_traits<Range> >::value>::type
			> {
			public:
				SPROUT_STATIC_CONSTEXPR typename sprout::container_traits<Range>::size_type static_size = Size;
				static SPROUT_CONSTEXPR typename sprout::container_traits<Range>::size_type fixed_size() {
					return static_size;
				}
			};
			template<typename Range, typename sprout::container_traits<Range>::size_type Size>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::container_traits<Range>::size_type
			sprout::adaptors::detail::sized_range_size<
				Range, Size,
				typename std::enable_if<!sprout::detail::has_static_size<sprout::container_traits<Range> >::value>::type
			>::static_size;

			template<
				typename Range, typename sprout::container_traits<Range>::size_type Size,
				typename Iterator = typename sprout::container_traits<Range>::iterator
			>
			class sized_range_default
				: public sprout::range::range_container<Iterator>
				, public sprout::adaptors::detail::sized_range_size<Range, Size>
			{
			public:
				typedef Range range_type;
				typedef sprout::range::range_container<Iterator> base_type;
				typedef typename base_type::iterator iterator;
			public:
				sized_range_default() = default;
				sized_range_default(sized_range_default const&) = default;
				explicit SPROUT_CONSTEXPR sized_range_default(iterator const& first, iterator const& last)
					: base_type(first, last)
				{}
			};
		}	// namespace detail
	}	// namespace adaptors

	//
	// container_construct_traits
	//
	template<typename Range, typename sprout::container_traits<Range>::size_type Size, typename Iterator>
	struct container_construct_traits<sprout::adaptors::detail::sized_range_default<Range, Size, Iterator> > {
	public:
		typedef typename sprout::containers::weak_rebind_size<
			typename sprout::container_construct_traits<Range>::copied_type,
			sprout::adaptors::detail::sized_range_default<Range, Size, Iterator>::static_size
		>::type copied_type;
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
			typename sprout::container_traits<sprout::adaptors::detail::sized_range_default<Range, Size, Iterator> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_DETAIL_SIZED_RANGE_DEFAULT_HPP
