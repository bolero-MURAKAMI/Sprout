#ifndef SPROUT_STRING_HPP
#define SPROUT_STRING_HPP

#include <cstddef>
#include <ios>
#include <algorithm>
#include <utility>
#include <string>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/array.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/operation/fixed/push_back.hpp>
#include <sprout/operation/fixed/push_front.hpp>
#include <sprout/operation/fixed/append_back.hpp>
#include <sprout/operation/fixed/append_front.hpp>
#include <sprout/iterator.hpp>
#include <sprout/utility/forward.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
#	include <algorithm>
#	include <sprout/iterator/index_iterator.hpp>
#endif

namespace sprout {
	//
	// char_traits
	//
	template<typename Char>
	class char_traits {
	private:
		typedef std::char_traits<Char> impl_type;
	public:
		typedef typename impl_type::char_type char_type;
		typedef typename impl_type::int_type int_type;
		typedef typename impl_type::off_type off_type;
		typedef typename impl_type::pos_type pos_type;
		typedef typename impl_type::state_type state_type;
	public:
		static void assign(char_type& c1, char_type const& c2) SPROUT_NOEXCEPT {
			impl_type::assign(c1, c2);
		}
		static SPROUT_CONSTEXPR bool eq(char_type c1, char_type c2) SPROUT_NOEXCEPT {
			return impl_type::eq(c1, c2);
		}
		static SPROUT_CONSTEXPR bool lt(char_type c1, char_type c2) SPROUT_NOEXCEPT {
			return impl_type::lt(c1, c2);
		}
		static SPROUT_CONSTEXPR int compare(char_type const* s1, char_type const* s2, std::size_t n) {
			return !n ? 0
				: lt(*s1, *s2) ? -1
				: lt(*s2, *s1) ? 1
				: compare(s1 + 1, s2 + 1, n - 1)
				;
		}
		static SPROUT_CONSTEXPR std::size_t length(char_type const* s) {
			return !*s ? 0
				: 1 + length(s + 1)
				;
		}
		static SPROUT_CONSTEXPR char_type const* find(char_type const* s, std::size_t n, char_type const& a) {
			return !n ? nullptr
				: eq(*s, a) ? s
				: find(s + 1, n - 1, a)
				;
		}
		static char_type* move(char_type* s1, char_type const* s2, std::size_t n) {
			return impl_type::move(s1, s2, n);
		}
		static char_type* copy(char_type* s1, char_type const* s2, std::size_t n) {
			return impl_type::copy(s1, s2, n);
		}
		static char_type* assign(char_type* s, std::size_t n, char_type a) {
			return impl_type::assign(s, n, a);
		}
		static SPROUT_CONSTEXPR int_type not_eof(int_type c) SPROUT_NOEXCEPT {
			return impl_type::not_eof(c);
		}
		static SPROUT_CONSTEXPR char_type to_char_type(int_type c) SPROUT_NOEXCEPT {
			return impl_type::to_char_type(c);
		}
		static SPROUT_CONSTEXPR int_type to_int_type(char_type c) SPROUT_NOEXCEPT {
			return impl_type::to_int_type(c);
		}
		static SPROUT_CONSTEXPR bool eq_int_type(int_type c1, int_type c2) SPROUT_NOEXCEPT {
			return impl_type::eq_int_type(c1, c2);
		}
		static SPROUT_CONSTEXPR int_type eof() SPROUT_NOEXCEPT {
			return impl_type::eof();
		}
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		template<typename ConstIterator>
		static SPROUT_CONSTEXPR int compare(char_type const* s1, ConstIterator s2, std::size_t n) {
			return !n ? 0
				: lt(*s1, *s2) ? -1
				: lt(*s2, *s1) ? 1
				: compare(s1 + 1, s2 + 1, n - 1)
				;
		}
		template<typename ConstIterator>
		static SPROUT_CONSTEXPR int compare(ConstIterator s1, char_type const* s2, std::size_t n) {
			return !n ? 0
				: lt(*s1, *s2) ? -1
				: lt(*s2, *s1) ? 1
				: compare(s1 + 1, s2 + 1, n - 1)
				;
		}
		template<typename ConstIterator1, typename ConstIterator2>
		static SPROUT_CONSTEXPR int compare(ConstIterator1 s1, ConstIterator2 s2, std::size_t n) {
			return !n ? 0
				: lt(*s1, *s2) ? -1
				: lt(*s2, *s1) ? 1
				: compare(s1 + 1, s2 + 1, n - 1)
				;
		}
		template<typename ConstIterator>
		static SPROUT_CONSTEXPR std::size_t length(ConstIterator s) {
			return !*s ? 0
				: 1 + length(s + 1)
				;
		}
		template<typename ConstIterator>
		static SPROUT_CONSTEXPR ConstIterator find(ConstIterator s, std::size_t n, char_type const& a) {
			return !n ? nullptr
				: eq(*s, a) ? s
				: find(s + 1, n - 1, a)
				;
		}
		template<typename Iterator, typename ConstIterator>
		static Iterator move(Iterator s1, ConstIterator s2, std::size_t n) {
			std::copy_backward(s2, s2 + n, s1);
			return s1;
		}
		template<typename Iterator, typename ConstIterator>
		static Iterator copy(Iterator s1, ConstIterator s2, std::size_t n) {
			std::copy(s2, s2 + n, s1);
			return s1;
		}
		template<typename Iterator>
		static Iterator assign(Iterator s, std::size_t n, char_type a) {
			std::fill(s, s + n, a);
			return s;
		}
#endif
	};

