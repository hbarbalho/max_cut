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

	int *myorder = (int*)malloc(sizeof(int)*instance->numVertex());
	for(int i=0;i<instance->numVertex();i++){
		myorder[i] = i;
	}
	int r,tmp,to;
	for(int i=0;i<instance->numVertex();i+=10){
		to = MIN(i+10,instance->numVertex()-2);
		for(int j=i;j<to;j++){
			r = i+rand_r(&seed)%(to-i);
			tmp = myorder[j];
			myorder[j] = myorder[r];
			myorder[r] = tmp;
		}
	}

	Vertex *v;
	int k=1;
	int sum=0;
	int last=1;
	while(k< instance->numVertex()){
		k=0;
		do{
			v = instance->bestVertex(myorder[k++]);
		}while(sol[v->get_index()]!=-1 && k< instance->numVertex());
		sum+=v->get_tmp_degree();
		if(sol[v->get_index()]==-1){
			sol[v->get_index()]=last;
			for(int j=0;j<instance->numVertex();j++){
				if(instance->edgeCost(v->get_index(),j)>0){
					sol[j]=!last;
					instance->getVertex(j)->dec_tmp_degree();
					v->dec_tmp_degree();
				}
			}
			instance->sortVertex();
			last = !last;
		}
	}
	free(myorder);
	instance->restoreVertexs();
	instance->sortVertex();

	Solution *solution = new Solution(sol,instance->numVertex(),instance);
	//free(sol);
	return solution;
}

