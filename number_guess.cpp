#include <iostream>
#include <random>

// Function to check if the guessed number is correct
bool is_correct(int guess, int target)
{
    return guess == target;
}


// Function to provide feedback on the guess
int provide_feedback(int guess, int target)
{
    if (guess < target)
    {
        std::cout << "Too Low." << std::endl;
        return 1;
    }
    else if (guess > target)
    {
        std::cout << "Too High." << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Correct!" << std::endl;
        return 0;
    }
}
// Main function to run the number guessing game
int main()
{
    int low = 1;
    int high = 100000;
    
    // Modern C++ random number generation
    std::random_device rd;  // Seed generator
    std::mt19937 gen(rd()); // Mersenne Twister generator
    std::uniform_int_distribution<int> dist(low, high); // Uniform distribution
    const int target_number = dist(gen); // Generate random number between low and high
    
    int user_guess = 0;
    int attempts = 0;

    std::cout << "Welcome to the Number Guessing Game!" << std::endl;
    std::cout << "I have selected a number between 1 and 100. Can you guess it?" << std::endl;
    while (!is_correct(user_guess, target_number))
    {
        std::cout << "Enter your guess: ";
        // Binary search logic for guessing
        user_guess = (low + high) / 2;
        std::cout << user_guess << std::endl;
        attempts++;

        if (!is_correct(user_guess, target_number))
        {
            if (provide_feedback(user_guess, target_number) == 1)
            {
                low = user_guess + 1;
            }
            else
            {
                high = user_guess - 1;
            }
        }

        else
        {
            std::cout << "Congratulations! You've guessed the number " << target_number << " in " << attempts << " attempts." << std::endl;
            break;
        }
    }
}