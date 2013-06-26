Qt 5 port - An Introduction to Design Patterns in C++ with Qt(2nd Edition)
=========

##### <del> the porting is not complete yet(As I have not finished the book)! However you could still download and check it out to save you time figuring why stuffs didn't work </del>

This is my attempt to port the source code([download it here](http://www.ics.com/designpatterns/dist/src.tar.gz
)) in the book "[An Introduction to Design Patterns in C++ with Qt(2nd Edition)](http://www.amazon.com/Introduction-Patterns-Prentice-Software-Development/dp/0132826453/)" by Alan Ezust and Paul Ezust [from Qt 4 to Qt 5](http://qt-project.org/wiki/Transition_from_Qt_4.x_to_Qt5), plus a bit of C++11. This repo also adds some files that are missing and required for some of the code to work(for example in /layout/form a main.cpp is missing).

I also did some of the exercises(for not just the cardgame) and uploaded it.

#### On Chapter 7. Libraries and Design Patterns(important!):
* How CPPLIBS work here is different from the book(it's mainly because I didn't figure out how the author did and I'm lazy to bother because I think my solution works too)! You might need to edit common.pri in the libs folder 
   - CPPLIBS here refers to the directory where the library(e.g., *.dll, *.so) will be built and accessed from. Make sure that directory exist! `CPPLIBS=C:/directory/where/libraries/are/built`
   - QTLIBS does not exist in the book, but since Qt compiler keeps bugging me that it cannot find Qt libs(like -lQt5Widgets, -lQt5Core) I provided this variable. Now, if you installed Qt 5 in a different directory you have to modify this variable `QTLIBS=C:/Qt/Qt5.0.2/5.0.2/mingw47_32/lib`
* If you wondered why a 'phononmetadata' project(and the test example that uses it) is comment out, it's because phono is DEPRECATED in Qt 5. It's been replaced by QtMultimedia. I was thinking of a 'qmultimediametadata' but maybe not...

  
Contribute
-----------

I've yet gone through the entire book so the port is not complete yet. If you're ahead of me or you have have linux/mac compatible patches or you think I could have done better, you could send me pull requests or something like that to suggest changes. Don't let noobness bother you - I'd really love to hear from you! (: 

You can also upload answers to the exercises if you want(I'll take them with open arms!! :D)

----------------------

all code here is tested with Qt 5.0.2 MinGW 4.7, Windows 7 32bit
