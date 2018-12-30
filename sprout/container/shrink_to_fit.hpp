/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_SHRINK_TO_FIT_HPP
#define SPROUT_CONTAINER_SHRINK_TO_FIT_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl container_shrink_to_fit(...);
}	// namespace sprout_adl

namespace sprout {
	namespace detail {
		template<typename T>
		struct has_mem_shrink_to_fit_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().shrink_to_fit())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_shrink_to_fit_test<T>::test(0))>::type>
		struct has_mem_shrink_to_fit
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_shrink_to_fit
			: public sprout::identity<decltype(sprout::detail::has_mem_shrink_to_fit_test<T>::test(0))>::type
		{};
#endif

		template<typename Container>
		inline SPROUT_CXX14_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_shrink_to_fit<Container&&>::value
		>::type
		container_shrink_to_fit_default(Container&& cont) {
			return SPROUT_FORWARD(Container, cont).shrink_to_fit();
		}
		template<typename Container>
		inline SPROUT_CXX14_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_shrink_to_fit<Container&&>::value
		>::type
		container_shrink_to_fit_default(Container&&) {
			return ;
		}
	}	// namespace detail

	namespace container_detail {
		template<typename Container>
		inline SPROUT_CXX14_CONSTEXPR void
		container_shrink_to_fit(Container&& cont) {
			return sprout::detail::container_shrink_to_fit_default(SPROUT_FORWARD(Container, cont));
		}
	}	// namespace container_detail

	//
	// shrink_to_fit
	//
	//	effect:
	//		ADL callable container_shrink_to_fit(cont) -> container_shrink_to_fit(cont)
	//		[default]
	//			callable cont.shrink_to_fit() -> cont.shrink_to_fit()
	//			otherwise -> no effects
	//
	template<typename Container>
	inline SPROUT_CXX14_CONSTEXPR void
	shrink_to_fit(Container&& cont) {
		using sprout::container_detail::container_shrink_to_fit;
		using sprout_adl::container_shrink_to_fit;
		return container_shrink_to_fit(SPROUT_FORWARD(Container, cont));
	}
}	// namespace sprout

#include <sprout/container/container_range_traits.hpp>

#endif	// #ifndef SPROUT_CONTAINER_SHRINK_TO_FIT_HPP
