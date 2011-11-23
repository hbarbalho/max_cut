/*
 * Vertex.cpp
 *
 *  Created on: Nov 16, 2011
 *      Author: hugo
 */

#include "Vertex.h"

Vertex::Vertex(int _index){
	degree = 0;
	tmp_degree = 0;
	index = _index;
}

void Vertex::inc_degree(){
	degree++;
	tmp_degree++;
}

int Vertex::get_degree(){
	return degree;
}

void Vertex::dec_tmp_degree(){
	tmp_degree--;
}

void Vertex::restore_tmp_degree(){
	tmp_degree = degree;
}

int Vertex::get_tmp_degree(){
	return tmp_degree;
}

int Vertex::get_index(){
	return index;
}
