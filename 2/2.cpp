#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <tuple>
#include <utility>

struct TPrettyPrinter {
private:
    std::stringstream stream;

public:
    std::string Str() const {
        return stream.str();
    }

    template<typename T>
    TPrettyPrinter& Format(const T& value) {
        stream << value;
        return *this;
    }

    TPrettyPrinter& Format(const std::string& value) {
        stream << value;
        return *this;
    }

    TPrettyPrinter& Format(const char* value) {
        stream << value;
        return *this;
    }

    template<typename T1, typename T2>
    TPrettyPrinter& Format(const std::pair<T1, T2>& p) {
        stream << "(";
        Format(p.first);
        stream << ", ";
        Format(p.second);
        stream << ")";
        return *this;
    }

    template<typename T>
    TPrettyPrinter& Format(const std::vector<T>& v) {
        stream << "[";
        for (size_t i = 0; i < v.size(); ++i) {
            if (i > 0) {
                stream << ", ";
            }
            Format(v[i]);
        }
        stream << "]";
        return *this;
    }

    template<typename T>
    TPrettyPrinter& Format(const std::set<T>& s) {
        stream << "{";
        auto it = s.begin();
        for (size_t i = 0; it != s.end(); ++i, ++it) {
            if (i > 0) {
                stream << ", ";
            }
            Format(*it);
        }
        stream << "}";
        return *this;
    }

    template<typename... Args>
    TPrettyPrinter& Format(const std::tuple<Args...>& t) {
        stream << "(";
        FormatTuple(t, std::index_sequence_for<Args...>{});
        stream << ")";
        return *this;
    }

private:
    template<typename Tuple, std::size_t... Is>
    void FormatTuple(const Tuple& t, std::index_sequence<Is...>) {
        ((Format(std::get<Is>(t)), (Is + 1 < sizeof...(Is) ? Format(", ") : *this)), ...);
    }
};

template<typename T>
std::string Format(const T& t) {
    return TPrettyPrinter().Format(t).Str();
}

int main() {
    std::tuple<std::string, int, int> t = {"xyz", 1, 2};
    std::vector<std::pair<int, int>> v = {{1, 4}, {5, 6}};
    std::string s1 = TPrettyPrinter().Format("vector: ").Format(v).Str();
    std::cout << s1 << std::endl;  // "vector: [(1, 4), (5, 6)]"
    std::string s2 = TPrettyPrinter().Format(t).Format(" ! ").Format(0).Str();
    std::cout << s2 << std::endl;  // "(xyz, 1, 2) ! 0"
    return 0;
}

