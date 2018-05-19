/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_FOLD_HPP
#define SPROUT_UTILITY_FOLD_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/move.hpp>

namespace sprout {
	template<typename BinaryOperation>
	class folder_forwarder {
	public:
		typedef BinaryOperation function_type;
	private:
		function_type binary_op_;
	public:
		explicit SPROUT_CONSTEXPR folder_forwarder(function_type const& binary_op)
			: binary_op_(binary_op)
		{}
		SPROUT_CONSTEXPR function_type const& func() const {
			return binary_op_;
		}
	};

	template<typename BinaryOperation, typename T>
	class folder {
	public:
		typedef BinaryOperation function_type;
		typedef T value_type;
	private:
		function_type binary_op_;
		value_type value_;
	public:
		explicit SPROUT_CONSTEXPR folder(function_type const& binary_op, value_type const& value)
			: binary_op_(binary_op), value_(value)
		{}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR folder& left(U&& val) {
			return (value_ = binary_op_(value_, SPROUT_FORWARD(U, val))), *this;
		}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR folder& right(U&& val) {
			return (value_ = binary_op_(SPROUT_FORWARD(U, val), value_)), *this;
		}
		SPROUT_CONSTEXPR function_type const& func() const {
			return binary_op_;
		}
		SPROUT_CONSTEXPR value_type value() const {
			return value_;
		}
		SPROUT_CONSTEXPR value_type get() const {
			return value_;
		}
		SPROUT_CONSTEXPR operator value_type() const {
			return value_;
		}
	};

	template<typename BinaryOperation, typename T>
	inline SPROUT_CONSTEXPR sprout::folder<BinaryOperation, T>
	operator,(sprout::folder_forwarder<BinaryOperation> const& lhs, T&& rhs) {
		return sprout::folder<BinaryOperation, T>(lhs.func(), SPROUT_FORWARD(T, rhs));
	}
	template<typename BinaryOperation, typename T>
	inline SPROUT_CONSTEXPR sprout::folder<BinaryOperation, T>
	operator,(T&& lhs, sprout::folder_forwarder<BinaryOperation> const& rhs) {
		return sprout::folder<BinaryOperation, T>(rhs.func(), SPROUT_FORWARD(T, lhs));
	}
	template<typename BinaryOperation, typename T, typename U>
	inline SPROUT_CONSTEXPR sprout::folder<BinaryOperation, T>&&
	operator,(sprout::folder<BinaryOperation, T>&& lhs, U&& rhs) {
		return sprout::move(lhs.left(SPROUT_FORWARD(U, rhs)));
	}
	template<typename BinaryOperation, typename T, typename U>
	inline SPROUT_CONSTEXPR sprout::folder<BinaryOperation, T>&&
	operator,(U&& lhs, sprout::folder<BinaryOperation, T>&& rhs) {
		return sprout::move(rhs.right(SPROUT_FORWARD(U, lhs)));
	}

	template<typename BinaryOperation>
	inline SPROUT_CONSTEXPR sprout::folder_forwarder<BinaryOperation>
	fold_by(BinaryOperation const& binary_op) {
		return sprout::folder_forwarder<BinaryOperation>(binary_op);
	}
	template<typename BinaryOperation, typename T>
	inline SPROUT_CONSTEXPR sprout::folder<BinaryOperation, T>
	fold_by(BinaryOperation const& binary_op, T&& init) {
		return sprout::folder<BinaryOperation, T>(binary_op, SPROUT_FORWARD(T, init));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_FOLD_HPP
