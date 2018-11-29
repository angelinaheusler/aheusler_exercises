/* Programming Techniques for Scientific Simulations, HS 2018
 * Week 11
 */

#ifndef ALGO_DERIVATION
#define ALGO_DERIVATION

enum OP_enum {Add, Multiply};

//********

template<typename T>
class Constant {
public:
    Constant(const T & v) : val_(v) {}
    T operator()(const T &) const {
		return val_;
    }
    T derivative(const T &) const {
		return 0;
    }
private:
    T val_;
};

// this function is just here so we don't need to write <int>. The function
// can deduce it (whereas the class can't)
template <typename T>
Constant<T> constant(const T & x) {
    return Constant<T>(x);
}

//********

template <typename T>
class Variable {
public:
    T operator()(const T & x) const {
		return x;
    }
    T derivative(const T & x) const {
		return 1;
    }
};

//********

template<typename L, typename R, OP_enum op>
class Expression {
public:
    Expression(const L & l, const R & r) : l_(l), r_(r) { }

    template <typename T>
    T operator()(const T & x) const {
        switch (op) { // we could just as well use if ... else if .... else
            case Add:
				return l_(x) + r_(x);
            case Multiply:
                return l_(x) * r_(x);
        }
    }

    template <typename T>
    T derivative(const T & x) const {
        switch (op) {
            case Add:
                return l_.derivative(x) + r_.derivative(x);
            case Multiply:
                return l_(x)*r_.derivative(x) + r_(x)*l_.derivative(x);
        }
    }

private:
    L l_;
    R r_;
};

//********

template<typename L, typename R>
Expression<L, R, Multiply> operator*(const L & l, const R & r) {
    return Expression<L, R, Multiply>(l, r);
}

template<typename L, typename R>
Expression<L, R, Add> operator+(const L & l, const R & r) {
    return Expression<L, R, Add>(l, r);
}

#endif //ALGO_DERIVATION

