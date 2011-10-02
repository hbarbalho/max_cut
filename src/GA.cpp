/*
 * GA.cpp
 *
 *  Created on: Oct 2, 2011
 *      Author: hugo
 */

#include "GA.h"
#include <stdlib.h>
#include <stdio.h>

Solution* GA::greedySolution(){
	printf("Solucao inicial\n");
	int *sol = (int*)malloc(sizeof(int)*instance->numVertex());
	for(int i=0;i<instance->numVertex();i++){
		sol[i]=-1;
	}

	Edge *edge = instance->bestEdge();
	for(int i=1;edge!=NULL;i++){
		if(sol[edge->i]<0 && sol[edge->j]<0){
			sol[edge->i] = 1;
			sol[edge->j] = 0;
		}else if(sol[edge->i]<0){
			sol[edge->i] = !sol[edge->j];
		}else{
			sol[edge->j] = !sol[edge->i];
		}
		edge = instance->bestEdge(i);
	}
	Solution *solution = new Solution(sol,instance->numVertex());
	return solution;
}
GA::GA(Instance *_instance) {
	cout << "GA"<<endl;
	instance = _instance;
	Solution *initial = greedySolution();
	initial->print();
}

GA::~GA() {
	// TODO Auto-generated destructor stub
}
