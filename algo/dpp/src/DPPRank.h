#ifndef DPP_RANK_H
#define DPP_RANK_H
#include <vector>
#include "Matrix.h"

#if 0
template<typename T>
float consine_distance(T* m, T* n, int dim);
#endif

class DPPRank {
public:
    DPPRank();
    ~DPPRank();
    void Rank(int k);
    void RankSlidingWindow(int window_size, int k);
    std::vector<int>& GetSolution();
    int BuildMatrix(std::vector<float> &item_weights, Matrix<float> &item_sim);
private:
    float prod(float *x, float *y, int dim);
    int argmax(std::vector<float> &items);
    bool IsLastRow(int row, Matrix<float> &mat) { return (row == (mat.GetRow()-1));} 
    bool IsLastCol(int col, Matrix<float> &mat) { return (col == (mat.GetCol()-1));}
private:
    Matrix<float> L_;
    std::vector<int> solution_;
};

#endif
