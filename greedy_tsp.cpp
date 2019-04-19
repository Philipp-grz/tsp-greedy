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
#include "greedy_tsp.hpp"


std::vector<Edge> greedy_TSP (std::vector<Edge> &edges, const int dim, int& compl_cost)
{																	// Als Parameter übergeben wir Pointer auf die Kanten, die Dimension,
	std::vector<Edge> tour;
	int tour_index=0;												// sowie die "Zielvariablen" für vollständige Kosten und die Tour.
																	// Den tour_index initialisieren wir mit 0, hierin zählen wir, wie viele Kanten unsere Teiltouren bereits haben.
	for (auto aktuelle_kante : edges)								// Die (vorher sortierten) Kanten gehen wir nun einmal vollständig durch:
	{
		if (tour_index!=dim)										// Sollte unsere Tour allerdings bereits dim viele Kanten haben, also vollständig sein, brauchen wir nichts weiter zu tun.
		{
			Node* n1=aktuelle_kante._node1;							// Dies sind die beiden Knoten, welche die aktuelle Kante verbindet.
			Node* n2=aktuelle_kante._node2;
			
			if (((*n1)._grad<2)&&((*n2)._grad<2))					// Sollte mindestens einer der beiden Knoten bereits Grad 2 haben, ist die Kante für uns uninteressant,
			{														// da in einer TSP-Tour am Ende kein Knoten einen anderen Grad als 2 hat.
				if (((n1->_parent->find())!=(n2->_parent->find()))||((((n1->_parent->find())==(n2->_parent->find())))&&tour_index==(dim-1))) // Ebenfalls prüfen wir ob die Knoten zusammenhängend sind (mithilfe von Union-Find). 
				{													// Sind sie nicht zusammenhängend, nutzen wir die aktuelle Kante. Sind sie zwar zusammenhängend, aber es fehlt nur noch eine Kante zur vollständigen Tour, nehmen wir die Kante ebenfalls.
					tour.push_back(aktuelle_kante);				// Wir fügen die Kante dann also in unseren Ziel-Vektor tour ein.
					compl_cost=compl_cost+aktuelle_kante._cost;	// Außerdem erhöhen wir die Gesamtkosten der Tour um die Kosten der Kante
					tour_index++;									// und erhöhen den Tour-Index sowie die Knotengrade der beiden Knoten.
					n1->_grad++;
					n2->_grad++;
					Node* n1_repr=n1->find();						// Dann führen wir noch das kanonische "Union-by-Rank" aus, um die Knoten
					Node* n2_repr=n2->find();						// auch in der Union-Find Struktur zusammenhängend zu haben.
					if ((*n1_repr)._rank>(*n2_repr)._rank)
					{
						(*n2_repr)._parent=n1_repr;
					}
					else 
					{
						(*n1_repr)._parent=n2_repr;
						if ((*n1_repr)._rank==(*n2_repr)._rank)
						{
							(*n2_repr)._rank++;
						}
					}
				}
			}
		}
	}
	return tour;	
}