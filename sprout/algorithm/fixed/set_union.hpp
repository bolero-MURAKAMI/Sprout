#ifndef SPROUT_ALGORITHM_FIXED_SET_UNION_HPP
#define SPROUT_ALGORITHM_FIXED_SET_UNION_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type set_union_impl_3(
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
			>::type set_union_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return set_union_impl_3(result, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)));
			}
			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type set_union_impl_2(
				InputIterator1 first1,
				InputIterator1 last1,
				InputIterator2 first2,
				InputIterator2 last2,
				Result const& result,
				Compare comp,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type set_union_impl_2(
				InputIterator1 first1,
				InputIterator1 last1,
				InputIterator2 first2,
				InputIterator2 last2,
				Result const& result,
				Compare comp,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < offset
					? first1 != last1
						? first2 != last2
							? comp(*first1, *first2)
								? set_union_impl_2(sprout::next(first1), last1, first2, last2, result, comp, offset, args..., *first1)
								: comp(*first2, *first1)
									? set_union_impl_2(first1, last1, sprout::next(first2), last2, result, comp, offset, args..., *first2)
									: set_union_impl_2(sprout::next(first1), last1, sprout::next(first2), last2, result, comp, offset, args..., *first1)
							: set_union_impl_2(sprout::next(first1), last1, first2, last2, result, comp, offset, args..., *first1)
						: first2 != last2
							? set_union_impl_2(first1, last1, sprout::next(first2), last2, result, comp, offset, args..., *first2)
							: set_union_impl_3(result, args...)
					: set_union_impl_3(result, args...)
					;
			}
			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type set_union_impl_1(
				InputIterator1 first1,
				InputIterator1 last1,
				InputIterator2 first2,
				InputIterator2 last2,
				Result const& result,
				Compare comp,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type set_union_impl_1(
				InputIterator1 first1,
				InputIterator1 last1,
				InputIterator2 first2,
				InputIterator2 last2,
				Result const& result,
				Compare comp,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < offset
					? set_union_impl_1(first1, last1, first2, last2, result, comp, offset, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)))
					: set_union_impl_2(first1, last1, first2, last2, result, comp, offset + sprout::size(result), args...)
					;
			}
			template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type set_union_impl(
				InputIterator1 first1,
				InputIterator1 last1,
				InputIterator2 first2,
				InputIterator2 last2,
				Result const& result,
				Compare comp
				)
			{
				return set_union_impl_1(first1, last1, first2, last2, result, comp, sprout::fixed_begin_offset(result));
			}
		}	// namespace detail
		//
		// set_union
		//
		template<typename InputIterator1, typename InputIterator2, typename Result, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type set_union(
			InputIterator1 first1,
			InputIterator1 last1,
			InputIterator2 first2,
			InputIterator2 last2,
			Result const& result,
			Compare comp
			)
		{
			return sprout::fixed::detail::set_union_impl(
				first1,
				last1,
				first2,
				last2,
				result,
				comp
				);
		}
		//
		// set_union
		//
		template<typename InputIterator1, typename InputIterator2, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type set_union(
			InputIterator1 first1,
			InputIterator1 last1,
			InputIterator2 first2,
			InputIterator2 last2,
			Result const& result
			)
		{
			return sprout::fixed::detail::set_union_impl(
				first1,
				last1,
				first2,
				last2,
				result,
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::less<typename sprout::fixed_container_traits<Result>::value_type>()
				);
		}
	}	// namespace fixed

	using sprout::fixed::set_union;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_SET_UNION_HPP
