#ifndef SPROUT_TUPLE_SSCRISK_CEL_UTILITY_HPP
#define SPROUT_TUPLE_SSCRISK_CEL_UTILITY_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sscrisk/cel/utility.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_size
		//
		template<typename T1, typename T2>
		class tuple_size<sscrisk::cel::pair<T1, T2> >
			: public std::integral_constant<std::size_t, 2>
		{};

		//
		// tuple_element
		//
		namespace detail {
			template<std::size_t I, typename T>
			class tuple_element_impl;
			template<typename T1, typename T2>
			class tuple_element_impl<0, sscrisk::cel::pair<T1, T2> > {
			public:
				typedef T1 type;
			};
			template<typename T1, typename T2>
			class tuple_element_impl<1, sscrisk::cel::pair<T1, T2> > {
			public:
				typedef T2 type;
			};
		}	// namespace detail
		template<std::size_t I, typename T1, typename T2>
		class tuple_element<I, sscrisk::cel::pair<T1, T2> >
			: public sprout::tuples::detail::tuple_element_impl<I, sscrisk::cel::pair<T1, T2> >
		{};

		//
		// get
		//
		namespace detail {
			template<std::size_t I, typename T>
			struct get_impl;
			template<typename T1, typename T2>
			struct get_impl<0, sscrisk::cel::pair<T1, T2> > {
			public:
				T1& operator()(sscrisk::cel::pair<T1, T2>& t) const {
					return t.first;
				}
				T1 const& operator()(sscrisk::cel::pair<T1, T2> const& t) const {
					return t.first;
				}
			};
			template<typename T1, typename T2>
			struct get_impl<1, sscrisk::cel::pair<T1, T2> > {
			public:
			public:
				T2& operator()(sscrisk::cel::pair<T1, T2>& t) const {
					return t.second;
				}
				T2 const& operator()(sscrisk::cel::pair<T1, T2> const& t) const {
					return t.second;
				}
			};
		}	// namespace detail
		template<std::size_t I, typename T1, typename T2>
		typename sprout::tuples::tuple_element<I, sscrisk::cel::pair<T1, T2> >::type& get(
			sscrisk::cel::pair<T1, T2>& t
			) SPROUT_NOEXCEPT
		{
			static_assert(I < 2, "get: index out of range");
			return sprout::tuples::detail::get_impl<I, sscrisk::cel::pair<T1, T2> >()(t);
		}
		template<std::size_t I, typename T1, typename T2>
		SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sscrisk::cel::pair<T1, T2> >::type const& get(
			sscrisk::cel::pair<T1, T2> const& t
			) SPROUT_NOEXCEPT
		{
			static_assert(I < 2, "get: index out of range");
			return sprout::tuples::detail::get_impl<I, sscrisk::cel::pair<T1, T2> >()(t);
		}
		template<std::size_t I, typename T1, typename T2>
		typename sprout::tuples::tuple_element<I, sscrisk::cel::pair<T1, T2> >::type&& get(
			sscrisk::cel::pair<T1, T2>&& t
			) SPROUT_NOEXCEPT
		{
			return std::move(sprout::tuples::get<I>(t));
		}
	}	// namespace tuples

	using sprout::tuples::get;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_SSCRISK_CEL_UTILITY_HPP
