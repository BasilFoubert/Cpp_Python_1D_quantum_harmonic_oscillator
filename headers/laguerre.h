#ifndef LAGUERRE
#define LAGUERRE

// SPEC À METTRE À JOUR

#include <armadillo>

class Laguerre {
    private:
    arma::vec const range;
    arma::cube values; ///< will contain the result calculated by eval(unsigned int, unsigned int)

    public:
    /**
     * Constructor
     * 
     * @param x The range of values you wish to evaluate Laguerre polynomials over
    */
    Laguerre(arma::vec const& x);

    /**
    * A procedure to pre-compute polynomials
    *
    * this method evaluates Laguerre polynomials L^j_i for all 0 <= j <= m and 0 <= i <= n over the range of values passed to the constructor and stores them
    *
    * @param m The method evaluates (m+1)(n+1) polynomials, from L^0_0 to L^m_n
    * @param n The method evaluates (m+1)(n+1) polynomials, from L^0_0 to L^m_n
    *
    * if this method is called several times with different pairs of integers (m_1, n_1) and (m_2, n_2), the values for Laguerre polynomials from L^0_0 to L^M_N will be stored, with M = max(m_1, m_2) and N = max(n_1, n_2), which means no pre-computed values are deleted, and pre-computed values are not re-computed
    */
    void eval(unsigned int const& m, unsigned int const& n);

    /**
     * A function to yield a pre-computed Laguerre polynomial
     * 
     * this method returns a vector that contains the values of the Laguerre polynomial L^m_n evaluated over the range of values passed to the constructor
     * 
     * @param n L^m_n is the polynomial yielded by this method
     * 
     * if this method is called on a polynomial that isn't computed yet, armadillo crashes the program
    */
    arma::vec get(unsigned int const& m, unsigned int const& n) const;

    /**
     * A function to check if the input vector is equal to the range of values passed to the constructor
    */
    bool is_range(arma::vec const& x) const;
};

#endif