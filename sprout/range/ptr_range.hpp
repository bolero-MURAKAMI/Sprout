#ifndef SPROUT_RANGE_PTR_RANGE_HPP
#define SPROUT_RANGE_PTR_RANGE_HPP

#include <cstddef>
#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/range/range_container.hpp>

namespace sprout {
	namespace range {
		//
		// make_ptr_range
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::range::range_container<sprout::ptr_index_iterator<T> >
		make_ptr_range(T* p, typename std::iterator_traits<T*>::difference_type n) {
			return sprout::range::range_container<sprout::ptr_index_iterator<T> >(
				sprout::ptr_index_iterator<T>(p),
				sprout::ptr_index_iterator<T>(p, n)
				);
		}

		template<typename T, std::size_t N>
		inline SPROUT_CONSTEXPR sprout::range::range_container<sprout::ptr_index_iterator<T> >
		make_ptr_range(T (& arr)[N]) {
			return sprout::range::range_container<sprout::ptr_index_iterator<T> >(
				sprout::ptr_index_iterator<T>(arr),
				sprout::ptr_index_iterator<T>(arr, N)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_PTR_RANGE_HPP
