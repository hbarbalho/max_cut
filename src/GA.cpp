/*
 * GA.cpp
 *
 *  Created on: Oct 2, 2011
 *      Author: hugo
 */

#include "GA.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define MIN(A,B)A<B?A:B

Solution* GA::greedySolution(){
	printf("Solucao inicial\n");
	int *sol = (int*)malloc(sizeof(int)*instance->numVertex());
	for(int i=0;i<instance->numVertex();i++){
		sol[i]=-1;
	}

	int *myorder = (int*)malloc(sizeof(int)*instance->numEdges());
	for(int i=0;i<instance->numEdges();i++){
		myorder[i] = i;
	}
	int r,tmp,to;
	for(int i=0;i<instance->numEdges();i+=10){
		to = MIN(i+10,instance->numEdges()-2);
		for(int j=i;j<to;j++){
			r = i+rand_r(&seed)%(to-i);
			tmp = myorder[j];
			myorder[j] = myorder[r];
			myorder[r] = tmp;
		}
	}
	cout<<endl;
	Edge *edge = instance->bestEdge(myorder[0]);
	for(int i=1;i<instance->numEdges();i++){
		if(sol[edge->i]<0 && sol[edge->j]<0){
			sol[edge->i] = 1;
			sol[edge->j] = 0;
		}else if(sol[edge->i]<0){
			sol[edge->i] = !sol[edge->j];
		}else if(sol[edge->j]<0){
			sol[edge->j] = !sol[edge->i];
		}
		edge = instance->bestEdge(myorder[i]);
	}
	free(myorder);
	Solution *solution = new Solution(sol,instance->numVertex(),instance);
	//free(sol);
	return solution;
}
Solution** GA::crossOver(Solution *a,Solution *b){
	int *vertexA = (int*) malloc(sizeof(int)* instance->numVertex());
	int *vertexB = (int*) malloc(sizeof(int)* instance->numVertex());
	int split = (int)floor(instance->numVertex()/2);
	printf("split %d\n",split);
	for(int i=0;i<instance->numVertex();i++){
		if(i<split)
			vertexA[i] = a->vertex[i];
		else
			vertexA[i] = b->vertex[i];
	}
	for(int i=0;i<instance->numVertex();i++){
		if(i<split)
			vertexB[i] = b->vertex[i];
		else
			vertexB[i] = a->vertex[i];
	}
	Solution *crossA = new Solution(vertexA,instance->numVertex(),instance);
	Solution *crossB = new Solution(vertexB,instance->numVertex(),instance);
	Solution **sols = (Solution**)malloc(sizeof(Solution*)*2);
	sols[0] = crossA;
	sols[1] = crossB;
	return sols;
}
GA::GA(Instance *_instance) {
	seed = 1;
	cout << "iniciando GA..."<<endl;
	instance = _instance;
	Solution *a,*b;
	cout << "A Cost: "<<(a=greedySolution())->getCost()<<endl;

	cout << "B Cost: "<<(b=greedySolution())->getCost()<<endl;

	Solution **cross = crossOver(a,b);

	cout << "A2 Cost: "<<(cross[0])->getCost()<<endl;

	cout << "B2 Cost: "<<(cross[1])->getCost()<<endl;


}

GA::~GA() {
	// TODO Auto-generated destructor stub
}
