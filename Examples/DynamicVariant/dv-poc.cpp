/*
 ==============================================================================
 Dynamic Variant Example - A "Bare Bones Python-Inspired Object System"
 ==============================================================================
 Well, the title is a blatant lie or rather describes into what this might be
 turned one day ... if Python didn't already exist or if you want a much more
 dynamic object system in C++ (and Objective C++ didn't already exist)

 Right now it's not more than "a proof of concept" and demonstrates what can
 be done with a Boost.Variant some more C++ standard containers and C++11 
 std::function in the spirit of the GoF Composite Pattern but without explicit
 use of base classes, inheritance, and virtual member functions.

 If you want to march on from here, sorry, you are on your own for the moment
 ... (until I find the time to add in more comments -- martin [at] tbfe.de).
*/

#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <iostream>
#include <sstream>
#include <boost/variant.hpp>

template<typename... Ts>
class DynamicVariant;

template<typename... Ts>
using DynamicCallable = std::function<void(DynamicVariant<Ts...> &)>;

template<typename... Ts>
using DynamicFunction = std::function<DynamicVariant<Ts...>(DynamicVariant<Ts...> &)>;

template<typename... Ts>
using DynamicType = boost::variant<
    DynamicVariant<Ts...>,
    DynamicCallable<Ts...>,
    std::string,
    Ts...
>;

template<typename... Ts>
class DynamicVariant
    : private std::map<std::string, DynamicType<Ts...>> {
    using super = std::map<std::string, DynamicType<Ts...>>;
    
    struct Printer;
    
public:

    using super::iterator;
    using super::const_iterator;
    using super::begin;
    using super::cbegin;
    using super::end;
    using super::cend;

    using Callable = DynamicCallable<Ts...>;
    using Function = DynamicFunction<Ts...>;

    DynamicVariant() = default;
    
    template<typename T>
    DynamicVariant(const std::string &index, T &&init) {
        insert(std::make_pair(index, init));
    }
    
    auto has(const std::string &index) const -> bool {
        return super::find(index) != super::end();
    }
    
    template<typename T>
    auto is(const std::string &index) -> T* {
        const auto &f = super::find(index);
        return (f == super::end())
                ? nullptr
                : boost::get<T>(&f->second);
    }
    
    template<typename T>
    auto is(const std::string &index) const -> const T * {
        return const_cast<DynamicVariant *>(this)->is<T>(index);
    }
    
    template<typename T>
    auto set(const std::string &index, T &&v) -> DynamicVariant & {
        super::operator[](index) = v;
        return *this;
    }
    
    auto unset(const std::string &index) -> DynamicVariant& {
        super::erase(index);
        return *this;
    }
    
    auto nested(const std::string &index) const -> const DynamicVariant& {
        return boost::get<DynamicVariant>(super::at(index));
    }
    
    auto nested(const std::string &index) -> DynamicVariant& {
        return boost::get<DynamicVariant>(super::operator[](index));
    }
    
    template<typename T, typename T2>
    auto get(const std::string &index, T &v, T2 &&deflt) const-> const DynamicVariant& {
        const auto p = is<T>(index);
        v = p ? *p : deflt;
        return *this;
    }
    
    template<typename T>
    auto get(const std::string &index, T &v) const -> const DynamicVariant& {
        return get(index, v, T());
    }
    
    auto setf(const std::string &index, Callable &&f) -> DynamicVariant& {
        super::operator[](index) = f;
        return *this;
    }
    
    auto getf(const std::string &) -> Function;
    
    template<typename R>
    auto at(const std::string &index) const -> const R& {
        return boost::get<R>(super::at(index));
    }
    
    auto merge(const DynamicVariant &other) -> DynamicVariant& {
        if (this != &other) {
            for (const auto &e : other)
                super::operator[](e.first) = e.second;
        }
        return *this;
    }
    
    auto clear() -> DynamicVariant& {
        auto it = super::cbegin();
        while (it != super::cend()) {
            if (it->first == "__proto") ++it;
            else it = super::erase(it);
        }
        return *this;
    }
    
    auto reset() -> DynamicVariant& {
        if (has("__proto"))
            merge(nested("__proto"));
        return *this;
    }
    
    auto proto(const DynamicVariant prototype) -> DynamicVariant& {
        super::operator[]("__proto") = std::move(prototype);
        return *this;
    }

    explicit operator std::string() const;
    
};

template<typename... Ts>
auto DynamicVariant<Ts...>::getf(const std::string &index) -> Function  {
    return [this, index](DynamicVariant &args) -> DynamicVariant {
        args["__this"] = *this;
        boost::get<DynamicCallable<Ts...> &>(super::at(index))(args);
        DynamicVariant<Ts...> result{};
        args.get("__result", result);
        return result;
    };
}

