#ifndef SPROUT_COMPOST_EFFECTS_SYNTHESIZED_HPP
#define SPROUT_COMPOST_EFFECTS_SYNTHESIZED_HPP

#include <sprout/config.hpp>
#include <sprout/functional/plus.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/value_holder.hpp>
#include <sprout/range/adaptor/transformed.hpp>

namespace sprout {
	namespace compost {
		namespace effects {
			//
			// synthesize_holder
			//
			template<typename RRange>
			class synthesize_holder {
			public:
				typedef RRange range2_type;
			private:
				sprout::value_holder<range2_type&> range_;
			public:
				synthesize_holder() = default;
				synthesize_holder(synthesize_holder const&) = default;
				explicit SPROUT_CONSTEXPR synthesize_holder(range2_type& range)
					: range_(range)
				{}
				SPROUT_CONSTEXPR range2_type& range() const {
					return range_;
				}
			};

			//
			// synthesized_forwarder
			//
			class synthesized_forwarder {
			public:
				template<typename RRange>
				SPROUT_CONSTEXPR sprout::compost::effects::synthesize_holder<
					typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
				>
				operator()(RRange&& range) {
					return sprout::compost::effects::synthesize_holder<
						typename std::remove_reference<typename sprout::lvalue_reference<RRange>::type>::type
					>(
						sprout::lvalue_forward<RRange>(range)
						);
				}
			};

			//
			// synthesized
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::effects::synthesized_forwarder synthesized{};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename T>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::synthesize_holder<T> const& rhs)
			-> decltype(
				sprout::forward<Range>(lhs)
					| sprout::adaptors::transformed(rhs.range(), sprout::plus<>())
				)
			{
				return sprout::forward<Range>(lhs)
					| sprout::adaptors::transformed(rhs.range(), sprout::plus<>())
					;
			}
		}	// namespace effects
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_SYNTHESIZED_HPP
