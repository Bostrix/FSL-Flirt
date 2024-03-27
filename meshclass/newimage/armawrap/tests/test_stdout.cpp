#include "tests.hpp"

int main(int argc, char *argv[]) {

  Matrix m(4, 4);
  Matrix m2(4, 4);
  RowVector r(4);
  ColumnVector c(8);

  randu(m);
  randu(m2);
  randu(r);
  randu(c);


  // AWMatrix
  cout << "m" << endl;
  cout << m << endl;

  // AWSubView
  cout << "m.SubMatrix" << endl;
  cout << m.SubMatrix(1, 3, 1, 3) << endl;

  // AWOp
  cout << "m.SubMatrix.t" << endl;
  cout << m.SubMatrix(1, 3, 1, 3).t() << endl;

  // AWEop
  cout << "m * 2" << endl;
  cout << m * 2 << endl;

  // AWGlue
  cout << "r * m" << endl;
  cout << r * m << endl;

  // AWSubView
  cout << "(m * 2).SubMatrix" << endl;
  cout << (m * 2).SubMatrix(1, 3, 1, 3) << endl;

  // AWEGlue
  cout << "m + m2" << endl;
  cout << m + m2 << endl;

  // Other things
  cout << "c" << endl;
  cout << c << endl;
  cout << "c.SubMatrix" << endl;
  cout << c.SubMatrix(2, 4, 1, 1) << endl;
  cout << "c.SubMatrix.t" << endl;
  cout << c.SubMatrix(2, 4, 1, 1).t() << endl;

  RowVector ct = c.SubMatrix(2, 4, 1, 1).t();

  cout << "ct.SubMatrix.t" << endl;
  cout << ct << endl;

}
