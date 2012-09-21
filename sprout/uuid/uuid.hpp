#ifndef SPROUT_UUID_UUID_HPP
#define SPROUT_UUID_UUID_HPP

#include <cstddef>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/reverse_iterator.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
#	include <sprout/iterator/index_iterator.hpp>
#endif

namespace sprout {
	namespace uuids {
		namespace detail {
			template<typename InputIterator>
			inline SPROUT_CONSTEXPR bool is_nil(InputIterator first, InputIterator last) {
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
			typedef sprout::index_iterator<uuid&> iterator;
			typedef sprout::index_iterator<uuid const&> const_iterator;
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
			void fill(const_reference value) {
				std::fill_n(begin(), size(), value);
			}
			void swap(uuid& other) SPROUT_NOEXCEPT {
				std::swap_ranges(other.begin(), other.end(), begin());
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
				return reverse_iterator(end());
			}
			SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT {
				return const_reverse_iterator(end());
			}
			reverse_iterator rend() SPROUT_NOEXCEPT {
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
				return static_size;
			}
			SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT {
				return size();
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
					: (throw std::out_of_range("uuid: index out of range"), elems[i])
					;
			}
			SPROUT_CONSTEXPR const_reference at(size_type i) const {
				return i < size()
					? elems[i]
					: (throw std::out_of_range("uuid: index out of range"), elems[i])
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

			pointer data() SPROUT_NOEXCEPT {
				return &elems[0];
			}
			SPROUT_CONSTEXPR const_pointer data() const SPROUT_NOEXCEPT {
				return &elems[0];
			}

			// others:
			pointer c_array() SPROUT_NOEXCEPT {
				return &elems[0];
			}
			void assign(const_reference value) {
				fill(value);
			}
			void rangecheck(size_type i) const {
				if (i >= size()) {
					throw std::out_of_range("uuid: index out of range");
				}
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
		inline SPROUT_CONSTEXPR bool operator==(sprout::uuids::uuid const& lhs, sprout::uuids::uuid const& rhs) {
			return NS_SSCRISK_CEL_OR_SPROUT::equal(lhs.begin(), lhs.end(), rhs.begin());
		}
		inline SPROUT_CONSTEXPR bool operator!=(sprout::uuids::uuid const& lhs, sprout::uuids::uuid const& rhs) {
			return !(lhs == rhs);
		}
		inline SPROUT_CONSTEXPR bool operator<(sprout::uuids::uuid const& lhs, sprout::uuids::uuid const& rhs) {
			return NS_SSCRISK_CEL_OR_SPROUT::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
		inline SPROUT_CONSTEXPR bool operator>(sprout::uuids::uuid const& lhs, sprout::uuids::uuid const& rhs) {
			return rhs < lhs;
		}
		inline SPROUT_CONSTEXPR bool operator<=(sprout::uuids::uuid const& lhs, sprout::uuids::uuid const& rhs) {
			return !(rhs < lhs);
		}
		inline SPROUT_CONSTEXPR bool operator>=(sprout::uuids::uuid const& lhs, sprout::uuids::uuid const& rhs) {
			return !(lhs < rhs);
		}

		//
		// swap
		//
		inline void swap(sprout::uuids::uuid& lhs, sprout::uuids::uuid& rhs) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs))) {
			lhs.swap(rhs);
		}
	}	// namespace uuids

	using sprout::uuids::uuid;
}	// namespace sprout

#endif	// #ifndef SPROUT_UUID_UUID_HPP
