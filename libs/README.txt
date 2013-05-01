These libraries compile against Qt 4.7.1.
Most of these classes require at least Qt 4.6 to build.

NOTE: you need to have an environment variable pointing to this directory

export CPPLIBS=path/for/built/libs    # bash
set CPPLIBS=X:\path\for\built\libs    # win32 cmd

Feel free to comment out the directories you do not want
to build in libs.pro or tests/tests.pro

filetagger and mobilitymetadata are both drop-in replacements for 
phononmetadata and you only need one of them. 

Building and using mobilitymetadata or filetagger 
requires installing or building additional libraries,
and you will find a README in each directory explaining 
the requirements.

In the case of filetagger, you need taglib 1.6.3.
In the case of mobilitymetadata, you need Qt Mobility 1.1.1

If you want taglib related projects below built, set this environment
variable before running qmake:

export USE_TAGLIB=true   # linux
set USE_TAGLIB=true      # windows

Why 3 versions of metadataloader?

On linux, all 3 of them work fine. You can use the phonon version no problem.
On windows, only taglib works for extracting metadata from MP3s so we offer
that as an alternative.
On Symbian, mobilitymetadata works the best. 

