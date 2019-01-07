/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_HAS_SPROUT_END_HPP
#define SPROUT_CONTAINER_HAS_SPROUT_END_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/container/end.hpp>

namespace sprout {
	//
	// has_sprout_end
	//
	namespace detail {
		template<typename T>
		struct has_sprout_end_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(sprout::end(std::declval<U>()))>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_sprout_end_test<T>::test(0))>::type>
		struct has_sprout_end
			: public Base_
		{};
#else
		template<typename T>
		struct has_sprout_end
			: public sprout::identity<decltype(sprout::detail::has_sprout_end_test<T>::test(0))>::type
		{};
#endif
	}	// namespace detail

	template<typename T>
	struct has_sprout_end
		: public sprout::detail::has_sprout_end<T>
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool has_sprout_end_v = sprout::has_sprout_end<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_HAS_SPROUT_END_HPP
