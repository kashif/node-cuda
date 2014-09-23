# node-cuda

[node-cuda](https://github.com/kashif/node-cuda) provides [NVIDIA CUDA](https://developer.nvidia.com/cuda-zone)™ bindings for [Node.js](http://nodejs.org/)®.

## Prerequisites

You will need to have a CUDA compatible GPU as well as the latest [CUDA Drivers and Toolkit](https://developer.nvidia.com/cuda-downloads) installed for your platform. Currently only tested on OSX and Linux 64-bit.

## Installation

To obtain and build the bindings:

    git clone git://github.com/kashif/node-cuda.git
    cd node-cuda
    node-gyp configure build

or install it via [npm](https://www.npmjs.org/):

    npm install node-cuda
