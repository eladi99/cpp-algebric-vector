#include "vector.h"
#include <sstream>

Vector::Vector (unsigned int dim, double arr[]) 
    : _dim (dim), _arr (new double[_dim]) {
    if (arr == nullptr) {
        for (unsigned int i = 0; i < _dim; i++) {
            _arr[i] = 0.0;
        }
    }
    else {
        for (unsigned int i = 0; i < _dim; i++) {
            _arr[i] = arr[i];
        }
    }
}

Vector::Vector (const Vector& vec) 
    : _dim (vec._dim), _arr (new double[_dim]) {
    for (unsigned int i = 0; i < _dim; i++) {
        _arr[i] = vec._arr[i];
    }
}

Vector::Vector (const Vector&& vec) 
    : _dim (vec._dim), _arr (new double[_dim]) {
    for (unsigned int i = 0; i < _dim; i++) {
        _arr[i] = vec._arr[i];
    }
}

Vector::~Vector () {
    delete[] _arr;
}

Vector Vector::zero_vec (unsigned int dim) {
    double *zero_arr = new double[dim];
    for (unsigned int i = 0; i < dim; i++) {
        zero_arr[i] = 0.0;
    }

    Vector vec0 (dim, zero_arr);
    delete[] zero_arr;
    return vec0;
}

Vector Vector::unit_vec (unsigned int dim, unsigned int ind) {
    Vector vec0 (zero_vec (dim));
    vec0[ind] = 1.0;
    return vec0;
}

unsigned int Vector::dim() const {
    return _dim;
}

Vector Vector::add (const Vector& vec) const {
    if (_dim != vec._dim) {
        throw std::length_error (
            "Cannot add vectors with diffenrent dimensions"
        );
    }
    
    double *sum_arr = new double[vec._dim];
    for (unsigned int i = 0; i < _dim; i++) {
        sum_arr[i] = _arr[i] + vec._arr[i];
    }

    Vector sum_vec (_dim, sum_arr);
    delete[] sum_arr;
    return sum_vec;
}

Vector Vector::subtract (const Vector& vec) const {
    if (_dim != vec._dim) {
        throw std::length_error (
            "Cannot subtract vectors with diffenrent dimensions"
        );
    }

    double *sum_arr = new double[vec._dim];
    for (unsigned int i = 0; i < _dim; i++) {
        sum_arr[i] = _arr[i] - vec._arr[i];
    }

    Vector sum_vec (_dim, sum_arr);
    delete[] sum_arr;
    return sum_vec;
}

Vector Vector::multiply_scalar (const double alpha) const {
    Vector mult_vec (*this);
    for (unsigned int i = 0; i < mult_vec._dim; i++) {
        mult_vec._arr[i] *= alpha;
    }

    return mult_vec;
}

double Vector::dot_product (const Vector& vec) const {
    if (_dim != vec._dim) {
        throw std::length_error (
            "Cannot multiply vectors with diffenrent dimensions"
        );
    }

    double mult = 0;
    for (unsigned int i = 0; i < _dim; i++) {
        mult += _arr[i] * vec._arr[i];
    }

    return mult;
}

double Vector::norm () const {
    return sqrt (dot_product (*this));
}

Vector Vector::normalize () const {
    return (1 / norm ()) * Vector (*this);
}

bool Vector::is_equal (const Vector& vec) const {
    if (_dim != vec._dim) {
        return false;
    }

    for (unsigned int i = 0; i < _dim; i++) {
        if (abs (_arr[i] - vec._arr[i]) > epsilon) {
            return false;
        }
    }

    return true;
}

Vector& Vector::operator= (const Vector& vec) {
    if (this == &vec) {
        return *this;
    }
    
    if (_dim != vec._dim) {
        throw std::length_error ("Vector length is fixed");
    }
    
    delete[] _arr;
    _arr = new double[_dim];
    for (unsigned int i = 0; i < _dim; i++) {
        _arr[i] = vec._arr[i];
    }
}

Vector Vector::operator- () const {
    return multiply_scalar (-1.0);
}

double& Vector::operator[] (unsigned int ind) {
    return _arr[ind];
}


const double& Vector::operator[] (unsigned int ind) const {
    return _arr[ind];
}

std::string Vector::to_string () const {
    std::ostringstream out_str;
    out_str << "(" << _arr[0];
    for (unsigned int i = 1; i < _dim; i++) {
        out_str << ", " << _arr[i];
    }

    out_str << ")";
    return out_str.str();
}

double angle (const Vector& vec1, const Vector& vec2) {
    return acos (vec1.normalize () * vec2.normalize ());
}

Vector operator+ (const Vector& vec1, const Vector& vec2) {
    return vec1.add (vec2);
}

Vector operator- (const Vector& vec1, const Vector& vec2) {
    return vec1.subtract (vec2);
}

Vector operator* (double alpha, const Vector& vec) {
    return vec.multiply_scalar (alpha);
}

double operator* (const Vector& vec1, const Vector& vec2) {
    return vec1.dot_product (vec2);
}

bool operator== (const Vector& vec1, const Vector& vec2) {
    return vec1.is_equal (vec2);
}

bool operator!= (const Vector& vec1, const Vector& vec2) {
    return !vec1.is_equal (vec2);
}