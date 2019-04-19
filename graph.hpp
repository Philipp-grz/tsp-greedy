#ifndef _graph_hpp_
#define _graph_hpp_

class Graph{
	public:
		Graph();
		Graph(std::vector<Node> nodes, std::vector<Edge> edges, const std::string name, const std::string comment, const int dim, const std::string type);
		~Graph();
		
		std::vector<Edge> _e;
		std::vector<Node> _v;
		std::string _name;
		std::string _comment;
		int _dim;
		std::string _type;
		
		
		
		void edge_sort ();	
		void make_edges_compl_graph ();
		
	
};
#endif