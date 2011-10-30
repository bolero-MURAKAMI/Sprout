#ifndef SPROUT_FIXED_CONTAINER_TRAITS_HPP
#define SPROUT_FIXED_CONTAINER_TRAITS_HPP

#include <cstddef>
#include <array>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace detail {
		template<typename Container>
		struct fixed_container_traits_base {
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
		struct fixed_container_traits_base<T[N]> {
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
	}	// namespace detail

	//
	// fixed_container_traits
	//
	template<typename Container>
	struct fixed_container_traits
		: public sprout::detail::fixed_container_traits_base<Container>
	{
	public:
		typedef Container fixed_container_type;
		typedef Container internal_type;
		typedef Container clone_type;
	public:
		SPROUT_STATIC_CONSTEXPR typename sprout::detail::fixed_container_traits_base<fixed_container_type>::size_type fixed_size
			= std::tuple_size<typename std::remove_const<internal_type>::type>::value
			;
	};
	template<typename T, std::size_t N>
	struct fixed_container_traits<T[N]>
		: public sprout::detail::fixed_container_traits_base<T[N]>
	{
	public:
		typedef T fixed_container_type[N];
		typedef T internal_type[N];
		typedef T clone_type[N];
	public:
		SPROUT_STATIC_CONSTEXPR typename sprout::detail::fixed_container_traits_base<T[N]>::size_type fixed_size = N;
	};
	template<typename Container>
	struct fixed_container_traits<Container const>
		: public sprout::fixed_container_traits<Container>
	{
	public:
		typedef typename sprout::fixed_container_traits<Container>::const_iterator iterator;
		typedef typename sprout::fixed_container_traits<Container>::const_reference reference;
		typedef typename sprout::fixed_container_traits<Container>::const_pointer pointer;
	};
	template<typename T, std::size_t N>
	struct fixed_container_traits<T const[N]>
		: public sprout::fixed_container_traits<T[N]>
	{
	public:
		typedef typename sprout::fixed_container_traits<T[N]>::const_iterator iterator;
		typedef typename sprout::fixed_container_traits<T[N]>::const_reference reference;
		typedef typename sprout::fixed_container_traits<T[N]>::const_pointer pointer;
	};

	//
	// rebind_fixed_size
	//
	template<typename Container>
	struct rebind_fixed_size {
	public:
		template<typename sprout::fixed_container_traits<Container>::size_type S>
		struct apply;
	};
	template<typename T, std::size_t N>
	struct rebind_fixed_size<T[N]> {
	public:
		template<typename sprout::fixed_container_traits<T[N]>::size_type S>
		struct apply {
		public:
			typedef T type[S];
		};
	};

	//
	// get_fixed_functor
	//
	template<typename Container>
	struct get_fixed_functor {
	public:
		typename sprout::fixed_container_traits<Container>::fixed_container_type& operator()(Container& cont) const {
			return cont;
		}
		SPROUT_CONSTEXPR typename sprout::fixed_container_traits<Container>::fixed_container_type const& operator()(Container const& cont) const {
			return cont;
		}
	};
	template<typename Container>
	struct get_fixed_functor<Container const>
		: public sprout::get_fixed_functor<Container>
	{};

	//
	// clone_functor
	//
	template<typename Container>
	struct clone_functor {
	public:
		template<typename Other>
		SPROUT_CONSTEXPR typename sprout::fixed_container_traits<Container>::clone_type operator()(Other&& cont) const {
			return typename sprout::fixed_container_traits<Container>::clone_type(sprout::forward<Other>(cont));
		}
	};
	template<typename Container>
	struct clone_functor<Container const>
		: public sprout::clone_functor<Container>
	{};

	//
	// make_clone_functor
	//
	template<typename Container>
	struct make_clone_functor {
	public:
		template<typename... Args>
		SPROUT_CONSTEXPR typename sprout::fixed_container_traits<Container>::clone_type operator()(Args&&... args) const {
			return typename sprout::fixed_container_traits<Container>::clone_type{{sprout::forward<Args>(args)...}};
		}
	};
	template<typename Container>
	struct make_clone_functor<Container const>
		: public sprout::make_clone_functor<Container>
	{};

	//
	// remake_clone_functor
	//
	template<typename Container>
	struct remake_clone_functor {
	public:
		template<typename Other, typename... Args>
		SPROUT_CONSTEXPR typename sprout::fixed_container_traits<Container>::clone_type operator()(
			Other&& other,
			typename sprout::fixed_container_traits<Container>::difference_type size,
			Args&&... args
			) const
		{
			return sprout::make_clone_functor<Container>().template operator()(sprout::forward<Args>(args)...);
		}
	};
	template<typename Container>
	struct remake_clone_functor<Container const>
		: public sprout::remake_clone_functor<Container>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_TRAITS_HPP
