#include <iostream>
#include <vector>
/*
    Dependency Inversion:
    A: High-level modules should not depend on low-level modules. Both should depend
       on abstractions.
    B: Abstractions should not depend on details. Details should depend on abstractions
*/

enum class Relationship
{
    parent,
    child,
    sibling
};

struct Person
{
    std::string name;
};

// Fix
struct RelationshipBrowser
{
    virtual std::vector<Person> find_all_children_of(const std::string& parent) = 0;
};

struct Relationships : public RelationshipBrowser    // low-level Module
{
    std::vector< std::tuple<Person, Relationship, Person> > relations;

    void add_parent_and_child(const Person& parent, const Person& child) {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }

    std::vector<Person> find_all_children_of(const std::string& parent) override {
        std::vector<Person> result;
        for(auto &[first, rel, second]: relations)
        {
            if(first.name == parent && rel == Relationship::parent) {
                result.push_back(second);
            }
        }
        return result;
    }
};


struct Research     // high-level
{
    // Strictly dependent on low-level module Relationships and it's internal structure that utilizes a vector of tuples
    // BAD PRACTICE: What if we change the impl of low-level module

    // Research(Relationships& relationships)
    // {
    //     auto& relations = relationships.relations;
    //     for(auto &&[first, rel, second]: relations)
    //     {
    //         if(first.name == "John" && rel == Relationship::parent) {
    //             std::cout << first.name << " has a child " << second.name << std::endl;
    //         }
    //     }
    // }

    // FIXED
    Research(RelationshipBrowser& browser)
    {
        for(auto &child: browser.find_all_children_of("John")) {
            std::cout << "John has a child named " << child.name << std::endl;
        }
    }
};


int main() {
    std::cout << "5. Dependency Inversion\n";

    Person parent{"John"};
    Person child1{"Mathew"}, child2{"Chris"};

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    Research _(relationships);

    return 0;
}
