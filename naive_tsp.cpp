#include <iostream>
#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include "node.hpp"

int naiv_TSP (const std::vector<Node>& nodes, const std::string& type)			// In dieser Funktion bestimmen wir die Länge einer Tour durch die Knoten in der Reihenfolge 1...n
{																	// Dazu übergeben wir neben den Knoten nur den EDGE_WEIGHT_TYPE.
	int length=0;													// Zunächst initialisieren wir alle Variablen.
	int j=0;
	
	for (unsigned int i=0; i<nodes.size(); i++)					// Dann gehen wir die Knotenmenge einmal durch, und bestimmen, in Abhängigkeit vom EDGE_WEIGHT_TYPE,
	{																// jeweils die Länge der Kante vom Knoten i zum Knoten i+1. Falls i der letzte Knoten ist, nehmen wir die Kante zum ersten Knoten.
		if (i+1<nodes.size())
		{
			j=i+1;	
		}
		else 
		{
			j=0;	
		}
		
		int cost_temp=0;
		if (type == "EUC_2D")										// Die Berechnung der Kantenlänge erfolgt analog zu weiter oben und zur TSPLIB-Dokumentation.
		{
			int xd=((nodes[i]._coord1)-(nodes[j]._coord1));
			int yd=((nodes[i]._coord2)-(nodes[j]._coord2));
			cost_temp= (int) ((sqrt(xd*xd + yd*yd))+0.5);
		}
		else
		{
			if (type == "CEIL_2D")
			{
				int xd=((nodes[i]._coord1)-(nodes[j]._coord1));
				int yd=((nodes[i]._coord2)-(nodes[j]._coord2));
				cost_temp= ceil (sqrt(xd*xd + yd*yd));
			}
		}
		
		length=length+cost_temp;									// Die aktuelle Länge wird auf die Gesamtlänge addiert
	}	
	return length;													// und diese dann zurückgegeben.
}