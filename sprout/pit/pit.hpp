#ifndef SPROUT_PIT_PIT_HPP
#define SPROUT_PIT_PIT_HPP

#include <utility>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/reverse_iterator.hpp>
#include <sprout/iterator/value_iterator.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// pit
	//
	template<typename Container>
	class pit
		: public sprout::container_traits_facade<Container>
	{
	private:
		typedef sprout::container_traits_facade<typename std::remove_reference<Container>::type> facade_type;
	public:
		typedef Container container_type;
		typedef typename facade_type::value_type value_type;
		typedef typename facade_type::reference reference;
		typedef typename facade_type::const_reference const_reference;
		typedef typename sprout::value_iterator<reference> iterator;
		typedef typename sprout::value_iterator<const_reference> const_iterator;
		typedef typename facade_type::size_type size_type;
		typedef typename facade_type::difference_type difference_type;
		typedef typename facade_type::pointer pointer;
		typedef typename facade_type::const_pointer const_pointer;
		typedef typename sprout::reverse_iterator<iterator> reverse_iterator;
		typedef typename sprout::reverse_iterator<const_iterator> const_reverse_iterator;
	public:
		SPROUT_STATIC_CONSTEXPR size_type enumerable_size = sprout::detail::static_size_or_zero<facade_type>::value;
	public:
		value_type elem;
	public:
		pit() = default;
		void swap(pit& other)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(elem, other.elem)))
		{
			sprout::swap(elem, other.elem);
		}
		// iterators:
		iterator begin() {
			return iterator(elem, enumerable_size);
		}
		SPROUT_CONSTEXPR const_iterator begin() const {
			return const_iterator(elem, enumerable_size);
		}
		iterator end() SPROUT_NOEXCEPT {
			return iterator(elem, 0);
		}
		SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
			return const_iterator(elem, 0);
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
			return const_iterator(elem, enumerable_size);
		}
		SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT {
			return const_iterator(elem, 0);
		}
		SPROUT_CONSTEXPR const_reverse_iterator crbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator crend() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
		}
		// capacity:
		SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT {
			return enumerable_size;
		}
		SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT {
			return size();
		}
		SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT {
			return enumerable_size == 0;
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
	SPROUT_CONSTEXPR_OR_CONST typename sprout::pit<Container>::size_type sprout::pit<Container>::enumerable_size;

	//
	// swap
	//
	template<typename Container>
	inline void
	swap(sprout::pit<Container>& lhs, sprout::pit<Container>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}
}	// namespace sprout

#include <sprout/pit/container.hpp>

#endif	// #ifndef SPROUT_PIT_PIT_HPP
