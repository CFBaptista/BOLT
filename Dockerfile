FROM ubuntu:24.04

WORKDIR /app

RUN \
    # Update package lists
    apt-get update && \
    \
    # GNU toolchain
    apt-get install -y binutils && \
    apt-get install -y g++ && \
    apt-get install -y lcov && \
    apt-get install -y make && \
    \
    # LLVM toolchain
    apt-get install -y clang && \
    apt-get install -y clang-format && \
    apt-get install -y clang-tidy && \
    apt-get install -y libstdc++-14-dev && \
    apt-get install -y lld && \
    \
    # Miscellaneous
    apt-get install -y catch2 && \
    apt-get install -y cmake && \
    apt-get install -y cppcheck && \
    apt-get install -y doxygen && \
    apt-get install -y git && \
    apt-get install -y python3 && \
    apt-get install -y ninja-build && \
    \
    # Clean up
    apt-get clean && \
    apt-get autoclean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/* var/cache/apt/archives/*

RUN ln -s /usr/bin/llvm-cov-18 /usr/local/bin/llvm-cov && \
    ln -s /usr/bin/llvm-profdata-18 /usr/local/bin/llvm-profdata

ENTRYPOINT ["/bin/bash"]
