#ifndef SPROUT_STRING_CHAR_TRAITS_HPP
#define SPROUT_STRING_CHAR_TRAITS_HPP

#include <cstddef>
#include <string>
#include <algorithm>
#include <sprout/config.hpp>
#include <sprout/functional/bind2nd.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/algorithm/find_if.hpp>
#include <sprout/algorithm/tristate_lexicographical_compare.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/cstring/strlen.hpp>

namespace sprout {
	namespace detail {
		template<typename Traits>
		class char_traits_eq {
		public:
			typedef Traits traits_type;
			typedef typename traits_type::char_type char_type;
			typedef bool result_type;
			typedef char_type first_argument_type;
			typedef char_type second_argument_type;
		public:
			SPROUT_CONSTEXPR bool operator()(char_type c1, char_type c2) const SPROUT_NOEXCEPT {
				return traits_type::eq(c1, c2);
			}
		};

		template<typename Traits>
		class char_traits_lt {
		public:
			typedef Traits traits_type;
			typedef typename traits_type::char_type char_type;
			typedef bool result_type;
			typedef char_type first_argument_type;
			typedef char_type second_argument_type;
		public:
			SPROUT_CONSTEXPR bool operator()(char_type c1, char_type c2) const SPROUT_NOEXCEPT {
				return traits_type::lt(c1, c2);
			}
		};
	}	// namespace detail

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
	private:
		static SPROUT_CONSTEXPR char_type const* find_impl(char_type const* found, char_type const* last) {
			return found == last ? nullptr
				: found
				;
		}
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
			return sprout::tristate_lexicographical_compare(
				sprout::as_iterator(s1), sprout::as_iterator(s1, n), char_type(),
				sprout::as_iterator(s2), sprout::as_iterator(s2, n), char_type(),
				sprout::detail::char_traits_lt<char_traits>()
				);
		}
		static SPROUT_CONSTEXPR std::size_t length(char_type const* s) {
			return sprout::strlen(s);
		}
		static SPROUT_CONSTEXPR char_type const* find(char_type const* s, std::size_t n, char_type const& a) {
			return find_impl(
				sprout::as_iterator_base(
					sprout::find_if(
						sprout::as_iterator(s), sprout::as_iterator(s, n),
						sprout::bind2nd(sprout::detail::char_traits_eq<char_traits>(), a)
						)
					),
				s + n
				);
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
			return sprout::tristate_lexicographical_compare(
				sprout::as_iterator(s1), sprout::as_iterator(s1, n), char_type(),
				s2, s2 + n, char_type(),
				sprout::detail::char_traits_lt<char_traits>()
				);
		}
		template<typename ConstIterator>
		static SPROUT_CONSTEXPR int compare(ConstIterator s1, char_type const* s2, std::size_t n) {
			return sprout::tristate_lexicographical_compare(
				s1, s1 + n, char_type(),
				sprout::as_iterator(s2), sprout::as_iterator(s2, n), char_type(),
				sprout::detail::char_traits_lt<char_traits>()
				);
		}
		template<typename ConstIterator1, typename ConstIterator2>
		static SPROUT_CONSTEXPR int compare(ConstIterator1 s1, ConstIterator2 s2, std::size_t n) {
			return sprout::tristate_lexicographical_compare(
				s1, s1 + n, char_type(),
				s2, s2 + n, char_type(),
				sprout::detail::char_traits_lt<char_traits>()
				);
		}
		template<typename ConstIterator>
		static SPROUT_CONSTEXPR std::size_t length(ConstIterator s) {
			return sprout::detail::strlen(s);
		}
		template<typename ConstIterator>
		static SPROUT_CONSTEXPR ConstIterator find(ConstIterator s, std::size_t n, char_type const& a) {
			return sprout::as_iterator_base(
				sprout::find_if(
					s, s + n,
					sprout::bind2nd(sprout::detail::char_traits_eq<char_traits>(), a)
					)
				);
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
	// char_traits_helper
	//
	template<typename Traits>
	class char_traits_helper {
	public:
		typedef Traits traits_type;
		typedef typename traits_type::char_type char_type;
		typedef typename traits_type::int_type int_type;
		typedef typename traits_type::off_type off_type;
		typedef typename traits_type::pos_type pos_type;
		typedef typename traits_type::state_type state_type;
	public:
		static SPROUT_CONSTEXPR std::size_t length(char_type const* s, std::size_t n) {
			return sprout::strlen(s, n);
		}
		static SPROUT_CONSTEXPR char_type const* find(char_type const* s, std::size_t n, char_type const& a) {
			return sprout::as_iterator_base(
				sprout::find_if(
					sprout::as_iterator(s), sprout::as_iterator(s, n),
					sprout::bind2nd(sprout::detail::char_traits_eq<traits_type>(), a)
					)
				);
		}
		static SPROUT_CONSTEXPR bool is_found(char_type const* found, char_type const* last) {
			return found != last;
		}
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		template<typename ConstIterator>
		static SPROUT_CONSTEXPR std::size_t length(ConstIterator s, std::size_t n) {
			return sprout::detail::strlen(s, n);
		}
		template<typename ConstIterator>
		static SPROUT_CONSTEXPR ConstIterator find(ConstIterator s, std::size_t n, char_type const& a) {
			return sprout::find_if(
				s, s + n,
				sprout::bind2nd(sprout::detail::char_traits_eq<traits_type>(), a)
				);
		}
		template<typename ConstIterator>
		static SPROUT_CONSTEXPR bool is_found(ConstIterator found, ConstIterator last) {
			return found != last;
		}
#endif
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_CHAR_TRAITS_HPP
