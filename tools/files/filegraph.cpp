/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <iterator>
#include <algorithm>
#include <boost/wave.hpp>
#include <boost/wave/preprocessing_hooks.hpp>
#include <boost/wave/cpplexer/cpp_lex_token.hpp>
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/filesystem.hpp>
#include <boost/range.hpp>
#include <boost/algorithm/string.hpp>
#include "../sprig/algorithm/string.hpp"
#include "../sprig/graph/depth_first_search.hpp"

class include_graph_hooks
	: public boost::wave::context_policies::default_preprocessing_hooks
{
private:
	typedef boost::wave::context_policies::default_preprocessing_hooks base_type;
public:
	// グラフのノード
	struct node_type {
		boost::filesystem::path absolute;
		boost::filesystem::path filename;
		bool has_include_guard;
	public:
		node_type(boost::filesystem::path const& absolute, boost::filesystem::path const& filename)
			: absolute(absolute), filename(filename), has_include_guard(false)
		{}
		operator boost::filesystem::path const&() const {
			return filename;
		}
		operator std::string() const {
			return filename.generic_string();
		}
		friend bool operator==(node_type const& lhs, node_type const& rhs) {
			return lhs.absolute == rhs.absolute;
		}
		friend bool operator==(node_type const& lhs, boost::filesystem::path const& rhs) {
			return lhs.absolute == rhs;
		}
		friend bool operator==(boost::filesystem::path const& lhs, node_type const& rhs) {
			return lhs == rhs.absolute;
		}
		friend bool operator!=(node_type const& lhs, node_type const& rhs) {
			return !(lhs == rhs);
		}
		friend bool operator!=(node_type const& lhs, boost::filesystem::path const& rhs) {
			return !(lhs == rhs);
		}
		friend bool operator!=(boost::filesystem::path const& lhs, node_type const& rhs) {
			return !(lhs == rhs);
		}
		template<typename Elem, typename Traits>
		friend std::basic_ostream<Elem, Traits>& operator<<(std::basic_ostream<Elem, Traits>& lhs, node_type const& rhs) {
			return lhs << rhs.filename.generic_string();
		}
	};
	typedef std::pair<int, int> edge_type;
	typedef boost::adjacency_list<
		boost::vecS,
		boost::vecS,
		boost::bidirectionalS,
		boost::no_property
	> graph_type;
private:
	std::vector<node_type> node_list_;
	std::vector<edge_type> edge_list_;
	std::vector<int> current_list_;
	int current_;
public:
	explicit include_graph_hooks(boost::filesystem::path const& start)
		: node_list_{node_type{boost::filesystem::absolute(start), start.filename()}}
		, edge_list_{}
		, current_list_{0}
		, current_(0)
	{}
	std::vector<node_type> const&
	nodes() const {
		return node_list_;
	}
	std::vector<edge_type> const&
	edges() const {
		return edge_list_;
	}
	// グラフ生成
	template<typename Graph>
	Graph make_graph() const {
		return Graph(edge_list_.begin(), edge_list_.end(), node_list_.size());
	}
	graph_type make_graph() const {
		return make_graph<graph_type>();
	}
	// graphviz 出力
	void write_graphviz(std::ostream& out) const {
		boost::write_graphviz(
			out,
			make_graph<graph_type>(),
			boost::make_label_writer(&node_list_[0])
		);
	}
	// 非インクルードガード検出
	template<typename OutputIterator>
	void collect_no_include_guard_files(OutputIterator result) const {
		std::copy_if(
			node_list_.begin() + 1, node_list_.end(), result,
			[](node_type const& e) { return !e.has_include_guard; }
			);
	}
	// 循環インクルード検出
	template<typename OutputIterator>
	void collect_circulated_includes(OutputIterator result) const {
		boost::depth_first_search(
			make_graph<graph_type>(),
			boost::visitor(sprig::make_back_edge_recorder(result))
			);
	}
	// 孤立ファイル検出
	template<typename OutputIterator>
	void collect_isolated_files(OutputIterator result, boost::filesystem::path const& path) const {
		typedef boost::filesystem::recursive_directory_iterator iterator;
		for (auto it = iterator(path), last = iterator(); it != last; ++it) {
			if (!boost::filesystem::is_directory(*it)) {
				boost::filesystem::path abspath(boost::filesystem::absolute(*it));
				auto found = std::find(node_list_.begin(), node_list_.end(), abspath);
				if (found == node_list_.end()) {	// インクルードされていないならば結果に追加
					*result++ = abspath.generic_string();
				}
			}
		}
	}
public:
	// インクルードファイルパス設定処理をフック
	template<typename Context>
	bool locate_include_file(
		Context& ctx,
		std::string& file_path,
		bool is_system,
		char const* current_name,
		std::string& dir_path,
		std::string& native_name
		)
	{
		std::string filename = is_system ? ('<' + file_path + '>') : ('\"' + file_path + '\"');
		if (!base_type::locate_include_file(ctx, file_path, is_system, current_name, dir_path, native_name)) {
			return false;
		}
		dir_path = filename;	// インクルードディレクティブのテキストで上書き
		return true;
	}
	// インクルードファイル解析開始をフック
	template<typename Context>
	void opened_include_file(
		Context const& /*ctx*/,
		std::string const& relname,
		std::string const& absname,
		bool /*is_system_include*/
		)
	{
		boost::filesystem::path abspath(boost::filesystem::absolute(absname));
		auto found = std::find(node_list_.begin(), node_list_.end(), abspath);
		auto to = std::distance(node_list_.begin(), found);
		if (found == node_list_.end()) {	// 最初のインクルードならばノードに追加
			node_list_.emplace_back(abspath, relname);
		}
		edge_list_.emplace_back(current_list_.back(), to);
		current_list_.push_back(to);	// カレントを更新
		current_ = to;
	}
	// インクルードファイル解析完了をフック
	template<typename Context>
	void returning_from_include_file(Context const& /*ctx*/) {
		current_ = current_list_.back();
		current_list_.pop_back();	// カレントを戻す
	}
	// インクルードガード検出をフック
	template<typename Context>
	void detected_include_guard(
		Context const& /*ctx*/,
		std::string const& /*filename*/,
		std::string const& /*include_guard*/
		)
	{
		node_list_.at(current_).has_include_guard = true;
	}
	template<typename Context, typename Token>
	void detected_pragma_once(
		Context const& /*ctx*/,
		Token const& /*pragma_token*/,
		std::string const& /*filename*/
		)
	{
		node_list_.at(current_).has_include_guard = true;
	}
};

