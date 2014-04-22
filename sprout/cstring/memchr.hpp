/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_MEMCHR_HPP
#define SPROUT_CSTRING_MEMCHR_HPP

#include <cstddef>
#include <type_traits>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/algorithm/find.hpp>

namespace sprout {
	namespace detail {
		template<typename T>
		struct memchr_result {
		private:
			static void const* check(void const*);
			static void* check(void*);
			static void check(...);
		public:
			typedef decltype(check(std::declval<T>())) type;
		};

		template<typename PtrIterator>
		inline SPROUT_CONSTEXPR PtrIterator
		memchr_impl(PtrIterator found, PtrIterator last) {
			return found == last ? nullptr
				: found
				;
		}
		template<typename PtrIterator, typename T>
		inline SPROUT_CONSTEXPR PtrIterator
		memchr(PtrIterator s, T c, std::size_t n) {
			return sprout::detail::memchr_impl(
				sprout::ptr_unindex(
					sprout::find(
						sprout::ptr_index(s), sprout::ptr_index(s, n),
						c
						)
					),
				s + n
				);
		}
	}	// namespace detail

	// 7.21.5.1 memchr ä÷êî
	//
	//	recursion depth:
	//		O(log N)
	//
#if 0
	inline SPROUT_CONSTEXPR void const*
	memchr(void const* s, int c, std::size_t n) {
		return sprout::detail::memchr(static_cast<unsigned char const*>(s), static_cast<unsigned char>(c), n);
	}

	inline SPROUT_CONSTEXPR void*
	memchr(void* s, int c, std::size_t n) {
		return sprout::detail::memchr(static_cast<unsigned char*>(s), static_cast<unsigned char>(c), n);
	}
#endif
	template<
		typename T,
		typename sprout::enabler_if<std::is_same<typename sprout::detail::memchr_result<T>::type, void const*>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR void const*
	memchr(T s, int c, std::size_t n) {
		return sprout::detail::memchr(static_cast<unsigned char const*>(s), static_cast<unsigned char>(c), n);
	}

	template<
		typename T,
		typename sprout::enabler_if<std::is_same<typename sprout::detail::memchr_result<T>::type, void*>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR void*
	memchr(T s, int c, std::size_t n) {
		return sprout::detail::memchr(static_cast<unsigned char*>(s), static_cast<unsigned char>(c), n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_MEMCHR_HPP
