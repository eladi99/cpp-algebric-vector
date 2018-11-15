#ifndef VECTOR_H 
#define VECTOR_H

#include <cmath>
#include <string>

class Vector {
    const unsigned int _dim;
    double *_arr;
    static constexpr double epsilon = 0.001;

public:
    explicit Vector (unsigned int dim, double arr[] = nullptr);
    Vector (const Vector& vec);
    Vector (const Vector&& vec);
    ~Vector ();
    
    Vector (double) = delete;
    operator double () = delete;

    static Vector zero_vec (unsigned int dim);
    static Vector unit_vec (unsigned int dim, unsigned int ind = 0);
    
    unsigned int dim () const;
    
    Vector add (const Vector& vec) const;
    Vector subtract (const Vector& vec) const;
    Vector multiply_scalar (const double alpha) const;
    double dot_product (const Vector& vec) const;
    bool is_equal (const Vector& vec) const;
    
    double norm () const;
    Vector normalize () const;
    
    std::string to_string () const;

    double& operator[] (unsigned int ind);
    const double& operator[] (unsigned int ind) const;
    Vector& operator= (const Vector& vec);
    Vector operator-() const;

    friend double angle (const Vector& vec1, const Vector& vec2);
    friend Vector operator+ (const Vector& vec1, const Vector& vec2);
    friend Vector operator- (const Vector& vec1, const Vector& vec2);
    friend Vector operator* (double alpha, const Vector& vec);
    friend double operator* (const Vector& vec1, const Vector& vec2);
    friend bool operator== (const Vector& vec1, const Vector& vec2);
    friend bool operator!= (const Vector& vec1, const Vector& vec2);
};

#endif /* VECTOR_H */