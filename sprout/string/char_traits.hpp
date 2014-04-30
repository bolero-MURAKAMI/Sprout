/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STRING_CHAR_TRAITS_HPP
#define SPROUT_STRING_CHAR_TRAITS_HPP

#include <cstdio>
#include <string>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/functional/bind2nd.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/algorithm/find_if.hpp>
#include <sprout/algorithm/tristate_lexicographical_compare.hpp>
#include <sprout/algorithm/cxx14/copy.hpp>
#include <sprout/algorithm/cxx14/copy_backward.hpp>
#include <sprout/algorithm/cxx14/fill.hpp>
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
		static SPROUT_CXX14_CONSTEXPR void assign(char_type& c1, char_type const& c2) SPROUT_NOEXCEPT {
			c1 = c2;
		}
#ifdef SPROUT_NO_CXX11_CHAR_TRAITS
		static SPROUT_CONSTEXPR bool eq(char_type c1, char_type c2) SPROUT_NOEXCEPT {
			return c1 == c2;
		}
		static SPROUT_CONSTEXPR bool lt(char_type c1, char_type c2) SPROUT_NOEXCEPT {
			return c1 < c2;
		}
#else
		static SPROUT_CONSTEXPR bool eq(char_type c1, char_type c2) SPROUT_NOEXCEPT {
			return impl_type::eq(c1, c2);
		}
		static SPROUT_CONSTEXPR bool lt(char_type c1, char_type c2) SPROUT_NOEXCEPT {
			return impl_type::lt(c1, c2);
		}
#endif
		static SPROUT_CONSTEXPR int compare(char_type const* s1, char_type const* s2, std::size_t n) {
			return sprout::tristate_lexicographical_compare(
				sprout::ptr_index(s1), sprout::ptr_index(s1, n), char_type(),
				sprout::ptr_index(s2), sprout::ptr_index(s2, n), char_type(),
				sprout::detail::char_traits_lt<char_traits>()
				);
		}
		static SPROUT_CONSTEXPR std::size_t length(char_type const* s) {
			return sprout::strlen(s);
		}
		static SPROUT_CONSTEXPR char_type const* find(char_type const* s, std::size_t n, char_type const& a) {
			return find_impl(
				sprout::ptr_unindex(
					sprout::find_if(
						sprout::ptr_index(s), sprout::ptr_index(s, n),
						sprout::bind2nd(sprout::detail::char_traits_eq<char_traits>(), a)
						)
					),
				s + n
				);
		}
		static SPROUT_CXX14_CONSTEXPR char_type* move(char_type* s1, char_type const* s2, std::size_t n) {
			sprout::copy_backward(s2, s2 + n, s1);
			return s1;
		}
		static SPROUT_CXX14_CONSTEXPR char_type* copy(char_type* s1, char_type const* s2, std::size_t n) {
			sprout::copy(s2, s2 + n, s1);
			return s1;
		}
		static SPROUT_CXX14_CONSTEXPR char_type* assign(char_type* s, std::size_t n, char_type a) {
			sprout::fill(s, s + n, a);
			return s;
		}
#ifdef SPROUT_NO_CXX11_CHAR_TRAITS
		static SPROUT_CONSTEXPR int_type not_eof(int_type c) SPROUT_NOEXCEPT {
			return eq_int_type(c, eof()) ? int_type()
				: c
				;
		}
		static SPROUT_CONSTEXPR char_type to_char_type(int_type c) SPROUT_NOEXCEPT {
			return static_cast<char_type>(c);
		}
		static SPROUT_CONSTEXPR int_type to_int_type(char_type c) SPROUT_NOEXCEPT {
			return static_cast<int_type>(c);
		}
		static SPROUT_CONSTEXPR bool eq_int_type(int_type c1, int_type c2) SPROUT_NOEXCEPT {
			return c1 == c2;
		}
		static SPROUT_CONSTEXPR int_type eof() SPROUT_NOEXCEPT {
			return static_cast<int_type>(EOF);
		}
#else
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
#endif
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		template<typename ConstInputIterator>
		static SPROUT_CONSTEXPR int compare(char_type const* s1, ConstInputIterator s2, std::size_t n) {
			return sprout::tristate_lexicographical_compare(
				sprout::ptr_index(s1), sprout::ptr_index(s1, n), char_type(),
				s2, s2 + n, char_type(),
				sprout::detail::char_traits_lt<char_traits>()
				);
		}
		template<typename ConstInputIterator>
		static SPROUT_CONSTEXPR int compare(ConstInputIterator s1, char_type const* s2, std::size_t n) {
			return sprout::tristate_lexicographical_compare(
				s1, s1 + n, char_type(),
				sprout::ptr_index(s2), sprout::ptr_index(s2, n), char_type(),
				sprout::detail::char_traits_lt<char_traits>()
				);
		}
		template<typename ConstInputIterator1, typename ConstInputIterator2>
		static SPROUT_CONSTEXPR int compare(ConstInputIterator1 s1, ConstInputIterator2 s2, std::size_t n) {
			return sprout::tristate_lexicographical_compare(
				s1, s1 + n, char_type(),
				s2, s2 + n, char_type(),
				sprout::detail::char_traits_lt<char_traits>()
				);
		}
		template<typename ConstInputIterator>
		static SPROUT_CONSTEXPR std::size_t length(ConstInputIterator s) {
			return sprout::detail::strlen(s);
		}
		template<typename ConstInputIterator>
		static SPROUT_CONSTEXPR ConstInputIterator find(ConstInputIterator s, std::size_t n, char_type const& a) {
			return sprout::ptr_unindex(
				sprout::find_if(
					s, s + n,
					sprout::bind2nd(sprout::detail::char_traits_eq<char_traits>(), a)
					)
				);
		}
		template<typename OutputIterator, typename ConstInputIterator>
		static SPROUT_CXX14_CONSTEXPR OutputIterator move(OutputIterator s1, ConstInputIterator s2, std::size_t n) {
			sprout::copy_backward(s2, s2 + n, s1);
			return s1;
		}
		template<typename OutputIterator, typename ConstInputIterator>
		static SPROUT_CXX14_CONSTEXPR OutputIterator copy(OutputIterator s1, ConstInputIterator s2, std::size_t n) {
			sprout::copy(s2, s2 + n, s1);
			return s1;
		}
		template<typename OutputIterator>
		static SPROUT_CXX14_CONSTEXPR OutputIterator assign(OutputIterator s, std::size_t n, char_type a) {
			sprout::fill(s, s + n, a);
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
			return sprout::ptr_unindex(
				sprout::find_if(
					sprout::ptr_index(s), sprout::ptr_index(s, n),
					sprout::bind2nd(sprout::detail::char_traits_eq<traits_type>(), a)
					)
				);
		}
		static SPROUT_CONSTEXPR bool is_found(char_type const* found, char_type const* last) {
			return found != last;
		}
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
		template<typename ConstInputIterator>
		static SPROUT_CONSTEXPR std::size_t length(ConstInputIterator s, std::size_t n) {
			return sprout::detail::strlen(s, n);
		}
		template<typename ConstInputIterator>
		static SPROUT_CONSTEXPR ConstInputIterator find(ConstInputIterator s, std::size_t n, char_type const& a) {
			return sprout::find_if(
				s, s + n,
				sprout::bind2nd(sprout::detail::char_traits_eq<traits_type>(), a)
				);
		}
		template<typename ConstInputIterator>
		static SPROUT_CONSTEXPR bool is_found(ConstInputIterator found, ConstInputIterator last) {
			return found != last;
		}
#endif
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_CHAR_TRAITS_HPP
