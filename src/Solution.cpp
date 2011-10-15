/*
 * Solution.cpp
 *
 *  Created on: Oct 2, 2011
 *      Author: hugo
 */

#include "Solution.h"
#include <stdio.h>

void Solution::print(){
	for(int i=0;i<length;i++)
		printf("%d ",vertex[i]);
	printf("\n");
}
int Solution::getCost(){
	return cost;
}

void Solution::setCost(int _cost){
	cost = _cost;
}

int Solution::recalculate_cost(int _i){
	int cost=Solution::cost;
	for(int i=0;i<length;i++){
		if(vertex[i]==vertex[_i])
			cost-=instance->edgeCost(i,_i);
		else
			cost+=instance->edgeCost(i,_i);
	}
	return cost;
}

int Solution::calculate_cost(){
	int cost=0;
	for(int i=0;i<length;i++)
		for(int j=i+1;j<length;j++){
			if(vertex[i]!=vertex[j]){
				cost+=instance->edgeCost(i,j);
			}
		}
	return cost;
}
Solution::Solution(int *_vertex, int _length,Instance *_instance) {
	vertex = _vertex;
	length = _length;
	instance = _instance;
	cost = calculate_cost();
}

Solution::~Solution() {
	// TODO Auto-generated destructor stub
}
