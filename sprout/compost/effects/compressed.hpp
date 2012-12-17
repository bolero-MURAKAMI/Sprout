#ifndef SPROUT_COMPOST_EFFECTS_COMPRESEDS_HPP
#define SPROUT_COMPOST_EFFECTS_COMPRESEDS_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/adaptor/transformed.hpp>

namespace sprout {
	namespace compost {
		namespace detail {
			template<typename Value, typename T>
			SPROUT_CONSTEXPR T
			compress_value(T const& x, Value const& threshold, Value const& ratio, Value const& gain) {
				return (x > threshold ? threshold + (x - threshold) * ratio
					: x < -threshold ? -threshold + (x + threshold) * ratio
					: x
					) * gain
					;
			}
		}	// namespace detail
		//
		// compress_value
		//
		template<typename Value, typename T = void>
		struct compress_value {
		public:
			typedef Value value_type;
			typedef T argument_type;
			typedef T result_type;
		private:
			value_type threshold_;
			value_type ratio_;
			value_type gain_;
		public:
			SPROUT_CONSTEXPR compress_value(Value const& threshold, Value const& ratio)
				: threshold_(threshold), ratio_(ratio), gain_(1 / (threshold + (1 - threshold) * ratio))
			{}
			SPROUT_CONSTEXPR result_type
			operator()(T const& x) const {
				return sprout::compost::detail::compress_value(x, threshold_, ratio_, gain_);
			}
		};
		template<typename Value>
		struct compress_value<Value, void> {
		public:
			typedef Value value_type;
		private:
			value_type threshold_;
			value_type ratio_;
			value_type gain_;
		public:
			SPROUT_CONSTEXPR compress_value(Value const& threshold, Value const& ratio)
				: threshold_(threshold), ratio_(ratio), gain_(1 / (threshold + (1 - threshold) * ratio))
			{}
			template<typename T>
			SPROUT_CONSTEXPR T
			operator()(T const& x) const {
				return sprout::compost::detail::compress_value(x, threshold_, ratio_, gain_);
			}
		};

		namespace effects {
			//
			// compress_holder
			//
			template<typename T>
			class compress_holder {
			public:
				typedef T value_type;
			private:
				value_type threshold_;
				value_type ratio_;
			public:
				compress_holder() = default;
				compress_holder(compress_holder const&) = default;
				SPROUT_CONSTEXPR compress_holder(value_type const& threshold, value_type const& ratio)
					: threshold_(threshold), ratio_(ratio)
				{}
				SPROUT_CONSTEXPR value_type const& threshold() const {
					return threshold_;
				}
				SPROUT_CONSTEXPR value_type const& ratio() const {
					return ratio_;
				}
			};


			//
			// compressed_forwarder
			//
			class compressed_forwarder {
			public:
				template<typename T>
				SPROUT_CONSTEXPR sprout::compost::effects::compress_holder<T>
				operator()(T const& threshold, T const& ratio) {
					return sprout::compost::effects::compress_holder<T>(threshold, ratio);
				}
			};

			//
			// compressed
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::effects::compressed_forwarder compressed = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename T>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::compress_holder<T> const& rhs)
			-> decltype(
				sprout::forward<Range>(lhs)
					| sprout::adaptors::transformed(sprout::compost::compress_value<T>(rhs.threshold(), rhs.ratio()))
				)
			{
				return sprout::forward<Range>(lhs)
					| sprout::adaptors::transformed(sprout::compost::compress_value<T>(rhs.threshold(), rhs.ratio()))
					;
			}
		}	// namespace effects

		using sprout::compost::effects::compressed;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_COMPRESEDS_HPP
