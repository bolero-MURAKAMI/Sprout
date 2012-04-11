#ifndef SPROUT_ITERATOR_REVERSE_ITERATOR_HPP
#define SPROUT_ITERATOR_REVERSE_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>

namespace sprout {
	//
	// reverse_iterator
	//
	template<typename Iterator>
	class reverse_iterator
		: public std::iterator<
			typename std::iterator_traits<Iterator>::iterator_category,
			typename std::iterator_traits<Iterator>::value_type,
			typename std::iterator_traits<Iterator>::difference_type,
			typename std::iterator_traits<Iterator>::pointer,
			typename std::iterator_traits<Iterator>::reference
		>
	{
	public:
		typedef Iterator iterator_type;
		typedef typename std::iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename std::iterator_traits<iterator_type>::value_type value_type;
		typedef typename std::iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename std::iterator_traits<iterator_type>::pointer pointer;
		typedef typename std::iterator_traits<iterator_type>::reference reference;
	protected:
		iterator_type current;
	private:
		iterator_type deref_tmp;
	public:
		reverse_iterator() = default;
		reverse_iterator(reverse_iterator const&) = default;
		explicit SPROUT_CONSTEXPR reverse_iterator(iterator_type it)
			: current(it)
			, deref_tmp(sprout::prev(it))
		{}
		template<typename U>
		SPROUT_CONSTEXPR reverse_iterator(reverse_iterator<U> const& it)
			: current(it)
			, deref_tmp(sprout::prev(it))
		{}
		template<typename U>
		reverse_iterator& operator=(reverse_iterator<U> const& it) {
			reverse_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return *deref_tmp;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*deref_tmp;
		}
		reverse_iterator& operator++() {
			--current;
			--deref_tmp;
			return *this;
		}
		reverse_iterator operator++(int) {
			reverse_iterator result(*this);
			--current;
			--deref_tmp;
			return result;
		}
		reverse_iterator& operator--() {
			++current;
			++deref_tmp;
			return *this;
		}
		reverse_iterator operator--(int) {
			reverse_iterator temp(*this);
			++current;
			++deref_tmp;
			return temp;
		}
		SPROUT_CONSTEXPR reverse_iterator operator+(difference_type n) const {
			return reverse_iterator(current - n);
		}
		SPROUT_CONSTEXPR reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(current + n);
		}
		reverse_iterator& operator+=(difference_type n) {
			reverse_iterator temp(current - n);
			temp.swap(*this);
			return *this;
		}
		reverse_iterator& operator-=(difference_type n) {
			reverse_iterator temp(current + n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return *(deref_tmp - n);
		}
		void swap(reverse_iterator& other) {
			using std::swap;
			swap(current, other.current);
			swap(deref_tmp, other.deref_tmp);
		}
	};
	template <typename Iterator1, typename Iterator2>
	SPROUT_CONSTEXPR bool operator==(
		sprout::reverse_iterator<Iterator1> const& lhs,
		sprout::reverse_iterator<Iterator2> const& rhs
		)
	{
		return lhs.base() == rhs.base();
	}
	template <typename Iterator1, typename Iterator2>
	SPROUT_CONSTEXPR bool operator!=(
		sprout::reverse_iterator<Iterator1> const& lhs,
		sprout::reverse_iterator<Iterator2> const& rhs
		)
	{
		return !(lhs == rhs);
	}
	template <typename Iterator1, typename Iterator2>
	SPROUT_CONSTEXPR bool operator<(
		sprout::reverse_iterator<Iterator1> const& lhs,
		sprout::reverse_iterator<Iterator2> const& rhs
		)
	{
		return lhs.base() < rhs.base();
	}
	template <typename Iterator1, typename Iterator2>
	SPROUT_CONSTEXPR bool operator>(
		sprout::reverse_iterator<Iterator1> const& lhs,
		sprout::reverse_iterator<Iterator2> const& rhs
		)
	{
		return rhs < lhs;
	}
	template <typename Iterator1, typename Iterator2>
	SPROUT_CONSTEXPR bool operator<=(
		sprout::reverse_iterator<Iterator1> const& lhs,
		sprout::reverse_iterator<Iterator2> const& rhs
		)
	{
		return !(rhs < lhs);
	}
	template <typename Iterator1, typename Iterator2>
	SPROUT_CONSTEXPR bool operator>=(
		sprout::reverse_iterator<Iterator1> const& lhs,
		sprout::reverse_iterator<Iterator2> const& rhs
		)
	{
		return !(lhs < rhs);
	}
	template <typename Iterator1, typename Iterator2>
	SPROUT_CONSTEXPR auto operator-(
		sprout::reverse_iterator<Iterator1> const& lhs,
		sprout::reverse_iterator<Iterator2> const& rhs
		) -> decltype(lhs.current - rhs.current)
	{
		return lhs.current - rhs.current;
	}
	template <typename Iterator>
	SPROUT_CONSTEXPR sprout::reverse_iterator<Iterator> operator+(
		typename sprout::reverse_iterator<Iterator>::difference_type n,
		sprout::reverse_iterator<Iterator> const& it
		)
	{
		return it + n;
	}

	//
	// swap
	//
	template<typename Iterator>
	void swap(sprout::reverse_iterator<Iterator>& lhs, sprout::reverse_iterator<Iterator>& rhs) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs))) {
		lhs.swap(rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_REVERSE_ITERATOR_HPP

