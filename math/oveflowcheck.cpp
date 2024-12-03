bool isAdditionOverflow(long long a, long long b) {
    // Check for overflow when adding a and b
    if (a > 0 && b > LLONG_MAX - a) {
        // Overflow occurred
        return true;
    }
    if (a < 0 && b < LLONG_MIN - a) {
        // Underflow occurred
        return true;
    }
    // No overflow
    return false;
}
 
bool isMultiplicationOverflow(long long a, long long b) {
    // Check for overflow when multiplying a and b
    if (a > 0 && b > 0 && a > LLONG_MAX / b) {
        // Overflow occurred
        return true;
    }
    if (a > 0 && b < 0 && b < LLONG_MIN / a) {
        // Underflow occurred
        return true;
    }
    if (a < 0 && b > 0 && a < LLONG_MIN / b) {
        // Underflow occurred
        return true;
    }
    if (a < 0 && b < 0 && a < LLONG_MAX / b) {
        // Overflow occurred
        return true;
    }
    // No overflow
    return false;
}