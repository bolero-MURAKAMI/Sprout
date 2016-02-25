/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <climits>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <iterator>
#include <type_traits>
#include <iostream>
#include <fstream>
#include <sprout/workaround/std/cstddef.hpp>

namespace toolspr {
	template<std::size_t N = 4, typename InputIterator>
	std::string read_chunk(InputIterator& it) {
		std::string s;
		for (std::size_t i = 0; i != N; ++i, ++it) {
			s.push_back(*it);
		}
		return s;
	}

	template<typename IntType, typename InputIterator>
	IntType read_int(InputIterator& it) {
		IntType n = 0;
		for (std::size_t i = 0; i != sizeof(IntType); ++i, ++it) {
			n |= static_cast<IntType>(static_cast<unsigned char>(*it)) << (i * CHAR_BIT);
		}
		return n;
	}
}	// namespace toolspr

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr
			<< "#error missing parameter.\n"
			<< std::flush
			;
		return 0;
	}

	std::ifstream ifs(argv[1], std::ios_base::in | std::ios_base::binary);
	std::istreambuf_iterator<char> it(ifs);
	std::istreambuf_iterator<char> last;
	std::cout
		<< "#if defined(COMPOST_LOADING_SOURCE_VERSION)\n"
			"\n"
			"COMPOST_SRC_VERSION(0)\n"
			"\n"
			"#elif defined(COMPOST_LOADING_SOURCE_INFO)\n"
			"\n"
		;

	if (toolspr::read_chunk(it) != "RIFF") {
		std::cerr
			<< "#error not RIFF file.\n"
			<< std::flush
			;
		return EXIT_FAILURE;
	}
	/*auto file_size = */toolspr::read_int<std::uint32_t>(it);
	if (toolspr::read_chunk(it) != "WAVE") {
		std::cerr
			<< "#error not WAVE format.\n"
			<< std::flush
			;
		return EXIT_FAILURE;
	}

	while (toolspr::read_chunk(it) != "fmt ") {
		auto chunk_size = toolspr::read_int<std::uint32_t>(it);
		std::advance(it, chunk_size);
	}
	auto fmt_size = toolspr::read_int<std::uint32_t>(it);
	auto format_tag = toolspr::read_int<std::uint16_t>(it);
	auto channels = toolspr::read_int<std::uint16_t>(it);
	auto samples_per_sec = toolspr::read_int<std::uint32_t>(it);
	auto bytes_per_sec = toolspr::read_int<std::uint32_t>(it);
	auto block_size = toolspr::read_int<std::uint16_t>(it);
	auto bits_per_sample = toolspr::read_int<std::uint16_t>(it);
	std::cout
		<< format_tag << ",\n"
		<< channels << ",\n"
		<< samples_per_sec << ",\n"
		<< bytes_per_sec << ",\n"
		<< block_size << ",\n"
		<< bits_per_sample << ",\n"
		;
	std::advance(it, fmt_size - 16);

	while (toolspr::read_chunk(it) != "data") {
		auto chunk_size = toolspr::read_int<std::uint32_t>(it);
		std::advance(it, chunk_size);
	}
	auto data_size = toolspr::read_int<std::uint32_t>(it);
	std::size_t size = data_size / (bits_per_sample / CHAR_BIT);
	std::cout
		<< size << "\n"
		<< "\n"
			"#elif defined(COMPOST_LOADING_SOURCE_DATA)\n"
			"\n"
		;
	if (size > 0) {
		if (bits_per_sample == 16) {
			for (std::size_t i = 1; i != size; ++i) {
				std::cout
					<< toolspr::read_int<std::int16_t>(it) << ",\n"
					;
			}
			std::cout
				<< toolspr::read_int<std::int16_t>(it) << "\n"
				;
		} else if (bits_per_sample == 8) {
			for (std::size_t i = 1; i != size; ++i) {
				std::cout
					<< toolspr::read_int<std::uint8_t>(it) << ",\n"
					;
			}
			std::cout
				<< toolspr::read_int<std::uint8_t>(it) << "\n"
				;
		}
	}

	std::cout
		<< "\n"
			"#endif\n"
		<< std::flush
		;
}
