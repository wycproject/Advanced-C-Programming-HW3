#ifndef CUBE_H_
#define CUBE_H_

#include "Object.h"
#include "Vector3.h"
#include "Ray.h"
#include "IntersectionInfo.h"

class Cube : public Object {
public:
    Vector3 minCorner;  // Minimum corner of the cube
    Vector3 maxCorner;  // Maximum corner of the cube

    Cube(const Vector3& minCorner, const Vector3& maxCorner) : minCorner(minCorner), maxCorner(maxCorner) {}

    virtual bool getIntersection(const Ray& ray, IntersectionInfo* I) const override {
        Vector3 invDir = 1.0 / ray.d;
        Vector3 tMin = (minCorner - ray.o) * invDir;
        Vector3 tMax = (maxCorner - ray.o) * invDir;

        Vector3 t1 = min(tMin, tMax);
        Vector3 t2 = max(tMin, tMax);

        double tNear = std::max(std::max(t1.x, t1.y), t1.z);
        double tFar = std::min(std::min(t2.x, t2.y), t2.z);

        if (tNear > tFar || tFar < 0)
            return false;

        I->t = tNear;
        I->hit = ray.o + ray.d * I->t;
        I->object = this;
        return true;
    }

    virtual Vector3 getNormal(const IntersectionInfo& I) const override {
        Vector3 hitPoint = I.hit;
        Vector3 diff = (hitPoint - minCorner).abs() - (maxCorner - minCorner);
        Vector3 normal = Vector3(0, 0, 0);

        if (fabs(diff.x) < 1e-4) normal.x = (hitPoint.x > minCorner.x) ? 1 : -1;
        else if (fabs(diff.y) < 1e-4) normal.y = (hitPoint.y > minCorner.y) ? 1 : -1;
        else if (fabs(diff.z) < 1e-4) normal.z = (hitPoint.z > minCorner.z) ? 1 : -1;

        return normal;
    }
};

#endif // CUBE_H_
