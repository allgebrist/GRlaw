# GRlaw: Gutenberg-Richter Analysis of Seismic Data
The Gutenberg-Richter law is an empirical model that expresses the connection between the magnitude *M* and the number *N(M)* of earthquakes of at least that magnitude in a given region. It is given by the equation *log N(M) = a - bM* for some constants *a* and *b* [1]. This repository contains some basic functions to estimate the *a* parameter (also known as the *productivity*) and the *b*-value of custom earthquake catalogs. Such functions were written using Rcpp, an open-source library that facilitates the integration of R and C++.


![alt text](https://github.com/allgebrist/GRlaw/blob/master/data/Screenshot.png)

### References
[1] Gutenberg, B. and C. F. Richter (1944). Frequency of earthquakes in California, Bull. Seism. Soc. Am.
34, 185-188. 

### Maintainer: 
#### Allan A. Zea (TU Berlin, Email: zealobo [at] campus.tu-berlin.de)

### License: MIT
