#ifndef SPROUT_UTILITY_PACK_HPP
#define SPROUT_UTILITY_PACK_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// tppack_at
	//
	namespace detail {
		template<std::size_t N, typename Head, typename... Tail>
		struct tppack_at_impl_1 {
		public:
			typedef typename sprout::detail::tppack_at_impl_1<N - 1, Tail...>::type type;
		};
		template<typename Head, typename... Tail>
		struct tppack_at_impl_1<0, Head, Tail...> {
		public:
			typedef Head type;
		};
		template<
			std::size_t N,
			typename... Args
		>
		struct tppack_at_impl
			: public sprout::detail::tppack_at_impl_1<N, Args...>
		{
			static_assert(N < sizeof...(Args), "N < sizeof...(Args)");
		};
	}	// namespace detail
	template<std::size_t N, typename... Args>
	struct tppack_at
		: public sprout::detail::tppack_at_impl<N, Args...>
	{};

	//
	// fppack_at
	//
	namespace detail {
		template<
			std::size_t N,
			typename R,
			typename Head,
			typename... Tail,
			typename sprout::enabler_if<N == 0>::type = sprout::enabler
		>
		SPROUT_CONSTEXPR R fppack_at_impl(Head&& head, Tail&&... tail) {
			return sprout::forward<Head>(head);
		}
		template<
			std::size_t N,
			typename R,
			typename Head,
			typename... Tail,
			typename sprout::enabler_if<N != 0>::type = sprout::enabler
		>
		SPROUT_CONSTEXPR R fppack_at_impl(Head&& head, Tail&&... tail) {
			return sprout::detail::fppack_at_impl<N - 1, R>(sprout::forward<Tail>(tail)...);
		}
	}	// namespace detail
	template<std::size_t N, typename... Args>
	SPROUT_CONSTEXPR typename sprout::tppack_at<N, Args&&...>::type fppack_at(Args&&... args) {
		return sprout::detail::fppack_at_impl<
			N,
			typename sprout::tppack_at<N, Args&&...>::type
		>(sprout::forward<Args>(args)...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PACK_HPP
