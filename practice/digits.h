#ifndef __DIGITS_H
#define __DIGITS_H

namespace Digits {

    int numOfDigits(long long num) {
        int count = {};
        for (; num; num /= 10)
            ++count;
        return count;
    }
    int getReversed(long long num) {
        long long reversed{}, digit;
        for (; num; num /= 10) {
            digit = num % 10;
            reversed = ((reversed * 10) + digit);
        }
        return reversed;
    }
    bool isPalindrome(long long num) {
        return (num == getReversed(num));
    }
    long long intPow(long long x, long long n) {
        if (n) {
            long long res = intPow(x, n/2);
            return (n & 1) ? (x * res * res) : (res * res);
        }
        return 1;
    }
    bool isArmstrong(long long num) {
        long long temp{num};
        int sum{}, digit, ndigits{numOfDigits(num)};
        for (; temp; temp /= 10) {
            digit = temp % 10;
            sum += intPow(digit, ndigits);
        }
        return (sum == num);
    }

}

#endif  // __DIGITS_H