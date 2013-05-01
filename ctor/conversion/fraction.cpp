class Fraction {
public:
    Fraction(int n)                  /* Single argument ctor defines a conversion from int. */
       : m_Numer(n), m_Denom(1) {}
    Fraction(int n, int d )
       : m_Numer(n), m_Denom(d) {}
    Fraction times(const Fraction& other) {
       return Fraction(m_Numer * other.m_Numer, m_Denom * other.m_Denom);
    }
private:
    int m_Numer, m_Denom;
};
int main() {
    int i;
    Fraction frac(8);                /* Conversion constructor call. */
    Fraction frac2 = 5;              /* Copy init (calls conversion ctor too). */
    frac = 9;                        /* Conversion followed by assignment. */
    frac = (Fraction) 7;             /* C-style typecast (deprecated). */
    frac = Fraction(6);              /* Explicit temporary, also a C++ typecast. */
    frac = static_cast<Fraction>(6); /* Preferred ANSI style typecast. */
    frac = frac2.times(19);          /* Implicit call to the conversion constructor. */
    return 0;
}

