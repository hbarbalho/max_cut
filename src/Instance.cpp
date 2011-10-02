/*
 * Instance.cpp
 *
 *  Created on: Sep 19, 2011
 *      Author: hugo
 */

#include "Instance.h"
#include<fstream>
#include<stdlib.h>

Instance::Instance(string arq_name) {
	Instance::arq_name = arq_name;
	loadFile();
}

Instance::~Instance() {
	for (int i = 0; i < num_vertex; i++) {
		free(matriz[i]);
	}
	free(matriz);
}

void Instance::loadFile() {
	ifstream myReadFile;
	myReadFile.open(arq_name.c_str());
	char output[100];
	int i, j, cost;
	if (myReadFile.is_open()) {
		myReadFile.getline(output, 100);
		sscanf(output, "%d %d", &num_vertex, &num_edges);
		matriz = (int**) malloc(sizeof(int*) * num_vertex);
		for (i = 0; i < num_vertex; i++) {
			matriz[i] = (int *) malloc(sizeof(int) * num_vertex);
			for (j = 0; j < num_vertex; j++) {
				matriz[i][j] = matriz[i][j] ^ matriz[i][j];
			}
		}

		while (!myReadFile.eof()) {
			myReadFile.getline(output, 100);
			sscanf(output, "%d %d %d", &i, &j, &cost);
			matriz[i][j] = cost;
		}
	} else {
		cout << "Not open" << endl;
	}
	myReadFile.close();
	cout << num_vertex << ":" << num_edges;
}
