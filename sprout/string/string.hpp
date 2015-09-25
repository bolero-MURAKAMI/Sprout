/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STRING_STRING_HPP
#define SPROUT_STRING_STRING_HPP

#include <string>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <type_traits>
#include <initializer_list>
#include <sprout/config.hpp>
#include <sprout/detail/predef.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/array/array.hpp>
#include <sprout/array/make_array.hpp>
#include <sprout/iterator/reverse_iterator.hpp>
#include <sprout/iterator/value_iterator.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/algorithm/find.hpp>
#include <sprout/algorithm/cxx14/swap_ranges.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/less.hpp>
#include <sprout/string/char_traits.hpp>
#include <sprout/string/npos.hpp>
#include <sprout/string/detail/operations.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
#	include <sprout/iterator/index_iterator.hpp>
#endif
#include <sprout/workaround/enable_if_with_array.hpp>

namespace sprout {
	namespace detail {
		template<typename Iterator, typename T, std::size_t N>
		class constant_size_source {
		private:
			typedef sprout::array<T, N> array_type;
		public:
			typedef typename array_type::size_type size_type;
			typedef typename array_type::const_reference const_reference;
		private:
			array_type arr_;
			size_type size_;
		public:
			SPROUT_CONSTEXPR constant_size_source()
				: arr_{{}}, size_()
			{}
			template<typename... Args>
			explicit SPROUT_CONSTEXPR constant_size_source(size_type n, Args&&... args)
				: arr_{{static_cast<T>(SPROUT_FORWARD(Args, args))...}}, size_(n)
			{}
			SPROUT_CONSTEXPR size_type size() const {
				return size_;
			}
			SPROUT_CONSTEXPR const_reference operator[](size_type i) const {
				return arr_[i];
			}
		};

		template<typename T, std::size_t N, typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_random_access_iterator<RandomAccessIterator>::value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type
		>::type
		make_constant_size_source(RandomAccessIterator const& first, RandomAccessIterator const& last) {
			return sprout::distance(first, last);
		}
		template<typename T, std::size_t N, typename InputIterator, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			N == sizeof...(Args),
			sprout::detail::constant_size_source<InputIterator, T, N>
		>::type
		make_constant_size_source_impl(InputIterator first, InputIterator last, Args const&... args) {
			return sprout::detail::constant_size_source<InputIterator, T, N>(sizeof...(args) + (first != last ? 1 : 0), args...);
		}
		template<typename T, std::size_t N, typename InputIterator, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			N != sizeof...(Args),
			sprout::detail::constant_size_source<InputIterator, T, N>
		>::type
		make_constant_size_source_impl(InputIterator first, InputIterator last, Args const&... args) {
			return first != last
				? sprout::detail::make_constant_size_source_impl<T, N>(sprout::next(first), last, args..., *first)
				: sprout::detail::constant_size_source<InputIterator, T, N>(sizeof...(args), args...)
				;
		}
		template<typename T, std::size_t N, typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::is_random_access_iterator<InputIterator>::value,
			sprout::detail::constant_size_source<InputIterator, T, N>
		>::type
		make_constant_size_source(InputIterator const& first, InputIterator const& last) {
			return sprout::detail::make_constant_size_source_impl<T, N>(first, last);
		}
	}	// namespace detail

	namespace detail {
		struct string_raw_construct_t {};
		struct string_checked_construct_t {};
		struct string_range_construct_t {};

		template<typename T, std::size_t N, typename Traits = sprout::char_traits<T> >
		class string_construct_access;

