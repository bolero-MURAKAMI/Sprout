#ifndef SPROUT_OPERATION_FIXED_SET_HPP
#define SPROUT_OPERATION_FIXED_SET_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// set
			//
			template<typename Container, typename T>
			struct set {
			public:
				typedef typename sprout::container_construct_traits<Container>::copied_type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Container, typename T, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR Result
			set_impl(
				Container const& cont, sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Container>::difference_type pos, T const& v
				)
			{
				return sprout::remake<Result>(
					cont,
					sprout::size(cont),
					(Indexes != pos
						? *sprout::next(sprout::internal_begin(cont), Indexes)
						: v
						)...
					);
			}
		}	// namespace detail
		//
		// set
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::set<Container, T>::type
		set(Container const& cont, typename sprout::container_traits<Container>::const_iterator pos, T const& v) {
			return sprout::fixed::detail::set_impl<typename sprout::fixed::result_of::set<Container, T>::type>(
				cont,
				sprout::index_range<
					0,
					sprout::container_traits<typename sprout::fixed::result_of::set<Container, T>::type>::static_size
					>::make(),
				NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::internal_begin(cont), pos),
				v
				);
		}
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::set<Container, T>::type
		set(Container const& cont, typename sprout::container_traits<Container>::difference_type pos, T const& v) {
			return sprout::fixed::detail::set_impl<typename sprout::fixed::result_of::set<Container, T>::type>(
				cont,
				sprout::index_range<
					0,
					sprout::container_traits<typename sprout::fixed::result_of::set<Container, T>::type>::static_size
					>::make(),
				NS_SSCRISK_CEL_OR_SPROUT::distance(sprout::internal_begin(cont), sprout::next(sprout::begin(cont), pos)),
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
