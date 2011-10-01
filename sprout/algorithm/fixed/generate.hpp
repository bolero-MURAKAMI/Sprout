#ifndef SPROUT_ALGORITHM_FIXED_GENERATE_HPP
#define SPROUT_ALGORITHM_FIXED_GENERATE_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<std::size_t InitSize, typename Container, typename Generator, typename Head, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				InitSize == sizeof...(Args) + 1,
				typename sprout::fixed_container_traits<Container>::value_type
			>::type call_gen(
				Generator gen,
				Head const& head,
				Args const&... args
				)
			{
				return gen(head, args...);
			}
			template<std::size_t InitSize, typename Container, typename Generator, typename Head, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				InitSize != sizeof...(Args) + 1,
				typename sprout::fixed_container_traits<Container>::value_type
			>::type call_gen(
				Generator gen,
				Head const& head,
				Args const&... args
				)
			{
				return call_gen<InitSize, Container>(gen, args...);
			}
			template<typename Container, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Container>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl_4(
				Container const& cont,
				Args const&... args
				)
			{
				return sprout::remake_clone<Container, Container>(cont, sprout::size(cont), args...);
			}
			template<typename Container, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Container>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl_4(
				Container const& cont,
				Args const&... args
				)
			{
				return generate_impl_4(cont, args..., *sprout::next(sprout::fixed_begin(cont), sizeof...(Args)));
			}
			template<std::size_t InitSize, typename Container, typename Generator, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Container>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl_3(
				Container const& cont,
				Generator gen,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				Args const&... args
				)
			{
				return sprout::remake_clone<Container, Container>(cont, sprout::size(cont), args...);
			}
			template<std::size_t InitSize, typename Container, typename Generator, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Container>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl_3(
				Container const& cont,
				Generator gen,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < offset
					? generate_impl_3<InitSize>(cont, gen, offset, args..., call_gen<InitSize, Container>(gen, args...))
					: generate_impl_4(cont, args...)
					;
			}
			template<typename Container, typename Head, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sizeof...(Args) == 0,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl_2_drop(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::size_type dropped_size,
				Head const& head,
				Args const&... args
				)
			{
				return sprout::remake_clone<Container, Container>(cont, sprout::size(cont), args...);
			}
			template<typename Container, typename Head, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sizeof...(Args) != 0,
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl_2_drop(
				Container const& cont,
				typename sprout::fixed_container_traits<Container>::size_type dropped_size,
				Head const& head,
				Args const&... args
				)
			{
				return sizeof...(Args) + 1 != dropped_size
					? generate_impl_2_drop(cont, dropped_size, args...)
					: generate_impl_4(cont, head, args...)
					;
			}
			template<std::size_t InitSize, typename Container, typename Generator, typename Head, typename... Args>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type generate_impl_2(
				Container const& cont,
				Generator gen,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::size_type size,
				std::size_t remain,
				Head const& head,
				Args const&... args
				)
			{
				return InitSize - remain != size
					? (remain > 1
						? generate_impl_2<InitSize>(cont, gen, offset, size, remain - 1, args..., head)
						: generate_impl_3<InitSize>(cont, gen, offset + size, args..., head)
						)
					: generate_impl_2_drop(cont, offset + size, head, args...)
					;
			}
			template<std::size_t InitSize, typename Container, typename Generator, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Container>::fixed_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl_1(
				Container const& cont,
				Generator gen,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::size_type size,
				Args const&... args
				)
			{
				return generate_impl_2<InitSize>(cont, gen, offset, size, InitSize, args...);
			}
			template<std::size_t InitSize, typename Container, typename Generator, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Container>::fixed_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl_1(
				Container const& cont,
				Generator gen,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::size_type size,
				Args const&... args
				)
			{
				return sizeof...(Args) - InitSize < offset
					? generate_impl_1<InitSize>(cont, gen, offset, size, args..., *sprout::next(sprout::fixed_begin(cont), sizeof...(Args) - InitSize))
					: generate_impl_2<InitSize>(cont, gen, offset, size, InitSize, args...)
					;
			}
			template<typename Container, typename Generator, typename... Inits>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type generate_impl(
				Container const& cont,
				Generator gen,
				typename sprout::fixed_container_traits<Container>::size_type size,
				Inits const&... inits
				)
			{
				return generate_impl_1<sizeof...(Inits)>(cont, gen, sprout::fixed_begin_offset(cont), size, inits...);
			}
		}	// namespace detail
		//
		// generate
		//
		template<typename Container, typename Generator, typename... Inits>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type generate(
			Container const& cont,
			Generator gen,
			Inits const&... inits
			)
		{
			return sprout::fixed::detail::generate_impl(cont, gen, sprout::size(cont), inits...);
		}
	}	// namespace fixed

	using sprout::fixed::generate;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_GENERATE_HPP
