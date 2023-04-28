#include "../src/Context.h"
#include <iostream>
#include <cassert>

int main() {
    std::string str = "hello";

    // test constructors

    Context c1;
    assert(c1.get_type() == Context::Type::Scalar);

    Context c2(123);
    assert(c2.get_type() == Context::Type::Scalar);
    assert(c2.get_int() == 123);

    Context c3(3.14);
    assert(c3.get_type() == Context::Type::Scalar);
    assert(c3.get_double() == 3.14);

    Context c4(true);
    assert(c4.get_type() == Context::Type::Scalar);
    assert(c4.get_bool() == true);

    Context c5(str);
    assert(c5.get_type() == Context::Type::Scalar);
    assert(c5.get_string() == "hello");

    std::cout << "Test constructors - successfully!" << std::endl ;

    // test methods
    c1.set_scalar(123);
    assert(c1.get_int() == 123);


    c1.set_scalar(3.14);
    assert(c1.get_double() == 3.14);


    c1.set_scalar(true);
    assert(c1.get_bool() == true);


    c1.set_scalar(str);
    assert(c1.get_string() == str);


    c1.add_element(Context(1));
    assert(c1.get_type() == Context::Type::Array);
    assert(c1.get_array().size() == 1);
    assert(c1.get_array()[0].get_int() == 1);

    str = "a";
    c2.add_element(str, Context(2));
    assert(c2.get_type() == Context::Type::Map);
    assert(c2.get_map().size() == 1);
    assert(c2.get_map().count(str) == 1);
    assert(c2.get_map().at(str).get_int() == 2);

    assert(c2.has_element("a"));
    assert(!c2.has_element("b"));

    assert(c2.get_element("a").get_int() == 2);


    Context x3(c5);
    assert(x3.get_type() == Context::Type::Scalar);
    assert(x3.get_string() == "hello");

    str = "Vasya";
    Context context;
    context.add_element("name", Context(str));
    context.add_element("age", Context(18));
    context.add_element("is_student", Context(true));
    context.add_element("grades", Context({85, 90, 95}));

    Context copy_context = context;

    Context moved_context = std::move(context);

    context.insert_element("email", Context("yandex.com"));
    assert(context.has_element("email"));

    context.remove_element("grades");
    assert(!context.has_element("grades"));

    Context c6;
    c6.add_element(Context(1));
    c6.add_element(Context(2));
    c6.add_element(Context(3));
    c6.move_element(0, 3);
   /* for(auto i : c6.get_array()){
        std::cout << i.get_int() << ' ';
    }*/

    std::cout<< std::endl << "Test methods - successfully!" << std::endl;
    std::cout << "Test Context class - successfully!" << std::endl;
    return 0;
}
