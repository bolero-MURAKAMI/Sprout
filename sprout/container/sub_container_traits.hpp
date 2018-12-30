/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_SUB_CONTAINER_TRAITS_HPP
#define SPROUT_CONTAINER_SUB_CONTAINER_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/container/traits_fwd.hpp>

namespace sprout {
	//
	// sub_container_traits
	//
	template<typename Container>
	struct sub_container_traits {
	public:
		template<typename Cont>
		struct internal {
		public:
			typedef Cont&& type;
		};
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR typename internal<Cont>::type
		get_internal(Cont&& cont) {
			return SPROUT_FORWARD(Cont, cont);
		}
	};
	template<typename Container>
	struct sub_container_traits<Container const>
		: public sprout::sub_container_traits<Container>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_SUB_CONTAINER_TRAITS_HPP
