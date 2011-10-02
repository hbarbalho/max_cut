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
Solution::Solution(int *_vertex, int _length) {
	vertex = _vertex;
	length = _length;
}

Solution::~Solution() {
	// TODO Auto-generated destructor stub
}
