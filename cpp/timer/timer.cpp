#include <chrono>
#include <iostream>

class Timer {
 public:
	void Start() {
		begin_ = std::chrono::high_resolution_clock::now();
	}

	int64_t StopMS() {
		end_ = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(end_ - begin_).count();
	}

	int64_t StopUS() {
		end_ = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(end_ - begin_).count();
	}
	
 private:
	 std::chrono::time_point<std::chrono::high_resolution_clock> begin_;
	 std::chrono::time_point<std::chrono::high_resolution_clock> end_;
};

int main(int argc, char** argv) {
	Timer t;
	t.Start();
	int sum = 0;
	for (int i=0; i<10000; ++i) {
		sum += i;
	}

	std::cout << "cost " << t.StopUS() << " us" << std::endl;
	std::cout << "cost " << t.StopMS() << " ms" << std::endl;
		

	return 0;
}
