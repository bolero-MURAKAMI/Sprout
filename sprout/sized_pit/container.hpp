/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_SIZED_PIT_CONTAINER_HPP
#define SPROUT_SIZED_PIT_CONTAINER_HPP

#include <type_traits>
#include <sprout/utility/forward.hpp>
#include <sprout/sized_pit/sized_pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>

namespace sprout {
	namespace detail {
		template<typename Container, typename = void>
		struct sized_pit_container_construct_traits;

		template<typename Container>
		struct sized_pit_container_construct_traits<
			sprout::sized_pit<Container>,
			typename std::enable_if<sprout::is_fixed_container<Container>::value>::type
		> {
		public:
			typedef typename sprout::container_construct_traits<Container>::copied_type copied_type;
		public:
			template<typename Cont>
			static SPROUT_CONSTEXPR copied_type
			deep_copy(Cont&&) {
				return copied_type();
			}
			template<typename... Args>
			static SPROUT_CONSTEXPR copied_type
			make(Args&&... args) {
				return sprout::make<copied_type>(SPROUT_FORWARD(Args, args)...);
			}
			template<typename Cont, typename... Args>
			static SPROUT_CONSTEXPR copied_type
			remake(Cont&& cont, typename sprout::container_traits<sprout::sized_pit<Container> >::difference_type size, Args&&... args) {
				return sprout::remake<copied_type>(SPROUT_FORWARD(Cont, cont), size, SPROUT_FORWARD(Args, args)...);
			}
		};

		template<typename Container>
		struct sized_pit_container_construct_traits<
			sprout::sized_pit<Container>,
			typename std::enable_if<!sprout::is_fixed_container<Container>::value>::type
		> {
		public:
			typedef typename sprout::container_construct_traits<Container>::copied_type copied_type;
		public:
			template<typename Cont>
			static SPROUT_CONSTEXPR copied_type
			deep_copy(Cont&&) {
				return copied_type();
			}
			template<typename... Args>
			static SPROUT_CONSTEXPR copied_type
			make(Args&&... args) {
				return sprout::make<copied_type>(SPROUT_FORWARD(Args, args)...);
			}
			template<typename Cont, typename... Args>
			static SPROUT_CONSTEXPR copied_type
			remake(Cont&& cont, typename sprout::container_traits<sprout::sized_pit<Container> >::difference_type size, Args&&... args) {
				return sprout::remake<copied_type>(SPROUT_FORWARD(Cont, cont), size, SPROUT_FORWARD(Args, args)...);
			}
			template<typename Cont, typename InputIterator>
			static SPROUT_CONSTEXPR copied_type
			remake(Cont&&, typename sprout::container_traits<sprout::sized_pit<Container> >::difference_type, InputIterator first, InputIterator last) {
				return copied_type(first, last);
			}
		};
	}	// namespace detail
	//
	// container_construct_traits
	//
	template<typename Container>
	struct container_construct_traits<sprout::sized_pit<Container> >
		: public sprout::detail::sized_pit_container_construct_traits<sprout::sized_pit<Container> >
	{};

	//
	// container_transform_traits
	//
	template<typename Container>
	struct container_transform_traits<sprout::sized_pit<Container> > {
	public:
		template<typename sprout::container_traits<sprout::sized_pit<Container> >::size_type Size>
		struct rebind_size {
		public:
			typedef sprout::sized_pit<
				typename sprout::container_transform_traits<Container>::template rebind_size<Size>::type
			> type;
		};
		template<typename Type>
		struct rebind_type {
		public:
			typedef sprout::sized_pit<
				typename sprout::container_transform_traits<Container>::template rebind_type<Type>::type
			> type;
		};
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_SIZED_PIT_CONTAINER_HPP
