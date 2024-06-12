#include "BigInteger.hpp"

void BigInteger::removeZeros(std::string& value) const
{
	value.erase(0, std::min(value.find_first_not_of('0'), value.size() - 1));
}

std::string BigInteger::add(std::string num1, std::string num2) const
{
	std::string result;
	result.reserve(std::max(num1.size(), num2.size()) + 1);

	int cur_num1 = (int)num1.length() - 1, cur_num2 = (int)num2.length() - 1;
	int carry = 0;
	while (cur_num1 >= 0 || cur_num2 >= 0 || carry) {
		int cur_sum = carry;
		if (cur_num1 >= 0) cur_sum += (num1[cur_num1--] - '0');
		if (cur_num2 >= 0) cur_sum += (num2[cur_num2--] - '0');
		result.push_back((cur_sum % 10) + '0');
		carry = (cur_sum / 10);
	}

	std::reverse(result.begin(), result.end());

	return result;
}

std::string BigInteger::subtract(std::string num1, std::string num2) const
{
	std::string result;
	result.reserve(num1.size());

	int cur_a = (int)num1.length() - 1, cur_b = (int)num2.length() - 1;
	while (cur_a >= 0 && cur_b >= 0) {
		if (num1[cur_a] >= num2[cur_b]) {
			result.push_back(((num1[cur_a] - '0') - (num2[cur_b] - '0')) + '0');
			--cur_a;
			--cur_b;
			continue;
		}
		int temp = cur_a;
		while (temp--) {
			if (num1[temp] == '0') num1[temp] = '9';
			else {
				num1[temp]--;
				break;
			}
		}
		int y = ((num1[cur_a]) - '0') + 10;
		result.push_back((y - (num2[cur_b] - '0')) + '0');
		--cur_a;
		--cur_b;
	}
	while (cur_a >= 0) result.push_back(num1[cur_a--]);
	std::reverse(result.begin(), result.end());
	removeZeros(result);
	return result;
}

std::string BigInteger::multiply(std::string num1, std::string num2) const
{
	int len1 = (int)num1.size();
	int len2 = (int)num2.size();
	if (len1 == 0 || len2 == 0)
		return "0";

	std::string result(len1 + len2, '0');

	for (int i = len1 - 1; i >= 0; i--)
	{
		for (int j = len2 - 1; j >= 0; j--)
		{
			int mul = (num1[i] - '0') * (num2[j] - '0');
			int p1 = i + j, p2 = i + j + 1;
			int sum = mul + (result[p2] - '0');

			result[p1] += sum / 10;
			result[p2] = (sum % 10) + '0';
		}
	}

	size_t startpos = result.find_first_not_of("0");
	if (std::string::npos != startpos) {
		return result.substr(startpos);
	}
	return "0";
}

std::string BigInteger::divide(std::string num1, std::string num2) const
{
	int len1 = (int)num1.size();
	int len2 = (int)num2.size();
	if (len1 < len2 || len2 == 0)
		return "0";
	if (len1 == len2)
		return (compare(num1, num2) < 0) ? "0" : "1";

	std::string result;
	std::string dividend = num1.substr(0, len2);
	int idx = len2;

	while (idx <= len1) {
		int count = 0;
		while (compare(dividend, num2) >= 0) {
			dividend = subtract(dividend, num2);
			count++;
		}
		result.push_back(count + '0');

		if (idx < len1)
			dividend += num1[idx];
		idx++;
	}

	removeZeros(result);
	return result;
}

std::string BigInteger::modulus(std::string num1, std::string num2) const
{
	std::string quotient = divide(num1, num2);
	std::string product = multiply(quotient, num2);
	std::string remainder = subtract(num1, product);
	return remainder;
}

BigInteger::BigInteger(std::string num)
{
	this->negative = (num[0] == '-') ? true : false;
	if (num[0] == '+' || num[0] == '-') 
		num.erase(num.begin());
	removeZeros(num);
	this->value = num;
}

int BigInteger::compare(std::string num1, std::string num2) const
{
	if (num1.size() != num2.size())
		return num1.size() > num2.size() ? 1 : -1;

	for (int i = 0; i < num1.size(); i++)
		if (num1[i] != num2[i])
			return num1[i] > num2[i] ? 1 : -1;

	return 0; // num1 and num2 are equal
}

BigInteger BigInteger::operator + (const BigInteger& other) const
{
	BigInteger result;

	// If both numbers are positive or negative, add them
	if (this->negative == other.negative) {
		result.value = add(this->value, other.value);
		result.negative = this->negative;
	}
	else {
		// If the numbers have different signs, subtract them
		if (*this >= other) {
			result.value = subtract(this->value, other.value);
			result.negative = this->negative;
		}
		else {
			result.value = subtract(other.value, this->value);
			result.negative = other.negative;
		}
	}
	return result;
}

BigInteger BigInteger::operator - (const BigInteger& other) const
{
	BigInteger result;

	// If both numbers are positive or negative, subtract them
	if (this->negative == other.negative) {
		if (*this >= other) {
			result.value = subtract(this->value, other.value);
			result.negative = this->negative;
		}
		else {
			result.value = subtract(other.value, this->value);
			result.negative = !this->negative;
		}
	}
	else {
		// If the numbers have different signs, add them
		result.value = add(this->value, other.value);
		result.negative = this->negative;
	}

	return result;
}

BigInteger BigInteger::operator * (const BigInteger& other) const
{
	BigInteger result;
	result.value = multiply(this->value, other.value);
	result.negative = (this->negative != other.negative);
	return result;
}

BigInteger BigInteger::operator / (const BigInteger& other) const
{
	if (other.value == "0")
		throw std::invalid_argument("Division by zero is undefined.");

	BigInteger result;
	result.value = divide(this->value, other.value);
	result.negative = (this->negative != other.negative);
	return result;
}

BigInteger BigInteger::operator % (const BigInteger& other) const
{
	if (other.value == "0")
		throw std::invalid_argument("Division by zero is undefined.");

	BigInteger result;
	result.value = modulus(this->value, other.value);
	result.negative = this->negative;
	return result;
}

BigInteger BigInteger::operator *= (const BigInteger& other)
{
	this->value = multiply(this->value, other.value);
	this->negative = (this->negative != other.negative);
	return *this;
}

bool BigInteger::operator == (const BigInteger& other) const
{
	return this->value == other.value && this->negative == other.negative;
}

bool BigInteger::operator >= (const BigInteger& other) const
{
	// If this number is positive and the other is negative, return true
	if (!this->negative && other.negative) 
		return true;

	// If this number is negative and the other is positive, return false
	if (this->negative && !other.negative) 
		return false;

	if (!this->negative) 
		return	this->value.length() > other.value.length() || 
				(this->value.length() == other.value.length() && 
				this->value >= other.value);

	return	this->value.length() < other.value.length() || 
			(this->value.length() == other.value.length() && 
			this->value <= other.value);
}

std::ostream& operator << (std::ostream& os, const BigInteger& obj)
{
	// Print the value of the BigInteger
	os << (obj.negative ? "-" : "") << obj.value;
	return os;
}

std::istream& operator >> (std::istream& is, BigInteger& obj)
{
	// Read a string from the input stream and construct a BigInteger from it
	std::string str;
	is >> str;
	obj = BigInteger(str);
	return is;
}
