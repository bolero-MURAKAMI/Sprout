#ifndef SPROUT_FUNCTIONAL_BIND_PLACEHOLDER_HPP
#define SPROUT_FUNCTIONAL_BIND_PLACEHOLDER_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// placeholder
	//
	template<int N>
	struct placeholder
//		: public std::integral_constant<int, N>
	{};
	template<>
	struct placeholder<-1>
//		: public std::integral_constant<int, -1>
	{
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

			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256> _va = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 1> _1tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 2> _2tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 3> _3tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 4> _4tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 5> _5tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 6> _6tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 7> _7tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 8> _8tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 9> _9tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 10> _10tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 11> _11tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 12> _12tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 13> _13tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 14> _14tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 15> _15tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 16> _16tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 17> _17tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 18> _18tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 19> _19tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 20> _20tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 21> _21tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 22> _22tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 23> _23tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 24> _24tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 25> _25tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 26> _26tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 27> _27tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 28> _28tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 29> _29tail = {};
			SPROUT_STATIC_CONSTEXPR sprout::placeholder<-256 - 30> _30tail = {};
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
	using sprout::placeholders::_22;
	using sprout::placeholders::_23;
	using sprout::placeholders::_24;
	using sprout::placeholders::_25;
	using sprout::placeholders::_26;
	using sprout::placeholders::_27;
	using sprout::placeholders::_28;
	using sprout::placeholders::_29;
	using sprout::placeholders::_30;

	using sprout::placeholders::_;

	using sprout::placeholders::_va;
	using sprout::placeholders::_1tail;
	using sprout::placeholders::_2tail;
	using sprout::placeholders::_3tail;
	using sprout::placeholders::_4tail;
	using sprout::placeholders::_5tail;
	using sprout::placeholders::_6tail;
	using sprout::placeholders::_7tail;
	using sprout::placeholders::_8tail;
	using sprout::placeholders::_9tail;
	using sprout::placeholders::_10tail;
	using sprout::placeholders::_11tail;
	using sprout::placeholders::_12tail;
	using sprout::placeholders::_13tail;
	using sprout::placeholders::_14tail;
	using sprout::placeholders::_15tail;
	using sprout::placeholders::_16tail;
	using sprout::placeholders::_17tail;
	using sprout::placeholders::_18tail;
	using sprout::placeholders::_19tail;
	using sprout::placeholders::_20tail;
	using sprout::placeholders::_21tail;
	using sprout::placeholders::_22tail;
	using sprout::placeholders::_23tail;
	using sprout::placeholders::_24tail;
	using sprout::placeholders::_25tail;
	using sprout::placeholders::_26tail;
	using sprout::placeholders::_27tail;
	using sprout::placeholders::_28tail;
	using sprout::placeholders::_29tail;
	using sprout::placeholders::_30tail;

	//
	// is_placeholder
	//
	template<typename T>
	struct is_placeholder
		: public std::integral_constant<int, 0>
	{};
	template<int N>
	struct is_placeholder<sprout::placeholder<N> >
		: public std::integral_constant<int, N>
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
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_BIND_PLACEHOLDER_HPP
