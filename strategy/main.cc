#include <iostream>
#include <memory>
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
        list_strategy->start(oss);
        for(auto &item: items)
        {
            list_strategy->add_list_item(oss, item);
        }
        list_strategy->end(oss);
    }

    void set_output_format(const OutputFormat& format)
    {
        switch (format)
        {
        case OutputFormat::markdown:
            list_strategy = std::make_unique<MarkdownListStrategy>();
            break;
        case OutputFormat::html:
            list_strategy = std::make_unique<HtmlListStrategy>();
            break;
        }
    }

    std::string str() { return oss.str(); }

private:
    std::ostringstream oss;
    std::unique_ptr<ListStrategy> list_strategy;
};

int main()
{
    std::cout << "Strategy Design Pattern\n";

    std::vector<std::string> items{"foo", "bar", "baz" };

    /*  Dynamic Strategy  */
    TextProcessor tp;
    tp.set_output_format(OutputFormat::markdown);
    tp.append_list(items);
    std::cout << tp.str() << "\n";

    tp.clear();
    tp.set_output_format(OutputFormat::html);
    tp.append_list(items);
    std::cout << tp.str() << "\n";

    return 0;
}
