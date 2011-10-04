/*
 * Instance.cpp
 *
 *  Created on: Sep 19, 2011
 *      Author: hugo
 */

#include "Instance.h"
#include<fstream>
#include<stdlib.h>
#include<stdio.h>

int compare (const void * a, const void * b)
{
  return ( ((Edge*)a)->cost - ((Edge*)b)->cost );
}


Instance::Instance(string arq_name) {
	Instance::arq_name = arq_name;
	loadFile();
}

Instance::~Instance() {
	for (int i = 0; i < num_vertex; i++) {
		free(matriz[i]);
	}
	free(matriz);
}

int Instance::edgeCost(int _i,int _j){
	return matriz[_i][_j]==NULL?0:matriz[_i][_j]->cost;
}

Edge* Instance::bestEdge(int _i){
	if(_i>=num_edges)return NULL;
	return order[_i];
}
Edge* Instance::bestEdge(){
	return bestEdge(0);
}
int Instance::numEdges(){
	return num_edges;
}

int Instance::numVertex(){
	return num_vertex;
}

void Instance::loadFile() {
	FILE *arq;
	arq = fopen(arq_name.c_str(),"r");
	char output[100];
	int i, j, cost;
	if (arq) {
		fscanf(arq, "%d %d", &num_vertex, &num_edges);
		order = (Edge**) malloc(sizeof(Edge*) * num_edges);
		matriz = (Edge***) malloc(sizeof(Edge**) * num_vertex);
		for (i = 0; i < num_vertex; i++) {
			matriz[i] = (Edge **) malloc(sizeof(Edge*) * num_vertex);
			for (j = 0; j < num_vertex; j++) {
				matriz[i][j] = NULL;
			}
		}
		int ordePos=0;
		while (fscanf(arq, "%d %d %d", &i, &j, &cost)!=EOF) {
			i--;
			j--;
			matriz[i][j] = new Edge(i,j,cost);
			order[ordePos++] = matriz[i][j];
		}
		qsort (order, num_edges, sizeof(Edge*), compare);
		printf("%d:%d\n", num_vertex,num_edges);
		fclose(arq);
	} else {
		printf("Not open\n");
	}
}
