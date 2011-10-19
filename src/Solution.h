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
	Solution(int *_vertex, int _length,int _cost,Instance *_instance);
	Solution(int *_vertex, int _length,Instance *_instance);
	virtual ~Solution();
	int recalculate_cost(int _i);
	void setCost(int _cost);
	float calculate_similarity(Solution*);
	int calculate_cost();
private:
	int cost;
};

#endif /* SOLUTION_H_ */
