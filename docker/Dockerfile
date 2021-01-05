FROM ubuntu:slim
WORKDIR /build
RUN apt-get update -qq && \
    apt-get install -qqy --no-install-recommends \
      build-essential \
      vim \
      git \
      cmake \
      wget \
      curl \
      htop &&\
    rm -rf ~/.cache
RUN git clone --recursive https://github.com/suhasghorp/OptionCalcParallel.git . &&\
    mkdir build &&\
    cd build &&\
    cmake -DTESTS=TRUE .. &&\
    make && make test && make install
WORKDIR /mnt
RUN rm -rf /build

