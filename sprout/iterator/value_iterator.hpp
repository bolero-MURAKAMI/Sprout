#ifndef SPROUT_ITERATOR_VALUE_ITERATOR_HPP
#define SPROUT_ITERATOR_VALUE_ITERATOR_HPP

#include <cstddef>
#include <limits>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/utility/value_holder.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// value_iterator
	//
	template<typename T>
	class value_iterator
		: public std::iterator<
			std::random_access_iterator_tag,
			typename sprout::value_holder<T>::value_type,
			std::ptrdiff_t,
			typename sprout::value_holder<T>::mutable_or_const_pointer,
			typename sprout::value_holder<T>::mutable_or_const_reference
		>
	{
	public:
		typedef T type;
		typedef typename std::conditional<
			std::is_reference<type>::value,
			typename std::decay<type>::type const&,
			typename std::decay<type>::type const
		>::type const_type;
	private:
		typedef std::iterator<
			std::random_access_iterator_tag,
			typename sprout::value_holder<T>::value_type,
			std::ptrdiff_t,
			typename sprout::value_holder<T>::mutable_or_const_pointer,
			typename sprout::value_holder<T>::mutable_or_const_reference
		> base_type;
	public:
		typedef typename base_type::iterator_category iterator_category;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::difference_type difference_type;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::reference reference;
	private:
		sprout::value_holder<T> holder_;
		difference_type count_;
	private:
		SPROUT_CONSTEXPR value_iterator(sprout::value_holder<T> const& r, difference_type count)
			: holder_(r), count_(count)
		{}
	public:
		SPROUT_CONSTEXPR value_iterator()
			: holder_(), count_()
		{}
		value_iterator(value_iterator const&) = default;
		explicit SPROUT_CONSTEXPR value_iterator(
			typename sprout::value_holder<T>::param_type p,
			difference_type count = std::numeric_limits<difference_type>::max()
			)
			: holder_(p), count_(count)
		{}
		operator value_iterator<const_type>() const {
			return value_iterator<const_type>(holder_.get(), count_);
		}
		SPROUT_CONSTEXPR value_iterator next() const {
			return value_iterator(holder_, count_ != 0 ? count_ - 1 : count_);
		}
		SPROUT_CONSTEXPR value_iterator prev() const {
			return value_iterator(holder_, count_ != 0 ? count_ + 1 : count_);
		}
		void swap(value_iterator& other)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(holder_, other.holder_)))
		{
			sprout::swap(holder_, other.holder_);
			sprout::swap(count_, other.count_);
		}
		friend SPROUT_CONSTEXPR bool operator==(value_iterator const& lhs, value_iterator const& rhs) {
			return lhs.count_ == rhs.count_ && (lhs.count_ == 0 || lhs.holder_.get() == rhs.holder_.get());
		}
		friend SPROUT_CONSTEXPR bool operator!=(value_iterator const& lhs, value_iterator const& rhs) {
			return !(lhs == rhs);
		}
		friend SPROUT_CONSTEXPR bool operator<(value_iterator const& lhs, value_iterator const& rhs) {
			return lhs.count_ > rhs.count_;
		}
		friend SPROUT_CONSTEXPR bool operator>(value_iterator const& lhs, value_iterator const& rhs) {
			return rhs < lhs;
		}
		friend SPROUT_CONSTEXPR bool operator<=(value_iterator const& lhs, value_iterator const& rhs) {
			return !(rhs < lhs);
		}
		friend SPROUT_CONSTEXPR bool operator>=(value_iterator const& lhs, value_iterator const& rhs) {
			return !(lhs < rhs);
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return count_ != 0
				? holder_.get()
				: (throw std::out_of_range("value_iterator<>: dereference at out of range"), holder_.get())
				;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return count_ != 0
				? holder_.get_pointer()
				: throw std::out_of_range("value_iterator<>: dereference at out of range")
				;
		}
		value_iterator& operator++() {
			value_iterator temp(next());
			temp.swap(*this);
			return *this;
		}
		value_iterator operator++(int) {
			value_iterator result(*this);
			++*this;
			return result;
		}
		value_iterator& operator--() {
			value_iterator temp(prev());
			temp.swap(*this);
			return *this;
		}
		value_iterator operator--(int) {
			value_iterator result(*this);
			--*this;
			return result;
		}
		SPROUT_CONSTEXPR value_iterator operator+(difference_type n) const {
			return value_iterator(holder_, count_ - n);
		}
		SPROUT_CONSTEXPR value_iterator operator-(difference_type n) const {
			return value_iterator(holder_, count_ + n);
		}
		value_iterator& operator+=(difference_type n) {
			value_iterator temp(holder_, count_ - n);
			temp.swap(*this);
			return *this;
		}
		value_iterator& operator-=(difference_type n) {
			value_iterator temp(holder_, count_ + n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return holder_.get();
		}
		friend SPROUT_CONSTEXPR difference_type operator-(value_iterator const& lhs, value_iterator const& rhs) {
			return rhs.count_ - lhs.count_;
		}
		friend SPROUT_CONSTEXPR value_iterator operator+(difference_type n, value_iterator const& it) {
			return it + n;
		}
	};

	//
	// swap
	//
	template<typename T>
	inline void
	swap(sprout::value_iterator<T>& lhs, sprout::value_iterator<T>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::value_iterator<T>
	iterator_next(sprout::value_iterator<T> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::value_iterator<T>
	iterator_prev(sprout::value_iterator<T> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_VALUE_ITERATOR_HPP
