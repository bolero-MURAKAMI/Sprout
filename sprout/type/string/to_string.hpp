#ifndef SPROUT_TYPE_STRING_TO_STRING_HPP
#define SPROUT_TYPE_STRING_TO_STRING_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/type/string.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/size.hpp>
#include <sprout/container/begin.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/preprocessor/cat.hpp>

namespace sprout {
	namespace types {
		//
		// to_string
		//
		template<typename Proxy>
		struct to_string {
		private:
			typedef decltype(Proxy()()) string_type;
			typedef sprout::container_traits<string_type> traits_type;
		private:
			template<typename IndexTuple>
			struct impl;
			template<sprout::index_t... Indexes>
			struct impl<sprout::index_tuple<Indexes...> > {
			public:
				typedef sprout::types::basic_string<
					typename traits_type::value_type,
					(*sprout::next(sprout::begin(Proxy()()), Indexes))...
				> type;
			};
		public:
			typedef typename impl<
				typename sprout::index_range<0, sprout::size(Proxy()())>::type
			>::type type;
		};
		namespace detail {
			template<typename Src, bool IsArray>
			struct string_typedef_impl {
			public:
				typedef typename std::decay<Src>::type result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(Src const& src) const {
					return src;
				}
			};
			template<typename Src>
			struct string_typedef_impl<Src, true> {
			public:
				typedef decltype(sprout::to_string(std::declval<Src const&>())) result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(Src const& src) const {
					return sprout::to_string(src);
				}
			};
		}	// namespace detail
		//
		// SPROUT_TYPES_STRING_TYPEDEF
		//
#		define SPROUT_TYPES_STRING_TYPEDEF(SOURCE, TYPE) \
		struct SPROUT_PP_CAT(SPROUT_TYPES_STRING_TYPEDEF_PROXY_, __LINE__) { \
		private: \
			typedef typename std::remove_reference<decltype(SOURCE)>::type src_type; \
			typedef sprout::types::detail::string_typedef_impl<src_type, std::is_array<src_type>::value> impl_type; \
		public: \
			typedef typename impl_type::result_type result_type; \
		public: \
			SPROUT_CONSTEXPR result_type operator()() const { \
				return impl_type()(SOURCE); \
			} \
		}; \
		typedef typename sprout::types::to_string<SPROUT_PP_CAT(SPROUT_TYPES_STRING_TYPEDEF_PROXY_, __LINE__)>::type TYPE
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_STRING_TO_STRING_HPP
