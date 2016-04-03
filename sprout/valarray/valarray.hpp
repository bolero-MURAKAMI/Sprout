/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_VALARRAY_HPP
#define SPROUT_VALARRAY_VALARRAY_HPP

#include <type_traits>
#include <stdexcept>
#include <initializer_list>
#include <array>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/array/array.hpp>
#include <sprout/math/less.hpp>
#include <sprout/iterator/index_iterator.hpp>
#include <sprout/iterator/reverse_iterator.hpp>
#include <sprout/functional/negate.hpp>
#include <sprout/functional/bit_not.hpp>
#include <sprout/functional/logical_not.hpp>
#include <sprout/functional/plus_assign.hpp>
#include <sprout/functional/minus_assign.hpp>
#include <sprout/functional/multiplies_assign.hpp>
#include <sprout/functional/divides_assign.hpp>
#include <sprout/functional/modulus_assign.hpp>
#include <sprout/functional/bit_and_assign.hpp>
#include <sprout/functional/bit_or_assign.hpp>
#include <sprout/functional/bit_xor_assign.hpp>
#include <sprout/functional/shift_left_assign.hpp>
#include <sprout/functional/shift_right_assign.hpp>
#include <sprout/functional/bind2nd.hpp>
#include <sprout/algorithm/min_element.hpp>
#include <sprout/algorithm/max_element.hpp>
#include <sprout/algorithm/fixed/copy.hpp>
#include <sprout/algorithm/fixed/copy_backward.hpp>
#include <sprout/algorithm/fixed/transform.hpp>
#include <sprout/algorithm/fixed/rotate.hpp>
#include <sprout/algorithm/cxx14/copy.hpp>
#include <sprout/algorithm/cxx14/fill.hpp>
#include <sprout/algorithm/cxx14/for_each.hpp>
#include <sprout/numeric/accumulate.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include <sprout/type_traits/is_nothrow_copy_constructible.hpp>
#include <sprout/array/array.hpp>
#include <sprout/valarray/valarray_fwd.hpp>
#include <sprout/valarray/slice_array.hpp>
#include <sprout/valarray/gslice_array.hpp>
#include <sprout/valarray/mask_array.hpp>
#include <sprout/valarray/indirect_array.hpp>

namespace sprout {
	namespace detail {
		struct valarray_raw_construct_t {};

		template<typename T, std::size_t N>
		class valarray_construct_access;

		template<typename T, std::size_t N>
		class valarray_impl {
		public:
			typedef T value_type;
			typedef sprout::array<value_type, N> array_type;
		public:
			static SPROUT_CONSTEXPR std::size_t
			checked_size(std::size_t n) {
				return N >= n ? n
					: throw std::length_error("valarray<>: length exceeded")
					;
			}
		public:
			array_type array_;
			std::size_t size_;
		public:
			SPROUT_CONSTEXPR valarray_impl()
				: array_{{}}, size_(0)
			{}
			explicit SPROUT_CONSTEXPR valarray_impl(std::size_t n)
				: array_{{}}, size_(checked_size(n))
			{}
			template<sprout::index_t... Indexes>
			SPROUT_CONSTEXPR valarray_impl(
				sprout::index_tuple<Indexes...>,
				value_type const& value, std::size_t n
				)
				: array_{{
					(sprout::math::less(Indexes, n) ? value
						: value_type()
						)...
					}}
				, size_(checked_size(n))
			{}
			template<typename RandomAccessIterator, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR valarray_impl(
				sprout::index_tuple<Indexes...>,
				RandomAccessIterator first, std::size_t n
				)
				: array_{{
					(sprout::math::less(Indexes, n) ? first[Indexes]
						: value_type()
						)...
					}}
				, size_(checked_size(n))
			{}
			valarray_impl(valarray_impl const& v) = default;
			valarray_impl(valarray_impl&& v) = default;
			template<typename... Args, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR valarray_impl(
				sprout::index_tuple<Indexes...>,
				sprout::detail::valarray_raw_construct_t, std::size_t n, Args&&... args
				)
				: array_{{
					(sprout::math::less(Indexes, n) ? static_cast<value_type>(SPROUT_FORWARD(Args, args))
						: value_type()
						)...
					}}
				, size_(n)
			{}
		};
	}	// namespace detail

