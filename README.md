# How to build
## Step 1 : Build cmake from source
    sudo apt update
    sudo apt install build-essential 
    sudo apt install libssl-dev
    sudo apt install pkg-config
    export OPENSSL_ROOT_DIR=/usr/include/openssl
    wget https://cmake.org/files/v3.29/cmake-3.29.2.tar.gz
    tar -xzvf cmake-3.29.2.tar.gz
    cd cmake-3.29.2
    ./bootstrap
    make -j$(nproc)
    sudo make install
    # Update PATH Environment Variable
    which cmake
    /usr/local/bin/cmake
    export PATH=/usr/local/bin/cmake:$PATH
    source ~/.bashrc
    cmake --version

## Step 2 : Install dependencies
    sudo apt-get install curl zip unzip tar            
    
    sudo apt install ninja-build
    
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg && bootstrap-vcpkg.bat -disableMetrics
    
## Step 2: Setup dependencies
    git clone https://github.com/pashnidgunde/playGround.git
    cd ./playGround
    
    cmake --preset=Ninja-gcc-x64-debug    
    cd build/Ninja-gcc-x64-debug
    ninja
    
    



