#ifndef SPROUT_ALGORITHM_FIXED_REPLACE_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_REPLACE_COPY_HPP

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
			template<typename RandomAccessIterator, typename Result, typename T, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type replace_copy_impl_ra(
				RandomAccessIterator first,
				RandomAccessIterator last,
				Result const& result,
				sprout::index_tuple<Indexes...>,
				T const& old_value,
				T const& new_value,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				typename sprout::fixed_container_traits<Result>::size_type size,
				typename sprout::fixed_container_traits<Result>::size_type input_size
				)
			{
				return sprout::remake_clone<Result, Result>(
					result,
					sprout::size(result),
					(Indexes >= offset && Indexes < offset + size && Indexes < offset + input_size
						? *sprout::next(first, Indexes - offset) == old_value ? new_value : *sprout::next(first, Indexes - offset)
						: *sprout::next(sprout::fixed_begin(result), Indexes)
						)...
					);
			}
			template<typename RandomAccessIterator, typename Result, typename T>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type replace_copy(
				RandomAccessIterator first,
				RandomAccessIterator last,
				Result const& result,
				T const& old_value,
				T const& new_value,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::detail::replace_copy_impl_ra(
					first,
					last,
					result,
					typename sprout::index_range<0, sprout::fixed_container_traits<Result>::fixed_size>::type(),
					old_value,
					new_value,
					sprout::fixed_begin_offset(result),
					sprout::size(result),
					NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last)
					);
			}
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type replace_copy_impl_3(
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
			>::type replace_copy_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return replace_copy_impl_3(result, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)));
			}
			template<typename InputIterator, typename Result, typename T, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type replace_copy_impl_2(
				InputIterator first,
				InputIterator last,
				Result const& result,
				T const& old_value,
				T const& new_value,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename T, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type replace_copy_impl_2(
				InputIterator first,
				InputIterator last,
				Result const& result,
				T const& old_value,
				T const& new_value,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < static_cast<std::size_t>(offset)
					? replace_copy_impl_2(sprout::next(first), last, result, old_value, new_value, offset, args..., *first == old_value ? new_value : *first)
					: replace_copy_impl_3(result, args...)
					;
			}
			template<typename InputIterator, typename Result, typename T, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type replace_copy_impl_1(
				InputIterator first,
				InputIterator last,
				Result const& result,
				T const& old_value,
				T const& new_value,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename T, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type replace_copy_impl_1(
				InputIterator first,
				InputIterator last,
				Result const& result,
				T const& old_value,
				T const& new_value,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < static_cast<std::size_t>(offset)
					? replace_copy_impl_1(first, last, result, old_value, new_value, offset, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)))
					: replace_copy_impl_2(first, last, result, old_value, new_value, offset + sprout::size(result), args...)
					;
			}
			template<typename InputIterator, typename Result, typename T>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type replace_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				T const& old_value,
				T const& new_value
				)
			{
				return replace_copy_impl_1(first, last, result, old_value, new_value, sprout::fixed_begin_offset(result));
			}
			template<typename InputIterator, typename Result, typename T>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type replace_copy(
				InputIterator first,
				InputIterator last,
				Result const& result,
				T const& old_value,
				T const& new_value,
				void*
				)
			{
				return sprout::fixed::detail::replace_copy_impl(
					first,
					last,
					result,
					old_value,
					new_value
					);
			}
		}	// namespace detail
		//
		// replace_copy
		//
		template<typename InputIterator, typename Result, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type replace_copy(
			InputIterator first,
			InputIterator last,
			Result const& result,
			T const& old_value,
			T const& new_value
			)
		{
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::fixed::detail::replace_copy(
				first,
				last,
				result,
				old_value,
				new_value,
				category()
				);
		}
	}	// namespace fixed

	using sprout::fixed::replace_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REPLACE_COPY_HPP
