#ifndef OPENMP_PI_CHUDNOVSKY_H
#define OPENMP_PI_CHUDNOVSKY_H

#include <gmp.h>
#include <gmpxx.h>
#include <string>
#include <cmath>

mpz_class qpow(mpz_class x, unsigned int n);
mpf_class my_sqrt(mpf_class n);
void bs(long a, long b, mpz_class &P, mpz_class &Q, mpz_class &T, int max_depth);
std::string pi_chudnovsky(unsigned int digits, int n_threads);

#endif //OPENMP_PI_CHUDNOVSKY_H
