/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_QUATERNION_HPP
#define SPROUT_MATH_QUATERNION_QUATERNION_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/array/array.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/math/quaternion/detail/abs_max.hpp>
#include <sprout/math/quaternion/detail/sum.hpp>
#include <sprout/math/quaternion/detail/mul.hpp>
#include <sprout/detail/static_size.hpp>

namespace sprout {
	namespace math {

#define	SPROUT_QUATERNION_ACCESSOR_GENERATOR(type) \
			SPROUT_CONSTEXPR type real() const { \
				return (elems_[0]); \
			} \
			SPROUT_CONSTEXPR quaternion<type> unreal() const { \
				return (quaternion<type>(static_cast<type>(0), elems_[1], elems_[2], elems_[3])); \
			} \
			SPROUT_CONSTEXPR type R_component_1() const { \
				return (elems_[0]); \
			} \
			SPROUT_CONSTEXPR type R_component_2() const { \
				return (elems_[1]); \
			} \
			SPROUT_CONSTEXPR type R_component_3() const { \
				return (elems_[2]); \
			} \
			SPROUT_CONSTEXPR type R_component_4() const { \
				return (elems_[3]); \
			} \
			SPROUT_CONSTEXPR sprout::complex<type> C_component_1() const { \
				return sprout::complex<type>(elems_[0], elems_[1]); \
			} \
			SPROUT_CONSTEXPR sprout::complex<type> C_component_2() const { \
				return sprout::complex<type>(elems_[2], elems_[3]); \
			}

#define	SPROUT_QUATERNION_MEMBER_ASSIGNMENT_GENERATOR(type) \
			template<typename X> \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator=(quaternion<X> const& a_affecter) { \
				elems_[0] = static_cast<type>(a_affecter.R_component_1()); \
				elems_[1] = static_cast<type>(a_affecter.R_component_2()); \
				elems_[2] = static_cast<type>(a_affecter.R_component_3()); \
				elems_[3] = static_cast<type>(a_affecter.R_component_4()); \
				return *this; \
			} \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator=(quaternion<type> const& a_affecter) { \
				elems_[0] = a_affecter.elems_[0]; \
				elems_[1] = a_affecter.elems_[1]; \
				elems_[2] = a_affecter.elems_[2]; \
				elems_[3] = a_affecter.elems_[3]; \
				return *this; \
			} \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator=(type const& a_affecter) { \
				elems_[0] = a_affecter; \
				elems_[1] = elems_[2] = elems_[3] = static_cast<type>(0); \
				return *this; \
			} \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator=(sprout::complex<type> const& a_affecter) { \
				elems_[0] = a_affecter.real(); \
				elems_[1] = a_affecter.imag(); \
				elems_[2] = elems_[3] = static_cast<type>(0); \
				return *this; \
			}

