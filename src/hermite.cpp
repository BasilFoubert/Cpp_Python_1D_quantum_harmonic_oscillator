#include "hermite.h"

Hermite::Hermite(arma::vec const& x) : range(x) {}

void Hermite::eval(unsigned int const& n) {
    unsigned int i = values.n_cols; // the index of the first polynomial that is yet to compute
    if (i <= n) { // no shrinking
        values.resize(range.n_elem, n+1);

        // values of H_0 and H_1
        if (i == 0) {
            values.col(0) = arma::vec(range.n_elem, arma::fill::ones);
            i++;
        }
        if (i == 1 && i <= n) {
            values.col(1) = 2 * range;
            i++;
        }

        // values found by induction
        for (; i <= n; i++) {
            values.col(i) = values.col(1) % values.col(i-1) - 2 * (i-1) * values.col(i-2);
        }
    }
}

arma::vec Hermite::get(unsigned int const& n) const {
    return values.col(n);
}

bool Hermite::is_range(arma::vec const& x) const {
    return arma::approx_equal(range, x, "absdiff", 0.0);
}