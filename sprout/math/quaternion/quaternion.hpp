/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the sprout Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.sprout.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_QUATERNION_HPP
#define SPROUT_MATH_QUATERNION_QUATERNION_HPP

#include <iosfwd>
#include <sstream>
#include <locale>
#include <sprout/config.hpp>
#include <sprout/array/array.hpp>
#include <sprout/math/abs.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/cosh.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/math/abs.hpp>
//#include <sprout/math/sinc.hpp>
//#include <sprout/math/sinhc.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/range/algorithm/max_element.hpp>
#include <sprout/range/numeric/accumulate.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			class abs_less {
			public:
				SPROUT_CONSTEXPR T
				operator()(T const& lhs, T const& rhs) const {
					return sprout::math::abs(lhs) < sprout::math::abs(rhs);
				}
			};
			template<typename T>
			class abs_plus {
			public:
				SPROUT_CONSTEXPR T
				operator()(T const& lhs, T const& rhs) const {
					return sprout::math::abs(lhs) + sprout::math::abs(rhs);
				}
			};
			template<typename T, std::size_t N>
			SPROUT_CONSTEXPR T
			abs_max(sprout::array<T, N> const& c) {
				return sprout::math::abs(*sprout::range::max_element(c, sprout::math::detail::abs_less<T>()));
			}
			template<typename T, std::size_t N>
			SPROUT_CONSTEXPR T
			sum(sprout::array<T, N> const& c) {
				return sprout::range::accumulate(c, static_cast<T>(0));
			}
			template<typename T, std::size_t N>
			SPROUT_CONSTEXPR T
			abs_sum(sprout::array<T, N> const& c) {
				return sprout::range::accumulate(c, static_cast<T>(0), sprout::math::detail::abs_plus<T>());
			}
			template<typename T>
			SPROUT_CONSTEXPR sprout::array<T, 2>
			mul(sprout::array<T, 2> const& l, T const& r) {
				return sprout::array<T, 2>{{
					l[0] * r,
					l[1] * r,
					}};
			}
			template<typename T>
			SPROUT_CONSTEXPR sprout::array<T, 2>
			mul(sprout::array<T, 2> const& l, sprout::array<T, 2> const& r) {
				return sprout::array<T, 2>{{
					l[0] * r[0],
					l[1] * r[1],
					}};
			}
			template<typename T>
			SPROUT_CONSTEXPR sprout::array<T, 4>
			mul(sprout::array<T, 4> const& l, T const& r) {
				return sprout::array<T, 4>{{
					l[0] * r,
					l[1] * r,
					l[2] * r,
					l[3] * r
					}};
			}
			template<typename T>
			SPROUT_CONSTEXPR sprout::array<T, 4>
			mul(sprout::array<T, 4> const& l, sprout::array<T, 4> const& r) {
				return sprout::array<T, 4>{{
					l[0] * r[0],
					l[1] * r[1],
					l[2] * r[2],
					l[3] * r[3]
					}};
			}
		}	// namespace detail

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
		class quaternion {
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
		public:
			SPROUT_STATIC_CONSTEXPR size_type static_size = array_type::static_size;
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
		template<typename T>
		SPROUT_CONSTEXPR_OR_CONST typename sprout::math::quaternion<T>::size_type sprout::math::quaternion<T>::static_size;

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
		public: \
			SPROUT_STATIC_CONSTEXPR size_type static_size = array_type::static_size; \
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

#define	SPROUT_QUATERNION_MEMBER_STATIC_SIZE_SPECIALIZATION_GENERATOR(type) \
		SPROUT_CONSTEXPR_OR_CONST typename sprout::math::quaternion<type>::size_type sprout::math::quaternion<type>::static_size;

		template<>
		class quaternion<float> {
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
		SPROUT_QUATERNION_MEMBER_STATIC_SIZE_SPECIALIZATION_GENERATOR(float)

		template<>
		class quaternion<double> {
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
		SPROUT_QUATERNION_MEMBER_STATIC_SIZE_SPECIALIZATION_GENERATOR(double)

		template<>
		class quaternion<long double> {
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
		SPROUT_QUATERNION_MEMBER_STATIC_SIZE_SPECIALIZATION_GENERATOR(long double)

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

		//
		// operator+
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator+(T const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs + rhs.R_component_1(),
				rhs.R_component_2(),
				rhs.R_component_3(),
				rhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator+(sprout::math::quaternion<T> const& lhs, T const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() + rhs,
				lhs.R_component_2(),
				lhs.R_component_3(),
				lhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator+(sprout::complex<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.real() + rhs.R_component_1(),
				lhs.imag() + rhs.R_component_2(),
				rhs.R_component_3(),
				rhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator+(sprout::math::quaternion<T> const& lhs, sprout::complex<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() + rhs.real(),
				lhs.R_component_2() + rhs.imag(),
				lhs.R_component_3(),
				lhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator+(sprout::math::quaternion<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() + rhs.R_component_1(),
				lhs.R_component_2() + rhs.R_component_2(),
				lhs.R_component_3() + rhs.R_component_3(),
				lhs.R_component_4() + rhs.R_component_4()
				);
		}
		//
		// operator-
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator-(T const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs - rhs.R_component_1(),
				rhs.R_component_2(),
				rhs.R_component_3(),
				rhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator-(sprout::math::quaternion<T> const& lhs, T const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() - rhs,
				lhs.R_component_2(),
				lhs.R_component_3(),
				lhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator-(sprout::complex<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.real() - rhs.R_component_1(),
				lhs.imag() - rhs.R_component_2(),
				rhs.R_component_3(),
				rhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator-(sprout::math::quaternion<T> const& lhs, sprout::complex<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() - rhs.real(),
				lhs.R_component_2() - rhs.imag(),
				lhs.R_component_3(),
				lhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator-(sprout::math::quaternion<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() - rhs.R_component_1(),
				lhs.R_component_2() - rhs.R_component_2(),
				lhs.R_component_3() - rhs.R_component_3(),
				lhs.R_component_4() - rhs.R_component_4()
				);
		}
		//
		// operator*
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator*(T const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs * rhs.R_component_1(),
				lhs * rhs.R_component_2(),
				lhs * rhs.R_component_3(),
				lhs * rhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator*(sprout::math::quaternion<T> const& lhs, T const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() * rhs,
				lhs.R_component_2() * rhs,
				lhs.R_component_3() * rhs,
				lhs.R_component_4() * rhs
				);
		}
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			mul_qc_impl(T const& a, T const& b, T const& c, T const& d, T const& ar, T const& br) {
				return sprout::math::quaternion<T>(
					+a * ar - b * br,
					+a * br + b * ar,
					+c * ar + d * br,
					-c * br + d * ar
					);
			}
		}	// namespace detail
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator*(sprout::complex<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::detail::mul_qc_impl(
				lhs.R_component_1(), lhs.R_component_2(), lhs.R_component_3(), lhs.R_component_4(),
				rhs.real(), rhs.imag()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator*(sprout::math::quaternion<T> const& lhs, sprout::complex<T> const& rhs) {
			return sprout::math::detail::mul_qc_impl(
				rhs.R_component_1(), rhs.R_component_2(), rhs.R_component_3(), rhs.R_component_4(),
				lhs.real(), lhs.imag()
				);
		}
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			mul_qq_impl(T const& a, T const& b, T const& c, T const& d, T const& ar, T const& br, T const& cr, T const& dr) {
				return sprout::math::quaternion<T>(
					+a * ar - b * br - c * cr - d * dr,
					+a * br + b * ar + c * dr - d * cr,
					+a * cr - b * dr + c * ar + d * br,
					+a * dr + b * cr - c * br + d * ar
					);
			}
		}	// namespace detail
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator*(sprout::math::quaternion<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::detail::mul_qq_impl(
				lhs.R_component_1(), lhs.R_component_2(), lhs.R_component_3(), lhs.R_component_4(),
				rhs.R_component_1(), rhs.R_component_2(), rhs.R_component_3(), rhs.R_component_4()
				);
		}
		//
		// operator/
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator/(T const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::quaternion<T>(
				lhs / rhs.R_component_1(),
				lhs / rhs.R_component_2(),
				lhs / rhs.R_component_3(),
				lhs / rhs.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator/(sprout::math::quaternion<T> const& lhs, T const& rhs) {
			return sprout::math::quaternion<T>(
				lhs.R_component_1() / rhs,
				lhs.R_component_2() / rhs,
				lhs.R_component_3() / rhs,
				lhs.R_component_4() / rhs
				);
		}
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			div_qq_impl_4(sprout::array<T, 4> const& tt) {
				return sprout::math::quaternion<T>(
					tt[0], tt[1], tt[2], tt[3]
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			div_qq_impl_3(sprout::array<T, 4> const& tr, T const& mixam, sprout::array<T, 4> const& tt) {
				return sprout::math::detail::div_qq_impl_3(
					sprout::math::detail::mul(tt, mixam / sprout::math::detail::sum(tr))
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			div_qq_impl_2(T const& a, T const& b, T const& c, T const& d, sprout::array<T, 4> const& tr, T const& mixam) {
				return sprout::math::detail::div_qq_impl_3(
					sprout::math::detail::mul(tr, tr), mixam,
					sprout::array<T, 4>{{
						+a * tr[0] + b * tr[1] + c * tr[2] + d * tr[3],
						-a * tr[1] + b * tr[0] - c * tr[3] + d * tr[2],
						-a * tr[2] + b * tr[3] + c * tr[0] - d * tr[1],
						-a * tr[3] - b * tr[2] + c * tr[1] + d * tr[0]
						}}
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			div_qq_impl_1(T const& a, T const& b, T const& c, T const& d, sprout::array<T, 4> const& tr, T const& mixam) {
				return sprout::math::detail::div_qq_impl_2(
					a, b, c, d, sprout::math::detail::mul(tr, mixam), mixam
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			div_qq_impl(T const& a, T const& b, T const& c, T const& d, sprout::array<T, 4> const& tr) {
				return sprout::math::detail::div_qq_impl_1(
					a, b, c, d, tr,
					static_cast<T>(1) / sprout::math::detail::abs_max(tr)
					);
			}
		}	// namespace detail
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator/(sprout::complex<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::detail::div_qq_impl(
				lhs.real(), lhs.imag(), static_cast<T>(0), static_cast<T>(0),
				sprout::array<T, 4>{{rhs.R_component_1(), rhs.R_component_2(), rhs.R_component_3(), rhs.R_component_4()}}
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator/(sprout::math::quaternion<T> const& lhs, sprout::complex<T> const& rhs) {
			return sprout::math::detail::div_qq_impl(
				lhs.R_component_1(), lhs.R_component_2(), lhs.R_component_3(), lhs.R_component_4(),
				sprout::array<T, 4>{{rhs.real(), rhs.imag(), static_cast<T>(0), static_cast<T>(0)}}
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator/(sprout::math::quaternion<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return sprout::math::detail::div_qq_impl(
				lhs.R_component_1(), lhs.R_component_2(), lhs.R_component_3(), lhs.R_component_4(),
				sprout::array<T, 4>{{rhs.R_component_1(), rhs.R_component_2(), rhs.R_component_3(), rhs.R_component_4()}}
				);
		}

		//
		// operator+
		// operator-
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator+(sprout::math::quaternion<T> const& q) {
			return q;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		operator-(sprout::math::quaternion<T> const& q) {
			return sprout::math::quaternion<T>(-q.R_component_1(), -q.R_component_2(), -q.R_component_3(), -q.R_component_4());
		}

		//
		// operator==
		// operator!=
		//
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator==(T const& lhs, sprout::math::quaternion<T> const& rhs) {
			return rhs.R_component_1() == lhs
				&& rhs.R_component_2() == static_cast<T>(0)
				&& rhs.R_component_3() == static_cast<T>(0)
				&& rhs.R_component_4() == static_cast<T>(0)
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator==(sprout::math::quaternion<T> const& lhs, T const& rhs) {
			return lhs.R_component_1() == rhs
				&& lhs.R_component_2() == static_cast<T>(0)
				&& lhs.R_component_3() == static_cast<T>(0)
				&& lhs.R_component_4() == static_cast<T>(0)
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator==(sprout::complex<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return rhs.R_component_1() == lhs.real()
				&& rhs.R_component_2() == lhs.imag()
				&& rhs.R_component_3() == static_cast<T>(0)
				&& rhs.R_component_4() == static_cast<T>(0)
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator==(sprout::math::quaternion<T> const& lhs, sprout::complex<T> const& rhs) {
			return lhs.R_component_1() == rhs.real()
				&& lhs.R_component_2() == rhs.imag()
				&& lhs.R_component_3() == static_cast<T>(0)
				&& lhs.R_component_4() == static_cast<T>(0)
				;
		}
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator==(sprout::math::quaternion<T> const& lhs, sprout::math::quaternion<T> const& rhs) {
			return rhs.R_component_1() == lhs.R_component_1()
				&& rhs.R_component_2() == lhs.R_component_2()
				&& rhs.R_component_3() == lhs.R_component_3()
				&& rhs.R_component_4() == lhs.R_component_4()
				;
		}

#define	SPROUT_QUATERNION_NOT_EQUAL_GENERATOR \
		{ \
			return !(lhs == rhs); \
		}

		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator!=(T const& lhs, sprout::math::quaternion<T> const& rhs)
		SPROUT_QUATERNION_NOT_EQUAL_GENERATOR
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator!=(sprout::math::quaternion<T> const& lhs, T const& rhs)
		SPROUT_QUATERNION_NOT_EQUAL_GENERATOR
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator!=(sprout::complex<T> const& lhs, sprout::math::quaternion<T> const& rhs)
		SPROUT_QUATERNION_NOT_EQUAL_GENERATOR
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator!=(sprout::math::quaternion<T> const& lhs, sprout::complex<T> const& rhs)
		SPROUT_QUATERNION_NOT_EQUAL_GENERATOR
		template<typename T>
		inline SPROUT_CONSTEXPR bool
		operator!=(sprout::math::quaternion<T> const& lhs, sprout::math::quaternion<T> const& rhs)
		SPROUT_QUATERNION_NOT_EQUAL_GENERATOR

#undef	SPROUT_QUATERNION_NOT_EQUAL_GENERATOR

		//
		// operator<<
		// operator>>
		//
		template<typename T, typename Elem, typename Traits>
		inline SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>&
		operator<<(	std::basic_ostream<Elem, Traits>& lhs, sprout::math::quaternion<T> const& rhs) {
			std::basic_ostringstream<Elem, Traits> s;
			s.flags(lhs.flags());
			s.imbue(lhs.getloc());
			s.precision(lhs.precision());
			s
				<< '('
				<< rhs.R_component_1() << ','
				<< rhs.R_component_2() << ','
				<< rhs.R_component_3() << ','
				<< rhs.R_component_4()
				<< ')'
				;
			return lhs << s.str();
		}
		template<typename T, typename Elem, typename Traits>
		inline SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>&
		operator>>(std::basic_istream<Elem, Traits>& lhs, sprout::math::quaternion<T>& rhs) {
			std::ctype<Elem> const& ct = std::use_facet<std::ctype<Elem> >(lhs.getloc());
			T a = T();
			T b = T();
			T c = T();
			T d = T();
			sprout::complex<T> u = sprout::complex<T>();
			sprout::complex<T> v = sprout::complex<T>();
			Elem ch = Elem();
			char cc;
			lhs >> ch;
			if (!lhs.good()) {
				goto finish;
			}
			cc = ct.narrow(ch, char());
			if (cc == '(') {
				lhs >> ch;
				if (!lhs.good()) {
					goto finish;
				}
				cc = ct.narrow(ch, char());
				if (cc == '(') {
					lhs.putback(ch);
					lhs >> u;
					a = u.real();
					b = u.imag();
					if (!lhs.good()) {
						goto finish;
					}
					lhs >> ch;
					if (!lhs.good()) {
						goto finish;
					}
					cc = ct.narrow(ch, char());
					if (cc == ')') {
						rhs = sprout::math::quaternion<T>(a, b);
					} else if (cc == ',') {
						lhs >> v;
						c = v.real();
						d = v.imag();
						if (!lhs.good()) {
							goto finish;
						}
						lhs >> ch;
						if (!lhs.good()) {
							goto finish;
						}
						cc = ct.narrow(ch, char());
						if (cc == ')') {
							rhs = sprout::math::quaternion<T>(a, b, c, d);
						} else {
							lhs.setstate(std::ios_base::failbit);
						}
					} else {
						lhs.setstate(std::ios_base::failbit);
					}
				} else {
					lhs.putback(ch);
					lhs >> a;
					if (!lhs.good()) {
						goto finish;
					}
					lhs >> ch;
					if (!lhs.good()) {
						goto finish;
					}
					cc = ct.narrow(ch, char());
					if (cc == ')') {
						rhs = sprout::math::quaternion<T>(a);
					} else if (cc == ',') {
						lhs >> ch;
						if (!lhs.good()) {
							goto finish;
						}
						cc = ct.narrow(ch, char());
						if (cc == '(') {
							lhs.putback(ch);
							lhs >> v;
							c = v.real();
							d = v.imag();
							if (!lhs.good()) {
								goto finish;
							}
							lhs >> ch;
							if (!lhs.good()) {
								goto finish;
							}
							cc = ct.narrow(ch, char());
							if (cc == ')') {
								rhs = sprout::math::quaternion<T>(a, b, c, d);
							} else {
								lhs.setstate(std::ios_base::failbit);
							}
						} else {
							lhs.putback(ch);
							lhs >> b;
							if (!lhs.good()) {
								goto finish;
							}
							lhs >> ch;
							if (!lhs.good()) {
								goto finish;
							}
							cc = ct.narrow(ch, char());
							if (cc == ')') {
								rhs = sprout::math::quaternion<T>(a, b);
							} else if (cc == ',') {
								lhs >> c;
								if (!lhs.good()) {
									goto finish;
								}
								lhs >> ch;
								if (!lhs.good()) {
									goto finish;
								}
								cc = ct.narrow(ch, char());
								if (cc == ')') {
									rhs = sprout::math::quaternion<T>(a, b, c);
								} else if (cc == ',') {
									lhs >> d;
									if (!lhs.good()) {
										goto finish;
									}
									lhs >> ch;
									if (!lhs.good()) {
										goto finish;
									}
									cc = ct.narrow(ch, char());
									if (cc == ')') {
										rhs = sprout::math::quaternion<T>(a, b, c, d);
									} else {
										lhs.setstate(std::ios_base::failbit);
									}
								} else {
									lhs.setstate(std::ios_base::failbit);
								}
							} else {
								lhs.setstate(std::ios_base::failbit);
							}
						}
					} else {
						lhs.setstate(std::ios_base::failbit);
					}
				}
			} else {
				lhs.putback(ch);
				lhs >> a;
				if (!lhs.good()) {
					goto finish;
				}
				rhs = sprout::math::quaternion<T>(a);
			}
		finish:
			return lhs;
		}

		//
		// real
		// unreal
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T
		real(sprout::math::quaternion<T> const& q) {
			return q.real();
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		unreal(sprout::math::quaternion<T> const& q) {
			return q.unreal();
		}

		//
		// sup
		// l1
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T
		sup(sprout::math::quaternion<T> const& q) {
			return sprout::math::detail::abs_max(
				sprout::array<T, 4>{{
					q.R_component_1(),
					q.R_component_2(),
					q.R_component_3(),
					q.R_component_4()
					}}
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR T
		l1(sprout::math::quaternion<T> const& q) {
			return sprout::math::detail::abs_sum(
				sprout::array<T, 4>{{
					q.R_component_1(),
					q.R_component_2(),
					q.R_component_3(),
					q.R_component_4()
					}}
				);
		}

		//
		// abs
		//
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			abs_q_impl_3(sprout::array<T, 4> const& temp, T const& maxim) {
				return maxim * sprout::math::sqrt(sprout::math::detail::sum(sprout::math::detail::mul(temp, temp)));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			abs_q_impl_2(sprout::array<T, 4> const& temp, T const& maxim) {
				return sprout::math::detail::abs_q_impl_3(
					sprout::math::detail::mul(temp, maxim), maxim
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			abs_q_impl_1(sprout::array<T, 4> const& temp, T const& maxim) {
				return maxim == static_cast<T>(0) ? sprout::math::quaternion<T>(maxim)
					: sprout::math::detail::abs_q_impl_2(
						temp, static_cast<T>(1) / maxim
						)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			abs_q_impl(sprout::array<T, 4> const& temp) {
				return sprout::math::detail::abs_q_impl_1(
					temp, sprout::math::detail::abs_max(temp)
					);
			}
		}	// namespace detail
		template<typename T>
		inline SPROUT_CONSTEXPR T
		abs(sprout::math::quaternion<T> const& q) {
			return sprout::math::detail::abs_q_impl(
				sprout::array<T, 4>{{
					q.R_component_1(),
					q.R_component_2(),
					q.R_component_3(),
					q.R_component_4()
					}}
				);
		}

#undef	SPROUT_QUATERNION_ARRAY_LOADER

		//
		// conj
		// norm
		//
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		conj(sprout::math::quaternion<T> const& q) {
			return sprout::math::quaternion<T>(
				+q.R_component_1(),
				-q.R_component_2(),
				-q.R_component_3(),
				-q.R_component_4()
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR T
		norm(sprout::math::quaternion<T> const& q) {
			return sprout::math::real(q * sprout::math::conj(q));
		}

		//
		// spherical
		// semipolar
		// multipolar
		// cylindrospherical
		// cylindrical
		//
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			spherical_impl(T const& rho, T const& theta, T const& phi1, T const& phi2, T const& p1, T const& p2) {
				return rho * sprout::math::quaternion<T>(
					sprout::math::cos(theta) * (p2 * p1),
					sprout::math::sin(theta) * (p2 * p1),
					sprout::math::sin(phi1) * p2,
					sprout::math::sin(phi2)
					);
			}
		}	// namespace detail
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		spherical(T const& rho, T const& theta, T const& phi1, T const& phi2) {
			return sprout::math::detail::spherical_impl(
				rho, theta, phi1, phi2,
				sprout::math::cos(phi1), sprout::math::cos(phi2)
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		semipolar(T const& rho, T const& alpha, T const& theta1, T const& theta2) {
			return rho * sprout::math::quaternion<T>(
				sprout::math::cos(alpha) * sprout::math::cos(theta1),
				sprout::math::cos(alpha) * sprout::math::sin(theta1),
				sprout::math::sin(alpha) * sprout::math::cos(theta2),
				sprout::math::sin(alpha) * sprout::math::sin(theta2)
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		multipolar(T const& rho1, T const& theta1, T const& rho2, T const& theta2) {
			return sprout::math::quaternion<T>(
				rho1 * sprout::math::cos(theta1),
				rho1 * sprout::math::sin(theta1),
				rho2 * sprout::math::cos(theta2),
				rho2 * sprout::math::sin(theta2)
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		cylindrospherical(T const& t, T const& radius, T const& longitude, T const& latitude) {
			return sprout::math::quaternion<T>(
				t,
				radius * sprout::math::cos(longitude) * sprout::math::cos(latitude),
				radius * sprout::math::sin(longitude) * sprout::math::cos(latitude),
				radius * sprout::math::sin(latitude)
				);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		cylindrical(T const& r, T const& angle, T const& h1, T const& h2) {
			return sprout::math::quaternion<T>(
				r * sprout::math::cos(angle),
				r * sprout::math::sin(angle),
				h1,
				h2
				);
		}

		//
		// exp
		//
		// !!!
//		namespace detail {
//			template<typename T>
//			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//			exp_impl_1(sprout::math::quaternion<T> const& q, T const& z, T const& w) {
//				return sprout::math::exp(sprout::math::real(q)) * sprout::math::quaternion<T>(
//					sprout::math::cos(z),
//					w * q.R_component_2(),
//					w * q.R_component_3(),
//					w * q.R_component_4()
//					);
//			}
//			template<typename T>
//			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//			exp_impl(sprout::math::quaternion<T> const& q, T const& z) {
//				return sprout::math::detail::exp_impl_1(
//					q, z,
//					sprout::math::sinc_pi(z)
//					);
//			}
//		}	// namespace detail
//		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//		exp(sprout::math::quaternion<T> const& q) {
//			return sprout::math::detail::exp_impl(
//				q,
//				sprout::math::abs(sprout::math::unreal(q))
//				);
//		}

		//
		// cos
		// sin
		// tan
		//
		// !!!
//		namespace detail {
//			template<typename T>
//			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//			cos_impl_1(sprout::math::quaternion<T> const& q, T const& z, T const& w) {
//				return sprout::math::quaternion<T>(
//					sprout::math::cos(q.real()) * sprout::math::cosh(z),
//					w * q.R_component_2(),
//					w * q.R_component_3(),
//					w * q.R_component_4()
//					);
//			}
//			template<typename T>
//			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//			cos_impl(sprout::math::quaternion<T> const& q, T const& z) {
//				return sprout::math::detail::cos_impl_1(
//					q, z,
//					-sprout::math::sin(q.real()) * sprout::math::sinhc_pi(z)
//					);
//			}
//		}	// namespace detail
//		template<typename T>
//		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//		cos(sprout::math::quaternion<T> const& q) {
//			return sprout::math::detail::cos_impl(
//				q,
//				sprout::math::abs(sprout::math::unreal(q))
//				);
//		}
//		namespace detail {
//			template<typename T>
//			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//			sin_impl_1(sprout::math::quaternion<T> const& q, T const& z, T const& w) {
//				return sprout::math::quaternion<T>(
//					sprout::math::sin(q.real()) * sprout::math::cosh(z),
//					w * q.R_component_2(),
//					w * q.R_component_3(),
//					w * q.R_component_4()
//					);
//			}
//			template<typename T>
//			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//			sin_impl(sprout::math::quaternion<T> const& q, T const& z) {
//				return sprout::math::detail::sin_impl_1(
//					q, z,
//					+sprout::math::cos(q.real()) * sprout::math::sinhc_pi(z)
//					);
//			}
//		}	// namespace detail
//		template<typename T>
//		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//		sin(sprout::math::quaternion<T> const& q) {
//			return sprout::math::detail::sin_impl(
//				q,
//				sprout::math::abs(sprout::math::unreal(q))
//				);
//		}
//		template<typename T>
//		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//		tan(sprout::math::quaternion<T> const& q) {
//			return sprout::math::sin(q) / sprout::math::cos(q);
//		}

		//
		// cosh
		// sinh
		// tanh
		//
		// !!!
//		template<typename T>
//		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//		cosh(sprout::math::quaternion<T> const& q) {
//			return (sprout::math::exp(+q) + sprout::math::exp(-q)) / static_cast<T>(2);
//		}
//		template<typename T>
//		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//		sinh(sprout::math::quaternion<T> const& q) {
//			return (sprout::math::exp(+q) - sprout::math::exp(-q)) / static_cast<T>(2);
//		}
//		template<typename T>
//		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
//		tanh(sprout::math::quaternion<T> const& q) {
//			return sprout::math::sinh(q) / sprout::math::cosh(q);
//		}

		//
		// pow
		//
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
			pow_q_impl(sprout::math::quaternion<T> const& q, int n, int	m, sprout::math::quaternion<T> const& result) {
				return n != m << 1 ? result * result * q
					: result * result
					;
			}
		}	// namespace detail
		template<typename T>
		inline SPROUT_CONSTEXPR sprout::math::quaternion<T>
		pow(sprout::math::quaternion<T> const& q, int n) {
			return n > 1 ? sprout::math::detail::pow_q_impl(
					q, n, n >> 1, sprout::math::pow(q, n >> 1)
					)
				: n == 1 ? q
				: n == 0 ? sprout::math::quaternion<T>(static_cast<T>(1))
				: sprout::math::pow(sprout::math::quaternion<T>(static_cast<T>(1)) / q, -n)
				;
		}
	}	// namespace math

	using sprout::math::quaternion;
	using sprout::math::real;
	using sprout::math::unreal;
	using sprout::math::sup;
	using sprout::math::l1;
	using sprout::math::abs;
	using sprout::math::conj;
	using sprout::math::norm;
	using sprout::math::spherical;
	using sprout::math::semipolar;
	using sprout::math::multipolar;
	using sprout::math::cylindrospherical;
	using sprout::math::cylindrical;
//	using sprout::math::exp;
//	using sprout::math::cos;
//	using sprout::math::sin;
//	using sprout::math::tan;
//	using sprout::math::cosh;
//	using sprout::math::sinh;
//	using sprout::math::tanh;
	using sprout::math::pow;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_QUATERNION_HPP
