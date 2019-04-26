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
{																	// Als Parameter �bergeben wir Pointer auf die Kanten, die Dimension,
	std::vector<Edge> tour;
	int tour_index=0;												// sowie die "Zielvariablen" f�r vollst�ndige Kosten und die Tour.
																	// Den tour_index initialisieren wir mit 0, hierin z�hlen wir, wie viele Kanten unsere Teiltouren bereits haben.
	for (auto const & aktuelle_kante : edges)								// Die (vorher sortierten) Kanten gehen wir nun einmal vollst�ndig durch:
	{
		if (tour_index!=dim)										// Sollte unsere Tour allerdings bereits dim viele Kanten haben, also vollst�ndig sein, brauchen wir nichts weiter zu tun.
		{
			Node & n1= *aktuelle_kante._node1;							// Dies sind die beiden Knoten, welche die aktuelle Kante verbindet.
			Node* n2=aktuelle_kante._node2;

			if (((n1)._grad<2)&&((*n2)._grad<2))					// Sollte mindestens einer der beiden Knoten bereits Grad 2 haben, ist die Kante f�r uns uninteressant,
			{														// da in einer TSP-Tour am Ende kein Knoten einen anderen Grad als 2 hat.
            auto const p1 = n1._parent->find();
            auto const p2 = n2->_parent->find();
				if ((p1 != p2) or ((p1 == p2) and tour_index==(dim-1))) // Ebenfalls pr�fen wir ob die Knoten zusammenh�ngend sind (mithilfe von Union-Find).
				{													// Sind sie nicht zusammenh�ngend, nutzen wir die aktuelle Kante. Sind sie zwar zusammenh�ngend, aber es fehlt nur noch eine Kante zur vollst�ndigen Tour, nehmen wir die Kante ebenfalls.
					tour.push_back(aktuelle_kante);				// Wir f�gen die Kante dann also in unseren Ziel-Vektor tour ein.
					compl_cost=compl_cost+aktuelle_kante._cost;	// Au�erdem erh�hen wir die Gesamtkosten der Tour um die Kosten der Kante
					tour_index++;									// und erh�hen den Tour-Index sowie die Knotengrade der beiden Knoten.
					n1._grad++;
					n2->_grad++;
					Node* n1_repr=n1.find();						// Dann f�hren wir noch das kanonische "Union-by-Rank" aus, um die Knoten
					Node* n2_repr=n2->find();						// auch in der Union-Find Struktur zusammenh�ngend zu haben.
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
