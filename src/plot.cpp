#include "plot.h"
#include <sstream>


Plot::Plot(double const& width, double const& height, unsigned int const& n_points_axis_x_or_y, unsigned int const& n_points_axis_z) : width(width), height(height), nx(n_points_axis_x_or_y), nz(n_points_axis_z) {}

arma::vec Plot::get_r_values_2D() {
  if (nx & 1) { // nx odd
    arma::vec r_values((nx+1) >> 1);
    for (unsigned int i = 0; i <= (nx >> 1); i++) {
      r_values(i) = i;
    }
    return (width / (nx-1.0)) * r_values;
  }
  else { // nx even
    arma::vec r_values(nx >> 1);
    for (unsigned int i = 1; i < nx; i += 2) {
      r_values(i >> 1) = i;
    }
    return (width / (2 * (nx-1.0))) * r_values;
  }
}

arma::vec Plot::get_r_values_3D() {
  if (nx & 1) { // nx odd
    arma::vec r_values((nx+1) * (nx+3) >> 3);
    for (unsigned int i = 0; i <= (nx >> 1); i++) {
      for (unsigned int j = 0; j <= i; j++) {
        r_values((i * (i+1) >> 1) + j) = sqrt(i*i + j*j);
      }
    }
    return (width / (nx-1.0)) * r_values;
  }
  else { // nx even
    arma::vec r_values(nx * (nx+2) >> 3);
    for (unsigned int i = 1; i < nx; i += 2) {
      for (unsigned int j = 1; j <= i; j += 2) {
        r_values(((i-1) * (i+1) >> 3) + (j >> 1)) = sqrt(i*i + j*j);
      }
    }
    return (width / (2 * (nx-1.0))) * r_values;
  }
}

arma::vec Plot::get_z_values() {
  return arma::linspace(-height/2, height/2, nz);
}

arma::mat Plot::polar_to_cartesian_2D(arma::mat const& polar_values) {
  arma::mat cartesian_values(nx, nz);
  unsigned int mid;
  if (nx & 1) {
    mid = nx >> 1;
    for (unsigned int k = 0; k < nz; k++) {
      for (unsigned int i = 0; i < nx; i++) {
        cartesian_values(i, k) = polar_values(abs((int) (i - mid)), k);
      }
    }
  }
  else {
    mid = nx - 1;
    for (unsigned int k = 0; k < nz; k++) {
      for(unsigned int i = 0; i < nx; i++) {
        cartesian_values(i, k) = polar_values((abs((int) ((i << 1) - mid)) - 1) >> 1, k);
      }
    }
  }
  return cartesian_values;
}

arma::cube Plot::polar_to_cartesian_3D(arma::mat const& polar_values) {
  arma::cube cartesian_values(nx, nx, nz);
  unsigned int a;
  unsigned int b;
  unsigned int mid;
  if (nx & 1) { // nx odd
    mid = nx >> 1;
    for (unsigned int k = 0; k < nz; k++) {
      for (unsigned int j = 0; j < nx; j++) {
        for (unsigned int i = 0; i < nx; i++) {
          a = abs((int) (i-mid));
          b = abs((int) (j-mid));
          if (a < b) {
            a += b;
            b = a-b;
            a -= b;
          }
          cartesian_values(i, j, k) = polar_values((a * (a+1) >> 1) + b, k);
        }
      }
    }
  }
  else { // nx even
    mid = nx - 1;
    for (unsigned int k = 0; k < nz; k++) {
      for (unsigned int j = 0; j < nx; j++) {
        for (unsigned int i = 0; i < nx; i++) {
          a = abs((int) ((i << 1) - mid)) >> 1;
          b = abs((int) ((j << 1) - mid)) >> 1;
          if (a < b) {
            a += b;
            b = a-b;
            a -= b;
          }
          cartesian_values(i, j, k) = polar_values((a * (a+1) >> 1) + b, k);
        }
      }
    }
  }
  return cartesian_values;
}

void Plot::write_3D(arma::cube const& values, char const* filename) {
	std::stringstream ss(std::stringstream::out | std::stringstream::binary);
  unsigned int nx = values.n_rows;
  unsigned int ny = values.n_cols;
  unsigned int nz = values.n_slices;
  ss.put(nx >> 8);
  ss.put(nx & 0xff);
  ss.put(ny >> 8);
  ss.put(ny & 0xff);
  ss.put(nz >> 8);
  ss.put(nz & 0xff);
  double theMin = 0.0;
  double theMax = values.max();
  for (uint k = 0; k < nz; k++)
  {
    for (uint j = 0; j < ny; j++)
    {
      for (uint i = 0; i < nx; i++)
      {
        uint v = 255 * (fabs(values(i, j, k)) - theMin) / (theMax - theMin);
        ss.put(v);
      }
    }
  }

	std::ofstream df3file;
	df3file.open(filename, std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
	df3file << ss.str();
	df3file.close();
}


void Plot::write_2D(arma::mat const& values, char const* filename){
    values.save(filename, arma::csv_ascii);
}