		template<typename T, std::size_t N, typename Traits>
		class basic_string_impl {
		public:
			typedef typename Traits::char_type value_type;
			typedef value_type& reference;
			typedef value_type const& const_reference;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef value_type* pointer;
			typedef value_type const* const_pointer;
			typedef Traits traits_type;
		public:
			value_type elems[N + 1];
			size_type len;
		public:
			SPROUT_CONSTEXPR basic_string_impl()
				: elems{}, len()
			{}
			basic_string_impl(basic_string_impl const&) = default;
			basic_string_impl(basic_string_impl&&) = default;
			template<typename String, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR basic_string_impl(
				sprout::index_tuple<Indexes...>,
				String const& str, size_type pos, size_type n
				)
				: elems{
					(sprout::math::less(Indexes, n) ? static_cast<value_type>(str[Indexes + pos])
						: value_type()
						)...
					}
				, len(n)
			{}
			template<typename String, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR basic_string_impl(
				sprout::index_tuple<Indexes...>,
				sprout::detail::string_checked_construct_t, String const& str, size_type pos, size_type n
				)
				: elems{
					(sprout::math::less(Indexes, n) ? static_cast<value_type>(str[Indexes + pos])
						: value_type()
						)...
					}
				, len(!sprout::math::less(N, n) ? n
					: throw std::out_of_range("basic_string<>: index out of range")
					)
			{}
			template<typename RandomAccessIterator, typename Size, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR basic_string_impl(
				sprout::index_tuple<Indexes...>,
				sprout::detail::string_range_construct_t, RandomAccessIterator const& str, Size n,
				std::random_access_iterator_tag*
				)
				: elems{
					(sprout::math::less(Indexes, n) ? static_cast<value_type>(str[Indexes])
						: value_type()
						)...
					}
				, len(!sprout::math::less(N, n) ? n
					: throw std::out_of_range("basic_string<>: index out of range")
					)
			{}
			template<typename InputIterator, typename Source, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR basic_string_impl(
				sprout::index_tuple<Indexes...>,
				sprout::detail::string_range_construct_t, InputIterator, Source const& str,
				void*
				)
				: elems{
					(sprout::math::less(Indexes, str.size()) ? static_cast<value_type>(str[Indexes])
						: value_type()
						)...
					}
				, len(!(N < str.size()) ? str.size()
					: throw std::out_of_range("basic_string<>: index out of range")
					)
			{}
			template<typename... Args, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR basic_string_impl(
				sprout::index_tuple<Indexes...>,
				sprout::detail::string_raw_construct_t, size_type n, Args&&... args
				)
				: elems{
					(sprout::math::less(Indexes, n) ? static_cast<value_type>(SPROUT_FORWARD(Args, args))
						: value_type()
						)...
					}
				, len(n)
			{}
		};
	}	// namespace detail

