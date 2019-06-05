#include "DPPRank.h"
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <set>
#include <string>

using namespace std;

int LoadSimMatrix(const char *matrix_path, Matrix<float> &mat);
int LoadWeight(const char *weight_path, vector<float> &weights);
template<typename T> string join(vector<T> arr, string delim=",");
float GetDetermine(vector<float> &D, vector<int> &Y);
static string dump_matrix(Matrix<float> &mat);
#define logger(fmt, ...) fprintf(stdout, fmt"\n",##__VA_ARGS__)

DPPRank::DPPRank() {
}

DPPRank::~DPPRank() {
}

float DPPRank::prod(float *x, float *y, int dim) {
    if (dim == 0) {
        return 0.0f;
    }

    float sum = 0.0f;
    for (int i=0; i<dim; ++i) {
        sum += x[i] * y[i];
    }

    return sum;
}

void DPPRank::Rank(int k) {
    if (k <= 0) return;
    
    int row = L_.GetRow();
    k = (k > row) ? row : k;

    vector<int> Z;
    vector<float> D;
    Matrix<float> C(L_.GetRow(), k);

    Z.reserve(row);
    D.reserve(row);
    // find the argmax and init Z
    int max_pos = -1;
    for (int i=0; i<row; ++i) {
        Z.push_back(i);
        D.push_back(L_(i,i));
        if (max_pos == -1 || L_(i,i) > L_(max_pos, max_pos)) {
            max_pos = i;
        }
    }

    int j = max_pos;
    solution_.push_back(j);
    Z[j] = -1; // set invalid value

    int iter = 0;
    while (iter < k) {
        // dump determine and Y
        logger("det:%0.6f, [%s]", GetDetermine(D,solution_), join(solution_).c_str());
        float max_value = -1.0;
        int max_pos = -1;
        float *cj = C(j);
        for (int i=0; i< (int)Z.size(); ++i) {
            if (Z[i] == -1) {
                continue;
            }

            float *ci = C(i);
            float factor = prod(ci, cj, iter);
            float ei = (L_(j,i) - factor) / sqrt(D[j]);
            C(i,iter) = ei;
            D[i] -= (ei * ei);
            if (max_pos == -1 || max_value < D[i]) {
                max_pos = i;
                max_value = D[i];
            }
        }

        j = max_pos;
        solution_.push_back(j);
        Z[j] = -1;
        ++iter;
    }
    
}

void DPPRank::RankSlidingWindow(int window_size, int k) {
    // define the variable 
    
    int dim = L_.GetRow();
    Matrix<float> V(window_size, window_size, 0.0);
    vector<vector<float> > C(dim);
    vector<int> Z(dim,0); // candidate set index
    vector<float> D(dim, 0);
    vector<int> &Y = solution_;
    logger("init env dim=%d,window_size=%d,k=%d", dim, window_size, k);

    // init env
    solution_.clear();
    for (int i=0; i<dim; ++i) {
        D[i] = L_(i,i);
        Z[i] = i;
    }

    int j = argmax(D);
    Y.push_back(j);
    Z[j] = -1;
    logger("argmax j=%d,size_C:%u", j, C.size());

    while (Z.size() > 0 && Y.size() < (size_t)k) {
        logger("interate:%u", Y.size());
        // update the cholesky matrix V
        size_t row = Y.size() - 1;
        row = (row >= (window_size - 1)) ? (window_size - 1) : row;
        for (size_t i=0; i<row; ++i) {
            V(row, i) = C[j][i];
        }
        V(row, row) = sqrt(D[j]);
        dump_matrix(V);

        // cholesky recursive method
        for (size_t i=0; i<Z.size(); ++i) {
            if (Z[i] == -1) {
                continue;
            }
            float ei = (L_(j,i) - prod(C[j].data(), C[i].data(), C[j].size())) / sqrt(D[j]);
            C[i].push_back(ei);
            D[i] = D[i] - ei * ei;
        }

        if (Y.size() >= window_size) {
            logger("over window_size:%d", window_size);
            vector<float> v;
            for (int row=1; row<V.GetRow(); ++row) {
                v.push_back(V(row,0));
                for (int col=1; col<V.GetCol(); ++col) {
                    V(row-1,col-1) = V(row, col); 
                    if (IsLastCol(col, V) || IsLastRow(row, V)) {
                        V(row, col) = 0.0f;
                    }
                }
            }

            // update A and C
            vector<float> A(dim, 0.0);
            for (size_t i=0; i<C.size(); ++i) {
                if (Z[i] != -1) {
                    A[i] = C[i][0];
                    C[i].erase(C[i].begin());
                }
            }

            for (int l=0; l<(window_size-1); ++l) {
                float t2 = V(l,l) * V(l,l) + v[l] * v[l];
                float t = sqrt(t2);
                for (int i=l+1; i<(int)v.size(); ++i) {
                    V(i,l) = (V(i,l) * V(l,l) + v[i] * v[l]) / t;
                    v[i] = (v[i] *t - V(i,l) * v[l]) / V(l,l);
                }

                for (size_t i=0; i<Z.size(); ++i) {
                    if (Z[i] == -1) {
                        continue;
                    }
                    C[i][l] = (C[i][l] * V(l,l) + A[i] *v[l]) / t;
                    A[i] = (A[i] * t - C[i][l] * v[l]) / V(l,l);
                }
                V(l,l) = t;
            }

            for (size_t i=0; i<Z.size(); ++i) {
                if (Z[i] == -1) {
                    continue;
                }
                D[i] = D[i] + A[i] * A[i];
            }
        }        

        // find the max D[i] in candidate set Z
        int max_pos = -1;
        for (size_t i=0; i<Z.size(); ++i) {
            if (Z[i] == -1) {
                continue;
            }

            if (max_pos == -1 || D[max_pos] < D[i]) {
                max_pos = i;
            }
        }

        j = max_pos;
        Y.push_back(j);
        Z[j] = -1;
    }
}

