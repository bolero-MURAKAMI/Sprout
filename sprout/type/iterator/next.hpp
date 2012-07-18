#ifndef SPROUT_TYPE_ITERATOR_NEXT_HPP
#define SPROUT_TYPE_ITERATOR_NEXT_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace types {
		//
		// next
		//
		template<typename Iterator, typename Enable = void>
		struct next {
		public:
			typedef typename Iterator::next type;
		};

		template<typename Iterator>
		struct next<Iterator const>
			: public sprout::types::next<Iterator>
		{};
		template<typename Iterator>
		struct next<Iterator volatile>
			: public sprout::types::next<Iterator>
		{};
		template<typename Iterator>
		struct next<Iterator const volatile>
			: public sprout::types::next<Iterator>
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ITERATOR_NEXT_HPP
