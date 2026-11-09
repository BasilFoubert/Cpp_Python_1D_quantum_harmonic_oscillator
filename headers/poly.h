#ifndef POLY
#define POLY

#include <armadillo>
#include "hermite.h"
#include "laguerre.h"

class Poly {
    public:
    Poly();
    ~Poly();

    /**
    * @brief Pre-computes Hermite polynomials up to a given order over a range of values.
    * 
    * This function calculates and stores Hermite polynomials H_i (with 0 <= i <= n)
    * for later retrieval, evaluated over the specified range of values.
    *
    * @param n The maximum order of the Hermite polynomial to compute.
    * @param range The range of values over which to evaluate the polynomials.
    */
    void calcHermite(unsigned int const& n, arma::vec const& range);

    /**
    * @brief Retrieves a pre-computed Hermite polynomial of a specified order.
    * 
    * This function returns the Hermite polynomial H_n that has been pre-computed
    * by the calcHermite function.
    *
    * @param n The order of the Hermite polynomial to retrieve.
    * @return arma::vec The pre-computed Hermite polynomial of order n.
    */
    arma::vec hermite(unsigned int const& n);

    /**
    * @brief Pre-computes associated Laguerre polynomials up to a given order over a range of values.
    * 
    * This function calculates and stores associated Laguerre polynomials L_n^m for
    * later retrieval, evaluated over the specified range of values.
    *
    * @param m The order of the associated polynomial.
    * @param n The degree of the Laguerre polynomial to compute.
    * @param range The range of values over which to evaluate the polynomials.
    */
    void calcLaguerre(unsigned int const& m, unsigned int const& n, arma::vec const& range);

    /**
    * @brief Retrieves a pre-computed associated Laguerre polynomial of specified degree and order.
    * 
    * This function returns the associated Laguerre polynomial L_n^m that has been
    * pre-computed by the calcLaguerre function.
    *
    * @param m The order of the associated polynomial.
    * @param n The degree of the Laguerre polynomial to retrieve.
    * @return arma::vec The pre-computed associated Laguerre polynomial L_n^m.
    */
    arma::vec laguerre(unsigned int const& m, unsigned int const& n);

    private:
    Hermite* herm;
    Laguerre* lag;
};

#endif