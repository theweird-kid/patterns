#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <boost/lexical_cast.hpp>

class Database
{
public:
    virtual int get_population(const std::string& name) = 0;
};

class SingletonDatabase : public Database
{
private:
    SingletonDatabase()
    {
        std::cout << "Initializing the Database\n";
        std::ifstream ifs("capitals.txt");
        std::string city, population;
        while(getline(ifs, city)) {
            getline(ifs, population);
            capitals[city] = boost::lexical_cast<int>(population);
        }
    }

    std::map<std::string, int> capitals;
public:
    SingletonDatabase(SingletonDatabase const&) = delete;
    SingletonDatabase& operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& getInstance() {
        // Meyer's Singleton : Guaranted to be thread safe from C++11.
        static SingletonDatabase db;
        return db;
    }

    int get_population(const std::string& name) override {
        return capitals[name];
    }
};

class DummyDatabse : public Database
{
    std::map<std::string, int> data_;
public:
    DummyDatabse() {
        data_["alpha"] = 1;
        data_["beta"] = 2;
        data_["gamma"] = 3;
    }

    int get_population(const std::string& name) override {
        return 0;
    }
};

// Ends up being integration test instead of unit test as it is heavily dependent on SingletonDatabse instance
struct SingletonRecordFinder
{
    int total_population(std::vector<std::string> &names) {
        int result{0};
        for(auto& name: names) {
            result += SingletonDatabase::getInstance().get_population(name);
        }
        return result;
    }
};

// Have DB instance through dependency Injection            # Can be used for unit tests
struct ConfigurableRecordFinder
{
    Database& db_;
    ConfigurableRecordFinder(Database &db) : db_(db) {}

    int total_population(std::vector<std::string> &names) {
        int result{0};
        for(auto& name: names) {
            result += db_.get_population(name);
        }
        return result;
    }
};


int main() {

}
