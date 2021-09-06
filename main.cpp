#include <iostream>
#include <cmath>
#include <bitset>

/**
 * @author Xuyang Chen
 *
 * @brief
 * Write a function which, for a given unsigned integer n, returns the number
 * of ones required when writing out all numbers in base 2 between 0 and n
 *
 * For example, f(0b1000) = 12 and f(0b1111) = 32
 *
 * The function must execute in linear time proportional to the number of
 * binary digits of n
 *
 */

// TODO comments suck

using namespace std;

// unsigned type used in computations
typedef unsigned short num;
const int bits_in_num = 8 * sizeof(num);

num digits_in_binary(num number){
    return (num)(log(number) / log(2));
}

num ones(num value){
    cout << "computing for value " << bitset<bits_in_num>(value) << endl;

    // counter for final answer
    num total_times = 0;

    // the current bit is set to 1
    num place_mask = 0b1;
    // the current bit and everything to the left is set to 1
    num visited_mask = 0b1;


    for (num i = 0; i <= digits_in_binary(value); i++){
        cout << "\nCurrently looking at " << i + 1 << " place" << endl;

        // where i+1 is the place of the current digit
        // in this loop we compute the number of times that
        // the current digit is 1 over all the sequential numbers <= val

        // all the bits strictly greater than the current digit
        num super_bits = value >> (i+1);
        cout << "super bits " << bitset<bits_in_num>(super_bits) << endl;

        // multiply super_bits by the place of the current digit for
        // the times the current digit was one LESS than val
        num super_times = super_bits * place_mask;
        cout << "super times " << super_times << endl;

        total_times += super_times;

        // we will add one if the current digit is one
        num current_bit = value & place_mask;
        if(current_bit){
            total_times += 1;
            cout << "add one for current bit" << endl;
        }

        place_mask <<= 1;
        visited_mask |= place_mask;
    }

    return total_times;
}

int main() {
    num value = 8;

    std::cout <<
          "Number of ones needed to count from 0 to " << value <<
          " is " << ones(value)
              << std::endl;
    return 0;
}
