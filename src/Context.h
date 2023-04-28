#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <variant>

class Context {
public:
    enum class Type { Scalar, Array, Map };

    Context() : m_type(Type::Scalar), m_scalar() {}
    explicit Context(int val) : m_type(Type::Scalar), m_scalar(val) {}
    explicit Context(double val) : m_type(Type::Scalar), m_scalar(val) {}
    explicit Context(bool val) : m_type(Type::Scalar), m_scalar(val) {}
    explicit Context(const std::string& val) : m_type(Type::Scalar), m_scalar(std::string(val)) {}
    explicit Context(const std::vector<Context>& val) : m_type(Type::Array), m_array(val) {}
    explicit Context(const std::map<std::string, Context>& val) : m_type(Type::Map), m_map(val) {}
    Context(const Context& other) = default;
    Context(Context&& other) = default;

    [[nodiscard]] Type get_type() const ;

    void set_scalar(int val);
    void set_scalar(double val);
    void set_scalar(bool val);
    void set_scalar(const std::string& val);

    [[nodiscard]] int get_int() const ;
    [[nodiscard]] double get_double() const ;
    [[nodiscard]] bool get_bool() const ;
    [[nodiscard]] std::string get_string() const ;

    [[nodiscard]] const std::vector<Context>& get_array() const ;

    [[nodiscard]] const std::map<std::string, Context>& get_map() const ;

    void add_element(const Context& context) ;

    void add_element(const std::string& key, const Context& context) ;

    [[nodiscard]] bool has_element(const std::string& key) const ;

    [[nodiscard]] const Context& get_element(const std::string& key) const ;

    Context& operator=(const Context& other);
    Context& operator=(Context&& other) noexcept ;

    void insert_element(const std::string& key, const Context& context);
    void remove_element(const std::string& key);
    void remove_element(std::size_t index);
    void move_element(const std::string& from_key, const std::string& to_key);
    void move_element(std::size_t from_index, std::size_t to_index);

private:
    Type m_type;
    std::variant<int, double, bool, std::string> m_scalar{};
    std::vector<Context> m_array;
    std::map<std::string, Context> m_map;
};
