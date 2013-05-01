
To Use the model test do the following:

1) Include the pri file at the end of your project pro file using the include() command like so:

include(../path/to/dir/modeltest.pri)

2) Then in your source include "modeltest.h" and instantiate ModelTest with your model so the test can live for the lifetime of your model.  For example:

#include <modeltest.h>

QDirModel *model = new QDirModel(this);
new ModelTest(model, this);

3) That is it.  When the test finds a problem it will assert.  modeltest.cpp contains some hints on how to fix problems that the test finds.

