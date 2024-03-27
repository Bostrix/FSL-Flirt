#include "tests.hpp"

int main(int argc, char *argv[]) {

  Matrix A(5, 5);

  randu(A);

  Matrix ATA = A.t() * A;

  SymmetricMatrix PD;
  PD << ATA;

  Matrix L = Cholesky(PD);

  cout << "ATA:" << endl;
  cout <<  ATA   << endl;
  cout << "PD: " << endl;
  cout <<  PD    << endl;
  cout << "L: "  << endl;
  cout <<  L     << endl;

  return 0;
}
