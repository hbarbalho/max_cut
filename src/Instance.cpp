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
#include<string.h>

int compareEdges (const void * a, const void * b)
{
	Edge **e1 = (Edge **)a;
	Edge **e2 = (Edge **)b;
	return (*e2)->cost - (*e1)->cost;
}

int compareVertex (const void * a, const void * b)
{
	Vertex **e1 = (Vertex **)a;
	Vertex **e2 = (Vertex **)b;
	return (*e2)->get_degree() - (*e1)->get_degree();
}

int compareVertexTmp (const void * a, const void * b)
{
	Vertex **e1 = (Vertex **)a;
	Vertex **e2 = (Vertex **)b;
	return (*e2)->get_tmp_degree() - (*e1)->get_tmp_degree();
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

void Instance::sortVertex(){
	qsort (v_order, num_vertex, sizeof(Vertex*),compareVertexTmp);
}

int Instance::edgeCost(int _i,int _j){
	if(matriz[_i][_j]!=NULL)
		return matriz[_i][_j]->cost;
	else if(matriz[_j][_i]!=NULL)
		return matriz[_j][_i]->cost;
	else
		return 0;
}
void Instance::restoreVertexs(){
	for(int i=0;i<num_vertex;i++)
		vertexs[i]->restore_tmp_degree();
}

Vertex* Instance::getVertex(int _i){
	if(_i>=num_vertex)return NULL;
	return vertexs[_i];
}

Vertex* Instance::bestVertex(int _i){
	if(_i>=num_vertex)return NULL;
	return v_order[_i];
}
Vertex* Instance::bestVertex(){
	return bestVertex(0);
}

bool Instance::has_edge(int i,int j){
	return matriz[i][j]!=NULL;
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
		v_order = (Vertex**) malloc(sizeof(Vertex*) * num_vertex);
		vertexs = (Vertex**) malloc(sizeof(Vertex*) * num_vertex);

		for (i = 0; i < num_vertex; i++) {
			vertexs[i] = new Vertex(i);
			v_order[i] = vertexs[i];
		}
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
			vertexs[i]->inc_degree();
			vertexs[j]->inc_degree();
		}
		qsort (v_order, num_vertex, sizeof(Vertex*),compareVertex);
		qsort (order, num_edges, sizeof(Edge*), compareEdges);
		printf("%d:%d\n", num_vertex,num_edges);
		fclose(arq);
	} else {
		printf("Not open\n");
	}
}
