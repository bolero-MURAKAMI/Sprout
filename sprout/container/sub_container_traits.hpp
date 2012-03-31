#ifndef SPROUT_CONTAINER_SUB_CONTAINER_TRAITS_HPP
#define SPROUT_CONTAINER_SUB_CONTAINER_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// sub_container_traits
	//
	template<typename Container>
	struct sub_container_traits {
	public:
		template<typename Cont>
		struct internal {
		public:
			typedef Cont&& type;
		};
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR typename internal<Cont>::type get_internal(Cont&& cont) {
			return sprout::forward<Cont>(cont);
		}
	};
	template<typename Container>
	struct sub_container_traits<Container const>
		: public sprout::sub_container_traits<Container>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_SUB_CONTAINER_TRAITS_HPP
