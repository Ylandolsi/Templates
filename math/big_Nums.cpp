
	
	// multiply a string number with a char digit
    string multiplyDigit(string& s, char c, int pad) {
        int i = size(s)-1, carry = 0, digit1 = c-'0', digit2, res;
		// the string is formed in reverse manner & then reversed at end
		// This is because it's O(1) to push at the end instead of at the start
        string ans = string(pad, '0');
        while(i >= 0) {
            digit2 = s[i--]-'0';                    // get digit of num1 to be multiplied with digit1
            res = digit1 * digit2 + carry;          // multiplication of digits + carry from previous
            carry = res / 10;                       // update carry
            ans += res%10+'0';                      // only consider last digit & add it to result
        }
        if(carry) ans += carry+'0';                 // if there's leftover carry at end after multiplying all digits
        reverse(begin(ans), end(ans));              // reverse back to get correct result
        return ans;
    }
	
	// adds two string numbers - https://leetcode.com/problems/add-strings/
    string addStrings(string &A, string& B) {
        if(size(A) < size(B)) return addStrings(B, A);   // we assume A is the bigger string
        int i = size(A)-1, j = size(B)-1, carry = 0, digit1, digit2, res;
        string ans = "";
        while(i >= 0) {
            digit1 = A[i--]-'0', digit2 = j >= 0 ? (B[j--]-'0') : 0;  // get digits from both numbers
            res = digit1 + digit2 + carry;               // add both digit and carry from previous
            carry = res / 10;                            // update carry
            ans += res%10+'0';                           // only consider last digit & add it to result
        }
        if(carry) ans += carry+'0';                      // if there's leftover carry at end after multiplying all digits
        reverse(begin(ans), end(ans));                   // We formed in reverse order. Reverse it back to get correct result
        return ans;
    }

    string multiply(string& A, string& B) {
        if(A == "0" || B == "0") return "0";                  // if either is 0, final result will be 0
		if(size(A) < size(B)) return multiply (B, A);
        string ans = "";
        for(int j = size(B)-1, pad = 0; j >= 0; j--) {
            auto res = multiplyDigit(A, B[j], pad++);         // multiply each digit of B with A considering proper padding of 0 at end
            ans = addStrings(ans, res);                       // keep adding intermediate result to final result
        }
        return ans;
    }
    string subtract(const string& n1, const string& n2) {
    bool isNegative = false;
    string num1 = n1, num2 = n2;
    
    if (num1.length() < num2.length() || (num1.length() == num2.length() && num1 < num2)) {
        isNegative = true;
        swap(num1, num2);
    }

    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

    vector<int> sub;
    int carry = 0;

    for (size_t i = 0; i < num1.length(); ++i) {
        int a = num1[i] - '0';
        int b = (i < num2.length()) ? num2[i] - '0' : 0;
        int diff = a - b + carry;

        if (diff < 0) {
            carry = -1;
            diff += 10;
        } else {
            carry = 0;
        }

        sub.push_back(diff);
    }

    while (sub.size() > 1 && sub.back() == 0) {
        sub.pop_back();
    }

    string result;
    for (auto it = sub.rbegin(); it != sub.rend(); ++it) {
        result += (*it + '0');
    }

    if (isNegative) {
        result = "-" + result;
    }

    return result;
}
bool isSmaller(const string& str1, const string& str2) {
    if (str1.length() < str2.length()) return true;
    if (str1.length() > str2.length()) return false;
    return str1 < str2;
}

string divideStrings(const string& dividend, const string& divisor) {
    if (divisor == "0") {
        throw invalid_argument("Division by zero is not allowed.");
    }
    if (isSmaller(dividend, divisor)) {
        return "0"; // If the dividend is smaller than the divisor, result is 0
    }

    string quotient;
    string current = "";

    for (char digit : dividend) {
        current += digit;

        // Remove leading zeros in current if any
        while (current.length() > 1 && current[0] == '0') {
            current.erase(current.begin());
        }

        int count = 0;
        while (!isSmaller(current, divisor)) {
            current = subtract(current, divisor);
            count++;
        }

        quotient += (count + '0');
    }

    while (quotient.length() > 1 && quotient[0] == '0') {
        quotient.erase(quotient.begin());
    }

    return quotient;
}