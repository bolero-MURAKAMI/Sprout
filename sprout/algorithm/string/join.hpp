#ifndef SPROUT_ALGORITHM_STRING_JOIN_HPP
#define SPROUT_ALGORITHM_STRING_JOIN_HPP

#include <cstddef>
#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace algorithm {
		namespace result_of {
			//
			// join
			//
			template<typename ContainerContainer>
			struct join {
			public:
				typedef typename sprout::container_transform_traits<
					typename sprout::container_traits<ContainerContainer>::value_type
				>::template rebind_size<
					sprout::container_traits<
						typename sprout::container_traits<ContainerContainer>::value_type
					>::static_size
					* sprout::container_traits<ContainerContainer>::static_size
				>::type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename ContainerInputIterator, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				Result
			>::type join_impl(
				ContainerInputIterator first_cont,
				ContainerInputIterator last_cont,
				Args const&... args
				);
			template<typename Result, typename ContainerInputIterator, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				Result
			>::type join_impl(
				ContainerInputIterator first_cont,
				ContainerInputIterator last_cont,
				Args const&... args
				);
			template<typename Result, typename ContainerInputIterator, typename InputIterator, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				Result
			>::type join_impl_1(
				ContainerInputIterator first_cont,
				ContainerInputIterator last_cont,
				InputIterator first,
				InputIterator last,
				Args const&... args
				)
			{
				return sprout::make<Result>(args...);
			}
			template<typename Result, typename ContainerInputIterator, typename InputIterator, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				Result
			>::type join_impl_1(
				ContainerInputIterator first_cont,
				ContainerInputIterator last_cont,
				InputIterator first,
				InputIterator last,
				Args const&... args
				)
			{
				return first != last
					? sprout::algorithm::detail::join_impl_1<Result>(first_cont, last_cont, sprout::next(first), last, args..., *first)
					: sprout::algorithm::detail::join_impl<Result>(sprout::next(first_cont), last_cont, args...)
					;
			}
			template<typename Result, typename ContainerInputIterator, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				Result
			>::type join_impl(
				ContainerInputIterator first_cont,
				ContainerInputIterator last_cont,
				Args const&... args
				)
			{
				return sprout::make<Result>(args...);
			}
			template<typename Result, typename ContainerInputIterator, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				Result
			>::type join_impl(
				ContainerInputIterator first_cont,
				ContainerInputIterator last_cont,
				Args const&... args
				)
			{
				return first_cont != last_cont
					? sprout::algorithm::detail::join_impl_1<Result>(first_cont, last_cont, sprout::begin(*first_cont), sprout::end(*first_cont), args...)
					: sprout::make<Result>(args...)
					;
			}
		}	// namespace detail
		//
		// join
		//
		template<typename ContainerContainer>
		SPROUT_CONSTEXPR inline typename sprout::algorithm::result_of::join<ContainerContainer>::type join(
			ContainerContainer const& cont_cont
			)
		{
			return sprout::algorithm::detail::join_impl<typename sprout::algorithm::result_of::join<ContainerContainer>::type>(
				sprout::begin(cont_cont),
				sprout::end(cont_cont)
				);
		}
	}	// namespace algorithm
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_STRING_JOIN_HPP
