#ifndef SPROUT_PIT_HPP
#define SPROUT_PIT_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator.hpp>
#include <sprout/iterator/value_iterator.hpp>

namespace sprout {
	//
	// pit
	//
	template<typename Container>
	class pit {
	public:
		typedef Container container_type;
		typedef pit fixed_container_type;
		typedef container_type internal_type;
		typedef typename sprout::fixed_container_traits<internal_type>::clone_type clone_type;
		typedef typename sprout::fixed_container_traits<internal_type>::value_type value_type;
		typedef typename sprout::fixed_container_traits<internal_type>::reference reference;
		typedef typename sprout::fixed_container_traits<internal_type>::const_reference const_reference;
		typedef typename sprout::value_iterator<reference> iterator;
		typedef typename sprout::value_iterator<const_reference> const_iterator;
		typedef typename sprout::fixed_container_traits<internal_type>::size_type size_type;
		typedef typename sprout::fixed_container_traits<internal_type>::difference_type difference_type;
		typedef typename sprout::fixed_container_traits<internal_type>::pointer pointer;
		typedef typename sprout::fixed_container_traits<internal_type>::const_pointer const_pointer;
		typedef typename sprout::reverse_iterator<iterator> reverse_iterator;
		typedef typename sprout::reverse_iterator<const_iterator> const_reverse_iterator;
	public:
		SPROUT_STATIC_CONSTEXPR size_type static_size = sprout::fixed_container_traits<fixed_container_type>::fixed_size;
		SPROUT_STATIC_CONSTEXPR size_type fixed_size = static_size;
	public:
		value_type elem;
	public:
		pit() = default;
		void swap(pit& other) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::swap(std::declval<value_type&>(), std::declval<value_type&>()))) {
			using std::swap;
			swap(elem, other.elem);
		}
		// iterators:
		iterator begin() {
			return iterator(elem, static_size);
		}
		SPROUT_CONSTEXPR const_iterator begin() const {
			return const_iterator(elem, static_size);
		}
		iterator end() SPROUT_NOEXCEPT {
			return iterator();
		}
		SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
			return const_iterator();
		}
		reverse_iterator rbegin() SPROUT_NOEXCEPT {
			return reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		reverse_iterator rend() SPROUT_NOEXCEPT {
			return reverse_iterator(begin());
		}
		SPROUT_CONSTEXPR const_reverse_iterator rend() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
		}
		SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT {
			return const_iterator(elem, static_size);
		}
		SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT {
			return const_iterator();
		}
		SPROUT_CONSTEXPR const_reverse_iterator crbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator crend() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
		}
		// capacity:
		SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT {
			return static_size;
		}
		SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT {
			return size();
		}
		SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT {
			return static_size == 0;
		}
		// element access:
		reference operator[](size_type i) {
			return elem;
		}
		SPROUT_CONSTEXPR const_reference operator[](size_type i) const {
			return elem;
		}
		reference at(size_type i) {
			return i < size()
				? elem
				: (throw std::out_of_range("pit<>: index out of range"), elem)
				;
		}
		SPROUT_CONSTEXPR const_reference at(size_type i) const {
			return i < size()
				? elem
				: (throw std::out_of_range("pit<>: index out of range"), elem)
				;
		}
		reference front() {
			return elem;
		}
		SPROUT_CONSTEXPR const_reference front() const {
			return elem;
		}
		reference back() {
			return elem;
		}
		SPROUT_CONSTEXPR const_reference back() const {
			return elem;
		}
		// others:
		void rangecheck(size_type i) const {
			if (i >= size()) {
				throw std::out_of_range("pit<>: index out of range");
			}
		}
	};
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::pit<Container>::size_type sprout::pit<Container>::static_size;
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::pit<Container>::size_type sprout::pit<Container>::fixed_size;

	//
	// operator==
	// operator!=
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator==(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return lhs.front() == rhs.front();
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator!=(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator<(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return lhs.front() < rhs.front();
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator>(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return rhs < lhs;
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator<=(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator>=(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return !(lhs < rhs);
	}

	//
	// swap
	//
	template<typename Container>
	inline void swap(sprout::pit<Container>& lhs, sprout::pit<Container>& rhs) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs))) {
		lhs.swap(rhs);
	}

	//
	// fixed_container_traits
	//
	template<typename Container>
	struct fixed_container_traits<sprout::pit<Container> >
		: public sprout::detail::fixed_container_traits_base<sprout::pit<Container> >
	{
	public:
		typedef typename sprout::pit<Container>::fixed_container_type fixed_container_type;
		typedef typename sprout::pit<Container>::internal_type internal_type;
		typedef typename sprout::pit<Container>::clone_type clone_type;
	public:
		SPROUT_STATIC_CONSTEXPR typename sprout::detail::fixed_container_traits_base<sprout::pit<Container> >::size_type fixed_size
			= std::tuple_size<typename std::remove_const<internal_type>::type>::value
			;
	};

	//
	// rebind_fixed_size
	//
	template<typename Container>
	struct rebind_fixed_size<sprout::pit<Container> > {
	public:
		template<typename sprout::fixed_container_traits<sprout::pit<Container> >::size_type S>
		struct apply {
			public:
				typedef sprout::pit<
					typename sprout::rebind_fixed_size<
						typename sprout::fixed_container_traits<sprout::pit<Container> >::internal_type
					>::template apply<S>::type
				> type;
		};
	};

	//
	// clone_functor
	//
	template<typename Container>
	struct clone_functor<sprout::pit<Container> > {
	private:
		typedef typename sprout::fixed_container_traits<sprout::pit<Container> >::clone_type clone_type;
	public:
		clone_type operator()(sprout::pit<Container>& cont) const {
			return clone_type();
		}
		SPROUT_CONSTEXPR clone_type operator()(sprout::pit<Container> const& cont) const {
			return clone_type();
		}
	};

	//
	// make_clone_functor
	//
	template<typename Container>
	struct make_clone_functor<sprout::pit<Container> > {
	private:
		typedef typename sprout::fixed_container_traits<sprout::pit<Container> >::clone_type clone_type;
		typedef typename sprout::fixed_container_traits<sprout::pit<Container> >::internal_type internal_type;
	public:
		template<typename... Args>
		SPROUT_CONSTEXPR clone_type operator()(Args const&... args) const {
			return sprout::make_clone<internal_type>(args...);
		}
	};

	//
	// remake_clone_functor
	//
	template<typename Container>
	struct remake_clone_functor<sprout::pit<Container> > {
	private:
		typedef typename sprout::fixed_container_traits<sprout::pit<Container> >::clone_type clone_type;
		typedef typename sprout::fixed_container_traits<sprout::pit<Container> >::internal_type internal_type;
	public:
		template<typename Other, typename... Args>
		clone_type operator()(
			Other& other,
			typename sprout::fixed_container_traits<sprout::pit<Container> >::difference_type size,
			Args const&... args
			) const
		{
			return sprout::remake_clone<internal_type, Other>(other, size, args...);
		}
		template<typename Other, typename... Args>
		SPROUT_CONSTEXPR clone_type operator()(
			Other const& other,
			typename sprout::fixed_container_traits<sprout::pit<Container> >::difference_type size,
			Args const&... args
			) const
		{
			return sprout::remake_clone<internal_type, Other>(other, size, args...);
		}
	};
}	// namespace sprout

namespace std {
	//
	// tuple_size
	//
	template<typename Container>
	struct tuple_size<sprout::pit<Container> > {
	public:
		typedef std::integral_constant<std::size_t, sprout::fixed_container_traits<sprout::pit<Container> >::fixed_size> type;
		SPROUT_STATIC_CONSTEXPR std::size_t value = type::value;
	};

	//
	// tuple_element
	//
	template<std::size_t I, typename Container>
	struct tuple_element<I, sprout::pit<Container> > {
	public:
		static_assert(I < sprout::fixed_container_traits<sprout::pit<Container> >::fixed_size, "tuple_element<>: index out of range");
		typedef typename sprout::fixed_container_traits<sprout::pit<Container> >::value_type type;
	};

	//
	// get
	//
	template<std::size_t I, typename Container>
	typename sprout::fixed_container_traits<sprout::pit<Container> >::value_type& get(
		sprout::pit<Container>& t
		) SPROUT_NOEXCEPT
	{
		static_assert(I < sprout::fixed_container_traits<sprout::pit<Container> >::fixed_size, "get: index out of range");
		return t[I];
	}
	template<std::size_t I, typename Container>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<sprout::pit<Container> >::value_type const& get(
		sprout::pit<Container> const& t
		) SPROUT_NOEXCEPT
	{
		static_assert(I < sprout::fixed_container_traits<sprout::pit<Container> >::fixed_size, "get: index out of range");
		return t[I];
	}
	template<std::size_t I, typename Container>
	typename sprout::fixed_container_traits<sprout::pit<Container> >::value_type&& get(
		sprout::pit<Container>&& t
		) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::move(std::get<I>(t))))
	{
		return std::move(std::get<I>(t));
	}
}	// namespace std

#endif	// #ifndef SPROUT_PIT_HPP