	//
	// basic_string
	//
	template<typename T, std::size_t N, typename Traits = sprout::char_traits<T> >
	class basic_string {
		friend class sprout::detail::string_construct_access<T, N, Traits>;
	private:
		typedef sprout::detail::basic_string_impl<T, N, Traits> impl_type;
	public:
		typedef typename impl_type::value_type value_type;
		typedef typename impl_type::reference reference;
		typedef typename impl_type::const_reference const_reference;
		typedef typename impl_type::size_type size_type;
		typedef typename impl_type::difference_type difference_type;
		typedef typename impl_type::pointer pointer;
		typedef typename impl_type::const_pointer const_pointer;
		typedef typename impl_type::traits_type traits_type;
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		typedef sprout::index_iterator<basic_string&, true> iterator;
		typedef sprout::index_iterator<basic_string const&, true> const_iterator;
#else
		typedef T* iterator;
		typedef T const* const_iterator;
#endif
		typedef sprout::reverse_iterator<iterator> reverse_iterator;
		typedef sprout::reverse_iterator<const_iterator> const_reverse_iterator;
	private:
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		template<typename Iterator>
		class is_string_iterator
			: public sprout::false_type
		{};
		template<typename Iterator>
		class is_string_iterator<Iterator const>
			: public is_string_iterator<Iterator>
		{};
		template<typename Iterator>
		class is_string_iterator<Iterator volatile>
			: public is_string_iterator<Iterator>
		{};
		template<typename Iterator>
		class is_string_iterator<Iterator const volatile>
			: public is_string_iterator<Iterator>
		{};
		template<std::size_t N2>
		class is_string_iterator<sprout::index_iterator<basic_string<T, N2, Traits>&, true> >
			: public sprout::true_type
		{};
		template<std::size_t N2>
		class is_string_iterator<sprout::index_iterator<basic_string<T, N2, Traits> const&, true> >
			: public sprout::true_type
		{};
#endif
	public:
		SPROUT_STATIC_CONSTEXPR size_type npos = sprout::npos_t::get<size_type>::value;
		SPROUT_STATIC_CONSTEXPR size_type static_size = N;
	public:
		static SPROUT_CONSTEXPR basic_string from_c_str(T const* s, size_type n) {
			return basic_string(s, n);
		}
		static SPROUT_CONSTEXPR basic_string from_c_str(T const* s) {
			return basic_string(s);
		}
		static SPROUT_NON_CONSTEXPR basic_string from_c_str(std::basic_string<T, Traits> const& s) {
			return from_c_str(s.data(), s.size());
		}
	private:
		impl_type impl_;
	private:
		template<typename... Args, typename Enable = typename std::enable_if<(sizeof...(Args) <= N)>::type>
		SPROUT_CONSTEXPR basic_string(sprout::detail::string_raw_construct_t, size_type n, Args&&... args)
			: impl_(
				sprout::index_pack<Args...>::make(),
				sprout::detail::string_raw_construct_t(), n, SPROUT_FORWARD(Args, args)...
				)
		{}
		SPROUT_CXX14_CONSTEXPR void maxcheck(size_type n) const {
			if (n > static_size) {
				throw std::out_of_range("basic_string<>: index out of range");
			}
		}
		SPROUT_CXX14_CONSTEXPR void lengthcheck(size_type n) const {
			if (n > static_size) {
				throw std::length_error("basic_string<>: length error");
			}
		}
	public:
		// construct/copy/destroy:
		SPROUT_CONSTEXPR basic_string() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
		basic_string(basic_string const&) = default;
		template<std::size_t N2, typename Enable = typename std::enable_if<(N2 < N)>::type>
		SPROUT_CONSTEXPR basic_string(basic_string<T, N2, Traits> const& str)
			: impl_(
				sprout::make_index_tuple<N2>::make(),
				str, 0, str.size()
				)
		{}
		SPROUT_CONSTEXPR basic_string(basic_string const& str, size_type pos, size_type n = npos)
			: impl_(
				sprout::make_index_tuple<N>::make(),
				str, pos, NS_SSCRISK_CEL_OR_SPROUT::min(n, str.size() - pos)
				)
		{}
		template<std::size_t N2, typename Enable = typename std::enable_if<(N2 < N)>::type>
		SPROUT_CONSTEXPR basic_string(basic_string<T, N2, Traits> const& str, size_type pos, size_type n = npos)
			: impl_(
				sprout::make_index_tuple<N2>::make(),
				str, pos, NS_SSCRISK_CEL_OR_SPROUT::min(n, str.size() - pos)
				)
		{}
		template<std::size_t N2 SPROUT_ENABLE_IF_WITH_ARRAY_IN_TEMPLATE_PARAMS((N2 - 1 <= N))>
		SPROUT_CONSTEXPR basic_string(T const(& arr)[N2] SPROUT_ENABLE_IF_WITH_ARRAY_IN_PARAMS((N2 - 1 <= N)))
			: impl_(
				sprout::make_index_tuple<N2 - 1>::make(),
				arr, 0, sprout::char_traits_helper<typename sprout::basic_string<T, N2 - 1>::traits_type>::length(arr, N2 - 1)
				)
		{}
		template<std::size_t N2 SPROUT_ENABLE_IF_WITH_ARRAY_IN_TEMPLATE_PARAMS((N2 - 1 <= N))>
		SPROUT_CONSTEXPR basic_string(T const(& arr)[N2], size_type n SPROUT_ENABLE_IF_WITH_ARRAY_IN_PARAMS((N2 - 1 <= N)))
			: impl_(
				sprout::make_index_tuple<N2 - 1>::make(),
				arr, 0, NS_SSCRISK_CEL_OR_SPROUT::min(n, sprout::char_traits_helper<typename sprout::basic_string<T, N2 - 1>::traits_type>::length(arr, N2 - 1))
				)
		{}
		explicit SPROUT_CONSTEXPR basic_string(value_type const* s)
			: impl_(
				sprout::make_index_tuple<N>::make(),
				sprout::detail::string_checked_construct_t(), s, 0, traits_type::length(s)
				)
		{}
		SPROUT_CONSTEXPR basic_string(value_type const* s, size_type n)
			: impl_(
				sprout::make_index_tuple<N>::make(),
				sprout::detail::string_checked_construct_t(), s, 0, NS_SSCRISK_CEL_OR_SPROUT::min(n, traits_type::length(s))
				)
		{}
		SPROUT_CONSTEXPR basic_string(size_type n, value_type c)
			: impl_(
				sprout::make_index_tuple<N>::make(),
				sprout::detail::string_checked_construct_t(), sprout::value_iterator<value_type>(c), 0, n
				)
		{}
		template<typename InputIterator, typename sprout::enabler_if<std::is_integral<InputIterator>::value>::type = sprout::enabler>
		SPROUT_CONSTEXPR basic_string(InputIterator first, InputIterator last)
			: impl_(
				sprout::make_index_tuple<N>::make(),
				sprout::detail::string_checked_construct_t(), sprout::value_iterator<value_type>(last), 0, first
				)
		{}
		template<typename InputIterator, typename sprout::enabler_if<!std::is_integral<InputIterator>::value>::type = sprout::enabler>
		SPROUT_CONSTEXPR basic_string(InputIterator first, InputIterator last)
			: impl_(
				sprout::make_index_tuple<N>::make(),
				sprout::detail::string_range_construct_t(), first, sprout::detail::make_constant_size_source<T, N>(first, last),
				typename sprout::identity<typename std::iterator_traits<InputIterator>::iterator_category*>::type()
				)
		{}
		SPROUT_INITIALIZER_LIST_CONSTEXPR basic_string(std::initializer_list<value_type> il)
			: impl_(
				sprout::make_index_tuple<N>::make(),
				sprout::detail::string_checked_construct_t(), il.begin(), 0, il.size()
				)
		{}

