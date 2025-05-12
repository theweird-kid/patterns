#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

// ------------------------------ S => Single Responsibility Principle ------------------------------------------------

// Is responsible for maintaining the entries
struct Journal
{
    std::string title;
    std::vector<std::string> entries;
    Journal(const std::string& title) : title(title) {}

    void add_entry(const std::string& entry)
    {
        static int count = 1;
        entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + entry);
    }

};

// Is responsible for Making the Journal Persistant, if some day we want to use a DB instead of file
// we just have to modify only this class;
struct PersistanceManager
{
    static void save(const Journal& journal, const std::string& filename)
    {
        std::ofstream ofs(filename);
        for(auto &e: journal.entries)
            ofs << e << std::endl;
    }
};

// ------------------------------------------- O => Open - Closed Principle --------------------------------------------------

enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product
{
    std::string name;
    Color color;
    Size size;
};

struct ProductFilter
{
    std::vector<Product*> by_color(std::vector<Product*> items, Color color)
    {
        std::vector<Product*> result;
        for(auto &item: items) {
            if(item->color == color)
                result.push_back(item);
        }
        return result;
    }
};

// forward declare
template <typename T> struct AndSpecification;
// Interface to check for certain type of specifications (Can be extended by inheritance)
template <typename T> struct Specification
{
    virtual bool is_satisfied(T *item) = 0;

    AndSpecification<T> operator &&(Specification<T>&& other) { return AndSpecification<T>(*this, other); }
};
// Interface for filter
template <typename T> struct Filter
{
    virtual std::vector<T*> filter(const std::vector<T*>& items, Specification<T>& spec) = 0;
};

// NOTE: Both filter and specification can be used for types other than product

// Implementing the Interface
struct BetterFilter : public Filter<Product>
{
    std::vector<Product*> filter(const std::vector<Product*>& items, Specification<Product>& spec) override
    {
        std::vector<Product*> result;
        for(auto &item: items){
            if(spec.is_satisfied(item))
                result.push_back(item);
        }
        return result;
    }
};

struct ColorSpecification : public Specification<Product>
{
    Color color;
    ColorSpecification(const Color col): color(col) {}
    bool is_satisfied(Product* prod) override { return prod->color == color; }
};

struct SizeSpecification : public Specification<Product>
{
    Size size;
    explicit SizeSpecification(const Size size) : size(size) {}
    bool is_satisfied(Product* prod) override { return prod->size == size; }
};

template <typename T> struct AndSpecification : Specification<T>
{
    Specification<T>& first;
    Specification<T>& second;

    AndSpecification(Specification<T>& first, Specification<T>& second)
        : first(first), second(second)
    {}

    bool is_satisfied(T* item) override { return first.is_satisfied(item) && second.is_satisfied(item); }
};

//----------------------------------------------


int main() {

    // Single Responsibility
    // Journal journal{"Dear Diary"};
    // journal.add_entry("I ate a bug");
    // journal.add_entry("I cried today");

    // PersistanceManager pm;
    // pm.save(journal, "Diary.txt");



    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::red, Size::large};

    std::vector<Product*> items { &apple, &tree, &house };

    // ProductFilter pf;
    // auto green_things = pf.by_color(items, Color::green);

    BetterFilter bf;
    ColorSpecification spec(Color::green);

    auto green_things = bf.filter(items, spec);
    for(auto &gt: green_things)
        std::cout << gt->name << std::endl;

    SizeSpecification spec2(Size::large);
    AndSpecification<Product> and_spec(spec, spec2);
    auto compact_spec = ColorSpecification(Color::green) && SizeSpecification(Size::large);

    auto green_large_things = bf.filter(items, compact_spec);
    for(auto &glt: green_large_things)
        std::cout << glt->name << std::endl;

    return 0;
}
