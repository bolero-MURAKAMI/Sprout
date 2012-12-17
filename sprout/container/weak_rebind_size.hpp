#ifndef SPROUT_CONTAINER_WEAK_REBIND_SIZE_HPP
#define SPROUT_CONTAINER_WEAK_REBIND_SIZE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/container_transform_traits.hpp>

namespace sprout {
	namespace containers {
		namespace detail {
			template<
				typename T,
				template<typename sprout::container_traits<T>::size_type> class = T::template rebind_size
			>
			std::true_type sprout_has_xxx_impl_check_template_rebind_size(int);
			template<typename T>
			std::false_type sprout_has_xxx_impl_check_template_rebind_size(long);
#if defined(_MSC_VER)
			template<typename T, typename Base_ = decltype(sprout::containers::detail::sprout_has_xxx_impl_check_template_rebind_size<T>(0))>
			struct has_rebind_size
				: public Base_
			{};
#else
			template<typename T>
			struct has_rebind_size
				: public decltype(sprout::containers::detail::sprout_has_xxx_impl_check_template_rebind_size<T>(0))
			{};
#endif
		}	// namespace detail
		//
		// is_rebindable_size
		//
		template<typename Container>
		struct is_rebindable_size
			: public sprout::containers::detail::has_rebind_size<
				sprout::container_transform_traits<Container>
			>
		{};
		template<typename Container>
		struct is_rebindable_size<Container const>
			: public sprout::containers::is_rebindable_size<Container>
		{};
		template<typename Container>
		struct is_rebindable_size<Container volatile>
			: public sprout::containers::is_rebindable_size<Container>
		{};
		template<typename Container>
		struct is_rebindable_size<Container const volatile>
			: public sprout::containers::is_rebindable_size<Container>
		{};

		namespace detail {
			template<typename Container, typename sprout::container_traits<Container>::size_type Size, typename = void>
			struct weak_rebind_size_impl;
			template<typename Container, typename sprout::container_traits<Container>::size_type Size>
			struct weak_rebind_size_impl<
				Container, Size,
				typename std::enable_if<sprout::containers::is_rebindable_size<Container>::value>::type
			>
				: public sprout::container_transform_traits<Container>::template rebind_size<Size>
			{};
			template<typename Container, typename sprout::container_traits<Container>::size_type Size>
			struct weak_rebind_size_impl<
				Container, Size,
				typename std::enable_if<!sprout::containers::is_rebindable_size<Container>::value>::type
			> {
			public:
				typedef Container type;
			};
		}	// namespace detail
		//
		// weak_rebind_size
		//
		template<typename Container, typename sprout::container_traits<Container>::size_type Size>
		struct weak_rebind_size
			: public sprout::containers::detail::weak_rebind_size_impl<Container, Size>
		{};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_WEAK_REBIND_SIZE_HPP
