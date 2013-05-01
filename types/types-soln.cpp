#include <QTextStream>

int main() {
	QTextStream cout(stdout);
	int i = 5;
	int j=6;
	int* p = &i;   /*  *p: 5  */

	int& r=i;      
	int& rpr=(*p);
	i = 10;
	p = &j;       /*  *p: 6 */
	rpr = 7;      /*  *p: 6 */

	r = 8;        /* rpr: 8 */
	cout << "i=" << i << " j=" << j << endl; /* i: ________ j: ________ */
	return 0;
}
