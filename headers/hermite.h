#ifndef HERMITE
#define HERMITE

#include <armadillo>

class Hermite {
    private:
    arma::vec const range;
    arma::mat values; ///< will contain the result calculated by the eval(unsigned int)

    public:
    /**
     * Constructor
     * 
     * @param x The range of values you wish to evaluate Hermite polynomials over
    */
    Hermite(arma::vec const& x);

    /**
    * A procedure to pre-compute Hermite polynomials
    *
    * this method evaluates Hermite polynomials H_i for all 0 <= i <= n over the range of values passed to the constructor and stores them
    *
    * @param n The method evaluates n+1 polynomials, from H_0 to H_n
    *
    * if this method is called several times with different integers n_1 and n_2, the values for Hermite polynomials from H_0 to H_m will be stored, with m = max(n_1, n_2), which means no pre-computed values are deleted, and pre-computed values are not re-computed
    */
    void eval(unsigned int const& n);

    /**
     * A function to yield a pre-computed Hermite polynomial
     * 
     * this method returns a vector that contains the values of the Hermite polynomial H_n evaluated over the range of values passed to the constructor
     * 
     * @param n H_n is the polynomial yielded by this method
     * 
     * if this method is called on a polynomial that isn't computed yet, armadillo crashes the program
    */
    arma::vec get(unsigned int const& n) const;

    /**
     * A function to check if the input vector is equal to the range of values passed to the constructor
    */
    bool is_range(arma::vec const& x) const;
};

#endif