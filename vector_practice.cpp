#include <iostream>
#include <vector>

std::vector<int> vectorOps()
{
    std::vector<int> numbers = {10, 20, 20, 40, 50};

    return numbers;
}

bool removeValue(std::vector<int>& numbers, int value)
{
    for(int i = 0; i < numbers.size(); i++)
    {
        if(numbers[i] == value)
        {
            numbers.erase(numbers.begin() + i );
            return true;
        }
    }

    return false;
}

int main()
{
    std::vector<int> numbers = vectorOps();

    if(removeValue(numbers, 30))
    {
        std::cout << "30 was removed" << std::endl;
    }
    else 
    {
        std::cout << "value not found" << std::endl;
    }

    return 0;
}