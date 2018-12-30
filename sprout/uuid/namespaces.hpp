/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UUID_NAMESPACES_HPP
#define SPROUT_UUID_NAMESPACES_HPP

#include <sprout/config.hpp>
#include <sprout/uuid/uuid.hpp>

namespace sprout {
	namespace uuids {
		//
		// namespace_dns_uuid
		//
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		namespace_dns_uuid() {
			return sprout::uuids::uuid{{
				0x6b, 0xa7, 0xb8, 0x10,
				0x9d, 0xad,
				0x11, 0xd1,
				0x80, 0xb4,
				0x00, 0xc0, 0x4f, 0xd4, 0x30, 0xc8
				}};
		}
		//
		// namespace_url_uuid
		//
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		namespace_url_uuid() {
			return sprout::uuids::uuid{{
				0x6b, 0xa7, 0xb8, 0x11,
				0x9d, 0xad,
				0x11, 0xd1,
				0x80, 0xb4,
				0x00, 0xc0, 0x4f, 0xd4, 0x30, 0xc8
				}};
		}
		//
		// namespace_oid_uuid
		//
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		namespace_oid_uuid() {
			return sprout::uuids::uuid{{
				0x6b, 0xa7, 0xb8, 0x12,
				0x9d, 0xad,
				0x11, 0xd1,
				0x80, 0xb4,
				0x00, 0xc0, 0x4f, 0xd4, 0x30, 0xc8
				}};
		}
		//
		// namespace_x500_uuid
		//
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		namespace_x500_uuid() {
			return sprout::uuids::uuid{{
				0x6b, 0xa7, 0xb8, 0x14,
				0x9d, 0xad,
				0x11, 0xd1,
				0x80, 0xb4,
				0x00, 0xc0, 0x4f, 0xd4, 0x30, 0xc8
				}};
		}
	}	// namespace uuids
}	// namespace sprout

#endif	// #ifndef SPROUT_UUID_NAMESPACES_HPP
