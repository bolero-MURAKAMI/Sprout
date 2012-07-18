#ifndef SPROUT_TYPE_ITERATOR_PREV_HPP
#define SPROUT_TYPE_ITERATOR_PREV_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace types {
		//
		// prev
		//
		template<typename Iterator, typename Enable = void>
		struct prev {
		public:
			typedef typename Iterator::prev type;
		};

		template<typename Iterator>
		struct prev<Iterator const>
			: public sprout::types::prev<Iterator>
		{};
		template<typename Iterator>
		struct prev<Iterator volatile>
			: public sprout::types::prev<Iterator>
		{};
		template<typename Iterator>
		struct prev<Iterator const volatile>
			: public sprout::types::prev<Iterator>
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ITERATOR_PREV_HPP
