/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_CALL_TRAITS_HPP
#define SPROUT_DETAIL_CALL_TRAITS_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		template<typename T, bool Small>
		struct ct_impl_1 {
		public:
			typedef T const& param_type;
		};
		template<typename T>
		struct ct_impl_1<T, true> {
		public:
			typedef T const param_type;
		};

		template<typename T, bool IsPointer, bool IsArithmetic>
		struct ct_impl {
		public:
			typedef T const& param_type;
		};
		template<typename T, bool IsPointer>
		struct ct_impl<T, IsPointer, true> {
		public:
			typedef typename sprout::detail::ct_impl_1<T, sizeof(T) <= sizeof(void*)>::param_type param_type;
		};
		template<typename T, bool IsArithmetic>
		struct ct_impl<T, true, IsArithmetic> {
		public:
			typedef T const param_type;
		};

		template<typename T>
		struct call_traits {
		public:
			typedef T value_type;
			typedef T& reference;
			typedef T const& const_reference;
			typedef typename sprout::detail::ct_impl<
				T,
				std::is_pointer<T>::value,
				std::is_arithmetic<T>::value
			>::param_type param_type;
		};
		template<typename T>
		struct call_traits<T&> {
			typedef T& value_type;
			typedef T& reference;
			typedef T const& const_reference;
			typedef T& param_type;
		};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_CALL_TRAITS_HPP
