/*
 * Vertex.h
 *
 *  Created on: Nov 16, 2011
 *      Author: hugo
 */

#ifndef VERTEX_H_
#define VERTEX_H_

class Vertex {
private:
	int degree;
	int tmp_degree;
	int index;
public:
	Vertex(int _index);
	void inc_degree();
	int get_degree();
	void restore_tmp_degree();
	void dec_tmp_degree();
	int get_tmp_degree();
	int get_index();
};

#endif /* VERTEX_H_ */
