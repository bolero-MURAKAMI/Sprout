/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_STRING_JOIN_HPP
#define SPROUT_ALGORITHM_STRING_JOIN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/range/adaptor/size_enumed.hpp>
#include <sprout/range/algorithm/lower_bound.hpp>
#include <sprout/range/numeric/fixed/partial_sum.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/is_c_str.hpp>

namespace sprout {
	namespace algorithm {
		namespace detail {
			template<typename String, typename = void>
			struct string_size;
			template<typename String>
			struct string_size<
				String,
				typename std::enable_if<sprout::is_c_str<String>::value>::type
			>
				: public sprout::integral_constant<
					typename sprout::container_traits<String>::size_type,
					sprout::container_traits<String>::static_size - 1
				>
			{};
			template<typename String>
			struct string_size<
				String,
				typename std::enable_if<!sprout::is_c_str<String>::value>::type
			>
				: public sprout::integral_constant<
					typename sprout::container_traits<String>::size_type,
					sprout::container_traits<String>::static_size
				>
			{};

			template<typename String>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_c_str<String>::value,
				typename sprout::container_traits<String>::difference_type
			>::type
			str_size(String const& str) {
				return sprout::size(str) - 1;
			}
			template<typename String>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_c_str<String>::value,
				typename sprout::container_traits<String>::difference_type
			>::type
			str_size(String const& str) {
				return sprout::size(str);
			}
		}	// namespace detail

		namespace results {
			//
			// join
			//
			template<typename ContainerContainer, typename Separator = void>
			struct join
				: public sprout::container_transform_traits<
					typename sprout::container_traits<ContainerContainer>::value_type
				>::template rebind_size<
					sprout::container_traits<
						typename sprout::container_traits<ContainerContainer>::value_type
					>::static_size
						? (sprout::container_traits<
								typename sprout::container_traits<ContainerContainer>::value_type
							>::static_size
							+ sprout::algorithm::detail::string_size<Separator>::value
							)
							* sprout::container_traits<ContainerContainer>::static_size
							- sprout::algorithm::detail::string_size<Separator>::value
						: 0
				>
			{};
			template<typename ContainerContainer>
			struct join<ContainerContainer, void>
				: public sprout::container_transform_traits<
					typename sprout::container_traits<ContainerContainer>::value_type
				>::template rebind_size<
					sprout::container_traits<
						typename sprout::container_traits<ContainerContainer>::value_type
					>::static_size
					* sprout::container_traits<ContainerContainer>::static_size
				>
			{};
		}	// namespace results

		namespace detail {
			template<typename Result, typename ContIterator, typename SizeIterator, typename Sizes>
			inline SPROUT_CONSTEXPR typename sprout::container_traits<Result>::value_type
			join_impl_ra_2(
				ContIterator const& first_cont,
				SizeIterator const& found,
				Sizes const& sizes,
				sprout::index_t idx
				)
			{
				typedef typename sprout::container_traits<Result>::value_type value_type;
				return found == sizes.end() ? value_type()
					: sprout::begin(first_cont[found - sizes.begin()])[idx - (found != sizes.begin() ? found[-1] : 0)]
					;
			}
			template<typename Result, typename ContIterator, sprout::index_t... Indexes, typename Sizes>
			inline SPROUT_CONSTEXPR Result
			join_impl_ra_1(
				ContIterator const& first_cont,
				sprout::index_tuple<Indexes...>,
				Sizes const& sizes
				)
			{
				return sprout::make<Result>(
					sprout::algorithm::detail::join_impl_ra_2<Result>(
						first_cont,
						sprout::range::lower_bound(sizes, Indexes + 1),
						sizes,
						Indexes
						)...
					);
			}
			template<typename Result, typename ContainerContainer>
			inline SPROUT_CONSTEXPR Result
			join_impl_ra(ContainerContainer const& cont_cont) {
				typedef typename sprout::container_traits<Result>::difference_type size_type;
				typedef sprout::array<
					size_type,
					sprout::container_traits<ContainerContainer>::static_size
				> sizes_type;
				return sprout::algorithm::detail::join_impl_ra_1<Result>(
					sprout::begin(cont_cont),
					sprout::container_indexes<Result>::make(),
					sprout::range::fixed::partial_sum(
						cont_cont | sprout::adaptors::size_enumed,
						sprout::pit<sizes_type>()
						)
					);
			}

