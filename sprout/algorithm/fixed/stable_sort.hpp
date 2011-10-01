#ifndef SPROUT_ALGORITHM_FIXED_STABLE_SORT_HPP
#define SPROUT_ALGORITHM_FIXED_STABLE_SORT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Compare, std::ptrdiff_t I1, std::ptrdiff_t... Indexes, std::ptrdiff_t I2, std::ptrdiff_t... SortedIndexes, std::ptrdiff_t... NextIndexes, std::ptrdiff_t... PreIndexes, std::ptrdiff_t... PostIndexes>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sizeof...(Indexes) != 0 && sizeof...(SortedIndexes) != 0,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort_impl_4(
				Container const& cont,
				Compare comp,
				sprout::index_tuple<I1, Indexes...>,
				sprout::index_tuple<I2, SortedIndexes...>,
				sprout::index_tuple<NextIndexes...>,
				sprout::index_tuple<PreIndexes...>,
				sprout::index_tuple<PostIndexes...>
				);
			template<typename Container, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type stable_sort_impl_finish(
				Container const& cont,
				sprout::index_tuple<Indexes...>
				)
			{
				return sprout::remake_clone<Container, Container>(cont, sprout::size(cont), (*sprout::next(sprout::fixed_begin(cont), Indexes))...);
			}
			template<typename Container, typename Compare, std::ptrdiff_t I1, std::ptrdiff_t... Indexes, std::ptrdiff_t I2, std::ptrdiff_t... SortedIndexes, std::ptrdiff_t... NextIndexes, std::ptrdiff_t... PreIndexes, std::ptrdiff_t... PostIndexes>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sizeof...(Indexes) == 0 && sizeof...(SortedIndexes) == 0,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort_impl_4(
				Container const& cont,
				Compare comp,
				sprout::index_tuple<I1, Indexes...>,
				sprout::index_tuple<I2, SortedIndexes...>,
				sprout::index_tuple<NextIndexes...>,
				sprout::index_tuple<PreIndexes...>,
				sprout::index_tuple<PostIndexes...>
				)
			{
				return comp(*sprout::next(sprout::fixed_begin(cont), I1), *sprout::next(sprout::fixed_begin(cont), I2))
					? stable_sort_impl_finish(cont, sprout::index_tuple<PreIndexes..., NextIndexes..., I1, I2, SortedIndexes..., PostIndexes...>())
					: stable_sort_impl_finish(cont, sprout::index_tuple<PreIndexes..., NextIndexes..., I2, I1, SortedIndexes..., PostIndexes...>())
					;
			}
			template<typename Container, typename Compare, std::ptrdiff_t I1, std::ptrdiff_t... Indexes, std::ptrdiff_t I2, std::ptrdiff_t... SortedIndexes, std::ptrdiff_t... NextIndexes, std::ptrdiff_t... PreIndexes, std::ptrdiff_t... PostIndexes>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sizeof...(Indexes) == 0 && sizeof...(SortedIndexes) != 0,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort_impl_4(
				Container const& cont,
				Compare comp,
				sprout::index_tuple<I1, Indexes...>,
				sprout::index_tuple<I2, SortedIndexes...>,
				sprout::index_tuple<NextIndexes...>,
				sprout::index_tuple<PreIndexes...>,
				sprout::index_tuple<PostIndexes...>
				)
			{
				return comp(*sprout::next(sprout::fixed_begin(cont), I1), *sprout::next(sprout::fixed_begin(cont), I2))
					? stable_sort_impl_finish(cont, sprout::index_tuple<PreIndexes..., NextIndexes..., I1, I2, SortedIndexes..., PostIndexes...>())
					: stable_sort_impl_4(cont, comp, sprout::index_tuple<I1>(), sprout::index_tuple<SortedIndexes...>(), sprout::index_tuple<NextIndexes..., I2>(), sprout::index_tuple<PreIndexes...>(), sprout::index_tuple<PostIndexes...>())
					;
			}
			template<typename Container, typename Compare, std::ptrdiff_t I1, std::ptrdiff_t... Indexes, std::ptrdiff_t I2, std::ptrdiff_t... SortedIndexes, std::ptrdiff_t... NextIndexes, std::ptrdiff_t... PreIndexes, std::ptrdiff_t... PostIndexes>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sizeof...(Indexes) != 0 && sizeof...(SortedIndexes) == 0,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort_impl_4(
				Container const& cont,
				Compare comp,
				sprout::index_tuple<I1, Indexes...>,
				sprout::index_tuple<I2, SortedIndexes...>,
				sprout::index_tuple<NextIndexes...>,
				sprout::index_tuple<PreIndexes...>,
				sprout::index_tuple<PostIndexes...>
				)
			{
				return comp(*sprout::next(sprout::fixed_begin(cont), I1), *sprout::next(sprout::fixed_begin(cont), I2))
					? stable_sort_impl_4(cont, comp, sprout::index_tuple<Indexes...>(), sprout::index_tuple<NextIndexes..., I1, I2, SortedIndexes...>(), sprout::index_tuple<>(), sprout::index_tuple<PreIndexes...>(), sprout::index_tuple<PostIndexes...>())
					: stable_sort_impl_4(cont, comp, sprout::index_tuple<Indexes...>(), sprout::index_tuple<NextIndexes..., I2, I1, SortedIndexes...>(), sprout::index_tuple<>(), sprout::index_tuple<PreIndexes...>(), sprout::index_tuple<PostIndexes...>())
					;
			}
			template<typename Container, typename Compare, std::ptrdiff_t I1, std::ptrdiff_t... Indexes, std::ptrdiff_t I2, std::ptrdiff_t... SortedIndexes, std::ptrdiff_t... NextIndexes, std::ptrdiff_t... PreIndexes, std::ptrdiff_t... PostIndexes>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sizeof...(Indexes) != 0 && sizeof...(SortedIndexes) != 0,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort_impl_4(
				Container const& cont,
				Compare comp,
				sprout::index_tuple<I1, Indexes...>,
				sprout::index_tuple<I2, SortedIndexes...>,
				sprout::index_tuple<NextIndexes...>,
				sprout::index_tuple<PreIndexes...>,
				sprout::index_tuple<PostIndexes...>
				)
			{
				return comp(*sprout::next(sprout::fixed_begin(cont), I1), *sprout::next(sprout::fixed_begin(cont), I2))
					? stable_sort_impl_4(cont, comp, sprout::index_tuple<Indexes...>(), sprout::index_tuple<NextIndexes..., I1, I2, SortedIndexes...>(), sprout::index_tuple<>(), sprout::index_tuple<PreIndexes...>(), sprout::index_tuple<PostIndexes...>())
					: stable_sort_impl_4(cont, comp, sprout::index_tuple<I1, Indexes...>(), sprout::index_tuple<SortedIndexes...>(), sprout::index_tuple<NextIndexes..., I2>(), sprout::index_tuple<PreIndexes...>(), sprout::index_tuple<PostIndexes...>())
					;
			}
			template<typename Container, typename Compare, std::ptrdiff_t I, std::ptrdiff_t... Indexes, std::ptrdiff_t... PreIndexes, std::ptrdiff_t... PostIndexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type stable_sort_impl_3(
				Container const& cont,
				Compare comp,
				sprout::index_tuple<I, Indexes...>,
				sprout::index_tuple<PreIndexes...>,
				sprout::index_tuple<PostIndexes...>
				)
			{
				return stable_sort_impl_4(cont, comp, sprout::index_tuple<Indexes...>(), sprout::index_tuple<I>(), sprout::index_tuple<>(), sprout::index_tuple<PreIndexes...>(), sprout::index_tuple<PostIndexes...>());
			}
			template<typename Container, typename Compare, std::ptrdiff_t... Indexes, std::ptrdiff_t... PreIndexes, std::ptrdiff_t... PostIndexes>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sizeof...(Indexes) <= 1),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort_impl_2(
				Container const& cont,
				Compare comp,
				sprout::index_tuple<Indexes...>,
				sprout::index_tuple<PreIndexes...>,
				sprout::index_tuple<PostIndexes...>
				)
			{
				return stable_sort_impl_finish(cont, sprout::index_tuple<PreIndexes..., Indexes..., PostIndexes...>());
			}
			template<typename Container, typename Compare, std::ptrdiff_t... Indexes, std::ptrdiff_t... PreIndexes, std::ptrdiff_t... PostIndexes>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sizeof...(Indexes) > 1),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort_impl_2(
				Container const& cont,
				Compare comp,
				sprout::index_tuple<Indexes...>,
				sprout::index_tuple<PreIndexes...>,
				sprout::index_tuple<PostIndexes...>
				)
			{
				return stable_sort_impl_3(cont, comp, sprout::index_tuple<Indexes...>(), sprout::index_tuple<PreIndexes...>(), sprout::index_tuple<PostIndexes...>());
			}
			template<typename Container, typename Compare, std::ptrdiff_t I, std::ptrdiff_t... Indexes, std::ptrdiff_t... RangeIndexes, std::ptrdiff_t... PreIndexes, std::ptrdiff_t... PostIndexes>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sizeof...(Indexes) == 0,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort_impl_1(
				Container const& cont,
				Compare comp,
				sprout::index_tuple<I, Indexes...>,
				sprout::index_tuple<RangeIndexes...>,
				sprout::index_tuple<PreIndexes...>,
				sprout::index_tuple<PostIndexes...>
				)
			{
				return I < sprout::fixed_begin_offset(cont)
					? stable_sort_impl_2(cont, comp, sprout::index_tuple<RangeIndexes...>(), sprout::index_tuple<PreIndexes..., I>(), sprout::index_tuple<PostIndexes...>())
					: I >= sprout::fixed_end_offset(cont)
					? stable_sort_impl_2(cont, comp, sprout::index_tuple<RangeIndexes...>(), sprout::index_tuple<PreIndexes...>(), sprout::index_tuple<PostIndexes..., I>())
					: stable_sort_impl_2(cont, comp, sprout::index_tuple<RangeIndexes..., I>(), sprout::index_tuple<PreIndexes...>(), sprout::index_tuple<PostIndexes...>())
					;
			}
			template<typename Container, typename Compare, std::ptrdiff_t I, std::ptrdiff_t... Indexes, std::ptrdiff_t... RangeIndexes, std::ptrdiff_t... PreIndexes, std::ptrdiff_t... PostIndexes>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sizeof...(Indexes) != 0,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type stable_sort_impl_1(
				Container const& cont,
				Compare comp,
				sprout::index_tuple<I, Indexes...>,
				sprout::index_tuple<RangeIndexes...>,
				sprout::index_tuple<PreIndexes...>,
				sprout::index_tuple<PostIndexes...>
				)
			{
				return I < sprout::fixed_begin_offset(cont)
					? stable_sort_impl_1(cont, comp, sprout::index_tuple<Indexes...>(), sprout::index_tuple<RangeIndexes...>(), sprout::index_tuple<PreIndexes..., I>(), sprout::index_tuple<PostIndexes...>())
					: I >= sprout::fixed_end_offset(cont)
					? stable_sort_impl_1(cont, comp, sprout::index_tuple<Indexes...>(), sprout::index_tuple<RangeIndexes...>(), sprout::index_tuple<PreIndexes...>(), sprout::index_tuple<PostIndexes..., I>())
					: stable_sort_impl_1(cont, comp, sprout::index_tuple<Indexes...>(), sprout::index_tuple<RangeIndexes..., I>(), sprout::index_tuple<PreIndexes...>(), sprout::index_tuple<PostIndexes...>())
					;
			}
			template<typename Container, typename Compare, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type stable_sort_impl(
				Container const& cont,
				Compare comp,
				sprout::index_tuple<Indexes...>
				)
			{
				return stable_sort_impl_1(cont, comp, sprout::index_tuple<Indexes...>(), sprout::index_tuple<>(), sprout::index_tuple<>(), sprout::index_tuple<>());
			}
		}	// namespace detail
		//
		// stable_sort
		//
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
				typename sprout::index_range<0, sprout::fixed_container_traits<Container>::fixed_size>::type()
				);
		}
		//
		// stable_sort
		//
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
				typename sprout::index_range<0, sprout::fixed_container_traits<Container>::fixed_size>::type()
				);
		}
	}	// namespace fixed

	using sprout::fixed::stable_sort;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_STABLE_SORT_HPP
