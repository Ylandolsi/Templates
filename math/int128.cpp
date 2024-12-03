
using i128 = __int128_t;
i128 abs(const i128 &x) { return x > 0 ? x : -x; }
istream &operator>>(istream &is, i128 &v) {
    string s;
    is >> s;
    v = 0;
    for(int i = 0; i < (int)s.size(); i++) {
        if(isdigit(s[i])) { v = v * 10 + s[i] - '0'; }
    }
    if(s[0] == '-') { v *= -1; }
    return is;
}
 
ostream &operator<<(ostream &os, const i128 &v) {
    if(v == 0) { return (os << "0"); }
    i128 num = v;
    if(v < 0) {
        os << '-';
        num = -num;
    }
    string s;
    for(; num > 0; num /= 10) { s.push_back((char)(num % 10) + '0'); }
    reverse(s.begin(), s.end());
    return (os << s);
}













	/// or

using  int128 =   signed __int128;
using uint128 = unsigned __int128;

namespace int128_io {

	inline auto char_to_digit(int chr) {
	    return static_cast<int>(isalpha(chr) ? 10+tolower(chr)-'a': chr-'0'); }

	inline auto digit_to_char(int digit) {
    	return static_cast<char>(digit > 9 ? 'a'+digit-10: '0'+digit); }

	template<class integer>
	inline auto to_int(const std::string &str, size_t *idx = nullptr, int base = 10) {
		size_t i = idx != nullptr ? *idx : 0;
		const auto n = str.size();
		const auto neg = str[i] == '-';
		integer num = 0;
		if (neg)
			++i;
		while (i < n)
			num *= base, num += char_to_digit(str[i++]);
		if (idx != nullptr)
			*idx = i;
		return neg ? -num : num; }

	template<class integer>
	inline auto to_string(integer num, int base = 10) {
		const auto neg = num < 0;
		std::string str;
		if (neg)
			num = -num;
		do
			str += digit_to_char(num%base), num /= base;
		while (num > 0);
		if (neg)
			str += '-';
		std::reverse(str.begin(),str.end());
		return str; }

	inline auto next_str(std::istream &stream) { std::string str; stream >> str; return str; }

	template<class integer>
	inline auto& read(std::istream &stream, integer &num) {
		num = to_int<integer>(next_str(stream));
		return stream; }

	template<class integer>
	inline auto& write(std::ostream &stream, integer num) { return stream << to_string(num); } }


inline auto& operator>>(istream &stream,  int128 &num) { return int128_io::read(stream,num); }
inline auto& operator>>(istream &stream, uint128 &num) { return int128_io::read(stream,num); }
inline auto& operator<<(ostream &stream,  int128  num) { return int128_io::write(stream,num); }
inline auto& operator<<(ostream &stream, uint128  num) { return int128_io::write(stream,num); }

inline auto uint128_max() {
	uint128 ans = 0;
    for (uint128 pow = 1; pow > 0; pow <<= 1)
		ans |= pow;
    return ans; }




