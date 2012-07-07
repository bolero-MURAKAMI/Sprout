#ifndef SPROUT_TYPE_TRAITS_FLOAT_PROMOTE_HPP
#define SPROUT_TYPE_TRAITS_FLOAT_PROMOTE_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		template<typename T>
		struct float_promote1
			: public std::conditional<
				std::is_floating_point<T>::value,
				std::common_type<T>,
				std::common_type<double>
			>::type
		{
			static_assert(
				std::is_arithmetic<T>::value,
				"float_promote requires arithmetic type."
				);
		};

		template<typename T, typename U>
		struct float_promote2
			: public std::conditional<
				(std::is_same<T, long double>::value || std::is_same<U, long double>::value),
				std::common_type<long double>,
				typename std::conditional<
					(std::is_same<T, float>::value && std::is_same<U, float>::value),
					float,
					double
				>
			>::type
		{
			static_assert(
				std::is_arithmetic<T>::value && std::is_arithmetic<U>::value,
				"float_promote requires arithmetic type."
				);
		};

		template<typename... Types>
		struct float_promote_impl;
		template<typename T, typename U, typename... Tail>
		struct float_promote_impl<T, U, Tail...>
			: public sprout::detail::float_promote_impl<
				typename sprout::detail::float_promote2<T, U>::type,
				Tail...
			>
		{};
		template<typename T>
		struct float_promote_impl<T>
			: public sprout::detail::float_promote1<T>
		{};
	}	// namespace detail

	//
	// float_promote
	//
	template<typename... Types>
	struct float_promote
		: public sprout::detail::float_promote_impl<
			typename std::remove_cv<Types>::type...
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_FLOAT_PROMOTE_HPP
