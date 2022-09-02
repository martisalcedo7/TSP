rm -rf build
mkdir build
cd build
cp ../fonts/arial.ttf .
cmake ..
make
time ./myApp