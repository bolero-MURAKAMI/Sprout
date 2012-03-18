#ifndef SPROUT_UUID_UDL_HPP
#define SPROUT_UUID_UDL_HPP

#include <sprout/config.hpp>
#include <sprout/uuid/uuid.hpp>

#if SPROUT_USE_USER_DEFINED_LITERALS

#include <cstddef>
#include <sprout/uuid/string_generator.hpp>

namespace sprout {
	namespace uuids {
		namespace udl {
			//
			// _uuid
			//
			SPROUT_CONSTEXPR sprout::uuids::uuid operator "" _uuid(char const* s, std::size_t) {
				return sprout::uuids::string_generator()(s);
			}
			SPROUT_CONSTEXPR sprout::uuids::uuid operator "" _uuid(wchar_t const* s, std::size_t) {
				return sprout::uuids::string_generator()(s);
			}
			SPROUT_CONSTEXPR sprout::uuids::uuid operator "" _uuid(char16_t const* s, std::size_t) {
				return sprout::uuids::string_generator()(s);
			}
			SPROUT_CONSTEXPR sprout::uuids::uuid operator "" _uuid(char32_t const* s, std::size_t) {
				return sprout::uuids::string_generator()(s);
			}
		}	// namespace uuids

		using sprout::uuids::udl::operator "" _uuid;
	}	// namespace udl

	using sprout::uuids::udl::operator "" _uuid;
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_UUID_UDL_HPP
