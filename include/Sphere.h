#ifndef Sphere_h_
#define Sphere_h_

#include <cmath>
#include "Object.h"
#include "Vector3.h"
#include "Ray.h"
#include "IntersectionInfo.h"
#include "BBox.h"

class Sphere : public Object {
public:
    Vector3 center; // Center of the sphere
    float r, r2; // Radius, Radius squared

    // Public constructor
    Sphere(const Vector3& center, float radius)
        : center(center), r(radius), r2(radius* radius) { }

    bool getIntersection(const Ray& ray, IntersectionInfo* I) const override {
        Vector3 s = center - ray.o;
        float sd = s * ray.d;
        float ss = s * s;

        // Compute discriminant
        float disc = sd * sd - ss + r2;

        // Complex values: No intersection
        if (disc < 0.f) return false;

        // Assume we are not in a sphere... The first hit is the lesser valued
        I->object = this;
        I->t = sd - sqrt(disc);
        return true;
    }

    Vector3 getNormal(const IntersectionInfo& I) const override {
        return normalize(I.hit - center);
    }

    BBox getBBox() const override {
        return BBox(center - Vector3(r, r, r), center + Vector3(r, r, r));
    }

    Vector3 getCentroid() const override {
        return center;
    }
};

#endif