Solution* GA::greedySolution2(){
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

Solution** GA::crossOver2points(Solution *a,Solution *b){
	int *vertexA = (int*) malloc(sizeof(int)* a->length);
	int *vertexB = (int*) malloc(sizeof(int)* b->length);
	int pointA = rand_r(&seed)%a->length;
	int pointB = rand_r(&seed)%b->length;

	for(int i=0;i<pointA;i++)
		vertexA[i]=a->vertex[i];
	for(int i=pointA;i<a->length;i++)
		vertexB[i]=a->vertex[i];


	for(int i=0;pointA+i<a->length;i++)
		vertexA[pointA+i]=b->vertex[i];

	for(int i=pointB,qnt=0;qnt<pointA;i=(i+1)%b->length,qnt++)
		vertexB[qnt]=b->vertex[i];

	Solution *crossA = new Solution(vertexA,instance->numVertex(),instance);
	Solution *crossB = new Solution(vertexB,instance->numVertex(),instance);
	Solution **sols = (Solution**)malloc(sizeof(Solution*)*2);
	sols[0] = crossA;
	sols[1] = crossB;
	return sols;
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
	printf("Creating population ...\n");
	Solution **sols = (Solution**)malloc(sizeof(Solution*)*size);
	int worst_pos=0;
	int length=0;
	Solution *sol;
	for(int i=0;i<size+10 || length<size;i++){
		sol = greedySolution();
		sol = localSearch2(sol);//localSearch(sol);//hybridHillClimbing(sol);
		if(length<size){
			sols[length] = sol;
			length++;
			if(length==size)
				sols = createSMP(sols,size,&length);
		}else{
			worst_pos = 0;
			for(int j=1;j<size;j++)
				if(sols[j]->getCost()<sols[worst_pos]->getCost())
					worst_pos = j;
			if(sol->getCost() > sols[worst_pos]->getCost()){
				sols[worst_pos]=sol;
				sols = createSMP(sols,size,&length);
			}
		}
	}

	qsort (sols, size, sizeof(Solution*), compareSols);
	for(int i=1;i<=2;i++){
		sols[length-i] = greedySolution();
		sols[length-i] = localSearch(sols[length-i]);
		for(int j=0;j<10;j++)
			sols[length-i] = localSearch2opt(sols[length-i]);
	}
	for(int i=0;i<length;i++)
		printf("%d ",sols[i]->getCost());
	printf("\n");
	return sols;
}

Solution* GA::localSearch2opt(Solution* sol){
	int *v_sol = (int*)malloc(sizeof(int)*instance->numVertex());
	for(int i=0;i<instance->numVertex();i++){
		v_sol[i]=sol->vertex[i];
	}
	int in,out,max=0,k;
	for(int i=0;i<instance->numVertex();i++){
		in=0;
		out = 0;
		for(int j=0;j<instance->numVertex();j++){
			if(v_sol[i]==v_sol[j] && instance->edgeCost(i,j)>0){
				in++;
			}
			if(v_sol[i]!=v_sol[j] && instance->edgeCost(i,j)>0){
				out++;
			}
		}
		if(in-out>max){
			max = in-out;
			k=i;
		}
	}
	if(max>0)v_sol[k] = !v_sol[k];
	Solution *solution = new Solution(v_sol,instance->numVertex(),instance);
	//free(sol);
	return solution;
}

Solution* GA::hillClimbing(Solution* sol){
	//printf("start hill\n");
	int best_cost=sol->getCost();
	int cost;
	for(int i=0;i<sol->length;i++){
		sol->vertex[i] = !sol->vertex[i];
		cost = sol->recalculate_cost(i);
		if(cost>best_cost){
			best_cost = cost;
			sol->setCost(best_cost);
		}else{
			sol->vertex[i] = !sol->vertex[i];
		}
	}
	//printf("end hill\n");
	return sol;
}

Solution* GA::hybridHillClimbing(Solution* sol){
	Solution *s;
	Solution *best= sol;
	for(int i=0;i<50;i++){
		s = localSearch(best);
		if(s->getCost() > best->getCost()){
			best = s;
		}else{
			s = sol;
		}
	}
	return best;
}
Solution* GA::localSearch2(Solution* sol){
	//printf("start hill\n");
	int best_cost=sol->getCost();
	int cost;
	for(int i=0;i<sol->length;i++){
		sol->vertex[i] = !sol->vertex[i];
		cost = sol->recalculate_cost(i);
		if(cost>best_cost){
			best_cost = cost;
			sol->setCost(best_cost);
			i=0;
		}else{
			sol->vertex[i] = !sol->vertex[i];
		}
	}
	//printf("end hill\n");
	return sol;
}

Solution** GA::createSMP(Solution** population,int size,int *size_smp){
	int new_size=1;
	Solution **sols = (Solution**)malloc(sizeof(Solution*)*size);
	sols[0] = population[0];
	for(int i=1;i<size;i++){
		int diff=1;
		float simi;
		for(int j=0;j<new_size;j++){
			simi = population[i]->calculate_similarity(sols[j]);
			if(floor(simi*1000)>=998){
				diff=0;
			}
		}
		if(diff){
			sols[new_size++] = population[i];
		}
	}
	*size_smp = new_size;
	memset(population,NULL,sizeof(Solution*)*size);
	free(population);
	return sols;
}

Solution* GA::localSearch(Solution* sol){
	int best_cost=sol->getCost();
	int best_move = -1;
	int cost;

	for(int i=0;i<sol->length;i++){
		sol->vertex[i] = !sol->vertex[i];
		cost = sol->recalculate_cost(i);
		sol->vertex[i] = !sol->vertex[i];
		if(cost>best_cost){
			best_move = i;
			best_cost = cost;
		}
	}

	Solution *ret;
	if(best_move>=0){
		int *vertexA = (int*) malloc(sizeof(int)* instance->numVertex());
		for(int i=0;i<sol->length;i++)
			vertexA[i]=sol->vertex[i];
		vertexA[best_move] = !vertexA[best_move];
		ret = new Solution(vertexA,sol->length,best_cost,instance);
		if(best_cost!=ret->calculate_cost()){
			printf("%d = %d?\n",best_cost,ret->calculate_cost());
			getchar();
		}
	}else
		ret = sol;
	return ret;
}

Solution* GA::pr(Solution* from, Solution* to){
	int *vertex = (int*)malloc(sizeof(int)*from->length);
	int *best_vertex = (int*)malloc(sizeof(int)*from->length);
	for(int i=0;i<instance->numVertex();i++){
		best_vertex[i] = from->vertex[i];
		vertex[i] = from->vertex[i];
	}

	Solution* sol = new Solution(vertex,from->length,from->getCost(),instance);
	int best_cost=sol->getCost();
	int cost;
	for(int i=0;i<instance->numVertex();i++){
		if(sol->vertex[i]!=to->vertex[i]){
			sol->vertex[i] = to->vertex[i];
			cost = sol->recalculate_cost(i);
			sol->setCost(cost);
			if(cost>best_cost){
				for(int i=0;i<instance->numVertex();i++)
					best_vertex[i] = sol->vertex[i];
				best_cost = cost;
			}
		}

	}
	free(sol);
	Solution* best = new Solution(best_vertex,sol->length,best_cost,instance);
	if(best->calculate_cost() !=best_cost)
		printf("PR wrong %d!=%d!!\n",best_cost,best->calculate_cost());
	return best;
}

GA::GA(Instance *_instance,int num_generations,int size_population,unsigned int _seed) {
	double s_CPU_inicial, s_CPU_final, s_total_inicial, s_total_final;
	Tempo_CPU_Sistema(&s_CPU_inicial, &s_total_inicial);
	bestSol=NULL;
	time = -1;
	seed = _seed;
	instance = _instance;
	int size=size_population;
	/*bestSol = greedySolution();
	bestSol = localSearch(bestSol);
	for(int i=0;i<100;i++)
		bestSol = localSearch2opt(bestSol);*/
	/*Solution *tmp,*last;
	bestSol = greedySolution();
	bestSol = localSearch2(bestSol);
	Solution **pool = (Solution**)malloc(sizeof(Solution*)*size);
	int len=1;
	int worst=-1;
	pool[0] = bestSol;
	for(int i=1;i<100;i++){
		printf("==========\ndoing %d\t",i);
		printf("Best %d\n",bestSol->getCost());
		tmp = greedySolution2();
		printf("\tConst %d\n",tmp->getCost());
		tmp = localSearch2(tmp);
		printf("\tBL %d\n",tmp->getCost());
		tmp = pr(tmp,pool[rand_r(&seed)%len]);
		printf("\tPR %d\n",tmp->getCost());
		if(tmp->getCost()>bestSol->getCost())
			bestSol = tmp;

		if(len<size){
			worst=-1;
			pool[len++]=tmp;
		}else if(worst==-1){
			worst = 0;
			for(int j=1;i<size;j++)
				if(pool[j]->getCost()<pool[worst]->getCost())
					worst = j;
			if(pool[worst]->getCost()<tmp->getCost()){
				pool[worst] = tmp;
				worst = -1;
				pool = createSMP(pool,size,&len);
			}
		}else{
			if(pool[worst]->getCost()<tmp->getCost()){
				pool[worst] = tmp;
				worst = -1;
				pool = createSMP(pool,size,&len);
			}
		}
	}*/
	Solution** population = createPopulation(size);
	Solution** new_pop;
	int new_size;
	for(int i=0;i<num_generations;i++){
		//printf("Generation ... %d\n",i);
		int size_smp=0;
		population = createSMP(population,size,&size_smp);

		int top= ceil(size_smp*0.3);
		int middle = top+ceil(size_smp*0.4);
		int rest = size_smp;

		new_pop = (Solution**)malloc(sizeof(Solution*)*size);
		new_size = 0;
		for(int j=0;j<top;j++)
			new_pop[new_size++] = population[j];

		while(new_size<size){
			int top_sol = rand_r(&seed)%top;
			int middle_sol;
			if(middle==top)
				middle_sol = top_sol;
			else
				middle_sol = top+rand_r(&seed)%(middle-top);
			int rest_sol;

			if(rest==middle)
				rest_sol = middle_sol;
			else
				rest_sol = rand_r(&seed)%(rest-middle)+middle;

			int rand = rand_r(&seed)%100;

			int s1_index,s2_index;
			if(rand<50){
				s1_index = top_sol;
				s2_index = middle_sol;
			}else if(rand<70){
				s1_index = top_sol;
				s2_index = rest_sol;
			}else{
				s1_index = middle_sol;
				s2_index = rest_sol;
			}

			Solution* s1 = population[s1_index];
			Solution* s2 = population[s2_index];
			if(rand_r(&seed)%10>=6){
				Solution** offspring = crossOver(s1,s2);
				s1 = offspring[0];
				s2 = offspring[1];
			}
			if(rand_r(&seed)%10>=2){
				s1 = mutation(s1,rand_r(&seed)%instance->numVertex(),rand_r(&seed)%instance->numVertex());
				s2 = mutation(s2,rand_r(&seed)%instance->numVertex(),rand_r(&seed)%instance->numVertex());
			}
			if(rand_r(&seed)%10>=5){
				s1 = localSearch2opt(s1);
				s2 = localSearch2opt(s2);
				//s1 = localSearch(s1);
				//s2 = localSearch(s2);
				//s1 = hillClimbing(s1);
				//s2 = hillClimbing(s2);
				//s1 = localSearch2(s1);
				//s2 = localSearch2(s2);
			}
			if(new_size+2<size){
				new_pop[new_size++] = s1;
				new_pop[new_size++] = s2;
			}else{
				new_pop[new_size++] = s1->getCost()>s2->getCost()?s1:s2;
			}
		}
		memset(population,NULL,sizeof(Solution*)*size);
		free(population);
		population = new_pop;
		if(rand_r(&seed)%10>=8){
			for(int j=0;j<top;j++){
				population[j] = localSearch2(population[j]);
			}
		}
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
