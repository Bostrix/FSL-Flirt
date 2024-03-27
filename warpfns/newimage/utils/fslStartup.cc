// Matthew Webster, WIN Analysis Group
// Copyright (C) 2022 University of Oxford
/*  CCOPYRIGHT  */
#include <cstdlib>
#include <iostream>

#include "threading.h"

namespace Utilities {

    //A global instance of this class is constructed before main to set key
    //FSL parameters. A binary environment variable, FSL_SKIP_GLOBAL, allows
    //all sub-methods to be bypassed.

    class globalConfig {
        public:
            globalConfig () {
                if ( std::getenv("FSL_SKIP_GLOBAL") && std::atoi(std::getenv("FSL_SKIP_GLOBAL")) != 0)
                    return;
                //Disable openblas threading
                Utilities::fsl_init_blas_threading();
            }
    };

    static globalConfig fslStartup;
}