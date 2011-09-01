#ifndef SPROUT_STRING_HPP
#define SPROUT_STRING_HPP

#include <cstddef>
#include <iosfwd>
#include <algorithm>
#include <utility>
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
	// basic_string
	//
	template<typename T, std::size_t N>
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
	public:
		static constexpr size_type static_size = N;
		static constexpr size_type fixed_size = static_size;
	public:
		T elems[N + 1];
	public:
		SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT {
			return N;
		}
		SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT {
			return N != 0;
		}
		SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT {
			return size();
		}
		void rangecheck(size_type i) const {
			if (i >= size()) {
				throw std::out_of_range("basic_string<>: index out of range");
			}
		}
		iterator begin() SPROUT_NOEXCEPT {
			return elems;
		}
		SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT {
			return elems;
		}
		SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT {
			return elems;
		}
		iterator end() SPROUT_NOEXCEPT {
			return elems + size();
		}
		SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
			return elems + size();
		}
		SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT {
			return elems + size();
		}
		reverse_iterator rbegin() SPROUT_NOEXCEPT {
			return reverse_iterator(begin());
		}
		SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
		}
		SPROUT_CONSTEXPR const_reverse_iterator crbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
		}
		reverse_iterator rend() SPROUT_NOEXCEPT {
			return reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator rend() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator crend() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
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
			return elems[size() - 1];
		}
		reference back() {
			return elems[size() - 1];
		}
		SPROUT_CONSTEXPR const_reference back() const {
			return elems[0];
		}
		pointer data() SPROUT_NOEXCEPT {
			return elems;
		}
		SPROUT_CONSTEXPR const_pointer data() const SPROUT_NOEXCEPT {
			return elems;
		}
		pointer c_array() SPROUT_NOEXCEPT {
			return elems;
		}
		const_pointer c_str() const SPROUT_NOEXCEPT {
			return elems;
		}
		void assign(const_reference value) {
			fill(value);
		}
		void fill(const_reference value) {
			std::fill_n(begin(), size(), value);
		}
		void swap(basic_string<T, N>& other) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::swap(std::declval<T&>(), std::declval<T&>()))) {
			std::swap_ranges(other.begin(), other.end(), begin());
		}
		template <typename T2>
		basic_string<T, N>& operator=(basic_string<T2, N> const& rhs) {
			std::copy(rhs.begin(), rhs.end(), begin());
			return *this;
		}
		template <typename T2>
		basic_string<T, N>& operator=(basic_string<T2, N>&& rhs) {
			std::move(rhs.begin(), rhs.end(), begin());
			return *this;
		}
	};
	template<typename T, std::size_t N1, std::size_t N2>
	SPROUT_CONSTEXPR inline bool operator==(sprout::basic_string<T, N1> const& lhs, sprout::basic_string<T, N2> const& rhs) {
		return N1 == N2 && NS_SSCRISK_CEL_OR_SPROUT_DETAIL::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template<typename T, std::size_t N1, std::size_t N2>
	SPROUT_CONSTEXPR inline bool operator!=(sprout::basic_string<T, N1> const& lhs, sprout::basic_string<T, N2> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T, std::size_t N1, std::size_t N2>
	SPROUT_CONSTEXPR inline bool operator<(sprout::basic_string<T, N1> const& lhs, sprout::basic_string<T, N2> const& rhs) {
		return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template<typename T, std::size_t N1, std::size_t N2>
	SPROUT_CONSTEXPR inline bool operator>(sprout::basic_string<T, N1> const& lhs, sprout::basic_string<T, N2> const& rhs) {
		return rhs < lhs;
	}
	template<typename T, std::size_t N1, std::size_t N2>
	SPROUT_CONSTEXPR inline bool operator<=(sprout::basic_string<T, N1> const& lhs, sprout::basic_string<T, N2> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T, std::size_t N1, std::size_t N2>
	SPROUT_CONSTEXPR inline bool operator>=(sprout::basic_string<T, N1> const& lhs, sprout::basic_string<T, N2> const& rhs) {
		return !(lhs < rhs);
	}

	//
	// swap
	//
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR inline void swap(sprout::basic_string<T, N>& lhs, sprout::basic_string<T, N>& rhs) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs))) {
		lhs.swap(rhs);
	}

	//
	// rebind_fixed_size
	//
	template<typename T, std::size_t N>
	struct rebind_fixed_size<sprout::basic_string<T, N> > {
	public:
		template<typename sprout::fixed_container_traits<sprout::basic_string<T, N> >::size_type S>
		struct apply {
			public:
				typedef sprout::basic_string<T, S> type;
		};
	};

	namespace detail {
		template<typename T, std::size_t N, std::ptrdiff_t...Indexes>
		SPROUT_CONSTEXPR inline sprout::basic_string<T, N - 1> to_string_impl(
			T const(& arr)[N],
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::basic_string<T, N - 1>{arr[Indexes]...};
		}
	}	// namespace detail
	//
	// to_string
	//
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR inline sprout::basic_string<T, N - 1> to_string(T const(& arr)[N]) {
		return sprout::detail::to_string_impl(arr, typename sprout::index_range<0, N - 1>::type());
	}

	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::push_back<sprout::basic_string<T, N>, T>::type operator+(
		sprout::basic_string<T, N> const& lhs,
		T const& rhs
		)
	{
		return sprout::fixed::push_back(lhs, rhs);
	}
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::push_front<sprout::basic_string<T, N>, T>::type operator+(
		T const& lhs,
		sprout::basic_string<T, N> const& rhs
		)
	{
		return sprout::fixed::push_front(rhs, lhs);
	}
	template<typename T, std::size_t N, std::size_t N2>
	SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::join_back<sprout::basic_string<T, N>, sprout::basic_string<T, N2 - 1> >::type operator+(
		sprout::basic_string<T, N> const& lhs,
		T const (& rhs)[N2]
		)
	{
		return sprout::fixed::join_back(lhs, to_string(rhs));
	}
	template<typename T, std::size_t N, std::size_t N2>
	SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::join_front<sprout::basic_string<T, N>, sprout::basic_string<T, N2 - 1> >::type operator+(
		T const (& lhs)[N2],
		sprout::basic_string<T, N> const& rhs
		)
	{
		return sprout::fixed::join_front(rhs, to_string(lhs));
	}
	template<typename T, std::size_t N, std::size_t N2>
	SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::join_back<sprout::basic_string<T, N>, sprout::basic_string<T, N2> >::type operator+(
		sprout::basic_string<T, N> const& lhs,
		sprout::basic_string<T, N2> const& rhs
		)
	{
		return sprout::fixed::join_back(lhs, rhs);
	}

	template<typename T, std::size_t N, typename Traits>
	inline std::basic_ostream<T, Traits>& operator<<(std::basic_ostream<T, Traits>& lhs, sprout::basic_string<T, N> const& rhs) {
		return lhs << rhs.c_str();
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
#endif	// #if 0
}	// namespace sprout

namespace std {
	//
	// tuple_size
	//
	template<typename T, std::size_t N>
	struct tuple_size<sprout::basic_string<T, N> > {
	public:
		typedef std::integral_constant<std::size_t, N> type;
		static constexpr std::size_t value = type::value;
	};

	//
	// tuple_element
	//
	template<std::size_t I, typename T, std::size_t N>
	struct tuple_element<I, sprout::basic_string<T, N> > {
	public:
		static_assert(I < N, "tuple_element<>: index out of range");
		typedef T type;
	};

	//
	// get
	//
	template<std::size_t I, typename T, std::size_t N>
	T& get(sprout::basic_string<T, N>& arr) SPROUT_NOEXCEPT {
		static_assert(I < N, "tuple_element<>: index out of range");
		return arr[I];
	}
	template<std::size_t I, typename T, std::size_t N>
	SPROUT_CONSTEXPR T const& get(sprout::basic_string<T, N> const& arr) SPROUT_NOEXCEPT {
		static_assert(I < N, "tuple_element<>: index out of range");
		return arr[I];
	}
	template<std::size_t I, typename T, std::size_t N>
	T&& get(sprout::basic_string<T, N>&& arr) SPROUT_NOEXCEPT {
		return std::move(get<I>(arr));
	}
}	// namespace std

#endif	// #ifndef SPROUT_STRING_HPP
