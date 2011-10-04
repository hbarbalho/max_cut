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
using namespace std;

class Instance {
public:
	Edge* bestEdge();
	Edge* bestEdge(int);
	int numEdges();
	int numVertex();
	int edgeCost(int,int);
	Instance(string arq_name);
	virtual ~Instance();
private:
	string arq_name;
	int num_edges;
	int num_vertex;
	Edge*** matriz;
	Edge** order;
	void loadFile();
};

#endif /* INSTANCE_H_ */
