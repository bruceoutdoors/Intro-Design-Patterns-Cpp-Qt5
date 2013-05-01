class Fraction {
public:
    Fraction(int n, int d = 1)
            : m_Numer(n), m_Denom(d) {}
    Fraction times(const Fraction& other) {
       return Fraction(m_Numer* other.m_Numer, m_Denom* other.m_Denom);
    }
            
private:
    int m_Numer, m_Denom;
};

