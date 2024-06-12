#ifndef BIG_INTEGER_HPP
#define BIG_INTEGER_HPP

#include <string>
#include <iostream>

class BigInteger {
	std::string value;
	bool negative;

	void removeZeros(std::string& value) const;
	std::string add(std::string num1, std::string num2) const;
	std::string subtract(std::string num1, std::string num2) const;
	std::string multiply(std::string num1, std::string num2) const;
	std::string divide(std::string num1, std::string num2) const;
	std::string modulus(std::string num1, std::string num2) const;
	int compare(std::string num1, std::string num2) const;

public:
	
	BigInteger() : value("0"), negative(false) {}
	BigInteger(int num) : BigInteger(std::to_string(num)) {
		negative = (num < 0) ? true : false;
	}
	BigInteger(long long num) : BigInteger(std::to_string(num)) {
		negative = (num < 0) ? true : false;
	}
	BigInteger(std::string num);

	std::string getValue() const {
		if (value == "0")
			return value;
		return (negative) ? "-" + value : value; 
	}

	BigInteger operator + (const BigInteger& other) const;
	BigInteger operator - (const BigInteger& other) const;
	BigInteger operator * (const BigInteger& other) const;
	BigInteger operator / (const BigInteger& other) const;
	BigInteger operator % (const BigInteger& other) const;
	BigInteger operator *= (const BigInteger& other);

	bool operator == (const BigInteger& other) const;
	bool operator >= (const BigInteger& other) const;

	friend std::ostream& operator << (std::ostream& os, const BigInteger& obj);
	friend std::istream& operator >> (std::istream& is, BigInteger& obj);

};

#endif
