#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#define _USE_MATH_DEFINES

extern "C" {
	void dsyev_(const char* JOBZ, const char* UPLO, const int* N, double* A, const int* LDA, double* W, double* WORK, const int* LWORK, int* INFO);
}

int main() {

	double K = 1.0;	double m = 1.0; const int N = 3;

	std::vector<double> M(N * N, 0);
	std::vector<double> o1(N); //calculated omega
	std::vector<double> o2(N); //to check

	//initialize matrix
	for (int n = 0; n < N - 1; ++n) M[n*(N + 1) + 1] = -1.0;
	for (int n = 1; n < N; ++n) M[n*(N + 1) - 1] = -1.0;
	for (int n = 0; n < N; ++n) M[n*(N + 1)] = 2.0;
	
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) std::cout << M[i*N + j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	int info; char jobz = 'V', uplo = 'L'; int w = 3*N - 1; std::vector<double> work(w);
	dsyev_(&jobz, &uplo, &N, &(M.front()), &N, &(o1.front()), &(work.front()), &w, &info);

	for (int n = 0; n < N; ++n) o1[n] = std::sqrt(K*o1[n]/m);
	for (int n = 0; n < N; ++n) o2[n] = std::sqrt(K*(2.0 - 2.0 * std::cos(M_PI * (n + 1) / (N + 1)))/m);
	for (int n = 0; n < N; ++n) std::cout << o1[n] << std::endl;
	
	return 0;
}
