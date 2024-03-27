#include "tests.hpp"

int main(int argc, char *argv[]) {

  // make sure that SVD works
  // for non-square matrices
  Matrix         A(12, 10);
  DiagonalMatrix D;
  Matrix         U;
  Matrix         V;
  randu(A);

  cout << "A: (" << A.Nrows() << ", " << A.Ncols() << ")" << endl;
  cout <<  A    << endl << endl;

  SVD(A, D, U, V);

  cout << "D: (" << D.Nrows() << ", " << D.Ncols() << ")" << endl;
  cout <<  D    << endl << endl;
  cout << "U: (" << U.Nrows() << ", " << U.Ncols() << ")" << endl;
  cout <<  U    << endl << endl;
  cout << "V: (" << V.Nrows() << ", " << V.Ncols() << ")" << endl;
  cout <<  V    << endl << endl;

  // But NEWMAT::SVD raises a ProgramException
  // for MxN matrices where M < N
  A = Matrix(10, 12);
  randu(A);

  try {
    SVD(A, D, U, V);
  }
  catch (NEWMAT::ProgramException) {
    cout << "SVD on a M < N matrix correctly raised an exception" << endl;
  }

  return 0;
}