		//
		// quaternion
		//
		template<typename T>
		class quaternion
			: public sprout::detail::inherit_static_size<sprout::array<T, 4> >
		{
		private:
			typedef sprout::array<T, 4> array_type;
		public:
			typedef T value_type;
			typedef typename array_type::iterator iterator;
			typedef typename array_type::const_iterator const_iterator;
			typedef typename array_type::reference reference;
			typedef typename array_type::const_reference const_reference;
			typedef typename array_type::size_type size_type;
			typedef typename array_type::pointer pointer;
			typedef typename array_type::const_pointer const_pointer;
			typedef typename array_type::reverse_iterator reverse_iterator;
			typedef typename array_type::const_reverse_iterator const_reverse_iterator;
		private:
			array_type elems_;
		public:
			explicit SPROUT_CONSTEXPR quaternion(
				T const& requested_a = T(),
				T const& requested_b = T(),
				T const& requested_c = T(),
				T const& requested_d = T()
				)
				: elems_{{requested_a, requested_b, requested_c, requested_d}}
			{}
			explicit SPROUT_CONSTEXPR quaternion(
				sprout::complex<T> const& z0,
				sprout::complex<T> const& z1 = sprout::complex<T>()
				)
				: elems_{{z0.real(), z0.imag(), z1.real(), z1.imag()}}
			{}
			template<typename X>
			explicit SPROUT_CONSTEXPR quaternion(quaternion<X> const& a_recopier)
				: elems_{{
					static_cast<T>(a_recopier.R_component_1()),
					static_cast<T>(a_recopier.R_component_2()),
					static_cast<T>(a_recopier.R_component_3()),
					static_cast<T>(a_recopier.R_component_4())
					}}
			{}
			SPROUT_QUATERNION_ACCESSOR_GENERATOR(T)
			SPROUT_QUATERNION_MEMBER_ASSIGNMENT_GENERATOR(T)
			SPROUT_CXX14_CONSTEXPR quaternion<T>& operator+=(T const& rhs) {
				T at = elems_[0] + rhs;
				elems_[0] = at;
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR quaternion<T>& operator+=(sprout::complex<T> const& rhs) {
				T at = elems_[0] + rhs.real();
				T bt = elems_[1] + rhs.imag();
				elems_[0] = at; 
				elems_[1] = bt;
				return *this;
			}
			template<typename X>
			SPROUT_CXX14_CONSTEXPR quaternion<T>& operator+=(quaternion<X> const& rhs) {
				T at = elems_[0] + static_cast<T>(rhs.R_component_1());
				T bt = elems_[1] + static_cast<T>(rhs.R_component_2());
				T ct = elems_[2] + static_cast<T>(rhs.R_component_3());
				T dt = elems_[3] + static_cast<T>(rhs.R_component_4());
				elems_[0] = at;
				elems_[1] = bt;
				elems_[2] = ct;
				elems_[3] = dt;
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR quaternion<T>& operator-=(T const& rhs) {
				T at = elems_[0] - rhs;
				elems_[0] = at;
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR quaternion<T>& operator-=(sprout::complex<T> const& rhs) {
				T at = elems_[0] - rhs.real();
				T bt = elems_[1] - rhs.imag();
				elems_[0] = at;
				elems_[1] = bt;
				return *this;
			}
			template<typename X>
			SPROUT_CXX14_CONSTEXPR quaternion<T>& operator-=(quaternion<X> const& rhs) {
				T at = elems_[0] - static_cast<T>(rhs.R_component_1());
				T bt = elems_[1] - static_cast<T>(rhs.R_component_2());
				T ct = elems_[2] - static_cast<T>(rhs.R_component_3());
				T dt = elems_[3] - static_cast<T>(rhs.R_component_4());
				elems_[0] = at;
				elems_[1] = bt;
				elems_[2] = ct;
				elems_[3] = dt;
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR quaternion<T>& operator*=(T const& rhs) {
				T at = elems_[0] * rhs;
				T bt = elems_[1] * rhs;
				T ct = elems_[2] * rhs;
				T dt = elems_[3] * rhs;
				elems_[0] = at;
				elems_[1] = bt;
				elems_[2] = ct;
				elems_[3] = dt;
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR quaternion<T>& operator*=(sprout::complex<T> const& rhs) {
				T ar = rhs.real();
				T br = rhs.imag();
				T at = +elems_[0] * ar - elems_[1] * br;
				T bt = +elems_[0] * br + elems_[1] * ar;
				T ct = +elems_[2] * ar + elems_[3] * br;
				T dt = -elems_[2] * br + elems_[3] * ar;
				elems_[0] = at;
				elems_[1] = bt;
				elems_[2] = ct;
				elems_[3] = dt;
				return *this;
			}
			template<typename X>
			SPROUT_CXX14_CONSTEXPR quaternion<T>& operator*=(quaternion<X> const& rhs) {
				T ar = static_cast<T>(rhs.R_component_1());
				T br = static_cast<T>(rhs.R_component_2());
				T cr = static_cast<T>(rhs.R_component_3());
				T dr = static_cast<T>(rhs.R_component_4());
				T at = +elems_[0] * ar - elems_[1] * br - elems_[2] * cr - elems_[3] * dr;
				T bt = +elems_[0] * br + elems_[1] * ar + elems_[2] * dr - elems_[3] * cr;
				T ct = +elems_[0] * cr - elems_[1] * dr + elems_[2] * ar + elems_[3] * br;
				T dt = +elems_[0] * dr + elems_[1] * cr - elems_[2] * br + elems_[3] * ar;
				elems_[0] = at;
				elems_[1] = bt;
				elems_[2] = ct;
				elems_[3] = dt;
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR quaternion<T>& operator/=(T const& rhs) {
				T at = elems_[0] / rhs;
				T bt = elems_[1] / rhs;
				T ct = elems_[2] / rhs;
				T dt = elems_[3] / rhs;
				elems_[0] = at;
				elems_[1] = bt;
				elems_[2] = ct;
				elems_[3] = dt;
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR quaternion<T>& operator/=(sprout::complex<T> const& rhs) {
				T ar = rhs.real();
				T br = rhs.imag();
				T denominator = ar * ar + br * br;
				T at =(+elems_[0] * ar + elems_[1] * br) / denominator;
				T bt =(-elems_[0] * br + elems_[1] * ar) / denominator;
				T ct =(+elems_[2] * ar - elems_[3] * br) / denominator;
				T dt =(+elems_[2] * br + elems_[3] * ar) / denominator;
				elems_[0] = at;
				elems_[1] = bt;
				elems_[2] = ct;
				elems_[3] = dt;
				return *this;
			}
			template<typename X>
			SPROUT_CXX14_CONSTEXPR quaternion<T>& operator/=(quaternion<X> const& rhs) {
				T ar = static_cast<T>(rhs.R_component_1());
				T br = static_cast<T>(rhs.R_component_2());
				T cr = static_cast<T>(rhs.R_component_3());
				T dr = static_cast<T>(rhs.R_component_4());
				T denominator = ar * ar + br * br + cr * cr + dr * dr;
				T at =(+elems_[0] * ar + elems_[1] * br + elems_[2] * cr + elems_[3] * dr) / denominator;
				T bt =(-elems_[0] * br + elems_[1] * ar - elems_[2] * dr + elems_[3] * cr) / denominator;
				T ct =(-elems_[0] * cr + elems_[1] * dr + elems_[2] * ar - elems_[3] * br) / denominator;
				T dt =(-elems_[0] * dr - elems_[1] * cr + elems_[2] * br + elems_[3] * ar) / denominator;
				elems_[0] = at;
				elems_[1] = bt;
				elems_[2] = ct;
				elems_[3] = dt;
				return *this;
			}
			// iterators:
			SPROUT_CXX14_CONSTEXPR iterator begin() SPROUT_NOEXCEPT {
				return elems_.begin();
			}
			SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT {
				return elems_.begin();
			}
			SPROUT_CXX14_CONSTEXPR iterator end() SPROUT_NOEXCEPT {
				return elems_.end();
			}
			SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
				return elems_.end();
			}
			SPROUT_CXX14_CONSTEXPR reverse_iterator rbegin() SPROUT_NOEXCEPT {
				return elems_.rbegin();
			}
			SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT {
				return elems_.rbegin();
			}
			SPROUT_CXX14_CONSTEXPR reverse_iterator rend() SPROUT_NOEXCEPT {
				return elems_.rend();
			}
			SPROUT_CONSTEXPR const_reverse_iterator rend() const SPROUT_NOEXCEPT {
				return elems_.rend();
			}
			SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT {
				return elems_.cbegin();
			}
			SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT {
				return elems_.cbegin();
			}
			SPROUT_CONSTEXPR const_reverse_iterator crbegin() const SPROUT_NOEXCEPT {
				return elems_.crbegin();
			}
			SPROUT_CONSTEXPR const_reverse_iterator crend() const SPROUT_NOEXCEPT {
				return elems_.crend();
			}
			// capacity:
			SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT {
				return elems_.size();
			}
			SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT {
				return elems_.max_size();
			}
			SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT {
				return elems_.empty();
			}
			// element access:
			SPROUT_CXX14_CONSTEXPR reference operator[](size_type i) {
				return elems_[i];
			}
			SPROUT_CONSTEXPR const_reference operator[](size_type i) const {
				return elems_[i];
			}
			SPROUT_CXX14_CONSTEXPR reference at(size_type i) {
				return elems_.at(i);
			}
			SPROUT_CONSTEXPR const_reference at(size_type i) const {
				return elems_.at(i);
			}
			SPROUT_CXX14_CONSTEXPR reference front() {
				return elems_.front();
			}
			SPROUT_CONSTEXPR const_reference front() const {
				return elems_.front();
			}
			SPROUT_CXX14_CONSTEXPR reference back() {
				return elems_.back();
			}
			SPROUT_CONSTEXPR const_reference back() const {
				return elems_.back();
			}

			SPROUT_CXX14_CONSTEXPR pointer data() SPROUT_NOEXCEPT {
				return elems_.data();
			}
			SPROUT_CONSTEXPR const_pointer data() const SPROUT_NOEXCEPT {
				return elems_.data();
			}
			SPROUT_CXX14_CONSTEXPR pointer c_array() SPROUT_NOEXCEPT {
				return elems_.c_array();
			}
			SPROUT_CONSTEXPR const_pointer c_array() const SPROUT_NOEXCEPT {
				return elems_.c_array();
			}
		};

		template<>
		class quaternion<float>;
		template<>
		class quaternion<double>;
		template<>
		class quaternion<long double>;

#define	SPROUT_QUATERNION_MEMBER_TYPE_DATA_GENERATOR(type) \
		private: \
			typedef sprout::array<type, 4> array_type; \
		public: \
			typedef type value_type; \
			typedef typename array_type::iterator iterator; \
			typedef typename array_type::const_iterator const_iterator; \
			typedef typename array_type::reference reference; \
			typedef typename array_type::const_reference const_reference; \
			typedef typename array_type::size_type size_type; \
			typedef typename array_type::pointer pointer; \
			typedef typename array_type::const_pointer const_pointer; \
			typedef typename array_type::reverse_iterator reverse_iterator; \
			typedef typename array_type::const_reverse_iterator const_reverse_iterator; \
		private: \
			array_type elems_;

#define	SPROUT_QUATERNION_CONSTRUCTOR_GENERATOR(type) \
			explicit SPROUT_CONSTEXPR quaternion( \
				type const& requested_a = static_cast<type>(0), \
				type const& requested_b = static_cast<type>(0), \
				type const& requested_c = static_cast<type>(0), \
				type const& requested_d = static_cast<type>(0) \
				) \
				: elems_{{requested_a, requested_a, requested_c, requested_d}} \
			{} \
			explicit SPROUT_CONSTEXPR quaternion( \
				sprout::complex<type> const& z0, \
				sprout::complex<type> const& z1 = sprout::complex<type>() \
				) \
				: elems_{{z0.real(), z0.imag(), z1.real(), z1.imag()}} \
			{}

#define	SPROUT_QUATERNION_MEMBER_ADD_GENERATOR_1(type) \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator+=(type const& rhs) { \
				elems_[0] += rhs; \
				return *this; \
			}

#define	SPROUT_QUATERNION_MEMBER_ADD_GENERATOR_2(type) \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator+=(sprout::complex<type> const& rhs) { \
				elems_[0] += rhs.real(); \
				elems_[1] += rhs.imag(); \
				return *this; \
			}

#define	SPROUT_QUATERNION_MEMBER_ADD_GENERATOR_3(type) \
			template<typename X> \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator+=(quaternion<X> const& rhs) { \
				elems_[0] += static_cast<type>(rhs.R_component_1()); \
				elems_[1] += static_cast<type>(rhs.R_component_2()); \
				elems_[2] += static_cast<type>(rhs.R_component_3()); \
				elems_[3] += static_cast<type>(rhs.R_component_4()); \
				return *this; \
			}

#define	SPROUT_QUATERNION_MEMBER_SUB_GENERATOR_1(type) \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator-=(type const& rhs) { \
				elems_[0] -= rhs; \
				return *this; \
			}

#define	SPROUT_QUATERNION_MEMBER_SUB_GENERATOR_2(type) \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator-=(sprout::complex<type> const& rhs) { \
				elems_[0] -= rhs.real(); \
				elems_[1] -= rhs.imag(); \
				return *this; \
			}

#define	SPROUT_QUATERNION_MEMBER_SUB_GENERATOR_3(type) \
			template<typename X> \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator-=(quaternion<X> const& rhs) { \
				elems_[0] -= static_cast<type>(rhs.R_component_1()); \
				elems_[1] -= static_cast<type>(rhs.R_component_2()); \
				elems_[2] -= static_cast<type>(rhs.R_component_3()); \
				elems_[3] -= static_cast<type>(rhs.R_component_4()); \
				return *this; \
			}

#define	SPROUT_QUATERNION_MEMBER_MUL_GENERATOR_1(type) \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator*=(type const& rhs) { \
				elems_[0] *= rhs; \
				elems_[1] *= rhs; \
				elems_[2] *= rhs; \
				elems_[3] *= rhs; \
				return *this; \
			}

#define	SPROUT_QUATERNION_MEMBER_MUL_GENERATOR_2(type) \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator*=(sprout::complex<type> const& rhs) { \
				type ar = rhs.real(); \
				type br = rhs.imag(); \
				type at = +elems_[0] * ar - elems_[1] * br; \
				type bt = +elems_[0] * br + elems_[1] * ar; \
				type ct = +elems_[2] * ar + elems_[3] * br; \
				type dt = -elems_[2] * br + elems_[3] * ar; \
				elems_[0] = at; \
				elems_[1] = bt; \
				elems_[2] = ct; \
				elems_[3] = dt; \
				return *this; \
			}

#define	SPROUT_QUATERNION_MEMBER_MUL_GENERATOR_3(type) \
			template<typename X> \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator*=(quaternion<X> const& rhs) { \
				type ar = static_cast<type>(rhs.R_component_1()); \
				type br = static_cast<type>(rhs.R_component_2()); \
				type cr = static_cast<type>(rhs.R_component_3()); \
				type dr = static_cast<type>(rhs.R_component_4()); \
				type at = +elems_[0] * ar - elems_[1] * br - elems_[2] * cr - elems_[3] * dr; \
				type bt = +elems_[0] * br + elems_[1] * ar + elems_[2] * dr - elems_[3] * cr; \
				type ct = +elems_[0] * cr - elems_[1] * dr + elems_[2] * ar + elems_[3] * br; \
				type dt = +elems_[0] * dr + elems_[1] * cr - elems_[2] * br + elems_[3] * ar; \
				elems_[0] = at; \
				elems_[1] = bt; \
				elems_[2] = ct; \
				elems_[3] = dt; \
				return *this; \
			}

#define	SPROUT_QUATERNION_MEMBER_DIV_GENERATOR_1(type) \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator/=(type const& rhs) { \
				elems_[0] /= rhs; \
				elems_[1] /= rhs; \
				elems_[2] /= rhs; \
				elems_[3] /= rhs; \
				return *this; \
			}

#define	SPROUT_QUATERNION_MEMBER_DIV_GENERATOR_2(type) \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator/=(sprout::complex<type> const& rhs) { \
				sprout::array<type, 2> tr{{ \
					rhs.real(), \
					rhs.imag() \
				}}; \
				type mixam = static_cast<type>(1) / sprout::math::detail::abs_max(tr); \
				tr = sprout::math::detail::mul(tr, mixam); \
				sprout::array<type, 4> tt{{ \
					+elems_[0] * tr[0] + elems_[1] * tr[1], \
					-elems_[0] * tr[1] + elems_[1] * tr[0], \
					+elems_[2] * tr[0] - elems_[3] * tr[1], \
					+elems_[2] * tr[1] + elems_[3] * tr[0] \
				}}; \
				tr = sprout::math::detail::mul(tr, tr); \
				tt = sprout::math::detail::mul(tt, mixam / sprout::math::detail::sum(tr)); \
				elems_[0] = tt[0]; \
				elems_[1] = tt[1]; \
				elems_[2] = tt[2]; \
				elems_[3] = tt[3]; \
				return *this; \
			}

