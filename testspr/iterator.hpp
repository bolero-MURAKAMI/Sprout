#ifndef TESTSPR_ITERATOR_HPP
#define TESTSPR_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/utility/swap.hpp>

namespace testspr {
	//
	// reduct_iterator
	//
	template<typename Iterator, typename Category = typename std::iterator_traits<Iterator>::iterator_category>
	class reduct_iterator
		: public std::iterator<
			Category,
			typename std::iterator_traits<Iterator>::value_type,
			typename std::iterator_traits<Iterator>::difference_type,
			typename std::iterator_traits<Iterator>::pointer,
			typename std::iterator_traits<Iterator>::reference
		>
	{
	public:
		typedef Iterator iterator_type;
		typedef Category iterator_category;
		typedef typename std::iterator_traits<iterator_type>::value_type value_type;
		typedef typename std::iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename std::iterator_traits<iterator_type>::pointer pointer;
		typedef typename std::iterator_traits<iterator_type>::reference reference;
	protected:
		iterator_type current;
	public:
		reduct_iterator() = default;
		SPROUT_CONSTEXPR reduct_iterator(reduct_iterator const& other) = default;
		explicit SPROUT_CONSTEXPR reduct_iterator(iterator_type it)
			: current(it)
		{}
		template<typename U, typename V>
		SPROUT_CONSTEXPR reduct_iterator(reduct_iterator<U, V> const& it)
			: current(it.base())
		{}
		template<typename U, typename V>
		reduct_iterator& operator=(reduct_iterator<U, V> const& it) {
			reduct_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return *current;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*current;
		}
		reduct_iterator& operator++() {
			--current;
			return *this;
		}
		reduct_iterator operator++(int) {
			reduct_iterator result(*this);
			--current;
			return result;
		}
		reduct_iterator& operator--() {
			++current;
			return *this;
		}
		reduct_iterator operator--(int) {
			reduct_iterator temp(*this);
			++current;
			return temp;
		}
		SPROUT_CONSTEXPR reduct_iterator operator+(difference_type n) const {
			return reduct_iterator(current + n);
		}
		SPROUT_CONSTEXPR reduct_iterator operator-(difference_type n) const {
			return reduct_iterator(current - n);
		}
		reduct_iterator& operator+=(difference_type n) {
			reduct_iterator temp(current + n);
			temp.swap(*this);
			return *this;
		}
		reduct_iterator& operator-=(difference_type n) {
			reduct_iterator temp(current - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return current[n];
		}
		SPROUT_CONSTEXPR reduct_iterator next() const {
			return reduct_iterator(sprout::next(current));
		}
		SPROUT_CONSTEXPR reduct_iterator prev() const {
			return reduct_iterator(sprout::prev(current));
		}
		void swap(reduct_iterator& other)
		SPROUT_NOEXCEPT_EXPR(
			SPROUT_NOEXCEPT_EXPR(swap(current, other.current))
			)
		{
			swap(current, other.current);
		}
	};

	template<typename Iterator1, typename Category1, typename Iterator2, typename Category2>
	inline SPROUT_CONSTEXPR bool
	operator==(testspr::reduct_iterator<Iterator1, Category1> const& lhs, testspr::reduct_iterator<Iterator2, Category2> const& rhs) {
		return lhs.base() == rhs.base();
	}
	template<typename Iterator1, typename Category1, typename Iterator2, typename Category2>
	inline SPROUT_CONSTEXPR bool
	operator!=(testspr::reduct_iterator<Iterator1, Category1> const& lhs, testspr::reduct_iterator<Iterator2, Category2> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Iterator1, typename Category1, typename Iterator2, typename Category2>
	inline SPROUT_CONSTEXPR bool
	operator<(testspr::reduct_iterator<Iterator1, Category1> const& lhs, testspr::reduct_iterator<Iterator2, Category2> const& rhs) {
		return lhs.base() < rhs.base();
	}
	template<typename Iterator1, typename Category1, typename Iterator2, typename Category2>
	inline SPROUT_CONSTEXPR bool
	operator>(testspr::reduct_iterator<Iterator1, Category1> const& lhs, testspr::reduct_iterator<Iterator2, Category2> const& rhs) {
		return rhs < lhs;
	}
	template<typename Iterator1, typename Category1, typename Iterator2, typename Category2>
	inline SPROUT_CONSTEXPR bool
	operator<=(testspr::reduct_iterator<Iterator1, Category1> const& lhs, testspr::reduct_iterator<Iterator2, Category2> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Iterator1, typename Category1, typename Iterator2, typename Category2>
	inline SPROUT_CONSTEXPR bool
	operator>=(testspr::reduct_iterator<Iterator1, Category1> const& lhs, testspr::reduct_iterator<Iterator2, Category2> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename Iterator1, typename Category1, typename Iterator2, typename Category2>
	inline SPROUT_CONSTEXPR decltype(std::declval<Iterator1>() - std::declval<Iterator2>())
	operator-(testspr::reduct_iterator<Iterator1, Category1> const& lhs, testspr::reduct_iterator<Iterator2, Category2> const& rhs) {
		return lhs.base() - rhs.base();
	}
	template<typename Iterator, typename Category>
	inline SPROUT_CONSTEXPR testspr::reduct_iterator<Iterator, Category>
	operator+(
		typename testspr::reduct_iterator<Iterator, Category>::difference_type n,
		testspr::reduct_iterator<Iterator, Category> const& it
		)
	{
		return it + n;
	}

	//
	// make_reduct_iterator
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduct_iterator<Iterator>
	make_reduct_iterator(Iterator it) {
		return testspr::reduct_iterator<Iterator>(it);
	}
	template<typename Category, typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduct_iterator<Iterator, Category>
	make_reduct_iterator(Iterator it) {
		return testspr::reduct_iterator<Iterator, Category>(it);
	}

	//
	// reduct_input
	// reduct_forward
	// reduct_bidirectional
	// reduct_random_access
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduct_iterator<Iterator, std::input_iterator_tag>
	reduct_input(Iterator it) {
		return testspr::reduct_iterator<Iterator, std::input_iterator_tag>(it);
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduct_iterator<Iterator, std::forward_iterator_tag>
	reduct_forward(Iterator it) {
		return testspr::reduct_iterator<Iterator, std::forward_iterator_tag>(it);
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduct_iterator<Iterator, std::bidirectional_iterator_tag>
	reduct_bidirectional(Iterator it) {
		return testspr::reduct_iterator<Iterator, std::bidirectional_iterator_tag>(it);
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduct_iterator<Iterator, std::random_access_iterator_tag>
	reduct_random_access(Iterator it) {
		return testspr::reduct_iterator<Iterator, std::random_access_iterator_tag>(it);
	}

	//
	// swap
	//
	template<typename Category, typename Iterator>
	inline void
	swap(testspr::reduct_iterator<Iterator, Category>& lhs, testspr::reduct_iterator<Iterator, Category>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_distance
	//
	template<typename Category, typename Iterator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<testspr::reduct_iterator<Iterator, Category> >::difference_type
	iterator_distance(testspr::reduct_iterator<Iterator, Category> first, testspr::reduct_iterator<Iterator, Category> last) {
		return sprout::distance(first.base(), last.base());
	}

	//
	// iterator_next
	//
	template<typename Category, typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduct_iterator<Iterator, Category>
	iterator_next(testspr::reduct_iterator<Iterator, Category> const& it) {
		return it.next();
	}
	template<typename Category, typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduct_iterator<Iterator, Category>
	iterator_next(
		testspr::reduct_iterator<Iterator, Category> const& it,
		typename testspr::reduct_iterator<Iterator, Category>::difference_type n
		)
	{
		return testspr::reduct_iterator<Iterator, Category>(sprout::next(it.base(), n));
	}

	//
	// iterator_prev
	//
	template<typename Category, typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduct_iterator<Iterator, Category>
	iterator_prev(testspr::reduct_iterator<Iterator, Category> const& it) {
		return it.prev();
	}
	template<typename Category, typename Iterator>
	inline SPROUT_CONSTEXPR testspr::reduct_iterator<Iterator, Category>
	iterator_prev(
		testspr::reduct_iterator<Iterator, Category> const& it,
		typename testspr::reduct_iterator<Iterator, Category>::difference_type n
		)
	{
		return testspr::reduct_iterator<Iterator, Category>(sprout::next(it.base(), n));
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_ITERATOR_HPP
