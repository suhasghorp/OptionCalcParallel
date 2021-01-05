# OptionCalcParallel

[![Build Status](https://travis-ci.com/suhasghorp/OptionCalcParallel.svg?branch=master)](https://travis-ci.com/suhasghorp/OptionCalcParallel)

A C++ Call Option Parallel Monte Carlo Pricer

## Running with Docker

A pre-built image of the project is available as a [Docker](https://www.docker.com/) image. To download the image, run

```bash
docker pull suhasghorp/OptionCalcParallel
```

To use the image, run the provided script to launch a Docker container named `OptionCalcParallel_dev` in the background

```bash
./launch_docker.sh
```

You may also build the Docker image yourself by providing the launch script with the `build` argument.

## Building From Source

First make sure that you have a C++ compiler and CMake installed. Clone the repo and install with CMake:

```bash
git clone --recursive https://github.com/suhasghorp/OptionCalcParallel.git
cd OptionCalcParallel
mkdir build
cd build
cmake ..
make
```

To build the documentation, you can invoke the `docs` make target:

```bash
make docs
```

## Running unit tests

One can run unit tests by building with the `TESTS` variable

```bash
mkdir build
cd build
cmake -DTESTS=TRUE ..
make
make test
```

The directory structure is as follows:

```bash
OptionCalcParallel
├── include
│   └── OptionCalcParallel
│       └── EquityPriceGenerator.h
│       └── MCEuroOptPricer.h
├── src
│   ├── CMakeLists.txt
│   └── EquityPriceGenerator.cpp
│   └── MCEuroOptPricer.cpp
├── example
│   ├── CMakeLists.txt
│   └── example.cpp
├── docker
│   └── Dockerfile
├── extern
│   ├── CMakeLists.txt
│   └── catch2
│   └── spdlog
├── tests
│   ├── CMakeLists.txt
│   └── test_OptionCalcParallel.cpp
├── docs
│   ├── CMakeLists.txt
│   └── main.md
├── README.md
├── LICENSE
├── CMakeLists.txt
├── launch_docker.sh
├── .travis.yml
└── .gitignore
```

## License

This software is licensed under the terms of the MIT license. See `LICENSE` for more details.
