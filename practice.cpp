#include <iostream>
#include <cmath>
#include <vector>

int square(int x)
{
    return x * x;
}

bool is_even(int x)
{
    return x % 2 == 0;
}

int find_max(int a, int b, int c)
{
    int max_value = a;
    if (b > max_value)
    {
        max_value = b;
    }
    if (c > max_value)
    {
        max_value = c;
    }
    return max_value;
}

int count_digits(int number)
{
    if (number == 0) return 1;
    int digit = 0;
    while (number >= 1)
    {
        number = number / 10;
        digit++;
    }
    return digit;
}

int reverse_number(int number)
{   
    int digits = count_digits(number);
    int original = number;
    int reversed = 0;
    for(int i = 0; i < digits; i++)
    {
        int digit = original % 10;
        reversed += digit * pow(10, digits - 1 - i);
        original = original / 10;
    }
    return reversed;
}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true; // 2 and 3 are prime
    if (n % 2 == 0 || n % 3 == 0) return false; // Divisible by 2 or 3

    for (int i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int countWords(std::string str)
{
    int count = 0;
    bool inWord = false;
    for (char c : str)
    {
        if (std::isspace(c))
        {
            if (inWord)
            {
                count++;
                inWord = false;
            }
        }
        else
        {
            inWord = true;
        }
    }
    if (inWord) count++;
    return count;
}



int main() {
    std::string text = "loerem ipsum, ehils world! to tjs a lcome to C++ prming.";
    int wordCount = countWords(text);
    std::cout << "Number of words: " << wordCount << std::endl;
    return 0;
}
