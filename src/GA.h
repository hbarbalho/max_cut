/*
 * GA.h
 *
 *  Created on: Oct 2, 2011
 *      Author: hugo
 */

#ifndef GA_H_
#define GA_H_
#include "Instance.h"
#include "Solution.h"

class GA {
private:
	Instance *instance;
	unsigned int seed;
	double time;
	Solution* bestSol;
	Solution* greedySolution();
	Solution** crossOver(Solution*,Solution*);
	Solution* mutation(Solution*,int,int);
	Solution** createPopulation(int size);
	Solution* localSearch(Solution*);
public:
	GA(Instance*,int num_generations,int size_population,unsigned int _seed);
	Solution* getBest();
	double getTime();
	virtual ~GA();
};

#endif /* GA_H_ */
