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
		inline SPROUT_CONSTEXPR unsigned char const*
		memchr_impl(unsigned char const* found, unsigned char const* last) {
			return found == last ? nullptr
				: found
				;
		}
		inline SPROUT_CONSTEXPR unsigned char*
		memchr_impl(unsigned char* found, unsigned char* last) {
			return found == last ? nullptr
				: found
				;
		}

		template<typename T>
		struct memchr_result {
		private:
			static void const* check(void const*);
			static void* check(void*);
			static void check(...);
		public:
			typedef decltype(check(std::declval<T>())) type;
		};
	}	// namespace detail

	// 7.21.5.1 memchr ä÷êî
	//
	//	recursion depth:
	//		O(log N)
	//
#if 0
	inline SPROUT_CONSTEXPR void const*
	memchr(void const* s, int c, std::size_t n) {
		return sprout::detail::memchr_impl(
			sprout::ptr_unindex(
				sprout::find(
					sprout::ptr_index(static_cast<unsigned char const*>(s)), sprout::ptr_index(static_cast<unsigned char const*>(s), n),
					static_cast<unsigned char>(c)
					)
				),
			static_cast<unsigned char const*>(s) + n
			);
	}

	inline SPROUT_CONSTEXPR void*
	memchr(void* s, int c, std::size_t n) {
		return sprout::detail::memchr_impl(
			sprout::ptr_unindex(
				sprout::find(
					sprout::ptr_index(static_cast<unsigned char*>(s)), sprout::ptr_index(static_cast<unsigned char*>(s), n),
					static_cast<unsigned char>(c)
					)
				),
			static_cast<unsigned char*>(s) + n
			);
	}
#endif
	template<
		typename T,
		typename sprout::enabler_if<std::is_same<typename sprout::detail::memchr_result<T>::type, void const*>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR void const*
	memchr(T s, int c, std::size_t n) {
		return sprout::detail::memchr_impl(
			sprout::ptr_unindex(
				sprout::find(
					sprout::ptr_index(static_cast<unsigned char const*>(s)), sprout::ptr_index(static_cast<unsigned char const*>(s), n),
					static_cast<unsigned char>(c)
					)
				),
			static_cast<unsigned char const*>(s) + n
			);
	}

	template<
		typename T,
		typename sprout::enabler_if<std::is_same<typename sprout::detail::memchr_result<T>::type, void*>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR void*
	memchr(T s, int c, std::size_t n) {
		return sprout::detail::memchr_impl(
			sprout::ptr_unindex(
				sprout::find(
					sprout::ptr_index(static_cast<unsigned char*>(s)), sprout::ptr_index(static_cast<unsigned char*>(s), n),
					static_cast<unsigned char>(c)
					)
				),
			static_cast<unsigned char*>(s) + n
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_MEMCHR_HPP
