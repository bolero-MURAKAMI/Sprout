#ifndef SPROUT_ITERATOR_VALUED_ITERATOR_HPP
#define SPROUT_ITERATOR_VALUED_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/value_holder.hpp>

namespace sprout {
	//
	// valued_iterator
	//
	template<typename Iterator, typename T>
	class valued_iterator
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
		typedef T content_type;
		typedef sprout::value_holder<T> holder_type;
		typedef typename holder_type::param_type param_type;
		typedef typename holder_type::mutable_or_const_reference get_type;
	protected:
		iterator_type current;
		holder_type holder;
	public:
		valued_iterator() = default;
		SPROUT_CONSTEXPR valued_iterator(valued_iterator const& other)
			: current(other.current)
			, holder(other.holder)
		{}
		explicit SPROUT_CONSTEXPR valued_iterator(iterator_type it)
			: current(it)
			, holder()
		{}
		SPROUT_CONSTEXPR valued_iterator(iterator_type it, holder_type const& r)
			: current(it)
			, holder(r)
		{}
		SPROUT_CONSTEXPR valued_iterator(iterator_type it, param_type p)
			: current(it)
			, holder(p)
		{}
		template<typename U, typename V>
		SPROUT_CONSTEXPR valued_iterator(valued_iterator<U, V> const& it)
			: current(it.base())
			, holder(it.get())
		{}
		template<typename U, typename V>
		valued_iterator& operator=(valued_iterator<U, V> const& it) {
			valued_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current;
		}
		SPROUT_CONSTEXPR get_type get() const {
			return holder.get();
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return *current;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*current;
		}
		valued_iterator& operator++() {
			++current;
			return *this;
		}
		valued_iterator operator++(int) {
			valued_iterator result(*this);
			++current;
			return result;
		}
		valued_iterator& operator--() {
			--current;
			return *this;
		}
		valued_iterator operator--(int) {
			valued_iterator temp(*this);
			--current;
			return temp;
		}
		SPROUT_CONSTEXPR valued_iterator operator+(difference_type n) const {
			return valued_iterator(current + n, holder);
		}
		SPROUT_CONSTEXPR valued_iterator operator-(difference_type n) const {
			return valued_iterator(current - n, holder);
		}
		valued_iterator& operator+=(difference_type n) {
			valued_iterator temp(current + n, holder);
			temp.swap(*this);
			return *this;
		}
		valued_iterator& operator-=(difference_type n) {
			valued_iterator temp(current - n, holder);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return *(current + n);
		}
		SPROUT_CONSTEXPR valued_iterator next() const {
			return valued_iterator(sprout::next(current), holder);
		}
		SPROUT_CONSTEXPR valued_iterator prev() const {
			return valued_iterator(sprout::prev(current), holder);
		}
		void swap(valued_iterator& other)
		SPROUT_NOEXCEPT_EXPR(
			SPROUT_NOEXCEPT_EXPR(swap(current, other.current))
			&& SPROUT_NOEXCEPT_EXPR(swap(holder, other.holder))
			)
		{
			swap(current, other.current);
			swap(holder, other.holder);
		}
	};

	template<typename Iterator1, typename T1, typename Iterator2, typename T2>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::valued_iterator<Iterator1, T1> const& lhs, sprout::valued_iterator<Iterator2, T2> const& rhs) {
		return lhs.base() == rhs.base();
	}
	template<typename Iterator1, typename T1, typename Iterator2, typename T2>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::valued_iterator<Iterator1, T1> const& lhs, sprout::valued_iterator<Iterator2, T2> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Iterator1, typename T1, typename Iterator2, typename T2>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::valued_iterator<Iterator1, T1> const& lhs, sprout::valued_iterator<Iterator2, T2> const& rhs) {
		return lhs.base() < rhs.base();
	}
	template<typename Iterator1, typename T1, typename Iterator2, typename T2>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::valued_iterator<Iterator1, T1> const& lhs, sprout::valued_iterator<Iterator2, T2> const& rhs) {
		return rhs < lhs;
	}
	template<typename Iterator1, typename T1, typename Iterator2, typename T2>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::valued_iterator<Iterator1, T1> const& lhs, sprout::valued_iterator<Iterator2, T2> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Iterator1, typename T1, typename Iterator2, typename T2>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::valued_iterator<Iterator1, T1> const& lhs, sprout::valued_iterator<Iterator2, T2> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename Iterator1, typename T1, typename Iterator2, typename T2>
	inline SPROUT_CONSTEXPR decltype(std::declval<Iterator1, T1>() - std::declval<Iterator2, T2>())
	operator-(sprout::valued_iterator<Iterator1, T1> const& lhs, sprout::valued_iterator<Iterator2, T2> const& rhs) {
		return lhs.base() - rhs.base();
	}
	template<typename Iterator, typename T>
	inline SPROUT_CONSTEXPR sprout::valued_iterator<Iterator, T>
	operator+(
		typename sprout::valued_iterator<Iterator, T>::difference_type n,
		sprout::valued_iterator<Iterator, T> const& it
		)
	{
		return it + n;
	}

	//
	// make_valued_iterator
	//
	template<typename Iterator, typename T>
	inline SPROUT_CONSTEXPR sprout::valued_iterator<Iterator, T>
	make_valued_iterator(Iterator it, T const& param) {
		return sprout::valued_iterator<Iterator, T>(it, param);
	}

	//
	// swap
	//
	template<typename Iterator, typename T>
	inline void
	swap(sprout::valued_iterator<Iterator, T>& lhs, sprout::valued_iterator<Iterator, T>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_distance
	//
	template<typename Iterator, typename T>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<sprout::valued_iterator<Iterator, T> >::difference_type
	iterator_distance(sprout::valued_iterator<Iterator, T> first, sprout::valued_iterator<Iterator, T> last) {
		return last - first;
	}

	//
	// iterator_next
	//
	template<typename Iterator, typename T>
	inline SPROUT_CONSTEXPR sprout::valued_iterator<Iterator, T>
	iterator_next(sprout::valued_iterator<Iterator, T> const& it) {
		return it.next();
	}
	template<typename Iterator, typename T>
	inline SPROUT_CONSTEXPR sprout::valued_iterator<Iterator, T>
	iterator_next(
		sprout::valued_iterator<Iterator, T> const& it,
		typename sprout::valued_iterator<Iterator, T>::difference_type n
		)
	{
		return it + n;
	}

	//
	// iterator_prev
	//
	template<typename Iterator, typename T>
	inline SPROUT_CONSTEXPR sprout::valued_iterator<Iterator, T>
	iterator_prev(sprout::valued_iterator<Iterator, T> const& it) {
		return it.prev();
	}
	template<typename Iterator, typename T>
	inline SPROUT_CONSTEXPR sprout::valued_iterator<Iterator, T>
	iterator_prev(
		sprout::valued_iterator<Iterator, T> const& it,
		typename sprout::valued_iterator<Iterator, T>::difference_type n
		)
	{
		return it - n;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_VALUED_ITERATOR_HPP
