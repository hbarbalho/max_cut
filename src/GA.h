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
	Solution* greedySolution();
public:
	GA(Instance*);
	virtual ~GA();
};

#endif /* GA_H_ */
