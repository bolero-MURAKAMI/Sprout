#ifndef SPROUT_TYPE_ITERATOR_ADVANCE_HPP
#define SPROUT_TYPE_ITERATOR_ADVANCE_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace types {
		//
		// advance
		//
		template<typename Iterator, std::ptrdiff_t Disatnce, typename Enable = void>
		struct advance
			: public Iterator::template advance<Disatnce>
		{};

		template<typename Iterator, std::ptrdiff_t Disatnce>
		struct advance<Iterator const, Disatnce>
			: public sprout::types::advance<Iterator, Disatnce>
		{};
		template<typename Iterator, std::ptrdiff_t Disatnce>
		struct advance<Iterator volatile, Disatnce>
			: public sprout::types::advance<Iterator, Disatnce>
		{};
		template<typename Iterator, std::ptrdiff_t Disatnce>
		struct advance<Iterator const volatile, Disatnce>
			: public sprout::types::advance<Iterator, Disatnce>
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ITERATOR_ADVANCE_HPP
