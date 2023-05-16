#!/bin/sh

cmake -S ./ -B ./build
cmake --build ./build --config RelWithDebInfo --clean-first
cmake --install ./build --prefix ./build/install

