/*
 * Main.cpp
 *
 *  Created on: Sep 19, 2011
 *      Author: hugo
 */

#include <iostream>
#include <stdio.h>
using namespace std;

#include "Instance.h"
#include "GA.h"

void run(char* inst,char* label,int num_generations,int size_population){
	Instance *instance = new Instance(inst);
	GA *ga;
	float total=0;
	double time=0;
	float qnt=0;
	for(int i=1;i<=1;i++){
		ga = new GA(instance,num_generations,size_population,i);
		total+=ga->getBest()->getCost();
		time+=ga->getTime();
		delete ga;
		qnt++;
	}
	if(qnt>0){
		printf("Media Custo(%s): %f\n",label,total/qnt);
		printf("Media Tempo(%s): %f\n",label,time/qnt);
		printf("############\n\n");
	}
	delete instance;
}

int main(int argv, char *arg[]){
	char location[100];
	char label[50];
	//run("instances/set1/gTest.rud","Test",100,10);

	for(int i=0;i<3;i++){
		sprintf(location,"instances/set1/g%d.rud",(i+1));
		sprintf(label,"G%d",(i+1));
		run(location,label,100,10);
	}

	return 0;
}
