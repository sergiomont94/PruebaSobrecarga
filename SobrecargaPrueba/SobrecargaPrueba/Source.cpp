#include "conio.h"
#include "iostream"
#include "algorithm"
#include "vector"
using namespace std;

class BigInt {
	vector<int> digits;
public:
	BigInt(const BigInt& a);
	BigInt(string num = "0");
	BigInt operator+(const BigInt& a) const;
	BigInt& operator+=(const BigInt& a);
	BigInt& operator=(BigInt a);
	friend std::ostream& operator<<(std::ostream& out, BigInt a);
};

struct Ascii2Int { int operator()(int c) { return c - '0'; } };

BigInt::BigInt(const BigInt& other) :digits(other.digits) {}

BigInt& BigInt::operator=(BigInt a) {
	digits.swap(a.digits);
	return *this;
}

BigInt::BigInt(string num) {
	transform(num.rbegin(), num.rend(), back_inserter(digits), Ascii2Int());
}
BigInt& BigInt::operator +=(const BigInt& a)
{
	unsigned int maxSize;
	unsigned int num = 0;
	unsigned int carry = 0;

	//size for output variable
	if (digits.size()<a.digits.size()) {
		maxSize = a.digits.size();
		digits.resize(a.digits.size());
	}
	else {
		maxSize = digits.size();
	}

	for (unsigned int i = 0; i < maxSize; i++)
	{
		if (i<a.digits.size())
			num = digits[i] + a.digits[i] + carry;
		else
			num = digits[i] + carry;

		if (num >= 10)
		{
			num = num - 10;
			carry = 1;
		}
		else {
			carry = 0;
		}

		digits[i] = num;
	}
	if (carry) {
		digits.push_back(1);
	}

	return *this;
}

BigInt BigInt::operator +(const BigInt& a) const
{
	return BigInt(*this) += a;

}

std::ostream& operator <<(std::ostream& out, BigInt a)
{
	for (unsigned int i = 0; i < a.digits.size(); i++) {
		out << a.digits[i] << endl;
	}
	return out;
}

int main() {
	BigInt B1("981654321");
	BigInt B2("98431");
	BigInt B3;
	B3 = B1 + B2;
	cout << "B1+B2 is" << B3 << endl;
	BigInt B4;
	B4 += B1;
	B4 += B2;
	B4 += B3;
	cout << "B4 is" << B4 << endl;
	return 0;
}