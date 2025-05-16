#include "drink_factory.hpp"

int main() {
    DrinkFactory df;
    auto coffee = df.make_drink("tea");
}
