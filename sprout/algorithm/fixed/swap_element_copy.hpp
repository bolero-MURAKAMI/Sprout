#ifndef SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_COPY_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/detail/container_complate.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Result, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type swap_element_copy_impl_ra(
				RandomAccessIterator first,
				RandomAccessIterator last,
				Result const& result,
				RandomAccessIterator pos1,
				RandomAccessIterator pos2,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				typename sprout::fixed_container_traits<Result>::size_type size,
				typename sprout::fixed_container_traits<Result>::size_type input_size
				)
			{
				return sprout::remake_clone<Result>(
					result,
					sprout::size(result),
					(Indexes >= offset && Indexes < offset + size && Indexes < offset + input_size
						? sprout::next(first, Indexes - offset) == pos1
							? *pos2
							: sprout::next(first, Indexes - offset) == pos2
							? *pos1
							: *sprout::next(first, Indexes - offset)
						: *sprout::next(sprout::fixed_begin(result), Indexes)
						)...
					);
			}
			template<typename RandomAccessIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type swap_element_copy(
				RandomAccessIterator first,
				RandomAccessIterator last,
				Result const& result,
				RandomAccessIterator pos1,
				RandomAccessIterator pos2,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::detail::swap_element_copy_impl_ra(
					first,
					last,
					result,
					pos1,
					pos2,
					typename sprout::index_range<0, sprout::fixed_container_traits<Result>::fixed_size>::type(),
					sprout::fixed_begin_offset(result),
					sprout::size(result),
					NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last)
					);
			}
			template<typename InputIterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type swap_element_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				InputIterator pos1,
				InputIterator pos2,
				typename sprout::fixed_container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type swap_element_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				InputIterator pos1,
				InputIterator pos2,
				typename sprout::fixed_container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? sprout::fixed::detail::swap_element_copy_impl(sprout::next(first), last, result, pos1, pos2, size, args..., first == pos1 ? *pos2 : first == pos2 ? *pos1 : *first)
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type swap_element_copy(
				InputIterator first,
				InputIterator last,
				Result const& result,
				InputIterator pos1,
				InputIterator pos2,
				void*
				)
			{
				return sprout::fixed::detail::swap_element_copy_impl(first, last, result, sprout::size(result));
			}
		}	// namespace detail
		//
		// swap_element_copy
		//
		template<typename InputIterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type swap_element_copy(
			InputIterator first,
			InputIterator last,
			Result const& result,
			InputIterator pos1,
			InputIterator pos2
			)
		{
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::fixed::detail::swap_element_copy(first, last, result, pos1, pos2, category());
		}
	}	// namespace fixed

	using sprout::fixed::swap_element_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SWAP_ELEMENT_COPY_HPP
