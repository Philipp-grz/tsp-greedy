#ifndef _graph_hpp_
#define _graph_hpp_

#include <vector>
#include <string>

#include "node.hpp"
#include "edge.hpp"

enum class EdgeWeightType {
   EUC_2D,
   EUC_RANDOM,
   hans
};
using NodeId = std::size_t;
using Weight = int;

class Graph{
	public:
		Graph();
		Graph(std::vector<Node> nodes, std::vector<Edge> edges, const std::string name, const std::string comment, const int dim, const std::string type);
      Graph(NodeId num_nodes);

      NodeId num_nodes() const;

      Node & node(NodeId node_id);
      Node const & node(NodeId node_id) const;

      void add_edge(NodeId a, NodeId b, Weight weight);


   // private:
		std::vector<Edge> _e;
		std::vector<Node> _v;
		std::string _name;
		std::string _comment;
		int _dim;
		std::string _type;

		void edge_sort ();
		void make_edges_compl_graph ();


};


// Graph parse_tsplib_file() {
//    ...
//    Graph result{num_nodes};
//
//    ...
//    result.add_edge(i, j, weight);
//    ...
//
//    return result;
// }

#endif
