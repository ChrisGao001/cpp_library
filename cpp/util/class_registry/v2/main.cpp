#include "dict.h"
#include <iostream>

using namespace std;
int main(int argc, char** argv) {
	Dict* dict = GlobalDictRegistry()->Create("TFDict");
	cout << dict->Name() << "," << dict->Compute(2, 3) << endl;
	dict = GlobalDictRegistry()->Create("TorchDict");
	cout << dict->Name() << "," << dict->Compute(2, 3) << endl;
	return 0;
}