	//
	// basic_string
	//
	template<typename T, std::size_t N, typename Traits = sprout::char_traits<T> >
	class basic_string {
	public:
		typedef T value_type;
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		typedef sprout::index_iterator<basic_string&> iterator;
		typedef sprout::index_iterator<basic_string const&> const_iterator;
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
		typedef Traits traits_type;
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
	private:
		template<typename U, typename Enable = void>
		struct is_index_iterator_impl
			: public std::false_type
		{};
		template<typename U>
		struct is_index_iterator_impl<
			U,
			typename std::enable_if<
				std::is_same<
					U,
					sprout::index_iterator<typename U::container_type>
				>::value
				&& std::is_same<
					typename std::iterator_traits<U>::value_type,
					value_type
				>::value
			>::type
		>
			: public std::true_type
		{};
		template<typename U>
		struct is_index_iterator
			: public is_index_iterator_impl<U>
		{};
#endif
	public:
		SPROUT_STATIC_CONSTEXPR size_type npos = -1;
		SPROUT_STATIC_CONSTEXPR size_type static_size = N;
		SPROUT_STATIC_CONSTEXPR size_type fixed_size = static_size;
	private:
		static SPROUT_CONSTEXPR int compare_impl_2(int compared, size_type n1, size_type n2) {
			return compared != 0 ? compared
				: n1 < n2 ? -1
				: n2 < n1 ? 1
				: 0
				;
		}
		static SPROUT_CONSTEXPR int compare_impl_1(value_type const* dest, size_type pos1, size_type n1, value_type const* s, size_type n2) {
			return compare_impl_2(
				traits_type::compare(dest + pos1, s, NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(n1, n2)),
				n1,
				n2
				);
		}
		template<std::ptrdiff_t... Indexes>
		static SPROUT_CONSTEXPR basic_string<T, N, Traits> from_c_str_impl(
			value_type const* s,
			size_type n,
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::basic_string<T, N, Traits>{{(Indexes < n ? s[Indexes] : T())...}, n};
		}
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		template<typename ConstIterator>
		static SPROUT_CONSTEXPR typename std::enable_if<
			is_index_iterator<ConstIterator>::value,
			int
		>::type compare_impl_1(value_type const* dest, size_type pos1, size_type n1, ConstIterator s, size_type n2) {
			return compare_impl_2(
				traits_type::compare(dest + pos1, s, NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(n1, n2)),
				n1,
				n2
				);
		}
		static SPROUT_CONSTEXPR int compare_impl_1(const_iterator dest, size_type pos1, size_type n1, value_type const* s, size_type n2) {
			return compare_impl_2(
				traits_type::compare(dest + pos1, s, NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(n1, n2)),
				n1,
				n2
				);
		}
		template<typename ConstIterator>
		static SPROUT_CONSTEXPR typename std::enable_if<
			is_index_iterator<ConstIterator>::value,
			int
		>::type compare_impl_1(const_iterator dest, size_type pos1, size_type n1, ConstIterator s, size_type n2) {
			return compare_impl_2(
				traits_type::compare(dest + pos1, s, NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(n1, n2)),
				n1,
				n2
				);
		}
#endif
		template<std::size_t M, std::ptrdiff_t... Indexes>
		static SPROUT_CONSTEXPR basic_string<T, sizeof...(Indexes), Traits> implicit_conversion_impl(
			T const(& elems)[M],
			size_type len,
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::basic_string<T, sizeof...(Indexes), Traits>{{(Indexes < M - 1 ? elems[Indexes] : T())...}, len};
		}
	public:
		static SPROUT_CONSTEXPR basic_string<T, N, Traits> from_c_str(value_type const* s, size_type n) {
			return !(N < n)
				? from_c_str_impl(s, n, typename sprout::index_range<0, N>::type())
				: throw std::out_of_range("basic_string<>: index out of range")
				;
		}
		static SPROUT_CONSTEXPR basic_string<T, N, Traits> from_c_str(value_type const* s) {
			return from_c_str(s, traits_type::length(s));
		}
	public:
		value_type elems[static_size + 1];
		size_type len;
	public:
		// construct/copy/destroy:
		template<std::size_t N2>
		basic_string<T, N, Traits>& operator=(basic_string<T, N2, Traits> const& rhs) {
			return assign(rhs);
		}
		basic_string<T, N, Traits>& operator=(value_type const* rhs) {
			return assign(rhs);
		}
		basic_string<T, N, Traits>& operator=(value_type rhs) {
			return assign(1, rhs);
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
			return const_reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		reverse_iterator rend() SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
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
			return len;
		}
		SPROUT_CONSTEXPR size_type length() const SPROUT_NOEXCEPT {
			return size();
		}
		SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT {
			return static_size;
		}
		void resize(size_type n, value_type c) {
			maxcheck(n);
			if (n > size()) {
				traits_type::assign(end(), n - size(), c);
			}
			traits_type::assign(begin() + n, max_size() - n, value_type());
			len = n;
		}
		void resize(size_type n) {
			resize(n, value_type());
		}
		void clear() {
			traits_type::assign(begin(), max_size(), value_type());
			len = 0;
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
				: (throw std::out_of_range("basic_string<>: index out of range"), elems[i])
				;
		}
		SPROUT_CONSTEXPR const_reference at(size_type i) const {
			return i < size()
				? elems[i]
				: (throw std::out_of_range("basic_string<>: index out of range"), elems[i])
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
		// modifiers:
		template<std::size_t N2>
		basic_string<T, N, Traits>& assign(basic_string<T, N2, Traits> const& str) {
			return assign(str.begin(), str.size());
		}
		template<std::size_t N2>
		basic_string<T, N, Traits>& assign(basic_string<T, N2, Traits> const& str, size_type pos, size_type n) {
			if (str.size() < pos + n) {
				throw std::out_of_range("basic_string<>: index out of range");
			}
			return assign(str.begin() + pos, n);
		}
		basic_string<T, N, Traits>& assign(value_type const* s, size_type n) {
			maxcheck(n);
			for (size_type i = 0; i < n; ++i) {
				traits_type::assign(elems[i], s[i]);
			}
			for (size_type i = n; i < max_size(); ++i) {
				traits_type::assign(elems[i], value_type());
			}
			len = n;
			return *this;
		}
		basic_string<T, N, Traits>& assign(value_type const* s) {
			return assign(s, traits_type::length(s));
		}
		basic_string<T, N, Traits>& assign(size_type n, value_type c) {
			maxcheck(n);
			traits_type::assign(begin(), n, c);
			traits_type::assign(begin() + n, max_size() - n, value_type());
			len = n;
			return *this;
		}
		template<typename Iterator>
		basic_string<T, N, Traits>& assign(Iterator first, Iterator last) {
			size_type n = 0;
			for (; n < max_size() || first != last; ++n, ++first) {
				traits_type::assign(elems[n], *first);
			}
			for (size_type i = n; i < max_size(); ++i) {
				traits_type::assign(elems[i], value_type());
			}
			len = n;
			return *this;
		}
		void swap(basic_string<T, N, Traits>& other) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::swap(std::declval<T&>(), std::declval<T&>()))) {
			std::swap_ranges(other.begin(), other.begin() + other.max_size(), begin());
			{
				using std::swap;
				swap(len, other.len);
			}
		}
		// string operations:
		SPROUT_CONSTEXPR const_pointer c_str() const SPROUT_NOEXCEPT {
			return &elems[0];
		}
		pointer data() SPROUT_NOEXCEPT {
			return &elems[0];
		}
		SPROUT_CONSTEXPR const_pointer data() const SPROUT_NOEXCEPT {
			return &elems[0];
		}
		SPROUT_CONSTEXPR basic_string<T, N, Traits> substr(size_type pos = 0, size_type n = npos) const {
			return !(size() < pos)
				? n == npos
					? substr(pos, size() - pos)
					: from_c_str(c_str() + pos, n)
				: throw std::out_of_range("basic_string<>: index out of range")
				;
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR int compare(basic_string<T, N2, Traits> const& str) const {
			return compare(0, size(), str.begin(), str.size());
		}
		SPROUT_CONSTEXPR int compare(value_type const* s) const {
			return compare(0, size(), s, traits_type::length(s));
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, basic_string<T, N2, Traits> const& str) const {
			return compare(pos1, n1, str, 0, npos);
		}
		SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, value_type const* s) const {
			return compare(pos1, n1, s, traits_type::length(s));
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, basic_string<T, N2, Traits> const& str, size_type pos2, size_type n2) const {
			return !(str.size() < pos2)
				? compare(pos1, n1, str.begin() + pos2, NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(n2, str.size() - pos2))
				: throw std::out_of_range("basic_string<>: index out of range")
				;
		}
		SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, value_type const* s, size_type n2) const {
			return !(size() < pos1)
				? compare_impl_1(begin(), pos1, NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(n1, size() - pos1), s, n2)
				: throw std::out_of_range("basic_string<>: index out of range")
				;
		}
		// others:
		template<std::size_t N2>
		SPROUT_CONSTEXPR operator basic_string<T, N2, Traits>() const {
			static_assert(N <= N2, "basic_string<>: implicit conversion to small string");
			return implicit_conversion_impl(
				elems,
				len,
				typename sprout::index_range<0, N2>::type()
				);
		}
		pointer c_array() SPROUT_NOEXCEPT {
			return &elems[0];
		}
		void rangecheck(size_type i) const {
			if (i >= size()) {
				throw std::out_of_range("basic_string<>: index out of range");
			}
		}
		void maxcheck(size_type n) const {
			if (n > max_size()) {
				throw std::out_of_range("basic_string<>: index out of range");
			}
		}
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		template<typename ConstIterator>
		typename std::enable_if<
			is_index_iterator<ConstIterator>::value,
			basic_string<T, N, Traits>&
		>::type assign(ConstIterator s, size_type n) {
			maxcheck(n);
			for (size_type i = 0; i < n; ++i) {
				traits_type::assign(elems[i], s[i]);
			}
			for (size_type i = n; i < max_size(); ++i) {
				traits_type::assign(elems[i], value_type());
			}
			len = n;
			return *this;
		}
		template<typename ConstIterator>
		typename std::enable_if<
			is_index_iterator<ConstIterator>::value,
			basic_string<T, N, Traits>&
		>::type assign(ConstIterator s) {
			return assign(s, traits_type::length(s));
		}
		template<typename ConstIterator>
		typename std::enable_if<
			is_index_iterator<ConstIterator>::value,
			basic_string<T, N, Traits>&
		>::type operator=(ConstIterator rhs) {
			return assign(rhs);
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_index_iterator<ConstIterator>::value,
			int
		>::type compare(ConstIterator s) const {
			return compare(0, size(), s, traits_type::length(s));
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_index_iterator<ConstIterator>::value,
			int
		>::type compare(size_type pos1, size_type n1, ConstIterator s) const {
			return compare(pos1, n1, s, traits_type::length(s));
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_index_iterator<ConstIterator>::value,
			int
		>::type compare(size_type pos1, size_type n1, ConstIterator s, size_type n2) const {
			return !(size() < pos1)
				? compare_impl_1(begin(), pos1, NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(n1, size() - pos1), s, n2)
				: throw std::out_of_range("basic_string<>: index out of range")
				;
		}
#endif
	};
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR typename sprout::basic_string<T, N, Traits>::size_type sprout::basic_string<T, N, Traits>::npos;
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR typename sprout::basic_string<T, N, Traits>::size_type sprout::basic_string<T, N, Traits>::static_size;
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR typename sprout::basic_string<T, N, Traits>::size_type sprout::basic_string<T, N, Traits>::fixed_size;

	//
	// operator==
	// operator!=
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	SPROUT_CONSTEXPR inline bool operator==(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return lhs.compare(rhs) == 0;
	}
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline bool operator==(sprout::basic_string<T, N, Traits> const& lhs, T const* rhs) {
		return lhs.compare(rhs) == 0;
	}
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline bool operator==(T const* lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return 0 == rhs.compare(lhs);
	}
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	SPROUT_CONSTEXPR inline bool operator!=(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline bool operator!=(sprout::basic_string<T, N, Traits> const& lhs, T const* rhs) {
		return !(lhs == rhs);
	}
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline bool operator!=(T const* lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	SPROUT_CONSTEXPR inline bool operator<(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return lhs.compare(rhs) < 0;
	}
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline bool operator<(sprout::basic_string<T, N, Traits> const& lhs, T const* rhs) {
		return lhs.compare(rhs) < 0;
	}
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline bool operator<(T const* lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return 0 < rhs.compare(lhs);
	}
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	SPROUT_CONSTEXPR inline bool operator>(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return rhs < lhs;
	}
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline bool operator>(sprout::basic_string<T, N, Traits> const& lhs, T const* rhs) {
		return rhs < lhs;
	}
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline bool operator>(T const* lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return rhs < lhs;
	}
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	SPROUT_CONSTEXPR inline bool operator<=(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline bool operator<=(sprout::basic_string<T, N, Traits> const& lhs, T const* rhs) {
		return !(rhs < lhs);
	}
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline bool operator<=(T const* lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T, std::size_t N1, std::size_t N2, typename Traits>
	SPROUT_CONSTEXPR inline bool operator>=(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline bool operator>=(sprout::basic_string<T, N, Traits> const& lhs, T const* rhs) {
		return !(lhs < rhs);
	}
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline bool operator>=(T const* lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return !(lhs < rhs);
	}

	//
	// swap
	//
	template<typename T, std::size_t N, typename Traits>
	inline void swap(
		sprout::basic_string<T, N, Traits>& lhs,
		sprout::basic_string<T, N, Traits>& rhs
		) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// operator>>
	// operator<<
	//
	template<typename T, std::size_t N, typename Traits, typename StreamTraits>
	inline std::basic_istream<T, StreamTraits>& operator>>(std::basic_istream<T, StreamTraits>& lhs, sprout::basic_string<T, N, Traits>& rhs) {
		typedef T elem_type;
		typedef StreamTraits traits_type;
		typedef std::basic_istream<T, StreamTraits> istream_type;
		typedef sprout::basic_string<T, N, Traits> string_type;
		typedef std::ctype<elem_type> ctype_type;
		typedef typename string_type::size_type size_type;
		std::ios_base::iostate state = std::ios_base::goodbit;
		bool changed = false;
		size_type current = 0;
		if (typename istream_type::sentry(lhs)) {
			ctype_type const& ctype_fac = std::use_facet<ctype_type>(lhs.getloc());
			try {
				size_type remain = 0 < lhs.width() && static_cast<size_type>(lhs.width()) < rhs.max_size()
					? static_cast<size_type>(lhs.width())
					: rhs.max_size()
					;
				typename traits_type::int_type meta = lhs.rdbuf()->sgetc();
				for (; remain; --remain, meta = lhs.rdbuf()->snextc())
					if (traits_type::eq_int_type(traits_type::eof(), meta)) {
						state |= std::ios_base::eofbit;
						break;
					} else if (ctype_fac.is(ctype_type::space, traits_type::to_char_type(meta))) {
						break;
					} else {
						rhs[current] = traits_type::to_char_type(meta);
						changed = true;
						++current;
					}
			} catch (...) {
				state |= std::ios_base::badbit;
			}
		}
		lhs.width(0);
		if (!changed) {
			state |= std::ios_base::failbit;
		}
		lhs.setstate(state);
		rhs.len = current;
		for (; current != rhs.max_size(); ++current) {
			rhs[current] = T();
		}
		return lhs;
	}
	template<typename T, std::size_t N, typename Traits, typename StreamTraits>
	inline std::basic_ostream<T, StreamTraits>& operator<<(std::basic_ostream<T, StreamTraits>& lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return lhs << rhs.c_str();
	}

	//
	// rebind_fixed_size
	//
	template<typename T, std::size_t N, typename Traits>
	struct rebind_fixed_size<sprout::basic_string<T, N, Traits> > {
	public:
		template<typename sprout::fixed_container_traits<sprout::basic_string<T, N, Traits> >::size_type S>
		struct apply {
			public:
				typedef sprout::basic_string<T, S, Traits> type;
		};
	};

	namespace detail {
		template<typename Container>
		struct make_clone_functor_impl;

		template<typename T, std::size_t N, typename Traits>
		struct make_clone_functor_impl<sprout::basic_string<T, N, Traits> > {
		private:
			typedef sprout::basic_string<T, N, Traits> container_type;
			typedef typename sprout::fixed_container_traits<container_type>::clone_type clone_type;
		private:
			template<std::size_t S>
			static SPROUT_CONSTEXPR clone_type make_impl(typename clone_type::size_type size) {
				return clone_type{{}, size};
			}
			template<std::size_t S, typename Head, typename... Tail>
			static SPROUT_CONSTEXPR typename std::enable_if<
				S == sizeof...(Tail),
				clone_type
			>::type make_impl(typename clone_type::size_type size, Head&& head, Tail&&... tail) {
				return clone_type{{sprout::forward<Tail>(tail)..., sprout::forward<Head>(head)}, size};
			}
			template<std::size_t S, typename Head, typename... Tail>
			static SPROUT_CONSTEXPR typename std::enable_if<
				S != sizeof...(Tail),
				clone_type
			>::type make_impl(typename clone_type::size_type size, Head&& head, Tail&&... tail) {
				return make_impl<S + 1>(size, sprout::forward<Tail>(tail)..., S >= size ? T() : sprout::forward<Head>(head));
			}
		public:
			static SPROUT_CONSTEXPR typename clone_type::size_type length() {
				return 0;
			}
			template<typename... Tail>
			static SPROUT_CONSTEXPR typename clone_type::size_type length(T const& head, Tail&&... tail) {
				return !head ? 0 : 1 + length(sprout::forward<Tail>(tail)...);
			}
			template<typename... Args>
			static SPROUT_CONSTEXPR clone_type make(typename clone_type::size_type size, Args&&... args) {
				return make_impl<0>(size, sprout::forward<Args>(args)...);
			}
		};
	}	// namespace detail

	//
	// make_clone_functor
	//
	template<typename T, std::size_t N, typename Traits>
	struct make_clone_functor<sprout::basic_string<T, N, Traits> > {
	private:
		typedef sprout::basic_string<T, N, Traits> container_type;
		typedef sprout::detail::make_clone_functor_impl<container_type> impl_type;
	public:
		template<typename... Args>
		SPROUT_CONSTEXPR typename sprout::fixed_container_traits<container_type>::clone_type operator()(Args&&... args) const {
			return impl_type::make(impl_type::length(sprout::forward<Args>(args)...), sprout::forward<Args>(args)...);
		}
	};

	//
	// remake_clone_functor
	//
	template<typename T, std::size_t N, typename Traits>
	struct remake_clone_functor<sprout::basic_string<T, N, Traits> > {
	private:
		typedef sprout::basic_string<T, N, Traits> container_type;
		typedef sprout::detail::make_clone_functor_impl<container_type> impl_type;
	public:
		template<typename Other, typename... Args>
		SPROUT_CONSTEXPR typename sprout::fixed_container_traits<container_type>::clone_type operator()(
			Other&& other,
			typename sprout::fixed_container_traits<container_type>::difference_type size,
			Args&&... args
			) const
		{
			return impl_type::make(size, sprout::forward<Args>(args)...);
		}
	};

	//
	// to_string
	//
	namespace detail {
		template<typename T, std::size_t N, std::ptrdiff_t... Indexes>
		SPROUT_CONSTEXPR inline sprout::basic_string<T, N - 1> to_string_impl_1(
			T const(& arr)[N],
			typename sprout::basic_string<T, N - 1>::size_type n,
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::basic_string<T, N - 1>{{(Indexes < n ? arr[Indexes] : T())...}, n};
		}
		template<typename T, std::size_t N, std::ptrdiff_t... Indexes>
		SPROUT_CONSTEXPR inline sprout::basic_string<T, N - 1> to_string_impl(
			T const(& arr)[N],
			sprout::index_tuple<Indexes...>
			)
		{
			return to_string_impl_1(arr, sprout::char_traits<T>::length(arr), sprout::index_tuple<Indexes...>());
		}
	}	// namespace detail
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR inline sprout::basic_string<T, N - 1> to_string(T const(& arr)[N]) {
		return sprout::detail::to_string_impl(arr, typename sprout::index_range<0, N - 1>::type());
	}

	//
	// string_from_c_str
	//
	template<std::size_t N, typename T>
	SPROUT_CONSTEXPR inline sprout::basic_string<T, N> string_from_c_str(T const* s, std::size_t n) {
		return sprout::basic_string<T, N>::from_c_str(s, n);
	}
	template<std::size_t N, typename T>
	SPROUT_CONSTEXPR inline sprout::basic_string<T, N> string_from_c_str(T const* s) {
		return sprout::basic_string<T, N>::from_c_str(s);
	}

	//
	// make_string
	//
	namespace detail {
		template<typename T, std::size_t N, std::ptrdiff_t... Indexes>
		SPROUT_CONSTEXPR inline sprout::basic_string<T, N - 1> make_string_impl_1(
			sprout::array<T, N> const& arr,
			std::size_t n,
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::basic_string<T, N - 1>{{(Indexes < n ? arr[Indexes] : T())...}, n};
		}
		template<typename T, std::size_t N, std::ptrdiff_t... Indexes>
		SPROUT_CONSTEXPR inline sprout::basic_string<T, N - 1> make_string_impl(
			sprout::array<T, N> const& arr,
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::detail::make_string_impl_1(
				arr,
				sprout::char_traits<T>::length(arr.begin()),
				sprout::index_tuple<Indexes...>()
				);
		}
	}	// namespace detail
	template<typename T, typename... Types>
	SPROUT_CONSTEXPR inline sprout::basic_string<typename std::decay<T>::type, 1 + sizeof...(Types)>
	make_string(T&& t, Types&&... args) {
		return sprout::detail::make_string_impl(
			sprout::make_array<typename std::decay<T>::type>(
				sprout::forward<T>(t),
				sprout::forward<Types>(args)...,
				T()
				),
			typename sprout::index_range<0, 1 + sizeof...(Types)>::type()
			);
	}

	//
	// operator+
	//
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::push_back<sprout::basic_string<T, N, Traits>, T>::type operator+(
		sprout::basic_string<T, N, Traits> const& lhs,
		T const& rhs
		)
	{
		return sprout::fixed::push_back(lhs, rhs);
	}
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::push_front<sprout::basic_string<T, N, Traits>, T>::type operator+(
		T const& lhs,
		sprout::basic_string<T, N, Traits> const& rhs
		)
	{
		return sprout::fixed::push_front(rhs, lhs);
	}
	template<typename T, std::size_t N, typename Traits, std::size_t N2>
	SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::append_back<
			sprout::basic_string<T, N, Traits>,
			sprout::basic_string<T, N2 - 1, Traits>
	>::type operator+(
		sprout::basic_string<T, N, Traits> const& lhs,
		T const (& rhs)[N2]
		)
	{
		return sprout::fixed::append_back(lhs, sprout::to_string(rhs));
	}
	template<typename T, std::size_t N, typename Traits, std::size_t N2>
	SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::append_front<
		sprout::basic_string<T, N, Traits>,
		sprout::basic_string<T, N2 - 1, Traits>
	>::type operator+(
		T const (& lhs)[N2],
		sprout::basic_string<T, N, Traits> const& rhs
		)
	{
		return sprout::fixed::append_front(rhs, sprout::to_string(lhs));
	}
	template<typename T, std::size_t N, typename Traits, std::size_t N2>
	SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::append_back<
		sprout::basic_string<T, N, Traits>,
		sprout::basic_string<T, N2, Traits>
	>::type operator+(
		sprout::basic_string<T, N, Traits> const& lhs,
		sprout::basic_string<T, N2, Traits> const& rhs
		)
	{
		return sprout::fixed::append_back(lhs, rhs);
	}

	//
	// string_t
	//
	template<std::size_t N>
	struct string_t {
	public:
		typedef sprout::basic_string<char, N> type;
	};
	//
	// wstring_t
	//
	template<std::size_t N>
	struct wstring_t {
	public:
		typedef sprout::basic_string<wchar_t, N> type;
	};
	//
	// u16string_t
	//
	template<std::size_t N>
	struct u16string_t {
	public:
		typedef sprout::basic_string<char16_t, N> type;
	};
	//
	// u32string_t
	//
	template<std::size_t N>
	struct u32string_t {
	public:
		typedef sprout::basic_string<char32_t, N> type;
	};

	namespace detail {
		template<typename T, typename Enable = void>
		struct is_basic_string_impl
			: public std::false_type
		{};
		template<typename T>
		struct is_basic_string_impl<
			T,
			typename std::enable_if<
				std::is_same<
					T,
					sprout::basic_string<typename T::value_type, T::static_size, typename T::traits_type>
				>::value
			>::type
		>
			: public std::true_type
		{};
	}	// namespace detail
	//
	// is_basic_string
	//
	template<typename T>
	struct is_basic_string
		: public sprout::detail::is_basic_string_impl<T>
	{};

	namespace detail {
		template<typename T, typename Elem, typename Enable = void>
		struct is_string_of_impl
			: public std::false_type
		{};
		template<typename T, typename Elem>
		struct is_string_of_impl<
			T,
			Elem,
			typename std::enable_if<
				std::is_same<
					T,
					sprout::basic_string<Elem, T::static_size>
				>::value
			>::type
		>
			: public std::true_type
		{};
	}	// namespace detail
	//
	// is_string_of
	//
	template<typename T, typename Elem>
	struct is_string_of
		: public sprout::detail::is_string_of_impl<T, Elem>
	{};

	//
	// is_string
	//
	template<typename T>
	struct is_string
		: public sprout::is_string_of<T, char>
	{};
	//
	// is_wstring
	//
	template<typename T>
	struct is_wstring
		: public sprout::is_string_of<T, wchar_t>
	{};
	//
	// is_u16string
	//
	template<typename T>
	struct is_u16string
		: public sprout::is_string_of<T, char16_t>
	{};
	//
	// is_u32string
	//
	template<typename T>
	struct is_u32string
		: public sprout::is_string_of<T, char32_t>
	{};
}	// namespace sprout

namespace std {
	//
	// tuple_size
	//
	template<typename T, std::size_t N, typename Traits>
	struct tuple_size<sprout::basic_string<T, N, Traits> > {
	public:
		typedef std::integral_constant<std::size_t, N> type;
		SPROUT_STATIC_CONSTEXPR std::size_t value = type::value;
	};

	//
	// tuple_element
	//
	template<std::size_t I, typename T, std::size_t N, typename Traits>
	struct tuple_element<I, sprout::basic_string<T, N, Traits> > {
	public:
		static_assert(I < N, "tuple_element<>: index out of range");
		typedef T type;
	};
}	// namespace std

#endif	// #ifndef SPROUT_STRING_HPP
