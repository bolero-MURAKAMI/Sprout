/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_DEEP_INTERNAL_HPP
#define SPROUT_CONTAINER_DEEP_INTERNAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/internal.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace containers {
		namespace detail {
			template<typename Container, typename Prev, typename = void>
			struct deep_internal_impl;
			template<typename Container, typename Prev>
			struct deep_internal_impl<
				Container, Prev,
				typename std::enable_if<!std::is_same<Container, Prev&&>::value>::type
			>
				: public sprout::containers::detail::deep_internal_impl<
					typename sprout::containers::internal<Container>::type, Container
				>
			{};
			template<typename Container, typename Prev>
			struct deep_internal_impl<
				Container, Prev,
				typename std::enable_if<std::is_same<Container, Prev&&>::value>::type
			>
				: public sprout::identity<Container>
			{};
		}	// namespace detail
		//
		// deep_internal
		//
		template<typename Container>
		struct deep_internal
			: public sprout::containers::detail::deep_internal_impl<
				typename sprout::containers::internal<Container>::type, Container
			>
		{};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_DEEP_INTERNAL_HPP
