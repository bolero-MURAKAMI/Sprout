#ifndef SPROUT_OPERATION_FIXED_INSERT_HPP
#define SPROUT_OPERATION_FIXED_INSERT_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/detail/param_at.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// insert
			//
			template<typename Container, typename T, typename... Values>
			struct insert {
			public:
				typedef typename sprout::rebind_fixed_size<
					typename sprout::fixed_container_traits<Container>::fixed_container_type
				>::template apply<
					sprout::fixed_container_traits<Container>::fixed_size + 1 + sizeof...(Values)
				>::type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Container, typename T, typename... Values, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline Result insert_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Container>::difference_type pos,
				T const& v,
				Values const&... values
				)
			{
				return Result{
					(Indexes < sprout::fixed_container_traits<Container>::fixed_size + 1 + sizeof...(Values)
						? (Indexes < pos
							? *(sprout::fixed_begin(cont) + Indexes)
							: Indexes < pos + 1 + sizeof...(Values)
							? sprout::detail::param_at<typename sprout::fixed_container_traits<Result>::value_type>(Indexes - pos, v, values...)
							: *(sprout::fixed_begin(cont) + Indexes - (1 + sizeof...(Values)))
							)
						: typename sprout::fixed_container_traits<Result>::value_type{}
						)...
					};
			}
		}	// namespace detail
		//
		// insert
		//
		template<typename Container, typename T, typename... Values>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::insert<Container, T, Values...>::type insert(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator pos,
			T const& v,
			Values const&... values
			)
		{
			return sprout::fixed::detail::insert_impl<typename sprout::fixed::result_of::insert<Container, T, Values...>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::insert<Container, T, Values...>::type>::fixed_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::fixed_begin(cont), pos),
				v,
				values...
				);
		}
		//
		// insert
		//
		template<typename Container, typename T, typename... Values>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::insert<Container, T, Values...>::type insert(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::difference_type pos,
			T const& v,
			Values const&... values
			)
		{
			return sprout::fixed::detail::insert_impl<typename sprout::fixed::result_of::insert<Container, T, Values...>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::insert<Container, T, Values...>::type>::fixed_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::fixed_begin(cont), sprout::begin(cont) + pos),
				v,
				values...
				);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_INSERT_HPP
