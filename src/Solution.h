/*
 * Solution.h
 *
 *  Created on: Oct 2, 2011
 *      Author: hugo
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_
#include "Instance.h"

class Solution {
public:
	int *vertex;
	int length;
	Instance *instance;
	void print();
	int getCost();
	Solution(int*,int,Instance*);
	virtual ~Solution();
private:
	int cost;
	int calculate_cost();
};

#endif /* SOLUTION_H_ */
