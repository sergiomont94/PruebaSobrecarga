#include "conio.h"
#include "iostream"
#include "algorithm"
#include "vector"
using namespace std;

class BigInt {
	vector<int> dig;
public:
	BigInt(const BigInt& a);
	BigInt(string num = "0");
	BigInt operator+(const BigInt& a) const;
	BigInt& operator+=(const BigInt& a);
	BigInt& operator=(BigInt a);
	friend std::ostream& operator<<(std::ostream& out, BigInt a);
};

struct Ascii2Int { int operator()(int c) { return c - '0'; } };

BigInt::BigInt(const BigInt& other) :dig(other.dig) {}

BigInt& BigInt::operator=(BigInt a) {
	dig.swap(a.dig);
	return *this;
}

BigInt::BigInt(string num) {
	transform(num.rbegin(), num.rend(), back_inserter(dig), Ascii2Int());
}
BigInt& BigInt::operator +=(const BigInt& a)
{
	unsigned int maxSize;
	unsigned int num = 0;
	unsigned int carry = 0;

	
	if (dig.size()<a.dig.size()) {
		maxSize = a.dig.size();
		dig.resize(a.dig.size());
	}
	else {
		maxSize = dig.size();
	}

	for (unsigned int i = 0; i < maxSize; i++)
	{
		if (i<a.dig.size())
			num = dig[i] + a.dig[i] + carry;
		else
			num = dig[i] + carry;

		if (num >= 10)
		{
			num = num - 10;
			carry = 1;
		}
		else {
			carry = 0;
		}

		dig[i] = num;
	}
	if (carry) {
		dig.push_back(1);
	}

	return *this;
}

BigInt BigInt::operator +(const BigInt& a) const
{
	return BigInt(*this) += a;

}

std::ostream& operator <<(std::ostream& out, BigInt a)
{
	for (unsigned int i = 0; i < a.dig.size(); i++) {
		out << a.dig[i] << endl;
	}
	return out;
}

int main() {
	BigInt B1("8957");
	BigInt B2("22");
	BigInt B3;
	B3 = B1 + B2;
	cout << "B1+B2 is" << B3 << endl;
	BigInt B4;
	B4 += B1;
	B4 += B2;
	B4 += B3;
	cout << "B4 is" << B4 << endl;
	

	system("pause");
}