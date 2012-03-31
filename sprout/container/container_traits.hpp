#ifndef SPROUT_CONTAINER_CONTAINER_TRAITS_HPP
#define SPROUT_CONTAINER_CONTAINER_TRAITS_HPP

#include <cstddef>
#include <array>
#include <sprout/config.hpp>

namespace sprout {
	//
	// container_traits
	//
	template<typename Container>
	struct container_traits;

	namespace detail {
		template<typename Container>
		struct container_traits_default_types {
		public:
			typedef typename Container::value_type value_type;
			typedef typename Container::iterator iterator;
			typedef typename Container::const_iterator const_iterator;
			typedef typename Container::reference reference;
			typedef typename Container::const_reference const_reference;
			typedef typename Container::size_type size_type;
			typedef typename Container::difference_type difference_type;
			typedef typename Container::pointer pointer;
			typedef typename Container::const_pointer const_pointer;
		};
		template<typename T, std::size_t N>
		struct container_traits_default_types<T[N]> {
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
		};

		template<typename Container>
		struct container_traits_default_size {
		public:
			SPROUT_STATIC_CONSTEXPR typename sprout::detail::container_traits_default_types<Container>::size_type static_size
				= std::tuple_size<Container>::value
				;
		public:
			static SPROUT_CONSTEXPR typename sprout::detail::container_traits_default_types<Container>::size_type fixed_size() {
				return static_size;
			}
		};
		template<typename T, std::size_t N>
		struct container_traits_default_size<T[N]> {
		public:
			SPROUT_STATIC_CONSTEXPR typename sprout::detail::container_traits_default_types<T[N]>::size_type static_size
				= N
				;
		public:
			static SPROUT_CONSTEXPR typename sprout::detail::container_traits_default_types<T[N]>::size_type fixed_size() {
				return static_size;
			}
		};
	}	// namespace detail

	template<typename Container>
	struct container_traits
		: public sprout::detail::container_traits_default_types<Container>
		, public sprout::detail::container_traits_default_size<Container>
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
		: public sprout::detail::container_traits_default_types<T[N]>
		, public sprout::detail::container_traits_default_size<T[N]>
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
