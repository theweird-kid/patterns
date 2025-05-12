#include <iostream>

// Interface Segregation Principle

struct Document;

// Problem: with this approach any client that implements this interface must implement all 3 methods
// even though we need only 1 or 2
struct IMachine
{
    virtual void print(Document& doc) = 0;
    virtual void scan(Document& doc) = 0;
    virtual void fax(Document& doc) = 0;
};

// Can be resolved with defining multiple interfaces for different tasks
struct IPrinter
{
    virtual void print(Document& doc) = 0;
};
struct IScanner
{
    virtual void scan(Document& doc) = 0;
};
struct IFax
{
    virtual void fax(Document& doc) = 0;
};
// Now if we need a print functionality only
struct Printer : IPrinter {
    void print(Document& doc) override {}
};
// If we want a machine with 2 features only
struct IMachine2 : IPrinter, IScanner {};
struct Machine : IMachine2 {
    IPrinter& printer;
    IScanner& scanner;

    Machine(IPrinter& printer, IScanner& scanner) : printer(printer), scanner(scanner) {}

    void print(Document& doc) override {}
    void scan(Document& doc) override {}
};

int main() {
    std::cout << "4. Interface Segregation Principle\n";



    return 0;
}
