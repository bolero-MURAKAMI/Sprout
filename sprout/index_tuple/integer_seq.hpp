#ifndef SPROUT_INDEX_TUPLE_INTEGER_SEQ_HPP
#define SPROUT_INDEX_TUPLE_INTEGER_SEQ_HPP

#include <cstddef>
#include <sprout/config.hpp>

namespace sprout {
	//
	// integer_seq
	//
	template<typename T, T... Is>
	struct integer_seq {
	public:
		typedef integer_seq type;
		template<T... J>
		struct rebind
			: public integer_seq<T, J...>
		{};
	public:
		typedef T value_type;
		template<typename Seq>
		struct transfer
			: public Seq::template rebind<Is...>
		{};
	public:
		SPROUT_STATIC_CONSTEXPR std::size_t size = sizeof...(Is);
	};
	template<typename T, T... Is>
	SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::integer_seq<T, Is...>::size;
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INTEGER_SEQ_HPP