#define	SPROUT_QUATERNION_MEMBER_DIV_GENERATOR_3(type) \
			template<typename X> \
			SPROUT_CXX14_CONSTEXPR quaternion<type>& operator/=(quaternion<X> const& rhs) { \
				sprout::array<type, 4> tr{{ \
					static_cast<type>(rhs.R_component_1()), \
					static_cast<type>(rhs.R_component_2()), \
					static_cast<type>(rhs.R_component_3()), \
					static_cast<type>(rhs.R_component_4()) \
				}}; \
				type mixam = static_cast<type>(1) / sprout::math::detail::abs_max(tr); \
				tr = sprout::math::detail::mul(tr, mixam); \
				sprout::array<type, 4> tt{{ \
					+elems_[0] * tr[0] + elems_[1] * tr[1] + elems_[2] * tr[2] + elems_[3] * tr[3], \
					-elems_[0] * tr[1] + elems_[1] * tr[0] - elems_[2] * tr[3] + elems_[3] * tr[2], \
					-elems_[0] * tr[2] + elems_[1] * tr[3] + elems_[2] * tr[0] - elems_[3] * tr[1], \
					-elems_[0] * tr[3] - elems_[1] * tr[2] + elems_[2] * tr[1] + elems_[3] * tr[0] \
				}}; \
				tr = sprout::math::detail::mul(tr, tr); \
				tt = sprout::math::detail::mul(tt, mixam / sprout::math::detail::sum(tr)); \
				elems_[0] = tt[0]; \
				elems_[1] = tt[1]; \
				elems_[2] = tt[2]; \
				elems_[3] = tt[3]; \
				return *this; \
			}

