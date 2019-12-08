#include <Rcpp.h>
#include <algorithm>

//' Compute the cumulative frequency of seismic events with given magnitudes
//'
//' @param magnitudes A numeric vector containing the magnitudes from a seismic event catalog.
//' @return A list containing the (sorted) vector \eqn{M} of magnitudes and the vector \eqn{N(M)} 
//' corresponding to the number of earthquakes of magnitude greater than or equal to \eqn{M}.
//' 
//' @export
//' @examples
//' cumulative_frequency(c(1, 1, 5))
//' cumulative_frequency(c(6, 5, 4, 3, 2, 1, 1))
//'
//' 
// [[Rcpp::export]]
// Function cumulative_frequency
Rcpp::List cumulative_frequency(Rcpp::NumericVector& magnitudes) {
  Rcpp::List cumulative_frequencies; 
  Rcpp::NumericVector frequencies(magnitudes.size(), 0);
  
  if (frequencies.size() == 1) {
    frequencies[0] = 1;
  } else {
    std::sort(magnitudes.begin(), magnitudes.end());
    std::sort(frequencies.begin(), frequencies.end());
    frequencies[frequencies.size()-1] = 1;
    for (int k = frequencies.size()-2; k >= 0; k--) {
      frequencies[k] = frequencies[k+1] + 1;
    }
  }
  
  cumulative_frequencies = Rcpp::List::create( Rcpp::Named("magnitude") = magnitudes, 
                                               Rcpp::Named("count") = frequencies );
  
  return cumulative_frequencies;
}


