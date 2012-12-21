#ifndef SPROUT_CSTRING_MEMCHR_HPP
#define SPROUT_CSTRING_MEMCHR_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT

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

	// 7.21.5.1  memchr ä÷êî
	inline SPROUT_CONSTEXPR void const*
	memchr(void const* s, int c, std::size_t n) {
		return sprout::detail::memchr_impl(
			sprout::as_iterator_base(
				NS_SSCRISK_CEL_OR_SPROUT::find(
					sprout::as_iterator(static_cast<unsigned char const*>(s)), sprout::as_iterator(static_cast<unsigned char const*>(s), n),
					static_cast<unsigned char>(c)
					)
				),
			static_cast<unsigned char const*>(s) + n
			);
	}

	inline SPROUT_CONSTEXPR void*
	memchr(void* s, int c, std::size_t n) {
		return sprout::detail::memchr_impl(
			sprout::as_iterator_base(
				NS_SSCRISK_CEL_OR_SPROUT::find(
					sprout::as_iterator(static_cast<unsigned char*>(s)), sprout::as_iterator(static_cast<unsigned char*>(s), n),
					static_cast<unsigned char>(c)
					)
				),
			static_cast<unsigned char*>(s) + n
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_MEMCHR_HPP
