#include <iostream>
#include <sstream>
#include <vector>

/*
    Starategy Design Pattern:
        Partially specify the behaviour of the system and then augment it
*/

enum class OutputFormat
{
    markdown,
    html
};

struct ListStrategy
{
    virtual void start(std::ostringstream& oss) {}
    virtual void add_list_item(std::ostringstream& oss, const std::string& item) = 0;
    virtual void end(std::ostringstream& oss) {}
};

struct MarkdownListStrategy : ListStrategy
{
    MarkdownListStrategy() {}
    void add_list_item(std::ostringstream& oss, const std::string& item) override
    {
        oss << "* " << item << "\n";
    }
};

struct HtmlListStrategy : ListStrategy
{
    HtmlListStrategy() {}
    void add_list_item(std::ostringstream& oss, const std::string& item) override
    {
        oss << "    <li>" << item << "</li>\n";
    }

    void start(std::ostringstream& oss) override
    {
        oss << "<ul>\n";
    }

    void end(std::ostringstream& oss) override
    {
        oss << "</ul>\n";
    }
};


template <typename LS>
struct TextProcessor
{
public:

    void clear()
    {
        oss.str("");
        oss.clear();
    }

    void append_list(const std::vector<std::string>& items)
    {
        list_strategy.start(oss);
        for(auto &item: items)
        {
            list_strategy.add_list_item(oss, item);
        }
        list_strategy.end(oss);
    }

    std::string str() { return oss.str(); }

private:
    std::ostringstream oss;
    LS list_strategy;
};

int main()
{
    std::vector<std::string> items{"foo", "bar", "baz" };

    /*  Dynamic Strategy  */
    TextProcessor<MarkdownListStrategy> tpm;
    tpm.append_list(items);
    std::cout << tpm.str() << "\n";

    TextProcessor<HtmlListStrategy> tph;
    tph.append_list(items);
    std::cout << tph.str() << "\n";

    return 0;
}
