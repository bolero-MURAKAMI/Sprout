#ifndef SPROUT_OPERATION_FIXED_RESIZE_BACKWARD_HPP
#define SPROUT_OPERATION_FIXED_RESIZE_BACKWARD_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/operation/fixed/resize.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// resize_backward
			//
			template<std::size_t N, typename Container>
			struct resize_backward
				: public sprout::fixed::result_of::resize<N, Container>
			{};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Container, typename T, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR inline Result resize_backward_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Result>::difference_type size,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				T const& v
				)
			{
				return sprout::make_clone<Result>(
					(Indexes >= offset && Indexes < offset + size
						? *sprout::next(sprout::begin(cont), Indexes - offset)
						: v
						)...
					);
			}
		}	// namespace detail
		//
		// resize_backward
		//
		template<std::size_t N, typename Container, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::resize_backward<N, Container>::type resize_backward(
			Container const& cont,
			T const& v
			)
		{
			return sprout::fixed::detail::resize_backward_impl<typename sprout::fixed::result_of::resize_backward<N, Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::resize_backward<N, Container>::type>::fixed_size>::type(),
				sprout::size(cont),
				static_cast<typename sprout::fixed_container_traits<Container>::difference_type>(
					sprout::fixed_container_traits<typename sprout::fixed::result_of::resize_backward<N, Container>::type>::fixed_size
					)
					- sprout::size(cont),
				v
				);
		}

		namespace detail {
			template<typename Result, typename Container, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR inline Result resize_backward_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Result>::difference_type size,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::make_clone<Result>(
					(Indexes >= offset && Indexes < offset + size
						? *sprout::next(sprout::begin(cont), Indexes - offset)
						: typename sprout::fixed_container_traits<Result>::value_type()
						)...
					);
			}
		}	// namespace detail
		//
		// resize_backward
		//
		template<std::size_t N, typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::resize_backward<N, Container>::type resize_backward(
			Container const& cont
			)
		{
			return sprout::fixed::detail::resize_backward_impl<typename sprout::fixed::result_of::resize_backward<N, Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::resize_backward<N, Container>::type>::fixed_size>::type(),
				sprout::size(cont),
				static_cast<typename sprout::fixed_container_traits<Container>::difference_type>(
					sprout::fixed_container_traits<typename sprout::fixed::result_of::resize_backward<N, Container>::type>::fixed_size
					)
					- sprout::size(cont)
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::resize_backward;
	}	// namespace result_of

	using sprout::fixed::resize_backward;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_RESIZE_BACKWARD_HPP
