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
	int _cost=cost;
	for(int i=0;i<length;i++){
		if(vertex[i]==vertex[_i])
			_cost-=instance->edgeCost(i,_i);
		else
			_cost+=instance->edgeCost(i,_i);
	}
	return _cost;
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

float Solution::calculate_similarity(Solution* sol){
	float inter=0;
	for(int i=0;i<length;i++){
		inter+=vertex[i]==sol->vertex[i];
	}
	return inter/(float)length;
}

Solution::Solution(int *_vertex, int _length,Instance *_instance) {
	vertex = _vertex;
	length = _length;
	instance = _instance;
	cost = calculate_cost();
}

Solution::Solution(int *_vertex, int _length,int _cost,Instance *_instance) {
	vertex = _vertex;
	length = _length;
	instance = _instance;
	cost = _cost;
}

Solution::~Solution() {
	// TODO Auto-generated destructor stub
}
