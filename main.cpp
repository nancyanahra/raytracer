#include "color.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include <iostream>


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





color ray_color(const ray& r){
		
	// t calculates the points the sphere 
	// is getting hit at, if it does get hit
	auto t = hit_sphere(point3(0,0,-1), 0.5, r);
	// if it is getting hit, then find the 
	// surface normal (unit vector) at that point
	// to get the outward normal: subtract the ray 
	// thats going from spheres center to the point 
	// on the sphere FROM the direction of the hit point
	if (t > 0.0) {
		vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
		
		//RGB goes from 0 to 1.
		// vectors range from -1 to 1
		//convert normalized color so that
		// -1 -> 0
		//  0 -> 0.5
		// +1 -> 1
		return 0.5*color(N.x()+1, N.y()+1,N.z()+1);
	
	}
	
	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5*(unit_direction.y() + 1.0);
	return  (1.0 - a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
}

int main() {


    // image height must be >= 1
	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 400;

	int image_height = int(image_width / aspect_ratio);
	image_height= (image_height < 1) ? 1 : image_height;

	//camera
	auto focal_length = 1.0;
	// viewport widths less than one are ok since theyre real valuedd
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (double(image_width)/image_height);
	auto camera_center = point3(0,0,0);

	//calculate the vectors across the horizontal and down the vertical
	//viewport edges.
	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	// calculate the horizontal and vertical delta vectors from pixel to pixel
	auto pixel_delta_u = viewport_u / image_width;
	auto pixel_delta_v = viewport_v / image_height;

	//Calculate the location of the upper left pixel
	auto viewport_upper_left =
		camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
	auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

		

    //render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j=0; j< image_height; j++){
    	std::cerr << "\rScanlines remaining: " << (image_height -j) << ' ' << std::flush;
        for(int i=0; i<image_width; i++){
        
		auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
		auto ray_direction = pixel_center - camera_center;
		ray r(camera_center, ray_direction);
		
		color pixel_color = ray_color(r);
           	 write_color(std::cout, pixel_color);
        }

    }
    
    std::clog << "\rDone.			\n";


	
}
