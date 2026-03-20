#include "rtweekend.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "camera.hpp"
#include "sphere.hpp"
#include "material.hpp"

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
    // color takes in rgb vals
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8), 0.6);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2),1.0);

    //spheres take in a point as center, radius, and a material type
    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
    camera cam;
    
  
	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 400;
	cam.samples_per_pixel = 100;
	cam.max_depth = 50;
	cam.render(world);




	
}
