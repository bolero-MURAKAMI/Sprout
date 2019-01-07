/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UUID_LITERALS_HPP
#define SPROUT_UUID_LITERALS_HPP

#include <sprout/config.hpp>
#include <sprout/uuid/uuid.hpp>
#include <sprout/detail/udl_namespace.hpp>

#if SPROUT_USE_USER_DEFINED_LITERALS

#include <type_traits>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/string.hpp>
#include <sprout/uuid/string_generator.hpp>
#include <sprout/uuid/name_generator.hpp>
#include <sprout/ctype/functor.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/metafunctions.hpp>
#include <sprout/range/algorithm/equal.hpp>
#include <sprout/range/ptr_range.hpp>
#include <sprout/detail/literal_def.hpp>

namespace sprout {
	namespace uuids {
		namespace detail {
			SPROUT_LITERAL_STRING_DEF(dns_token, "dns", 3);
			SPROUT_LITERAL_STRING_DEF(url_token, "url", 3);
			SPROUT_LITERAL_STRING_DEF(oid_token, "oid", 3);
			SPROUT_LITERAL_STRING_DEF(x500_token, "x500", 4);

			template<typename InputRange>
			inline SPROUT_CONSTEXPR sprout::uuids::md5_name_generator
			uuid3_impl(InputRange const& rng) {
				typedef typename std::decay<typename sprout::containers::value_type<InputRange>::type>::type value_type;
				typedef sprout::ctypes::nocase_equal_to<value_type> predicate_type;
				return sprout::range::equal(rng, sprout::uuids::detail::dns_token<value_type>::value, predicate_type()) ? sprout::uuids::make_uuid3_dns()
					: sprout::range::equal(rng, sprout::uuids::detail::url_token<value_type>::value, predicate_type()) ? sprout::uuids::make_uuid3_url()
					: sprout::range::equal(rng, sprout::uuids::detail::oid_token<value_type>::value, predicate_type()) ? sprout::uuids::make_uuid3_oid()
					: sprout::range::equal(rng, sprout::uuids::detail::x500_token<value_type>::value, predicate_type()) ? sprout::uuids::make_uuid3_x500()
					: sprout::uuids::make_uuid3(sprout::uuids::make_uuid(sprout::begin(rng), sprout::end(rng)))
					;
			}

			template<typename InputRange>
			inline SPROUT_CONSTEXPR sprout::uuids::sha1_name_generator
			uuid5_impl(InputRange const& rng) {
				typedef typename std::decay<typename sprout::containers::value_type<InputRange>::type>::type value_type;
				typedef sprout::ctypes::nocase_equal_to<value_type> predicate_type;
				return sprout::range::equal(rng, sprout::uuids::detail::dns_token<value_type>::value, predicate_type()) ? sprout::uuids::make_uuid5_dns()
					: sprout::range::equal(rng, sprout::uuids::detail::url_token<value_type>::value, predicate_type()) ? sprout::uuids::make_uuid5_url()
					: sprout::range::equal(rng, sprout::uuids::detail::oid_token<value_type>::value, predicate_type()) ? sprout::uuids::make_uuid5_oid()
					: sprout::range::equal(rng, sprout::uuids::detail::x500_token<value_type>::value, predicate_type()) ? sprout::uuids::make_uuid5_x500()
					: sprout::uuids::make_uuid5(sprout::uuids::make_uuid(sprout::begin(rng), sprout::end(rng)))
					;
			}
		}	// namespace detail
	}	// namespace uuids

	namespace literals {
		namespace uuids {
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
#if SPROUT_USE_UNICODE_LITERALS
			inline SPROUT_CONSTEXPR sprout::uuids::uuid
			operator"" _uuid(char16_t const* s, std::size_t size) {
				return sprout::uuids::make_uuid(s, s + size);
			}
			inline SPROUT_CONSTEXPR sprout::uuids::uuid
			operator"" _uuid(char32_t const* s, std::size_t size) {
				return sprout::uuids::make_uuid(s, s + size);
			}
#endif

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
#if SPROUT_USE_UNICODE_LITERALS
			inline SPROUT_CONSTEXPR sprout::uuids::md5_name_generator
			operator"" _uuid3(char16_t const* s, std::size_t size) {
				return sprout::uuids::detail::uuid3_impl(sprout::range::make_ptr_range(s, size));
			}
			inline SPROUT_CONSTEXPR sprout::uuids::md5_name_generator
			operator"" _uuid3(char32_t const* s, std::size_t size) {
				return sprout::uuids::detail::uuid3_impl(sprout::range::make_ptr_range(s, size));
			}
#endif

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
#if SPROUT_USE_UNICODE_LITERALS
			inline SPROUT_CONSTEXPR sprout::uuids::sha1_name_generator
			operator"" _uuid5(char16_t const* s, std::size_t size) {
				return sprout::uuids::detail::uuid5_impl(sprout::range::make_ptr_range(s, size));
			}
			inline SPROUT_CONSTEXPR sprout::uuids::sha1_name_generator
			operator"" _uuid5(char32_t const* s, std::size_t size) {
				return sprout::uuids::detail::uuid5_impl(sprout::range::make_ptr_range(s, size));
			}
#endif
		}	// namespace uuids

		using sprout::literals::uuids::operator"" _uuid;
		using sprout::literals::uuids::operator"" _uuid3;
		using sprout::literals::uuids::operator"" _uuid5;
	}	// namespace literals

	using sprout::literals::uuids::operator"" _uuid;
	using sprout::literals::uuids::operator"" _uuid3;
	using sprout::literals::uuids::operator"" _uuid5;
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_UUID_LITERALS_HPP
