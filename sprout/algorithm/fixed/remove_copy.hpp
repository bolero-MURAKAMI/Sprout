#ifndef SPROUT_ALGORITHM_FIXED_REMOVE_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_REMOVE_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/remove_iterator.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/pit.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator, typename Result, typename T, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			remove_copy_impl(
				InputIterator first, InputIterator last,
				Result const& result, T const& value,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename T, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			remove_copy_impl(
				InputIterator first, InputIterator last,
				Result const& result, T const& value,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? *first == value
						? sprout::fixed::detail::remove_copy_impl(sprout::next(first), last, result, value, size, args...)
						: sprout::fixed::detail::remove_copy_impl(sprout::next(first), last, result, value, size, args..., *first)
					: sprout::detail::container_complate(result, args...)
					;
			}

			template<typename InputIterator, typename Result, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			remove_copy(InputIterator first, InputIterator last, Result const& result, T const& value) {
				return sprout::fixed::detail::remove_copy_impl(first, last, result, value, sprout::size(result));
			}

			template<typename InputIterator, typename Result, typename T>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			remove_copy(InputIterator first, InputIterator last, Result const& result, T const& value) {
				return sprout::remake<Result>(
					result, sprout::size(result),
					sprout::make_remove_iterator(value, first, last),
					sprout::make_remove_iterator(value, last, last)
					);
			}
		}	// namespace detail
		//
		// remove_copy
		//
		template<typename InputIterator, typename Result, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		remove_copy(InputIterator first, InputIterator last, Result const& result, T const& value) {
			return sprout::fixed::detail::remove_copy(first, last, result, value);
		}

		template<typename Result, typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		remove_copy(InputIterator first, InputIterator last, T const& value) {
			return sprout::fixed::remove_copy(first, last, sprout::pit<Result>(), value);
		}
	}	// namespace fixed

	using sprout::fixed::remove_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REMOVE_COPY_HPP
