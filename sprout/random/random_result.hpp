/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_RANDOM_RESULT_HPP
#define SPROUT_RANDOM_RANDOM_RESULT_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/generator/functions.hpp>
#include <sprout/random/random_result_fwd.hpp>
#include <sprout/random/variate_generator.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/detail/nil_base.hpp>

namespace sprout {
	namespace random {
		//
		// random_result
		//
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
			typedef sprout::random::variate_generator<engine_type, distribution_type> generator_type;
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
			generator_type generator_;
		public:
			SPROUT_CONSTEXPR random_result()
				: result_(), generator_()
			{}
			random_result(random_result const&) = default;
			SPROUT_CONSTEXPR random_result(
				result_type result,
				engine_type const& engine, distribution_type const& distribution
				)
				: result_(result)
				, generator_(engine, distribution)
			{}
			SPROUT_CONSTEXPR random_result operator()() const {
				return generator_();
			}
			SPROUT_CXX14_CONSTEXPR result_type& generated_value() SPROUT_NOEXCEPT {
				return result_;
			}
			SPROUT_CONSTEXPR result_type const& generated_value() const SPROUT_NOEXCEPT {
				return result_;
			}
			SPROUT_CXX14_CONSTEXPR generator_type& next_generator() SPROUT_NOEXCEPT {
				return generator_;
			}
			SPROUT_CONSTEXPR generator_type const& next_generator() const SPROUT_NOEXCEPT {
				return generator_;
			}
			SPROUT_CXX14_CONSTEXPR result_type& result() SPROUT_NOEXCEPT {
				return result_;
			}
			SPROUT_CONSTEXPR result_type const& result() const SPROUT_NOEXCEPT {
				return result_;
			}
			SPROUT_CXX14_CONSTEXPR generator_type& next() SPROUT_NOEXCEPT {
				return generator_;
			}
			SPROUT_CONSTEXPR generator_type const& next() const SPROUT_NOEXCEPT {
				return generator_;
			}
			SPROUT_CXX14_CONSTEXPR engine_type& engine() SPROUT_NOEXCEPT {
				return generator_.engine();
			}
			SPROUT_CONSTEXPR engine_type const& engine() const SPROUT_NOEXCEPT {
				return generator_.engine();
			}
			SPROUT_CXX14_CONSTEXPR distribution_type& distribution() SPROUT_NOEXCEPT {
				return generator_.distribution();
			}
			SPROUT_CONSTEXPR distribution_type const& distribution() const SPROUT_NOEXCEPT {
				return generator_.distribution();
			}
			SPROUT_CXX14_CONSTEXPR operator result_type&() SPROUT_NOEXCEPT {
				return result_;
			}
			SPROUT_CONSTEXPR operator result_type const&() const SPROUT_NOEXCEPT {
				return result_;
			}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return distribution().min();
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return distribution().max();
			}
			SPROUT_CXX14_CONSTEXPR void swap(random_result& other)
			SPROUT_NOEXCEPT_IF(
				SPROUT_NOEXCEPT_EXPR(sprout::swap(result_, other.result_))
				&& SPROUT_NOEXCEPT_EXPR(sprout::swap(generator_, other.generator_))
				)
			{
				sprout::swap(result_, other.result_);
				sprout::swap(generator_, other.generator_);
			}
			friend SPROUT_CONSTEXPR bool operator==(random_result const& lhs, random_result const& rhs) SPROUT_NOEXCEPT {
				return lhs.result_ == rhs.result_
					&& lhs.generator_ == rhs.generator_
					;
			}
			friend SPROUT_CONSTEXPR bool operator!=(random_result const& lhs, random_result const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
			SPROUT_CONSTEXPR reference operator*() const SPROUT_NOEXCEPT {
				return result_;
			}
			SPROUT_CONSTEXPR pointer operator->() const SPROUT_NOEXCEPT {
				return &result_;
			}
			SPROUT_CXX14_CONSTEXPR random_result& operator++() {
				random_result temp((*this)());
				temp.swap(*this);
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR random_result operator++(int) {
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
			typedef engine_type generator_type;
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
			generator_type generator_;
		public:
			SPROUT_CONSTEXPR random_result()
				: result_(), generator_()
			{}
			random_result(random_result const&) = default;
			SPROUT_CONSTEXPR random_result(result_type result, engine_type const& engine)
				: result_(result), generator_(engine)
			{}
			SPROUT_CONSTEXPR random_result operator()() const {
				return generator_();
			}
			SPROUT_CXX14_CONSTEXPR result_type& generated_value() SPROUT_NOEXCEPT {
				return result_;
			}
			SPROUT_CONSTEXPR result_type const& generated_value() const SPROUT_NOEXCEPT {
				return result_;
			}
			SPROUT_CXX14_CONSTEXPR generator_type& next_generator() SPROUT_NOEXCEPT {
				return generator_;
			}
			SPROUT_CONSTEXPR generator_type const& next_generator() const SPROUT_NOEXCEPT {
				return generator_;
			}
			SPROUT_CXX14_CONSTEXPR result_type& result() SPROUT_NOEXCEPT {
				return result_;
			}
			SPROUT_CONSTEXPR result_type const& result() const SPROUT_NOEXCEPT {
				return result_;
			}
			SPROUT_CXX14_CONSTEXPR generator_type& next() SPROUT_NOEXCEPT {
				return generator_;
			}
			SPROUT_CONSTEXPR generator_type const& next() const SPROUT_NOEXCEPT {
				return generator_;
			}
			SPROUT_CXX14_CONSTEXPR engine_type& engine() SPROUT_NOEXCEPT {
				return generator_;
			}
			SPROUT_CONSTEXPR engine_type const& engine() const SPROUT_NOEXCEPT {
				return generator_;
			}
			SPROUT_CXX14_CONSTEXPR operator result_type&() SPROUT_NOEXCEPT {
				return result_;
			}
			SPROUT_CONSTEXPR operator result_type const&() const SPROUT_NOEXCEPT {
				return result_;
			}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return engine().min();
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return engine().max();
			}
			friend SPROUT_CONSTEXPR bool operator==(random_result const& lhs, random_result const& rhs) SPROUT_NOEXCEPT {
				return lhs.result_ == rhs.result_
					&& lhs.generator_ == rhs.generator_
					;
			}
			friend SPROUT_CONSTEXPR bool operator!=(random_result const& lhs, random_result const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
			SPROUT_CXX14_CONSTEXPR void swap(random_result& other)
			SPROUT_NOEXCEPT_IF(
				SPROUT_NOEXCEPT_EXPR(sprout::swap(result_, other.result_))
				&& SPROUT_NOEXCEPT_EXPR(sprout::swap(generator_, other.generator_))
				)
			{
				sprout::swap(result_, other.result_);
				sprout::swap(generator_, other.generator_);
			}
			SPROUT_CONSTEXPR reference operator*() const SPROUT_NOEXCEPT {
				return result_;
			}
			SPROUT_CONSTEXPR pointer operator->() const SPROUT_NOEXCEPT {
				return &result_;
			}
			SPROUT_CXX14_CONSTEXPR random_result& operator++() {
				random_result temp((*this)());
				temp.swap(*this);
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR random_result operator++(int) {
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
		inline SPROUT_CXX14_CONSTEXPR void
		swap(sprout::random::random_result<Engine, Distribution>& lhs, sprout::random::random_result<Engine, Distribution>& rhs)
		SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
		{
			lhs.swap(rhs);
		}

		//
		// iterator_next
		//
		template<typename Engine, typename Distribution>
		inline SPROUT_CONSTEXPR sprout::random::random_result<Engine, Distribution>
		iterator_next(sprout::random::random_result<Engine, Distribution> const& it) {
			return it();
		}
	}	// namespace random

	namespace tuples {
		namespace detail {
			template<std::size_t I, typename T>
			struct tuple_element_impl;
			template<std::size_t I, typename Engine, typename Distribution>
			struct tuple_element_impl<I, sprout::random::random_result<Engine, Distribution> >
				: public sprout::detail::nil_base
			{};
			template<typename Engine, typename Distribution>
			struct tuple_element_impl<0, sprout::random::random_result<Engine, Distribution> >
				: public sprout::identity<typename sprout::random::random_result<Engine, Distribution>::result_type>
			{};
			template<typename Engine, typename Distribution>
			struct tuple_element_impl<1, sprout::random::random_result<Engine, Distribution> >
				: public sprout::identity<typename sprout::random::random_result<Engine, Distribution>::generator_type>
			{};

			template<std::size_t I, typename T>
			struct get_impl;
			template<typename Engine, typename Distribution>
			struct get_impl<0, sprout::random::random_result<Engine, Distribution> > {
			public:
				SPROUT_CONSTEXPR typename sprout::random::random_result<Engine, Distribution>::result_type&
				operator()(sprout::random::random_result<Engine, Distribution>& t) const {
					return t.generated_value();
				}
				SPROUT_CONSTEXPR typename sprout::random::random_result<Engine, Distribution>::result_type const&
				operator()(sprout::random::random_result<Engine, Distribution> const& t) const {
					return t.generated_value();
				}
			};
			template<typename Engine, typename Distribution>
			struct get_impl<1, sprout::random::random_result<Engine, Distribution> > {
			public:
				SPROUT_CONSTEXPR typename sprout::random::random_result<Engine, Distribution>::generator_type&
				operator()(sprout::random::random_result<Engine, Distribution>& t) const {
					return t.next_generator();
				}
				SPROUT_CONSTEXPR typename sprout::random::random_result<Engine, Distribution>::generator_type const&
				operator()(sprout::random::random_result<Engine, Distribution> const& t) const {
					return t.next_generator();
				}
			};
		}	// namespace detail
	}	// namespace tuples
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// tuple_size
	//
	template<typename Engine, typename Distribution>
	struct tuple_size<sprout::random::random_result<Engine, Distribution> >
		: public sprout::integral_constant<std::size_t, 2>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename Engine, typename Distribution>
	struct tuple_element<I, sprout::random::random_result<Engine, Distribution> >
		: public sprout::tuples::detail::tuple_element_impl<I, sprout::random::random_result<Engine, Distribution> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

namespace sprout {
	namespace random {
		//
		// tuple_get
		//
		template<std::size_t I, typename Engine, typename Distribution>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::random::random_result<Engine, Distribution> >::type&
		tuple_get(sprout::random::random_result<Engine, Distribution>& t) SPROUT_NOEXCEPT {
			static_assert(I < 2, "tuple_get: index out of range");
			return sprout::tuples::detail::get_impl<I, sprout::random::random_result<Engine, Distribution> >()(t);
		}
		template<std::size_t I, typename Engine, typename Distribution>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::random::random_result<Engine, Distribution> >::type const&
		tuple_get(sprout::random::random_result<Engine, Distribution> const& t) SPROUT_NOEXCEPT {
			static_assert(I < 2, "tuple_get: index out of range");
			return sprout::tuples::detail::get_impl<I, sprout::random::random_result<Engine, Distribution> >()(t);
		}
		template<std::size_t I, typename Engine, typename Distribution>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::random::random_result<Engine, Distribution> >::type&&
		tuple_get(sprout::random::random_result<Engine, Distribution>&& t) SPROUT_NOEXCEPT {
			return sprout::move(sprout::tuples::get<I>(t));
		}
	}	// namespace random
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_RANDOM_RESULT_HPP
