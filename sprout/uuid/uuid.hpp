/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UUID_UUID_HPP
#define SPROUT_UUID_UUID_HPP

#include <utility>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/reverse_iterator.hpp>
#include <sprout/algorithm/equal.hpp>
#include <sprout/algorithm/lexicographical_compare.hpp>
#include <sprout/algorithm/cxx14/fill_n.hpp>
#include <sprout/algorithm/cxx14/swap_ranges.hpp>
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
#	include <sprout/iterator/index_iterator.hpp>
#endif

namespace sprout {
	namespace uuids {
		namespace detail {
			template<typename InputIterator>
			inline SPROUT_CONSTEXPR bool
			is_nil(InputIterator first, InputIterator last) {
				return first == last ? true
					: !*first && sprout::uuids::detail::is_nil(sprout::next(first), last)
					;
			}
		}	// namespace detail

		//
		// uuid
		//
		class uuid {
		public:
			typedef std::uint8_t value_type;
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
			typedef sprout::index_iterator<uuid&, true> iterator;
			typedef sprout::index_iterator<uuid const&, true> const_iterator;
#else
			typedef std::uint8_t* iterator;
			typedef std::uint8_t const* const_iterator;
#endif
			typedef std::uint8_t& reference;
			typedef std::uint8_t const& const_reference;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef std::uint8_t* pointer;
			typedef std::uint8_t const* const_pointer;
			typedef sprout::reverse_iterator<iterator> reverse_iterator;
			typedef sprout::reverse_iterator<const_iterator> const_reverse_iterator;
		public:
			//
			// variant_type
			//
			enum variant_type {
				variant_ncs,
				variant_rfc_4122,
				variant_microsoft,
				variant_future
			};
			//
			// version_type
			//
			enum version_type {
				version_unknown = -1,
				version_time_based = 1,
				version_dce_security = 2,
				version_name_based_md5 = 3,
				version_random_number_based = 4,
				version_name_based_sha1 = 5
			};
		public:
			SPROUT_STATIC_CONSTEXPR size_type static_size = 16;
		public:
			value_type elems[static_size];
		public:
			SPROUT_CXX14_CONSTEXPR void fill(const_reference value) {
				sprout::fill_n(begin(), size(), value);
			}
			SPROUT_CXX14_CONSTEXPR void swap(uuid& other) SPROUT_NOEXCEPT {
				sprout::swap_ranges(other.begin(), other.end(), begin());
			}
			// iterators:
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
			SPROUT_CXX14_CONSTEXPR iterator begin() SPROUT_NOEXCEPT {
				return iterator(*this, 0);
			}
			SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT {
				return const_iterator(*this, 0);
			}
			SPROUT_CXX14_CONSTEXPR iterator end() SPROUT_NOEXCEPT {
				return iterator(*this, size());
			}
			SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
				return const_iterator(*this, size());
			}
#else
			SPROUT_CXX14_CONSTEXPR iterator begin() SPROUT_NOEXCEPT {
				return elems;
			}
			SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT {
				return elems;
			}
			SPROUT_CXX14_CONSTEXPR iterator end() SPROUT_NOEXCEPT {
				return begin() + size();
			}
			SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
				return begin() + size();
			}
#endif
			SPROUT_CXX14_CONSTEXPR reverse_iterator rbegin() SPROUT_NOEXCEPT {
				return reverse_iterator(end());
			}
			SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT {
				return const_reverse_iterator(end());
			}
			SPROUT_CXX14_CONSTEXPR reverse_iterator rend() SPROUT_NOEXCEPT {
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
				return elems;
			}
			SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT {
				return cbegin() + size();
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
			SPROUT_CXX14_CONSTEXPR reference operator[](size_type i) {
				return elems[i];
			}
			SPROUT_CONSTEXPR const_reference operator[](size_type i) const {
				return elems[i];
			}
			SPROUT_CXX14_CONSTEXPR reference at(size_type i) {
				return i < size()
					? elems[i]
					: (throw std::out_of_range("uuid: index out of range"), elems[i])
					;
			}
			SPROUT_CONSTEXPR const_reference at(size_type i) const {
				return i < size()
					? elems[i]
					: (throw std::out_of_range("uuid: index out of range"), elems[i])
					;
			}
			SPROUT_CXX14_CONSTEXPR reference front() {
				return elems[0];
			}
			SPROUT_CONSTEXPR const_reference front() const {
				return elems[0];
			}
			SPROUT_CXX14_CONSTEXPR reference back() {
				return elems[size() - 1];
			}
			SPROUT_CONSTEXPR const_reference back() const {
				return elems[size() - 1];
			}

			SPROUT_CXX14_CONSTEXPR pointer data() SPROUT_NOEXCEPT {
				return elems;
			}
			SPROUT_CONSTEXPR const_pointer data() const SPROUT_NOEXCEPT {
				return elems;
			}

			// others:
			SPROUT_CXX14_CONSTEXPR pointer c_array() SPROUT_NOEXCEPT {
				return elems;
			}
			SPROUT_CONSTEXPR const_pointer c_array() const SPROUT_NOEXCEPT {
				return elems;
			}
			SPROUT_CXX14_CONSTEXPR void assign(const_reference value) {
				fill(value);
			}
			SPROUT_CXX14_CONSTEXPR void rangecheck(size_type i) const {
				return i >= size() ? throw std::out_of_range("uuid: index out of range")
					: (void)0
					;
			}

			SPROUT_CONSTEXPR bool is_nil() const {
				return sprout::uuids::detail::is_nil(begin(), end());
			}
			SPROUT_CONSTEXPR variant_type variant() const {
				return (elems[8] & 0x80) == 0x00 ? variant_ncs
					: (elems[8] & 0xC0) == 0x80 ? variant_rfc_4122
					: (elems[8] & 0xE0) == 0xC0 ? variant_microsoft
					: variant_future
					;
			}
			SPROUT_CONSTEXPR version_type version() const {
				return (elems[6] & 0xF0) == 0x10 ? version_time_based
					: (elems[6] & 0xF0) == 0x20 ? version_dce_security
					: (elems[6] & 0xF0) == 0x30 ? version_name_based_md5
					: (elems[6] & 0xF0) == 0x40 ? version_random_number_based
					: (elems[6] & 0xF0) == 0x50 ? version_name_based_sha1
					: version_unknown
					;
			}
		};