	//
	// valarray
	//
	template<typename T, std::size_t N>
	class valarray {
		friend class sprout::detail::valarray_construct_access<T, N>;
	private:
		typedef sprout::detail::valarray_impl<T, N> impl_type;
		typedef typename impl_type::array_type array_type;
	public:
		typedef typename array_type::value_type value_type;
		typedef typename array_type::iterator iterator;
		typedef typename array_type::const_iterator const_iterator;
		typedef typename array_type::reference reference;
		typedef typename array_type::const_reference const_reference;
		typedef typename array_type::size_type size_type;
		typedef typename array_type::difference_type difference_type;
		typedef typename array_type::pointer pointer;
		typedef typename array_type::const_pointer const_pointer;
		typedef typename array_type::reverse_iterator reverse_iterator;
		typedef typename array_type::const_reverse_iterator const_reverse_iterator;
		typedef value_type result_type;
	public:
		SPROUT_STATIC_CONSTEXPR size_type static_size = N;
	private:
		impl_type impl_;
	private:
		template<typename... Args, typename Enable = typename std::enable_if<(sizeof...(Args) <= N)>::type>
		SPROUT_CONSTEXPR valarray(sprout::detail::valarray_raw_construct_t, size_type n, Args&&... args)
			: impl_(
				sprout::index_pack<Args...>::make(),
				sprout::detail::valarray_raw_construct_t(), n, SPROUT_FORWARD(Args, args)...
				)
		{}
		SPROUT_CXX14_CONSTEXPR void
		maxcheck(size_type n) const {
			if (n > max_size()) {
				throw std::out_of_range("valarray<>: index out of range");
			}
		}
		SPROUT_CXX14_CONSTEXPR void
		lengthcheck(size_type n) const {
			if (n > max_size()) {
				throw std::length_error("valarray<>: length exceeded");
			}
		}
	public:
		// construct/destroy:
		SPROUT_CONSTEXPR valarray() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
		explicit SPROUT_CONSTEXPR valarray(std::size_t n)
			: impl_(n)
		{}
		SPROUT_CONSTEXPR valarray(value_type const& value, std::size_t n)
			: impl_(
				sprout::make_index_tuple<N>::make(),
				value, n
				)
		{}
		SPROUT_CONSTEXPR valarray(value_type const* first, std::size_t n)
			: impl_(
				sprout::make_index_tuple<N>::make(),
				first, n
				)
		{}
		valarray(valarray const&) = default;
		valarray(valarray&&) = default;
		SPROUT_INITIALIZER_LIST_CONSTEXPR valarray(std::initializer_list<value_type> il)
			: impl_(
				sprout::make_index_tuple<N>::make(),
				il.begin(), il.size()
				)
		{}
		SPROUT_CONSTEXPR valarray(sprout::slice_array<value_type, N> const& x)
			: impl_(
				sprout::make_index_tuple<N>::make(),
				x.begin(), x.size()
				)
		{}
		template<std::size_t M>
		SPROUT_CONSTEXPR valarray(sprout::gslice_array<value_type, N, M> const& x)
			: impl_(
				sprout::make_index_tuple<N>::make(),
				x.begin(), x.size()
				)
		{}
		template<std::size_t M>
		SPROUT_CONSTEXPR valarray(sprout::mask_array<value_type, N, M> const& x)
			: impl_(
				sprout::make_index_tuple<N>::make(),
				x.begin(), x.size()
				)
		{}
		template<std::size_t M>
		SPROUT_CONSTEXPR valarray(sprout::indirect_array<value_type, N, M> const& x)
			: impl_(
				sprout::make_index_tuple<N>::make(),
				x.begin(), x.size()
				)
		{}
		// assignment:
		SPROUT_CXX14_CONSTEXPR valarray&
		operator=(valarray const& rhs) {
			impl_.array_ = rhs.array_;
			impl_.size_ = rhs.size_;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR valarray&
		operator=(valarray&& rhs) SPROUT_NOEXCEPT {
			impl_.array_ = sprout::move(rhs.array_);
			impl_.size_ = sprout::move(rhs.size_);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR valarray&
		operator=(value_type const& rhs) {
			impl_.array_.fill(rhs);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR valarray&
		operator=(std::initializer_list<value_type> rhs) {
			lengthcheck(rhs.size());
			sprout::copy(rhs.begin(), rhs.end(), begin());
			impl_.size_ = rhs.size();
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR valarray&
		operator=(sprout::slice_array<value_type, N> const& rhs) {
			lengthcheck(rhs.size());
			sprout::copy(rhs.begin(), rhs.end(), begin());
			impl_.size_ = rhs.size();
			return *this;
		}
		template<std::size_t M>
		SPROUT_CXX14_CONSTEXPR valarray&
		operator=(sprout::gslice_array<value_type, N, M> const& rhs) {
			lengthcheck(rhs.size());
			sprout::copy(rhs.begin(), rhs.end(), begin());
			impl_.size_ = rhs.size();
			return *this;
		}
		template<std::size_t M>
		SPROUT_CXX14_CONSTEXPR valarray&
		operator=(sprout::mask_array<value_type, N, M> const& rhs) {
			lengthcheck(rhs.size());
			sprout::copy(rhs.begin(), rhs.end(), begin());
			impl_.size_ = rhs.size();
			return *this;
		}
		template<std::size_t M>
		SPROUT_CXX14_CONSTEXPR valarray&
		operator=(sprout::indirect_array<value_type, N, M> const& rhs) {
			lengthcheck(rhs.size());
			sprout::copy(rhs.begin(), rhs.end(), begin());
			impl_.size_ = rhs.size();
			return *this;
		}
		// element access:
		SPROUT_CONSTEXPR value_type const&
		operator[](std::size_t i) const {
			return impl_.array_[i];
		}
		SPROUT_CXX14_CONSTEXPR value_type&
		operator[](std::size_t i) {
			return impl_.array_[i];
		}
		// subset operations:
		SPROUT_CONSTEXPR valarray
		operator[](sprout::slice s) const {
			return valarray(sprout::slice_array<value_type, N>(const_cast<valarray&>(*this), s));
		}
		SPROUT_CXX14_CONSTEXPR sprout::slice_array<value_type, N>
		operator[](sprout::slice s) {
			return sprout::slice_array<value_type, N>(*this, s);
		}
		template<std::size_t M>
		SPROUT_CONSTEXPR valarray
		operator[](sprout::gslice<M> const& gs) const {
			return valarray(sprout::gslice_array<value_type, N, M>(const_cast<valarray&>(*this), gs));
		}
		template<std::size_t M>
		SPROUT_CXX14_CONSTEXPR sprout::gslice_array<value_type, N, M>
		operator[](sprout::gslice<M> const& gs) {
			return sprout::gslice_array<value_type, N, M>(*this, gs);
		}
		template<std::size_t M>
		SPROUT_CONSTEXPR valarray
		operator[](valarray<bool, M> const& vb) const {
			return valarray(sprout::mask_array<value_type, N, M>(const_cast<valarray&>(*this), vb));
		}
		template<std::size_t M>
		SPROUT_CXX14_CONSTEXPR sprout::mask_array<value_type, N, M>
		operator[](valarray<bool, M> const& vb) {
			return sprout::mask_array<value_type, N, M>(*this, vb);
		}
		template<std::size_t M>
		SPROUT_CONSTEXPR valarray
		operator[](valarray<std::size_t, M> const& vs) const {
			return valarray(sprout::indirect_array<value_type, N, M>(const_cast<valarray&>(*this), vs));
		}
		template<std::size_t M>
		SPROUT_CXX14_CONSTEXPR sprout::indirect_array<value_type, N, M>
		operator[](valarray<std::size_t, M> const& vs) {
			return sprout::indirect_array<value_type, N, M>(*this, vs);
		}
		// unary operators:
		SPROUT_CONSTEXPR valarray
		operator+() const {
			return *this;
		}
		SPROUT_CONSTEXPR valarray
		operator-() const {
			return sprout::fixed::transform(begin(), end(), *this, sprout::negate<>());
		}
		SPROUT_CONSTEXPR valarray
		operator~() const {
			return sprout::fixed::transform(begin(), end(), *this, sprout::bit_not<>());
		}
		SPROUT_CONSTEXPR valarray<bool, N>
		operator!() const {
			return sprout::fixed::transform<valarray<bool, N> >(begin(), end(), sprout::logical_not<>());
		}
		// computed assignment:
		SPROUT_CXX14_CONSTEXPR valarray&
		operator*=(value_type const& x) {
			sprout::for_each(begin(), end(), sprout::bind2nd(sprout::multiplies_assign<>(), x));
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR valarray&
		operator/=(value_type const& x) {
			sprout::for_each(begin(), end(), sprout::bind2nd(sprout::divides_assign<>(), x));
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR valarray&
		operator%=(value_type const& x) {
			sprout::for_each(begin(), end(), sprout::bind2nd(sprout::modulus_assign<>(), x));
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR valarray&
		operator+=(value_type const& x) {
			sprout::for_each(begin(), end(), sprout::bind2nd(sprout::plus_assign<>(), x));
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR valarray&
		operator-=(value_type const& x) {
			sprout::for_each(begin(), end(), sprout::bind2nd(sprout::minus_assign<>(), x));
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR valarray&
		operator^=(value_type const& x) {
			sprout::for_each(begin(), end(), sprout::bind2nd(sprout::bit_xor_assign<>(), x));
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR valarray&
		operator&=(value_type const& x) {
			sprout::for_each(begin(), end(), sprout::bind2nd(sprout::bit_and_assign<>(), x));
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR valarray&
		operator|=(value_type const& x) {
			sprout::for_each(begin(), end(), sprout::bind2nd(sprout::bit_or_assign<>(), x));
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR valarray&
		operator<<=(value_type const& x) {
			sprout::for_each(begin(), end(), sprout::bind2nd(sprout::shift_left_assign<>(), x));
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR valarray&
		operator>>=(value_type const& x) {
			sprout::for_each(begin(), end(), sprout::bind2nd(sprout::shift_right_assign<>(), x));
			return *this;
		}
		// member functions:
		SPROUT_CXX14_CONSTEXPR void
		swap(valarray& other) SPROUT_NOEXCEPT {
			sprout::swap(impl_.array_, other.impl_.array_);
			sprout::swap(impl_.size_, other.impl_.size_);
		}
		SPROUT_CONSTEXPR std::size_t
		size() const {
			return impl_.size_;
		}
		SPROUT_CONSTEXPR value_type
		sum() const {
			return sprout::accumulate(begin(), end(), value_type());
		}
		SPROUT_CONSTEXPR value_type
		min() const {
			return *sprout::min_element(begin(), end());
		}
		SPROUT_CONSTEXPR value_type
		max() const {
			return *sprout::max_element(begin(), end());
		}
		SPROUT_CONSTEXPR valarray
		shift(int i) const {
			return i > 0 ? sprout::fixed::copy(begin() + i, end(), *this)
				: i < 0 ? sprout::fixed::copy_backward(begin(), end() + i, *this)
				: *this
				;
		}
		SPROUT_CONSTEXPR valarray
		cshift(int i) const {
			return i > 0 ? sprout::fixed::rotate(*this, begin() + i)
				: i < 0 ? sprout::fixed::rotate(*this, end() + i)
				: *this
				;
		}
		SPROUT_CONSTEXPR valarray
		apply(value_type func(value_type)) const {
			return sprout::fixed::transform(begin(), end(), *this, func);
		}
		SPROUT_CONSTEXPR valarray
		apply(value_type func(value_type const&)) const {
			return sprout::fixed::transform(begin(), end(), *this, func);
		}
		template<typename F>
		SPROUT_CONSTEXPR valarray
		apply(F func) const {
			return sprout::fixed::transform(begin(), end(), *this, func);
		}
		SPROUT_CXX14_CONSTEXPR void
		resize(std::size_t n, value_type x = value_type()) {
			lengthcheck(n);
			impl_.size_ = n;
			impl_.array_.fill(x);
		}

		// modifiers (array):
		SPROUT_CXX14_CONSTEXPR void fill(const_reference value) {
			impl_.array_.fill(value);
		}
		SPROUT_CONSTEXPR valarray fill(const_reference value) const {
			return valarray(value, size());
		}
		SPROUT_CXX14_CONSTEXPR void assign(const_reference value) {
			impl_.array_.assign(value);
		}
		SPROUT_CONSTEXPR valarray assign(const_reference value) const {
			return valarray(value, size());
		}
		// iterators (array):
		SPROUT_CXX14_CONSTEXPR iterator begin() SPROUT_NOEXCEPT {
			return impl_.array_.begin();
		}
		SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT {
			return impl_.array_.begin();
		}
		SPROUT_CXX14_CONSTEXPR iterator end() SPROUT_NOEXCEPT {
			return impl_.array_.begin() + size();
		}
		SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
			return impl_.array_.begin() + size();
		}
		SPROUT_CXX14_CONSTEXPR reverse_iterator rbegin() SPROUT_NOEXCEPT {
			return impl_.array_.rend() - size();
		}
		SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT {
			return impl_.array_.rend() - size();
		}
		SPROUT_CXX14_CONSTEXPR reverse_iterator rend() SPROUT_NOEXCEPT {
			return impl_.array_.rend();
		}
		SPROUT_CONSTEXPR const_reverse_iterator rend() const SPROUT_NOEXCEPT {
			return impl_.array_.rend();
		}
		SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT {
			return impl_.array_.cbegin();
		}
		SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT {
			return impl_.array_.cbegin() + size();
		}
		SPROUT_CONSTEXPR const_reverse_iterator crbegin() const SPROUT_NOEXCEPT {
			return impl_.array_.crend() - size();
		}
		SPROUT_CONSTEXPR const_reverse_iterator crend() const SPROUT_NOEXCEPT {
			return impl_.array_.crend();
		}
		// capacity (array):
		SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT {
			return impl_.array_.max_size();
		}
		SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT {
			return size() != 0;
		}
		// element access (array):
		SPROUT_CXX14_CONSTEXPR reference at(size_type i) {
			return i < size() ? (*this)[i]
				: (throw std::out_of_range("valarray<>: index out of range"), (*this)[i])
				;
		}
		SPROUT_CONSTEXPR const_reference at(size_type i) const {
			return i < size() ? (*this)[i]
				: (throw std::out_of_range("valarray<>: index out of range"), (*this)[i])
				;
		}
		SPROUT_CXX14_CONSTEXPR reference front() {
			return impl_.array_.front();
		}
		SPROUT_CONSTEXPR const_reference front() const {
			return impl_.array_.front();
		}
		SPROUT_CXX14_CONSTEXPR reference back() {
			return (*this)[size() - 1];
		}
		SPROUT_CONSTEXPR const_reference back() const {
			return (*this)[size() - 1];
		}

		SPROUT_CXX14_CONSTEXPR pointer data() SPROUT_NOEXCEPT {
			return impl_.array_.data();
		}
		SPROUT_CONSTEXPR const_pointer data() const SPROUT_NOEXCEPT {
			return impl_.array_.data();
		}
		SPROUT_CXX14_CONSTEXPR pointer c_array() SPROUT_NOEXCEPT {
			return impl_.array_.c_array();
		}
		SPROUT_CONSTEXPR const_pointer c_array() const SPROUT_NOEXCEPT {
			return impl_.array_.c_array();
		}
		// others (array):
		SPROUT_CXX14_CONSTEXPR void rangecheck(size_type i) const {
			return i >= size() ? throw std::out_of_range("valarray<>: index out of range")
				: (void)0
				;
		}

		SPROUT_CXX14_CONSTEXPR iterator nth(size_type i) {
			return i < size() ? begin() + i
				: (throw std::out_of_range("valarray<>: index out of range"), iterator())
				;
		}
		SPROUT_CONSTEXPR const_iterator nth(size_type i) const {
			return i < size() ? begin() + i
				: (throw std::out_of_range("valarray<>: index out of range"), const_iterator())
				;
		}
		SPROUT_CXX14_CONSTEXPR size_type index_of(iterator p) SPROUT_NOEXCEPT {
			return impl_.array_.index_of(p);
		}
		SPROUT_CONSTEXPR size_type index_of(const_iterator p) const SPROUT_NOEXCEPT {
			return impl_.array_.index_of(p);
		}
	};
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR_OR_CONST typename sprout::valarray<T, N>::size_type sprout::valarray<T, N>::static_size;

	//
	// swap
	//
	template<typename T, std::size_t N>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::valarray<T, N>& lhs, sprout::valarray<T, N>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	namespace detail {
		template<typename T, std::size_t N>
		class valarray_construct_access {
		public:
			template<typename... Args>
			static SPROUT_CONSTEXPR sprout::valarray<T, N>
			raw_construct(typename sprout::valarray<T, N>::size_type n, Args&&... args) {
				return sprout::valarray<T, N>(sprout::detail::valarray_raw_construct_t(), n, SPROUT_FORWARD(Args, args)...);
			}
		};

		template<typename Container>
		struct make_construct_impl;

		template<typename T, std::size_t N>
		struct make_construct_impl<sprout::valarray<T, N> > {
		private:
			typedef sprout::valarray<T, N> copied_type;
		public:
			template<typename... Args>
			static SPROUT_CONSTEXPR copied_type
			make(Args&&... args) {
				typedef sprout::detail::valarray_construct_access<T, N> access_type;
				return access_type::raw_construct(sizeof...(args), SPROUT_FORWARD(Args, args)...);
			}
			template<typename... Args>
			static SPROUT_CONSTEXPR copied_type
			sized_make(typename copied_type::size_type size, Args&&... args) {
				typedef sprout::detail::valarray_construct_access<T, N> access_type;
				return access_type::raw_construct(size, SPROUT_FORWARD(Args, args)...);
			}
		};
	}	// namespace detail

	//
	// to_valarray
	//
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	to_valarray(sprout::valarray<T, N> const& arr)
	SPROUT_NOEXCEPT_IF(sprout::is_nothrow_copy_constructible<T>::value)
	{
		return arr;
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<typename std::remove_cv<T>::type, N>
	to_valarray(T (& arr)[N])
	SPROUT_NOEXCEPT_IF(sprout::is_nothrow_copy_constructible<typename std::remove_cv<T>::type>::value)
	{
		return sprout::valarray<typename std::remove_cv<T>::type, N>(arr, N);
	}
	namespace detail {
		template<typename T, std::size_t N, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::valarray<T, N>
		to_valarray_impl(std::array<T, N> const& arr, sprout::index_tuple<Indexes...>)
		SPROUT_NOEXCEPT_IF(sprout::is_nothrow_copy_constructible<T>::value)
		{
			typedef sprout::detail::make_construct_impl<sprout::valarray<T, N> > construct_type;
			return construct_type::make(arr[Indexes]...);
		}
	}	// namespace detail
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	to_valarray(std::array<T, N> const& arr)
	SPROUT_NOEXCEPT_IF(sprout::is_nothrow_copy_constructible<T>::value)
	{
		return sprout::detail::to_valarray_impl(arr, sprout::make_index_tuple<N>::make());
	}
	namespace detail {
		template<typename T, std::size_t N, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::valarray<T, N>
		to_valarray_impl(sprout::array<T, N> const& arr, sprout::index_tuple<Indexes...>)
		SPROUT_NOEXCEPT_IF(sprout::is_nothrow_copy_constructible<T>::value)
		{
			typedef sprout::detail::make_construct_impl<sprout::valarray<T, N> > construct_type;
			return construct_type::make(arr[Indexes]...);
		}
	}	// namespace detail
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::valarray<T, N>
	to_valarray(sprout::array<T, N> const& arr)
	SPROUT_NOEXCEPT_IF(sprout::is_nothrow_copy_constructible<T>::value)
	{
		return sprout::detail::to_valarray_impl(arr, sprout::make_index_tuple<N>::make());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_VALARRAY_HPP
