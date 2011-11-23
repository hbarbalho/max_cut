/*
 * Instance.h
 *
 *  Created on: Sep 19, 2011
 *      Author: hugo
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <string.h>
#include <iostream>
#include "Edge.h"
#include "Vertex.h"
using namespace std;

class Instance {
public:
	Edge* bestEdge();
	Edge* bestEdge(int);
	Vertex* bestVertex(int);
	Vertex* bestVertex();
	Vertex* getVertex(int);
	int numEdges();
	int numVertex();
	void sortVertex();
	void restoreVertexs();
	int edgeCost(int,int);
	bool has_edge(int i,int j);
	Instance(string arq_name);
	virtual ~Instance();
private:
	string arq_name;
	int num_edges;
	int num_vertex;
	Edge*** matriz;
	Edge** order;
	Vertex** v_order;
	Vertex** vertexs;

	void loadFile();
};

#endif /* INSTANCE_H_ */
