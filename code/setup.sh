CURRENTDIR=`pwd`
mkdir /tmp/octoDrone-deps
cd /tmp/octoDrone-deps
git clone https://github.com/glfw/glfw.git
git clone https://github.com/nigels-com/glew.git
cd glew/
cd auto/
make PYTHON=python2
cd ../
make
sudo make install
cd ../glfw/
cmake .
make
sudo make install
rm -rf /tmp/octoDrone-deps
cd $CURRENTDIR
mkdir liboctodrone/build
mkdir liboctodrone/lib
mkdir liboctodronecomms/build
mkdir liboctodronecomms/lib
mkdir liboctodroneparrot/build
mkdir liboctodroneparrot/lib
mkdir programs/build
mkdir simulations/build
mkdir simulations/bin
./build.sh
