/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UUID_UDL_HPP
#define SPROUT_UUID_UDL_HPP

#include <sprout/config.hpp>
#include <sprout/uuid/uuid.hpp>

#if SPROUT_USE_USER_DEFINED_LITERALS

#include <cstddef>
#include <type_traits>
#include <sprout/string.hpp>
#include <sprout/uuid/string_generator.hpp>
#include <sprout/uuid/name_generator.hpp>
#include <sprout/ctype/functor.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/metafunctions.hpp>
#include <sprout/range/algorithm/equal.hpp>
#include <sprout/range/ptr_range.hpp>

namespace sprout {
	namespace uuids {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::basic_string<T, 3>
			dns_token();
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<char, 3>
			dns_token<char>() {
				return sprout::to_string("dns");
			}
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, 3>
			dns_token<wchar_t>() {
				return sprout::to_string(L"dns");
			}
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, 3>
			dns_token<char16_t>() {
				return sprout::to_string(u"dns");
			}
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, 3>
			dns_token<char32_t>() {
				return sprout::to_string(U"dns");
			}

			template<typename T>
			inline SPROUT_CONSTEXPR sprout::basic_string<T, 3>
			url_token();
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<char, 3>
			url_token<char>() {
				return sprout::to_string("url");
			}
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, 3>
			url_token<wchar_t>() {
				return sprout::to_string(L"url");
			}
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, 3>
			url_token<char16_t>() {
				return sprout::to_string(u"url");
			}
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, 3>
			url_token<char32_t>() {
				return sprout::to_string(U"url");
			}

			template<typename T>
			inline SPROUT_CONSTEXPR sprout::basic_string<T, 3>
			oid_token();
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<char, 3>
			oid_token<char>() {
				return sprout::to_string("oid");
			}
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, 3>
			oid_token<wchar_t>() {
				return sprout::to_string(L"oid");
			}
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, 3>
			oid_token<char16_t>() {
				return sprout::to_string(u"oid");
			}
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, 3>
			oid_token<char32_t>() {
				return sprout::to_string(U"oid");
			}

			template<typename T>
			inline SPROUT_CONSTEXPR sprout::basic_string<T, 4>
			x500_token();
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<char, 4>
			x500_token<char>() {
				return sprout::to_string("x500");
			}
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<wchar_t, 4>
			x500_token<wchar_t>() {
				return sprout::to_string(L"x500");
			}
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<char16_t, 4>
			x500_token<char16_t>() {
				return sprout::to_string(u"x500");
			}
			template<>
			inline SPROUT_CONSTEXPR sprout::basic_string<char32_t, 4>
			x500_token<char32_t>() {
				return sprout::to_string(U"x500");
			}

			template<typename InputRange>
			inline SPROUT_CONSTEXPR sprout::uuids::md5_name_generator
			uuid3_impl(InputRange const& rng) {
				typedef typename std::decay<typename sprout::containers::value_type<InputRange>::type>::type value_type;
				typedef sprout::ctypes::nocase_equal_to<value_type> predicate_type;
				return sprout::range::equal(rng, sprout::uuids::detail::dns_token<value_type>(), predicate_type()) ? sprout::uuids::make_uuid3_dns()
					: sprout::range::equal(rng, sprout::uuids::detail::url_token<value_type>(), predicate_type()) ? sprout::uuids::make_uuid3_url()
					: sprout::range::equal(rng, sprout::uuids::detail::oid_token<value_type>(), predicate_type()) ? sprout::uuids::make_uuid3_oid()
					: sprout::range::equal(rng, sprout::uuids::detail::x500_token<value_type>(), predicate_type()) ? sprout::uuids::make_uuid3_x500()
					: sprout::uuids::make_uuid3(sprout::uuids::make_uuid(sprout::begin(rng), sprout::end(rng)))
					;
			}

			template<typename InputRange>
			inline SPROUT_CONSTEXPR sprout::uuids::sha1_name_generator
			uuid5_impl(InputRange const& rng) {
				typedef typename std::decay<typename sprout::containers::value_type<InputRange>::type>::type value_type;
				typedef sprout::ctypes::nocase_equal_to<value_type> predicate_type;
				return sprout::range::equal(rng, sprout::uuids::detail::dns_token<value_type>(), predicate_type()) ? sprout::uuids::make_uuid5_dns()
					: sprout::range::equal(rng, sprout::uuids::detail::url_token<value_type>(), predicate_type()) ? sprout::uuids::make_uuid5_url()
					: sprout::range::equal(rng, sprout::uuids::detail::oid_token<value_type>(), predicate_type()) ? sprout::uuids::make_uuid5_oid()
					: sprout::range::equal(rng, sprout::uuids::detail::x500_token<value_type>(), predicate_type()) ? sprout::uuids::make_uuid5_x500()
					: sprout::uuids::make_uuid5(sprout::uuids::make_uuid(sprout::begin(rng), sprout::end(rng)))
					;
			}
		}	// namespace detail

