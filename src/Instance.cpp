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

int compareEdges (const void * a, const void * b)
{
	Edge **e1 = (Edge **)a;
	Edge **e2 = (Edge **)b;
	return (*e2)->cost - (*e1)->cost;
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
	if(matriz[_i][_j]!=NULL)
		return matriz[_i][_j]->cost;
	else if(matriz[_j][_i]!=NULL)
		return matriz[_j][_i]->cost;
	else
		return 0;
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
		qsort (order, num_edges, sizeof(Edge*), compareEdges);
		printf("%d:%d\n", num_vertex,num_edges);
		fclose(arq);
	} else {
		printf("Not open\n");
	}
}
