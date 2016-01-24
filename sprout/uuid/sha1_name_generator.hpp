/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UUID_SHA1_NAME_GENERATOR_HPP
#define SPROUT_UUID_SHA1_NAME_GENERATOR_HPP

#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/uuid/uuid.hpp>
#include <sprout/uuid/namespaces.hpp>
#include <sprout/checksum/sha1.hpp>

namespace sprout {
	namespace uuids {
		//
		// sha1_name_generator
		//
		class sha1_name_generator {
		public:
			typedef sprout::uuids::uuid result_type;
		private:
			typedef result_type::value_type value_type;
		private:
			sprout::sha1 sum_;
		private:
			SPROUT_CONSTEXPR result_type sha_to_uuid_1(sprout::sha1::value_type const& value) const {
				return result_type{{
					value[0],
					value[1],
					value[2],
					value[3],
					value[4],
					value[5],
					static_cast<value_type>((value[6] & 0x5F) | 0x50),
					value[7],
					static_cast<value_type>((value[8] & 0xBF) | 0x80),
					value[9],
					value[10],
					value[11],
					value[12],
					value[13],
					value[14],
					value[15]
					}};
			}
			SPROUT_CONSTEXPR result_type sha_to_uuid(sprout::sha1 const& sha) const {
				return sha_to_uuid_1(sha.checksum());
			}
		public:
			SPROUT_CONSTEXPR sha1_name_generator()
				: sum_(sprout::sha1().c_process_range(sprout::uuids::uuid{{0}}))
			{}
			explicit SPROUT_CONSTEXPR sha1_name_generator(sprout::uuids::uuid const& namespace_uuid)
				: sum_(sprout::sha1().c_process_range(namespace_uuid))
			{}
			template<typename Elem, std::size_t N, typename Traits>
			SPROUT_CONSTEXPR result_type operator()(sprout::basic_string<Elem, N, Traits> const& name) const {
				return sha_to_uuid(sum_.c_process_range(name));
			}
			SPROUT_CONSTEXPR result_type operator()(char const* name) const {
				return sha_to_uuid(sum_.c_process_bytes(name, sprout::char_traits<char>::length(name)));
			}
			SPROUT_CONSTEXPR result_type operator()(wchar_t const* name) const {
				return sha_to_uuid(sum_.c_process_bytes(name, sprout::char_traits<wchar_t>::length(name)));
			}
			SPROUT_CONSTEXPR result_type operator()(char16_t const* name) const {
				return sha_to_uuid(sum_.c_process_bytes(name, sprout::char_traits<char16_t>::length(name)));
			}
			SPROUT_CONSTEXPR result_type operator()(char32_t const* name) const {
				return sha_to_uuid(sum_.c_process_bytes(name, sprout::char_traits<char32_t>::length(name)));
			}
		};

		//
		// make_uuid5
		//
		template<typename Elem, std::size_t N, typename Traits>
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid5(sprout::basic_string<Elem, N, Traits> const& name) {
			return sprout::uuids::sha1_name_generator()(name);
		}
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid5(char const* name) {
			return sprout::uuids::sha1_name_generator()(name);
		}
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid5(wchar_t const* name) {
			return sprout::uuids::sha1_name_generator()(name);
		}
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid5(char16_t const* name) {
			return sprout::uuids::sha1_name_generator()(name);
		}
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid5(char32_t const* name) {
			return sprout::uuids::sha1_name_generator()(name);
		}

		template<typename Elem, std::size_t N, typename Traits>
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid5(sprout::uuids::uuid const& namespace_uuid, sprout::basic_string<Elem, N, Traits> const& name) {
			return sprout::uuids::sha1_name_generator(namespace_uuid)(name);
		}
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid5(sprout::uuids::uuid const& namespace_uuid, char const* name) {
			return sprout::uuids::sha1_name_generator(namespace_uuid)(name);
		}
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid5(sprout::uuids::uuid const& namespace_uuid, wchar_t const* name) {
			return sprout::uuids::sha1_name_generator(namespace_uuid)(name);
		}
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid5(sprout::uuids::uuid const& namespace_uuid, char16_t const* name) {
			return sprout::uuids::sha1_name_generator(namespace_uuid)(name);
		}
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		make_uuid5(sprout::uuids::uuid const& namespace_uuid, char32_t const* name) {
			return sprout::uuids::sha1_name_generator(namespace_uuid)(name);
		}

		inline SPROUT_CONSTEXPR sprout::uuids::sha1_name_generator
		make_uuid5() {
			return sprout::uuids::sha1_name_generator();
		}
		inline SPROUT_CONSTEXPR sprout::uuids::sha1_name_generator
		make_uuid5(sprout::uuids::uuid const& namespace_uuid) {
			return sprout::uuids::sha1_name_generator(namespace_uuid);
		}

		//
		// make_uuid5_dns
		// make_uuid5_url
		// make_uuid5_oid
		// make_uuid5_x500
		//
		inline SPROUT_CONSTEXPR sprout::uuids::sha1_name_generator
		make_uuid5_dns() {
			return sprout::uuids::sha1_name_generator(sprout::uuids::namespace_dns_uuid());
		}
		inline SPROUT_CONSTEXPR sprout::uuids::sha1_name_generator
		make_uuid5_url() {
			return sprout::uuids::sha1_name_generator(sprout::uuids::namespace_url_uuid());
		}
		inline SPROUT_CONSTEXPR sprout::uuids::sha1_name_generator
		make_uuid5_oid() {
			return sprout::uuids::sha1_name_generator(sprout::uuids::namespace_oid_uuid());
		}
		inline SPROUT_CONSTEXPR sprout::uuids::sha1_name_generator
		make_uuid5_x500() {
			return sprout::uuids::sha1_name_generator(sprout::uuids::namespace_x500_uuid());
		}
	}	// namespace uuids
}	// namespace sprout

#endif	// #ifndef SPROUT_UUID_SHA1_NAME_GENERATOR_HPP
