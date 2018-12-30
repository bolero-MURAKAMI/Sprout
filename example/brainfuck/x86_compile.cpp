/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sprout/config.hpp>
#include <sprout/endian_traits.hpp>
#include <sprout/string.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/range/algorithm.hpp>
#include <sprout/preprocessor/stringize.hpp>
#include <sprout/assert.hpp>


//
// PE structs
//	Copy and Paste from <windows.h>
//
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;


//
// File header format.
//

typedef struct _IMAGE_FILE_HEADER {
    WORD    Machine;
    WORD    NumberOfSections;
    DWORD   TimeDateStamp;
    DWORD   PointerToSymbolTable;
    DWORD   NumberOfSymbols;
    WORD    SizeOfOptionalHeader;
    WORD    Characteristics;
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;


//
// Directory format.
//

typedef struct _IMAGE_DATA_DIRECTORY {
    DWORD   VirtualAddress;
    DWORD   Size;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16

//
// Optional header format.
//

typedef struct _IMAGE_OPTIONAL_HEADER {
    //
    // Standard fields.
    //

    WORD    Magic;
    BYTE    MajorLinkerVersion;
    BYTE    MinorLinkerVersion;
    DWORD   SizeOfCode;
    DWORD   SizeOfInitializedData;
    DWORD   SizeOfUninitializedData;
    DWORD   AddressOfEntryPoint;
    DWORD   BaseOfCode;
    DWORD   BaseOfData;

    //
    // NT additional fields.
    //

    DWORD   ImageBase;
    DWORD   SectionAlignment;
    DWORD   FileAlignment;
    WORD    MajorOperatingSystemVersion;
    WORD    MinorOperatingSystemVersion;
    WORD    MajorImageVersion;
    WORD    MinorImageVersion;
    WORD    MajorSubsystemVersion;
    WORD    MinorSubsystemVersion;
    DWORD   Win32VersionValue;
    DWORD   SizeOfImage;
    DWORD   SizeOfHeaders;
    DWORD   CheckSum;
    WORD    Subsystem;
    WORD    DllCharacteristics;
    DWORD   SizeOfStackReserve;
    DWORD   SizeOfStackCommit;
    DWORD   SizeOfHeapReserve;
    DWORD   SizeOfHeapCommit;
    DWORD   LoaderFlags;
    DWORD   NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;


//
// Section header format.
//

#define IMAGE_SIZEOF_SHORT_NAME              8

typedef struct _IMAGE_SECTION_HEADER {
    BYTE    Name[IMAGE_SIZEOF_SHORT_NAME];
//    union {
//            DWORD   PhysicalAddress;
//            DWORD   VirtualSize;
//    } Misc;
	struct {
            DWORD   VirtualSize;
	} Misc;
    DWORD   VirtualAddress;
    DWORD   SizeOfRawData;
    DWORD   PointerToRawData;
    DWORD   PointerToRelocations;
    DWORD   PointerToLinenumbers;
    WORD    NumberOfRelocations;
    WORD    NumberOfLinenumbers;
    DWORD   Characteristics;
} IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;


//
// binary size for output
//
#ifndef BRAINFUCK_BINARY_SIZE
#	define BRAINFUCK_BINARY_SIZE (16 * 1024)
#endif

//
// loop limit
//
#ifndef BRAINFUCK_LOOP_LIMIT
#	define BRAINFUCK_LOOP_LIMIT 256
#endif

//
// source file name
//
#ifndef BRAINFUCK_SOURCE_FILE
#	define BRAINFUCK_SOURCE_FILE a.bf
#endif


//
// constants
//
SPROUT_STATIC_CONSTEXPR std::size_t bin_size = BRAINFUCK_BINARY_SIZE;

SPROUT_STATIC_CONSTEXPR std::size_t loop_limit = BRAINFUCK_LOOP_LIMIT;

SPROUT_STATIC_CONSTEXPR auto source = sprout::to_string(
#	include SPROUT_PP_STRINGIZE(BRAINFUCK_SOURCE_FILE)
	);

SPROUT_STATIC_CONSTEXPR std::int32_t addr_putchar = 0x00405044;
SPROUT_STATIC_CONSTEXPR std::int32_t addr_getchar = addr_putchar + 4;
SPROUT_STATIC_CONSTEXPR std::int32_t addr_buf = 0x00406000;


//
// output functions
//
template<typename OutputIterator, typename T>
SPROUT_CXX14_CONSTEXPR std::size_t
write_bytes(OutputIterator& out, T const& val) {
	typedef sprout::little_endian_traits<T> traits;
	for (std::size_t i = 0; i != traits::size(); ++i) {
		*out++ = sprout::little_endian_traits<T>::get_byte(val, i);
	}
	return traits::size();
}
template<typename OutputIterator, typename T, std::size_t N>
SPROUT_CXX14_CONSTEXPR std::size_t
write_bytes(OutputIterator& out, T const(& vals)[N]) {
	typedef sprout::little_endian_traits<T> traits;
	for (std::size_t i = 0; i != N; ++i) {
		::write_bytes(out, vals[i]);
	}
	return traits::size() * N;
}
template<typename OutputIterator, typename Head, typename... Tail>
SPROUT_CXX14_CONSTEXPR std::size_t
write_bytes(OutputIterator& out, Head const& head, Tail const&... tail) {
	return ::write_bytes(out, head) + ::write_bytes(out, tail...);
}

template<typename OutputIterator>
SPROUT_CXX14_CONSTEXPR std::size_t
write_pe_header(OutputIterator& out, std::size_t n = 0) {
	SPROUT_CONSTEXPR unsigned char stub[] = {
		// 00-3b: DOS Header
		'M',  'Z',  0x50, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0f, 0x00, 0xff, 0xff, 0x00, 0x00,
		0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		// 3c-3f: Pointer to PE Header (=80)
		0x80, 0x00, 0x00, 0x00,
		// 40-7f: DOS Stub
		0xba, 0x10, 0x00, 0x0e, 0x1f, 0xb4, 0x09, 0xcd, 0x21, 0xb8, 0x01, 0x4c, 0xcd, 0x21, 0x90, 0x90,
		'T', 'h', 'i', 's', ' ', 'p', 'r', 'o', 'g', 'r', 'a', 'm', ' ', 'c', 'a', 'n',
		'n', 'o', 't', ' ', 'b', 'e', ' ', 'r', 'u', 'n', ' ', 'i', 'n', ' ', 'D', 'O',
		'S', ' ', 'm', 'o', 'd', 'e', '.', '\r', '\n', '$', 0, 0, 0, 0, 0, 0,
		// 80-83: PE Signature
		'P', 'E', 0, 0
	};
	n += ::write_bytes(
		out,
		stub
		);

	SPROUT_CONSTEXPR ::IMAGE_FILE_HEADER coff = {
		0x014c,								// Machine
		3,									// NumberOfSections
		0,									// TimeDateStamp
		0,									// PointerToSymbolTable
		0,									// NumberOfSymbols
		sizeof(::IMAGE_OPTIONAL_HEADER32),	// SizeOfOptionalHeader
		0x030f								// Characteristics
	};
	n += ::write_bytes(
		out,
		coff.Machine,
		coff.NumberOfSections,
		coff.TimeDateStamp,
		coff.PointerToSymbolTable,
		coff.NumberOfSymbols,
		coff.SizeOfOptionalHeader,
		coff.Characteristics
		);

	SPROUT_CONSTEXPR ::IMAGE_OPTIONAL_HEADER32 opt = {
		0x010b,			// Magic
		6, 0,			// MajorLinkerVersion, MinorLinkerVersion
		::bin_size,		// SizeOfCode
		0,				// SizeOfInitializedData
		65536,			// SizeOfUninitializedData
		0x1000,			// AddressOfEntryPoint
		0x1000,			// BaseOfCode
		0x6000,			// BaseOfData
		0x00400000,		// ImageBase
		0x1000,			// SectionAlignment
		0x0200,			// FileAlignment
		4, 0,			// MajorOperatingSystemVersion, MinorOperatingSystemVersion
		0, 0,			// MajorImageVersion, MinorImageVersion
		4, 0,			// MajorSubsystemVersion, MinorSubsystemVersion
		0,				// Win32VersionValue
		0x16000,		// SizeOfImage
		0x200,			// SizeOfHeaders
		0,				// CheckSum
		3,				// Subsystem
		0,				// DllCharacteristics
		1024 * 1024,	// SizeOfStackReserve
		8 * 1024,		// SizeOfStackCommit
		1024 * 1024,	// SizeOfHeapReserve
		4 * 1024,		// SizeOfHeapCommit
		0,				// LoaderFlags
		16,				// NumberOfRvaAndSizes
		{
			{},
			{
				0x5000,	// VirtualAddress (import table)
				100		// Size
			},
			{}
		}
	};
	n += ::write_bytes(
		out,
		opt.Magic,
		opt.MajorLinkerVersion, opt.MinorLinkerVersion,
		opt.SizeOfCode,
		opt.SizeOfInitializedData,
		opt.SizeOfUninitializedData,
		opt.AddressOfEntryPoint,
		opt.BaseOfCode,
		opt.BaseOfData,
		opt.ImageBase,
		opt.SectionAlignment,
		opt.FileAlignment,
		opt.MajorOperatingSystemVersion, opt.MinorOperatingSystemVersion,
		opt.MajorImageVersion, opt.MinorImageVersion,
		opt.MajorSubsystemVersion, opt.MinorSubsystemVersion,
		opt.Win32VersionValue,
		opt.SizeOfImage,
		opt.SizeOfHeaders,
		opt.CheckSum,
		opt.Subsystem,
		opt.DllCharacteristics,
		opt.SizeOfStackReserve,
		opt.SizeOfStackCommit,
		opt.SizeOfHeapReserve,
		opt.SizeOfHeapCommit,
		opt.LoaderFlags,
		opt.NumberOfRvaAndSizes,
		opt.DataDirectory[0].VirtualAddress, opt.DataDirectory[0].Size,
		opt.DataDirectory[1].VirtualAddress, opt.DataDirectory[1].Size
		);
	for (std::size_t i = 2; i != IMAGE_NUMBEROF_DIRECTORY_ENTRIES; ++i) {
		n += ::write_bytes(
			out,
			opt.DataDirectory[i].VirtualAddress, opt.DataDirectory[i].Size
			);
	}

	SPROUT_CONSTEXPR ::IMAGE_SECTION_HEADER sects[3] = {
		{
			".text",		// Name
			{::bin_size},	// Misc.VirtualSize
			0x1000,			// VirtualAddress
			::bin_size,		// SizeOfRawData
			0x400,			// PointerToRawData
			0,				// PointerToRelocations
			0,				// PointerToLinenumbers
			0,				// NumberOfRelocations
			0,				// NumberOfLinenumbers
			0x60500060		// Characteristics
		},
		{
			".idata",		// Name
			{100},			// Misc.VirtualSize
			0x5000,			// VirtualAddress
			512,			// SizeOfRawData
			0x200,			// PointerToRawData
			0,				// PointerToRelocations
			0,				// PointerToLinenumbers
			0,				// NumberOfRelocations
			0,				// NumberOfLinenumbers
			0xc0300040		// Characteristics
		},
		{
			".bss",			// Name
			{65536},		// Misc.VirtualSize
			0x6000,			// VirtualAddress
			0,				// SizeOfRawData
			0,				// PointerToRawData
			0,				// PointerToRelocations
			0,				// PointerToLinenumbers
			0,				// NumberOfRelocations
			0,				// NumberOfLinenumbers
			0xc0400080		// Characteristics
		}
	};
	for (std::size_t i = 0; i != 3; ++i) {
		n += ::write_bytes(
			out,
			sects[i].Name,
			sects[i].Misc.VirtualSize,
			sects[i].VirtualAddress,
			sects[i].SizeOfRawData,
			sects[i].PointerToRawData,
			sects[i].PointerToRelocations,
			sects[i].PointerToLinenumbers,
			sects[i].NumberOfRelocations,
			sects[i].NumberOfLinenumbers,
			sects[i].Characteristics
			);
	}

	for (; n != 0x200; ) {
		n += ::write_bytes(
			out,
			(unsigned char)0
			);
	}
	return n;
}

template<typename OutputIterator>
SPROUT_CXX14_CONSTEXPR std::size_t
write_idata(OutputIterator& out, std::size_t n = 0) {
	SPROUT_CONSTEXPR int idt[] = {
		// IDT 1
		0x5028, 0, 0, 0x5034, 0x5044,
		// IDT (end)
		0, 0, 0, 0, 0
	};
	n += ::write_bytes(
		out,
		idt
		);

	SPROUT_CONSTEXPR int ilt_iat[] = {
		0x5050, 0x505a, 0
	};

	// ILT
	n += ::write_bytes(
		out,
		ilt_iat
		);
	n += ::write_bytes(
		out,
		"msvcrt.dll\0\0\0\0\0"
		);

	// IAT
	n += ::write_bytes(
		out,
		ilt_iat
		);
	n += ::write_bytes(
		out,
		(std::int16_t)0,
		"putchar",
		(std::int16_t)0,
		"getchar"
		);

	for (; n != 0x400; ) {
		n += ::write_bytes(
			out,
			(unsigned char)0
			);
	}
	return n;
}

//
// compile
//
template<std::size_t LoopLimit = 256, typename InputIterator, typename RandomAccessIterator>
SPROUT_CXX14_CONSTEXPR std::size_t
compile(InputIterator first, InputIterator last, RandomAccessIterator& out_first) {
	sprout::array<int, LoopLimit> loops {{}};	// loop stack
	auto loop_first = sprout::begin(loops);
	auto loop_last = sprout::end(loops);
	auto loop = loop_first;

	int idx = 0;
	auto out = out_first;

	idx += ::write_bytes(
		out,
		(unsigned char)0x31, (unsigned char)0xc9,														// xor ecx, ecx
		(unsigned char)0x57,																			// push edi
		(unsigned char)0xbf, ::addr_buf																	// mov edi, addr_buf
		);

	for (; first != last; ++first) {
		switch (*first) {
			case '>':
				idx += ::write_bytes(
					out,
					(unsigned char)0x66, (unsigned char)0x41											// inc cx
					);
				break;
			case '<':
				idx += ::write_bytes(
					out,
					(unsigned char)0x66, (unsigned char)0x49											// dec cx
					);
				break;
			case '+':
				idx += ::write_bytes(
					out,
					(unsigned char)0xfe, (unsigned char)0x04, (unsigned char)0x0f						// inc byte [edi+ecx]
					);
				break;
			case '-':
				idx += ::write_bytes(
					out,
					(unsigned char)0xfe, (unsigned char)0x0c, (unsigned char)0x0f						// dec byte [edi+ecx]
					);
				break;
			case '.':
				idx += ::write_bytes(
					out,
					(unsigned char)0x51,																// push ecx
					(unsigned char)0x0f, (unsigned char)0xb6, (unsigned char)0x04, (unsigned char)0x0f,	// movzx eax,byte [edi+ecx]
					(unsigned char)0x50,																// push eax
					(unsigned char)0xa1, ::addr_putchar,												// mov eax, [addr_putchar]
					(unsigned char)0xff, (unsigned char)0xd0,											// call eax
					(unsigned char)0x58,																// pop eax
					(unsigned char)0x59																	// pop ecx
					);
				break;
			case ',':
				idx += ::write_bytes(
					out,
					(unsigned char)0x51,																// push ecx
					(unsigned char)0xa1, ::addr_getchar,												// mov eax, [addr_getchar]
					(unsigned char)0xff, (unsigned char)0xd0,											// call eax
					(unsigned char)0x59,																// pop ecx
					(unsigned char)0x88, (unsigned char)0x04, (unsigned char)0x0f						// mov [edi+ecx],al
					);
				break;
			case '[':
				SPROUT_ASSERT_MSG(loop != loop_last, "loop overflow");
				*loop++ = idx;	// push index to stack
				idx += ::write_bytes(
					out,
					(unsigned char)0x80, (unsigned char)0x3c, (unsigned char)0x0f, (unsigned char)0x00,	// cmp byte [edi+ecx],0
					(unsigned char)0x0f, (unsigned char)0x84,											// jz (immediately after corresponding ']')
					(unsigned char)0xde, (unsigned char)0xad, (unsigned char)0xbe, (unsigned char)0xef	// (set address later)
					);
				break;
			case ']':
			{
				SPROUT_ASSERT_MSG(loop != loop_first, "missing '['");
				int idx_loop = *--loop;
				idx += ::write_bytes(
					out,
					(unsigned char)0xe9, (std::int32_t)(idx_loop - (idx + 5))							// jmp idx_loop
					);
				auto out_loop = out_first + (idx_loop + 6);
				::write_bytes(
					out_loop,
					(std::int32_t)(idx - (idx_loop + 10))												// (address)
					);
				break;
			}
		}
		SPROUT_ASSERT_MSG(idx <= (int)::bin_size - 32, "buffer overflow");
	}

	SPROUT_ASSERT_MSG(loop == loop_first, "missing ']'");

	// end
	idx += ::write_bytes(
		out,
		(unsigned char)0x5f,																			// pop edi
		(unsigned char)0x31, (unsigned char)0xc0,														// xor eax, eax
		(unsigned char)0xc3																				// ret
		);

	return idx;
}

//
// build
//
template<std::size_t LoopLimit = 256, typename InputIterator, typename RandomAccessIterator>
SPROUT_CXX14_CONSTEXPR std::size_t
build(InputIterator first, InputIterator last, RandomAccessIterator& out) {
	std::size_t n = 0;
	n += ::write_pe_header(out, n);					// header
	n += ::write_idata(out, n);						// .idata section
	n += ::compile<LoopLimit>(first, last, out);	// compile
	return n;
}


SPROUT_CXX14_CONSTEXPR sprout::sub_array<sprout::array<unsigned char, ::bin_size> >
build_brainfuck() {
	sprout::array<unsigned char, ::bin_size> bin{{}};
	auto out = sprout::begin(bin);
	auto n = ::build<::loop_limit>(sprout::begin(::source), sprout::end(::source), out);
	return sprout::sub_copy(bin, 0, n);
}

int main(int argc, char* argv[]) {
	SPROUT_CXX14_CONSTEXPR auto bin = ::build_brainfuck();

	char const* filename = argc >= 2 ? argv[1]
		: "a.exe"
		;
	std::ofstream ofs(filename);
	if (!ofs) {
		std::cout
			<< "could not open file" << std::endl
			;
		return -1;
	}
	sprout::range::copy(bin, std::ostreambuf_iterator<char>(ofs));
}
