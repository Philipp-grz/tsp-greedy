#include <iostream>
#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <math.h>
#include "node.hpp"
#include "edge.hpp"
#include "graph.hpp"
#include "greedy_tsp.hpp"
#include "naive_tsp.hpp"
#include "tsplib_functions.hpp"


int main(const int count, char ** args){
	
	std::string dateiname;											// Hier wird der Dateiname gespeichert werden										// In diesen die Kanten,
	std::vector<Edge> tour;											// und in diesen die fertige Tour.
	int compl_cost=0;												// Hier speichern wir die Gesamtkosten der Tour.
	
	if (count == 2){ dateiname = args[1];}							// Überprüfe, ob der Aufruf genau eine Datei übergeben hat,
	else {															// und falls nicht, Fehlermeldung und Ende des Programmes.
		std::cout<< "Ungültige Eingabe"<< std::endl;
		return 0;
	}
	
	std::ifstream datei(dateiname);									// Ließt die angegebene Datei ein und erzeugt das zugehörige ifstream-Objekt
	
	if (not datei)													// Fehlermeldung und Programmabbruch, falls angegebene Datei nicht existiert
	{
		std::cout <<"Keine Datei " << dateiname << " gefunden!" <<std::endl;
		return 0;
	}
	
	std::unique_ptr<Graph> graph = datei_einlesen(datei);	// Wir schreiben die Datei in unsere Variablen, und überprüfen gleichzeitig, ob es eine gültige TSP-Datei ist.
	
	std::cout << "Naive Tourlänge (1...n) beträgt "<<naiv_TSP(graph->_v, graph->_type)<<std::endl;	// Hier geben wir die Länge einer Tour durch die Knoten der Reihenfolge 1...n aus.
	
	graph->make_edges_compl_graph();							// Hier erstellen wir alle Kanten eines vollständigen Graphen zu den gegebenen Knoten.
	
	graph->edge_sort();												// Die Kanten werden sortiert,
	
	tour = greedy_TSP(graph->_e, graph->_dim, compl_cost);					// und der Greedy-Algo wird ausgeführt.
	
	tour_output(tour, graph->_name, graph->_comment, graph->_dim, graph->_type, compl_cost);	// Am Ende wird die gefundene Tour ausgegeben.
	
	std::cout <<"Greedy-Tourlänge beträgt "<<compl_cost<<std::endl;
	
	return 0;
}