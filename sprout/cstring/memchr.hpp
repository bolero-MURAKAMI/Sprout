#ifndef SPROUT_CSTRING_MEMCHR_HPP
#define SPROUT_CSTRING_MEMCHR_HPP

#include <cstddef>
#include <sprout/config.hpp>
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
	}	// namespace detail

	// 7.21.5.1 memchr ä÷êî
	//
	//	recursion depth:
	//		O(log N)
	//
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
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_MEMCHR_HPP
