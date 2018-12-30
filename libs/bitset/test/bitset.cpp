/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LIBS_BITSET_TEST_BITSET_CPP
#define SPROUT_LIBS_BITSET_TEST_BITSET_CPP

#include <sstream>
#include <sprout/bitset.hpp>
#include <sprout/utility/move.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void bitset_test() {
		using namespace sprout;
		{
			typedef sprout::bitset<40> bitset_t;
			SPROUT_STATIC_CONSTEXPR auto bits1 = bitset_t(0xDEADBEEF);

			// 20.5.2 bitset operations:

			// operator=
			{
				auto bits = bitset_t(0xDEADBACE);
				bits = bits1;
				TESTSPR_ASSERT(bits == bits1);
			}
			{
				auto bits2 = bits1;
				auto bits = bitset_t(0xDEADBACE);
				bits = sprout::move(bits2);
				TESTSPR_ASSERT(bits == bits1);
			}

			// operator&=
			{
				auto bits = bits1;
				bits &= bitset_t(0xDEADFACE);
				TESTSPR_ASSERT(bits == bitset_t(0xDEADBACE));
			}

			// operator|=
			{
				auto bits = bits1;
				bits |= bitset_t(0xDEADFACE);
				TESTSPR_ASSERT(bits == bitset_t(0xDEADFEEF));
			}

			// operator^=
			{
				auto bits = bits1;
				bits ^= bitset_t(0xDEADFACE);
				TESTSPR_ASSERT(bits == bitset_t(0x4421));
			}

			// operator<<=
			{
				auto bits = bits1;
				bits <<= 10;
				TESTSPR_ASSERT(bits == bitset_t(0x7AB6FBBC00ull));
			}

			// operator>>=
			{
				auto bits = bits1;
				bits >>= 10;
				TESTSPR_ASSERT(bits == bitset_t(0x37AB6Full));
			}

			// set
			TESTSPR_BOTH_ASSERT(bits1.set() == bitset_t(0xFFFFFFFFFFull));
			TESTSPR_BOTH_ASSERT(bits1.set(0, false) == bitset_t(0xDEADBEEE));
			TESTSPR_BOTH_ASSERT(bits1.set(4, true) == bitset_t(0xDEADBEFF));
			{
				auto bits = bits1;
				bits.set();
				TESTSPR_ASSERT(bits == bitset_t(0xFFFFFFFFFFull));
			}
			{
				auto bits = bits1;
				bits.set(0, false);
				TESTSPR_ASSERT(bits == bitset_t(0xDEADBEEE));
			}
			{
				auto bits = bits1;
				bits.set(4, true);
				TESTSPR_ASSERT(bits == bitset_t(0xDEADBEFF));
			}

			// reset
			TESTSPR_BOTH_ASSERT(bits1.reset() == bitset_t(0x0));
			TESTSPR_BOTH_ASSERT(bits1.reset(0) == bitset_t(0xDEADBEEE));
			{
				auto bits = bits1;
				bits.reset();
				TESTSPR_ASSERT(bits == bitset_t(0x0));
			}
			{
				auto bits = bits1;
				bits.reset(0);
				TESTSPR_ASSERT(bits == bitset_t(0xDEADBEEE));
			}

			// operator~
			TESTSPR_BOTH_ASSERT(~bits1 == bitset_t(0xFF21524110ull));
			TESTSPR_BOTH_ASSERT(~~bits1 == bitset_t(0xDEADBEEF));

			// flip
			TESTSPR_BOTH_ASSERT(bits1.flip() == bitset_t(0xFF21524110ull));
			TESTSPR_BOTH_ASSERT(bits1.flip(0) == bitset_t(0xDEADBEEE));
			TESTSPR_BOTH_ASSERT(bits1.flip(4) == bitset_t(0xDEADBEFF));
			{
				auto bits = bits1;
				bits.flip();
				TESTSPR_ASSERT(bits == bitset_t(0xFF21524110ull));
			}
			{
				auto bits = bits1;
				bits.flip(0);
				TESTSPR_ASSERT(bits == bitset_t(0xDEADBEEE));
			}
			{
				auto bits = bits1;
				bits.flip(4);
				TESTSPR_ASSERT(bits == bitset_t(0xDEADBEFF));
			}

			// element access:

			// operator[]
			TESTSPR_BOTH_ASSERT(bits1[0] == 1);
			TESTSPR_BOTH_ASSERT(bits1[4] == 0);
			{
				auto bits = bits1;
				TESTSPR_ASSERT(bits[0] == 1);
				TESTSPR_ASSERT(bits[4] == 0);
				bits[0] = ~bits[0];
				bits[4] = ~bits[4];
				TESTSPR_ASSERT(bits[0] == 0);
				TESTSPR_ASSERT(bits[4] == 1);
			}

			// to_ulong
			TESTSPR_BOTH_ASSERT(bits1.to_ulong() == 0xDEADBEEF);

			// to_ullong
			TESTSPR_BOTH_ASSERT(bits1.to_ullong() == 0xDEADBEEF);

			// to_string
			TESTSPR_ASSERT(bits1.to_string() == "0000000011011110101011011011111011101111");

			// count
			TESTSPR_BOTH_ASSERT(bits1.count() == 24);

			// size
			TESTSPR_BOTH_ASSERT(bits1.size() == 40);

			// operator==
			TESTSPR_BOTH_ASSERT(bits1 == bitset_t(0xDEADBEEF));
			TESTSPR_BOTH_ASSERT(!(bits1 == bitset_t(0xDEADFACE)));

			// operator!=
			TESTSPR_BOTH_ASSERT(!(bits1 != bitset_t(0xDEADBEEF)));
			TESTSPR_BOTH_ASSERT(bits1 != bitset_t(0xDEADFACE));

			// test
			TESTSPR_BOTH_ASSERT(bits1.test(0) == 1);
			TESTSPR_BOTH_ASSERT(bits1.test(4) == 0);

			// all
			TESTSPR_BOTH_ASSERT(!bits1.all());
			TESTSPR_BOTH_ASSERT(bitset_t(0xFFFFFFFFFFull).all());

			// any
			TESTSPR_BOTH_ASSERT(bits1.any());
			TESTSPR_BOTH_ASSERT(!bitset_t(0x0).any());

			// none
			TESTSPR_BOTH_ASSERT(!bits1.none());
			TESTSPR_BOTH_ASSERT(bitset_t(0x0).none());

			// operator<<
			TESTSPR_BOTH_ASSERT((bits1 << 10) == bitset_t(0x7AB6FBBC00ull));

			// operator>>
			TESTSPR_BOTH_ASSERT((bits1 >> 10) == bitset_t(0x37AB6Full));

			// 20.5.4 bitset operators:

			// operator&
			TESTSPR_BOTH_ASSERT((bits1 & bitset_t(0xDEADFACE)) == bitset_t(0xDEADBACE));

			// operator|
			TESTSPR_BOTH_ASSERT((bits1 | bitset_t(0xDEADFACE)) == bitset_t(0xDEADFEEF));

			// operator^
			TESTSPR_BOTH_ASSERT((bits1 ^ bitset_t(0xDEADFACE)) == bitset_t(0x4421));

			// operator<<
			{
				std::ostringstream os;
				os << bits1;
				TESTSPR_ASSERT(os.str() == "0000000011011110101011011011111011101111");
			}

			// operator>>
			{
				std::istringstream is("0000000011011110101011011011111011101111");
				auto bits = bitset_t();
				is >> bits;
				TESTSPR_ASSERT(bits == bitset_t(0xDEADBEEF));
			}

			// 20.5.3 hash support

			// sprout::to_hash, sprout::hash
			TESTSPR_BOTH_ASSERT(sprout::to_hash(bits1) == sprout::hash<decltype(bits1)>()(bits1));
			TESTSPR_BOTH_ASSERT(sprout::to_hash(bits1) != sprout::to_hash(bitset_t()));
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::bitset_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_BITSET_TEST_BITSET_CPP
