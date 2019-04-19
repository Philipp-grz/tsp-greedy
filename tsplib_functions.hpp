#ifndef _tsplib_functions_hpp_
#define _tsplib_functions_hpp_

std::unique_ptr<Graph> datei_einlesen (std::ifstream& datei);
void tour_output(const std::vector<Edge>& tour, const std::string& name, const std::string& comment, const int& dim, const std::string& type, const int& compl_cost);
std::string lineprepare (std::string line);
#endif