		namespace udl {
			//
			// _uuid
			//
			inline SPROUT_CONSTEXPR sprout::uuids::uuid
			operator"" _uuid(char const* s, std::size_t size) {
				return sprout::uuids::make_uuid(s, s + size);
			}
			inline SPROUT_CONSTEXPR sprout::uuids::uuid
			operator"" _uuid(wchar_t const* s, std::size_t size) {
				return sprout::uuids::make_uuid(s, s + size);
			}
			inline SPROUT_CONSTEXPR sprout::uuids::uuid
			operator"" _uuid(char16_t const* s, std::size_t size) {
				return sprout::uuids::make_uuid(s, s + size);
			}
			inline SPROUT_CONSTEXPR sprout::uuids::uuid
			operator"" _uuid(char32_t const* s, std::size_t size) {
				return sprout::uuids::make_uuid(s, s + size);
			}

			//
			// _uuid3
			//
			inline SPROUT_CONSTEXPR sprout::uuids::md5_name_generator
			operator"" _uuid3(char const* s, std::size_t size) {
				return sprout::uuids::detail::uuid3_impl(sprout::range::make_ptr_range(s, size));
			}
			inline SPROUT_CONSTEXPR sprout::uuids::md5_name_generator
			operator"" _uuid3(wchar_t const* s, std::size_t size) {
				return sprout::uuids::detail::uuid3_impl(sprout::range::make_ptr_range(s, size));
			}
			inline SPROUT_CONSTEXPR sprout::uuids::md5_name_generator
			operator"" _uuid3(char16_t const* s, std::size_t size) {
				return sprout::uuids::detail::uuid3_impl(sprout::range::make_ptr_range(s, size));
			}
			inline SPROUT_CONSTEXPR sprout::uuids::md5_name_generator
			operator"" _uuid3(char32_t const* s, std::size_t size) {
				return sprout::uuids::detail::uuid3_impl(sprout::range::make_ptr_range(s, size));
			}

			//
			// _uuid5
			//
			inline SPROUT_CONSTEXPR sprout::uuids::sha1_name_generator
			operator"" _uuid5(char const* s, std::size_t size) {
				return sprout::uuids::detail::uuid5_impl(sprout::range::make_ptr_range(s, size));
			}
			inline SPROUT_CONSTEXPR sprout::uuids::sha1_name_generator
			operator"" _uuid5(wchar_t const* s, std::size_t size) {
				return sprout::uuids::detail::uuid5_impl(sprout::range::make_ptr_range(s, size));
			}
			inline SPROUT_CONSTEXPR sprout::uuids::sha1_name_generator
			operator"" _uuid5(char16_t const* s, std::size_t size) {
				return sprout::uuids::detail::uuid5_impl(sprout::range::make_ptr_range(s, size));
			}
			inline SPROUT_CONSTEXPR sprout::uuids::sha1_name_generator
			operator"" _uuid5(char32_t const* s, std::size_t size) {
				return sprout::uuids::detail::uuid5_impl(sprout::range::make_ptr_range(s, size));
			}
		}	// namespace udl

		using sprout::uuids::udl::operator"" _uuid;
		using sprout::uuids::udl::operator"" _uuid3;
		using sprout::uuids::udl::operator"" _uuid5;
	}	// namespace uuids

	namespace udl {
		namespace uuids {
			using sprout::uuids::udl::operator"" _uuid;
			using sprout::uuids::udl::operator"" _uuid3;
			using sprout::uuids::udl::operator"" _uuid5;
		}	// namespace uuids

		using sprout::uuids::udl::operator"" _uuid;
		using sprout::uuids::udl::operator"" _uuid3;
		using sprout::uuids::udl::operator"" _uuid5;
	}	// namespace udl

	using sprout::uuids::udl::operator"" _uuid;
	using sprout::uuids::udl::operator"" _uuid3;
	using sprout::uuids::udl::operator"" _uuid5;
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_UUID_UDL_HPP
