#include "chudnovsky.h"

#include <iostream>
#include <fstream>
#include <omp.h>
#include <vector>
#define MAX_THREADS 16

int main (int argc, const char *argv[]) {
	std::vector<int> a = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
	for (auto n: a) {
		std::cout << "digits: " << n << std::endl;
		for (int thread = 1; thread <= MAX_THREADS; thread*=2) {
			std::cout << "threads: " << thread << " ";
			double start = omp_get_wtime();
			std::string pi = pi_chudnovsky(n, thread);
			double end = omp_get_wtime();
			std::cout << "time: " << end - start << std::endl;
			std::ofstream f("pi" + std::to_string(thread) + ".txt");
			if (f.is_open()) {
				f << pi << std::endl;
				f.close();
			}
		}
		std::cout << "============" << std::endl;
	}

//	std::cout << pi << std::endl;
	return 0;
}