#include "wgraph.h"

// 
//  - Distance between two vertices
//    d(sv, v) = Dd[tv]
//
 weight
	Dijkstra(wgraph& G, vertex sv, vertex tv )
{
	vertex vn = G.size();
	//  Inialize vertices as unlabeled
	vector<bool> Dl(vn, false);
	//  Infinity for lengths
	weight infty = UINT_MAX;
	//  Inialitize distance to sv to infty for all vertices but sv
	vector<weight> Dd(vn, infty);
	Dd[sv] = 0;
	//  Vertex mdv with minimum distance to starting vertex sv: sv
	vertex mdv = sv;
	do {
		//  Label mdv and check distance from sv to its adjacents	
		Dl[mdv] = true;
		for (ind i = 0; i < G[mdv].size(); i++)
			if (Dd[G[mdv][i].first] > Dd[mdv] + G[mdv][i].second)
				Dd[G[mdv][i].first] = Dd[mdv] + G[mdv][i].second;
		//  Find new not labeled vertex mdv with minimum distance to sv
		weight md = infty;
		mdv = vn;
		for (vertex v = 0; v < vn; v++)
			if (md > Dd[v] && !Dl[v]) {
				md = Dd[v];
				mdv = v;
			}
	} while (mdv < vn && mdv != tv  );
	return Dd[tv];
}

 
// 
//  - Maximum distance from starting vertex
//    Mdsv = max_v d(sv, v) = max_v Dd[v]
//
 weight
	 Dijkstra(wgraph& G, vertex sv )
 {
	 vertex vn = G.size();
	 //  Inialize vertices as unlabeled
	 vector<bool> Dl(vn, false);
	 //  Infinity for lengths
	 weight infty = UINT_MAX;
	 //  Inialitize distance to sv to infty for all vertices but sv
	 vector<weight> Dd(vn, infty);
	 Dd[sv] = 0;
	 //  Vertex mdv with minimum distance to starting vertex sv: sv
	 vertex mdv = sv;
	 do {
		 //  Label mdv and check distance from sv to its adjacents	
		 Dl[mdv] = true;
		 for (ind i = 0; i < G[mdv].size(); i++)
			 if (Dd[G[mdv][i].first] > Dd[mdv] + G[mdv][i].second)
				 Dd[G[mdv][i].first] = Dd[mdv] + G[mdv][i].second;
		 //  Find new not labeled vertex mdv with minimum distance to sv
		 weight md = infty;
		 mdv = vn;
		 for (vertex v = 0; v < vn; v++)
			 if (md > Dd[v] && !Dl[v]) {
				 md = Dd[v];
				 mdv = v;
			 }
	 } while (mdv < vn);

	 weight Mdsv = 0;
	 for (ind i = 0; i < vn; i++) {
		if (Mdsv < Dd[i])
			Mdsv = Dd[i];
		if (Dd[i] == infty)
			i = vn;
	}

	 return Mdsv;
 }
//
//   Diameter
//   D = max_sv_tv d(sv,tv) = max_sv Mdsv
//
 weight 
	 Diameter(wgraph& G)
 {
	 weight D = 0;
	 vertex vn = G.size();
	 weight infty = UINT_MAX;
	 for (vertex sv = 0; sv < vn; sv++) {
		 weight Mdsv = Dijkstra(G, sv);
		 if (Mdsv == infty)
			 return Mdsv;
		 if (D < Mdsv)
			 D = Mdsv;
	 }
	 return D;
 }

//
//  Minimal path weights by Dijkstra's method to stream
//  - Distances to all vertices: weights of minimal paths
//
void
	Dijkstra(wgraph& G, vertex sv, ofstream& fout)
{
	vertex vn = G.size();
	//  Inialize vertices as unlabeled
	vector<bool> Dl(vn, false);
	//  Infinity for lengths
	weight infty = UINT_MAX;
	//  Inialitize distance to sv to infty for all vertices but sv
	vector<weight> Dd(vn, infty);
	Dd[sv] = 0;
	//  Vertex mdv with minimum distance to starting vertex sv: sv
	vertex mdv = sv;
	do {
		//  Label mdv and check distance from sv to its adjacents	
		Dl[mdv] = true;
		for (ind i = 0; i < G[mdv].size(); i++)
			if (Dd[G[mdv][i].first] > Dd[mdv] + G[mdv][i].second)
				Dd[G[mdv][i].first] = Dd[mdv] + G[mdv][i].second;
		//  Find new not labeled vertex mdv with minimum distance to sv
		weight md = infty;
		mdv = vn;
		for (vertex v = 0; v < vn; v++)
			if (md > Dd[v] && !Dl[v]) {
				md = Dd[v];
				mdv = v;
			}
	} while (mdv < vn);
	fout << "\nDistances from starting vertex " << sv << endl;
	for (vertex v = 0; v < vn; v++){
		if (Dd[v] < infty)
			fout << v << "\t" << Dd[v] << endl;
		else
			fout << v << "\tNot connected" << endl;
	}
}

//   
//   Minimal paths from/to starting vertex
//
void
	Dijkstra_Tree(wgraph& G, vertex sv, ofstream& fout)
{
//  IMPLEMENTEU  LA FUNCI� A PARTIR DE L'ANTERIOR
	vertex vn = G.size();
	//  Inialize vertices as unlabeled
	vector<bool> Dl(vn, false);
	vector<vertex> Dp(vn, vn);
	//  Infinity for lengths
	weight infty = UINT_MAX;
	//  Inialitize distance to sv to infty for all vertices but sv
	vector<weight> Dd(vn, infty);
	Dd[sv] = 0;
	Dp[sv] = sv;
	//  Vertex mdv with minimum distance to starting vertex sv: sv
	vertex mdv = sv;
	do {
		//  Label mdv and check distance from sv to its adjacents	
		Dl[mdv] = true;
		for (ind i = 0; i < G[mdv].size(); i++)
			if (Dd[G[mdv][i].first] > Dd[mdv] + G[mdv][i].second) {
				Dd[G[mdv][i].first] = Dd[mdv] + G[mdv][i].second;
				Dp[G[mdv][i].first] = mdv;
			}
		//  Find new not labeled vertex mdv with minimum distance to sv
		weight md = infty;
		mdv = vn;
		for (vertex v = 0; v < vn; v++)
			if (md > Dd[v] && !Dl[v]) {
				md = Dd[v];
				mdv = v;
			}
	} while (mdv < vn);
	fout << "\nDistances from starting vertex " << sv << endl;
	for (vertex v = 0; v < vn; v++){
		if (Dd[v] < infty)
			fout << v << "\t" << Dd[v] << endl;
		else
			fout << v << "\tNot connected" << endl;
	}

	for (vertex v = 0; v < vn; v++){
		fout << v ;
		if (Dp[v] <  vn) {
			vertex pv = v;
			while (pv != sv) {
				pv = Dp[pv];
				fout << " - " << pv;
			}
			fout << endl;
		}
		else
			fout << v << "\tNot connected" << endl;
	}
}



