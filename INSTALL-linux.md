# Build on Ubuntu 16.04

## Build caffe for waifu2x-caffe

```
git clone -b waifu2x-caffe-ubuntu https://github.com/nagadomi/caffe.git ltcggie-caffe
cd ltcggie-caffe
cp Makefile.config.example-ubuntu Makefile.config
# edit Makefile.config
make
```

## Build waifu2x-caffe

(I tested on Ubuntu16.04 + CUDA8.0 + CuDNN 5.0 + GTX 1080)

```sh
git clone -b ubuntu https://github.com/nagadomi/waifu2x-caffe.git
cd waifu2x-caffe
git submodule update --init --recursive

# create symlink to ltcggie-caffe
ln -s ../ltcggie-caffe ./caffe
ln -s ../ltcggie-caffe ./libcaffe

# build
rm -fr build # clean
mkdir build
cd build
cmake .. -DCUDA_NVCC_FLAGS="-D_FORCE_INLINES  -gencode arch=compute_61,code=sm_61 " # sm_61 is for GTX1080
make
ln -s `realpath ./waifu2x-caffe` ../bin
```

## Run
```
cd bin
./waifu2x-caffe -p cudnn -m scale -i input.png -o out.png | nkf
./waifu2x-caffe -p cuda -m scale -i input.png -o out.png | nkf
./waifu2x-caffe -p cpu -m scale -i input.png -o out.png | nkf
```