std::vector<int>& DPPRank::GetSolution() {
    return solution_;
}

int DPPRank::BuildMatrix(std::vector<float> &item_weights, Matrix<float> &item_sim) {
    L_.Swap(item_sim);
#if 0
    int row = item_sim.GetRow();
    int col = item_sim.GetCol();
    logger("BuildMatrix row=%d,col=%d", row, col);
    if (row != col || item_weights.size() != static_cast<size_t>(row)) {
        return -1;
    }

    L_.SetSize(row, col);
    for (int i=0; i<row; ++i) {
        for (int j=0; j<col; ++j) {
            L_(i,j) = item_sim(i,j) * item_weights[i] * item_weights[j];
	    if (i == 12 && j == 12) {
                logger("i:%d,j:%d,sim:%f,wi:%f,wj:%f", i,j,item_sim(i,j), item_weights[i], item_weights[j]); 
	    }
        }
    }
#endif
    dump_matrix(L_);
    return 0;
}

int DPPRank::argmax(std::vector<float> &items) {
    if (items.empty()) {
        return -1;
    }
    
    int pos = 0;
    int size = (int)items.size();
    for (int i=1; i<size; ++i) {
        if (items[pos] < items[i]) {
            pos = i;
        }
    }
return pos;
}

//#ifdef DEBUG

int main(int argc, char **argv) {
    DPPRank rank;
    Matrix<float> sim_matrix;
    vector<float> weights;
    const char *matrix_path = "./item.bin";
    const char *weight_path = "./weight.bin";


    if (LoadSimMatrix(matrix_path, sim_matrix) != 0) {
        logger("fail to load sim matrix");
        return -1;
    }
#if 0
    if (LoadWeight(weight_path, weights) != 0) {
        logger("fail to load weight path");
        return -1;
    }
#endif

    if (rank.BuildMatrix(weights, sim_matrix) != 0) {
        logger("fail to build matrix");
        return -1;
    }

    rank.RankSlidingWindow(4,8);
    //rank.Rank(8);
    vector<int> &solution = rank.GetSolution();
    logger("solution: [%s]", join(solution).c_str());
    
    return 0;
}

int LoadSimMatrix(const char *matrix_path, Matrix<float> &mat) {
    FILE *matrix_file = fopen(matrix_path, "rb");
    if (matrix_file == NULL) {
        return -1;
    }

    int row = 0;
    int col = 0;
    if (fread(&row,sizeof(int), 1, matrix_file) != 1) {
        logger("fail to read row");
        return -1;
    }

    if (fread(&col,sizeof(int), 1, matrix_file) != 1) {
        logger("fail to read col");
        return -1;
    }
    logger("row=%d, col=%d", row, col);
    mat.SetSize(row, col);
    int num_item = row * col;
    if (fread(mat.GetData(),sizeof(float), num_item, matrix_file) != num_item) {
        logger("fail to read matrix data");
        return -1;
    }

    return 0;
}

int LoadWeight(const char *weight_path, vector<float> &weights) {
    FILE *weight_file = fopen(weight_path, "rb");
    if (weight_file == NULL) {
        return -1;
    }

    int num_item = 0;
    if (fread(&num_item, sizeof(float), 1, weight_file) != 1) {
        logger("fail to read file");
        return -1;
    }

    logger("dim=%d", num_item);
    weights.resize(num_item);
    if (fread(weights.data(), sizeof(float), num_item, weight_file) != num_item) {
        logger("fail to read weight");
        return -1;
    }
    logger("50=%f", weights[49]);
    
    return 0;
}

string dump_matrix(Matrix<float> &mat) {
    	ostringstream oss;
	int row = mat.GetRow();
	int col = mat.GetCol();
        logger("dump_matrix row=%d,col=%d", row, col);
	for (int i=0; i<row; ++i) {
		float *x = mat(i);
		for (int j=0; j<col; ++j) {
			if (j != 0) {
				cout <<",";
			}
			cout << x[j];	
		}
		cout << endl;
	}
	//logger("matrix :\n:", oss.str().c_str());
	return oss.str();
}

template<typename T>
string join(vector<T> arr, string delim=",")
{
    ostringstream oss;
    if (arr.empty()) {
        return ""; 
    }   

    for (int i=0; i<arr.size(); ++i) {
        if (i != 0) {
            oss << delim;
        }
        oss << arr[i];
    }   

    return oss.str();
}

float GetDetermine(vector<float> &D, vector<int> &Y) {
    float sum = 1.0;
    for (size_t i=0; i<Y.size(); ++i) {
        int pos = Y[i];
        sum *= D[pos];
    }
    return sum;
}

//#endif
