#ifndef SPROUT_UUID_NAME_GENERATOR_HPP
#define SPROUT_UUID_NAME_GENERATOR_HPP

#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/uuid/uuid.hpp>
#include <sprout/checksum/sha1.hpp>

namespace sprout {
	namespace uuids {
		//
		// name_generator
		//
		class name_generator {
		public:
			typedef sprout::uuids::uuid result_type;
		private:
			typedef sprout::sha1 const sha1_const_type;
			typedef typename result_type::value_type value_type;
		private:
			sprout::sha1 sha_;
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
			SPROUT_CONSTEXPR name_generator()
				: sha_(sha1_const_type().process_range(sprout::uuids::uuid{{0}}))
			{}
			explicit SPROUT_CONSTEXPR name_generator(sprout::uuids::uuid const& namespace_uuid)
				: sha_(sha1_const_type().process_range(namespace_uuid))
			{}
			template<typename Elem, std::size_t N, typename Traits>
			SPROUT_CONSTEXPR result_type operator()(sprout::basic_string<Elem, N, Traits> const& name) const {
				return sha_to_uuid(sha_.process_range(name));
			}
			SPROUT_CONSTEXPR result_type operator()(char const* name) const {
				return sha_to_uuid(sha_.process_bytes(name, sprout::char_traits<char>::length(name)));
			}
			SPROUT_CONSTEXPR result_type operator()(wchar_t const* name) const {
				return sha_to_uuid(sha_.process_bytes(name, sprout::char_traits<wchar_t>::length(name)));
			}
			SPROUT_CONSTEXPR result_type operator()(char16_t const* name) const {
				return sha_to_uuid(sha_.process_bytes(name, sprout::char_traits<char16_t>::length(name)));
			}
			SPROUT_CONSTEXPR result_type operator()(char32_t const* name) const {
				return sha_to_uuid(sha_.process_bytes(name, sprout::char_traits<char32_t>::length(name)));
			}
		};
	}	// namespace uuids
}	// namespace sprout

#endif	// #ifndef SPROUT_UUID_NAME_GENERATOR_HPP
