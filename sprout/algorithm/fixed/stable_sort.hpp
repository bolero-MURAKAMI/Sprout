#ifndef SPROUT_ALGORITHM_FIXED_STABLE_SORT_HPP
#define SPROUT_ALGORITHM_FIXED_STABLE_SORT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type stable_sort_impl_restart(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::size_type size,
				typename sprout::fixed_container_traits<Container>::value_type const& prev_value,
				Args const&... args
				);
			template<typename Container, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Container>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort_impl_synonym(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::size_type size,
				typename sprout::fixed_container_traits<Container>::const_iterator first,
				typename sprout::fixed_container_traits<Container>::const_iterator last,
				typename sprout::fixed_container_traits<Container>::value_type const& value,
				typename sprout::fixed_container_traits<Container>::size_type count,
				Args const&... args
				)
			{
				return sprout::remake_clone<Container, Container>(cont, sprout::size(cont), args...);
			}
			template<typename Container, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Container>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort_impl_synonym(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::size_type size,
				typename sprout::fixed_container_traits<Container>::const_iterator first,
				typename sprout::fixed_container_traits<Container>::const_iterator last,
				typename sprout::fixed_container_traits<Container>::value_type const& value,
				typename sprout::fixed_container_traits<Container>::size_type count,
				Args const&... args
				)
			{
				return first != last && count != 0
					? !comp(*first, value) && !comp(value, *first)
						? sprout::fixed::detail::stable_sort_impl_synonym(cont, comp, size, sprout::next(first), last, value, count - 1, args..., *first)
						: sprout::fixed::detail::stable_sort_impl_synonym(cont, comp, size, sprout::next(first), last, value, count, args...)
					: sprout::fixed::detail::stable_sort_impl_restart(cont, comp, size, value, args...)
					;
			}
			template<typename Container, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type stable_sort_impl_restart_1(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::size_type size,
				typename sprout::fixed_container_traits<Container>::const_iterator first,
				typename sprout::fixed_container_traits<Container>::const_iterator last,
				typename sprout::fixed_container_traits<Container>::value_type const& value,
				typename sprout::fixed_container_traits<Container>::size_type count,
				typename sprout::fixed_container_traits<Container>::const_iterator current,
				typename sprout::fixed_container_traits<Container>::value_type const& prev_value,
				Args const&... args
				)
			{
				return first != last
					? comp(prev_value, *first)
						? count == 0 || comp(*first, value)
							? sprout::fixed::detail::stable_sort_impl_restart_1(cont, comp, size, sprout::next(first), last, *first, 1, first, prev_value, args...)
							: comp(value, *first)
								? sprout::fixed::detail::stable_sort_impl_restart_1(cont, comp, size, sprout::next(first), last, value, count, current, prev_value, args...)
								: sprout::fixed::detail::stable_sort_impl_restart_1(cont, comp, size, sprout::next(first), last, value, count + 1, current, prev_value, args...)
						: sprout::fixed::detail::stable_sort_impl_restart_1(cont, comp, size, sprout::next(first), last, value, count, current, prev_value, args...)
					: sprout::fixed::detail::stable_sort_impl_synonym(cont, comp, size, sprout::next(current), last, value, count - 1, args..., value)
					;
			}
			template<typename Container, typename Compare, typename... Args>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type stable_sort_impl_restart(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::size_type size,
				typename sprout::fixed_container_traits<Container>::value_type const& prev_value,
				Args const&... args
				)
			{
				return sizeof...(Args) < size
					? sprout::fixed::detail::stable_sort_impl_restart_1(
						cont,
						comp,
						size,
						sprout::begin(cont),
						sprout::end(cont),
						*sprout::begin(cont),
						0,
						sprout::begin(cont),
						prev_value,
						args...
						)
					: sprout::detail::container_complate(cont, args...)
					;
			}
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type stable_sort_impl_1(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::size_type size,
				typename sprout::fixed_container_traits<Container>::const_iterator first,
				typename sprout::fixed_container_traits<Container>::const_iterator last,
				typename sprout::fixed_container_traits<Container>::value_type const& value,
				typename sprout::fixed_container_traits<Container>::size_type count,
				typename sprout::fixed_container_traits<Container>::const_iterator current
				)
			{
				return first != last
					? comp(*first, value)
						? sprout::fixed::detail::stable_sort_impl_1(cont, comp, size, sprout::next(first), last, *first, 1, first)
						: comp(value, *first)
							? sprout::fixed::detail::stable_sort_impl_1(cont, comp, size, sprout::next(first), last, value, count, current)
							: sprout::fixed::detail::stable_sort_impl_1(cont, comp, size, sprout::next(first), last, value, count + 1, current)
					: sprout::fixed::detail::stable_sort_impl_synonym(cont, comp, size, sprout::next(current), last, value, count - 1, value)
					;
			}
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type stable_sort_impl(
				Container const& cont,
				Compare comp,
				typename sprout::fixed_container_traits<Container>::size_type size
				)
			{
				return sprout::fixed::detail::stable_sort_impl_1(
					cont,
					comp,
					size,
					sprout::next(sprout::begin(cont)),
					sprout::end(cont),
					*sprout::begin(cont),
					1,
					sprout::begin(cont)
					);
			}
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::fixed_container_traits<Container>::fixed_size <= 1),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort(
				Container const& cont,
				Compare comp
				)
			{
				return sprout::clone(cont);
			}
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::fixed_container_traits<Container>::fixed_size > 1),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort(
				Container const& cont,
				Compare comp
				)
			{
				return sprout::fixed::detail::stable_sort_impl(
					cont,
					comp,
					sprout::size(cont)
					);
			}
			template<typename Container>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::fixed_container_traits<Container>::fixed_size <= 1),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort(
				Container const& cont
				)
			{
				return sprout::clone(cont);
			}
			template<typename Container>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::fixed_container_traits<Container>::fixed_size > 1),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort(
				Container const& cont
				)
			{
				return sprout::fixed::detail::stable_sort_impl(
					cont,
					NS_SSCRISK_CEL_OR_SPROUT_DETAIL::less<typename sprout::fixed_container_traits<Container>::value_type>(),
					sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// stable_sort
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type stable_sort(
			Container const& cont,
			Compare comp
			)
		{
			return sprout::fixed::detail::stable_sort(cont, comp);
		}
		//
		// stable_sort
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type stable_sort(
			Container const& cont
			)
		{
			return sprout::fixed::detail::stable_sort(cont);
		}
	}	// namespace fixed

	using sprout::fixed::stable_sort;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_STABLE_SORT_HPP
