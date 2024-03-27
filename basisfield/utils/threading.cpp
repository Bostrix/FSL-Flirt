#include <array>
#include <cstdint>
#include <cstdlib>
#include <dlfcn.h>
#include <string>
#include "threading.h"


namespace Utilities {

void fsl_init_blas_threading(uint16_t flags) {

  static std::array<std::string, 6> blaspaths = {
    "libblas.so",
    "libblas.dylib",
    "libcblas.so",
    "libcblas.dylib",
    "libopenblas.so",
    "libopenblas.dylib"
  };

  /*
   * Now load libblas.so. If it is an OpenBLAS
   * implementation, get a ref to openblas_set_num_threads,
   * and use it to set the number of threads to 1. All errors
   * (e.g. cannot find libblas.so) are silently ignored.
   */

  /* load libblas */
  void *blas = NULL;
  for (auto path : blaspaths) {
    blas = dlopen(path.c_str(), RTLD_LAZY);

    /*
     * clear any error messages, but ignore them - dlerror
     * may return an error message even if the library has
     * been successfully loaded.
     */
    dlerror();
    if (blas != NULL) {
      break;
    }
  }
  if (blas == NULL) {
    return;
  }

  /* get ref to openblas_set_num_threads function */
  typedef void (*func)(int num_threads);
  func set_threads = (func)dlsym(blas, "openblas_set_num_threads");

  /* clear but ignore error messages */
  dlerror();
  if (set_threads == NULL) {
    return;
  }

  /* disable openblas threading */
  set_threads(1);

  /* close blas, and clear error in case dlclose fails */
  dlclose(blas);
  dlerror();
}
} // namespace Utilities
