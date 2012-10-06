#ifndef SPROUT_OPERATION_FIXED_INSERT_HPP
#define SPROUT_OPERATION_FIXED_INSERT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/detail/param_at.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// insert
			//
			template<typename Container, typename T, typename... Values>
			struct insert {
			public:
				typedef typename sprout::container_transform_traits<
					Container
				>::template rebind_size<
					sprout::container_traits<Container>::static_size + 1 + sizeof...(Values)
				>::type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Container, typename T, typename... Values, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result
			insert_impl(
				Container const& cont, sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Container>::difference_type pos, T const& v, Values const&... values
				)
			{
				return sprout::remake<Result>(
					cont,
					sprout::size(cont) + 1 + sizeof...(Values),
					(Indexes < sprout::container_traits<Container>::static_size + 1 + sizeof...(Values)
						? (Indexes < pos
							? *sprout::next(sprout::internal_begin(cont), Indexes)
							: Indexes < pos + 1 + sizeof...(Values)
							? sprout::detail::param_at<typename sprout::container_traits<Result>::value_type>(Indexes - pos, v, values...)
							: *sprout::next(sprout::internal_begin(cont), Indexes - (1 + sizeof...(Values)))
							)
						: typename sprout::container_traits<Result>::value_type()
						)...
					);
			}
		}	// namespace detail
		//
		// insert
		//
		template<typename Container, typename T, typename... Values>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::insert<Container, T, Values...>::type
		insert(
			Container const& cont, typename sprout::container_traits<Container>::const_iterator pos,
			T const& v, Values const&... values
			)
		{
			return sprout::fixed::detail::insert_impl<typename sprout::fixed::result_of::insert<Container, T, Values...>::type>(
				cont,
				sprout::index_range<
					0,
					sprout::container_traits<typename sprout::fixed::result_of::insert<Container, T, Values...>::type>::static_size
					>::make(),
				NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::internal_begin(cont), pos),
				v,
				values...
				);
		}
		template<typename Container, typename T, typename... Values>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::insert<Container, T, Values...>::type
		insert(
			Container const& cont, typename sprout::container_traits<Container>::difference_type pos,
			T const& v, Values const&... values
			)
		{
			return sprout::fixed::detail::insert_impl<typename sprout::fixed::result_of::insert<Container, T, Values...>::type>(
				cont,
				sprout::index_range<
					0,
					sprout::container_traits<typename sprout::fixed::result_of::insert<Container, T, Values...>::type>::static_size
					>::make(),
				NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::internal_begin(cont), sprout::next(sprout::begin(cont), pos)),
				v,
				values...
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::insert;
	}	// namespace result_of

	using sprout::fixed::insert;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_INSERT_HPP
