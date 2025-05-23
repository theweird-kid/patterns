#include <cstddef>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

struct HTMLElement {
    std::string name, text;
    std::vector<HTMLElement> elements;
    const size_t indent_size = 2;

    HTMLElement() = default;
    HTMLElement(const std::string &name, const std::string &text) : name(name) , text(text) {}

    std::string str(int indent = 0) const {
        std::ostringstream oss;
        std::string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << std::endl;
        if(text.size() > 0)
            oss << std::string(indent_size*(indent+1), ' ') << text << std::endl;

        for(const auto& e: elements)
            oss << e.str(indent+1);

        oss << i << "</" << name << ">" << std::endl;
        return oss.str();
    }
};

struct HTMLBuilder {
    HTMLElement root;
    HTMLBuilder(std::string root_name) {
        root.name = root_name;
    }

    HTMLBuilder& add_child(std::string child_name, std::string child_text) {
        HTMLElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }

    std::string str() const { return root.str(); }

    operator HTMLElement() const { return root; }
};

int main() {
    HTMLBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li", "world");
    std::cout << builder.str() << std::endl;
}