#define	SPROUT_QUATERNION_MEMBER_ADD_GENERATOR(type) \
			SPROUT_QUATERNION_MEMBER_ADD_GENERATOR_1(type) \
			SPROUT_QUATERNION_MEMBER_ADD_GENERATOR_2(type) \
			SPROUT_QUATERNION_MEMBER_ADD_GENERATOR_3(type)

#define	SPROUT_QUATERNION_MEMBER_SUB_GENERATOR(type) \
			SPROUT_QUATERNION_MEMBER_SUB_GENERATOR_1(type) \
			SPROUT_QUATERNION_MEMBER_SUB_GENERATOR_2(type) \
			SPROUT_QUATERNION_MEMBER_SUB_GENERATOR_3(type)

#define	SPROUT_QUATERNION_MEMBER_MUL_GENERATOR(type) \
			SPROUT_QUATERNION_MEMBER_MUL_GENERATOR_1(type) \
			SPROUT_QUATERNION_MEMBER_MUL_GENERATOR_2(type) \
			SPROUT_QUATERNION_MEMBER_MUL_GENERATOR_3(type)

#define	SPROUT_QUATERNION_MEMBER_DIV_GENERATOR(type) \
			SPROUT_QUATERNION_MEMBER_DIV_GENERATOR_1(type) \
			SPROUT_QUATERNION_MEMBER_DIV_GENERATOR_2(type) \
			SPROUT_QUATERNION_MEMBER_DIV_GENERATOR_3(type)

