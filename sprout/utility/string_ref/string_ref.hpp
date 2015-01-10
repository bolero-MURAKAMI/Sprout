/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_STRING_REF_STRING_REF_HPP
#define SPROUT_UTILITY_STRING_REF_STRING_REF_HPP

#include <string>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/iterator/reverse_iterator.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/string/char_traits.hpp>
#include <sprout/string/npos.hpp>
#include <sprout/string/string.hpp>
#include <sprout/string/detail/operations.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
#	include <sprout/iterator/index_iterator.hpp>
#endif

namespace sprout {
	//
	// basic_string_ref
	//
	template<typename T, typename Traits = sprout::char_traits<T> >
	class basic_string_ref {
	public:
		typedef T value_type;
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		typedef sprout::index_iterator<basic_string_ref&, true> iterator;
		typedef sprout::index_iterator<basic_string_ref const&, true> const_iterator;
#else
		typedef T const* iterator;
		typedef T const* const_iterator;
#endif
		typedef T const& reference;
		typedef T const& const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef T const* pointer;
		typedef T const* const_pointer;
		typedef sprout::reverse_iterator<iterator> reverse_iterator;
		typedef sprout::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef Traits traits_type;
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
	private:
		template<typename Iterator>
		class is_string_ref_iterator
			: public sprout::bool_constant<
				std::is_same<Iterator, sprout::index_iterator<basic_string_ref&, true> >::value
					|| std::is_same<Iterator, sprout::index_iterator<basic_string_ref const&, true> >::value
			>
		{};
		template<typename Iterator>
		class is_string_ref_iterator<Iterator const>
			: public is_string_ref_iterator<Iterator>
		{};
		template<typename Iterator>
		class is_string_ref_iterator<Iterator volatile>
			: public is_string_ref_iterator<Iterator>
		{};
		template<typename Iterator>
		class is_string_ref_iterator<Iterator const volatile>
			: public is_string_ref_iterator<Iterator>
		{};
#endif
	public:
		SPROUT_STATIC_CONSTEXPR size_type npos = sprout::npos_t::get<size_type>::value;
	private:
		const_pointer ptr_;
		size_type len_;
	private:
	public:
		// construct/copy/destroy:
		SPROUT_CONSTEXPR basic_string_ref()
			: ptr_(0), len_(0)
		{}
		basic_string_ref(basic_string_ref const& rhs) = default;
		SPROUT_CXX14_CONSTEXPR basic_string_ref& operator=(basic_string_ref const& rhs) {
			basic_string_ref temp(rhs);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR basic_string_ref(const_pointer str)
			: ptr_(str), len_(traits_type::length(str))
		{}
		template<std::size_t N>
		SPROUT_CONSTEXPR basic_string_ref(sprout::basic_string<T, N, Traits> const& str)
			: ptr_(str.data()), len_(str.size())
		{}
		template<typename Allocator>
		SPROUT_NON_CONSTEXPR basic_string_ref(std::basic_string<T, Traits, Allocator> const& str)
			: ptr_(str.data()), len_(str.size())
		{}
		SPROUT_CONSTEXPR basic_string_ref(const_pointer str, size_type len)
			: ptr_(str), len_(len)
		{}
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
		SPROUT_CONSTEXPR const_reverse_iterator
		rbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
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
			return len_;
		}
		SPROUT_CONSTEXPR size_type
		length() const SPROUT_NOEXCEPT {
			return size();
		}
		SPROUT_CONSTEXPR size_type
		max_size() const SPROUT_NOEXCEPT {
			return size();
		}
		SPROUT_CXX14_CONSTEXPR void
		clear() {
			len_ = 0;
		}
		SPROUT_CONSTEXPR bool
		empty() const SPROUT_NOEXCEPT {
			return size() == 0;
		}
		// element access:
		SPROUT_CONSTEXPR const_reference
		operator[](size_type i) const {
			return ptr_[i];
		}
		SPROUT_CONSTEXPR const_reference
		at(size_type i) const {
			return i < size() ? ptr_[i]
				: (throw std::out_of_range("basic_string_ref<>: index out of range"), ptr_[i])
				;
		}
		SPROUT_CONSTEXPR const_reference
		front() const {
			return ptr_[0];
		}
		SPROUT_CONSTEXPR const_reference
		back() const {
			return ptr_[size() - 1];
		}
		// modifiers:
		SPROUT_CXX14_CONSTEXPR void
		swap(basic_string_ref& other)
		SPROUT_NOEXCEPT
		{
			sprout::swap(ptr_, other.ptr_);
			sprout::swap(len_, other.len_);
		}
		SPROUT_CXX14_CONSTEXPR void
		remove_prefix(size_type n) {
			if (n > size()) {
				n = size();
			}
			ptr_ += n;
			len_ -= n;
		}
		SPROUT_CONSTEXPR basic_string_ref
		remove_prefix(size_type n) const {
			return n > size() ? basic_string_ref(data() + size(), 0)
				: basic_string_ref(data() + n, size() - n)
				;
		}
		SPROUT_CXX14_CONSTEXPR void
		remove_suffix(size_type n) {
			if (n > size()) {
				n = size();
			}
			len_ -= n;
		}
		SPROUT_CONSTEXPR basic_string_ref
		remove_suffix(size_type n) const {
			return n > size() ? basic_string_ref(data(), 0)
				: basic_string_ref(data(), size() - n)
				;
		}
		// string operations:
		SPROUT_CONSTEXPR const_pointer
		c_str() const SPROUT_NOEXCEPT {
			return data();
		}
		SPROUT_CONSTEXPR const_pointer
		data() const SPROUT_NOEXCEPT {
			return ptr_;
		}

