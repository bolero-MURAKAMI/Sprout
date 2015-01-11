/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef TOOLS_SPRIG_GRAPH_BACK_EDGE_RECORDER_HPP
#define TOOLS_SPRIG_GRAPH_BACK_EDGE_RECORDER_HPP

#include <boost/graph/depth_first_search.hpp>

namespace sprig {
	//
	// back_edge_recorder
	//
	template<typename OutputIterator>
	struct back_edge_recorder
		: public boost::default_dfs_visitor
	{
	private:
		OutputIterator out_;
	public:
		explicit back_edge_recorder(OutputIterator out)
			: out_(out)
		{}
		template<typename Edge, typename Graph>
		void back_edge(Edge const& e, Graph const&) {
			*out_++ = e;
		}
	};
	//
	// make_back_edge_recorder
	//
	template<typename OutputIterator >
	inline sprig::back_edge_recorder<OutputIterator>
	make_back_edge_recorder(OutputIterator out) {
		return sprig::back_edge_recorder<OutputIterator>(out);
	}
}	// namespace sprig

#endif	// #ifndef TOOLS_SPRIG_GRAPH_BACK_EDGE_RECORDER_HPP