#define	SPROUT_QUATERNION_MEMBER_ALGEBRAIC_GENERATOR(type) \
			SPROUT_QUATERNION_MEMBER_ADD_GENERATOR(type) \
			SPROUT_QUATERNION_MEMBER_SUB_GENERATOR(type) \
			SPROUT_QUATERNION_MEMBER_MUL_GENERATOR(type) \
			SPROUT_QUATERNION_MEMBER_DIV_GENERATOR(type)

#define	SPROUT_QUATERNION_MEMBER_CONTAINER_GENERATOR(type) \
			SPROUT_CXX14_CONSTEXPR iterator begin() SPROUT_NOEXCEPT { \
				return elems_.begin(); \
			} \
			SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT { \
				return elems_.begin(); \
			} \
			SPROUT_CXX14_CONSTEXPR iterator end() SPROUT_NOEXCEPT { \
				return elems_.end(); \
			} \
			SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT { \
				return elems_.end(); \
			} \
			SPROUT_CXX14_CONSTEXPR reverse_iterator rbegin() SPROUT_NOEXCEPT { \
				return elems_.rbegin(); \
			} \
			SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT { \
				return elems_.rbegin(); \
			} \
			SPROUT_CXX14_CONSTEXPR reverse_iterator rend() SPROUT_NOEXCEPT { \
				return elems_.rend(); \
			} \
			SPROUT_CONSTEXPR const_reverse_iterator rend() const SPROUT_NOEXCEPT { \
				return elems_.rend(); \
			} \
			SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT { \
				return elems_.cbegin(); \
			} \
			SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT { \
				return elems_.cbegin(); \
			} \
			SPROUT_CONSTEXPR const_reverse_iterator crbegin() const SPROUT_NOEXCEPT { \
				return elems_.crbegin(); \
			} \
			SPROUT_CONSTEXPR const_reverse_iterator crend() const SPROUT_NOEXCEPT { \
				return elems_.crend(); \
			} \
			 \
			SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT { \
				return elems_.size(); \
			} \
			SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT { \
				return elems_.max_size(); \
			} \
			SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT { \
				return elems_.empty(); \
			} \
			 \
			SPROUT_CXX14_CONSTEXPR reference operator[](size_type i) { \
				return elems_[i]; \
			} \
			SPROUT_CONSTEXPR const_reference operator[](size_type i) const { \
				return elems_[i]; \
			} \
			SPROUT_CXX14_CONSTEXPR reference at(size_type i) { \
				return elems_.at(i); \
			} \
			SPROUT_CONSTEXPR const_reference at(size_type i) const { \
				return elems_.at(i); \
			} \
			SPROUT_CXX14_CONSTEXPR reference front() { \
				return elems_.front(); \
			} \
			SPROUT_CONSTEXPR const_reference front() const { \
				return elems_.front(); \
			} \
			SPROUT_CXX14_CONSTEXPR reference back() { \
				return elems_.back(); \
			} \
			SPROUT_CONSTEXPR const_reference back() const { \
				return elems_.back(); \
			} \
			 \
			SPROUT_CXX14_CONSTEXPR pointer data() SPROUT_NOEXCEPT { \
				return elems_.data(); \
			} \
			SPROUT_CONSTEXPR const_pointer data() const SPROUT_NOEXCEPT { \
				return elems_.data(); \
			} \
			SPROUT_CXX14_CONSTEXPR pointer c_array() SPROUT_NOEXCEPT { \
				return elems_.c_array(); \
			} \
			SPROUT_CONSTEXPR const_pointer c_array() const SPROUT_NOEXCEPT { \
				return elems_.c_array(); \
			}

