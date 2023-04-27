#include "Context.h"

void Context::set_scalar(int val) { m_type = Type::Scalar; m_scalar = val; }

Context::Type Context::get_type() const { return m_type; }

void Context::set_scalar(double val) { m_type = Type::Scalar; m_scalar = val; }

void Context::set_scalar(bool val) { m_type = Type::Scalar; m_scalar = val; }

void Context::set_scalar(const std::string &val) { m_type = Type::Scalar; m_scalar = val; }

int Context::get_int() const { return std::get<int>(m_scalar); }

double Context::get_double() const { return std::get<double>(m_scalar); }

bool Context::get_bool() const { return std::get<bool>(m_scalar); }

std::string Context::get_string() const {return std::get<std::string>(m_scalar);}

const std::vector<Context> &Context::get_array() const {
    if (m_type != Type::Array) {
        throw std::logic_error("Context is not an array");
    }
    return m_array;
}

const std::map<std::string, Context> &Context::get_map() const {
    if (m_type != Type::Map) {
        throw std::logic_error("Context is not a map");
    }
    return m_map;
}

void Context::add_element(const Context &context) {
    if (m_type == Type::Scalar) {
        m_type = Type::Array;
    }
    m_array.push_back(context);
}

void Context::add_element(const std::string &key, const Context &context) {
    if (m_type == Type::Scalar) {
        m_type = Type::Map;
    }
    else if(m_type == Type::Array){
        throw std::logic_error("Context cannot be a map because it is already an array");
    }
    m_map[key] = context;

}

bool Context::has_element(const std::string &key) const {
    if (m_type != Type::Map) {
        return false;
    }
    return m_map.find(key) != m_map.end();
}

const Context &Context::get_element(const std::string &key) const {
    if (m_type != Type::Map) {
        throw std::logic_error("Context is not a map");
    }
    auto it = m_map.find(key);
    if (it == m_map.end()) {
        throw std::out_of_range("Key not found in map");
    }
    return it->second;
}
