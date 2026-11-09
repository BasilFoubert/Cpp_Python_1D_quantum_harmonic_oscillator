#include "laguerre.h"

Laguerre::Laguerre(arma::vec const& x) : range(x) {}

void Laguerre::eval(unsigned int const& m, unsigned int const& n) {
    unsigned int const mid_i = values.n_cols;
    unsigned int const mid_j = values.n_slices; // Laguerre polynomials from H^0_0 to H^{j-1}_{i-1} are already stored
    if (mid_i <= n || mid_j <= m) { // no shrinking
        unsigned int const N = std::max(mid_i, n+1);
        unsigned int const M = std::max(mid_j, m+1);
        values.resize(range.n_elem, N, M);


        unsigned int i;
        unsigned int j;
        
        for (j = 0; j < M; j++) {
            i = (j < mid_j) ? mid_i : 0;
            if (i == 0) {
                values.slice(j).col(0) = arma::vec(range.n_elem, arma::fill::ones);
                i++;
            }
            if (i == 1 && i < N) {
                values.slice(j).col(1) = 1.0 + j - range;
                i++;
            }
            for(; i < N; i++) {
                values.slice(j).col(i) = (2.0 + (1.0/i) * (j-1.0-range)) % values.slice(j).col(i-1) - (1.0 + (j-1.0)/i) * values.slice(j).col(i-2);
            }
        }
    }
}

arma::vec Laguerre::get(unsigned int const& m, unsigned int const& n) const {
    return values.slice(m).col(n);
}

bool Laguerre::is_range(arma::vec const& x) const {
    return arma::approx_equal(range, x, "absdiff", 0.0);
}