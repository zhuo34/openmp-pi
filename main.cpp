#include "pi.h"

#include <iostream>
#include <fstream>
#include <omp.h>
#include <vector>
#define MAX_THREADS 16

void test_simple();
void test_chudnovsky();

int main (int argc, const char *argv[]) {
	test_chudnovsky();
	return 0;
}

void test_simple() {
	std::vector<int> a = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
	for (auto n: a) {
		std::cout << "digits: " << n << std::endl;
		for (int thread = 1; thread <= MAX_THREADS; thread++) {
			std::cout << "threads: " << thread << " ";
			double start = omp_get_wtime();
			std::string pi = pi_simple(n, thread);
			double end = omp_get_wtime();
			std::cout << "time: " << end - start << std::endl;
			std::cout << pi << std::endl;
		}
		std::cout << "============" << std::endl;
	}
}

void test_chudnovsky() {
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
}