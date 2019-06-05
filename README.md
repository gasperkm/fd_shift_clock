# FD shift clock
A clock widget constructed in wxWidgets to show local time and one other time zone.
Compile the app with:

```
make
```

Run it with:

```
./fd_shift_clock
```
# Installing wxWidgets
Prerequisites to installing wxWidgets on a clean installation of linux are the following packages:

```
# on Debian related systems
sudo apt-get install binutils build-essential git gcc g++ libgtk-2.0-dev libc++1
# on CentOS and Fedore related systems
sudo yum install epel-release
sudo yum repolist
sudo yum install binutils git gcc gcc-c++ gtk2-devel
```

To install wxWidgets, download the version from the [wxWidgets download site](https://www.wxwidgets.org/downloads/). We assume that `$WXSOURCE` is the location of the downloaded source file, `$WXINSTALL` will be the location of its installation and `X.Y.Z` is the version of wxWidgets. Install it using the following lines:

```
cd $WXSOURCE
tar -jxf wxWidgets-X.Y.Z.tar.bz2
cd $WXSOURCE/wxWidgets-X.Y.Z
mkdir ./gtk-build
cd ./gtk-build
../configure --enable-unicode --enable-debug --prefix=$WXINSTALL/wxWidgets-X.Y.Z
make
make install
```

For wxWidgets to be correctly recognized, add the following environmental variables (preferrably in the `~/.bashrc` script):

```
export WXLIN=$WXINSTALL/wxWidgets-X.Y.Z
export PATH=$WXLIN/bin:$PATH
export LD_LIBRARY_PATH=$WXLIN/lib:$LD_LIBRARY_PATH
```

