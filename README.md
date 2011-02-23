# node-cuda

node-cuda provides [NVIDIA CUDA](http://www.nvidia.com/object/cuda_home_new.html) bindings for [Node.js](http://nodejs.org/).

# Prerequisites

You will need to have a CUDA compatible GPU as well as have the appropriate [CUDA Toolkit](http://developer.nvidia.com/object/cuda_3_2_downloads.html) (version 3.2) installed for your platform.

# Installation

To obtain and build the bindings:

    git clone http://github.com/kashif/node-cuda.git
    cd node-cuda
    node-waf configure build
