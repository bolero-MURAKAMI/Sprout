/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ARRAY_ARRAY_HPP
#define SPROUT_ARRAY_ARRAY_HPP

#include <utility>
#include <type_traits>
#include <stdexcept>
#include <array>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/reverse_iterator.hpp>
#include <sprout/iterator/const_iterator_cast.hpp>
#include <sprout/algorithm/cxx14/copy.hpp>
#include <sprout/algorithm/cxx14/move.hpp>
#include <sprout/algorithm/cxx14/fill_n.hpp>
#include <sprout/algorithm/cxx14/swap_ranges.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/type_traits/is_nothrow_copy_constructible.hpp>
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
#	include <sprout/iterator/index_iterator.hpp>
#endif

namespace sprout {
	//
	// array
	//
	template<typename T, std::size_t N>
	class array {
	public:
		typedef T value_type;
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		typedef sprout::index_iterator<array&, true> iterator;
		typedef sprout::index_iterator<array const&, true> const_iterator;
#else
		typedef T* iterator;
		typedef T const* const_iterator;
#endif
		typedef T& reference;
		typedef T const& const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T const* const_pointer;
		typedef sprout::reverse_iterator<iterator> reverse_iterator;
		typedef sprout::reverse_iterator<const_iterator> const_reverse_iterator;
	public:
		SPROUT_STATIC_CONSTEXPR size_type static_size = N;
	private:
		template<sprout::index_t Index>
		static SPROUT_CONSTEXPR value_type const&
		dummy_get(value_type const& value) {
			return value;
		}
		template<sprout::index_t... Indexes>
		static SPROUT_CONSTEXPR array
		fill_impl(value_type const& value, sprout::index_tuple<Indexes...>) {
			return array{{dummy_get<Indexes>(value)...}};
		}
	public:
		value_type elems[static_size ? static_size : 1];
	private:
		template<sprout::index_t... Indexes>
		SPROUT_CONSTEXPR std::array<T, N>
		to_std_array(sprout::index_tuple<Indexes...>) const
		SPROUT_NOEXCEPT_IF(sprout::is_nothrow_copy_constructible<typename std::remove_cv<T>::type>::value)
		{
			return std::array<T, N>{{elems[Indexes]...}};
		}
	public:
		// construct/copy/destroy:
		template<typename T2>
		SPROUT_CXX14_CONSTEXPR array& operator=(array<T2, N> const& rhs) {
			sprout::copy(rhs.begin(), rhs.end(), begin());
			return *this;
		}
		template<typename T2>
		SPROUT_CXX14_CONSTEXPR array& operator=(array<T2, N>&& rhs) {
			sprout::move(rhs.begin(), rhs.end(), begin());
			return *this;
		}
		// modifiers:
		SPROUT_CXX14_CONSTEXPR void fill(const_reference value) {
			sprout::fill_n(begin(), size(), value);
		}
		SPROUT_CONSTEXPR array fill(const_reference value) const {
			return fill_impl(value, sprout::index_n<0, N>::make());
		}
		SPROUT_CXX14_CONSTEXPR void assign(const_reference value) {
			fill(value);
		}
		SPROUT_CONSTEXPR array assign(const_reference value) const {
			return fill(value);
		}
		SPROUT_CXX14_CONSTEXPR void swap(array& other)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::swap(std::declval<T&>(), std::declval<T&>()))
		{
			sprout::swap_ranges(other.begin(), other.end(), begin());
		}
		// iterators:
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		SPROUT_CXX14_CONSTEXPR iterator begin() SPROUT_NOEXCEPT {
			return iterator(*this, 0);
		}
		SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT {
			return const_iterator(*this, 0);
		}
		SPROUT_CXX14_CONSTEXPR iterator end() SPROUT_NOEXCEPT {
			return iterator(*this, size());
		}
		SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
			return const_iterator(*this, size());
		}
