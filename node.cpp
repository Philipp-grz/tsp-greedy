#include <iostream>
#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include "node.hpp"

Node::Node (int index, double coord1, double coord2, Node* parent, int rank, int grad)
: _index(index), _coord1(coord1), _coord2(coord2), _parent(parent), _rank(rank), _grad(grad)
{}
Node::~Node()
{}

Node* Node::find (){												// Funktion des find für Union-find																// Es wird ein Knotenindex und eine Knotenmenge übergeben,
	Node* v = this;
	if (v->_index != (v->_parent)->_index) 							// Wir vergleichen den Knoten mit seinem Parent
	{																// (über den Index), falls diese nicht identisch sind
		v->_parent=v->_parent->find();								// folgt der rekursive find-Aufruf
	}																		
	return v->_parent;												// Am Ende wird der aktuelle parent-Pointer zurückgegeben.
}
