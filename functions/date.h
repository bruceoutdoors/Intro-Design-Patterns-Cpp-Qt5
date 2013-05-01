#ifndef _DATE_H_
#define _DATE_H_
//start
class Date {
public:
    Date(int d = 0, int m = 0, int y = 0);

    /** @param eoln if true, output end of line
        character after the date.
    */
    void display(bool eoln = true) const;
//end

//start
private:
    int m_Day, m_Month, m_Year;
};
//end
#endif

