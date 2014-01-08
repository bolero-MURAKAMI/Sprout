/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UUID_RANDOM_GENERATOR_HPP
#define SPROUT_UUID_RANDOM_GENERATOR_HPP

#include <cstdint>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/uuid/uuid.hpp>
#include <sprout/random/default_random_engine.hpp>
#include <sprout/random/uniform_int_distribution.hpp>
#include <sprout/random/variate_generator.hpp>

namespace sprout {
	namespace uuids {
		//
		// basic_random_generator
		//
		template<typename UniformRandomNumberGenerator = sprout::random::default_random_engine>
		class basic_random_generator {
		public:
			typedef sprout::uuids::uuid result_type;
		private:
			typedef UniformRandomNumberGenerator engine_type;
			typedef sprout::random::uniform_int_distribution<std::uint32_t> distribution_type;
			typedef typename result_type::value_type value_type;
		private:
			distribution_type distribution_;
		private:
			SPROUT_CONSTEXPR result_type random_to_uuid_1(std::uint32_t v0, std::uint32_t v1, std::uint32_t v2, std::uint32_t v3) const {
				return result_type{{
					static_cast<value_type>((v0 >> 24) & 0xFF),
					static_cast<value_type>((v0 >> 16) & 0xFF),
					static_cast<value_type>((v0 >> 8) & 0xFF),
					static_cast<value_type>((v0) & 0xFF),
					static_cast<value_type>((v1 >> 24) & 0xFF),
					static_cast<value_type>((v1 >> 16) & 0xFF),
					static_cast<value_type>(((v1 >> 8) & 0x4F) | 0x40),
					static_cast<value_type>((v1) & 0xFF),
					static_cast<value_type>(((v2 >> 24) & 0xBF) | 0x80),
					static_cast<value_type>((v2 >> 16) & 0xFF),
					static_cast<value_type>((v2 >> 8) & 0xFF),
					static_cast<value_type>((v2) & 0xFF),
					static_cast<value_type>((v3 >> 24) & 0xFF),
					static_cast<value_type>((v3 >> 16) & 0xFF),
					static_cast<value_type>((v3 >> 8) & 0xFF),
					static_cast<value_type>((v3) & 0xFF)
					}};
			}
			template<typename Random, typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) == 3,
				result_type
			>::type random_to_uuid(Random const& rnd, Args... args) const {
				return random_to_uuid_1(args..., rnd.result());
			}
			template<typename Random, typename... Args>
			SPROUT_CONSTEXPR typename std::enable_if<
				sizeof...(Args) != 3,
				result_type
			>::type random_to_uuid(Random const& rnd, Args... args) const {
				return random_to_uuid(rnd(), args..., rnd.result());
			}
		public:
			SPROUT_CONSTEXPR basic_random_generator()
				: distribution_(sprout::numeric_limits<std::uint32_t>::min(), sprout::numeric_limits<std::uint32_t>::max())
			{}
			template<typename T>
			SPROUT_CONSTEXPR typename std::enable_if<
				std::is_integral<T>::value,
				result_type
			>::type
			operator()(T const& seed) const {
				return operator()(engine_type(seed));
			}
			template<typename Engine>
			SPROUT_CONSTEXPR typename std::enable_if<
				!std::is_integral<Engine>::value,
				result_type
			>::type
			operator()(Engine const& engine) const {
				return random_to_uuid(sprout::random::combine(engine, distribution_)());
			}
		};

		//
		// random_generator
		//
		typedef sprout::uuids::basic_random_generator<> random_generator;

		//
		// make_uuid4
		//
		template<typename T>
		SPROUT_CONSTEXPR typename std::enable_if<
			std::is_integral<T>::value,
			sprout::uuids::uuid
		>::type
		make_uuid4(T const& seed) {
			return sprout::uuids::random_generator()(seed);
		}
		template<typename Engine>
		SPROUT_CONSTEXPR typename std::enable_if<
			!std::is_integral<Engine>::value,
			sprout::uuids::uuid
		>::type
		make_uuid4(Engine const& engine) {
			return sprout::uuids::random_generator()(engine);
		}
	}	// namespace uuids
}	// namespace sprout

#endif	// #ifndef SPROUT_UUID_RANDOM_GENERATOR_HPP
