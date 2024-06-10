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

// ... rest of the code remains the same ...


BigInteger::BigInteger(std::string num)
{
	this->negative = (num[0] == '-') ? true : false;
	if (num[0] == '+' || num[0] == '-') 
		num.erase(num.begin());
	removeZeros(num);
	this->value = num;
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
	return BigInteger();
}

BigInteger BigInteger::operator / (const BigInteger& other) const
{
	return BigInteger();
}

BigInteger BigInteger::operator % (const BigInteger& other) const
{
	return BigInteger();
}

BigInteger BigInteger::operator *= (const BigInteger& other) const
{
	return BigInteger();
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
