// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <cstdint>
#include <iostream>

enum class Steps : uint8_t {
  invalid, empty, fill, heat,
  wash, rinse, spin, dry, complete
};

constexpr unsigned colour_wash_size = 10;

// Array of Step objects
Steps colour_wash[colour_wash_size] = {
    Steps::fill,
    Steps::heat,
    Steps::wash,
    Steps::empty,
    Steps::fill,
    Steps::rinse,
    Steps::empty,
    Steps::spin,
    Steps::dry,
    Steps::complete,
};

int main()
{
  for (unsigned i {}; i < colour_wash_size; ++i) {
    // std::cout << static_cast<unsigned>(colour_wash[i]) << ' ';  // using C+14 cast
    std::cout << unsigned(colour_wash[i]) << ' ';                  // using C+17 cast
  }
  std::cout << '\n';
}
