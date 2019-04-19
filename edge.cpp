#include <iostream>
#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include "node.hpp"
#include "edge.hpp"
														// zwei Node-Pointer auf die Knoten, die sie verbindet,
		Edge::Edge (Node* node1, Node* node2, int cost)					// sowie die Länge der Kante als int.
		: _node1(node1), _node2(node2), _cost(cost)
		{}
		Edge::~Edge()
		{}