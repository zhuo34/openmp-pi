#include "pi.h"

std::string pi_simple(int N, int n_threads) {
	mpf_class sum = 0;
	mpf_class step = 1.0 / N;
	mpf_class x;
	#pragma omp parallel for private( x ) reduction(+: sum) num_threads(n_threads)
	for (int i = 0; i < N; i++) {
		x = ( i + 0.5 ) * step;
		sum += 4.0 / (1.0 + x * x);
	}
	mpf_class pi = sum*step;
	mp_exp_t exp;
	return pi.get_str(exp);
}


mpz_class qpow(mpz_class x, unsigned int n) {
	if (x == 0) {
		return x;
	}
	if (n == 0) {
		return 1;
	}
	mpz_class t = qpow(x, n / 2);
	return t * t * (n % 2 ? x : 1);
}

mpz_class C(640320);
mpz_class C3_OVER_24(qpow(C, 3) / 24);

void bs(long a, long b, mpz_class &P, mpz_class &Q, mpz_class &T, int max_depth=0) {
	if (b - a == 1) {
		if (a == 0) {
			P = Q = mpz_class(1);
		} else {
			P = mpz_class((6*a-5)*(2*a-1)*(6*a-1));
			Q = mpz_class(a*a*a*C3_OVER_24);
		}
		T = P * (13591409 + 545140134*a);
		if (a%2 == 1) {
			T = -T;
		}
	} else {
		long m = (a + b) / 2;
		mpz_class Pam, Qam, Tam;
		mpz_class Pmb, Qmb, Tmb;
		if (max_depth > 0) {
#pragma omp parallel sections default(shared)
			{
#pragma omp section
				{
					bs(a, m, Pam, Qam, Tam, max_depth - 1);
				}
#pragma omp section
				{
					bs(m, b, Pmb, Qmb, Tmb, max_depth-1);
				}
			}
		} else {
			bs(a, m, Pam, Qam, Tam, max_depth);
			bs(m, b, Pmb, Qmb, Tmb, max_depth);
		}
		P = Pam * Pmb;
		Q = Qam * Qmb;
		T = Qmb * Tam + Pam * Tmb;
	}
}

mpf_class my_sqrt(mpf_class n) {
	mpf_class n_sqrt;
	mpf_sqrt(n_sqrt.get_mpf_t(), n.get_mpf_t());
	return n_sqrt;
}

std::string pi_chudnovsky(unsigned int digits, int n_threads=1) {
	mpf_set_default_prec(digits*log2(10));
//	std::cout << "precision: " << mpf_get_default_prec() << std::endl;
	mpf_class DIGITS_PER_TERM = log(C3_OVER_24.get_d()/6/2/6);
	mpf_class a = digits/DIGITS_PER_TERM + 1;
	long N = a.get_si();
//	std::cout << "term: " << N << std::endl;
	mpz_class P, Q, T;
	bs(0, N * 10, P, Q, T, (int)log2(n_threads));
	mpf_class pi = (Q * 426880 * my_sqrt(10005)) / T;
	mp_exp_t exp;
	std::string ret = pi.get_str(exp);
	return ret;
}
