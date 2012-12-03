#ifndef SPROUT_COMPOST_FORMATS_AS_IMAG_HPP
#define SPROUT_COMPOST_FORMATS_AS_IMAG_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/complex.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/adaptor/transformed.hpp>

namespace sprout {
	namespace compost {
		//
		// to_imag_value
		//
		struct to_imag_value {
		public:
			template<typename Complex>
			SPROUT_CONSTEXPR decltype(imag(std::declval<Complex const&>())) operator()(Complex const& x) const {
				return imag(x);
			}
		};

		namespace formats {
			//
			// as_imag_forwarder
			//
			class as_imag_forwarder {};

			//
			// as_imag
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::formats::as_imag_forwarder as_imag{};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::formats::as_imag_forwarder const& rhs)
			-> decltype(
				sprout::forward<Range>(lhs)
					| sprout::adaptors::transformed(sprout::compost::to_imag_value())
				)
			{
				return sprout::forward<Range>(lhs)
					| sprout::adaptors::transformed(sprout::compost::to_imag_value())
					;
			}
		}	// namespace formats

		using sprout::compost::formats::as_imag;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_FORMATS_AS_IMAG_HPP
