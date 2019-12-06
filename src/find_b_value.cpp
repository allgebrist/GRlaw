#include <Rcpp.h>
#include <math.h>
#include <string>
#include <algorithm>

// N(M): cumulative curve, giving the number of
//       earthquakes of magnitude greater than
//       or equal to M per year
//
// https://www.kaggle.com/c/LANL-Earthquake-Prediction

// Inline function to take base 10 logarithm
inline double common_logarithm(double x) { 
  return ::log10(x);
}

// [[Rcpp::export]]
// Function least_squares
Rcpp::List least_squares(Rcpp::NumericVector& N, Rcpp::NumericVector& M) {
  Rcpp::List line; 
  
  Rcpp::NumericVector X(N.size());
  Rcpp::NumericVector Y = M;
  
  // Store the base 10 loagarithm of all entries from N(M) into X
  std::transform(N.begin(), N.end(), X.begin(), common_logarithm);
  X.names() = N.names();
  
  // Compute average of X[] and Y[] 
  double X_avg = 0, Y_avg = 0;
  for (int k = 0; k < X.size(); k++) {
    X_avg += X[k];
    Y_avg += Y[k];
  }
  X_avg /= (double) X.size();
  Y_avg /= (double) Y.size();
  
  // Compute Beta
  double top = 0, bottom = 0;
  for (int k = 0; k < X.size(); k++) {
    top += ((X[k] - X_avg) * (Y[k] - Y_avg));
    bottom += ((X[k] - X_avg) * (Y[k]- Y_avg));
  }
  double a = top / bottom;
  double b = Y_avg - a * X_avg;
  
  line = Rcpp::List::create( Rcpp::Named("a") = a, Rcpp::Named("b_value") = b );
  return line;
}

// [[Rcpp::export]]
// Function maximum_likelihood_estimation
double maximum_likelihood_estimation(Rcpp::NumericVector& data) {
  double data_length = (double) data.size(), data_avg = 0;
  double data_min = *std::min_element(data.begin(), data.end());
  for (auto x : data) {
    data_avg += x;
  }
  data_avg /= data_length;
  double mle = log10(exp(1)) / (data_avg - data_min);
  return mle;
}

// [[Rcpp::export]]
// Function find_b_value
double find_b_value(Rcpp::NumericVector& N, Rcpp::NumericVector& M, std::string method = "ls") {
  if (method == "ls") {
    // Fit the line log(N(M)) vs M
    Rcpp::Function least_squares("least_squares");
    Rcpp::List line = Rcpp::as<Rcpp::List>( least_squares(N, M) );
    return line["b_value"];
  } else if (method == "mle") {
    // Compute maximum likelihood estimation
    Rcpp::Function maximum_likelihood_estimation("maximum_likelihood_estimation");
    double b_value = Rcpp::as<double>( maximum_likelihood_estimation(M) );
    return b_value;
  } else {
    // Throw error if no valid method is specified
    throw std::invalid_argument("Please specify a valid method.");
  }
  return 0;
}

/*** R
maximum_likelihood_estimation(c(4, 5, 6))
find_b_value(c(-1, 0, 2), c(4, 5, 6), method = "mle")
find_b_value(c(1, 10, 100), c(0, 1, 2), method = "ls")
find_b_value(c(-1, 0, 2), c(4, 5, 6), method = "fifa_world_cup")
*/
