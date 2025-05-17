#include <ios>
#include <iostream>
#include "observer.hpp"
#include "observable.hpp"
#include "safe_observable.hpp"

// Using CRTP
class Person : public ThreadSafeObservable<Person>       // Observable
{
    int age_;
public:
    Person(int age) : age_(age) {}

    int get_age()
    {
        return age_;
    }

    void set_age(int age)
    {
        if(this->age_ == age) return;

        auto old_can_vote = get_can_vote();
        this->age_ = age;
        notify(*this, "age");

        if(old_can_vote != get_can_vote()) {
            notify(*this, "can_vote");
        }
    }

    bool get_can_vote() const {
        return age_ >= 18;
    }
};

struct ConsolePersonObserver : public Observer<Person>          // Observer
{
private:
    void field_changed(Person &source, const std::string &field_name) override
    {
        std::cout << "Person " << &source << " " << field_name << " has changed to ";
        if(field_name == "age") std::cout << source.get_age();
        if(field_name == "can_vote") std::cout << std::boolalpha << source.get_can_vote();
        std::cout << "\n";
    }
};

/*
--------------------------------------------------- OBSERVER PATTERN with BOOST/SIGNALS2 ----------------------------------------------------
*/
#include <boost/signals2.hpp>
template <typename T> struct Observable2
{
    boost::signals2::signal<void(T&, const std::string&)> field_changed;
};

class Person2 : public Observable2<Person2>
{
    int age_;
public:
    void set_age(int age)
    {
        if(this->age_ == age) return;
        this->age_ = age;
        field_changed(*this, "age");
    }

    int get_age() const {
        return age_;
    }
};

// --------------------------------------------------------------------------------------------------------------------------------------- //

struct TrafficAdministration : Observer<Person>
{
    void field_changed(Person &source, const std::string &field_name) override
    {
        //if(source.get_age() < )
    }
};

int main() {
    std::cout << "Observer Pattern\n";
    Person person{10};
    ConsolePersonObserver ob;
    person.subscribe(ob);

    person.set_age(13);
    person.set_age(23);
    person.unsubscribe(ob);
    person.set_age(17);

    // observer with boost
    // Person2 p2;
    // auto conn = p2.field_changed.connect(
    //     [](Person2 &p, const std::string &field_name)
    //     {
    //         std::cout << field_name << " has changed\n";
    //     }
    // );

    // p2.set_age(20);
    // conn.disconnect();
    // p2.set_age(25);

    return 0;
}
