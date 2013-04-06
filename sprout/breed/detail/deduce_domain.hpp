#ifndef SPROUT_BREED_DETAIL_DEDUCE_DOMAIN_HPP
#define SPROUT_BREED_DETAIL_DEDUCE_DOMAIN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/utility/pack.hpp>
#include <sprout/breed/breed_fwd.hpp>

//
// SPROUT_BREED_ASSERT_VALID_DOMAIN
//
#ifndef SPROUT_BREED_ASSERT_VALID_DOMAIN
#	define SPROUT_BREED_ASSERT_VALID_DOMAIN(DOM) static_assert( \
	!std::is_same<DOM, sprout::breed::detail::not_a_domain>::value, \
	"!std::is_same<DOM, sprout::breed::detail::not_a_domain>::value" \
	)
#endif

namespace sprout {
	namespace breed {
		namespace detail {
			template<typename Domain>
			struct domain_
				: public domain_<typename Domain::breed_super_domain>
			{
			public:
				typedef Domain type;
				typedef domain_<typename Domain::breed_super_domain> base;
			public:
				using base::deduce_;
				static SPROUT_CONSTEXPR type deduce_(domain_<Domain> const*);
			};
			template<>
			struct domain_<sprout::breed::detail::not_a_domain> {
			public:
				typedef sprout::breed::detail::not_a_domain type;
			public:
				static type deduce_(void const*);
			};

			template<>
			struct domain_<sprout::breed::default_domain>
				: public domain_<sprout::breed::detail::not_a_domain>
			{};

			template<>
			struct domain_<sprout::breed::basic_default_domain>
				: public domain_<sprout::breed::detail::not_a_domain>
			{};

			sprout::breed::detail::sized_type<1>::type default_test(
				void const*,
				void const*
				);
			sprout::breed::detail::sized_type<2>::type default_test(
				sprout::breed::detail::domain_<sprout::breed::default_domain> const*,
				void const*
				);
			sprout::breed::detail::sized_type<2>::type default_test(
				sprout::breed::detail::domain_<sprout::breed::basic_default_domain> const*, void const*
				);
			sprout::breed::detail::sized_type<3>::type default_test(
				void const*,
				sprout::breed::detail::domain_<sprout::breed::default_domain> const*
				);
			sprout::breed::detail::sized_type<3>::type default_test(
				void const*,
				sprout::breed::detail::domain_<sprout::breed::basic_default_domain> const*
				);
			sprout::breed::detail::sized_type<4>::type default_test(
				sprout::breed::detail::domain_<sprout::breed::default_domain> const*,
				sprout::breed::detail::domain_<sprout::breed::default_domain> const*
				);
			sprout::breed::detail::sized_type<4>::type default_test(
				sprout::breed::detail::domain_<sprout::breed::basic_default_domain> const*,
				sprout::breed::detail::domain_<sprout::breed::default_domain> const*
				);
			sprout::breed::detail::sized_type<4>::type default_test(
				sprout::breed::detail::domain_<sprout::breed::default_domain> const*,
				sprout::breed::detail::domain_<sprout::breed::basic_default_domain> const*
				);
			sprout::breed::detail::sized_type<4>::type default_test(
				sprout::breed::detail::domain_<sprout::breed::basic_default_domain> const*,
				sprout::breed::detail::domain_<sprout::breed::basic_default_domain> const*
				);

			template<typename D0>
			struct common_domain1 {
			public:
				typedef D0 type;
			};

			template<typename E0>
			struct deduce_domain1
				: public sprout::breed::domain_of<E0>
			{};

			template<
				typename D0,
				typename D1,
				int DefaultCase = sizeof(
					sprout::breed::detail::default_test(
						static_cast<sprout::breed::detail::domain_<D0> const*>(0),
						static_cast<sprout::breed::detail::domain_<D1> const*>(0)
						)
					)
			>
			struct common_domain2 {
			public:
				typedef decltype(sprout::breed::detail::domain_<D0>::deduce_(
					static_cast<sprout::breed::detail::domain_<D1> const*>(0)
					)) type;
			};
			template<typename D0, typename D1>
			struct common_domain2<D0, D1, 2> {
			public:
				typedef D1 type;
			};
			template<typename D0, typename D1>
			struct common_domain2<D0, D1, 3> {
			public:
				typedef D0 type;
			};
			template<typename D0>
			struct common_domain2<D0, sprout::breed::default_domain, 4> {
			public:
				typedef D0 type;
			};
			template<typename D0>
			struct common_domain2<D0, sprout::breed::basic_default_domain, 4> {
			public:
				typedef D0 type;
			};
			template<typename D1>
			struct common_domain2<sprout::breed::default_domain, D1, 4> {
			public:
				typedef D1 type;
			};
			template<typename D1>
			struct common_domain2<sprout::breed::basic_default_domain, D1, 4> {
			public:
				typedef D1 type;
			};
			template<>
			struct common_domain2<sprout::breed::default_domain, sprout::breed::default_domain, 4> {
			public:
				typedef sprout::breed::default_domain type;
			};
			template<>
			struct common_domain2<sprout::breed::basic_default_domain, sprout::breed::default_domain, 4> {
			public:
				typedef sprout::breed::default_domain type;
			};
			template<>
			struct common_domain2<sprout::breed::default_domain, sprout::breed::basic_default_domain, 4> {
			public:
				typedef sprout::breed::default_domain type;
			};
			template<>
			struct common_domain2<sprout::breed::basic_default_domain, sprout::breed::basic_default_domain, 4> {
			public:
				typedef sprout::breed::basic_default_domain type;
			};

			template<typename E0, typename E1>
			struct deduce_domain2
				: public common_domain2<
					typename sprout::breed::domain_of<E0>::type,
					typename sprout::breed::domain_of<E1>::type
				>
			{};

			template<typename... Args>
			struct common_domain {
			private:
				template<typename Common, typename Head, typename... Tail>
				struct common_impl {
				public:
					typedef typename common_impl<
						typename sprout::breed::detail::common_domain2<Common, Head>::type,
						Tail...
					>::type type;
				};
				template<typename Common, typename Head>
				struct common_impl<Common, Head> {
				public:
					typedef typename sprout::breed::detail::common_domain2<Common, Head>::type type;
				};
			public:
				template<typename Head, typename... Tail>
				struct common
					: public common_impl<Head, Tail...>
				{};
				template<typename Head>
				struct common<Head>
					: public sprout::breed::detail::common_domain1<Head>
				{};
			public:
				typedef typename common<Args...>::type type;
				SPROUT_BREED_ASSERT_VALID_DOMAIN(type);
			};

			template<typename IndexTuple, typename... Args>
			struct deduce_domain_impl;
			template<typename... Args, sprout::index_t... Indexes>
			struct deduce_domain_impl<sprout::index_tuple<Indexes...>, Args...>
				: public sprout::breed::detail::common_domain<
					typename sprout::breed::domain_of<
						typename sprout::tppack_at<Indexes, Args...>::type
					>::type...
				>
			{};

			template<typename... Args>
			struct deduce_domain
				: public sprout::breed::detail::deduce_domain_impl<
					typename sprout::make_index_tuple<sizeof...(Args)>::type,
					Args...
				>
			{};
		}	// namespace detail
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_DETAIL_DEDUCE_DOMAIN_HPP
