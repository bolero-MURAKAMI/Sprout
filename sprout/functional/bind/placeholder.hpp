#ifndef SPROUT_FUNCTIONAL_BIND_PLACEHOLDER_HPP
#define SPROUT_FUNCTIONAL_BIND_PLACEHOLDER_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// placeholder
	//
	template<int N>
	struct placeholder {};
	template<>
	struct placeholder<-1> {
	public:
		template<int N2>
		SPROUT_CONSTEXPR operator sprout::placeholder<N2>() const {
			return sprout::placeholder<N2>();
		}
	};

	namespace placeholders {
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<1> _1 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<2> _2 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<3> _3 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<4> _4 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<5> _5 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<6> _6 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<7> _7 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<8> _8 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<9> _9 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<10> _10 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<11> _11 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<12> _12 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<13> _13 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<14> _14 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<15> _15 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<16> _16 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<17> _17 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<18> _18 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<19> _19 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<20> _20 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<21> _21 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<22> _22 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<23> _23 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<24> _24 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<25> _25 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<26> _26 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<27> _27 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<28> _28 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<29> _29 = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<30> _30 = {};

			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-1> _ = {};
		}	// anonymous-namespace
	}	// namespace placeholders
	using sprout::placeholders::_1;
	using sprout::placeholders::_2;
	using sprout::placeholders::_3;
	using sprout::placeholders::_4;
	using sprout::placeholders::_5;
	using sprout::placeholders::_6;
	using sprout::placeholders::_7;
	using sprout::placeholders::_8;
	using sprout::placeholders::_9;
	using sprout::placeholders::_10;
	using sprout::placeholders::_11;
	using sprout::placeholders::_12;
	using sprout::placeholders::_13;
	using sprout::placeholders::_14;
	using sprout::placeholders::_15;
	using sprout::placeholders::_16;
	using sprout::placeholders::_17;
	using sprout::placeholders::_18;
	using sprout::placeholders::_19;
	using sprout::placeholders::_20;
	using sprout::placeholders::_21;
	using sprout::placeholders::_2;
	using sprout::placeholders::_23;
	using sprout::placeholders::_24;
	using sprout::placeholders::_25;
	using sprout::placeholders::_26;
	using sprout::placeholders::_27;
	using sprout::placeholders::_28;
	using sprout::placeholders::_29;
	using sprout::placeholders::_30;

	using sprout::placeholders::_;

	//
	// is_placeholder
	//
	template<typename T>
	struct is_placeholder
		: public std::integral_constant<int, 0>
	{};
	template<typename T>
	struct is_placeholder<T const>
		: public sprout::is_placeholder<T>
	{};
	template<typename T>
	struct is_placeholder<T volatile>
		: public sprout::is_placeholder<T>
	{};
	template<typename T>
	struct is_placeholder<T const volatile>
		: public sprout::is_placeholder<T>
	{};
	template<int N>
	struct is_placeholder<sprout::placeholder<N> >
		: public std::integral_constant<int, N>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_BIND_PLACEHOLDER_HPP
