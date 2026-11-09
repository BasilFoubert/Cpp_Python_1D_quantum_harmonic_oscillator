#ifndef PLOT
#define PLOT

#include <armadillo>

class Plot {
	public:
	
	/**
	 * Constructor
	 * 
	 * Takes a width and a height, and resolutions (number of points) along x (same resolution for y) and z axes
	 * The class then provides utilities to plot a function that takes polar (r, z) coordinates (i.e. create a matrix or a cube of values of the function, indexed by integers that represent cartesian coordinates), in 2D or 3D
	 * 
	 * @param n_points_axis_x_or_y will be referred to as nx from now on
	 * @param n_points_axis_z will be referred to as nz from now on
	 * 
	 * The standard 2D plot is the function evaluated on a (width * height) rectangle centered at (0,0), on (nx * nz) evenly spaced points
	 * 
	 * The standard 3D plot is the function evaluated on a (width * width * height) rectangle centered at (0,0,0), on (nx * nx * nz) evenly spaced points
	 * 
	 * Example : if f is a function that takes (double r,z) arguments and f2 takes (arma::vec rvals, zvals) arguments and returns a matrix M(i,j) = f(rvals(i), zvals(j)), then this is how to get :
	 * 
	 * a standard 2D plot of f :
	 *     Plot plt(20e-15, 40e-15, 32, 64); // 20*40 fm centered at (0,0), resolution 32*64
	 *     arma::vec rvals = plt.get_r_values_2D();
	 *     arma::vec zvals = plt.get_z_values();
	 *     arma::mat polar_values = f2(rvals, zvals);
	 *     arma::mat plot2D = plt.polar_to_cartesian_2D(polar_values);
	 *     plt.write_2D(plot2D, "example.???");
	 * 
	 * a standard 3D plot of f :
	 *     Plot plt(20e-15, 40e-15, 32, 64); // 20*20*40 fm centered at (0,0,0), resolution 32*32*64
	 *     arma::vec rvals = plt.get_r_values_3D();
	 *     arma::vec zvals = plt.get_z_values();
	 *     arma::mat polar_values = f2(rvals, zvals);
	 *     arma::cube plot3D = plt.polar_to_cartesian_3D(polar_values);
	 *     plt.write_3D(plot2D, "example.df3");
	 *     
	*/
	Plot(double const& width, double const& height, unsigned int const& n_points_axis_x_or_y, unsigned int const& n_points_axis_z);
	

	/**
	 * Gets the values of r to evaluate the function on in order to get a standard 2D plot
	*/
	arma::vec get_r_values_2D();

	/**
	 * Gets the values of r to evaluate the function on in order to get a standard 3D plot
	*/
	arma::vec get_r_values_3D();

	/**
	 * Gets the values of z to evaluate the function on in order to get a standard 2D or 3D plot
	*/
	arma::vec get_z_values();

	/**
	 * Converts a matrix M(i,j) = f(rVals(i), zVals(j)) into a standard 2D plot of f, assuming f takes (r,z) coordinates and rVals and zVals were obtained respectively with the get_r_values_2D() and get_z_values() methods
	*/
	arma::mat polar_to_cartesian_2D(arma::mat const& polar_values);

	/**
	 * Converts a matrix M(i,j) = f(rVals(i), zVals(j)) into a standard 3D plot of f, assuming f takes (r,z) coordinates and rVals and zVals were obtained respectively with the get_r_values_3D() and get_z_values() methods
	*/
	arma::cube polar_to_cartesian_3D(arma::mat const& polar_values);

	/**
	 * Writes a standard 3D plot to an 8-bit df3 file
	 * 
	 * WARNING : the standard 3D plot doesn't contain any information about the width and height, only about resolutions, so a program using the file must know the width and height in order to plot with the correct scale
	*/
	static void write_3D(arma::cube const& values, char const* filename);

	/**
	 * Writes a standard 2D plot to TODO
	 * 
	 * WARNING : the standard 2D plot doesn't contain any information about the width and height, only about resolutions, so a program using the file must know the width and height in order to plot with the correct scale
	*/
	static void write_2D(arma::mat const& values, char const* filename);

	private:
	double const width;
	double const height;
	unsigned int const nx;
	unsigned int const nz;
};

#endif