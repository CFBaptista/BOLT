FROM ubuntu:26.04

WORKDIR /app

RUN \
    # Update package list
    apt-get update && \
    # Install GNU tools
    apt-get install -y binutils && \
    apt-get install -y g++-16 && \
    apt-get install -y gdb && \
    apt-get install -y libstdc++-16-dev && \
    apt-get install -y make && \
    # Install LLVM tools
    apt-get install -y clang-21 && \
    apt-get install -y clang-format-21 && \
    apt-get install -y clang-tidy-21 && \
    apt-get install -y clangd-21 && \
    apt-get install -y libc++-21-dev && \
    apt-get install -y lld-21 && \
    apt-get install -y lldb-21 && \
    # Install additional tools
    apt-get install -y catch2 && \
    apt-get install -y cmake && \
    apt-get install -y cppcheck && \
    apt-get install -y doxygen && \
    apt-get install -y git && \
    apt-get install -y lcov && \
    apt-get install -y ninja-build && \
    # Clean up
    apt-get clean && \
    apt-get autoclean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/* var/cache/apt/archives/*

RUN \
    # Configure default GNU tools
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-16 100 && update-alternatives --set g++ /usr/bin/g++-16 && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-16 100 && update-alternatives --set gcc /usr/bin/gcc-16 && \
    # Configure default LLVM tools
    update-alternatives --install /usr/bin/clang clang /usr/bin/clang-21 100 && update-alternatives --set clang /usr/bin/clang-21 && \
    update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-21 100 && update-alternatives --set clang++ /usr/bin/clang++-21 && \
    update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-21 100 && update-alternatives --set clang-format /usr/bin/clang-format-21 && \
    update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-21 100 && update-alternatives --set clang-tidy /usr/bin/clang-tidy-21 && \
    update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-21 100 && update-alternatives --set clangd /usr/bin/clangd-21 && \
    update-alternatives --install /usr/bin/lld lld /usr/bin/lld-21 100 && update-alternatives --set lld /usr/bin/lld-21 && \
    update-alternatives --install /usr/bin/lldb lldb /usr/bin/lldb-21 100 && update-alternatives --set lldb /usr/bin/lldb-21

ENTRYPOINT ["/bin/bash"]
