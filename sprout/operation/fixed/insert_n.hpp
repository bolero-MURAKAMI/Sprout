#ifndef SPROUT_OPERATION_FIXED_INSERT_N_HPP
#define SPROUT_OPERATION_FIXED_INSERT_N_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/operation/fixed/insert.hpp>
#include <sprout/detail/param_at.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// insert_n
			//
			template<std::size_t N, typename Container, typename T, typename... Values>
			struct insert_n {
			public:
				typedef typename sprout::container_transform_traits<
					Container
				>::template rebind_size<
					sprout::container_traits<Container>::static_size + (1 + sizeof...(Values)) * N
				>::type type;
			};
		}	// namespace result_of

		namespace detail {
			template<std::size_t N, typename Result, typename Container, typename T, typename... Values, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR inline Result insert_n_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Container>::difference_type pos,
				T const& v,
				Values const&... values
				)
			{
				return sprout::remake<Result>(
					cont,
					sprout::size(cont) + (1 + sizeof...(Values)) * N,
					(Indexes < sprout::container_traits<Container>::static_size + (1 + sizeof...(Values)) * N
						? (Indexes < pos
							? *(sprout::internal_begin(cont) + Indexes)
							: Indexes < pos + (1 + sizeof...(Values)) * N
							? sprout::detail::param_at<typename sprout::container_traits<Result>::value_type>((Indexes - pos) % (1 + sizeof...(Values)), v, values...)
							: *sprout::next(sprout::internal_begin(cont), Indexes - (1 + sizeof...(Values)) * N)
							)
						: typename sprout::container_traits<Result>::value_type()
						)...
					);
			}
		}	// namespace detail
		//
		// insert_n
		//
		template<std::size_t N, typename Container, typename T, typename... Values>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::insert_n<N, Container, T, Values...>::type insert_n(
			Container const& cont,
			typename sprout::container_traits<Container>::const_iterator pos,
			T const& v,
			Values const&... values
			)
		{
			return sprout::fixed::detail::insert_n_impl<N, typename sprout::fixed::result_of::insert_n<N, Container, T, Values...>::type>(
				cont,
				typename sprout::index_range<0, sprout::container_traits<typename sprout::fixed::result_of::insert_n<N, Container, T, Values...>::type>::static_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::internal_begin(cont), pos),
				v,
				values...
				);
		}
		//
		// insert_n
		//
		template<std::size_t N, typename Container, typename T, typename... Values>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::insert_n<N, Container, T, Values...>::type insert_n(
			Container const& cont,
			typename sprout::container_traits<Container>::difference_type pos,
			T const& v,
			Values const&... values
			)
		{
			return sprout::fixed::detail::insert_n_impl<N, typename sprout::fixed::result_of::insert_n<N, Container, T, Values...>::type>(
				cont,
				typename sprout::index_range<0, sprout::container_traits<typename sprout::fixed::result_of::insert_n<N, Container, T, Values...>::type>::static_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::internal_begin(cont), sprout::next(sprout::begin(cont), pos)),
				v,
				values...
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::insert_n;
	}	// namespace result_of

	using sprout::fixed::insert_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_INSERT_N_HPP
