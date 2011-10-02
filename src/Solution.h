/*
 * Solution.h
 *
 *  Created on: Oct 2, 2011
 *      Author: hugo
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_

class Solution {
public:
	int *vertex;
	int length;
	void print();
	Solution(int*,int);
	virtual ~Solution();
};

#endif /* SOLUTION_H_ */
