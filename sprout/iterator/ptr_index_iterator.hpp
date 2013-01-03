#ifndef SPROUT_ITERATOR_PTR_INDEX_ITERATOR_HPP
#define SPROUT_ITERATOR_PTR_INDEX_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// ptr_index_iterator
	//
	template<typename T>
	class ptr_index_iterator
		: public std::iterator<
			typename std::iterator_traits<T*>::iterator_category,
			typename std::iterator_traits<T*>::value_type,
			typename std::iterator_traits<T*>::difference_type,
			typename std::iterator_traits<T*>::pointer,
			typename std::iterator_traits<T*>::reference
		>
	{
	public:
		typedef T type;
	private:
		typedef std::iterator<
			typename std::iterator_traits<T*>::iterator_category,
			typename std::iterator_traits<T*>::value_type,
			typename std::iterator_traits<T*>::difference_type,
			typename std::iterator_traits<T*>::pointer,
			typename std::iterator_traits<T*>::reference
		> base_type;
	public:
		typedef typename base_type::iterator_category iterator_category;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::difference_type difference_type;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::reference reference;
		typedef typename std::remove_pointer<pointer>::type const* const_pointer;
	private:
		pointer p_;
		difference_type index_;
	public:
		SPROUT_CONSTEXPR ptr_index_iterator()
			: p_()
			, index_()
		{}
		ptr_index_iterator(ptr_index_iterator const&) = default;
		explicit SPROUT_CONSTEXPR ptr_index_iterator(pointer p)
			: p_(p)
			, index_(0)
		{}
		SPROUT_CONSTEXPR ptr_index_iterator(pointer p, difference_type index)
			: p_(p)
			, index_(index)
		{}
		operator ptr_index_iterator<const_pointer>() const {
			return ptr_index_iterator<const_pointer>(p_, index_);
		}
		SPROUT_CONSTEXPR pointer base() const {
			return p_;
		}
		SPROUT_CONSTEXPR difference_type index() const {
			return index_;
		}
		SPROUT_CONSTEXPR pointer ptr() const {
			return p_ + index_;
		}
		SPROUT_CONSTEXPR ptr_index_iterator next() const {
			return ptr_index_iterator(p_, index_ + 1);
		}
		SPROUT_CONSTEXPR ptr_index_iterator prev() const {
			return ptr_index_iterator(p_, index_ - 1);
		}
		void swap(ptr_index_iterator& other)
		SPROUT_NOEXCEPT
		{
			sprout::swap(p_, other.p_);
			sprout::swap(index_, other.index_);
		}
		friend SPROUT_CONSTEXPR bool operator==(ptr_index_iterator const& lhs, ptr_index_iterator const& rhs) {
			return lhs.index_ == rhs.index_;
		}
		friend SPROUT_CONSTEXPR bool operator!=(ptr_index_iterator const& lhs, ptr_index_iterator const& rhs) {
			return !(lhs == rhs);
		}
		friend SPROUT_CONSTEXPR bool operator<(ptr_index_iterator const& lhs, ptr_index_iterator const& rhs) {
			return lhs.index_ < rhs.index_;
		}
		friend SPROUT_CONSTEXPR bool operator>(ptr_index_iterator const& lhs, ptr_index_iterator const& rhs) {
			return rhs < lhs;
		}
		friend SPROUT_CONSTEXPR bool operator<=(ptr_index_iterator const& lhs, ptr_index_iterator const& rhs) {
			return !(rhs < lhs);
		}
		friend SPROUT_CONSTEXPR bool operator>=(ptr_index_iterator const& lhs, ptr_index_iterator const& rhs) {
			return !(lhs < rhs);
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return p_[index_];
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return p_ + index_;
		}
		ptr_index_iterator& operator++() {
			ptr_index_iterator temp(next());
			temp.swap(*this);
			return *this;
		}
		ptr_index_iterator operator++(int) {
			ptr_index_iterator result(*this);
			++*this;
			return result;
		}
		ptr_index_iterator& operator--() {
			ptr_index_iterator temp(prev());
			temp.swap(*this);
			return *this;
		}
		ptr_index_iterator operator--(int) {
			ptr_index_iterator result(*this);
			--*this;
			return result;
		}
		SPROUT_CONSTEXPR ptr_index_iterator operator+(difference_type n) const {
			return ptr_index_iterator(p_, index_ + n);
		}
		SPROUT_CONSTEXPR ptr_index_iterator operator-(difference_type n) const {
			return ptr_index_iterator(p_, index_ - n);
		}
		ptr_index_iterator& operator+=(difference_type n) {
			ptr_index_iterator temp(p_, index_ + n);
			temp.swap(*this);
			return *this;
		}
		ptr_index_iterator& operator-=(difference_type n) {
			ptr_index_iterator temp(p_, index_ - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return p_[index_ + n];
		}
		friend SPROUT_CONSTEXPR difference_type operator-(ptr_index_iterator const& lhs, ptr_index_iterator const& rhs) {
			return lhs.index_ - rhs.index_;
		}
		friend SPROUT_CONSTEXPR ptr_index_iterator operator+(difference_type n, ptr_index_iterator const& it) {
			return it + n;
		}
	};

	//
	// swap
	//
	template<typename T>
	inline void
	swap(sprout::ptr_index_iterator<T>& lhs, sprout::ptr_index_iterator<T>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// make_ptr_index_iterator
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::ptr_index_iterator<T>
	make_ptr_index_iterator(T* p) {
		return sprout::ptr_index_iterator<T>(p);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::ptr_index_iterator<T>
	make_ptr_index_iterator(T* p, typename sprout::ptr_index_iterator<T>::difference_type index) {
		return sprout::ptr_index_iterator<T>(p, index);
	}

	//
	// as_iterator
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::ptr_index_iterator<T>
	as_iterator(T* p) {
		return sprout::make_ptr_index_iterator(p);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::ptr_index_iterator<T>
	as_iterator(T* p, typename std::iterator_traits<T*>::difference_type n) {
		return sprout::make_ptr_index_iterator(p, n);
	}

	template<typename Iterator>
	inline SPROUT_CONSTEXPR Iterator
	as_iterator(Iterator const& it) {
		return it;
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR Iterator
	as_iterator(Iterator const& it, typename std::iterator_traits<Iterator>::difference_type n) {
		return sprout::next(it, n);
	}

	//
	// as_iterator_base
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::ptr_index_iterator<T>::pointer
	as_iterator_base(sprout::ptr_index_iterator<T> const& it) {
		return it.ptr();
	}
	template<typename Iterator>
	inline SPROUT_CONSTEXPR Iterator
	as_iterator_base(Iterator const& it) {
		return it;
	}

	//
	// is_ptr_index_iterator
	//
	template<typename T>
	struct is_ptr_index_iterator
		: public std::false_type
	{};
	template<typename T>
	struct is_ptr_index_iterator<T const>
		: public sprout::is_ptr_index_iterator<T>
	{};
	template<typename T>
	struct is_ptr_index_iterator<T const volatile>
		: public sprout::is_ptr_index_iterator<T>
	{};
	template<typename T>
	struct is_ptr_index_iterator<sprout::ptr_index_iterator<T> >
		: public std::true_type
	{};

	//
	// iterator_next
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::ptr_index_iterator<T>
	iterator_next(sprout::ptr_index_iterator<T> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::ptr_index_iterator<T>
	iterator_prev(sprout::ptr_index_iterator<T> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_PTR_INDEX_ITERATOR_HPP
