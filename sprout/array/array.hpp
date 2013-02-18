#ifndef SPROUT_ARRAY_ARRAY_HPP
#define SPROUT_ARRAY_ARRAY_HPP

#include <cstddef>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/reverse_iterator.hpp>
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
	public:
		void fill(const_reference value) {
			std::fill_n(begin(), size(), value);
		}
		SPROUT_CONSTEXPR array fill(const_reference value) const {
			return fill_impl(value, sprout::index_n<0, N>::make());
		}
		void swap(array<T, N>& other)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::swap(std::declval<T&>(), std::declval<T&>())))
		{
			std::swap_ranges(other.begin(), other.end(), begin());
		}
		// iterators:
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		iterator begin() SPROUT_NOEXCEPT {
			return iterator(*this, 0);
		}
		SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT {
			return const_iterator(*this, 0);
		}
		iterator end() SPROUT_NOEXCEPT {
			return iterator(*this, size());
		}
		SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
			return const_iterator(*this, size());
		}
#else
		iterator begin() SPROUT_NOEXCEPT {
			return &elems[0];
		}
		SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT {
			return &elems[0];
		}
		iterator end() SPROUT_NOEXCEPT {
			return &elems[0] + size();
		}
		SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
			return &elems[0] + size();
		}
#endif
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
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT {
			return const_iterator(*this, 0);
		}
		SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT {
			return const_iterator(*this, size());
		}
#else
		SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT {
			return &elems[0];
		}
		SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT {
			return &elems[0] + size();
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
		reference operator[](size_type i) {
			return elems[i];
		}
		SPROUT_CONSTEXPR const_reference operator[](size_type i) const {
			return elems[i];
		}
		reference at(size_type i) {
			return i < size()
				? elems[i]
				: (throw std::out_of_range("array<>: index out of range"), elems[i])
				;
		}
		SPROUT_CONSTEXPR const_reference at(size_type i) const {
			return i < size()
				? elems[i]
				: (throw std::out_of_range("array<>: index out of range"), elems[i])
				;
		}
		reference front() {
			return elems[0];
		}
		SPROUT_CONSTEXPR const_reference front() const {
			return elems[0];
		}
		reference back() {
			return elems[size() - 1];
		}
		SPROUT_CONSTEXPR const_reference back() const {
			return elems[size() - 1];
		}

		pointer data() SPROUT_NOEXCEPT {
			return &elems[0];
		}
		SPROUT_CONSTEXPR const_pointer data() const SPROUT_NOEXCEPT {
			return &elems[0];
		}
		// others:
		template<typename T2>
		array<T, N>& operator=(array<T2, N> const& rhs) {
			std::copy(rhs.begin(), rhs.end(), begin());
			return *this;
		}
		template<typename T2>
		array<T, N>& operator=(array<T2, N>&& rhs) {
			std::move(rhs.begin(), rhs.end(), begin());
			return *this;
		}
		pointer c_array() SPROUT_NOEXCEPT {
			return &elems[0];
		}
		void assign(const_reference value) {
			fill(value);
		}
		SPROUT_CONSTEXPR array assign(const_reference value) const {
			return fill(value);
		}
		void rangecheck(size_type i) const {
			if (i >= size()) {
				throw std::out_of_range("array<>: index out of range");
			}
		}
	};
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR_OR_CONST typename sprout::array<T, N>::size_type sprout::array<T, N>::static_size;

	//
	// swap
	//
	template<typename T, std::size_t N>
	inline void
	swap(sprout::array<T, N>& lhs, sprout::array<T, N>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	namespace detail {
		template<typename T, std::size_t N, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::array<T, N>
		to_array_impl(T const (& arr)[N], sprout::index_tuple<Indexes...>) {
			return sprout::array<T, N>{{arr[Indexes]...}};
		}
	}	// namespace detail
	//
	// to_array
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::array<T, N>
	to_array(T const (& arr)[N]) {
		return sprout::detail::to_array_impl(arr, sprout::index_range<0, N>::make());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ARRAY_ARRAY_HPP
