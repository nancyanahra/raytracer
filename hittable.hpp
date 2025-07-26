#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "ray.hpp"

    class hit_record {

	    public: 
	        point3 p;
	        vec3 normal;
	        //our hit will only count if this t is: t_min < t < t_max
	        double t;
	        
	        bool front_face;
	        
	        void set_face_normal(const ray& r, const vec3& outward_normal){
	        
	            // sets the hit record normal vector
	            // note: the parameter 'outward_normal' is assumed to have unit length
	            
	            // angle > 90 deg , so ray direction and 
	            //outward surface normal point in opposite directions
	            // so true if ray is hitting the outside surface of sphere
	            front_face = dot(r.direction(), outward_normal) < 0;
	            // normal otherwise points inward towards sphere if ray dir and surf norm 
	            // point in same direction
	            normal = front_face ? outward_normal : -outward_normal;
	            
	            }

	        
	        }
	        
    };

    class hittable {

        public:
            virtual ~hittable() = default;
            
            virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
         

    };
    
    #endif
