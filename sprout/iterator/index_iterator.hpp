/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_INDEX_ITERATOR_HPP
#define SPROUT_ITERATOR_INDEX_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/iterator/const_iterator_cast.hpp>
#include <sprout/iterator/detail/iterator_to_pointer.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// index_iterator
	//
	template<typename Container, bool ConvertibleToPointer = false>
	class index_iterator
		: public std::iterator<
			std::random_access_iterator_tag,
			typename sprout::container_traits<typename std::remove_reference<Container>::type>::value_type,
			typename sprout::container_traits<typename std::remove_reference<Container>::type>::difference_type,
			typename std::conditional<
				std::is_const<typename std::remove_reference<Container>::type>::value,
				typename sprout::container_traits<typename std::remove_reference<Container>::type>::const_pointer,
				typename sprout::container_traits<typename std::remove_reference<Container>::type>::pointer
			>::type,
			typename std::conditional<
				std::is_const<typename std::remove_reference<Container>::type>::value,
				typename sprout::container_traits<typename std::remove_reference<Container>::type>::const_reference,
				typename sprout::container_traits<typename std::remove_reference<Container>::type>::reference
			>::type
		>
		, public sprout::detail::iterator_to_pointer_base<
			sprout::index_iterator<Container, ConvertibleToPointer>,
			typename std::conditional<
				std::is_const<typename std::remove_reference<Container>::type>::value,
				typename sprout::container_traits<typename std::remove_reference<Container>::type>::const_pointer,
				typename sprout::container_traits<typename std::remove_reference<Container>::type>::pointer
			>::type,
			ConvertibleToPointer
		>
	{
	public:
		typedef Container container_type;
		typedef typename sprout::container_traits<typename std::remove_reference<container_type>::type> traits_type;
		typedef typename std::conditional<
			std::is_reference<container_type>::value,
			typename std::remove_reference<container_type>::type const&,
			typename std::remove_reference<container_type>::type const
		>::type const_container_type;
	private:
		typedef std::iterator<
			std::random_access_iterator_tag,
			typename traits_type::value_type,
			typename traits_type::difference_type,
			typename std::conditional<
				std::is_const<typename std::remove_reference<container_type>::type>::value,
				typename traits_type::const_pointer,
				typename traits_type::pointer
			>::type,
			typename std::conditional<
				std::is_const<typename std::remove_reference<container_type>::type>::value,
				typename traits_type::const_reference,
				typename traits_type::reference
			>::type
		> base_type;
		typedef sprout::value_holder<container_type> holder_type;
	public:
		typedef typename base_type::iterator_category iterator_category;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::difference_type difference_type;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::reference reference;
		typedef typename traits_type::size_type size_type;
	private:
		holder_type holder_;
		difference_type index_;
	private:
		SPROUT_CONSTEXPR index_iterator(holder_type const& r, difference_type index)
			: holder_(r), index_(index)
		{}
	public:
		SPROUT_CONSTEXPR index_iterator()
			: holder_(), index_()
		{}
		index_iterator(index_iterator const&) = default;
		explicit SPROUT_CONSTEXPR index_iterator(typename holder_type::param_type p)
			: holder_(p), index_(0)
		{}
		SPROUT_CONSTEXPR index_iterator(typename holder_type::param_type p, difference_type index)
			: holder_(p), index_(index)
		{}
		SPROUT_CONSTEXPR operator index_iterator<const_container_type>() const {
			return index_iterator<const_container_type>(holder_.get(), index_);
		}
		SPROUT_CONSTEXPR typename holder_type::mutable_or_const_reference base() const {
			return holder_.get();
		}
		SPROUT_CONSTEXPR difference_type index() const {
			return index_;
		}
		SPROUT_CONSTEXPR index_iterator next() const {
			return index_iterator(holder_, index_ + 1);
		}
		SPROUT_CONSTEXPR index_iterator prev() const {
			return index_iterator(holder_, index_ - 1);
		}
		SPROUT_CXX14_CONSTEXPR void swap(index_iterator& other)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(holder_, other.holder_)))
		{
			sprout::swap(holder_, other.holder_);
			sprout::swap(index_, other.index_);
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return holder_.get()[index_];
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &holder_.get()[index_];
		}
		SPROUT_CXX14_CONSTEXPR index_iterator& operator++() {
			index_iterator temp(next());
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR index_iterator operator++(int) {
			index_iterator result(*this);
			++*this;
			return result;
		}
		SPROUT_CXX14_CONSTEXPR index_iterator& operator--() {
			index_iterator temp(prev());
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR index_iterator operator--(int) {
			index_iterator result(*this);
			--*this;
			return result;
		}
		SPROUT_CONSTEXPR index_iterator operator+(difference_type n) const {
			return index_iterator(holder_, index_ + n);
		}
		SPROUT_CONSTEXPR index_iterator operator-(difference_type n) const {
			return index_iterator(holder_, index_ - n);
		}
		SPROUT_CXX14_CONSTEXPR index_iterator& operator+=(difference_type n) {
			index_iterator temp(holder_, index_ + n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR index_iterator& operator-=(difference_type n) {
			index_iterator temp(holder_, index_ - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return holder_.get()[index_ + n];
		}
	};

	template<typename Container1, typename Container2, bool C>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<typename std::decay<Container1>::type, typename std::decay<Container2>::type>::value,
		bool
	>::type
	operator==(sprout::index_iterator<Container1, C> const& lhs, sprout::index_iterator<Container2, C> const& rhs) {
		return lhs.index() == rhs.index();
	}
	template<typename Container1, typename Container2, bool C>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<typename std::decay<Container1>::type, typename std::decay<Container2>::type>::value,
		bool
	>::type
	operator!=(sprout::index_iterator<Container1, C> const& lhs, sprout::index_iterator<Container2, C> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Container1, typename Container2, bool C>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<typename std::decay<Container1>::type, typename std::decay<Container2>::type>::value,
		bool
	>::type
	operator<(sprout::index_iterator<Container1, C> const& lhs, sprout::index_iterator<Container2, C> const& rhs) {
		return lhs.index() < rhs.index();
	}
	template<typename Container1, typename Container2, bool C>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<typename std::decay<Container1>::type, typename std::decay<Container2>::type>::value,
		bool
	>::type
	operator>(sprout::index_iterator<Container1, C> const& lhs, sprout::index_iterator<Container2, C> const& rhs) {
		return rhs < lhs;
	}
	template<typename Container1, typename Container2, bool C>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<typename std::decay<Container1>::type, typename std::decay<Container2>::type>::value,
		bool
	>::type
	operator<=(sprout::index_iterator<Container1, C> const& lhs, sprout::index_iterator<Container2, C> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Container1, typename Container2, bool C>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<typename std::decay<Container1>::type, typename std::decay<Container2>::type>::value,
		bool
	>::type
	operator>=(sprout::index_iterator<Container1, C> const& lhs, sprout::index_iterator<Container2, C> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename Container1, typename Container2, bool C>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<typename std::decay<Container1>::type, typename std::decay<Container2>::type>::value,
		decltype(
			std::declval<typename std::iterator_traits<sprout::index_iterator<Container1, C> >::difference_type>()
				- std::declval<typename std::iterator_traits<sprout::index_iterator<Container2, C> >::difference_type>()
			)
	>::type
	operator-(sprout::index_iterator<Container1, C> const& lhs, sprout::index_iterator<Container2, C> const& rhs) {
		return lhs.index() - rhs.index();
	}
	template<typename Container, bool C>
	inline SPROUT_CONSTEXPR sprout::index_iterator<Container, C>
	operator+(typename sprout::index_iterator<Container, C>::difference_type n, sprout::index_iterator<Container, C> const& it) {
		return it + n;
	}

	//
	// swap
	//
	template<typename Container, bool C>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::index_iterator<Container, C>& lhs, sprout::index_iterator<Container, C>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// is_index_iterator
	//
	template<typename T>
	struct is_index_iterator
		: public sprout::false_type
	{};
	template<typename T>
	struct is_index_iterator<T const>
		: public sprout::is_index_iterator<T>
	{};
	template<typename T>
	struct is_index_iterator<T const volatile>
		: public sprout::is_index_iterator<T>
	{};
	template<typename Container, bool C>
	struct is_index_iterator<sprout::index_iterator<Container, C> >
		: public sprout::true_type
	{};

	//
	// iterator_next
	//
	template<typename Container, bool C>
	inline SPROUT_CONSTEXPR sprout::index_iterator<Container, C>
	iterator_next(sprout::index_iterator<Container, C> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename Container, bool C>
	inline SPROUT_CONSTEXPR sprout::index_iterator<Container, C>
	iterator_prev(sprout::index_iterator<Container, C> const& it) {
		return it.prev();
	}

	//
	// is_const_iterator_cast_convertible
	//
	template<typename FromContainer, typename ToContainer, bool C>
	struct is_const_iterator_cast_convertible<sprout::index_iterator<FromContainer, C>, sprout::index_iterator<ToContainer, C> >
		: public std::is_same<typename std::decay<FromContainer>::type, typename std::decay<ToContainer>::type>
	{};
	//
	// const_iterator_conversion
	//
	template<
		typename T,
		typename Container, bool C,
		typename sprout::enabler_if<sprout::is_const_iterator_cast_convertible<sprout::index_iterator<Container, C>, T>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR T
	const_iterator_conversion(sprout::index_iterator<Container, C> const& it) {
		return T(const_cast<typename T::container_type>(it.base()), it.index());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_INDEX_ITERATOR_HPP
