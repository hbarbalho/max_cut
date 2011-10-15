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
#include <sys/resource.h>
#define MIN(A,B)A<B?A:B

void Tempo_CPU_Sistema(double *seg_CPU_total, double *seg_sistema_total)
{
  long seg_CPU, seg_sistema, mseg_CPU, mseg_sistema;
  struct rusage ptempo;

  getrusage(0,&ptempo);

  seg_CPU = ptempo.ru_utime.tv_sec;
  mseg_CPU = ptempo.ru_utime.tv_usec;
  seg_sistema = ptempo.ru_stime.tv_sec;
  mseg_sistema = ptempo.ru_stime.tv_usec;

 *seg_CPU_total     = (seg_CPU + 0.000001 * mseg_CPU);
 *seg_sistema_total = (seg_sistema + 0.000001 * mseg_sistema);
}

static int compareSols (const void * a, const void * b)
{
	Solution **s1 = (Solution **)a;
	Solution **s2 = (Solution **)b;
	return (*s2)->getCost() - (*s1)->getCost();
}

Solution* GA::greedySolution(){
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

Solution* GA::mutation(Solution *a,int p1,int p2){
	int *vertexM = (int*) malloc(sizeof(int)* instance->numVertex());
	for(int i=0;i<instance->numVertex();i++){
		if(i==p1)
			vertexM[i] = a->vertex[p2];
		else if(i==p2)
			vertexM[i] = a->vertex[p1];
		else
			vertexM[i] = a->vertex[i];
	}
	return new Solution(vertexM,instance->numVertex(),instance);
}

Solution** GA::crossOver(Solution *a,Solution *b){
	int *vertexA = (int*) malloc(sizeof(int)* instance->numVertex());
	int *vertexB = (int*) malloc(sizeof(int)* instance->numVertex());
	int split = (int)floor(instance->numVertex()/2);
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

Solution** GA::createPopulation(int size){
	Solution **sols = (Solution**)malloc(sizeof(Solution*)*size);
	for(int i=0;i<size;i++){
		sols[i] = greedySolution();
	}
	qsort (sols, size, sizeof(Solution*), compareSols);
	return sols;
}
GA::GA(Instance *_instance,int num_generations,int size_population,unsigned int _seed) {
	double s_CPU_inicial, s_CPU_final, s_total_inicial, s_total_final,t;
	Tempo_CPU_Sistema(&s_CPU_inicial, &s_total_inicial);
	bestSol=NULL;
	time = -1;
	seed = _seed;
	instance = _instance;
	int size=size_population;
	Solution** population = createPopulation(size);
	Solution** new_pop;
	int new_size;
	int top= floor(size*0.3);
	int middle = top+floor(size*0.4);
	int rest = size;

	for(int i=0;i<num_generations;i++){
		new_pop = (Solution**)malloc(sizeof(Solution*)*size);
		new_size = 0;
		for(int j=0;j<top;j++)
			new_pop[new_size++] = population[j];

		while(new_size<size){
			if(rand_r(&seed)%10>=6){
				int top_sol = rand_r(&seed)%top;
				int middle_sol = top+rand_r(&seed)%(middle-top);
				Solution** offspring = crossOver(population[top_sol],population[middle_sol]);
				if(new_size+2<size){
					new_pop[new_size++] = offspring[0];
					new_pop[new_size++] = offspring[1];
				}else{
					new_pop[new_size++] = offspring[0]->getCost()>offspring[1]->getCost()?offspring[0]:offspring[1];
				}
			}else{
				int middle_sol = top+rand_r(&seed)%(middle-top);
				Solution* sol = mutation(population[middle_sol],rand_r(&seed)%instance->numVertex(),rand_r(&seed)%instance->numVertex());
				new_pop[new_size++] = sol;
			}
		}
		memset(population,NULL,sizeof(Solution*)*size);
		free(population);
		population = new_pop;
		qsort (population, size, sizeof(Solution*), compareSols);
	}
	bestSol = population[0];
	Tempo_CPU_Sistema(&s_CPU_final, &s_total_final);
	time = s_CPU_final - s_CPU_inicial;

}

Solution* GA::getBest(){
	return bestSol;
}
double GA::getTime(){
	return time;
}

GA::~GA() {
	// TODO Auto-generated destructor stub
}
