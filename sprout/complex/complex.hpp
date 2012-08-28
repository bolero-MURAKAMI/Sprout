#ifndef SPROUT_COMPLEX_COMPLEX_HPP
#define SPROUT_COMPLEX_COMPLEX_HPP

#include <sprout/config.hpp>

namespace sprout {
	template<typename T>
	class complex;

	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR T complex_norm(sprout::complex<T> const& x) {
			return x.real() * x.real() + x.imag() * x.imag();
		}
	}	// namespace detail

	//
	// complex
	//
	template<typename T>
	class complex {
	public:
		typedef T value_type;
	private:
		T re_;
		T im_;
	public:
		SPROUT_CONSTEXPR complex(T const& re = T(), T const& im = T())
			: re_(re)
			, im_(im)
		{}
		SPROUT_CONSTEXPR complex(complex const&) = default;
		template<typename X>
		SPROUT_CONSTEXPR complex(complex<X> const& other)
			: re_(other.real())
			, im_(other.imag())
		{}
		SPROUT_CONSTEXPR T real() const {
			return re_;
		}
		void real(T re) {
			re_ = re;
		}
		SPROUT_CONSTEXPR T imag() const{
			return im_;
		}
		void imag(T im) {
			im_ = im;
		}
		complex<T>& operator=(T const& rhs) {
			re_ = rhs;
			im_ = T();
			return *this;
		}
		complex<T>& operator+=(T const& rhs) {
			re_ += rhs;
			return *this;
		}
		complex<T>& operator-=(T const& rhs) {
			re_ -= rhs;
			return *this;
		}
		complex<T>& operator*=(T const& rhs) {
			re_ *= rhs;
			im_ *= rhs;
			return *this;
		}
		complex<T>& operator/=(T const& rhs) {
			re_ /= rhs;
			im_ /= rhs;
			return *this;
		}
		complex& operator=(complex const&) = default;
		template<typename X>
		complex<T>& operator=(complex<X> const& rhs) {
			re_ = rhs.real();
			im_ = rhs.imag();
			return *this;
		}
		template<typename X>
		complex<T>& operator+=(complex<X> const& rhs) {
			re_ += rhs.real();
			im_ += rhs.imag();
			return *this;
		}
		template<typename X>
		complex<T>& operator-=(complex<X> const& rhs) {
			re_ -= rhs.real();
			im_ -= rhs.imag();
			return *this;
		}
		template<typename X>
		complex<T>& operator*=(complex<X> const& rhs) {
			return *this = complex<T>(
				re_ * rhs.real() - im_ * rhs.imag(),
				re_ * rhs.imag() + im_ * rhs.real()
				);
		}
		template<typename X>
		complex<T>& operator/=(complex<X> const& rhs) {
			T n = sprout::detail::complex_norm(rhs);
			return *this = complex<T>(
				(re_ * rhs.real() + im_ * rhs.imag()) / n,
				(im_ * rhs.real() - re_ * rhs.imag()) / n
				);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_COMPLEX_HPP