			template<typename Result, typename ContIterator, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				Result
			>::type join_impl(
				ContIterator const& first_cont, ContIterator const& last_cont,
				Args const&... args
				);
			template<typename Result, typename ContIterator, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				Result
			>::type join_impl(
				ContIterator const& first_cont, ContIterator const& last_cont,
				Args const&... args
				);
			template<typename Result, typename ContIterator, typename InputIterator, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				Result
			>::type join_impl_1(
				ContIterator, ContIterator,
				InputIterator const&, InputIterator const&,
				Args const&... args
				)
			{
				return sprout::make<Result>(args...);
			}
			template<typename Result, typename ContIterator, typename InputIterator, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				Result
			>::type join_impl_1(
				ContIterator const& first_cont, ContIterator const& last_cont,
				InputIterator const& first, InputIterator const& last,
				Args const&... args
				)
			{
				return first != last
					? sprout::algorithm::detail::join_impl_1<Result>(
						first_cont, last_cont,
						sprout::next(first), last,
						args..., *first
						)
					: sprout::algorithm::detail::join_impl<Result>(sprout::next(first_cont), last_cont, args...)
					;
			}
			template<typename Result, typename ContIterator, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				Result
			>::type join_impl(
				ContIterator, ContIterator,
				Args const&... args
				)
			{
				return sprout::make<Result>(args...);
			}
			template<typename Result, typename ContIterator, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				Result
			>::type join_impl(
				ContIterator const& first_cont, ContIterator const& last_cont,
				Args const&... args
				)
			{
				return first_cont != last_cont
					? sprout::algorithm::detail::join_impl_1<Result>(
						first_cont, last_cont,
						sprout::begin(*first_cont), sprout::end(*first_cont),
						args...
						)
					: sprout::make<Result>(args...)
					;
			}

			template<typename ContainerContainer>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_random_access_iterator<
					typename sprout::container_traits<ContainerContainer const>::iterator
				>::value
					&& sprout::is_random_access_iterator<
						typename sprout::container_traits<
							typename sprout::container_traits<ContainerContainer const>::value_type
						>::iterator
					>::value
					,
				typename sprout::algorithm::results::join<ContainerContainer>::type
			>::type
			join(ContainerContainer const& cont_cont) {
				typedef typename sprout::algorithm::results::join<ContainerContainer>::type result_type;
				return sprout::algorithm::detail::join_impl_ra<result_type>(cont_cont);
			}
			template<typename ContainerContainer>
			inline SPROUT_CONSTEXPR typename std::enable_if<!(
				sprout::is_random_access_iterator<
					typename sprout::container_traits<ContainerContainer const>::iterator
				>::value
					&& sprout::is_random_access_iterator<
						typename sprout::container_traits<
							typename sprout::container_traits<ContainerContainer const>::value_type
						>::iterator
					>::value
					),
				typename sprout::algorithm::results::join<ContainerContainer>::type
			>::type
			join(ContainerContainer const& cont_cont) {
				typedef typename sprout::algorithm::results::join<ContainerContainer>::type result_type;
				return sprout::algorithm::detail::join_impl<result_type>(
					sprout::begin(cont_cont),
					sprout::end(cont_cont)
					);
			}
		}	// namespace detail
		//
		// join
		//
		template<typename ContainerContainer>
		inline SPROUT_CONSTEXPR typename sprout::algorithm::results::join<ContainerContainer>::type
		join(ContainerContainer const& cont_cont) {
			return sprout::algorithm::detail::join(cont_cont);
		}

		namespace detail {
			template<typename Result, typename ContIterator, typename SepIterator, typename SizeIterator, typename Sizes>
			inline SPROUT_CONSTEXPR typename sprout::container_traits<Result>::value_type
			join_impl_ra_2(
				ContIterator const& first_cont, SepIterator const& first,
				SizeIterator const& found,
				Sizes const& sizes,
				sprout::index_t idx
				)
			{
				typedef typename sprout::container_traits<Result>::value_type value_type;
				return found == sizes.end() ? value_type()
					: (found - sizes.begin()) % 2 ? first[idx - found[-1]]
					: sprout::begin(first_cont[(found - sizes.begin()) / 2])[idx - (found != sizes.begin() ? found[-1] : 0)]
					;
			}
			template<typename Result, typename ContIterator, typename SepIterator, sprout::index_t... Indexes, typename Sizes>
			inline SPROUT_CONSTEXPR Result
			join_impl_ra_1(
				ContIterator const& first_cont,
				SepIterator const& first,
				sprout::index_tuple<Indexes...>,
				Sizes const& sizes
				)
			{
				return sprout::make<Result>(
					sprout::algorithm::detail::join_impl_ra_2<Result>(
						first_cont,
						first,
						sprout::range::lower_bound(sizes, Indexes + 1),
						sizes,
						Indexes
						)...
					);
			}
			template<typename Result, typename ContainerContainer, typename Separator>
			inline SPROUT_CONSTEXPR Result
			join_impl_ra(ContainerContainer const& cont_cont, Separator const& separator) {
				typedef typename sprout::container_traits<Result>::difference_type size_type;
				typedef sprout::array<
					size_type,
					sprout::container_traits<ContainerContainer>::static_size
						? sprout::container_traits<ContainerContainer>::static_size * 2 - 1
						: 0
				> sizes_type;
				return sprout::algorithm::detail::join_impl_ra_1<Result>(
					sprout::begin(cont_cont),
					sprout::begin(separator),
					sprout::container_indexes<Result>::make(),
					sprout::range::fixed::partial_sum(
						cont_cont | sprout::adaptors::size_enumed(sprout::algorithm::detail::str_size(separator), true),
						sprout::pit<sizes_type>()
						)
					);
			}

