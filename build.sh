rm -rf build
mkdir build
cd build
cmake ..
make
time ./TSP -m bf -f ../data/italy.csv