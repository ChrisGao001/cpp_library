#include <stdio.h>
#include <fstream>
#include <math.h>
#include "util/matrix.h"
#include "util/random.h"

int convert_vector(const char *file_path, const char *dest);
int convert_matrix(const char *file_path, const char *dest);

float normal(float *x, int dim) {
	float sum = 0;
	for (int i=0; i<dim; ++i) {
		sum += x[i] * x[i];
	}
	return sqrt(sum);
}

float dot(float *x, float *y, int dim) {
	float sum = 0;
	for (int i=0; i<dim; ++i) {
		sum += x[i] * y[i];
	}
	return sum;
}
	
float cosine_distance(float *x, float *y, int dim) {
	float normal_x = normal(x, dim);
	float normal_y = normal(y, dim);
	float ret = (dot(x,y,dim))/(normal_x * normal_y);
	return (ret);
}

int main(int argc, char **argv) {
	DMatrixDouble d;
	d.load("./matrix.txt");
	d.saveToBinaryFile("item.bin");
	DMatrixDouble sim_d;
#if 0
	sim_d.setSize(50,50);
	d.init(0,1);
	DVectorDouble v;
	v.setSize(50);
	for (int i=0; i<50; ++i) {
		v(i) = ran_uniform() * 5;
	}	
	
	for (int i=0; i<50; ++i) {
		float *x = d(i);
		for (int j=i; j<50; ++j) {
			float *y = d(j);
			float dist = cosine_distance(x, y, 50);
			sim_d(i,j) = dist;
			sim_d(j,i) = dist;
		}
	}
	
	v.save("./weight.txt");
	v.saveToBinaryFile("./weight.bin");
	d.save("./item.txt");
	d.saveToBinaryFile("./item.bin");
	sim_d.save("sim.txt");
	sim_d.saveToBinaryFile("./sim.bin");
#endif		
	return 0;
}
