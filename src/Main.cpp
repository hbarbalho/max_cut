/*
 * Main.cpp
 *
 *  Created on: Sep 19, 2011
 *      Author: hugo
 */

#include <iostream>
using namespace std;

#include "Instance.h"

int main(int argv, char *arg[]){
	Instance *instance = new Instance("/home/hugo/workspace/max_cut/instances/set1/g1.rud");
	delete instance;
	return 0;
}