			template<typename Result, typename ContIterator, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				Result
			>::type join_impl(
				ContIterator const& first_cont, ContIterator const& last_cont,
				Args const&... args
				);
			template<typename Result, typename ContIterator, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				Result
			>::type join_impl(
				ContIterator const& first_cont, ContIterator const& last_cont,
				Args const&... args
				);
			template<typename Result, typename ContIterator, typename SepIterator, typename InputIterator, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				Result
			>::type join_impl_1(
				ContIterator, ContIterator,
				SepIterator, SepIterator,
				bool,
				InputIterator const&, InputIterator const&,
				Args const&... args
				)
			{
				return sprout::make<Result>(args...);
			}
			template<typename Result, typename ContIterator, typename SepIterator, typename InputIterator, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				Result
			>::type join_impl_1(
				ContIterator const& first_cont, ContIterator const& last_cont,
				SepIterator const& sep_first, SepIterator const& sep_last,
				bool sep,
				InputIterator const& first, InputIterator const& last,
				Args const&... args
				)
			{
				return first != last
					? sprout::algorithm::detail::join_impl_1<Result>(
						first_cont, last_cont,
						sep_first, sep_last,
						sep,
						sprout::next(first), last,
						args..., *first
						)
					: sep
						? sprout::algorithm::detail::join_impl<Result>(
							sprout::next(first_cont), last_cont,
							sep_first, sep_last,
							false,
							args...
							)
						: sprout::algorithm::detail::join_impl<Result>(
							first_cont, last_cont,
							sep_first, sep_last,
							true,
							args...
							)
					;
			}
			template<typename Result, typename ContIterator, typename SepIterator, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				Result
			>::type join_impl(
				ContIterator, ContIterator,
				SepIterator, SepIterator,
				bool,
				Args const&... args
				)
			{
				return sprout::make<Result>(args...);
			}
			template<typename Result, typename ContIterator, typename SepIterator, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				Result
			>::type join_impl(
				ContIterator const& first_cont, ContIterator const& last_cont,
				SepIterator const& sep_first, SepIterator const& sep_last,
				bool sep,
				Args const&... args
				)
			{
				return first_cont != last_cont
					? sep
						? sprout::algorithm::detail::join_impl_1<Result>(
							first_cont, last_cont,
							sep_first, sep_last,
							sep,
							sep_first, sep_last,
							args...
							)
						: sprout::algorithm::detail::join_impl_1<Result>(
							first_cont, last_cont,
							sep_first, sep_last,
							sep,
							sprout::begin(*first_cont), sprout::end(*first_cont),
							args...
							)
					: sprout::make<Result>(args...)
					;
			}

			template<typename ContainerContainer, typename Separator>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_random_access_iterator<
					typename sprout::container_traits<ContainerContainer const>::iterator
				>::value
					&& sprout::is_random_access_iterator<
						typename sprout::container_traits<
							typename sprout::container_traits<ContainerContainer const>::value_type
						>::iterator
					>::value
					&& sprout::is_random_access_iterator<
						typename sprout::container_traits<Separator const>::iterator
					>::value
					,
				typename sprout::algorithm::results::join<ContainerContainer, Separator>::type
			>::type
			join(ContainerContainer const& cont_cont, Separator const& separator) {
				typedef typename sprout::algorithm::results::join<ContainerContainer, Separator>::type result_type;
				return sprout::algorithm::detail::join_impl_ra<result_type>(cont_cont, separator);
			}
			template<typename ContainerContainer, typename Separator>
			inline SPROUT_CONSTEXPR typename std::enable_if<!(
				sprout::is_random_access_iterator<
					typename sprout::container_traits<ContainerContainer const>::iterator
				>::value
					&& sprout::is_random_access_iterator<
						typename sprout::container_traits<
							typename sprout::container_traits<ContainerContainer const>::value_type
						>::iterator
					>::value
					&& sprout::is_random_access_iterator<
						typename sprout::container_traits<Separator const>::iterator
					>::value
					),
				typename sprout::algorithm::results::join<ContainerContainer, Separator>::type
			>::type
			join(ContainerContainer const& cont_cont, Separator const& separator) {
				typedef typename sprout::algorithm::results::join<ContainerContainer, Separator>::type result_type;
				return sprout::algorithm::detail::join_impl<result_type>(
					sprout::begin(cont_cont),
					sprout::end(cont_cont),
					sprout::begin(separator),
					sprout::end(separator),
					false
					);
			}
		}	// namespace detail
		//
		// join
		//
		template<typename ContainerContainer, typename Separator>
		inline SPROUT_CONSTEXPR typename sprout::algorithm::results::join<ContainerContainer, Separator>::type
		join(ContainerContainer const& cont_cont, Separator const& separator) {
			return sprout::algorithm::detail::join(cont_cont, separator);
		}
	}	// namespace algorithm
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_STRING_JOIN_HPP
