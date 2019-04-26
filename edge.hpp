#ifndef _edge_hpp_
#define _edge_hpp_

#include "node.hpp"

class Edge {														// Dies ist meine Kanten-Klasse. Jede Kante erhält als Konstruktor-Elemente
	public: 														// zwei Node-Pointer auf die Knoten, die sie verbindet,
		Edge (Node* node1, Node* node2, const int cost);					// sowie die Länge der Kante als int.
		~Edge();
		Node* _node1;
		Node* _node2;
		int _cost;
};
#endif
