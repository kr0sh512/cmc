class Sum
{
private:
  int a, b;

public:
  int
    get() const {
    return a + b;
  }

  Sum(int a, int b) : a(a), b(b) {};
  Sum(Sum sum, int b) : a(sum.get()), b(b) {};
};
