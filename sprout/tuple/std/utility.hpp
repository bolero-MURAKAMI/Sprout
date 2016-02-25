/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_STD_UTILITY_HPP
#define SPROUT_TUPLE_STD_UTILITY_HPP

#include <type_traits>
#include <array>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple.hpp>

namespace sprout {
	namespace tuples {
		namespace detail {
			template<std::size_t I, typename T>
			struct get_impl;
			template<typename T1, typename T2>
			struct get_impl<0, std::pair<T1, T2> > {
			public:
				SPROUT_CONSTEXPR T1& operator()(std::pair<T1, T2>& t) const {
					return t.first;
				}
				SPROUT_CONSTEXPR T1 const& operator()(std::pair<T1, T2> const& t) const {
					return t.first;
				}
			};
			template<typename T1, typename T2>
			struct get_impl<1, std::pair<T1, T2> > {
			public:
				SPROUT_CONSTEXPR T2& operator()(std::pair<T1, T2>& t) const {
					return t.second;
				}
				SPROUT_CONSTEXPR T2 const& operator()(std::pair<T1, T2> const& t) const {
					return t.second;
				}
			};
		}	// namespace detail
	}	// namespace tuples
}	// namespace sprout

namespace sprout {
	namespace tuples {
		//
		// tuple_access_traits
		//
		template<typename T1, typename T2>
		struct tuple_access_traits<std::pair<T1, T2> > {
		public:
			template<std::size_t I>
			static SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, std::pair<T1, T2> >::type&
			tuple_get(std::pair<T1, T2>& t) SPROUT_NOEXCEPT {
				static_assert(I < 2, "tuple_get: index out of range");
				return sprout::tuples::detail::get_impl<I, std::pair<T1, T2> >()(t);
			}
			template<std::size_t I>
			static SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, std::pair<T1, T2> >::type const&
			tuple_get(std::pair<T1, T2> const& t) SPROUT_NOEXCEPT {
				static_assert(I < 2, "tuple_get: index out of range");
				return sprout::tuples::detail::get_impl<I, std::pair<T1, T2> >()(t);
			}
			template<std::size_t I>
			static SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, std::pair<T1, T2> >::type&&
			tuple_get(std::pair<T1, T2>&& t) SPROUT_NOEXCEPT {
				return sprout::move(tuple_get<I>(t));
			}
		};
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_STD_UTILITY_HPP
