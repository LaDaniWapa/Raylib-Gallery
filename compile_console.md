## create docker container
Container from this [repo](https://github.com/geniot/trimui-smart-pro-toolchain)
```bash
docker run -d --name gallery -it --volume=./:/work/ --workdir=/work trimui-sdk
```

## go inside
```bash
docker start gallery
docker exec -it gallery /bin/bash
```

## install cmake
```bash
wget https://github.com/Kitware/CMake/releases/download/v3.27.9/cmake-3.27.9-linux-x86_64.tar.gz
tar -xzf cmake-3.27.9-linux-x86_64.tar.gz
export PATH=/opt/cmake-3.27.9-linux-x86_64/bin:$PATH
echo 'export PATH=/opt/cmake-3.27.9-linux-x86_64/bin:$PATH' >> ~/.bashrc
```

## compile
```bash
cd /work
mkdir -p build && cd build
cmake -DTRIMUI=ON ..
make -j$(nproc)
```