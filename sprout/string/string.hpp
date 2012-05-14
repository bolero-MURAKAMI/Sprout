#ifndef SPROUT_STRING_STRING_HPP
#define SPROUT_STRING_STRING_HPP

#include <cstddef>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/array.hpp>
#include <sprout/iterator/reverse_iterator.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/string/char_traits.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
#	include <sprout/iterator/index_iterator.hpp>
#endif

namespace sprout {
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
	public:
		SPROUT_STATIC_CONSTEXPR size_type npos = -1;
		SPROUT_STATIC_CONSTEXPR size_type static_size = N;
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
				traits_type::compare(dest + pos1, s, NS_SSCRISK_CEL_OR_SPROUT::min(n1, n2)),
				n1,
				n2
				);
		}
		template<sprout::index_t... Indexes>
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
			sprout::is_index_iterator<ConstIterator>::value,
			int
		>::type compare_impl_1(value_type const* dest, size_type pos1, size_type n1, ConstIterator s, size_type n2) {
			return compare_impl_2(
				traits_type::compare(dest + pos1, s, NS_SSCRISK_CEL_OR_SPROUT::min(n1, n2)),
				n1,
				n2
				);
		}
		static SPROUT_CONSTEXPR int compare_impl_1(const_iterator dest, size_type pos1, size_type n1, value_type const* s, size_type n2) {
			return compare_impl_2(
				traits_type::compare(dest + pos1, s, NS_SSCRISK_CEL_OR_SPROUT::min(n1, n2)),
				n1,
				n2
				);
		}
		template<typename ConstIterator>
		static SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_index_iterator<ConstIterator>::value,
			int
		>::type compare_impl_1(const_iterator dest, size_type pos1, size_type n1, ConstIterator s, size_type n2) {
			return compare_impl_2(
				traits_type::compare(dest + pos1, s, NS_SSCRISK_CEL_OR_SPROUT::min(n1, n2)),
				n1,
				n2
				);
		}
#endif
		template<std::size_t M, sprout::index_t... Indexes>
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
				? from_c_str_impl(s, n, sprout::index_range<0, N>::make())
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
				? compare(pos1, n1, str.begin() + pos2, NS_SSCRISK_CEL_OR_SPROUT::min(n2, str.size() - pos2))
				: throw std::out_of_range("basic_string<>: index out of range")
				;
		}
		SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, value_type const* s, size_type n2) const {
			return !(size() < pos1)
				? compare_impl_1(begin(), pos1, NS_SSCRISK_CEL_OR_SPROUT::min(n1, size() - pos1), s, n2)
				: throw std::out_of_range("basic_string<>: index out of range")
				;
		}
		// others:
		template<std::size_t N2, typename Enable = typename std::enable_if<(N2 > N)>::type>
		SPROUT_CONSTEXPR operator basic_string<T, N2, Traits>() const {
			return implicit_conversion_impl(
				elems,
				len,
				sprout::index_range<0, N2>::make()
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
			sprout::is_index_iterator<ConstIterator>::value,
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
			sprout::is_index_iterator<ConstIterator>::value,
			basic_string<T, N, Traits>&
		>::type assign(ConstIterator s) {
			return assign(s, traits_type::length(s));
		}
		template<typename ConstIterator>
		typename std::enable_if<
			sprout::is_index_iterator<ConstIterator>::value,
			basic_string<T, N, Traits>&
		>::type operator=(ConstIterator rhs) {
			return assign(rhs);
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_index_iterator<ConstIterator>::value,
			int
		>::type compare(ConstIterator s) const {
			return compare(0, size(), s, traits_type::length(s));
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_index_iterator<ConstIterator>::value,
			int
		>::type compare(size_type pos1, size_type n1, ConstIterator s) const {
			return compare(pos1, n1, s, traits_type::length(s));
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_index_iterator<ConstIterator>::value,
			int
		>::type compare(size_type pos1, size_type n1, ConstIterator s, size_type n2) const {
			return !(size() < pos1)
				? compare_impl_1(begin(), pos1, NS_SSCRISK_CEL_OR_SPROUT::min(n1, size() - pos1), s, n2)
				: throw std::out_of_range("basic_string<>: index out of range")
				;
		}
#endif
	};
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR typename sprout::basic_string<T, N, Traits>::size_type sprout::basic_string<T, N, Traits>::npos;
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR typename sprout::basic_string<T, N, Traits>::size_type sprout::basic_string<T, N, Traits>::static_size;

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

	namespace detail {
		template<typename Container>
		struct make_construct_impl;

		template<typename T, std::size_t N, typename Traits>
		struct make_construct_impl<sprout::basic_string<T, N, Traits> > {
		private:
			typedef sprout::basic_string<T, N, Traits> copied_type;
		private:
			template<std::size_t M>
			static SPROUT_CONSTEXPR typename copied_type::size_type length_impl(sprout::array<T, M> const& arr) {
				return NS_SSCRISK_CEL_OR_SPROUT::distance(
					arr.begin(),
					NS_SSCRISK_CEL_OR_SPROUT::find(arr.begin(), arr.end(), T())
					);
			}
			template<typename... Args, sprout::index_t... Indexes>
			static SPROUT_CONSTEXPR copied_type make_impl(
				typename copied_type::size_type size,
				sprout::index_tuple<Indexes...>,
				Args&&... args
				)
			{
				return copied_type{
					{(Indexes < size ? sprout::forward<Args>(args) : T())...},
					size
					};
			}
		public:
			template<typename... Args>
			static SPROUT_CONSTEXPR typename copied_type::size_type length(Args&&... args) {
				return length_impl(sprout::make_array<T>(sprout::forward<Args>(args)...));
			}
			template<typename... Args>
			static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
				return make_impl(
					length(args...),
					sprout::index_range<0, sizeof...(Args)>::make(),
					sprout::forward<Args>(args)...
					);
			}
			template<typename... Args>
			static SPROUT_CONSTEXPR copied_type make(typename copied_type::size_type size, Args&&... args) {
				return make_impl(
					size,
					sprout::index_range<0, sizeof...(Args)>::make(),
					sprout::forward<Args>(args)...
					);
			}
		};
	}	// namespace detail

	//
	// to_string
	//
	namespace detail {
		template<typename T, std::size_t N, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, N - 1> to_string_impl_1(
			T const(& arr)[N],
			typename sprout::basic_string<T, N - 1>::size_type n,
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::basic_string<T, N - 1>{{(Indexes < n ? arr[Indexes] : T())...}, n};
		}
		template<typename T, std::size_t N, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::basic_string<T, N - 1> to_string_impl(
			T const(& arr)[N],
			sprout::index_tuple<Indexes...>
			)
		{
			return to_string_impl_1(arr, sprout::char_traits<T>::length(arr), sprout::index_tuple<Indexes...>());
		}
	}	// namespace detail
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N - 1> to_string(T const(& arr)[N]) {
		return sprout::detail::to_string_impl(arr, sprout::index_range<0, N - 1>::make());
	}

	//
	// string_from_c_str
	//
	template<std::size_t N, typename T>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N> string_from_c_str(T const* s, std::size_t n) {
		return sprout::basic_string<T, N>::from_c_str(s, n);
	}
	template<std::size_t N, typename T>
	inline SPROUT_CONSTEXPR sprout::basic_string<T, N> string_from_c_str(T const* s) {
		return sprout::basic_string<T, N>::from_c_str(s);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_STRING_HPP
