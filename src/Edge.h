/*
 * Edge.h
 *
 *  Created on: Oct 2, 2011
 *      Author: hugo
 */

#ifndef EDGE_H_
#define EDGE_H_

class Edge {
public:
	int i,j,cost;
	Edge(int,int,int);
	virtual ~Edge();
};

#endif /* EDGE_H_ */
