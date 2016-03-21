/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_SUB_ARRAY_SUB_ARRAY_HPP
#define SPROUT_SUB_ARRAY_SUB_ARRAY_HPP

#include <utility>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/cxx14/fill_n.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/move.hpp>

namespace sprout {
	namespace detail {
		struct is_non_reference_array_tag {};
		struct is_not_non_reference_array_tag {};

		template<typename Container>
		class sub_array_impl {
		public:
			typedef Container container_type;
			typedef typename std::remove_reference<container_type>::type internal_type;
		public:
			SPROUT_STATIC_CONSTEXPR bool is_reference = std::is_reference<container_type>::value;
			SPROUT_STATIC_CONSTEXPR bool is_const = std::is_const<internal_type>::value;
		public:
			typedef typename sprout::container_traits<internal_type>::const_iterator impl_const_iterator;
			typedef typename sprout::container_traits<internal_type>::difference_type impl_difference_type;
		public:
			typedef typename std::conditional<
				is_reference,
				internal_type*,
				typename std::remove_const<internal_type>::type
			>::type holder_type;
			typedef typename std::conditional<
				is_reference,
				internal_type&,
				internal_type const&
			>::type param_type;
			typedef internal_type const& const_param_type;
		public:
			typedef typename std::conditional<
				std::is_array<holder_type>::value,
				sprout::detail::is_non_reference_array_tag,
				sprout::detail::is_not_non_reference_array_tag
			>::type array_tag;
		public:
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				std::is_reference<Arr>::value,
				holder_type
			>::type to_holder(param_type arr) {
				return &arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				!std::is_reference<Arr>::value,
				holder_type const&
			>::type to_holder(param_type arr) {
				return arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				std::is_reference<Arr>::value,
				param_type
			>::type to_param(holder_type arr) {
				return *arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				!std::is_reference<Arr>::value,
				param_type
			>::type to_param(holder_type& arr) {
				return arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				!std::is_reference<Arr>::value,
				param_type
			>::type to_param(holder_type const& arr) {
				return arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				std::is_reference<Arr>::value,
				const_param_type
			>::type to_const_param(holder_type arr) {
				return *arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				!std::is_reference<Arr>::value,
				const_param_type
			>::type to_const_param(holder_type const& arr) {
				return arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				std::is_reference<Arr>::value,
				internal_type&
			>::type to_held(holder_type arr) {
				return *arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				!std::is_reference<Arr>::value,
				internal_type&
			>::type to_held(holder_type& arr) {
				return arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				!std::is_reference<Arr>::value,
				internal_type const&
			>::type to_held(holder_type const& arr) {
				return arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				std::is_reference<Arr>::value,
				internal_type const&
			>::type to_const_held(holder_type arr) {
				return *arr;
			}
			template<typename Arr>
			static SPROUT_CONSTEXPR typename std::enable_if<
				!std::is_reference<Arr>::value,
				internal_type const&
			>::type to_const_held(holder_type const& arr) {
				return arr;
			}
		public:
			holder_type array_;
			impl_difference_type to_first_;
			impl_difference_type to_last_;
		public:
			SPROUT_CONSTEXPR sub_array_impl()
				: array_()
				, to_first_()
				, to_last_()
			{}
			sub_array_impl(sub_array_impl const&) = default;
		public:
			template<typename ContainerTag, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ContainerTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				impl_const_iterator first,
				impl_const_iterator last,
				typename std::enable_if<std::is_same<ContainerTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_{to_holder<Container>(arr)[Indexes]...}
				, to_first_(sprout::distance(sprout::cbegin(arr), first))
				, to_last_(sprout::distance(sprout::cbegin(arr), last))
			{}
			template<typename ContainerTag, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ContainerTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				impl_const_iterator first,
				impl_const_iterator last,
				typename std::enable_if<!std::is_same<ContainerTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_(to_holder<Container>(arr))
				, to_first_(sprout::distance(sprout::cbegin(arr), first))
				, to_last_(sprout::distance(sprout::cbegin(arr), last))
			{}
			template<typename ContainerTag, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ContainerTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				impl_difference_type to_first,
				impl_difference_type to_last,
				typename std::enable_if<std::is_same<ContainerTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_{to_holder<Container>(arr)[Indexes]...}
				, to_first_(to_first)
				, to_last_(to_last)
			{}
			template<typename ContainerTag, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR sub_array_impl(
				ContainerTag,
				param_type arr,
				sprout::index_tuple<Indexes...>,
				impl_difference_type to_first,
				impl_difference_type to_last,
				typename std::enable_if<!std::is_same<ContainerTag, sprout::detail::is_non_reference_array_tag>::value>::type* = 0
				)
				: array_(to_holder<Container>(arr))
				, to_first_(to_first)
				, to_last_(to_last)
			{}
		};
	}	// namespace detail

	//
	// sub_array
	//
	template<typename Container>
	class sub_array
		: public sprout::container_traits_facade<typename std::remove_reference<Container>::type>
	{
	private:
		typedef sprout::detail::sub_array_impl<Container> impl_type;
		typedef sprout::container_traits_facade<typename std::remove_reference<Container>::type> facade_type;
	public:
		typedef typename impl_type::container_type container_type;
		typedef typename impl_type::internal_type internal_type;
	public:
		SPROUT_STATIC_CONSTEXPR bool is_reference = impl_type::is_reference;
		SPROUT_STATIC_CONSTEXPR bool is_const = impl_type::is_const;
	public:
		typedef typename facade_type::value_type value_type;
		typedef typename facade_type::iterator iterator;
		typedef typename facade_type::const_iterator const_iterator;
		typedef typename facade_type::reference reference;
		typedef typename facade_type::const_reference const_reference;
		typedef typename facade_type::size_type size_type;
		typedef typename facade_type::difference_type difference_type;
		typedef typename facade_type::pointer pointer;
		typedef typename facade_type::const_pointer const_pointer;
	public:
		SPROUT_STATIC_CONSTEXPR size_type enumerable_size = sprout::detail::static_size_or_zero<facade_type>::value;
	public:
		typedef typename impl_type::holder_type holder_type;
		typedef typename impl_type::param_type param_type;
		typedef typename impl_type::const_param_type const_param_type;
	private:
		typedef typename impl_type::array_tag array_tag;
	private:
		impl_type impl_;
	public:
		// construct/copy/destroy:
		SPROUT_CONSTEXPR sub_array() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
		sub_array(sub_array const&) = default;
		SPROUT_CONSTEXPR sub_array(param_type arr, const_iterator first, const_iterator last)
			: impl_(
				array_tag(),
				arr,
				sprout::make_index_tuple<enumerable_size>::make(),
				first,
				last
				)
		{}
		SPROUT_CONSTEXPR sub_array(param_type arr, difference_type to_first, difference_type to_last)
			: impl_(
				array_tag(),
				arr,
				sprout::make_index_tuple<enumerable_size>::make(),
				to_first,
				to_last
				)
		{}
		SPROUT_CONSTEXPR sub_array(sub_array const& other, const_iterator first, const_iterator last)
			: impl_(
				array_tag(),
				impl_type::template to_param<Container>(other.impl_.array_),
				sprout::make_index_tuple<enumerable_size>::make(),
				sprout::distance(sprout::begin(other.get_internal()), first),
				sprout::distance(sprout::begin(other.get_internal()), last)
				)
		{}
		SPROUT_CONSTEXPR sub_array(sub_array const& other, difference_type to_first, difference_type to_last)
			: impl_(
				array_tag(),
				impl_type::template to_param<Container>(other.impl_.array_),
				sprout::make_index_tuple<enumerable_size>::make(),
				other.impl_.to_first_ + to_first,
				other.impl_.to_first_ + to_last
				)
		{}
		template<typename Container2>
		SPROUT_CXX14_CONSTEXPR sub_array& operator=(sub_array<Container2> const& rhs) {
			impl_.array_ = rhs.impl_.array_;
			impl_.to_first_ = rhs.impl_.to_first_;
			impl_.to_last_ = rhs.impl_.to_last_;
			return *this;
		}
		template<typename Container2>
		SPROUT_CXX14_CONSTEXPR sub_array& operator=(sub_array<Container2>&& rhs) {
			impl_.array_ = sprout::move(rhs.impl_.array_);
			impl_.to_first_ = sprout::move(rhs.impl_.to_first_);
			impl_.to_last_ = sprout::move(rhs.impl_.to_last_);
			return *this;
		}

		SPROUT_CXX14_CONSTEXPR void fill(const_reference value) {
			sprout::fill_n(begin(), size(), value);
		}
		template<typename Container2>
		SPROUT_CXX14_CONSTEXPR void swap(sub_array<Container2>& other)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::swap(other.impl_.array_, impl_.array_))
		{
			sprout::swap(other.impl_.array_, impl_.array_);
			sprout::swap(other.impl_.to_first_, impl_.to_first_);
			sprout::swap(other.impl_.to_last_, impl_.to_last_);
		}
		// iterators:
		SPROUT_CXX14_CONSTEXPR iterator begin() {
			return sprout::next(sprout::begin(get_internal()), impl_.to_first_);
		}
		SPROUT_CONSTEXPR const_iterator begin() const {
			return sprout::next(sprout::begin(get_internal()), impl_.to_first_);
		}
		SPROUT_CXX14_CONSTEXPR iterator end() {
			return sprout::next(sprout::begin(get_internal()), impl_.to_last_);
		}
		SPROUT_CONSTEXPR const_iterator end() const {
			return sprout::next(sprout::begin(get_internal()), impl_.to_last_);
		}
		SPROUT_CONSTEXPR const_iterator cbegin() const {
			return sprout::next(sprout::begin(get_internal()), impl_.to_first_);
		}
		SPROUT_CONSTEXPR const_iterator cend() const {
			return sprout::next(sprout::begin(get_internal()), impl_.to_last_);
		}
		// capacity:
		SPROUT_CONSTEXPR size_type size() const {
			return impl_.to_last_ - impl_.to_first_;
		}
		SPROUT_CONSTEXPR size_type max_size() const {
			return size();
		}
		SPROUT_CONSTEXPR bool empty() const {
			return impl_.to_first_ == impl_.to_last_;
		}
		// element access:
		SPROUT_CXX14_CONSTEXPR reference operator[](size_type i) {
			return *sprout::next(sprout::begin(get_internal()), impl_.to_first_ + i);
		}
		SPROUT_CONSTEXPR const_reference operator[](size_type i) const {
			return *sprout::next(sprout::begin(get_internal()), impl_.to_first_ + i);
		}
		SPROUT_CXX14_CONSTEXPR reference at(size_type i) {
			return i < size() ? *sprout::next(sprout::begin(get_internal()), impl_.to_first_ + i)
				: (throw std::out_of_range("sub_array<>: index out of range"), *sprout::next(sprout::begin(get_internal()), impl_.to_first_ + i))
				;
		}
		SPROUT_CONSTEXPR const_reference at(size_type i) const {
			return i < size() ? *sprout::next(sprout::begin(get_internal()), impl_.to_first_ + i)
				: (throw std::out_of_range("sub_array<>: index out of range"), *sprout::next(sprout::begin(get_internal()), impl_.to_first_ + i))
				;
		}
		SPROUT_CXX14_CONSTEXPR reference front() {
			return *sprout::next(sprout::begin(get_internal()), impl_.to_first_);
		}
		SPROUT_CONSTEXPR const_reference front() const {
			return *sprout::next(sprout::begin(get_internal()), impl_.to_first_);
		}
		SPROUT_CXX14_CONSTEXPR reference back() {
			return *sprout::next(sprout::begin(get_internal()), impl_.to_last_ - 1);
		}
		SPROUT_CONSTEXPR const_reference back() const {
			return *sprout::next(sprout::begin(get_internal()), impl_.to_last_ - 1);
		}

		SPROUT_CXX14_CONSTEXPR pointer data() {
			return get_internal().data() + impl_.to_first_;
		}
		SPROUT_CONSTEXPR const_pointer data() const {
			return get_internal().data() + impl_.to_first_;
		}
		// others:
		SPROUT_CXX14_CONSTEXPR pointer c_array() {
			return data();
		}
		SPROUT_CONSTEXPR const_pointer c_array() const {
			return data();
		}
		SPROUT_CXX14_CONSTEXPR void assign(const_reference value) {
			fill(value);
		}
		SPROUT_CXX14_CONSTEXPR void rangecheck(size_type i) const {
			return i >= size() ? throw std::out_of_range("uuid: index out of range")
				: (void)0
				;
		}

		SPROUT_CXX14_CONSTEXPR internal_type& get_internal() {
			return impl_type::template to_held<Container>(impl_.array_);
		}
		SPROUT_CONSTEXPR internal_type const& get_internal() const {
			return impl_type::template to_const_held<Container>(impl_.array_);
		}
		SPROUT_CXX14_CONSTEXPR internal_type& get_array() {
			return impl_type::template to_held<Container>(impl_.array_);
		}
		SPROUT_CONSTEXPR internal_type const& get_array() const {
			return impl_type::template to_const_held<Container>(impl_.array_);
		}
		SPROUT_CONSTEXPR difference_type to_first() const {
			return impl_.to_first_;
		}
		SPROUT_CONSTEXPR difference_type to_last() const {
			return impl_.to_last_;
		}
		SPROUT_CONSTEXPR difference_type from_begin() const {
			return impl_.to_first_;
		}
		SPROUT_CONSTEXPR difference_type from_end() const {
			return impl_.to_last_ - sprout::size(get_internal());
		}

		SPROUT_CXX14_CONSTEXPR sub_array& window(difference_type to_first = 0) {
			impl_.to_first_ = to_first;
			impl_.to_last_ = size();
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR sub_array& window(difference_type to_first, difference_type to_last) {
			impl_.to_first_ = to_first;
			impl_.to_last_ = to_last;
			return *this;
		}
		SPROUT_CONSTEXPR sub_array window(difference_type to_first = 0) const {
			return sub_array(impl_.array_, to_first, size());
		}
		SPROUT_CONSTEXPR sub_array window(difference_type to_first, difference_type to_last) const {
			return sub_array(impl_.array_, to_first, to_last);
		}
		SPROUT_CONSTEXPR sub_array cwindow(difference_type to_first = 0) const {
			return window(to_first);
		}
		SPROUT_CONSTEXPR sub_array cwindow(difference_type to_first, difference_type to_last) const {
			return window(to_first, to_last);
		}

		SPROUT_CXX14_CONSTEXPR sub_array& offset(difference_type from_begin = 0, difference_type from_end = 0) {
			impl_.to_first_ += from_begin;
			impl_.to_last_ += from_end;
			return *this;
		}
		SPROUT_CONSTEXPR sub_array offset(difference_type from_begin = 0, difference_type from_end = 0) const {
			return sub_array(impl_.array_, impl_.to_first_ + from_begin, impl_.to_last_ + from_end);
		}
		SPROUT_CONSTEXPR sub_array coffset(difference_type from_begin = 0, difference_type from_end = 0) const {
			return offset(from_begin, from_end);
		}

		SPROUT_CXX14_CONSTEXPR iterator nth(size_type i) {
			return i < size()
				? sprout::next(begin(), i)
				: (throw std::out_of_range("sub_array<>: index out of range"), iterator())
				;
		}
		SPROUT_CONSTEXPR const_iterator nth(size_type i) const {
			return i < size()
				? sprout::next(begin(), i)
				: (throw std::out_of_range("array<>: index out of range"), const_iterator())
				;
		}
		SPROUT_CXX14_CONSTEXPR size_type index_of(iterator p) {
			return sprout::distance(begin(), p);
		}
		SPROUT_CONSTEXPR size_type index_of(const_iterator p) const {
			return sprout::distance(begin(), p);
		}

		SPROUT_CXX14_CONSTEXPR void push_back(value_type const& x) {
			impl_.array_[impl_.to_last_] = x;
			++impl_.to_last_;
		}
		SPROUT_CXX14_CONSTEXPR void push_back(value_type&& x) {
			impl_.array_[impl_.to_last_] = sprout::move(x);
			++impl_.to_last_;
		}
		SPROUT_CXX14_CONSTEXPR void pop_back() {
			impl_.array_[impl_.to_last_ - 1] = value_type();
			--impl_.to_last_;
		}
		SPROUT_CXX14_CONSTEXPR void drop_back() {
			--impl_.to_last_;
		}
		SPROUT_CXX14_CONSTEXPR void push_front(value_type const& x) {
			impl_.array_[impl_.to_first_ - 1] = x;
			--impl_.to_first_;
		}
		SPROUT_CXX14_CONSTEXPR void push_front(value_type&& x) {
			impl_.array_[impl_.to_first_ - 1] = sprout::move(x);
			--impl_.to_first_;
		}
		SPROUT_CXX14_CONSTEXPR void pop_front() {
			impl_.array_[impl_.to_first_] = value_type();
			++impl_.to_first_;
		}
		SPROUT_CXX14_CONSTEXPR void drop_front() {
			++impl_.to_first_;
		}
	};
	template<typename Container>
	SPROUT_CONSTEXPR_OR_CONST typename sprout::sub_array<Container>::size_type sprout::sub_array<Container>::enumerable_size;

	//
	// swap
	//
	template<typename Container>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::sub_array<Container>& lhs, sprout::sub_array<Container>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}
}	// namespace sprout

#include <sprout/sub_array/container.hpp>

#endif	// #ifndef SPROUT_SUB_ARRAY_SUB_ARRAY_HPP
