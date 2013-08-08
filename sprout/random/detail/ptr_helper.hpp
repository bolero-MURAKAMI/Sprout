/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_DETAIL_PTR_HELPER_HPP
#define SPROUT_RANDOM_DETAIL_PTR_HELPER_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace random {
		namespace detail {
			template<typename T>
			struct ptr_helper {
				typedef T value_type;
				typedef T& reference_type;
				typedef T const& const_reference_type;
				typedef T const& rvalue_type;
				static reference_type ref(T& r) {
					return r;
				}
				static SPROUT_CONSTEXPR const_reference_type ref(T const& r) {
					return r;
				}
			};
			template<typename T>
			struct ptr_helper<T&> {
				typedef T value_type;
				typedef T& reference_type;
				typedef T const& const_reference_type;
				typedef T& rvalue_type;
				static reference_type ref(T& r) {
					return r;
				}
				static SPROUT_CONSTEXPR const_reference_type ref(T const& r) {
					return r;
				}
			};
			template<typename T>
			struct ptr_helper<T const&> {
				typedef T value_type;
				typedef T const& reference_type;
				typedef T const& const_reference_type;
				typedef T const& rvalue_type;
				static SPROUT_CONSTEXPR const_reference_type ref(T const& r) {
					return r;
				}
			};
			template<typename T>
			struct ptr_helper<T*> {
				typedef T value_type;
				typedef T& reference_type;
				typedef T const& const_reference_type;
				typedef T* rvalue_type;
				static reference_type ref(T* p) {
					return *p;
				}
				static SPROUT_CONSTEXPR const_reference_type ref(T const* p) {
					return *p;
				}
			};
			template<typename T>
			struct ptr_helper<T const*> {
				typedef T value_type;
				typedef T const& reference_type;
				typedef T const& const_reference_type;
				typedef T const* rvalue_type;
				static SPROUT_CONSTEXPR const_reference_type ref(T const* p) {
					return *p;
				}
			};
		}	// namespace detail
	}	// namespace random
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_DETAIL_PTR_HELPER_HPP