		//
		// operator==
		// operator!=
		// operator<
		// operator>
		// operator<=
		// operator>=
		//
		inline SPROUT_CONSTEXPR bool
		operator==(sprout::uuids::uuid const& lhs, sprout::uuids::uuid const& rhs) {
			return sprout::equal(lhs.begin(), lhs.end(), rhs.begin());
		}
		inline SPROUT_CONSTEXPR bool
		operator!=(sprout::uuids::uuid const& lhs, sprout::uuids::uuid const& rhs) {
			return !(lhs == rhs);
		}
		inline SPROUT_CONSTEXPR bool
		operator<(sprout::uuids::uuid const& lhs, sprout::uuids::uuid const& rhs) {
			return sprout::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
		inline SPROUT_CONSTEXPR bool
		operator>(sprout::uuids::uuid const& lhs, sprout::uuids::uuid const& rhs) {
			return rhs < lhs;
		}
		inline SPROUT_CONSTEXPR bool
		operator<=(sprout::uuids::uuid const& lhs, sprout::uuids::uuid const& rhs) {
			return !(rhs < lhs);
		}
		inline SPROUT_CONSTEXPR bool
		operator>=(sprout::uuids::uuid const& lhs, sprout::uuids::uuid const& rhs) {
			return !(lhs < rhs);
		}

		//
		// swap
		//
		inline SPROUT_CXX14_CONSTEXPR void
		swap(sprout::uuids::uuid& lhs, sprout::uuids::uuid& rhs)
		SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
		{
			lhs.swap(rhs);
		}
	}	// namespace uuids

	using sprout::uuids::uuid;
}	// namespace sprout

#endif	// #ifndef SPROUT_UUID_UUID_HPP