// システムインクルードパスの取得
template<typename OutputIterator>
void collect_sysinclude_paths(OutputIterator result, std::string const& command = "g++") {
	{
		std::ofstream ofs("_collect_sysinclude_paths.cpp");
	}
	std::system((command + " -v -E _collect_sysinclude_paths.cpp 1> /dev/null 2> _collect_sysinclude_paths").c_str());
	{
		std::ifstream ifs("_collect_sysinclude_paths");
		std::string text(
			std::istreambuf_iterator<char>(ifs.rdbuf()),
			std::istreambuf_iterator<char>()
			);
		auto rng = boost::make_iterator_range(text);
		rng = sprig::find_skip(rng, boost::algorithm::first_finder("#include <...>"));	// インクルードパスの始点までスキップ
		rng = sprig::find_skip(rng, boost::algorithm::first_finder("\n"));
		while (boost::algorithm::starts_with(rng, " ")) {
			auto found = sprig::find_between(
				rng,
				boost::algorithm::token_finder(boost::algorithm::is_space(), boost::algorithm::token_compress_on),
				boost::algorithm::first_finder("\n")
				);
			*result++ = std::string(boost::begin(found), boost::end(found));
			rng = boost::make_iterator_range(boost::end(found), boost::end(rng));
			rng = sprig::find_skip(rng, boost::algorithm::first_finder("\n"));
		}
	}
}

