/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef TOOLS_COMPOST_WAVE_IO_HPP
#define TOOLS_COMPOST_WAVE_IO_HPP

#include <climits>
#include <cstddef>
#include <cstdint>
#include <string>
#include <algorithm>
#include <ios>
#include <iostream>
#include <fstream>
#include <type_traits>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/soundcard.h>

namespace toolspr {
	//
	// output_plot
	//
	//	output for gnuplot
	//
	template<typename Elem, typename Traits, typename InputRange>
	std::basic_ostream<Elem, Traits>& output_plot(std::basic_ostream<Elem, Traits>& os, InputRange const& range) {
		os << std::fixed;
		unsigned x = 0;
		for (auto const& e : range) {
			os << x++ << ',' << e << '\n';
		}
		return os;
	}
	template<typename InputRange>
	std::basic_ostream<Elem, Traits>& output_plot(std::string const& filename, InputRange const& range) {
		std::ofstream os(filename);
		output_plot(os, range);
	}

	//
	// output_plot_real
	//
	//	output for gnuplot (only real part)
	//
	template<typename Elem, typename Traits, typename InputRange>
	std::basic_ostream<Elem, Traits>& output_plot_real(std::basic_ostream<Elem, Traits>& os, InputRange const& range) {
		os << std::fixed;
		unsigned x = 0;
		for (auto const& e : range) {
			os << x++ << ',' << real(e) << '\n';
		}
		return os;
	}
	template<typename InputRange>
	std::basic_ostream<Elem, Traits>& output_plot_real(std::string const& filename, InputRange const& range) {
		std::ofstream os(filename);
		output_plot_real(os, range);
	}

	//
	// write_chunk
	// write_int
	// write_wav
	//
	//	write data for wav format
	//
	template<typename OutputIterator>
	void write_chunk(OutputIterator& it, std::string const& s) {
		it = std::copy(s.begin(), s.end(), it);
	}
	template<typename IntType, typename OutputIterator>
	void write_int(OutputIterator& it, IntType const& n) {
		for (std::size_t i = 0; i != sizeof(IntType); ++i, ++it) {
			*it = static_cast<char>((static_cast<typename std::make_unsigned<IntType>::type>(n) >> (i * CHAR_BIT)) & 0xFF);
		}
	}
	template<typename OutputIterator, typename InputRange>
	void write_wav(OutputIterator& it, sprout::compost::sources::info_type const& info, InputRange const& data) {
		std::size_t data_size = info.size * info.bits_per_sample / CHAR_BIT;

		write_chunk(it, "RIFF");
		write_int(it, 36 + data_size);
		write_chunk(it, "WAVE");
		write_chunk(it, "fmt ");
		write_int(it, 16);
		write_int(it, info.format_tag);
		write_int(it, info.channels);
		write_int(it, info.samples_per_sec);
		write_int(it, info.bytes_per_sec);
		write_int(it, info.block_size);
		write_int(it, info.bits_per_sample);
		write_chunk(it, "data");
		write_int(it, data_size);
		if (info.bits_per_sample == 16) {
			for (auto e : data) {
				write_int<std::int16_t>(it, e);
			}
		} else if (info.bits_per_sample == 8) {
			for (auto e : data) {
				write_int<std::uint8_t>(it, e);
			}
		}
	}

	//
	// output_wav
	//
	//	output for wav format
	//
	template<typename Elem, typename Traits, typename InputRange>
	void output_wav(std::basic_ostream<Elem, Traits>& os, sprout::compost::sources::info_type const& info, InputRange const& data) {
		std::ostreambuf_iterator<Elem> it(os);
		write_wav(it, info, data);
	}
	template<typename InputRange>
	void output_wav(std::string const& filename, sprout::compost::sources::info_type const& info, InputRange const& data) {
		std::ofstream os(filename, std::ios_base::out | std::ios_base::binary);
		output_wav(os, info, data);
	}

	//
	// setup_dev_dsp
	//
	//	Setting up dsp device
	//
	int setup_dev_dsp(sprout::compost::sources::info_type const& info) {
		/* open of dsp device */
		int fd = open("/dev/dsp", O_RDWR);
		if (fd < 0) {
			std::cerr << "open of /dev/dsp failed" << std::endl;
			return -1;
		}

		/* initializations of dsp device */
		int arg = 0;
		int status = 0;
		/* sampling bit rate */
		arg = info.bits_per_sample;
		status = ioctl(fd, SOUND_PCM_WRITE_BITS, &arg);
		if (status == -1 || arg != info.bits_per_sample) {
			return -1;
		}
		/* stereo or monoral */
		arg = info.channels;
		status = ioctl(fd, SOUND_PCM_WRITE_CHANNELS, &arg);
		if (status == -1 || arg != info.channels) {
			return -1;
		}
		/* sampling frequency */
		arg = info.samples_per_sec;
		status = ioctl(fd, SOUND_PCM_WRITE_RATE, &arg);
		if (status == -1 || arg != static_cast<int>(info.samples_per_sec)) {
			return -1;
		}

		return fd;
	}

	//
	// write_dev_dsp
	//
	//	write to dsp device
	//
	ssize_t write_dev_dsp(int fd, void const* buf, std::size_t n) {
		return write(fd, buf, n);
	}
}	// namespace toolspr

#endif	// #ifndef TOOLS_COMPOST_WAVE_IO_HPP
