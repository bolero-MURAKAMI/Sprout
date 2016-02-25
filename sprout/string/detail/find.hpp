/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STRING_DETAIL_FIND_HPP
#define SPROUT_STRING_DETAIL_FIND_HPP

#include <sprout/config.hpp>
#include <sprout/string/char_traits.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace string_detail {
		template<typename String, typename ConstIterator>
		static SPROUT_CONSTEXPR typename String::size_type
		find_impl_1(
			typename String::const_iterator data, typename String::size_type len,
			ConstIterator s, typename String::size_type pos, typename String::size_type n
			)
		{
			return pos <= len - n
				? String::traits_type::eq(data[pos], *s) && String::traits_type::compare(data + (pos + 1), s + 1, n - 1) == 0
					? pos
					: sprout::string_detail::find_impl_1<String>(data, len, s, pos + 1, n)
				: String::npos
				;
		}
		template<typename String, typename ConstIterator>
		static SPROUT_CONSTEXPR typename String::size_type
		find_impl(
			typename String::const_iterator data, typename String::size_type len,
			ConstIterator s, typename String::size_type pos, typename String::size_type n
			)
		{
			return n == 0 ? (pos <= len ? pos : String::npos)
				: n <= len ? sprout::string_detail::find_impl_1<String>(data, len, s, pos, n)
				: String::npos
				;
		}
		template<typename String>
		static SPROUT_CONSTEXPR typename String::size_type
		find_c_impl_1(
			typename String::const_iterator data, typename String::size_type len,
			typename String::const_iterator p
			)
		{
			return sprout::char_traits_helper<typename String::traits_type>::is_found(p, data + len) ? p - data
				: String::npos
				;
		}
		template<typename String>
		static SPROUT_CONSTEXPR typename String::size_type
		find_c_impl(
			typename String::const_iterator data, typename String::size_type len,
			typename String::value_type c, typename String::size_type pos
			)
		{
			return pos < len ? sprout::string_detail::find_c_impl_1<String>(
					data, len, sprout::char_traits_helper<typename String::traits_type>::find(data + pos, len - pos, c)
					)
				: String::npos
				;
		}
		template<typename String, typename ConstIterator>
		static SPROUT_CONSTEXPR typename String::size_type
		rfind_impl_1(
			typename String::const_iterator data, typename String::size_type len,
			ConstIterator s, typename String::size_type pos, typename String::size_type n
			)
		{
			return String::traits_type::compare(data + pos, s, n) == 0 ? pos
				: pos > 0 ? sprout::string_detail::rfind_impl_1<String>(data, len, s, pos - 1, n)
				: String::npos
				;
		}
		template<typename String, typename ConstIterator>
		static SPROUT_CONSTEXPR typename String::size_type
		rfind_impl(
			typename String::const_iterator data, typename String::size_type len,
			ConstIterator s, typename String::size_type pos, typename String::size_type n
			)
		{
			return n <= len ? sprout::string_detail::rfind_impl_1<String>(
					data, len, s, NS_SSCRISK_CEL_OR_SPROUT::min(typename String::size_type(len - n), pos), n
					)
				: String::npos
				;
		}
		template<typename String>
		static SPROUT_CONSTEXPR typename String::size_type
		rfind_c_impl_1(
			typename String::const_iterator data, typename String::size_type len, typename String::value_type c
			)
		{
			return len > 0
				? String::traits_type::eq(data[len - 1], c)
					? len - 1
					: sprout::string_detail::rfind_c_impl_1<String>(data, len - 1, c)
				: String::npos
				;
		}

		template<typename String>
		static SPROUT_CONSTEXPR typename String::size_type
		rfind_c_impl(
			typename String::const_iterator data, typename String::size_type len,
			typename String::value_type c, typename String::size_type pos
			)
		{
			return len ? sprout::string_detail::rfind_c_impl_1<String>(data, len - 1 > pos ? pos + 1 : len, c)
				: String::npos
				;
		}
		template<typename String, typename ConstIterator>
		static SPROUT_CONSTEXPR typename String::size_type
		find_first_of_impl(
			typename String::const_iterator data, typename String::size_type len,
			ConstIterator s, typename String::size_type pos, typename String::size_type n
			)
		{
			return n && pos < len
				? sprout::char_traits_helper<typename String::traits_type>::is_found(
					sprout::char_traits_helper<typename String::traits_type>::find(s, n, data[pos]), s + n
					)
					? pos
					: sprout::string_detail::find_first_of_impl<String>(data, len, s, pos + 1, n)
				: String::npos
				;
		}
		template<typename String, typename ConstIterator>
		static SPROUT_CONSTEXPR typename String::size_type
		find_last_of_impl_1(
			typename String::const_iterator data, typename String::size_type len,
			ConstIterator s, typename String::size_type pos, typename String::size_type n
			)
		{
			return sprout::char_traits_helper<typename String::traits_type>::is_found(
					sprout::char_traits_helper<typename String::traits_type>::find(s, n, data[len]), s + n
					) ? len
				: len ? sprout::string_detail::find_last_of_impl_1<String>(data, len - 1, s, pos, n)
				: String::npos
				;
		}
		template<typename String, typename ConstIterator>
		static SPROUT_CONSTEXPR typename String::size_type
		find_last_of_impl(
			typename String::const_iterator data, typename String::size_type len,
			ConstIterator s, typename String::size_type pos, typename String::size_type n
			)
		{
			return len && n ? sprout::string_detail::find_last_of_impl_1<String>(data, len - 1 > pos ? pos : len - 1, s, pos, n)
				: String::npos
				;
		}
		template<typename String, typename ConstIterator>
		static SPROUT_CONSTEXPR typename String::size_type
		find_first_not_of_impl(
			typename String::const_iterator data, typename String::size_type len,
			ConstIterator s, typename String::size_type pos, typename String::size_type n
			)
		{
			return pos < len
				? !sprout::char_traits_helper<typename String::traits_type>::is_found(
					sprout::char_traits_helper<typename String::traits_type>::find(s, n, data[pos]), s + n
					)
					? pos
					: sprout::string_detail::find_first_not_of_impl<String>(data, len, s, pos + 1, n)
				: String::npos
				;
		}
		template<typename String>
		static SPROUT_CONSTEXPR typename String::size_type
		find_first_not_of_c_impl(
			typename String::const_iterator data, typename String::size_type len,
			typename String::value_type c, typename String::size_type pos
			)
		{
			return pos < len ? !String::traits_type::eq(data[pos], c)
					? pos
					: sprout::string_detail::find_first_not_of_c_impl<String>(data, len, c, pos + 1)
				: String::npos
				;
		}
		template<typename String, typename ConstIterator>
		static SPROUT_CONSTEXPR typename String::size_type
		find_last_not_of_impl_1(
			typename String::const_iterator data, typename String::size_type len,
			ConstIterator s, typename String::size_type pos, typename String::size_type n
			)
		{
			return !sprout::char_traits_helper<typename String::traits_type>::is_found(
					sprout::char_traits_helper<typename String::traits_type>::find(s, n, data[len]), s + n
					) ? len
				: len ? sprout::string_detail::find_last_not_of_impl_1<String>(data, len - 1, s, pos, n)
				: String::npos
				;
		}
		template<typename String, typename ConstIterator>
		static SPROUT_CONSTEXPR typename String::size_type
		find_last_not_of_impl(
			typename String::const_iterator data, typename String::size_type len,
			ConstIterator s, typename String::size_type pos, typename String::size_type n
			)
		{
			return len ? sprout::string_detail::find_last_not_of_impl_1<String>(data, len - 1 > pos ? pos : len - 1, s, pos, n)
				: String::npos
				;
		}
		template<typename String>
		static SPROUT_CONSTEXPR typename String::size_type
		find_last_not_of_c_impl_1(
			typename String::const_iterator data, typename String::size_type len,
			typename String::value_type c, typename String::size_type pos
			)
		{
			return !String::traits_type::eq(data[len], c) ? len
				: len ? sprout::string_detail::find_last_not_of_c_impl_1<String>(data, len - 1, c, pos)
				: String::npos
				;
		}
		template<typename String>
		static SPROUT_CONSTEXPR typename String::size_type
		find_last_not_of_c_impl(
			typename String::const_iterator data, typename String::size_type len,
			typename String::value_type c, typename String::size_type pos
			)
		{
			return len ? sprout::string_detail::find_last_not_of_c_impl_1<String>(data, len - 1 > pos ? pos : len - 1, c, pos)
				: String::npos
				;
		}
	}	// namespace string_detail
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_DETAIL_FIND_HPP
