This is an alternative to phononmetadata which works on
windows, mac, and linux. 

This library requires taglib 1.6, which builds on
    windows and is included on most linux distros and macports/fink:
    http://developer.kde.org/~wheeler/taglib.html

debian/ubuntu/fink install instructions:
    apt-get install libtag1-dev libtag1-doc libtag1

Windows build/install instructions:
  download and install cmake
  Decide on a directory to install to that contains no spaces.
       call that TAGLIB_DIR, and set an environment variable to point to it. 
  Follow these instructions:
        http://www.joelverhagen.com/blog/2010/11/how-to-compile-taglib-on-windows/
  in cmake-gui, after the configure:
        set the CMAKE_INSTALL_PREFIX to TAGLIB_DIR
  make
  make install
  copy %TAGLIB_DIR%\lib*.* %CPPLIBS%

Some of the other examples and testcases optionally use this library instead
of phonon if you have the USE_TAGLIB environment variable set before you run
qmake.  

