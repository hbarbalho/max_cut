/*
 * Instance.h
 *
 *  Created on: Sep 19, 2011
 *      Author: hugo
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <string.h>
#include <iostream>
using namespace std;

class Instance {
public:
	Instance(string arq_name);
	virtual ~Instance();
private:
	string arq_name;
	int num_edges;
	int num_vertex;
	int** matriz;
	void loadFile();
};

#endif /* INSTANCE_H_ */