#else
		SPROUT_CXX14_CONSTEXPR iterator begin() SPROUT_NOEXCEPT {
			return iterator(elems);
		}
		SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT {
			return iterator(elems);
		}
		SPROUT_CXX14_CONSTEXPR iterator end() SPROUT_NOEXCEPT {
			return iterator(elems) + size();
		}
		SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
			return iterator(elems) + size();
		}
#endif
		SPROUT_CXX14_CONSTEXPR reverse_iterator rbegin() SPROUT_NOEXCEPT {
			return reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		SPROUT_CXX14_CONSTEXPR reverse_iterator rend() SPROUT_NOEXCEPT {
			return reverse_iterator(begin());
		}
		SPROUT_CONSTEXPR const_reverse_iterator rend() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
		}
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT {
			return const_iterator(*this, 0);
		}
		SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT {
			return const_iterator(*this, size());
		}
#else
		SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT {
			return const_iterator(elems);
		}
		SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT {
			return const_iterator(elems) + size();
		}
#endif
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
			return size() == 0;
		}
		// element access:
		SPROUT_CXX14_CONSTEXPR reference operator[](size_type i) {
			return elems[i];
		}
		SPROUT_CONSTEXPR const_reference operator[](size_type i) const {
			return elems[i];
		}
		SPROUT_CXX14_CONSTEXPR reference at(size_type i) {
			return i < size() ? elems[i]
				: (throw std::out_of_range("array<>: index out of range"), elems[i])
				;
		}
		SPROUT_CONSTEXPR const_reference at(size_type i) const {
			return i < size() ? elems[i]
				: (throw std::out_of_range("array<>: index out of range"), elems[i])
				;
		}
		SPROUT_CXX14_CONSTEXPR reference front() {
			return elems[0];
		}
		SPROUT_CONSTEXPR const_reference front() const {
			return elems[0];
		}
		SPROUT_CXX14_CONSTEXPR reference back() {
			return elems[size() - 1];
		}
		SPROUT_CONSTEXPR const_reference back() const {
			return elems[size() - 1];
		}

		SPROUT_CXX14_CONSTEXPR pointer data() SPROUT_NOEXCEPT {
			return elems;
		}
		SPROUT_CONSTEXPR const_pointer data() const SPROUT_NOEXCEPT {
			return elems;
		}
		SPROUT_CXX14_CONSTEXPR pointer c_array() SPROUT_NOEXCEPT {
			return data();
		}
		SPROUT_CONSTEXPR const_pointer c_array() const SPROUT_NOEXCEPT {
			return data();
		}
		// others:
		SPROUT_CXX14_CONSTEXPR void rangecheck(size_type i) const {
			return i >= size() ? throw std::out_of_range("array<>: index out of range")
				: (void)0
				;
		}

#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		SPROUT_CXX14_CONSTEXPR iterator nth(size_type i) {
			return i < size() ? iterator(*this, i)
				: (throw std::out_of_range("array<>: index out of range"), iterator())
				;
		}
		SPROUT_CONSTEXPR const_iterator nth(size_type i) const {
			return i < size() ? const_iterator(*this, i)
				: (throw std::out_of_range("array<>: index out of range"), const_iterator())
				;
		}
		SPROUT_CXX14_CONSTEXPR size_type index_of(iterator p) SPROUT_NOEXCEPT {
			return p.index();
		}
		SPROUT_CONSTEXPR size_type index_of(const_iterator p) const SPROUT_NOEXCEPT {
			return p.index();
		}
#else
		SPROUT_CXX14_CONSTEXPR iterator nth(size_type i) {
			return i < size() ? iterator(elems) + i
				: (throw std::out_of_range("array<>: index out of range"), iterator())
				;
		}
		SPROUT_CONSTEXPR const_iterator nth(size_type i) const {
			return i < size() ? const_iterator(elems) + i
				: (throw std::out_of_range("array<>: index out of range"), const_iterator())
				;
		}
		SPROUT_CXX14_CONSTEXPR size_type index_of(iterator p) SPROUT_NOEXCEPT {
			return sprout::distance(begin(), p);
		}
		SPROUT_CONSTEXPR size_type index_of(const_iterator p) const SPROUT_NOEXCEPT {
			return sprout::distance(begin(), p);
		}