#define	SPROUT_QUATERNION_BASE_STATIC_SIZE_DECL(type) \
			public sprout::detail::inherit_static_size<sprout::array<type, 4> >


		template<>
		class quaternion<float>
			: SPROUT_QUATERNION_BASE_STATIC_SIZE_DECL(float)
		{
		public:
			SPROUT_QUATERNION_MEMBER_TYPE_DATA_GENERATOR(float)
		public:
			SPROUT_QUATERNION_CONSTRUCTOR_GENERATOR(float)
			explicit SPROUT_CONSTEXPR quaternion(quaternion<double> const& a_recopier);
			explicit SPROUT_CONSTEXPR quaternion(quaternion<long double> const& a_recopier);
			SPROUT_QUATERNION_ACCESSOR_GENERATOR(float)
			SPROUT_QUATERNION_MEMBER_ASSIGNMENT_GENERATOR(float)
			SPROUT_QUATERNION_MEMBER_ALGEBRAIC_GENERATOR(float)
			SPROUT_QUATERNION_MEMBER_CONTAINER_GENERATOR(float)
		};

		template<>
		class quaternion<double>
			: SPROUT_QUATERNION_BASE_STATIC_SIZE_DECL(double)
		{
		public:
			SPROUT_QUATERNION_MEMBER_TYPE_DATA_GENERATOR(double)
		public:
			SPROUT_QUATERNION_CONSTRUCTOR_GENERATOR(double)
			explicit SPROUT_CONSTEXPR quaternion(quaternion<float> const& a_recopier);
			explicit SPROUT_CONSTEXPR quaternion(quaternion<long double> const& a_recopier);
			SPROUT_QUATERNION_ACCESSOR_GENERATOR(double)
			SPROUT_QUATERNION_MEMBER_ASSIGNMENT_GENERATOR(double)
			SPROUT_QUATERNION_MEMBER_ALGEBRAIC_GENERATOR(double)
			SPROUT_QUATERNION_MEMBER_CONTAINER_GENERATOR(double)
		};

		template<>
		class quaternion<long double>
			: SPROUT_QUATERNION_BASE_STATIC_SIZE_DECL(long double)
		{
		public:
			SPROUT_QUATERNION_MEMBER_TYPE_DATA_GENERATOR(long double)
		public:
			SPROUT_QUATERNION_CONSTRUCTOR_GENERATOR(long double)
			explicit SPROUT_CONSTEXPR quaternion(quaternion<float> const& a_recopier);
			explicit SPROUT_CONSTEXPR quaternion(quaternion<double> const& a_recopier);
			SPROUT_QUATERNION_ACCESSOR_GENERATOR(long double)
			SPROUT_QUATERNION_MEMBER_ASSIGNMENT_GENERATOR(long double)
			SPROUT_QUATERNION_MEMBER_ALGEBRAIC_GENERATOR(long double)
			SPROUT_QUATERNION_MEMBER_CONTAINER_GENERATOR(long double)
		};

		SPROUT_CONSTEXPR sprout::math::quaternion<float>::quaternion(sprout::math::quaternion<double> const& a_recopier)
			: elems_{{
				static_cast<float>(a_recopier.R_component_1()),
				static_cast<float>(a_recopier.R_component_2()),
				static_cast<float>(a_recopier.R_component_3()),
				static_cast<float>(a_recopier.R_component_4())
				}}
		{}
		SPROUT_CONSTEXPR sprout::math::quaternion<float>::quaternion(sprout::math::quaternion<long double> const& a_recopier)
			: elems_{{
				static_cast<float>(a_recopier.R_component_1()),
				static_cast<float>(a_recopier.R_component_2()),
				static_cast<float>(a_recopier.R_component_3()),
				static_cast<float>(a_recopier.R_component_4())
				}}
		{}

		SPROUT_CONSTEXPR sprout::math::quaternion<double>::quaternion(sprout::math::quaternion<float> const& a_recopier)
			: elems_{{
				static_cast<double>(a_recopier.R_component_1()),
				static_cast<double>(a_recopier.R_component_2()),
				static_cast<double>(a_recopier.R_component_3()),
				static_cast<double>(a_recopier.R_component_4())
				}}
		{}
		SPROUT_CONSTEXPR sprout::math::quaternion<double>::quaternion(sprout::math::quaternion<long double> const& a_recopier)
			: elems_{{
				static_cast<double>(a_recopier.R_component_1()),
				static_cast<double>(a_recopier.R_component_2()),
				static_cast<double>(a_recopier.R_component_3()),
				static_cast<double>(a_recopier.R_component_4())
				}}
		{}

		SPROUT_CONSTEXPR sprout::math::quaternion<long double>::quaternion(sprout::math::quaternion<float> const& a_recopier)
			: elems_{{
				static_cast<long double>(a_recopier.R_component_1()),
				static_cast<long double>(a_recopier.R_component_2()),
				static_cast<long double>(a_recopier.R_component_3()),
				static_cast<long double>(a_recopier.R_component_4())
				}}
		{}
		SPROUT_CONSTEXPR sprout::math::quaternion<long double>::quaternion(sprout::math::quaternion<double> const& a_recopier)
			: elems_{{
				static_cast<long double>(a_recopier.R_component_1()),
				static_cast<long double>(a_recopier.R_component_2()),
				static_cast<long double>(a_recopier.R_component_3()),
				static_cast<long double>(a_recopier.R_component_4())
				}}
		{}

