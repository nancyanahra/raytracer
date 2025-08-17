#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"

class sphere : public hittable {



    public:
        sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}
        
        bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
            // center - origin
            // the vector from the ray origin to the sphere center
            vec3 oc = center - r.origin();
            // ray direction squared length
            auto a = r.direction().length_squared();
            
            // dot product of direction and origin->center
            // half the linear coefficient in the quadratic equation that
            // determines where ( if at all) the ray intersects the sphere
            // basically tells us how much the ray is "pointing towards" 
            // the center of the sphere
            auto h = dot(r.direction(), oc);
            auto c = oc.length_squared() - radius*radius;
            //discriminant is used to check intersection
            auto discriminant = h*h - a*c;
            if(discriminant < 0) return false;
            
            auto sqrtd = std::sqrt(discriminant);
            
            // find nearest root (hittable surface) that lies in the acceptable range.
            // is the first root within the range?
            auto root = (h-sqrtd)/a;
            if (root <= ray_tmin || ray_tmax <= root){
                //if the first one isnt, is the second root in range?
                root = (h+sqrtd)/a;
                if (root <=ray_tmin || ray_tmax <= root)
                    return false;
            }
            
            //this will select the first of the two roots in range (if any)
            
            // ray parameter t where the hit occurred
            rec.t = root;
            //point of intersection
            rec.p = r.at(rec.t);

            // true that it is getting hit, then find the 
	        // surface normal (unit vector) at that point
	        // to get the outward normal: subtract the ray 
	        // thats going from spheres center to the point 
	        // on the sphere FROM the direction of the hit point
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            
            return true;    
        
        }
        
     private:
     
        point3 center;
        double radius;

};

#endif