#endif

		SPROUT_CONSTEXPR operator std::array<T, N>() const
		SPROUT_NOEXCEPT_IF(sprout::is_nothrow_copy_constructible<typename std::remove_cv<T>::type>::value)
		{
			return to_std_array(sprout::make_index_tuple<N>::make());
		}
	};
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR_OR_CONST typename sprout::array<T, N>::size_type sprout::array<T, N>::static_size;

	//
	// swap
	//
	template<typename T, std::size_t N>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::array<T, N>& lhs, sprout::array<T, N>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::array<T, N>::iterator
	range_begin(sprout::array<T, N>& t) SPROUT_NOEXCEPT {
		return sprout::const_iterator_cast<typename sprout::array<T, N>::iterator>(sprout::as_const(t).begin());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::array<T, N>::iterator
	range_end(sprout::array<T, N>& t) SPROUT_NOEXCEPT {
		return sprout::const_iterator_cast<typename sprout::array<T, N>::iterator>(sprout::as_const(t).end());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::array<T, N>::reference
	range_at(sprout::array<T, N>& t, typename sprout::array<T, N>::size_type i) {
		return const_cast<typename sprout::array<T, N>::reference>(sprout::as_const(t).at(i));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::array<T, N>::reference
	range_front(sprout::array<T, N>& t) {
		return const_cast<typename sprout::array<T, N>::reference>(sprout::as_const(t).front());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::array<T, N>::reference
	range_back(sprout::array<T, N>& t) {
		return const_cast<typename sprout::array<T, N>::reference>(sprout::as_const(t).back());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::array<T, N>::iterator
	range_nth(sprout::array<T, N>& t, typename sprout::array<T, N>::size_type i) {
		return sprout::const_iterator_cast<typename sprout::array<T, N>::iterator>(sprout::as_const(t).nth(i));
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::array<T, N>::size_type
	range_index_of(sprout::array<T, N>& t, typename sprout::array<T, N>::iterator p) SPROUT_NOEXCEPT {
		return sprout::as_const(t).index_of(p);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::array<T, N>::pointer
	range_data(sprout::array<T, N>& t) SPROUT_NOEXCEPT {
		return const_cast<typename sprout::array<T, N>::pointer>(sprout::as_const(t).data());
	}

	//
	// to_array
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::array<T, N>
	to_array(sprout::array<T, N> const& arr)
	SPROUT_NOEXCEPT_IF(sprout::is_nothrow_copy_constructible<T>::value)
	{
		return arr;
	}
	namespace detail {
		template<typename T, std::size_t N, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::array<typename std::remove_cv<T>::type, N>
		to_array_impl(T (& arr)[N], sprout::index_tuple<Indexes...>)
		SPROUT_NOEXCEPT_IF(sprout::is_nothrow_copy_constructible<typename std::remove_cv<T>::type>::value)
		{
			return sprout::array<typename std::remove_cv<T>::type, N>{{arr[Indexes]...}};
		}
	}	// namespace detail
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::array<typename std::remove_cv<T>::type, N>
	to_array(T (& arr)[N])
	SPROUT_NOEXCEPT_IF(sprout::is_nothrow_copy_constructible<typename std::remove_cv<T>::type>::value)
	{
		return sprout::detail::to_array_impl(arr, sprout::make_index_tuple<N>::make());
	}
	namespace detail {
		template<typename T, std::size_t N, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::array<T, N>
		to_array_impl(std::array<T, N> const& arr, sprout::index_tuple<Indexes...>)
		SPROUT_NOEXCEPT_IF(sprout::is_nothrow_copy_constructible<T>::value)
		{
			return sprout::array<T, N>{{arr[Indexes]...}};
		}
	}	// namespace detail
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::array<T, N>
	to_array(std::array<T, N> const& arr)
	SPROUT_NOEXCEPT_IF(sprout::is_nothrow_copy_constructible<T>::value)
	{
		return sprout::detail::to_array_impl(arr, sprout::make_index_tuple<N>::make());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ARRAY_ARRAY_HPP
