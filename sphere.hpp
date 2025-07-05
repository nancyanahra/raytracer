#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "vec3.hpp"

class sphere : public hittable {

    public:
        sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}
        
        bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        
            vec3 oc = center - r.origin();
            auto a = r.direction().length_squared();
            
            auto h = dot(r.direction(), oc);
            auto c = oc.length_squared() - radius*radius;
            
            auto discriminant = h*h - a*c;
            if(discriminant < 0) return false;
            
            auto sqrtd = std::sqrt(discriminant);
            
            // find nearest root (hittable surface) that lies in the acceptable range.
            // is the first root within the range?
            auto root = (h-sqrtd)/a;
            if (root <= ray_tmin || ray|tmax <= root){
                //if the first one isnt, is the second root in range?
                root = (h+sqrtd)/a;
                if (root <=ray_tmin || ray_tmax <= root)
                    return false;
            }
            
            //this will select the first of the two roots in range (if any)
            rec.t = root;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            
            return true;    
        
        }
        
     private:
     
        point3 center;
        double radius;

};

#endif
