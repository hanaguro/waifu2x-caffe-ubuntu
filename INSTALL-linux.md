# Build on Ubuntu

- Build caffe from https://github.com/BVLC/caffe

```sh
git submodule update --init --recursive

ln -s /path-to-caffe ./caffe
ln -s /path-to-caffe/build ./libcaffe

mkdir build
cd build
cmake ..
make

ln -s `realpath ./waifu2x-caffe` ../bin
```
