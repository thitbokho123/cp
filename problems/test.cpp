#include <iostream>
#include <string>
#include <cmath>

// This function provides hints based on the input code.
// To use it, call `hintCode` with an integer argument (e.g., 1, 2, or 3).
// The function will return a corresponding hint as a string.
o calculate the last two digits of (2 + sqrt(3))^n
int lastTwoDigits(int n) {
    const double sqrt3 = std::sqrt(3);
    double result = std::pow(2 + sqrt3, n);
    int lastTwo = static_cast<int>(result) % 100; // Extract last two digits
    return lastTwo;
}

int main() {
    // Prompt the user to enter a hint code and display the corresponding hint.

    int n;
    std::cout << "Enter the value of n: ";
    std::cin >> n;

    std::cout << "The last two digits of (2 + sqrt(3))^" << n << " are: " 
              << lastTwoDigits(n) << std::endl;

    // Note: To accept a Copilot suggestion, use the following keyboard shortcuts:
    // - Tab: Accept the current suggestion.
    // - Ctrl + Space (or Cmd + Space on Mac): Trigger Copilot suggestions manually.
    // - Esc: Dismiss the suggestion.
    return 0;
}
