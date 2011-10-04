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
	int from,to,r,tmp;
	for(int i=0;i<(int)floor(instance->numEdges()/10.0);i++){
		to = (i+1)*10;
		from = to-10;
		for(int j=from;j<to;j++){
			r = from+rand_r(&seed)%10;
			tmp = myorder[j];
			myorder[j] = myorder[r];
			myorder[r] = tmp;
		}
	}
	from = to;
	to = instance->numEdges()-1;
	for(int j=from;j<to;j++){
		r = from+rand_r(&seed)%10;
		tmp = myorder[j];
		myorder[j] = myorder[r];
		myorder[r] = tmp;
	}


	Edge *edge = instance->bestEdge(myorder[0]);
	for(int i=1;edge!=NULL;i++){
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
	Solution *solution = new Solution(sol,instance->numVertex(),instance);
	return solution;
}
GA::GA(Instance *_instance) {
	seed = 1;
	cout << "iniciando GA..."<<endl;
	instance = _instance;
	Solution *initial = greedySolution();
	initial->print();
	cout << "Cost: "<<initial->getCost()<<endl;
}

GA::~GA() {
	// TODO Auto-generated destructor stub
}
