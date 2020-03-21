/*
 * Desc: BinaryIndexedTree排行榜算法
 * 根据分数查排名
 * Refer:https://www.jishuwen.com/d/pkKC
 */

#include <unordered_map>
#include <iostream>
#include <string.h>

using namespace std;

class BinaryIndexedTree {
 public:
    BinaryIndexedTree(int max_score);
    ~BinaryIndexedTree();
    int rank(int score) { return (sum(max_score_) - sum(score) + 1);}
    void update(int old_score, int new_score);
    void add(int i,int val);
 private:
    int lowbit(int x) { return x & (-x);}
    int sum(int i);

 private:
    int *bit_ = nullptr;
    int max_score_ = 0;
};

BinaryIndexedTree::BinaryIndexedTree(int max_score) {
    max_score_ = max_score;
    bit_ = new(std::nothrow) int[max_score_ + 1];
    memset(bit_, 0, sizeof(int) * (max_score_ + 1));
}

BinaryIndexedTree::~BinaryIndexedTree() {
    if (bit_) {
        delete [] bit_;
    }
}

int BinaryIndexedTree::sum(int i)
{ 
    int s=0; 
    while(i>0) {
        s+=bit_[i]; 
        i-=lowbit(i); 
    } 
    return s; 
}
void BinaryIndexedTree::update(int old_score, int new_score) {
    add(old_score, -1);
    add(new_score, 1);
}

void BinaryIndexedTree::add(int i,int val) {
    while(i<=max_score_) {
        bit_[i]+=val; 
        i+=lowbit(i);  
    } 
}

int main(int argc, char** argv) {
        BinaryIndexedTree obj(100);
        obj.add(3, 5);
        obj.add(1, 1);
        obj.add(7, 5);
        obj.add(10, 5);
        obj.add(100, 1);
        cout << "elem:" << 100 << ",rank:" << obj.rank(100) << endl;
        cout << "elem:" << 7 << ",rank:" << obj.rank(7) << endl;
        cout << "elem:" << 10 << ",rank:" << obj.rank(10) << endl;
        cout << "elem:" << 3 << ",rank:" << obj.rank(3) << endl;
	return 0;
}
