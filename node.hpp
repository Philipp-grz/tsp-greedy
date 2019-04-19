#ifndef _node_hpp_
#define _node_hpp_

class Node {														// Dies ist meine Knoten-Klasse. Jeder Knoten erhält als
	public: 														// Konstruktor-Elemente einen Index (1:1 aus der Datei),
		Node (const int index, const double coord1, const double coord2, Node* parent, int rank, int grad);
		~Node();
		int _index;
		double _coord1;
		double _coord2;	
		Node* _parent;
		int _rank;
		int _grad;
		
								// In dieser Funktion sortieren wir gegebene Kanten nach ihrem Gewicht.
		Node* find ();
};
#endif