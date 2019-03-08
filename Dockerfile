FROM stronglytyped/arm-none-eabi-gcc

# Install Protobuf
RUN apt-get update && \
    apt-get -y install git unzip build-essential autoconf libtool pkg-config

RUN git clone https://github.com/google/protobuf.git && \
    cd protobuf && \
    ./autogen.sh && \
    ./configure && \
    make && \
    make install && \
    ldconfig && \
    make clean && \
    cd .. && \
    rm -r protobuf


