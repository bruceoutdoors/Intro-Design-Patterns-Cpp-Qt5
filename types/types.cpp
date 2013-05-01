#include <QTextStream>

int main() {
	QTextStream cout(stdout);
	int i = 5;
	int j=6;
	int* p = &i;                             /*  *p: ______  */
	int& r=i;      
	int& rpr=(*p);
	i = 10;
	p = &j;                                  /*  *p: ________ */
	rpr = 7;                                 /*  *p: ________ */

	r = 8;                                   /* rpr: ________ */
	cout << "i=" << i << " j=" << j << endl; /*  i: ________ j: ________ */
	return 0;
}
