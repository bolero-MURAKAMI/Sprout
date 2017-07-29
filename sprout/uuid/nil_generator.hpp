/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UUID_NIL_GENERATOR_HPP
#define SPROUT_UUID_NIL_GENERATOR_HPP

#include <sprout/config.hpp>
#include <sprout/uuid/uuid.hpp>

namespace sprout {
	namespace uuids {
		//
		// nil_generator
		//
		class nil_generator {
		public:
			typedef sprout::uuids::uuid result_type;
		public:
			SPROUT_CONSTEXPR result_type operator()() const {
				return result_type{{0}};
			}
		};

		//
		// nil_uuid
		//
		inline SPROUT_CONSTEXPR sprout::uuids::uuid
		nil_uuid() {
			return sprout::uuids::nil_generator()();
		}
	}	// namespace uuids
}	// namespace sprout

#endif	// #ifndef SPROUT_UUID_NIL_GENERATOR_HPP
