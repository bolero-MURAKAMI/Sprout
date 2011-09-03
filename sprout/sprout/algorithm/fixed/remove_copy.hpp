#ifndef SPROUT_ALGORITHM_FIXED_REMOVE_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_REMOVE_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type remove_copy_impl_3(
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
			>::type remove_copy_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return remove_copy_impl_3(result, args..., *(sprout::fixed_begin(result) + sizeof...(Args)));
			}
			template<typename Iterator, typename Result, typename T, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type remove_copy_impl_2(
				Iterator first,
				Iterator last,
				Result const& result,
				T const& value,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename Iterator, typename Result, typename T, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type remove_copy_impl_2(
				Iterator first,
				Iterator last,
				Result const& result,
				T const& value,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < offset
					? *first == value
						? remove_copy_impl_2(first + 1, last, result, value, offset, args...)
						: remove_copy_impl_2(first + 1, last, result, value, offset, args..., *first)
					: remove_copy_impl_3(result, args...)
					;
			}
			template<typename Iterator, typename Result, typename T, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type remove_copy_impl_1(
				Iterator first,
				Iterator last,
				Result const& result,
				T const& value,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
			}
			template<typename Iterator, typename Result, typename T, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type remove_copy_impl_1(
				Iterator first,
				Iterator last,
				Result const& result,
				T const& value,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < offset
					? remove_copy_impl_1(first, last, result, value, offset, args..., *(sprout::fixed_begin(result) + sizeof...(Args)))
					: remove_copy_impl_2(first, last, result, value, offset + sprout::size(result), args...)
					;
			}
			template<typename Iterator, typename Result, typename T>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type remove_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				T const& value
				)
			{
				return remove_copy_impl_1(first, last, result, value, sprout::fixed_begin_offset(result));
			}
		}	// namespace detail
		//
		// remove_copy
		//
		template<typename Iterator, typename Result, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type remove_copy(
			Iterator first,
			Iterator last,
			Result const& result,
			T const& value
			)
		{
			return sprout::fixed::detail::remove_copy_impl(first, last, result, value);
		}
	}	// namespace fixed

	using sprout::fixed::remove_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REMOVE_COPY_HPP