		SPROUT_CXX14_CONSTEXPR basic_string&
		operator=(basic_string const& rhs) {
			return assign(rhs);
		}
		template<std::size_t N2, typename Enable = typename std::enable_if<(N2 != N)>::type>
		SPROUT_CXX14_CONSTEXPR basic_string&
		operator=(basic_string<T, N2, Traits> const& rhs) {
			return assign(rhs);
		}
		SPROUT_CXX14_CONSTEXPR basic_string&
		operator=(value_type const* rhs) {
			return assign(rhs);
		}
		SPROUT_CXX14_CONSTEXPR basic_string&
		operator=(value_type rhs) {
			return assign(1, rhs);
		}
		// iterators:
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		SPROUT_CXX14_CONSTEXPR iterator
		begin() SPROUT_NOEXCEPT {
			return iterator(*this, 0);
		}
		SPROUT_CONSTEXPR const_iterator
		begin() const SPROUT_NOEXCEPT {
			return const_iterator(*this, 0);
		}
		SPROUT_CXX14_CONSTEXPR iterator
		end() SPROUT_NOEXCEPT {
			return iterator(*this, size());
		}
		SPROUT_CONSTEXPR const_iterator
		end() const SPROUT_NOEXCEPT {
			return const_iterator(*this, size());
		}
#else
		SPROUT_CXX14_CONSTEXPR iterator
		begin() SPROUT_NOEXCEPT {
			return data();
		}
		SPROUT_CONSTEXPR const_iterator
		begin() const SPROUT_NOEXCEPT {
			return data();
		}
		SPROUT_CXX14_CONSTEXPR iterator
		end() SPROUT_NOEXCEPT {
			return data() + size();
		}
		SPROUT_CONSTEXPR const_iterator
		end() const SPROUT_NOEXCEPT {
			return data() + size();
		}
#endif
		SPROUT_CXX14_CONSTEXPR reverse_iterator
		rbegin() SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator
		rbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		SPROUT_CXX14_CONSTEXPR reverse_iterator
		rend() SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
		}
		SPROUT_CONSTEXPR const_reverse_iterator
		rend() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
		}
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		SPROUT_CONSTEXPR const_iterator
		cbegin() const SPROUT_NOEXCEPT {
			return const_iterator(*this, 0);
		}
		SPROUT_CONSTEXPR const_iterator
		cend() const SPROUT_NOEXCEPT {
			return const_iterator(*this, size());
		}
#else
		SPROUT_CONSTEXPR const_iterator
		cbegin() const SPROUT_NOEXCEPT {
			return data();
		}
		SPROUT_CONSTEXPR const_iterator
		cend() const SPROUT_NOEXCEPT {
			return data() + size();
		}
