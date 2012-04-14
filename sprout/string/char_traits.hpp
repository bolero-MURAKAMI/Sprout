#ifndef SPROUT_STRING_CHAR_TRAITS_HPP
#define SPROUT_STRING_CHAR_TRAITS_HPP

#include <cstddef>
#include <algorithm>
#include <string>
#include <sprout/config.hpp>

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
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_CHAR_TRAITS_HPP
