IF NOT "%1" == "-no-cmake" (
    cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja -B ./bin .
)

ninja -C bin
