#include "poly.h"

Poly::Poly() : herm(new Hermite(arma::vec())), lag(new Laguerre(arma::vec())) {}

Poly::~Poly() {
    delete herm;
    delete lag;
}

void Poly::calcHermite(unsigned int const& n, arma::vec const& range) {
    if (!herm->is_range(range)) {
        delete herm;
        herm = new Hermite(range);
    }
    herm->eval(n);
}

arma::vec Poly::hermite(unsigned int const& n) {
    return herm->get(n);
}
    
void Poly::calcLaguerre(unsigned int const& m, unsigned int const& n, arma::vec const& range) {
    if (!lag->is_range(range)) {
        delete lag;
        lag = new Laguerre(range);
    }
    lag->eval(m, n);
}

arma::vec Poly::laguerre(unsigned int const& m, unsigned int const& n) {
    return lag->get(m, n);
}
