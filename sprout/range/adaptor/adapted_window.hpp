#ifndef SPROUT_RANGE_ADAPTOR_ADAPTED_WINDOW_HPP
#define SPROUT_RANGE_ADAPTOR_ADAPTED_WINDOW_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/arithmetic_promote.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/range/adaptor/taken.hpp>
#include <sprout/range/adaptor/dropped.hpp>
#include <sprout/range/adaptor/window.hpp>
#include <sprout/range/adaptor/jointed.hpp>

namespace sprout {
	namespace adaptors {
		//
		// adapt_window_holder
		//
		template<typename Adaptor, typename Difference1, typename Difference2 = void>
		class adapt_window_holder {
		public:
			typedef Adaptor adaptor_type;
			typedef typename sprout::arithmetic_promote<Difference1, Difference2>::type difference_type;
		private:
			adaptor_type adaptor_;
			difference_type to_first_;
			difference_type to_last_;
		public:
			explicit SPROUT_CONSTEXPR adapt_window_holder(adaptor_type const& adaptor, difference_type to_first, difference_type to_last)
				: adaptor_(adaptor), to_first_(to_first), to_last_(to_last)
			{}
			SPROUT_CONSTEXPR adaptor_type const& adaptor() const {
				return adaptor_;
			}
			SPROUT_CONSTEXPR difference_type const& to_first() const {
				return to_first_;
			}
			SPROUT_CONSTEXPR difference_type const& to_last() const {
				return to_last_;
			}
		};
		template<typename Adaptor, typename Difference>
		class adapt_window_holder<Adaptor, Difference, void> {
		public:
			typedef Adaptor adaptor_type;
			typedef Difference difference_type;
		private:
			adaptor_type adaptor_;
			difference_type to_first_;
		public:
			explicit SPROUT_CONSTEXPR adapt_window_holder(adaptor_type const& adaptor, difference_type to_first)
				: adaptor_(adaptor), to_first_(to_first)
			{}
			SPROUT_CONSTEXPR adaptor_type const& adaptor() const {
				return adaptor_;
			}
			SPROUT_CONSTEXPR difference_type const& to_first() const {
				return to_first_;
			}
		};

		//
		// adapted_window_forwarder
		//
		class adapted_window_forwarder {
		public:
			template<typename Adaptor, typename Difference1, typename Difference2>
			SPROUT_CONSTEXPR sprout::adaptors::adapt_window_holder<Adaptor, Difference1, Difference2>
			operator()(Adaptor const& adaptor, Difference1 to_first, Difference2 to_last) const {
				return sprout::adaptors::adapt_window_holder<Adaptor, Difference1, Difference2>(adaptor, to_first, to_last);
			}
			template<typename Adaptor, typename Difference>
			SPROUT_CONSTEXPR sprout::adaptors::adapt_window_holder<Adaptor, Difference>
			operator()(Adaptor const& adaptor, Difference to_first) const {
				return sprout::adaptors::adapt_window_holder<Adaptor, Difference>(adaptor, to_first);
			}
		};

		//
		// adapted_window
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::adapted_window_forwarder adapted_window = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Adaptor, typename Difference1, typename Difference2>
		inline SPROUT_CONSTEXPR auto
		operator|(Range&& lhs, sprout::adaptors::adapt_window_holder<Adaptor, Difference1, Difference2> const& rhs)
		-> decltype(
			sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::taken(rhs.to_first())
				| sprout::adaptors::jointed(sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::window(rhs.to_first(), rhs.to_last()) | rhs.adaptor())
				| sprout::adaptors::jointed(sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::dropped(rhs.to_last()))
			)
		{
			return sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::taken(rhs.to_first())
				| sprout::adaptors::jointed(sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::window(rhs.to_first(), rhs.to_last()) | rhs.adaptor())
				| sprout::adaptors::jointed(sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::dropped(rhs.to_last()))
				;
		}
		template<typename Range, typename Adaptor, typename Difference>
		inline SPROUT_CONSTEXPR auto
		operator|(Range&& lhs, sprout::adaptors::adapt_window_holder<Adaptor, Difference> const& rhs)
		-> decltype(
			sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::taken(rhs.to_first())
				| sprout::adaptors::jointed(sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::window(rhs.to_first()) | rhs.adaptor())
			)
		{
			return sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::taken(rhs.to_first())
				| sprout::adaptors::jointed(sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::window(rhs.to_first()) | rhs.adaptor())
				;
		}
	}	// namespace adaptors
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_ADAPTED_WINDOW_HPP
