#include "vector.h"

Vector::Vector (int dim, double arr[]) : _dim(dim), _arr(new double[_dim]) {
    for (int i = 0; i < _dim; i++) {
        _arr[i] = arr[i];
    }
}

Vector::Vector (const Vector& vec) : _dim(vec._dim), _arr(new double[_dim]) {
    for (int i = 0; i < _dim; i++) {
        _arr[i] = vec._arr[i];
    }
}

Vector::Vector (const Vector&& vec) : _dim(vec._dim), _arr(new double[_dim]) {
    for (int i = 0; i < _dim; i++) {
        _arr[i] = vec._arr[i];
    }
}

Vector::~Vector () {
    delete[] _arr;
}

Vector Vector::zero_vec (int dim) {
    double *zero_arr = new double[dim];
    for (int i = 0; i < dim; i++) {
        zero_arr[i] = 0.0;
    }

    Vector zero_vec (dim, zero_arr);
    delete[] zero_arr;
    return zero_vec;
}

Vector Vector::unit_vec (int dim, int ind) {
    Vector zero_vec(dim);
    zero_vec[ind] = 1.0;
    return zero_vec;
}

Vector Vector::add (const Vector& vec) const {
    if (_dim != vec._dim) {
        throw std::length_error ("Cannot add vectors with diffenrent dimensions");
    }
    
    double *sum_arr = new double[vec._dim];
    for (int i = 0; i < _dim; i++) {
        sum_arr[i] = _arr[i] + vec._arr[i];
    }

    Vector sum_vec (_dim, sum_arr);
    delete[] sum_arr;
    return sum_vec;
}

Vector Vector::subtract (const Vector& vec) const {
    if (_dim != vec._dim) {
        throw std::length_error ("Cannot subtract vectors with diffenrent dimensions");
    }

    return add (vec.multiply_scalar (-1.0));
}

Vector Vector::multiply_scalar (const double alpha) const {
    Vector mult_vec (*this);
    for (int i = 0; i < mult_vec._dim; i++) {
        mult_vec._arr[i] *= alpha;
    }

    return mult_vec;
}

double Vector::multiply_vector (const Vector& vec) const {
    if (_dim != vec._dim) {
        throw std::length_error ("Cannot multiply vectors with diffenrent dimensions");
    }

    double mult = 0;
    for (int i = 0; i < _dim; i++) {
        mult += _arr[i] * vec._arr[i];
    }

    return mult;
}

double Vector::norm () const {
    return sqrt (multiply_vector(*this));
}

double& Vector::operator[] (int ind) {
    return _arr[ind];
}


const double& Vector::operator[] (int ind) const {
    return _arr[ind];
}

std::ostringstream Vector::to_string() const {
    std::ostringstream out_str;
    out_str << "(" << _arr[0];
    for (int i = 1; i < _dim; i++) {
        out_str << ", " << _arr[i];
    }

    out_str << ")";
    return out_str;
}

Vector operator+ (const Vector& vec1, const Vector& vec2) {
    return vec1.add(vec2);
}

Vector operator- (const Vector& vec1, const Vector& vec2) {
    return vec1.subtract(vec2);
}
Vector operator* (double alpha, const Vector& vec) {
    return vec.multiply_scalar(alpha);
}
Vector operator* (const Vector& vec1, const Vector& vec2) {
    return vec1.multiply_vector(vec2);
}