/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_PIT_CONTAINER_HPP
#define SPROUT_PIT_CONTAINER_HPP

#include <type_traits>
#include <sprout/utility/forward.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>

namespace sprout {
	namespace detail {
		template<typename Container, typename = void>
		struct pit_container_construct_traits;

		template<typename Container>
		struct pit_container_construct_traits<
			sprout::pit<Container>,
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
				return sprout::make<copied_type>(sprout::forward<Args>(args)...);
			}
			template<typename Cont, typename... Args>
			static SPROUT_CONSTEXPR copied_type
			remake(Cont&& cont, typename sprout::container_traits<sprout::pit<Container> >::difference_type size, Args&&... args) {
				return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
			}
		};

		template<typename Container>
		struct pit_container_construct_traits<
			sprout::pit<Container>,
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
				return sprout::make<copied_type>(sprout::forward<Args>(args)...);
			}
			template<typename Cont, typename... Args>
			static SPROUT_CONSTEXPR copied_type
			remake(Cont&& cont, typename sprout::container_traits<sprout::pit<Container> >::difference_type size, Args&&... args) {
				return sprout::remake<copied_type>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
			}
			template<typename Cont, typename InputIterator>
			static SPROUT_CONSTEXPR copied_type
			remake(Cont&&, typename sprout::container_traits<sprout::pit<Container> >::difference_type, InputIterator first, InputIterator last) {
				return copied_type(first, last);
			}
		};
	}	// namespace detail
	//
	// container_construct_traits
	//
	template<typename Container>
	struct container_construct_traits<sprout::pit<Container> >
		: public sprout::detail::pit_container_construct_traits<sprout::pit<Container> >
	{};

	//
	// container_transform_traits
	//
	template<typename Container>
	struct container_transform_traits<sprout::pit<Container> > {
	public:
		template<typename sprout::container_traits<sprout::pit<Container> >::size_type Size>
		struct rebind_size {
		public:
			typedef sprout::pit<
				typename sprout::container_transform_traits<Container>::template rebind_size<Size>::type
			> type;
		};
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_PIT_CONTAINER_HPP
