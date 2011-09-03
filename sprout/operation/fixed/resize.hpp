#ifndef SPROUT_OPERATION_FIXED_RESIZE_HPP
#define SPROUT_OPERATION_FIXED_RESIZE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// resize
			//
			template<std::size_t N, typename Container>
			struct resize {
			public:
				typedef typename sprout::rebind_fixed_size<
					Container
				>::template apply<
					N
				>::type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Container, typename T, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline Result resize_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Result>::difference_type size,
				T const& v
				)
			{
				return sprout::make_clone<Result>(
					(Indexes < size
						? *(sprout::begin(cont) + Indexes)
						: v
						)...
					);
			}
		}	// namespace detail
		//
		// resize
		//
		template<std::size_t N, typename Container, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::resize<N, Container>::type resize(
			Container const& cont,
			T const& v
			)
		{
			return sprout::fixed::detail::resize_impl<typename sprout::fixed::result_of::resize<N, Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::resize<N, Container>::type>::fixed_size>::type(),
				sprout::size(cont),
				v
				);
		}

		namespace detail {
			template<typename Result, typename Container, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline Result resize_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Result>::difference_type size
				)
			{
				return sprout::make_clone<Result>(
					(Indexes < size
						? *(sprout::begin(cont) + Indexes)
						: typename sprout::fixed_container_traits<Result>::value_type()
						)...
					);
			}
		}	// namespace detail
		//
		// resize
		//
		template<std::size_t N, typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::resize<N, Container>::type resize(
			Container const& cont
			)
		{
			return sprout::fixed::detail::resize_impl<typename sprout::fixed::result_of::resize<N, Container>::type>(
				cont, typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::resize<N, Container>::type>::fixed_size>::type(),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::resize;
	}	// namespace result_of

	using sprout::fixed::resize;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_RESIZE_HPP