int main(int argc, const char* argv[]) {
	std::string src;
	std::string command;
	std::string text;

	if (argc >= 2) {
		src = argv[1];

		// ファイルの内容を全部 text に読み込む
		std::ifstream ifs(argv[1]);
		text = std::string(
			std::istreambuf_iterator<char>(ifs.rdbuf()),
			std::istreambuf_iterator<char>()
			);
	}
	if (argc >= 3) {
		command = argv[2];
	}

	try {
		// プリプロセッサを用意
		typedef boost::wave::context<
			std::string::iterator,
			boost::wave::cpplexer::lex_iterator<boost::wave::cpplexer::lex_token<> >,
			boost::wave::iteration_context_policies::load_file_to_string,
			::include_graph_hooks
		> context_type;
		context_type ctx(text.begin(), text.end(), src.c_str(), ::include_graph_hooks(src));

		// ランゲージの設定
		ctx.set_language(
			boost::wave::language_support(
				boost::wave::support_cpp11
				| boost::wave::support_option_include_guard_detection	// インクルードガード検出
				)
			);
		// インクルードパスの設定
		if (!command.empty()) {
			std::cout
				<< "collect command :\n"
				<< command << "\n"
				;
		}
		{
			std::vector<std::string> list;
			if (command.empty()) {
				::collect_sysinclude_paths(std::back_inserter(list));
			} else {
				::collect_sysinclude_paths(std::back_inserter(list), command);
			}
			std::cout
				<< "sysinclude paths :\n"
				;
			for (auto&& e : list) {
				std::cout
					<< " " << e << "\n"
					;
				ctx.add_sysinclude_path(e.c_str());
			}
			std::cout
				<< std::flush
				;
		}

		if (!src.empty()) {
			// プリプロセスを走らせる
			for (auto&& e : ctx) {
				//std::cout << e.get_value();
			}
		}

		for ( ; ;) {
			std::cout
				<< "> "
				<< std::flush
				;
			std::string line;
			std::getline(std::cin, line);
			if (line.empty()) {
				break;
			}
			std::vector<std::string> tokens;
			boost::algorithm::split(tokens, line, boost::algorithm::is_space());
			if (tokens.at(0) == "find") {
				// インクルードファイルを検索
				if (tokens.size() < 2) {
					std::cout
						<< "missing parameter.\n"
						<< std::flush
						;
					continue;
				}
				std::cout
					<< "find <" << tokens.at(1) << "> :\n"
					;
				std::string filepath(tokens.at(1));
				std::string dirpath;
				if (!ctx.find_include_file(filepath, dirpath, true, 0)) {
					std::cout
						<< " not found\n"
						<< std::flush
						;
					continue;
				}
				std::cout
					<< " " << filepath << "\n"
					<< std::flush
					;
			} else if (tokens.at(0) == "graph") {
				// グラフ出力
				std::cout
					<< "graph output > out.graph.dot\n"
					;
				std::ofstream ofs("out.graph.dot");
				ctx.get_hooks().write_graphviz(ofs);
				std::cout
					<< std::flush
					;
			} else if (tokens.at(0) == "noguard") {
				// 非インクルードガードを出力
				std::vector<::include_graph_hooks::node_type> list;
				ctx.get_hooks().collect_no_include_guard_files(std::back_inserter(list));
				std::cout
					<< "no include guarde files (" << list.size() << ") :\n"
					;
				for (auto const& e : list) {
					std::cout
						<< " " << e << "\n"
						;
				}
				std::cout
					<< std::flush
					;
			} else if (tokens.at(0) == "circulated") {
				// 循環インクルードを出力
				std::vector<typename boost::graph_traits<::include_graph_hooks::graph_type>::edge_descriptor> list;
				ctx.get_hooks().collect_circulated_includes(std::back_inserter(list));
				auto g = ctx.get_hooks().make_graph();
				std::cout
					<< "circulated includes (" << list.size() << ") :\n"
					;
				for (auto const& e : list) {
					std::cout
						<< " " << boost::source(e, g) << "[" << ctx.get_hooks().nodes()[boost::source(e, g)] << "]\n"
						<< "  -> " << boost::target(e, g) << "[" << ctx.get_hooks().nodes()[boost::target(e, g)] << "]\n"
						;
				}
				std::cout
					<< std::flush
					;
			} else if (tokens.at(0) == "isolated") {
				// Sprout の孤立ファイルを出力
				std::cout
					<< "isolated files output > out.isolated.txt\n"
					;
				std::ofstream ofs("out.isolated.txt");
				// Sprout のシステムインクル－ドパスを取得
				std::string filepath("sprout/config.hpp");
				std::string dirpath;
				if (!ctx.find_include_file(filepath, dirpath, true, 0)) {
					std::cerr
						<< "#error sprout not found\n"
						<< std::flush
						;
					continue;
				}
				dirpath = boost::filesystem::path(filepath).parent_path().generic_string();
				// リスト出力
				std::vector<std::string> list;
				ctx.get_hooks().collect_isolated_files(std::back_inserter(list), dirpath);
				std::sort(list.begin(), list.end());
				std::copy(list.begin(), list.end(), std::ostream_iterator<std::string>(ofs, "\n"));
				std::cout
					<< std::flush
					;
			} else {
				std::cout
					<< "invalid command\n"
					<< std::flush
					;
			}
		}
	} catch (boost::wave::cpp_exception& e) {
		// プリプロセスでエラー発生
		std::cerr
			<< "#error " << e.file_name() << "(" << e.line_no() << "):" << e.description() << "\n"
			<< std::flush
			;
	}
}
