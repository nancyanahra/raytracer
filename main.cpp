#include "rtweekend.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "camera.hpp"
#include "sphere.hpp"

double hit_sphere(const point3& center, double radius, const ray& r){

	// solving for t in the ray-sphere intersection gives values for a, b, an dc
	// this oc vector goes from the origin of the ray to the center of the sphere
	vec3 oc = center - r.origin();
	// a = d ⋅ d
	// a vector dotted with itself = squared length of that vector
	auto a = r.direction().length_squared();
	//b = -2d ⋅ (C - Q), but we simplify the ray-sphere intersection
	// with the line below
	auto h = dot(r.direction(), oc);
	//c = (C - Q) ⋅ (C - Q)
	auto c = oc.length_squared() - radius*radius;
	auto discriminant = h*h -a*c;
	
	if (discriminant < 0){
	
		// sphere does not get hit
		return -1.0;

	} else { 
		// sphere gets at least hit at a tangent or goes through it
		// this returns the points where the sphere gets hit
		return (h - std::sqrt(discriminant) )/a;
	
	}

}

int main() {
 

    // World
    
    // this is just a list of hittable objects.
    hittable_list world;
    
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5)); // our main "hittable: sphere
    
    world.add(make_shared<sphere>(point3(0,-100.5,-1),100)); // green sphere "representing earth"


    camera cam;
    
  
	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 400;
	cam.render(world);




	
}
