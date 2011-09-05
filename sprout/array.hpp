#ifndef SPROUT_ARRAY_HPP
#define SPROUT_ARRAY_HPP

#include <cstddef>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/detail/iterator.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	//
	// array
	//
	template<typename T, std::size_t N>
	class array {
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
		SPROUT_STATIC_CONSTEXPR size_type static_size = N;
		SPROUT_STATIC_CONSTEXPR size_type fixed_size = static_size;
	public:
		T elems[N ? N : 1];
	public:
		SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT {
			return N;
		}
		SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT {
			return N == 0;
		}
		SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT {
			return size();
		}
		void rangecheck(size_type i) const {
			if (i >= size()) {
				throw std::out_of_range("array<>: index out of range");
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
			return reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator crbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		reverse_iterator rend() SPROUT_NOEXCEPT {
			return reverse_iterator(begin());
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
		void assign(const_reference value) {
			fill(value);
		}
		void fill(const_reference value) {
			std::fill_n(begin(), size(), value);
		}
		void swap(array<T, N>& other) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::swap(std::declval<T&>(), std::declval<T&>()))) {
			std::swap_ranges(other.begin(), other.end(), begin());
		}
		template <typename T2>
		array<T, N>& operator=(array<T2, N> const& rhs) {
			std::copy(rhs.begin(), rhs.end(), begin());
			return *this;
		}
		template <typename T2>
		array<T, N>& operator=(array<T2, N>&& rhs) {
			std::move(rhs.begin(), rhs.end(), begin());
			return *this;
		}
	};
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR inline bool operator==(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR inline bool operator!=(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR inline bool operator<(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR inline bool operator>(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return rhs < lhs;
	}
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR inline bool operator<=(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR inline bool operator>=(sprout::array<T, N> const& lhs, sprout::array<T, N> const& rhs) {
		return !(lhs < rhs);
	}

	//
	// swap
	//
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR inline void swap(sprout::array<T, N>& lhs, sprout::array<T, N>& rhs) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs))) {
		lhs.swap(rhs);
	}

	//
	// rebind_fixed_size
	//
	template<typename T, std::size_t N>
	struct rebind_fixed_size<sprout::array<T, N> > {
	public:
		template<typename sprout::fixed_container_traits<sprout::array<T, N> >::size_type S>
		struct apply {
			public:
				typedef sprout::array<T, S> type;
		};
	};

	namespace detail {
		template<typename T, typename Enable = void>
		struct is_array_impl {
		public:
			typedef std::integral_constant<bool, false> type;
			SPROUT_STATIC_CONSTEXPR bool value = type::value;
		};
		template<typename T>
		struct is_array_impl<
			T,
			typename std::enable_if<
				std::is_same<
					T,
					sprout::array<typename T::value_type, T::static_size>
				>::value
			>::type
		> {
		public:
			typedef std::integral_constant<bool, true> type;
			SPROUT_STATIC_CONSTEXPR bool value = type::value;
		};
	}	// namespace detail
	//
	// is_array
	//
	template<typename T>
	struct is_array
		: public sprout::detail::is_array_impl<T>
	{};

	//
	// make_array
	//
	template<typename T, typename... Tail>
	SPROUT_CONSTEXPR inline sprout::array<T, 1 + sizeof...(Tail)> make_array(T const& head, Tail const&... tail) {
		return sprout::array<T, 1 + sizeof...(Tail)>{{head, tail...}};
	}
	template<typename T>
	SPROUT_CONSTEXPR inline sprout::array<T, 0> make_array() {
		return sprout::array<T, 0>{};
	}

	namespace detail {
		template<typename T, std::size_t N, std::ptrdiff_t...Indexes>
		SPROUT_CONSTEXPR inline sprout::array<T, N> to_array_impl(
			T const (& arr)[N],
			sprout::index_tuple<Indexes...>
			)
		{
			return sprout::array<T, N>{{arr[Indexes]...}};
		}
	}	// namespace detail
	//
	// to_array
	//
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR inline sprout::array<T, N> to_array(T const (& arr)[N]) {
		return sprout::detail::to_array_impl(arr, typename sprout::index_range<0, N>::type());
	}
}	// namespace sprout

namespace std {
	//
	// tuple_size
	//
	template<typename T, std::size_t N>
	struct tuple_size<sprout::array<T, N> > {
	public:
		typedef std::integral_constant<std::size_t, N> type;
		SPROUT_STATIC_CONSTEXPR std::size_t value = type::value;
	};

	//
	// tuple_element
	//
	template<std::size_t I, typename T, std::size_t N>
	struct tuple_element<I, sprout::array<T, N> > {
	public:
		static_assert(I < N, "tuple_element<>: index out of range");
		typedef T type;
	};

	//
	// get
	//
	template<std::size_t I, typename T, std::size_t N>
	T& get(sprout::array<T, N>& arr) SPROUT_NOEXCEPT {
		static_assert(I < N, "tuple_element<>: index out of range");
		return arr[I];
	}
	template<std::size_t I, typename T, std::size_t N>
	SPROUT_CONSTEXPR T const& get(sprout::array<T, N> const& arr) SPROUT_NOEXCEPT {
		static_assert(I < N, "tuple_element<>: index out of range");
		return arr[I];
	}
	template<std::size_t I, typename T, std::size_t N>
	T&& get(sprout::array<T, N>&& arr) SPROUT_NOEXCEPT {
		return std::move(get<I>(arr));
	}
}	// namespace std

#endif	// #ifndef SPROUT_ARRAY_HPP
