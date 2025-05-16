#pragma once
#include <string>
#include "hot_drink.hpp"
#include "hot_drink_factory.hpp"
#include <functional>
#include <map>
#include <functional>
#include <memory>

class DrinkFactory
{
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;
public:
    DrinkFactory()
    {
        hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
        hot_factories["tea"] = std::make_unique<TeaFactory>();
    }

    std::unique_ptr<HotDrink> make_drink(const std::string& name) {
        auto drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }
};

// Functional Abstract Factory
class DrinkWithVolumeFactory
{
    std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;
public:
    DrinkWithVolumeFactory()
    {
        factories["tea"] = [](){
            auto tea = std::make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };
    }

    std::unique_ptr<HotDrink> make_drink(const std::string& name)
    {
        return factories[name]();
    }
};
