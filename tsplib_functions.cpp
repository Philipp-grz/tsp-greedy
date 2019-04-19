#include <iostream>
#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <memory>
#include "node.hpp"
#include "edge.hpp"
#include "graph.hpp"
#include "tsplib_functions.hpp"

																	// In der folgenden Funktion geben wir eine Tour im TSPLIB-Format aus.
void tour_output(const std::vector<Edge>& tour, const std::string& name, const std::string& comment, const int& dim, const std::string& type, const int& compl_cost)
{																	// Als Parameter benötigen wir dafür die Tour selbst sowie alle anzugebenden Daten.
	std::ofstream tour_out((name)+"_tour.txt");					// Hier öffnen bzw. erstellen ggf. die passende Datei zur Ausgabe.
	tour_out <<"NAME: "+name+"_tour\r\n"<<"COMMENT: "+comment+"\r\n"<<"TYPE: TSP\r\n"<<"DIMENSION: "<<dim<<"\r\n"<<"EDGE_WEIGHT_TYPE: "+type+"\r\n"<<"COSTS OF TOUR: "<<compl_cost<<"\r\n"<<"NODE_COORD_SECTION\r\n";
	for (auto b : tour)											// Hierüber schreiben wir alle Spezifikationen sowie die Gesamtlänge der Tour in die Datei.
	{																// Dann gehen wir die Tour nocheinmals durch und schreiben jeweils alle Kanten in eine neue Zeile der Datei.
		tour_out << b._node1->_index << " " << b._node2->_index<<" "<<b._cost<<"\r\n";
	}
	tour_out <<"EOF"<< "\r\n";										// Ans Ende noch das freiwillige "EOF"
}

std::unique_ptr<Graph> datei_einlesen (std::ifstream& datei)
{																	// Als Parameter erhält die Funktion Pointer auf alle Objekte, in die sie schreiben soll.
	std::string zeile;												// In diesem Hilfsstring speichern wir jeweils die aktuelle Zeile.
	std::unique_ptr<Graph> graph(new Graph);
	
	while (std::getline(datei, zeile))								// Wir gehen die Datei durch, bis wir ans Ende kommen.
	{
		if (zeile != "EOF") 										// Sollte in der aktuellen Zeile "EOF" stehen, hören wir auch auf.
		{
			zeile=lineprepare(zeile);								// Zunächst säubern wir die Zeile mit lineprepare
			std::stringstream ss(zeile);							// Dann erstellen wir uns einen stringstream aus der Zeile,
			std::string word;										// und als weiteren Hilfsstring word.
			ss >> word;												// Wir speichern nun das erste Wort der Zeile in word und werten es im folgenden aus:
			if (word == "NAME")
			{
				ss >> graph->_name;
			}										// Falls es "NAME" lautet, wird das darauf folgende Wort in die Variable name geschrieben.
			if (word == "COMMENT"){									// Analog verfahren wir bei "COMMENT", allerdings werden hier alle Wörter bis zum Ende
				while (not ss.eof()) 								// der Zeile reingeschrieben.
				{
					std::string temp;
					ss >> temp;
					graph->_comment = graph->_comment +" "+ temp;  
				}
			}	
			if (word == "TYPE"){									// Sollte nach "TYPE" etwas anderes als "TSP" kommen, weisen wir die Eingabe zurück,
				ss >> word;											// da wir nur das TSP betrachtet haben.
				if (word != "TSP"){
					std::cout <<"Ungültige Instanz! Bitte TSP-Instanz eingeben!"<<std::endl;
					return 0;
				}
			}
			if (word == "DIMENSION"){								// Die Dimension des Problems wird gespeichert
				ss >> word;
				graph->_dim=std::stoi(word);
			}
			if (word == "EDGE_WEIGHT_TYPE"){						// Falls der EDGE_WEIGHT_TYPE ein anderer als EUC_2D oder CEIL_2D ist, weisen wir die Eingabe ebenfalls zurück.
				ss >> word;											// Den EDGE_WEIGHT_TYPE merken wir uns in type, da anhand dessen die Kosten der Kanten berechnen.
				if (word != "EUC_2D"){
					if (word != "CEIL_2D"){
						std::cout <<"Ungültige Instanz! Bitte eukl. TSP-Instanz eingeben!"<<std::endl;
						return 0;
					}
				}
				graph->_type = word;
			}
			if (word == "NODE_COORD_SECTION"){						// Nach "NODE_COORD_SECTION" kommen die Knoten, also beginnen wir eine Schleife:
				while (std::getline(datei, zeile))					// Solange es noch Zeilen gibt, gehen wir die Datei weiter durch
				{
					std::stringstream sst(zeile);					// und speichern die aktuelle Zeile als stringstream.
					sst>>word;										// Falls EOF erreicht wird, hören wir auf.
					if (word != "EOF") 								
					{												// Ansonsten lesen wir den stringstream in die folgenden Variablen aus:
						int index_temp;								// für den Index des Knotens
						double coord1_temp;							// die Koordinaten des Knotens
						double coord2_temp;
						std::stringstream ss(zeile);				// Wir erzeugen den stringstream nochmals neu, da wir eben bereits das erste Wort entfernt hatten.
						ss >> index_temp >> coord1_temp >> coord2_temp;	// Nun speichern wir die Werte analog zur Dokumentation in den Variablen.
						//std::unique_ptr<Node> node_temp(new Node(index_temp, coord1_temp, coord2_temp,NULL ,0, 0));	// Hier erstellen wir einen temporären Knoten mit den aktuellen Werten,
						Node* node_temp = new Node(index_temp, coord1_temp, coord2_temp,NULL ,0, 0);
						node_temp->_parent=node_temp;				// und setzen den parent-Pointer zunächst auf sich selbst (vgl. Union-Find)
						//std::cout<<node_temp.get()->_parent<<std::endl;
						graph->_v.push_back(*(node_temp));			// Anschließend hängen wir den Knoten an den Vector dran.
					}
			
				}
			}
		}	
	}
	return graph;														// Falls keine Dateizurückweisung stattfand, geben wir die 1 zurück.
}

std::string lineprepare (std::string line)
{							// In dieser Funktion wird jeweils eine Zeile aus der Eingabe vorbereitet,
																	// indem zunächst alle Doppelpunkte gelöscht werden.
	line.erase(std::remove(line.begin(), line.end(), ':'), line.end());
	
	for ( unsigned int a = 0; a < line.size(); a++ )				// Anschließend werden mehrfache Leerzeichen gelöscht,
	{																// um das Auslesen der Daten zu vereinfachen
        if ( line.at(a) == ' ' )
		{
			a++;
			if( line.at(a) == ' ' )
			{
				line.erase(a,1);
				a -= 1;
	        }
		}
	}
	return line;													// Am Ende wird der gesäuberte String zurückgegeben
}