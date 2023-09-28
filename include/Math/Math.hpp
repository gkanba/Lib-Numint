#ifndef _IG_MATH_H_
#define _IG_MATH_H_

#include <functional>

namespace Numint::Math{

// Abstract struct of Parameter of class T representation.
template <typename T>
struct Parameter{
    virtual T value(double time)
    {
        return T();
    }
};

// Time Variant Parameter of class T representation.
template <typename T, class... Args>
struct TimeVariantParameter : public Parameter<T>{
private:
    std::function<T(double)> eq;
public:
    // Default constructor.
    TimeVariantParameter() = default;
    // Default initializing constructor.
    TimeVariantParameter(const std::function<T(double)> equation) : eq(equation) {}
    // Function to get value.
    T value(double time){
        return eq(time);
    }
};

// Time Invariant Parameter of class T representation.
template <typename T>
struct TimeInvariantParameter : public Parameter<T>{
private:
    T c;
public:
    // Default constructor.
    TimeInvariantParameter() = default;
    // Default intializing constructor.
    TimeInvariantParameter(const T constant) : c(constant) {}
    // Function to get value.
    T value(double time){
        return c;
    }
};

// Abstract struct of class T to class U map (function) representation.
template <typename T, typename U>
struct Function{
private:
    std::function<U(T)> func;
public:
    // Default constructor.
    Function() = default;
    Function(std::function<U(T)> function) : func(function) {}
    // Function to get value.
    U value(T arg)
    {
        return func(arg);
    }
};

}

#endif