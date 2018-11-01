#include <cmath>
#include <sstream>

class Vector {
    const int _dim;
    double *_arr;

public:
    Vector (int dim, double arr[] = nullptr);
    Vector (const Vector& vec);
    Vector (const Vector&& vec);
    ~Vector ();

    Vector zero_vec (int dim);
    Vector unit_vec (int dim, int ind = 0);
    Vector add (const Vector& vec) const;
    Vector subtract (const Vector& vec) const;
    Vector multiply_scalar (const double alpha) const;
    double multiply_vector (const Vector& vec) const;
    double norm () const;
    
    double& operator[] (int ind);
    const double& operator[] (int ind) const;

    std::ostringstream to_string() const;

    friend Vector operator+ (const Vector& vec1, const Vector& vec2);
    friend Vector operator- (const Vector& vec1, const Vector& vec2);
    friend Vector operator* (double alpha, const Vector& vec);
    friend Vector operator* (const Vector& vec1, const Vector& vec2);
};