template<typename... Ts>
class DynamicVariant<Ts...>::Printer : public boost::static_visitor<> {
    std::ostream &os;
public:
    Printer(std::ostream &os_) : os(os_) {}
    template<typename T>
    void operator()(const T &v) const {
        os << v;
    }
    void operator()(const std::string &v) const {
        os << '"' << v << '"';
    }
    void operator()(const DynamicCallable<Ts...> &) const {
        os << "[](DynamicVariant &) -> void";
    }
    void operator()(const DynamicVariant<Ts...> &v) const {
        os << std::string(v);
    }
};

template<typename... Ts>
DynamicVariant<Ts...>::operator std::string() const {
    std::ostringstream os;
    os << "{ ";
    for (const auto &elem : *this) {
        os << elem.first << ": ";
        boost::apply_visitor(typename DynamicVariant<Ts...>::Printer(os), elem.second);
        os << "; ";
    }
    os << "}";
    return os.str();
}

int main() {
    using My_DynamicVariant = DynamicVariant<int, double, std::string>;
    My_DynamicVariant v;
    v.set("atu", 42);
    v.set("pi", 3.14);

    My_DynamicVariant other;
    other.set("greet", std::string("hello, world"));
    std::cout << "v: " << std::string(v) << "\n";
    std::cout << "other: " << std::string(other) << "\n";
    
    v.set("inside", other);
    std::cout << "v. " << std::string(v) << "\n";
    v.nested("inside").set("more", 1e6f)
                      .set("greet", "hi!");
    std::cout << "v: " << std::string(v) << "\n";
    
    v.setf("sayhello", [](My_DynamicVariant &args) {
            std::cout << "Salve "
                      << args.at<std::string>("name")
                      << "!\n";
    });
    My_DynamicVariant my_args;
    std::string my_result;
    my_args.set("name", "Martin");
    std::cout << "my_args: " << std::string(my_args) << "\n";
    v.getf("sayhello")(my_args);
    
    v.setf("sayhello", [](My_DynamicVariant &args) {
            const auto &instance(args.nested("__this"));
            const auto &fullname(args.at<std::string>("first")
                               + " "
                               + args.at<std::string>("last"));
            std::cout << fullname << ": "
                      << instance.nested("inside").at<std::string>("greet")
                      << '\n';
            My_DynamicVariant result;
            result.set("fullname", fullname);
            args.set("__result", result);
            std::cout << "args: " << std::string(args) << std::endl;
    });
    std::cout << "v: " << std::string(v) << std::endl;
    My_DynamicVariant other_args{my_args};
    std::cout << "other_args" << std::string(other_args) << std::endl;
    other_args.unset("name");
    std::cout << "other_args: " << std::string(other_args) << std::endl;
    
    other_args.set("first", "Martin");
    other_args.set("last", "Weitzel");
    std::cout << "other_args: " << std::string(other_args) << std::endl;
    other_args.merge(v.getf("sayhello")(other_args));
    std::cout << "other_args: " << std::string(other_args) << std::endl;
    other_args.get("fullname", my_result, "(no result)");
    std::cout << my_result << std::endl;
    
    using Other_DynamicVariant = DynamicVariant<int, std::string, std::shared_ptr<std::ostream>>;
    Other_DynamicVariant base;
    base.set("times", 3);
    base.set("say", std::string("who knows?"));
    auto outstream = std::make_shared<std::ostringstream>();
    base.set("out", outstream);
    base.setf("greet", [](Other_DynamicVariant &_) {
    //  std::shared_ptr<std::ostream> out; _.nested("__this").get("out", out);
    //  if (out) *out << "what's up?\n";
        Other_DynamicVariant instance = _.nested("__this");
        int i{};
        instance.get("times", i);
        while (i-- > 0)
            *instance.at<std::shared_ptr<std::ostream>>("out") << instance.at<std::string>("say") << '\n';
    });
    std::cout << "base: " << std::string(base) << std::endl;
    base.proto(base);
    std::cout << "base: " << std::string(base) << std::endl;
    base.set("first", 456);
    base.set("middle", 789);
    std::cout << "base: " << std::string(base) << std::endl;
    base.clear().reset();
    std::cout << "base: " << std::string(base) << std::endl;
    Other_DynamicVariant empty;
    base.getf("greet")(empty);
    base.set("say", std::string("what's up?"));
    std::cout << "base: " << std::string(base) << std::endl;
    base.getf("greet")(empty);
    std::shared_ptr<std::ostream> out;
    std::cout << outstream->str();
}
