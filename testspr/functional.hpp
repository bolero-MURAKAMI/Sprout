#ifndef TESTSPR_FUNCTIONAL_HPP
#define TESTSPR_FUNCTIONAL_HPP

#include <sprout/config.hpp>

namespace testspr {
	//
	// do_nothing
	//
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	do_nothing(T const&) SPROUT_NOEXCEPT {
		return true;
	}

	//
	// is_even
	//
	template<typename T>
	struct is_even {
	public:
		typedef T argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& t) const { return t % 2 == 0; }
	};
	//
	// is_odd
	//
	template<typename T>
	struct is_odd {
	public:
		typedef T argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& t) const { return t % 2 != 0; }
	};
	//
	// is_multiple_of
	//
	template<typename T, typename U = T>
	struct is_multiple_of {
	public:
		typedef T first_argument_type;
		typedef U second_argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& t, U const& u) const { return t % u == 0; }
	};

	//
	// less
	//
	template<typename T>
	struct less {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const { return lhs < rhs; }
	};
	//
	// greater
	//
	template<typename T>
	struct greater {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const { return lhs > rhs; }
	};
	//
	// equal_to
	//
	template<typename T>
	struct equal_to {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const { return lhs == rhs; }
	};
	//
	// mod_less
	//
	template<typename T, T mod>
	struct mod_less {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;
	public:
		SPROUT_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const { return lhs % mod < rhs % mod; }
	};

	//
	// less_than
	//
	template<typename T>
	struct less_than {
	public:
		typedef T argument_type;
		typedef bool result_type;
	public:
		T value;
	public:
		explicit SPROUT_CONSTEXPR less_than(T const& value) : value(value) {}
		SPROUT_CONSTEXPR bool operator()(T const& x) const { return x < value; }
	};
	//
	// greater_than
	//
	template<typename T>
	struct greater_than {
	public:
		typedef T argument_type;
		typedef bool result_type;
	public:
		T value;
	public:
		explicit SPROUT_CONSTEXPR greater_than(T const& value) : value(value) {}
		SPROUT_CONSTEXPR bool operator()(T const& x) const { return x > value; }
	};

	//
	// x2
	//
	template<typename T>
	struct x2 {
	public:
		typedef T argument_type;
		typedef T result_type;
	public:
		SPROUT_CONSTEXPR T operator()(T const& t) const { return t + t; }
	};

	//
	// plus
	//
	template<typename T>
	struct plus {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef T result_type;
	public:
		SPROUT_CONSTEXPR T operator()(T const& lhs, T const& rhs) const { return lhs + rhs; }
	};

	//
	// gen_iota
	//
	template<typename T>
	struct gen_iota {
	public:
		struct result {
		public:
			T val;
			gen_iota gen;
		public:
			SPROUT_CONSTEXPR T const& generated_value() const { return val; }
			SPROUT_CONSTEXPR gen_iota const& next_generator() const { return gen; }
		};
	private:
		T val;
	public:
		explicit SPROUT_CONSTEXPR gen_iota(T const& val = T())
			: val(val)
		{}
		SPROUT_CONSTEXPR result operator()() const { return result{val, gen_iota(val + 1)}; }
	};
	//
	// unf_iota
	//
	template<typename T>
	struct unf_iota {
	public:
		struct result {
		public:
			T val;
		public:
			SPROUT_CONSTEXPR T const& generated_value() const { return val; }
			SPROUT_CONSTEXPR T next_generator() const { return val + 1; }
		};
	public:
		SPROUT_CONSTEXPR result operator()(T const& val) const { return result{val}; }
	};

	//
	// x2_visitor
	//
	template<typename R = void>
	class x2_visitor {
	public:
		typedef R result_type;
	public:
		template<typename T>
		SPROUT_CONSTEXPR result_type operator()(T const& t) const { return static_cast<result_type>(t + t); }
	};
	//
	// x2_assign_visitor
	//
	template<typename R = void>
	class x2_assign_visitor {
	public:
		typedef R result_type;
	public:
		template<typename T>
		SPROUT_CONSTEXPR result_type operator()(T& t) const { return static_cast<result_type>(t += t); }
	};
}	// namespace testspr

#endif	// #ifndef TESTSPR_FUNCTIONAL_HPP
