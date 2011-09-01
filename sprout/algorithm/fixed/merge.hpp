#ifndef SPROUT_ALGORITHM_FIXED_MERGE_HPP
#define SPROUT_ALGORITHM_FIXED_MERGE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type merge_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return typename sprout::fixed_container_traits<Result>::fixed_container_type{args...};
			}
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type merge_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return merge_impl_3(result, args..., *(sprout::fixed_begin(result) + sizeof...(Args)));
			}
			template<typename Iterator1, typename Iterator2, typename Result, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type merge_impl_2(
				Iterator1 first1,
				Iterator1 last1,
				Iterator2 first2,
				Iterator2 last2,
				Result const& result,
				Compare comp,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return typename sprout::fixed_container_traits<Result>::fixed_container_type{args...};
			}
			template<typename Iterator1, typename Iterator2, typename Result, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type merge_impl_2(
				Iterator1 first1,
				Iterator1 last1,
				Iterator2 first2,
				Iterator2 last2,
				Result const& result,
				Compare comp,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < offset
					? first1 != last1
						? first2 != last2
							? comp(*first2, *first1)
								? merge_impl_2(first1, last1, first2 + 1, last2, result, comp, offset, args..., *first2)
								: merge_impl_2(first1 + 1, last1, first2, last2, result, comp, offset, args..., *first1)
							: merge_impl_2(first1 + 1, last1, first2, last2, result, comp, offset, args..., *first1)
						: first2 != last2
							? merge_impl_2(first1, last1, first2 + 1, last2, result, comp, offset, args..., *first2)
							: merge_impl_3(result, args...)
					: merge_impl_3(result, args...)
					;
			}
			template<typename Iterator1, typename Iterator2, typename Result, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type merge_impl_1(
				Iterator1 first1,
				Iterator1 last1,
				Iterator2 first2,
				Iterator2 last2,
				Result const& result,
				Compare comp,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return typename sprout::fixed_container_traits<Result>::fixed_container_type{args...};
			}
			template<typename Iterator1, typename Iterator2, typename Result, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type merge_impl_1(
				Iterator1 first1,
				Iterator1 last1,
				Iterator2 first2,
				Iterator2 last2,
				Result const& result,
				Compare comp,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < offset
					? merge_impl_1(first1, last1, first2, last2, result, comp, offset, args..., *(sprout::fixed_begin(result) + sizeof...(Args)))
					: merge_impl_2(first1, last1, first2, last2, result, comp, offset + sprout::size(result), args...)
					;
			}
			template<typename Iterator1, typename Iterator2, typename Result, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type merge_impl(
				Iterator1 first1,
				Iterator1 last1,
				Iterator2 first2,
				Iterator2 last2,
				Result const& result,
				Compare comp
				)
			{
				return merge_impl_1(first1, last1, first2, last2, result, comp, sprout::fixed_begin_offset(result));
			}
		}	// namespace detail
		//
		// merge
		//
		template<typename Iterator1, typename Iterator2, typename Result, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type merge(
			Iterator1 first1,
			Iterator1 last1,
			Iterator2 first2,
			Iterator2 last2,
			Result const& result,
			Compare comp
			)
		{
			return sprout::fixed::detail::merge_impl(
				first1,
				last1,
				first2,
				last2,
				result,
				comp
				);
		}
		//
		// merge
		//
		template<typename Iterator1, typename Iterator2, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type merge(
			Iterator1 first1,
			Iterator1 last1,
			Iterator2 first2,
			Iterator2 last2,
			Result const& result
			)
		{
			return sprout::fixed::detail::merge_impl(
				first1,
				last1,
				first2,
				last2,
				result,
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::less<typename sprout::fixed_container_traits<Result>::value_type>()
				);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_MERGE_HPP
