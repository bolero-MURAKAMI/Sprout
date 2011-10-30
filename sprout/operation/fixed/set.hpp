#ifndef SPROUT_OPERATION_FIXED_SET_HPP
#define SPROUT_OPERATION_FIXED_SET_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// set
			//
			template<typename Container, typename T>
			struct set {
			public:
				typedef typename sprout::fixed_container_traits<Container>::clone_type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Container, typename T, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline Result set_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Container>::difference_type pos,
				T const& v
				)
			{
				return sprout::remake_clone<Result>(
					cont,
					sprout::size(cont),
					(Indexes != pos
						? *sprout::next(sprout::fixed_begin(cont), Indexes)
						: v
						)...
					);
			}
		}	// namespace detail
		//
		// set
		//
		template<typename Container, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::set<Container, T>::type set(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::const_iterator pos,
			T const& v
			)
		{
			return sprout::fixed::detail::set_impl<typename sprout::fixed::result_of::set<Container, T>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::set<Container, T>::type>::fixed_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::fixed_begin(cont), pos),
				v
				);
		}
		//
		// set
		//
		template<typename Container, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::set<Container, T>::type set(
			Container const& cont,
			typename sprout::fixed_container_traits<Container>::difference_type pos,
			T const& v
			)
		{
			return sprout::fixed::detail::set_impl<typename sprout::fixed::result_of::set<Container, T>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::set<Container, T>::type>::fixed_size>::type(),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::fixed_begin(cont), sprout::next(sprout::begin(cont), pos)),
				v
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::set;
	}	// namespace result_of

	using sprout::fixed::set;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_SET_HPP