#endif
		SPROUT_CONSTEXPR const_reverse_iterator
		crbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator
		crend() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
		}
		// capacity:
		SPROUT_CONSTEXPR size_type
		size() const SPROUT_NOEXCEPT {
			return impl_.len;
		}
		SPROUT_CONSTEXPR size_type
		length() const SPROUT_NOEXCEPT {
			return size();
		}
		SPROUT_CONSTEXPR size_type
		max_size() const SPROUT_NOEXCEPT {
			return static_size;
		}
		SPROUT_CXX14_CONSTEXPR void
		resize(size_type n, value_type c) {
			lengthcheck(n);
			if (n > size()) {
				traits_type::assign(end(), n - size(), c);
			}
			traits_type::assign(begin() + n, static_size - n, value_type());
			impl_.len = n;
		}
		SPROUT_CXX14_CONSTEXPR void
		resize(size_type n) {
			resize(n, value_type());
		}
		SPROUT_CXX14_CONSTEXPR void
		clear() SPROUT_NOEXCEPT {
			traits_type::assign(begin(), static_size, value_type());
			impl_.len = 0;
		}
		SPROUT_CONSTEXPR bool
		empty() const SPROUT_NOEXCEPT {
			return size() == 0;
		}
		// element access:
		SPROUT_CXX14_CONSTEXPR reference
		operator[](size_type i) {
			return impl_.elems[i];
		}
		SPROUT_CONSTEXPR const_reference
		operator[](size_type i) const {
			return impl_.elems[i];
		}
		SPROUT_CXX14_CONSTEXPR reference
		at(size_type i) {
			return i < size() ? impl_.elems[i]
				: (throw std::out_of_range("basic_string<>: index out of range"), impl_.elems[i])
				;
		}
		SPROUT_CONSTEXPR const_reference
		at(size_type i) const {
			return i < size() ? impl_.elems[i]
				: (throw std::out_of_range("basic_string<>: index out of range"), impl_.elems[i])
				;
		}
		SPROUT_CXX14_CONSTEXPR reference
		front() {
			return impl_.elems[0];
		}
		SPROUT_CONSTEXPR const_reference
		front() const {
			return impl_.elems[0];
		}
		SPROUT_CXX14_CONSTEXPR reference
		back() {
			return impl_.elems[size() - 1];
		}
		SPROUT_CONSTEXPR const_reference
		back() const {
			return impl_.elems[size() - 1];
		}
		// modifiers:
		template<std::size_t N2>
		SPROUT_CXX14_CONSTEXPR basic_string&
		assign(basic_string<T, N2, Traits> const& str) {
			return assign(str, 0, npos);
		}
		template<std::size_t N2>
		SPROUT_CXX14_CONSTEXPR basic_string&
		assign(basic_string<T, N2, Traits> const& str, size_type pos, size_type n) {
			if (str.size() < pos) {
				throw std::out_of_range("basic_string<>: index out of range");
			}
			return assign(str.begin() + pos, NS_SSCRISK_CEL_OR_SPROUT::min(n, str.size() - pos));
		}
		SPROUT_CXX14_CONSTEXPR basic_string&
		assign(value_type const* s, size_type n) {
			lengthcheck(n);
			for (size_type i = 0; i < n; ++i) {
				traits_type::assign(impl_.elems[i], s[i]);
			}
			for (size_type i = n; i < static_size; ++i) {
				traits_type::assign(impl_.elems[i], value_type());
			}
			impl_.len = n;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR basic_string&
		assign(value_type const* s) {
			return assign(s, traits_type::length(s));
		}
		SPROUT_CXX14_CONSTEXPR basic_string&
		assign(size_type n, value_type c) {
			maxcheck(n);
			traits_type::assign(begin(), n, c);
			traits_type::assign(begin() + n, static_size - n, value_type());
			impl_.len = n;
			return *this;
		}
		template<typename InputIterator>
		SPROUT_CXX14_CONSTEXPR basic_string&
		assign(InputIterator first, InputIterator last) {
			size_type n = 0;
			for (; n < static_size || first != last; ++n, ++first) {
				traits_type::assign(impl_.elems[n], *first);
			}
			for (size_type i = n; i < static_size; ++i) {
				traits_type::assign(impl_.elems[i], value_type());
			}
			impl_.len = n;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR void
		swap(basic_string& other)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::swap(std::declval<T&>(), std::declval<T&>()))
		{
			sprout::swap_ranges(other.begin(), other.begin() + other.max_size(), begin());
			sprout::swap(impl_.len, other.impl_.len);
		}
		// string operations:
		SPROUT_CONSTEXPR const_pointer
		c_str() const SPROUT_NOEXCEPT {
			return data();
		}
		SPROUT_CXX14_CONSTEXPR pointer
		data() SPROUT_NOEXCEPT {
			return impl_.elems;
		}
		SPROUT_CONSTEXPR const_pointer
		data() const SPROUT_NOEXCEPT {
			return impl_.elems;
		}
		SPROUT_CXX14_CONSTEXPR pointer
		c_array() SPROUT_NOEXCEPT {
			return impl_.elems;
		}
		SPROUT_CONSTEXPR const_pointer
		c_array() const SPROUT_NOEXCEPT {
			return impl_.elems;
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR size_type
		find(basic_string<T, N2, Traits> const& str, size_type pos = 0) const SPROUT_NOEXCEPT {
			return sprout::string_detail::find_impl<basic_string>(begin(), size(), str.begin(), pos, str.size());
		}
		SPROUT_CONSTEXPR size_type
		find(value_type const* s, size_type pos, size_type n) const {
			return sprout::string_detail::find_impl<basic_string>(begin(), size(), s, pos, n);
		}
		SPROUT_CONSTEXPR size_type
		find(value_type const* s, size_type pos = 0) const {
			return find(s, pos, traits_type::length(s));
		}
		SPROUT_CONSTEXPR size_type
		find(value_type c, size_type pos = 0) const {
			return sprout::string_detail::find_c_impl<basic_string>(begin(), size(), c, pos);
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR size_type
		rfind(basic_string<T, N2, Traits> const& str, size_type pos = npos) const SPROUT_NOEXCEPT {
			return sprout::string_detail::rfind_impl<basic_string>(begin(), size(), str.begin(), pos, str.size());
		}
		SPROUT_CONSTEXPR size_type
		rfind(value_type const* s, size_type pos, size_type n) const {
			return sprout::string_detail::rfind_impl<basic_string>(begin(), size(), s, pos, n);
		}
		SPROUT_CONSTEXPR size_type
		rfind(value_type const* s, size_type pos = npos) const {
			return rfind(s, pos, traits_type::length(s));
		}
		SPROUT_CONSTEXPR size_type
		rfind(value_type c, size_type pos = npos) const {
			return sprout::string_detail::rfind_c_impl<basic_string>(begin(), size(), c, pos);
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR size_type
		find_first_of(basic_string<T, N2, Traits> const& str, size_type pos = 0) const SPROUT_NOEXCEPT {
			return sprout::string_detail::find_first_of_impl<basic_string>(begin(), size(), str.begin(), pos, str.size());
		}
		SPROUT_CONSTEXPR size_type
		find_first_of(value_type const* s, size_type pos, size_type n) const {
			return sprout::string_detail::find_first_of_impl<basic_string>(begin(), size(), s, pos, n);
		}
		SPROUT_CONSTEXPR size_type
		find_first_of(value_type const* s, size_type pos = 0) const {
			return find_first_of(s, pos, traits_type::length(s));
		}
		SPROUT_CONSTEXPR size_type
		find_first_of(value_type c, size_type pos = 0) const {
			return find(c, pos);
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR size_type
		find_last_of(basic_string<T, N2, Traits> const& str, size_type pos = npos) const SPROUT_NOEXCEPT {
			return sprout::string_detail::find_last_of_impl<basic_string>(begin(), size(), str.begin(), pos, str.size());
		}
		SPROUT_CONSTEXPR size_type
		find_last_of(value_type const* s, size_type pos, size_type n) const {
			return sprout::string_detail::find_last_of_impl<basic_string>(begin(), size(), s, pos, n);
		}
		SPROUT_CONSTEXPR size_type
		find_last_of(value_type const* s, size_type pos = npos) const {
			return find_last_of(s, pos, traits_type::length(s));
		}
		SPROUT_CONSTEXPR size_type
		find_last_of(value_type c, size_type pos = npos) const {
			return rfind(c, pos);
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR size_type
		find_first_not_of(basic_string<T, N2, Traits> const& str, size_type pos = 0) const SPROUT_NOEXCEPT {
			return sprout::string_detail::find_first_not_of_impl<basic_string>(begin(), size(), str.begin(), pos, str.size());
		}
		SPROUT_CONSTEXPR size_type
		find_first_not_of(value_type const* s, size_type pos, size_type n) const {
#if SPROUT_GCC_IN_RANGE((5, 1, 0), (5, 3, 0))
			return sprout::string_detail::find_first_not_of_impl<basic_string>(begin(), size(), sprout::ptr_index(s), pos, n);
#else
			return sprout::string_detail::find_first_not_of_impl<basic_string>(begin(), size(), s, pos, n);
#endif
		}
		SPROUT_CONSTEXPR size_type
		find_first_not_of(value_type const* s, size_type pos = 0) const {
			return find_first_not_of(s, pos, traits_type::length(s));
		}
		SPROUT_CONSTEXPR size_type
		find_first_not_of(value_type c, size_type pos = 0) const {
			return sprout::string_detail::find_first_not_of_c_impl<basic_string>(begin(), size(), c, pos);
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR size_type
		find_last_not_of(basic_string<T, N2, Traits> const& str, size_type pos = npos) const SPROUT_NOEXCEPT {
			return sprout::string_detail::find_last_not_of_impl<basic_string>(begin(), size(), str.begin(), pos, str.size());
		}
		SPROUT_CONSTEXPR size_type
		find_last_not_of(value_type const* s, size_type pos, size_type n) const {
#if SPROUT_GCC_IN_RANGE((5, 1, 0), (5, 3, 0))
			return sprout::string_detail::find_last_not_of_impl<basic_string>(begin(), size(), sprout::ptr_index(s), pos, n);
#else
			return sprout::string_detail::find_last_not_of_impl<basic_string>(begin(), size(), s, pos, n);
#endif
		}
		SPROUT_CONSTEXPR size_type
		find_last_not_of(value_type const* s, size_type pos = npos) const {
			return find_last_not_of(s, pos, traits_type::length(s));
		}
		SPROUT_CONSTEXPR size_type
		find_last_not_of(value_type c, size_type pos = npos) const {
			return sprout::string_detail::find_last_not_of_c_impl<basic_string>(begin(), size(), c, pos);
		}
		SPROUT_CONSTEXPR basic_string
		substr(size_type pos = 0, size_type n = npos) const {
			return !(size() < pos) ? from_c_str(c_str() + pos, NS_SSCRISK_CEL_OR_SPROUT::min(n, size() - pos))
				: throw std::out_of_range("basic_string<>: index out of range")
				;
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR int
		compare(basic_string<T, N2, Traits> const& str) const {
			return compare(0, size(), str.begin(), str.size());
		}
		SPROUT_CONSTEXPR int
		compare(value_type const* s) const {
			return compare(0, size(), s, traits_type::length(s));
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR int
		compare(size_type pos1, size_type n1, basic_string<T, N2, Traits> const& str) const {
			return compare(pos1, n1, str, 0, npos);
		}
		SPROUT_CONSTEXPR int
		compare(size_type pos1, size_type n1, value_type const* s) const {
			return compare(pos1, n1, s, traits_type::length(s));
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR int
		compare(size_type pos1, size_type n1, basic_string<T, N2, Traits> const& str, size_type pos2, size_type n2) const {
			return !(str.size() < pos2)
				? compare(pos1, n1, str.begin() + pos2, NS_SSCRISK_CEL_OR_SPROUT::min(n2, str.size() - pos2))
				: throw std::out_of_range("basic_string<>: index out of range")
				;
		}
		SPROUT_CONSTEXPR int
		compare(size_type pos1, size_type n1, value_type const* s, size_type n2) const {
			return !(size() < pos1)
				? sprout::string_detail::compare_impl<basic_string>(begin(), pos1, NS_SSCRISK_CEL_OR_SPROUT::min(n1, size() - pos1), s, n2)
				: throw std::out_of_range("basic_string<>: index out of range")
				;
		}
		// conversions:
		template<typename Allocator>
		SPROUT_EXPLICIT_CONVERSION SPROUT_NON_CONSTEXPR operator std::basic_string<T, Traits, Allocator>() const {
			return std::basic_string<T, Traits, Allocator>(data(), size());
		}

		SPROUT_CXX14_CONSTEXPR void rangecheck(size_type i) const {
			return i >= size() ? throw std::out_of_range("uuid: index out of range")
				: (void)0
				;
		}

#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		// construct/copy/destroy (for string iterator):
		template<typename StringConstIterator>
		SPROUT_CXX14_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			basic_string&
		>::type
		operator=(StringConstIterator rhs) {
			return assign(rhs);
		}

		// modifiers (for string iterator):
		template<typename StringConstIterator>
		SPROUT_CXX14_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			basic_string&
		>::type
		assign(StringConstIterator s, size_type n) {
			lengthcheck(n);
			for (size_type i = 0; i < n; ++i) {
				traits_type::assign(impl_.elems[i], s[i]);
			}
			for (size_type i = n; i < static_size; ++i) {
				traits_type::assign(impl_.elems[i], value_type());
			}
			impl_.len = n;
			return *this;
		}
		template<typename StringConstIterator>
		SPROUT_CXX14_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			basic_string&
		>::type
		assign(StringConstIterator s) {
			return assign(s, traits_type::length(s));
		}

		// string operations (for string iterator):
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			size_type
		>::type
		find(StringConstIterator s, size_type pos, size_type n) const {
			return sprout::string_detail::find_impl<basic_string>(begin(), size(), s, pos, n);
		}
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			size_type
		>::type
		find(StringConstIterator s, size_type pos = 0) const {
			return find(s, pos, traits_type::length(s));
		}
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			size_type
		>::type
		rfind(StringConstIterator s, size_type pos, size_type n) const {
			return sprout::string_detail::rfind_impl<basic_string>(begin(), size(), s, pos, n);
		}
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			size_type
		>::type
		rfind(StringConstIterator s, size_type pos = npos) const {
			return rfind(s, pos, traits_type::length(s));
		}
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			size_type
		>::type
		find_first_of(StringConstIterator s, size_type pos, size_type n) const {
			return sprout::string_detail::find_first_of_impl<basic_string>(begin(), size(), s, pos, n);
		}
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			size_type
		>::type
		find_first_of(StringConstIterator s, size_type pos = 0) const {
			return find_first_of(s, pos, traits_type::length(s));
		}
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			size_type
		>::type
		find_last_of(StringConstIterator s, size_type pos, size_type n) const {
			return sprout::string_detail::find_last_of_impl<basic_string>(begin(), size(), s, pos, n);
		}
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			size_type
		>::type
		find_last_of(StringConstIterator s, size_type pos = 0) const {
			return find_last_of(s, pos, traits_type::length(s));
		}
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			size_type
		>::type
		find_first_not_of(StringConstIterator s, size_type pos, size_type n) const {
			return sprout::string_detail::find_first_not_of_impl<basic_string>(begin(), size(), s, pos, n);
		}
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			size_type
		>::type
		find_first_not_of(StringConstIterator s, size_type pos = 0) const {
			return sprout::string_detail::find_first_not_of_impl<basic_string>(s, pos, traits_type::length(s));
		}
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			size_type
		>::type
		find_last_not_of(StringConstIterator s, size_type pos, size_type n) const {
			return sprout::string_detail::find_last_not_of_impl<basic_string>(begin(), size(), s, pos, n);
		}
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			size_type
		>::type
		find_last_not_of(StringConstIterator s, size_type pos = npos) const {
			return sprout::string_detail::find_last_not_of_impl<basic_string>(s, pos, traits_type::length(s));
		}
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			int
		>::type
		compare(StringConstIterator s) const {
			return compare(0, size(), s, traits_type::length(s));
		}
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			int
		>::type
		compare(size_type pos1, size_type n1, StringConstIterator s) const {
			return compare(pos1, n1, s, traits_type::length(s));
		}
		template<typename StringConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_iterator<StringConstIterator>::value,
			int
		>::type
		compare(size_type pos1, size_type n1, StringConstIterator s, size_type n2) const {
			return !(size() < pos1)
				? sprout::string_detail::compare_impl<basic_string>(begin(), pos1, NS_SSCRISK_CEL_OR_SPROUT::min(n1, size() - pos1), s, n2)
				: throw std::out_of_range("basic_string<>: index out of range")
				;
		}
#endif

#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		SPROUT_CXX14_CONSTEXPR iterator nth(size_type i) {
			return i < size()
				? iterator(*this, i)
				: (throw std::out_of_range("basic_string<>: index out of range"), iterator())
				;
		}
		SPROUT_CONSTEXPR const_iterator nth(size_type i) const {
			return i < size()
				? const_iterator(*this, i)
				: (throw std::out_of_range("basic_string<>: index out of range"), const_iterator())
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
			return i < size()
				? data() + i
				: (throw std::out_of_range("basic_string<>: index out of range"), iterator())
				;
		}
		SPROUT_CONSTEXPR const_iterator nth(size_type i) const {
			return i < size()
				? data() + i
				: (throw std::out_of_range("basic_string<>: index out of range"), const_iterator())
				;
		}SPROUT_CXX14_CONSTEXPR
		SPROUT_CONSTEXPR size_type index_of(iterator p) SPROUT_NOEXCEPT {
			return sprout::distance(begin(), p);
		}
		SPROUT_CONSTEXPR size_type index_of(const_iterator p) const SPROUT_NOEXCEPT {
			return sprout::distance(begin(), p);
		}
#endif
	};
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR_OR_CONST typename sprout::basic_string<T, N, Traits>::size_type sprout::basic_string<T, N, Traits>::npos;
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR_OR_CONST typename sprout::basic_string<T, N, Traits>::size_type sprout::basic_string<T, N, Traits>::static_size;

	//
	// swap
	//
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::basic_string<T, N, Traits>& lhs, sprout::basic_string<T, N, Traits>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	namespace detail {
		template<typename T, std::size_t N, typename Traits>
		class string_construct_access {
		public:
			template<typename... Args>
			static SPROUT_CONSTEXPR sprout::basic_string<T, N, Traits>
			raw_construct(typename sprout::basic_string<T, N, Traits>::size_type n, Args&&... args) {
				return sprout::basic_string<T, N, Traits>(sprout::detail::string_raw_construct_t(), n, SPROUT_FORWARD(Args, args)...);
			}
		};

		template<typename Container>
		struct make_construct_impl;

		template<typename T, std::size_t N, typename Traits>
		struct make_construct_impl<sprout::basic_string<T, N, Traits> > {
		private:
			typedef sprout::basic_string<T, N, Traits> copied_type;
		private:
			template<std::size_t M>
			static SPROUT_CONSTEXPR typename copied_type::size_type
			length_impl(sprout::array<T, M> const& arr) {
				return sprout::distance(arr.begin(), sprout::find(arr.begin(), arr.end(), T()));
			}
		public:
			template<typename... Args>
			static SPROUT_CONSTEXPR typename copied_type::size_type
			length(Args&&... args) {
				return length_impl(sprout::make_array<T>(SPROUT_FORWARD(Args, args)...));
			}
			template<typename... Args>
			static SPROUT_CONSTEXPR copied_type
			make(Args&&... args) {
				typedef sprout::detail::string_construct_access<T, N, Traits> access_type;
				return access_type::raw_construct(length(args...), SPROUT_FORWARD(Args, args)...);
			}
			template<typename... Args>
			static SPROUT_CONSTEXPR copied_type
			make(typename copied_type::size_type size, Args&&... args) {
				typedef sprout::detail::string_construct_access<T, N, Traits> access_type;
				return access_type::raw_construct(size, SPROUT_FORWARD(Args, args)...);
			}
		};
	}	// namespace detail

	//
	// to_string
	//
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N, Traits>
	to_string(sprout::basic_string<T, N, Traits> const& s) {
		return s;
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N - 1>
	to_string(T const(& arr)[N]) {
		return sprout::basic_string<T, N - 1>(arr);
	}

	//
	// string_from_c_str
	//
	template<std::size_t N, typename T>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N>
	string_from_c_str(T const* s, std::size_t n) {
		return sprout::basic_string<T, N>::from_c_str(s, n);
	}
	template<std::size_t N, typename T>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N>
	string_from_c_str(T const* s) {
		return sprout::basic_string<T, N>::from_c_str(s);
	}
	template<std::size_t N, typename T, typename Traits>
	inline SPROUT_NON_CONSTEXPR sprout::basic_string<T, N, Traits>
	string_from_c_str(std::basic_string<T, Traits> const& s) {
		return sprout::basic_string<T, N, Traits>::from_c_str(s);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_STRING_HPP
