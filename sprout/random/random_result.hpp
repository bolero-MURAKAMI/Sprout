#ifndef SPROUT_RANDOM_RANDOM_RESULT_HPP
#define SPROUT_RANDOM_RANDOM_RESULT_HPP

#include <cstddef>
#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>

namespace sprout {
	namespace random {
		//
		// random_result
		//
		template<typename Engine, typename Distribution = void, typename Enable = void>
		class random_result;

		template<typename Engine, typename Distribution>
		class random_result<
			Engine,
			Distribution,
			typename std::enable_if<!std::is_same<Distribution, void>::value>::type
		>
			: public std::iterator<
				std::input_iterator_tag,
				typename Distribution::result_type,
				std::ptrdiff_t,
				typename Distribution::result_type const*,
				typename Distribution::result_type const&
			>
		{
		public:
			typedef Engine engine_type;
			typedef Distribution distribution_type;
			typedef typename distribution_type::result_type result_type;
		private:
			typedef std::iterator<
				std::input_iterator_tag,
				result_type,
				std::ptrdiff_t,
				result_type const*,
				result_type const&
			> base_type;
		public:
			typedef typename base_type::iterator_category iterator_category;
			typedef typename base_type::value_type value_type;
			typedef typename base_type::difference_type difference_type;
			typedef typename base_type::pointer pointer;
			typedef typename base_type::reference reference;
		private:
			result_type result_;
			engine_type engine_;
			distribution_type distribution_;
		public:
			SPROUT_CONSTEXPR random_result()
				: result_()
				, engine_()
				, distribution_()
			{}
			SPROUT_CONSTEXPR random_result(
				result_type result,
				engine_type const& engine,
				distribution_type const& distribution
				)
				: result_(result)
				, engine_(engine)
				, distribution_(distribution)
			{}
			SPROUT_CONSTEXPR operator result_type() const {
				return result_;
			}
			SPROUT_CONSTEXPR random_result operator()() const {
				return distribution_(engine_);
			}
			result_type& result() {
				return result_;
			}
			SPROUT_CONSTEXPR result_type const& result() const {
				return result_;
			}
			engine_type& engine() {
				return engine_;
			}
			SPROUT_CONSTEXPR engine_type const& engine() const {
				return engine_;
			}
			distribution_type& distribution() {
				return distribution_;
			}
			SPROUT_CONSTEXPR distribution_type const& distribution() const {
				return distribution_;
			}
			SPROUT_CONSTEXPR result_type min() const {
				return distribution_.min();
			}
			SPROUT_CONSTEXPR result_type max() const {
				return distribution_.max();
			}
			void swap(random_result& other) {
				using std::swap;
				swap(result_, other.result_);
				swap(engine_, other.engine_);
				swap(distribution_, other.distribution_);
			}
			friend SPROUT_CONSTEXPR bool operator==(random_result const& lhs, random_result const& rhs) {
				return lhs.result_ == rhs.result_
					&& lhs.engine_ == rhs.engine_
					&& lhs.distribution_ == rhs.distribution_
					;
			}
			friend SPROUT_CONSTEXPR bool operator!=(random_result const& lhs, random_result const& rhs) {
				return !(lhs == rhs);
			}
			SPROUT_CONSTEXPR reference operator*() const {
				return result_;
			}
			SPROUT_CONSTEXPR pointer operator->() const {
				return &result_;
			}
			random_result& operator++() {
				random_result temp((*this)());
				temp.swap(*this);
				return *this;
			}
			random_result operator++(int) {
				random_result result(*this);
				++*this;
				return result;
			}
		};
		template<typename Engine, typename Distribution>
		class random_result<
			Engine,
			Distribution,
			typename std::enable_if<std::is_same<Distribution, void>::value>::type
		>
			: public std::iterator<
				std::input_iterator_tag,
				typename Engine::result_type,
				std::ptrdiff_t,
				typename Engine::result_type const*,
				typename Engine::result_type const&
			>
		{
		public:
			typedef Engine engine_type;
			typedef typename engine_type::result_type result_type;
		private:
			typedef std::iterator<
				std::input_iterator_tag,
				result_type,
				std::ptrdiff_t,
				result_type const*,
				result_type const&
			> base_type;
		public:
			typedef typename base_type::iterator_category iterator_category;
			typedef typename base_type::value_type value_type;
			typedef typename base_type::difference_type difference_type;
			typedef typename base_type::pointer pointer;
			typedef typename base_type::reference reference;
		private:
			result_type result_;
			engine_type engine_;
		public:
			SPROUT_CONSTEXPR random_result()
				: result_()
				, engine_()
			{}
			SPROUT_CONSTEXPR random_result(
				result_type result,
				engine_type const& engine
				)
				: result_(result)
				, engine_(engine)
			{}
			SPROUT_CONSTEXPR operator result_type() const {
				return result_;
			}
			SPROUT_CONSTEXPR random_result operator()() const {
				return engine_();
			}
			result_type& result() {
				return result_;
			}
			SPROUT_CONSTEXPR result_type const& result() const {
				return result_;
			}
			engine_type& engine() {
				return engine_;
			}
			SPROUT_CONSTEXPR engine_type const& engine() const {
				return engine_;
			}
			SPROUT_CONSTEXPR result_type min() const {
				return engine_.min();
			}
			SPROUT_CONSTEXPR result_type max() const {
				return engine_.max();
			}
			friend SPROUT_CONSTEXPR bool operator==(random_result const& lhs, random_result const& rhs) {
				return lhs.result_ == rhs.result_
					&& lhs.engine_ == rhs.engine_
					;
			}
			friend SPROUT_CONSTEXPR bool operator!=(random_result const& lhs, random_result const& rhs) {
				return !(lhs == rhs);
			}
			void swap(random_result& other) {
				using std::swap;
				swap(result_, other.result_);
				swap(engine_, other.engine_);
			}
			SPROUT_CONSTEXPR reference operator*() const {
				return result_;
			}
			SPROUT_CONSTEXPR pointer operator->() const {
				return &result_;
			}
			random_result& operator++() {
				random_result temp((*this)());
				temp.swap(*this);
				return *this;
			}
			random_result operator++(int) {
				random_result result(*this);
				random_result temp((*this)());
				temp.swap(*this);
				return result;
			}
		};

		//
		// swap
		//
		template<typename Engine, typename Distribution>
		void swap(
			sprout::random::random_result<Engine, Distribution>& lhs,
			sprout::random::random_result<Engine, Distribution>& rhs
			)
		{
			lhs.swap(rhs);
		}

		//
		// next
		//
		template<typename Engine, typename Distribution>
		SPROUT_CONSTEXPR sprout::random::random_result<Engine, Distribution> next(
			sprout::random::random_result<Engine, Distribution> const& it
			)
		{
			return it();
		}
	}	// namespace random

	using sprout::random::random_result;
}	// namespace sprout

#endif // #ifndef SPROUT_RANDOM_RANDOM_RESULT_HPP
