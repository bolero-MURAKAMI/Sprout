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
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/operation/fixed/push_back.hpp>
#include <sprout/operation/fixed/push_front.hpp>
#include <sprout/operation/fixed/join_back.hpp>
#include <sprout/operation/fixed/join_front.hpp>
#include <sprout/detail/iterator.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL

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
	};

	//
	// basic_string
	//
	template<typename T, std::size_t N, typename Traits = sprout::char_traits<T> >
	class basic_string {
	public:
		typedef T value_type;
		typedef T* iterator;
		typedef T const* const_iterator;
		typedef T& reference;
		typedef T const& const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T const* const_pointer;
		typedef sprout::detail::reverse_iterator<iterator> reverse_iterator;
		typedef sprout::detail::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef Traits traits_type;
	public:
		SPROUT_STATIC_CONSTEXPR size_type npos = -1;
		SPROUT_STATIC_CONSTEXPR size_type static_size = N;
		SPROUT_STATIC_CONSTEXPR size_type fixed_size = static_size;
	public:
		T elems[N + 1];
		size_type len;
	private:
		SPROUT_CONSTEXPR int compare_impl_2(int compared, size_type n1, size_type n2) const {
			return compared != 0 ? compared
				: n1 < n2 ? -1
				: n2 < n1 ? 1
				: 0
				;
		}
		SPROUT_CONSTEXPR int compare_impl_1(size_type pos1, size_type n1, char const* s, size_type n2) const {
			return compare_impl_2(
				traits_type::compare(c_str() + pos1, s, NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(n1, n2)),
				n1,
				n2
				);
		}
	public:
		SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT {
			return len;
		}
		SPROUT_CONSTEXPR size_type length() const SPROUT_NOEXCEPT {
			return size();
		}
		SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT {
			return size() == 0;
		}
		SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT {
			return N;
		}
		void rangecheck(size_type i) const {
			if (i >= size()) {
				throw std::out_of_range("basic_string<>: index out of range");
			}
		}
		iterator begin() SPROUT_NOEXCEPT {
			return &elems[0];
		}
		SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT {
			return &elems[0];
		}
		SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT {
			return &elems[0];
		}
		iterator end() SPROUT_NOEXCEPT {
			return &elems[0] + size();
		}
		SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
			return &elems[0] + size();
		}
		SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT {
			return &elems[0] + size();
		}
		reverse_iterator rbegin() SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator crbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		reverse_iterator rend() SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
		}
		SPROUT_CONSTEXPR const_reverse_iterator rend() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
		}
		SPROUT_CONSTEXPR const_reverse_iterator crend() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
		}
		reference operator[](size_type i) {
			return elems[i];
		}
		SPROUT_CONSTEXPR const_reference operator[](size_type i) const {
			return elems[i];
		}
		reference at(size_type i) {
			rangecheck(i);
			return elems[i];
		}
		const_reference at(size_type i) const {
			rangecheck(i);
			return elems[i];
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
		pointer c_array() SPROUT_NOEXCEPT {
			return &elems[0];
		}
		SPROUT_CONSTEXPR const_pointer c_str() const SPROUT_NOEXCEPT {
			return &elems[0];
		}
		void fill(const_reference value) {
			std::fill_n(begin(), size(), value);
		}
		void swap(basic_string<T, N, Traits>& other) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::swap(std::declval<T&>(), std::declval<T&>()))) {
			std::swap_ranges(other.begin(), other.end(), begin());
		}
		template<typename T2, typename Traits2>
		basic_string<T, N, Traits>& operator=(basic_string<T2, N, Traits2> const& rhs) {
			std::copy(rhs.begin(), rhs.end(), begin());
			return *this;
		}
		template<typename T2, typename Traits2>
		basic_string<T, N, Traits>& operator=(basic_string<T2, N, Traits2>&& rhs) {
			std::move(rhs.begin(), rhs.end(), begin());
			return *this;
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR int compare(basic_string<T, N2, Traits> const& str) const {
			return compare(0, size(), str.c_str(), str.size());
		}
		SPROUT_CONSTEXPR int compare(T const* s) const {
			return compare(0, size(), s, traits_type::length(s));
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, basic_string<T, N2, Traits> const& str) const {
			return compare(pos1, n1, str, 0, npos);
		}
		SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, char const* s) const {
			return compare(pos1, n1, s, traits_type::length(s));
		}
		template<std::size_t N2>
		SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, basic_string<T, N2, Traits> const& str, size_type pos2, size_type n2) const {
			return !(str.size() < pos2)
				? compare(pos1, n1, str.c_str() + pos2, NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(n2, str.size() - pos2))
				: throw "basic_string<>: index out of range"
				;
		}
		SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, char const* s, size_type n2) const {
			return !(size() < pos1)
				? compare_impl_1(pos1, NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(n1, size() - pos1), s, n2)
				: throw "basic_string<>: index out of range"
				;
		}
	};
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
	// resize
	//
	namespace detail {
		template<typename T, std::size_t N, typename Traits, typename... Args>
		SPROUT_CONSTEXPR inline typename std::enable_if<
			sizeof...(Args) != N,
			sprout::basic_string<T, N, Traits>
		>::type resize_impl(
			sprout::basic_string<T, N, Traits> const& str,
			typename sprout::basic_string<T, N, Traits>::size_type new_size,
			Args const&... args
			)
		{
			return sprout::detail::resize_impl(str, new_size, args..., sizeof...(Args) < new_size ? str[sizeof...(Args)] : T());
		}
		template<typename T, std::size_t N, typename Traits, typename... Args>
		SPROUT_CONSTEXPR inline typename std::enable_if<
			sizeof...(Args) == N,
			sprout::basic_string<T, N, Traits>
		>::type resize_impl(
			sprout::basic_string<T, N, Traits> const& str,
			typename sprout::basic_string<T, N, Traits>::size_type new_size,
			Args const&... args
			)
		{
			return sprout::basic_string<T, N, Traits>{{args...}, new_size};
		}
	}	// namespace detail
	template<typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR inline sprout::basic_string<T, N, Traits> resize(
		sprout::basic_string<T, N, Traits> const& str,
		typename sprout::basic_string<T, N, Traits>::size_type new_size
		)
	{
		return new_size <= N ? sprout::detail::resize_impl(str, new_size)
			: throw "basic_string<>: index out of range"
			;
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

	//
	// make_clone_functor
	//
	template<typename T, std::size_t N, typename Traits>
	struct make_clone_functor<sprout::basic_string<T, N, Traits> > {
	private:
		typedef typename sprout::fixed_container_traits<sprout::basic_string<T, N, Traits> >::clone_type clone_type;
	private:
		static SPROUT_CONSTEXPR typename clone_type::size_type length() {
			return 0;
		}
		template<typename... Tail>
		static SPROUT_CONSTEXPR typename clone_type::size_type length(T const& head, Tail const&... tail) {
			return !head ? 0 : 1 + length(tail...);
		}
	public:
		template<typename... Args>
		SPROUT_CONSTEXPR clone_type operator()(Args const&... args) const {
			return clone_type{{args...}, length(args...)};
		}
	};

	namespace detail {
		template<typename T, typename Enable = void>
		struct is_basic_string_impl {
		public:
			typedef std::integral_constant<bool, false> type;
			SPROUT_STATIC_CONSTEXPR bool value = type::value;
		};
		template<typename T>
		struct is_basic_string_impl<
			T,
			typename std::enable_if<
				std::is_same<
					T,
					sprout::basic_string<typename T::value_type, T::static_size, typename T::traits_type>
				>::value
			>::type
		> {
		public:
			typedef std::integral_constant<bool, true> type;
			SPROUT_STATIC_CONSTEXPR bool value = type::value;
		};
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
		struct is_string_of_impl {
		public:
			typedef std::integral_constant<bool, false> type;
			SPROUT_STATIC_CONSTEXPR bool value = type::value;
		};
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
		> {
		public:
			typedef std::integral_constant<bool, true> type;
			SPROUT_STATIC_CONSTEXPR bool value = type::value;
		};
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

	namespace detail {
		template<typename T, std::size_t N, std::ptrdiff_t...Indexes>
		SPROUT_CONSTEXPR inline sprout::basic_string<T, N - 1> to_string_impl_1(
			T const(& arr)[N],
			sprout::index_tuple<Indexes...>,
			typename sprout::basic_string<T, N - 1>::size_type len
			)
		{
			return sprout::basic_string<T, N - 1>{{(Indexes < len ? arr[Indexes] : T())...}, len};
		}
		template<typename T, std::size_t N, std::ptrdiff_t...Indexes>
		SPROUT_CONSTEXPR inline sprout::basic_string<T, N - 1> to_string_impl(
			T const(& arr)[N],
			sprout::index_tuple<Indexes...>
			)
		{
			return to_string_impl_1(arr, sprout::index_tuple<Indexes...>(), sprout::char_traits<T>::length(arr));
		}
	}	// namespace detail
	//
	// to_string
	//
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR inline sprout::basic_string<T, N - 1> to_string(T const(& arr)[N]) {
		return sprout::detail::to_string_impl(arr, typename sprout::index_range<0, N - 1>::type());
	}

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
	SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::join_back<
			sprout::basic_string<T, N, Traits>,
			sprout::basic_string<T, N2 - 1, Traits>
	>::type operator+(
		sprout::basic_string<T, N, Traits> const& lhs,
		T const (& rhs)[N2]
		)
	{
		return sprout::fixed::join_back(lhs, sprout::to_string(rhs));
	}
	template<typename T, std::size_t N, typename Traits, std::size_t N2>
	SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::join_front<
		sprout::basic_string<T, N, Traits>,
		sprout::basic_string<T, N2 - 1, Traits>
	>::type operator+(
		T const (& lhs)[N2],
		sprout::basic_string<T, N, Traits> const& rhs
		)
	{
		return sprout::fixed::join_front(rhs, sprout::to_string(lhs));
	}
	template<typename T, std::size_t N, typename Traits, std::size_t N2>
	SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::join_back<
		sprout::basic_string<T, N, Traits>,
		sprout::basic_string<T, N2, Traits>
	>::type operator+(
		sprout::basic_string<T, N, Traits> const& lhs,
		sprout::basic_string<T, N2, Traits> const& rhs
		)
	{
		return sprout::fixed::join_back(lhs, rhs);
	}

	template<typename T, std::size_t N, typename Traits, typename StreamTraits>
	inline std::basic_ostream<T, StreamTraits>& operator<<(std::basic_ostream<T, StreamTraits>& lhs, sprout::basic_string<T, N, Traits> const& rhs) {
		return lhs << rhs.c_str();
	}
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

#if 0
	//
	// string
	//
	template<std::size_t N>
	using string = sprout::basic_string<char, N>;
	//
	// wstring
	//
	template<std::size_t N>
	using wstring = sprout::basic_string<wchar_t, N>;
	//
	// u16string
	//
	template<std::size_t N>
	using u16string = sprout::basic_string<char16_t, N>;
	//
	// u32string
	//
	template<std::size_t N>
	using u32string = sprout::basic_string<char32_t, N>;
#endif	// #if 0

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

	//
	// get
	//
	template<std::size_t I, typename T, std::size_t N, typename Traits>
	T& get(sprout::basic_string<T, N, Traits>& arr) SPROUT_NOEXCEPT {
		static_assert(I < N, "tuple_element<>: index out of range");
		return arr[I];
	}
	template<std::size_t I, typename T, std::size_t N, typename Traits>
	SPROUT_CONSTEXPR T const& get(sprout::basic_string<T, N, Traits> const& arr) SPROUT_NOEXCEPT {
		static_assert(I < N, "tuple_element<>: index out of range");
		return arr[I];
	}
	template<std::size_t I, typename T, std::size_t N, typename Traits>
	T&& get(sprout::basic_string<T, N, Traits>&& arr) SPROUT_NOEXCEPT {
		return std::move(get<I>(arr));
	}
}	// namespace std

#endif	// #ifndef SPROUT_STRING_HPP

