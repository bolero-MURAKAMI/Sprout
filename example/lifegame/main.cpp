/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/algorithm/fixed/unfold.hpp>
#include <sprout/utility/pair.hpp>
#include <sprout/array.hpp>

//
// next_cell
//
template<typename Value, typename Size>
inline SPROUT_CONSTEXPR Value
next_cell(Value const& val, Size n) {
	return val ? n == 2 || n == 3 : n == 3;
}
template<typename Container, typename Difference1, typename Difference2>
inline SPROUT_CONSTEXPR typename sprout::container_traits<typename sprout::container_traits<Container>::value_type>::value_type
next_cell(Container const& cont, Difference1 i, Difference2 j) {
	return i == 0
			// +----
			// | o x
			// | x x
			? j == 0
				? ::next_cell(
					cont[i][j],
					0
						+ cont[i][j + 1]
						+ cont[i + 1][j] + cont[i + 1][j + 1]
					)
			// ----+
			// x o |
			// x x |
			: j == static_cast<Difference2>(sprout::size(cont[i]) - 1)
				? ::next_cell(
					cont[i][j],
					0
						+ cont[i][j - 1]
						+ cont[i + 1][j - 1] + cont[i + 1][j]
					)
			// -----
			// x o x
			// x x x
			: ::next_cell(
				cont[i][j],
				0
					+ cont[i][j - 1] + cont[i][j + 1]
					+ cont[i + 1][j - 1] + cont[i + 1][j] + cont[i + 1][j + 1]
				)
		: i == static_cast<Difference1>(sprout::size(cont) - 1)
			// | x x
			// | o x
			// +----
			? j == 0
				? ::next_cell(
					cont[i][j],
					0
						+ cont[i - 1][j] + cont[i - 1][j + 1]
						+ cont[i][j + 1]
					)
			// x x |
			// x o |
			// ----+
			: j == static_cast<Difference2>(sprout::size(cont[i]) - 1)
				? ::next_cell(
					cont[i][j],
					0
						+ cont[i - 1][j - 1] + cont[i - 1][j]
						+ cont[i][j - 1]
					)
			// x x x
			// x o x
			// -----
			: ::next_cell(
				cont[i][j],
				0
					+ cont[i - 1][j - 1] + cont[i - 1][j] + cont[i - 1][j + 1]
					+ cont[i][j - 1] + cont[i][j + 1]
				)
		// | x x
		// | o x
		// | x x
		: j == 0
			? ::next_cell(
				cont[i][j],
				0
					+ cont[i - 1][j] + cont[i - 1][j + 1]
					+ cont[i][j + 1]
					+ cont[i + 1][j] + cont[i + 1][j + 1])
		// x x |
		// x o |
		// x x |
		: j == static_cast<Difference2>(sprout::size(cont[i]) - 1)
			? ::next_cell(
				cont[i][j],
				0
					+ cont[i - 1][j - 1] + cont[i - 1][j]
					+ cont[i][j - 1]
					+ cont[i + 1][j - 1] + cont[i + 1][j]
				)
		// x x x
		// x o x
		// x x x
		: ::next_cell(
			cont[i][j],
			0
				+ cont[i - 1][j - 1] + cont[i - 1][j] + cont[i - 1][j + 1]
				+ cont[i][j - 1] + cont[i][j + 1]
				+ cont[i + 1][j - 1] + cont[i + 1][j] + cont[i + 1][j + 1]
			)
		;
}

namespace detail {
	template<typename Container, sprout::index_t... Js>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::value_type
	next_cells_2(Container const& cont, sprout::index_t i, sprout::index_tuple<Js...>) {
		return sprout::remake<typename sprout::container_traits<Container>::value_type>(
			cont[i], sprout::size(cont[i]),
			::next_cell(cont, i, Js)...
			);
	}
	template<typename Container, sprout::index_t... Is>
	inline SPROUT_CONSTEXPR Container
	next_cells_1(Container const& cont, sprout::index_tuple<Is...>) {
		return sprout::remake<Container>(
			cont, sprout::size(cont),
			detail::next_cells_2(cont, Is, sprout::container_indexes<typename sprout::container_traits<Container>::value_type>::make())...
			);
	}
}	// namespace detail
//
// next_cells
//
template<typename Container>
inline SPROUT_CONSTEXPR Container
next_cells(Container const& cont) {
	return detail::next_cells_1(cont, sprout::container_indexes<Container>::make());
}

namespace detail {
	struct gen_next_cells {
	public:
		template<typename Container>
		SPROUT_CONSTEXPR sprout::pair<Container, Container>
		operator()(Container const& cont) const {
			return sprout::pair<Container, Container>(cont, ::next_cells(cont));
		}
	};
}	// namespace detail
//
// next_cells
//
template<std::size_t N, typename Container>
inline SPROUT_CONSTEXPR sprout::array<Container, N>
next_cells(Container const& cont) {
	return sprout::fixed::unfold<sprout::array<Container, N> >(detail::gen_next_cells(), cont);
}

#include <sprout/array.hpp>
#include <testspr/print.hpp>

#define BOARD_WIDTH 16
#define BOARD_HEIGHT 16
#define BOARD_COUNT 16

template<typename Container>
void SPROUT_NON_CONSTEXPR print_board(Container const& board) {
	testspr::print_hl();
	for (auto&& line : board) {
		for (auto&& cell : line) {
			testspr::print(cell ? "■" : "□", ' ');
		}
		testspr::print_ln();
	}
}

int main() {
	typedef sprout::array<sprout::array<int, BOARD_WIDTH>, BOARD_HEIGHT> board_type;

	// セルの初期配置
#define _ 0
#define X 1
	SPROUT_STATIC_CONSTEXPR board_type board0
	{{
		{{_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}},
		{{_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}},
		{{_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}},
		{{_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}},
		{{_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}},
		{{_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}},
		{{_, _, _, _, _, X, _, _, _, _, _, _, _, _, _, _}},
		{{_, _, _, _, _, _, _, X, _, _, _, _, _, _, _, _}},
		{{_, _, _, _, X, X, _, _, X, X, X, _, _, _, _, _}},
		{{_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}},
		{{_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}},
		{{_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}},
		{{_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}},
		{{_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}},
		{{_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}},
		{{_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _}}
	}};
#undef _
#undef X

	// ライフゲームの実行
	SPROUT_STATIC_CONSTEXPR auto boards = ::next_cells<BOARD_COUNT>(board0);

	// 表示
	for (auto&& board : boards) {
		::print_board(board);
	}
}

