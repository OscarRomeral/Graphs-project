#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>
 using namespace std;
 typedef unsigned int vertex;
 typedef unsigned int edge;
 typedef unsigned int ind; 
 typedef unsigned int degree; 
 typedef unsigned int component;
 typedef unsigned int weight;
 typedef vector<vector<pair<vertex,weight> > > wgraph;
 wgraph wgraph_complete( ind n,  weight Mw );
 wgraph wgraph_read( string fname );
 void wgraph_write(  wgraph& G, ofstream& fout );
 weight	Dijkstra(wgraph& G, vertex sv, vertex tv);
 weight Dijkstra(wgraph& G, vertex sv);
 weight Diameter(wgraph& G);
 void Dijkstra(wgraph& G, vertex sv, ofstream& fout);
 void Dijkstra_Tree(wgraph& G, vertex sv, ofstream& fout);
 weight Kruskal_Trees(wgraph& G, ofstream& fout);
 weight Prim_Trees(wgraph& G, ofstream& fout);
