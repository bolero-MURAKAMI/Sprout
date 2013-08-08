/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_HASH_HASH_HPP
#define SPROUT_FUNCTIONAL_HASH_HASH_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>
#include <sprout/functional/hash/to_hash.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// hash
	//
	template<typename T = void>
	struct hash {
	public:
		typedef T argument_type;
		typedef std::size_t result_type;
	public:
		SPROUT_CONSTEXPR std::size_t operator()(T const& v) const {
			return sprout::to_hash(v);
		}
	};
	template<typename T>
	struct hash<T const>
		: public sprout::hash<T>
	{};
	template<typename T>
	struct hash<T volatile>
		: public sprout::hash<T>
	{};
	template<typename T>
	struct hash<T const volatile>
		: public sprout::hash<T>
	{};
	template<>
	struct hash<void> {
	public:
		typedef std::size_t result_type;
	public:
		template<typename T>
		SPROUT_CONSTEXPR std::size_t
		operator()(T&& v)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::to_hash(sprout::forward<T>(v))))
		{
			return sprout::to_hash(sprout::forward<T>(v));
		}
	};

#define SPROUT_HASH_SPECIALIZE(type) \
	template<> \
	struct hash<type> { \
	public: \
		typedef type argument_type; \
		typedef std::size_t result_type; \
	public: \
		SPROUT_CONSTEXPR std::size_t operator()(type v) const { \
			return sprout::to_hash(v); \
		} \
	}
#define SPROUT_HASH_SPECIALIZE_REF(type) \
	template<> \
	struct hash<type> { \
	public: \
		typedef type argument_type; \
		typedef std::size_t result_type; \
	public: \
		SPROUT_CONSTEXPR std::size_t operator()(type const& v) const { \
			return sprout::to_hash(v); \
		} \
	}

	SPROUT_HASH_SPECIALIZE(bool);
	SPROUT_HASH_SPECIALIZE(char);
	SPROUT_HASH_SPECIALIZE(signed char);
	SPROUT_HASH_SPECIALIZE(unsigned char);
	SPROUT_HASH_SPECIALIZE(char16_t);
	SPROUT_HASH_SPECIALIZE(char32_t);
	SPROUT_HASH_SPECIALIZE(wchar_t);
	SPROUT_HASH_SPECIALIZE(short);
	SPROUT_HASH_SPECIALIZE(unsigned short);
	SPROUT_HASH_SPECIALIZE(int);
	SPROUT_HASH_SPECIALIZE(unsigned int);
	SPROUT_HASH_SPECIALIZE(long);
	SPROUT_HASH_SPECIALIZE(unsigned long);
	SPROUT_HASH_SPECIALIZE(long long);
	SPROUT_HASH_SPECIALIZE(unsigned long long);

#undef SPROUT_HASH_SPECIALIZE
#undef SPROUT_HASH_SPECIALIZE_REF

	template<typename T>
	struct hash<T*> {
	public:
		typedef T* argument_type;
		typedef std::size_t result_type;
	public:
		std::size_t operator()(T* v) const {
			return sprout::to_hash(v);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HASH_HPP
