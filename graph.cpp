#include <iostream>
#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include "node.hpp"
#include "edge.hpp"
#include "graph.hpp"


	Graph::Graph()
	: _e(std::vector<Edge>()), _v(std::vector<Node>()), _name(""), _comment(""), _dim(0), _type("")
	{}
	Graph::Graph(std::vector<Node> nodes, std::vector<Edge> edges, std::string name, std::string comment, int dim, std::string type)
	: _e(edges), _v(nodes), _name(name), _comment(comment), _dim(dim), _type(type)
	{}

	void Graph::edge_sort ()
	{
		struct
		{														// Hier definiere ich eine Hilfsstruktur,
			bool operator()(Edge a, Edge b) const						// um die Kanten gleich nach ihren Kosten mit
				{   														// std::sort sortieren zu können.
					return a._cost < b._cost;								// Die Kosten beider Kanten sollen verglichen werden,
				}   														// und der Rückgabewert sagt, ob Kante a (die Erste)
		} 																// geringere Kosten hat als Kante b (die Zweite).
		edgesort;

		std::sort(_e.begin(), _e.end(), edgesort);
	}

	void Graph::make_edges_compl_graph ()
{																	// Die Funktion erhält Pointer auf das Kanten-Array, das Knoten-Array und alle anderen wichtigen Variablen.
	std::vector<Edge> edges;
	for (int i=0; i<_dim; i++)										// Da von jedem Knoten zu jedem anderen Knoten eine Kante verläuft,
	{																// benötigen wir zwei for-Schleifen, welche jeweils die Knotenanzahl durchlaufen
		for (int j=0; j<_dim; j++)
		{
			if (i!=j)												// Dieser Fall wird ausgeschlossen, da Kanten zu sich selbst im TSP irrelevant sind
			{
				Node & node1_tmp= _v[i];						// Dies sind Pointer auf die beiden aktuellen Knoten, wir werden sie nachher nutzen,
				Node* node2_tmp=&(_v[j]);						// wenn wir die Kante erstellen.
				int cost_temp=0;									// Die Kosten der Kante sind zunächst 0.

				if (_type == "EUC_2D")								// Je nachdem in welchem Edge-Weight-Type wir sind, müssen die Kosten anders berechnet werden.
				{													// Dies ist einfach die Berechnung der Kosten für EUC_2D, wie sie in der TSPLIB Dokumentation beschrieben wird.
					int xd=((node1_tmp._coord1)-(node2_tmp->_coord1));
					int yd=((node1_tmp._coord2)-(node2_tmp->_coord2));
					cost_temp= (int) ((sqrt(xd*xd + yd*yd))+0.5);	// Es wird auf die nächste Ganzzahl gerundet.
				}
				if (_type == "CEIL_2D")								// Falls wir als Edge-Weight-Type CEIL_2D haben, wird am Ende auf jeden Fall aufgerundet.
				{
					int xd=((node1_tmp._coord1)-(node2_tmp->_coord1));
					int yd=((node1_tmp._coord2)-(node2_tmp->_coord2));
					cost_temp= ceil (sqrt(xd*xd + yd*yd));
				}


				Edge edge_temp (&node1_tmp, node2_tmp, cost_temp);	// Mit der berechneten Länge sowie den beiden Knoten-Pointern
				edges.push_back(edge_temp);						// wird nun die Kante erstellt und am Ende des Array angehangen.
			}
		}
	}
	_e = edges;;
}


