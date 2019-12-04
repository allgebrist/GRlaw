#include <Rcpp.h>
#include <math.h>
#include <string>
#include <algorithm>
using namespace Rcpp;

// N(M): cumulative curve, giving the number of
//       earthquakes of magnitude greater than
//       or equal to M per year
//
// https://www.kaggle.com/c/LANL-Earthquake-Prediction


// [[Rcpp::export]]
// Function find_b_value
double find_b_value(Rcpp::NumericVector& N, std::string method = "ls") {
  if (method == "ls") {
    // fit linear regression
  } else if (method == "mle") {
    // compute maximum likelihood estimation
    Rcpp::Function maximum_likelihood_estimation("maximum_likelihood_estimation");
    double b_value = as<double>( maximum_likelihood_estimation(N) );
    return b_value;
  } else {
    // throw error
    throw std::invalid_argument("Please specify a valid method.");
  }
  return 0;
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

/*** R
maximum_likelihood_estimation(c(-1, 0, 2))
find_b_value(c(-1, 0, 2), method = "mle")
find_b_value(c(-1, 0, 2), method = "fifa_world_cup")
*/
