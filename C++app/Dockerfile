# Use a base image with CMake, Clang, and other necessary tools
FROM debian:12

# Set the working directory
WORKDIR /home/pp/Projects/orderbook-sim/C++app

# Set the cluster_url environment variable
ENV CLUSTER_URL http://your-cluster-url

# Install CMake, Clang, and other build tools, including the nlohmann-json3-dev package
RUN apt-get update && \
    apt-get install -y cmake clang build-essential libcurl4-openssl-dev nlohmann-json3-dev

# Copy your C++ project source code and CMakeLists.txt into the container
COPY . /home/pp/Projects/orderbook-sim/C++app

# Create a build directory
RUN mkdir -p /home/pp/Projects/orderbook-sim/C++app/build

# Build the C++ project
RUN cd /home/pp/Projects/orderbook-sim/C++app/build && \
    cmake .. && \
    make

# Set the entry point to run your C++ program
CMD ["/app/build/orderbook-sim"]