		SPROUT_CONSTEXPR size_type
		find(basic_string_ref const& str, size_type pos = 0) const SPROUT_NOEXCEPT {
			return sprout::string_detail::find_impl<basic_string_ref>(begin(), size(), str.begin(), pos, str.size());
		}
		SPROUT_CONSTEXPR size_type
		find(value_type const* s, size_type pos, size_type n) const {
			return sprout::string_detail::find_impl<basic_string_ref>(begin(), size(), s, pos, n);
		}
		SPROUT_CONSTEXPR size_type
		find(value_type const* s, size_type pos = 0) const {
			return find(s, pos, traits_type::length(s));
		}
		SPROUT_CONSTEXPR size_type
		find(value_type c, size_type pos = 0) const {
			return sprout::string_detail::find_c_impl<basic_string_ref>(begin(), size(), c, pos);
		}
		SPROUT_CONSTEXPR size_type
		rfind(basic_string_ref const& str, size_type pos = npos) const SPROUT_NOEXCEPT {
			return sprout::string_detail::rfind_impl<basic_string_ref>(begin(), size(), str.begin(), pos, str.size());
		}
		SPROUT_CONSTEXPR size_type
		rfind(value_type const* s, size_type pos, size_type n) const {
			return sprout::string_detail::rfind_impl<basic_string_ref>(begin(), size(), s, pos, n);
		}
		SPROUT_CONSTEXPR size_type
		rfind(value_type const* s, size_type pos = npos) const {
			return rfind(s, pos, traits_type::length(s));
		}
		SPROUT_CONSTEXPR size_type
		rfind(value_type c, size_type pos = npos) const {
			return sprout::string_detail::rfind_c_impl<basic_string_ref>(begin(), size(), c, pos);
		}
		SPROUT_CONSTEXPR size_type
		find_first_of(basic_string_ref const& str, size_type pos = 0) const SPROUT_NOEXCEPT {
			return sprout::string_detail::find_first_of_impl<basic_string_ref>(begin(), size(), str.begin(), pos, str.size());
		}
		SPROUT_CONSTEXPR size_type
		find_first_of(value_type const* s, size_type pos, size_type n) const {
			return sprout::string_detail::find_first_of_impl<basic_string_ref>(begin(), size(), s, pos, n);
		}
		SPROUT_CONSTEXPR size_type
		find_first_of(value_type const* s, size_type pos = 0) const {
			return find_first_of(s, pos, traits_type::length(s));
		}
		SPROUT_CONSTEXPR size_type
		find_first_of(value_type c, size_type pos = 0) const {
			return find(c, pos);
		}
		SPROUT_CONSTEXPR size_type
		find_last_of(basic_string_ref const& str, size_type pos = npos) const SPROUT_NOEXCEPT {
			return sprout::string_detail::find_last_of_impl<basic_string_ref>(begin(), size(), str.begin(), pos, str.size());
		}
		SPROUT_CONSTEXPR size_type
		find_last_of(value_type const* s, size_type pos, size_type n) const {
			return sprout::string_detail::find_last_of_impl<basic_string_ref>(begin(), size(), s, pos, n);
		}
		SPROUT_CONSTEXPR size_type
		find_last_of(value_type const* s, size_type pos = npos) const {
			return find_last_of(s, pos, traits_type::length(s));
		}
		SPROUT_CONSTEXPR size_type
		find_last_of(value_type c, size_type pos = npos) const {
			return rfind(c, pos);
		}
		SPROUT_CONSTEXPR size_type
		find_first_not_of(basic_string_ref const& str, size_type pos = 0) const SPROUT_NOEXCEPT {
			return sprout::string_detail::find_first_not_of_impl<basic_string_ref>(begin(), size(), str.begin(), pos, str.size());
		}
		SPROUT_CONSTEXPR size_type
		find_first_not_of(value_type const* s, size_type pos, size_type n) const {
			return sprout::string_detail::find_first_not_of_impl<basic_string_ref>(begin(), size(), s, pos, n);
		}
		SPROUT_CONSTEXPR size_type
		find_first_not_of(value_type const* s, size_type pos = 0) const {
			return find_first_not_of(s, pos, traits_type::length(s));
		}
		SPROUT_CONSTEXPR size_type
		find_first_not_of(value_type c, size_type pos = 0) const {
			return sprout::string_detail::find_first_not_of_c_impl<basic_string_ref>(begin(), size(), c, pos);
		}
		SPROUT_CONSTEXPR size_type
		find_last_not_of(basic_string_ref const& str, size_type pos = npos) const SPROUT_NOEXCEPT {
			return sprout::string_detail::find_last_not_of_impl<basic_string_ref>(begin(), size(), str.begin(), pos, str.size());
		}
		SPROUT_CONSTEXPR size_type
		find_last_not_of(value_type const* s, size_type pos, size_type n) const {
			return sprout::string_detail::find_last_not_of_impl<basic_string_ref>(begin(), size(), s, pos, n);
		}
		SPROUT_CONSTEXPR size_type
		find_last_not_of(value_type const* s, size_type pos = npos) const {
			return find_last_not_of(s, pos, traits_type::length(s));
		}
		SPROUT_CONSTEXPR size_type
		find_last_not_of(value_type c, size_type pos = npos) const {
			return sprout::string_detail::find_last_not_of_c_impl<basic_string_ref>(begin(), size(), c, pos);
		}
		SPROUT_CONSTEXPR basic_string_ref
		substr(size_type pos = 0, size_type n = npos) const {
			return !(size() < pos) ? n == npos
					? substr(pos, size() - pos)
					: basic_string_ref(c_str() + pos, n)
				: throw std::out_of_range("basic_string_ref<>: index out of range")
				;
		}
		SPROUT_CONSTEXPR int
		compare(basic_string_ref const& str) const {
			return compare(0, size(), str.begin(), str.size());
		}
		SPROUT_CONSTEXPR int
		compare(value_type const* s) const {
			return compare(0, size(), s, traits_type::length(s));
		}
		SPROUT_CONSTEXPR int
		compare(size_type pos1, size_type n1, basic_string_ref const& str) const {
			return compare(pos1, n1, str, 0, npos);
		}
		SPROUT_CONSTEXPR int
		compare(size_type pos1, size_type n1, value_type const* s) const {
			return compare(pos1, n1, s, traits_type::length(s));
		}
		SPROUT_CONSTEXPR int
		compare(size_type pos1, size_type n1, basic_string_ref const& str, size_type pos2, size_type n2) const {
			return !(str.size() < pos2)
				? compare(pos1, n1, str.begin() + pos2, NS_SSCRISK_CEL_OR_SPROUT::min(n2, str.size() - pos2))
				: throw std::out_of_range("basic_string_ref<>: index out of range")
				;
		}
		SPROUT_CONSTEXPR int
		compare(size_type pos1, size_type n1, value_type const* s, size_type n2) const {
			return !(size() < pos1)
				? sprout::string_detail::compare_impl<basic_string_ref>(begin(), pos1, NS_SSCRISK_CEL_OR_SPROUT::min(n1, size() - pos1), s, n2)
				: throw std::out_of_range("basic_string_ref<>: index out of range")
				;
		}
		SPROUT_CONSTEXPR bool
		starts_with(value_type c) const {
			return !empty() && traits_type::eq(c, front());
		}
		SPROUT_CONSTEXPR bool
		starts_with(basic_string_ref const& str) const {
			return size() >= str.size() && traits_type::compare(data(), str.data(), str.size()) == 0;
		}
		SPROUT_CONSTEXPR bool
		ends_with(value_type c) const {
			return !empty() && traits_type::eq(c, back());
		}
		SPROUT_CONSTEXPR bool
		ends_with(basic_string_ref const& str) const {
			return size() >= str.size() && traits_type::compare(data() + size() - str.size(), str.data(), str.size()) == 0;
		}
		// others:
		template<typename Allocator>
		SPROUT_EXPLICIT_CONVERSION SPROUT_NON_CONSTEXPR operator std::basic_string<T, Traits, Allocator>() const {
			return std::basic_string<T, Traits, Allocator>(data(), size());
		}
		SPROUT_CONSTEXPR const_pointer
		c_array() const SPROUT_NOEXCEPT {
			return data();
		}
		SPROUT_CXX14_CONSTEXPR pointer
		c_array() SPROUT_NOEXCEPT {
			return data();
		}
		// others:
		SPROUT_CXX14_CONSTEXPR void
		rangecheck(size_type i) const {
			if (i >= size()) {
				throw std::out_of_range("basic_string_ref<>: index out of range");
			}
		}

#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			size_type
		>::type
		find(ConstIterator s, size_type pos, size_type n) const {
			return sprout::string_detail::find_impl<basic_string_ref>(begin(), size(), s, pos, n);
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			size_type
		>::type
		find(ConstIterator s, size_type pos = 0) const {
			return find(s, pos, traits_type::length(s));
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			size_type
		>::type
		rfind(ConstIterator s, size_type pos, size_type n) const {
			return sprout::string_detail::rfind_impl<basic_string_ref>(begin(), size(), s, pos, n);
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			size_type
		>::type
		rfind(ConstIterator s, size_type pos = npos) const {
			return rfind(s, pos, traits_type::length(s));
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			size_type
		>::type
		find_first_of(ConstIterator s, size_type pos, size_type n) const {
			return sprout::string_detail::find_first_of_impl<basic_string_ref>(begin(), size(), s, pos, n);
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			size_type
		>::type
		find_first_of(ConstIterator s, size_type pos = 0) const {
			return find_first_of(s, pos, traits_type::length(s));
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			size_type
		>::type
		find_last_of(ConstIterator s, size_type pos, size_type n) const {
			return sprout::string_detail::find_last_of_impl<basic_string_ref>(begin(), size(), s, pos, n);
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			size_type
		>::type
		find_last_of(ConstIterator s, size_type pos = 0) const {
			return find_last_of(s, pos, traits_type::length(s));
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			size_type
		>::type
		find_first_not_of(ConstIterator s, size_type pos, size_type n) const {
			return sprout::string_detail::find_first_not_of_impl<basic_string_ref>(begin(), size(), s, pos, n);
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			size_type
		>::type
		find_first_not_of(ConstIterator s, size_type pos = 0) const {
			return sprout::string_detail::find_first_not_of_impl<basic_string_ref>(s, pos, traits_type::length(s));
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			size_type
		>::type
		find_last_not_of(ConstIterator s, size_type pos, size_type n) const {
			return sprout::string_detail::find_last_not_of_impl<basic_string_ref>(begin(), size(), s, pos, n);
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			size_type
		>::type
		find_last_not_of(ConstIterator s, size_type pos = npos) const {
			return sprout::string_detail::find_last_not_of_impl<basic_string_ref>(s, pos, traits_type::length(s));
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			int
		>::type
		compare(ConstIterator s) const {
			return compare(0, size(), s, traits_type::length(s));
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			int
		>::type
		compare(size_type pos1, size_type n1, ConstIterator s) const {
			return compare(pos1, n1, s, traits_type::length(s));
		}
		template<typename ConstIterator>
		SPROUT_CONSTEXPR typename std::enable_if<
			is_string_ref_iterator<ConstIterator>::value,
			int
		>::type
		compare(size_type pos1, size_type n1, ConstIterator s, size_type n2) const {
			return !(size() < pos1)
				? sprout::string_detail::compare_impl<basic_string_ref>(begin(), pos1, NS_SSCRISK_CEL_OR_SPROUT::min(n1, size() - pos1), s, n2)
				: throw std::out_of_range("basic_string_ref<>: index out of range")
				;
		}
#endif
	};
	template<typename T, typename Traits>
	SPROUT_CONSTEXPR_OR_CONST typename sprout::basic_string_ref<T, Traits>::size_type sprout::basic_string_ref<T, Traits>::npos;

	//
	// swap
	//
	template<typename T, typename Traits>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::basic_string_ref<T, Traits>& lhs, sprout::basic_string_ref<T, Traits>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// to_string_ref
	//
	template<typename T, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string_ref<T, Traits>
	to_string_ref(sprout::basic_string_ref<T, Traits> const& s) {
		return s;
	}
	template<typename T, std::size_t N, typename Traits>
	inline SPROUT_CONSTEXPR sprout::basic_string_ref<T, Traits>
	to_string_ref(sprout::basic_string<T, N, Traits> const& s) {
		return sprout::basic_string_ref<T, Traits>(s);
	}
	template<typename T, typename Traits>
	inline SPROUT_NON_CONSTEXPR sprout::basic_string_ref<T, Traits>
	to_string_ref(std::basic_string<T, Traits> const& s) {
		return sprout::basic_string_ref<T, Traits>(s);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::basic_string_ref<T>
	to_string_ref(T const* str) {
		return sprout::basic_string_ref<T>(str);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::basic_string_ref<T>
	to_string_ref(T const* str, std::size_t len) {
		return sprout::basic_string_ref<T>(str, len);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_STRING_REF_STRING_REF_HPP
