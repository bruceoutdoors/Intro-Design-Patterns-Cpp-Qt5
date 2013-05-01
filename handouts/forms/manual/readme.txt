Lab 2: Order Form - manual coding.

In this lab, you are to implement the missing methods from orderform.h,
to construct an input dialog form for Order objects.

This dialog should have at least 3 fields (label + input widget) that
       look roughly like this:

       QString name
       QDate date
       int quantity
       double unitPrice;
       double totalPrice;


The code goes in orderform.cpp.

The user should be able to click "submit" to send data into
the Order, or "cancel" to restore the data from the Order.

The totalPrice field should be read-only, and calculated based on the
quantity and unitPrice.
