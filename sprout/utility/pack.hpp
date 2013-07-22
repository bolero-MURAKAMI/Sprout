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
		template<std::size_t I, typename Head, typename... Tail>
		struct tppack_at_impl_1
			: public sprout::detail::tppack_at_impl_1<I - 1, Tail...>
		{};
		template<typename Head, typename... Tail>
		struct tppack_at_impl_1<0, Head, Tail...> {
		public:
			typedef Head type;
		};
		template<std::size_t I, typename... Args>
		struct tppack_at_impl
			: public sprout::detail::tppack_at_impl_1<I, Args...>
		{
			static_assert(I < sizeof...(Args), "I < sizeof...(Args)");
		};
	}	// namespace detail
	template<std::size_t I, typename... Args>
	struct tppack_at
		: public sprout::detail::tppack_at_impl<I, Args...>
	{};

	//
	// tppack_c_at
	//
	template<std::size_t I, typename T, T... Args>
	struct tppack_c_at
		: public sprout::tppack_at<I, std::integral_constant<T, Args>...>::type
	{};

	//
	// fppack_at
	//
	namespace detail {
		template<
			std::size_t I, typename R, typename Head, typename... Tail,
			typename sprout::enabler_if<I == 0>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR R
		fppack_at_impl(Head&& head, Tail&&...) {
			return sprout::forward<Head>(head);
		}
		template<
			std::size_t I, typename R, typename Head, typename... Tail,
			typename sprout::enabler_if<I != 0>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR R
		fppack_at_impl(Head&&, Tail&&... tail) {
			return sprout::detail::fppack_at_impl<I - 1, R>(sprout::forward<Tail>(tail)...);
		}
	}	// namespace detail
	template<std::size_t I, typename... Args>
	inline SPROUT_CONSTEXPR typename sprout::tppack_at<I, Args&&...>::type
	fppack_at(Args&&... args) {
		return sprout::detail::fppack_at_impl<
			I,
			typename sprout::tppack_at<I, Args&&...>::type
		>(sprout::forward<Args>(args)...);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PACK_HPP
