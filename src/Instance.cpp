/*
 * Instance.cpp
 *
 *  Created on: Sep 19, 2011
 *      Author: hugo
 */

#include "Instance.h"
#include<fstream>

Instance::Instance(string arq_name) {
	Instance::arq_name = arq_name;
	loadFile();
}

Instance::~Instance() {
	// TODO Auto-generated destructor stub
}

void Instance::loadFile() {
	ifstream myReadFile;
	myReadFile.open(arq_name.c_str());
	char output[100];
	if (myReadFile.is_open()) {
		myReadFile >> output;
		sscanf(output, "%d", &num_vertex);
		myReadFile >> output;
		sscanf(output, "%d", &num_edges);
		while (!myReadFile.eof()) {
			myReadFile >> output;
			//cout << output;
		}
	}else{
		cout << "Not open" << endl;
	}
	myReadFile.close();
	cout << num_vertex << ":" << num_edges;
}
