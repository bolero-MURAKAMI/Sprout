#ifndef SPROUT_RANGE_ADAPTOR_ADAPTED_OFFSET_HPP
#define SPROUT_RANGE_ADAPTOR_ADAPTED_OFFSET_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/arithmetic_promote.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/range/adaptor/taken.hpp>
#include <sprout/range/adaptor/taken_end.hpp>
#include <sprout/range/adaptor/offset.hpp>
#include <sprout/range/adaptor/jointed.hpp>

namespace sprout {
	namespace adaptors {
		//
		// adapt_offset_holder
		//
		template<typename Adaptor, typename Difference1, typename Difference2 = void>
		class adapt_offset_holder {
		public:
			typedef Adaptor adaptor_type;
			typedef typename sprout::arithmetic_promote<Difference1, Difference2>::type difference_type;
		private:
			adaptor_type adaptor_;
			difference_type from_begin_;
			difference_type from_end_;
		public:
			explicit SPROUT_CONSTEXPR adapt_offset_holder(adaptor_type const& adaptor, difference_type from_begin, difference_type from_end)
				: adaptor_(adaptor), from_begin_(from_begin), from_end_(from_end)
			{}
			SPROUT_CONSTEXPR adaptor_type const& adaptor() const {
				return adaptor_;
			}
			SPROUT_CONSTEXPR difference_type const& from_begin() const {
				return from_begin_;
			}
			SPROUT_CONSTEXPR difference_type const& from_end() const {
				return from_end_;
			}
		};
		template<typename Adaptor, typename Difference>
		class adapt_offset_holder<Adaptor, Difference, void> {
		public:
			typedef Adaptor adaptor_type;
			typedef Difference difference_type;
		private:
			adaptor_type adaptor_;
			difference_type from_begin_;
		public:
			explicit SPROUT_CONSTEXPR adapt_offset_holder(adaptor_type const& adaptor, difference_type from_begin)
				: adaptor_(adaptor), from_begin_(from_begin)
			{}
			SPROUT_CONSTEXPR adaptor_type const& adaptor() const {
				return adaptor_;
			}
			SPROUT_CONSTEXPR difference_type const& from_begin() const {
				return from_begin_;
			}
		};

		//
		// adapted_offset_forwarder
		//
		class adapted_offset_forwarder {
		public:
			template<typename Adaptor, typename Difference1, typename Difference2>
			SPROUT_CONSTEXPR sprout::adaptors::adapt_offset_holder<Adaptor, Difference1, Difference2>
			operator()(Adaptor const& adaptor, Difference1 from_begin, Difference2 from_end) {
				return sprout::adaptors::adapt_offset_holder<Adaptor, Difference1, Difference2>(adaptor, from_begin, from_end);
			}
			template<typename Adaptor, typename Difference>
			SPROUT_CONSTEXPR sprout::adaptors::adapt_offset_holder<Adaptor, Difference>
			operator()(Adaptor const& adaptor, Difference from_begin) {
				return sprout::adaptors::adapt_offset_holder<Adaptor, Difference>(adaptor, from_begin);
			}
		};

		//
		// adapted_offset
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::adapted_offset_forwarder adapted_offset = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Adaptor, typename Difference1, typename Difference2>
		inline SPROUT_CONSTEXPR auto
		operator|(Range&& lhs, sprout::adaptors::adapt_offset_holder<Adaptor, Difference1, Difference2> const& rhs)
		-> decltype(
			sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::taken(rhs.from_begin())
				| sprout::adaptors::jointed(sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::offset(rhs.from_begin(), rhs.from_end()) | rhs.adaptor())
				| sprout::adaptors::jointed(sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::taken_end(rhs.from_end()))
			)
		{
			return sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::taken(rhs.from_begin())
				| sprout::adaptors::jointed(sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::offset(rhs.from_begin(), rhs.from_end()) | rhs.adaptor())
				| sprout::adaptors::jointed(sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::taken_end(rhs.from_end()))
				;
		}
		template<typename Range, typename Adaptor, typename Difference>
		inline SPROUT_CONSTEXPR auto
		operator|(Range&& lhs, sprout::adaptors::adapt_offset_holder<Adaptor, Difference> const& rhs)
		-> decltype(
			sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::taken(rhs.from_begin())
				| sprout::adaptors::jointed(sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::offset(rhs.from_begin()) | rhs.adaptor())
			)
		{
			return sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::taken(rhs.from_begin())
				| sprout::adaptors::jointed(sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::offset(rhs.from_begin()) | rhs.adaptor())
				;
		}
	}	// namespace adaptors
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_ADAPTED_OFFSET_HPP
