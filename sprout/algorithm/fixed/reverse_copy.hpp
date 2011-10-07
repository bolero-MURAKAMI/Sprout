#ifndef SPROUT_ALGORITHM_FIXED_REVERSE_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_REVERSE_COPY_HPP

#include <cstddef>
#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Result, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type reverse_copy_impl_ra(
				RandomAccessIterator first,
				RandomAccessIterator last,
				Result const& result,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				typename sprout::fixed_container_traits<Result>::size_type size,
				typename sprout::fixed_container_traits<Result>::size_type input_size
				)
			{
				return sprout::remake_clone<Result, Result>(
					result,
					sprout::size(result),
					(Indexes >= offset && Indexes < offset + size && Indexes < offset + input_size
						? *sprout::prev(last, 1 + Indexes - offset)
						: *sprout::next(sprout::fixed_begin(result), Indexes)
						)...
					);
			}
			template<typename RandomAccessIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type reverse_copy(
				RandomAccessIterator first,
				RandomAccessIterator last,
				Result const& result,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::detail::reverse_copy_impl_ra(
					first,
					last,
					result,
					typename sprout::index_range<0, sprout::fixed_container_traits<Result>::fixed_size>::type(),
					sprout::fixed_begin_offset(result),
					sprout::size(result),
					NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last)
					);
			}
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type reverse_copy_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type reverse_copy_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return reverse_copy_impl_3(result, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)));
			}
			template<typename BidirectionalIterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type reverse_copy_impl_2(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename BidirectionalIterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type reverse_copy_impl_2(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < static_cast<std::size_t>(offset)
					? reverse_copy_impl_2(first, sprout::prev(last), result, offset, args..., *sprout::prev(last))
					: reverse_copy_impl_3(result, args...)
					;
			}
			template<typename BidirectionalIterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type reverse_copy_impl_1(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename BidirectionalIterator, typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type reverse_copy_impl_1(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < static_cast<std::size_t>(offset)
					? reverse_copy_impl_1(first, last, result, offset, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)))
					: reverse_copy_impl_2(first, last, result, offset + sprout::size(result), args...)
					;
			}
			template<typename BidirectionalIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type reverse_copy_impl(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result
				)
			{
				return reverse_copy_impl_1(first, last, result, sprout::fixed_begin_offset(result));
			}
			template<typename BidirectionalIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type reverse_copy(
				BidirectionalIterator first,
				BidirectionalIterator last,
				Result const& result,
				void*
				)
			{
				return sprout::fixed::detail::reverse_copy_impl(
					first,
					last,
					result
					);
			}
		}	// namespace detail
		//
		// reverse_copy
		//
		template<typename BidirectionalIterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type reverse_copy(
			BidirectionalIterator first,
			BidirectionalIterator last,
			Result const& result
			)
		{
			typedef typename std::iterator_traits<BidirectionalIterator>::iterator_category* category;
			return sprout::fixed::detail::reverse_copy(
				first,
				last,
				result,
				category()
				);
		}
	}	// namespace fixed

	using sprout::fixed::reverse_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REVERSE_COPY_HPP
