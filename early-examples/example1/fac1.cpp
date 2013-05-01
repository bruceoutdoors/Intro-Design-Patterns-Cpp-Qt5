#include <QtGui>

int main (int argc, char* argv[]) {                 /* Start
        of function "main" which returns int. */
    QApplication app(argc, argv);                   /* Start of
        every Qt GUI application. */
    QTextStream cout(stdout);                       /* Create a QTextStream to standard output. */

    // Declarations of variables
    int answer = 0;                                 /* Must be defined
        outside the do loop because it is used in the condition
        outside the do block. */

    do {
        // local variables to the loop:
        int factArg = 0;
        int fact(1);
        factArg = QInputDialog::getInt(0, "Factorial Calculator",
            "Factorial of:", 1);                    /* Pop up dialog,
             wait for user to enter an integer, return it. */
        cout << "User entered: " << factArg << endl;
        int i=2;
        while (i <= factArg) {
            fact = fact * i;
            ++i;
        }
        QString response = QString("The factorial of %1 is %2.\n%3")
            .arg(factArg).arg(fact)                 /* Each %n is replaced with an arg() value. */
            .arg("Compute another factorial?");     /* Long statements can continue on multiple lines, as long as they are broken on token boundaries. */
        answer = QMessageBox::question(0, "Play again?", response,
            QMessageBox::Yes | QMessageBox::No);    /* Bitwise or of two values. */
    } while (answer == QMessageBox::Yes);
    return EXIT_SUCCESS;
}