#undef	SPROUT_QUATERNION_MEMBER_CONTAINER_GENERATOR
#undef	SPROUT_QUATERNION_MEMBER_ALGEBRAIC_GENERATOR
#undef	SPROUT_QUATERNION_MEMBER_ADD_GENERATOR
#undef	SPROUT_QUATERNION_MEMBER_SUB_GENERATOR
#undef	SPROUT_QUATERNION_MEMBER_MUL_GENERATOR
#undef	SPROUT_QUATERNION_MEMBER_DIV_GENERATOR
#undef	SPROUT_QUATERNION_MEMBER_ADD_GENERATOR_1
#undef	SPROUT_QUATERNION_MEMBER_ADD_GENERATOR_2
#undef	SPROUT_QUATERNION_MEMBER_ADD_GENERATOR_3
#undef	SPROUT_QUATERNION_MEMBER_SUB_GENERATOR_1
#undef	SPROUT_QUATERNION_MEMBER_SUB_GENERATOR_2
#undef	SPROUT_QUATERNION_MEMBER_SUB_GENERATOR_3
#undef	SPROUT_QUATERNION_MEMBER_MUL_GENERATOR_1
#undef	SPROUT_QUATERNION_MEMBER_MUL_GENERATOR_2
#undef	SPROUT_QUATERNION_MEMBER_MUL_GENERATOR_3
#undef	SPROUT_QUATERNION_MEMBER_DIV_GENERATOR_1
#undef	SPROUT_QUATERNION_MEMBER_DIV_GENERATOR_2
#undef	SPROUT_QUATERNION_MEMBER_DIV_GENERATOR_3
#undef	SPROUT_QUATERNION_CONSTRUCTOR_GENERATOR
#undef	SPROUT_QUATERNION_MEMBER_TYPE_DATA_GENERATOR
#undef	SPROUT_QUATERNION_MEMBER_ASSIGNMENT_GENERATOR
#undef	SPROUT_QUATERNION_ACCESSOR_GENERATOR
	}	// namespace math

	using sprout::math::quaternion;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_QUATERNION_HPP
