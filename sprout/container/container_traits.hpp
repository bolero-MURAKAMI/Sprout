#ifndef SPROUT_CONTAINER_CONTAINER_TRAITS_HPP
#define SPROUT_CONTAINER_CONTAINER_TRAITS_HPP

#include <cstddef>
#include <array>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/has_xxx.hpp>
#include <sprout/type_traits/inherit_if_xxx.hpp>

namespace sprout {
	template<typename Container>
	struct container_traits;

	namespace detail {
		//
		// inherit_if_value_type
		// inherit_if_iterator
		// inherit_if_const_iterator
		// inherit_if_reference
		// inherit_if_const_reference
		// inherit_if_size_type
		// inherit_if_difference_type
		// inherit_if_pointer
		// inherit_if_static_size
		//
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(value_type);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(iterator);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(const_iterator);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(reference);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(const_reference);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(size_type);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(difference_type);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(pointer);
		SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(const_pointer);
		SPROUT_INHERIT_IF_XXX_CONSTANT_DEF_LAZY(static_size);

		//
		// has_static_size
		//
		SPROUT_HAS_XXX_VALUE_DEF_LAZY(static_size);

		template<typename Container, typename Enable = void>
		struct inherit_if_fixed_size {};
		template<typename Container>
		struct inherit_if_fixed_size<
			Container,
			typename std::enable_if<sprout::detail::has_static_size<Container>::value>::type
		> {
		public:
			static SPROUT_CONSTEXPR decltype(Container::static_size) fixed_size() {
				return Container::static_size;
			}
		};

		template<typename Container>
		struct container_traits_default
			: public sprout::detail::inherit_if_value_type<Container>
			, public sprout::detail::inherit_if_iterator<Container>
			, public sprout::detail::inherit_if_const_iterator<Container>
			, public sprout::detail::inherit_if_reference<Container>
			, public sprout::detail::inherit_if_const_reference<Container>
			, public sprout::detail::inherit_if_size_type<Container>
			, public sprout::detail::inherit_if_difference_type<Container>
			, public sprout::detail::inherit_if_pointer<Container>
			, public sprout::detail::inherit_if_const_pointer<Container>
			, public sprout::detail::inherit_if_static_size<Container>
			, public sprout::detail::inherit_if_fixed_size<Container>
		{};
		template<typename T, std::size_t N>
		struct container_traits_default<T[N]> {
		public:
			typedef T value_type;
			typedef T* iterator;
			typedef T const* const_iterator;
			typedef T& reference;
			typedef T const& const_reference;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T const* const_pointer;
		public:
			SPROUT_STATIC_CONSTEXPR size_type static_size = N ;
		public:
			static SPROUT_CONSTEXPR size_type fixed_size() {
				return static_size;
			}
		};
	}	// namespace detail

	//
	// container_traits
	//
	template<typename Container>
	struct container_traits
		: public sprout::detail::container_traits_default<Container>
	{};
	template<typename Container>
	struct container_traits<Container const>
		: public sprout::container_traits<Container>
	{
	public:
		typedef typename sprout::container_traits<Container>::const_iterator iterator;
		typedef typename sprout::container_traits<Container>::const_reference reference;
		typedef typename sprout::container_traits<Container>::const_pointer pointer;
	};

	template<typename T, std::size_t N>
	struct container_traits<T[N]>
		: public sprout::detail::container_traits_default<T[N]>
	{};
	template<typename T, std::size_t N>
	struct container_traits<T const[N]>
		: public sprout::container_traits<T[N]>
	{
	public:
		typedef typename sprout::container_traits<T[N]>::const_iterator iterator;
		typedef typename sprout::container_traits<T[N]>::const_reference reference;
		typedef typename sprout::container_traits<T[N]>::const_pointer pointer;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_CONTAINER_TRAITS_HPP
