#ifndef VEC3_HPP
#define VEC3_HPP
class vec3 {
	public:
		double e[3];
		//constructors
		vec3() : e{0,0,0} {}
		vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

		//accessors for individual componnets of the vector

		double x() const { return e[0]; }
		double y() const { return e[1]; }
		double z() const { return e[2]; }

		// Operators: negation & indexing

		vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]);}
		double operator[](int i) const  { return e[i]; }
		double& operator[](int i) {return e[i]; }
		
		//operators

		vec3& operator+=(const vec3& v) {
		
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];
			return *this;

		}

		vec3& operator*=(double t) {

			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
			return *this;

		}
	

		vec3& operator/=(double t) {
			return *this*=1/t;
		}

		// length and squared length
		
		double length() const {

			return std::sqrt(length_squared());
		}

		double length_squared() const {
			return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
		}
		
		static vec3 random(){
		
		    return vec3(random_double(),random_double(), random_double());
		}
		static vec3 random(double min, double max){
		    return vec3(random_double(min,max), random_double(min,max),random_double(min,max));
		}

};

// same thing as vec3
using point3 = vec3;

//Vector Utility Functions

// how to print a vec3

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}


// adding 2 vec3s together to result in a new vec3
inline vec3 operator+(const vec3& u, const vec3& v){

	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);

}	


inline vec3 operator-(const vec3& u, const vec3&v) {

	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2]- v.e[2]);

}

inline vec3 operator*(const vec3& u, const vec3& v) {


	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
	
	
inline vec3 operator*(double t, const vec3& v) {
	return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {

	return t * v;

}

inline vec3 operator/(const vec3& v, double t){

	return (1/t)*v;
}

inline double dot(const vec3& u, const vec3& v){
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
	

}

//
// i		j		k
// u.e[0]	u.e[1]		u.e[2]
// v.e[0]	v.e[1]		v.e[2]
//
//

inline vec3 cross(const vec3& u, const vec3& v) {

	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
			u.e[2] * v.e[0] - u.e[0] *v.e[2],
			u.e[0] * v.e[1] - u.e[1] *v.e[0]);

}

inline vec3 unit_vector(const vec3& v){
	return v/v.length();
}
	
inline vec3 random_unit_vector(){

// keep rejecting bad samples until we get a good sample
    while(true){
        //pick a random point inside the cube surrounding the unit sphere
        auto p= vec3::random(-1,1);
        //calculates the squuared length of the vector p
        auto lensq = p.length_squared();
        
        //accept the vector if it  falls inside or on the unit sphere
        if(1e-160 < lensq && lensq <=1){
            return p/sqrt(lensq);
        }
    
    }

}

inline vec3 random_on_hemisphere(const vec3& normal){
    // if the random unit vector generated was in the same hemisphere as the normal
    // just return that. otherwise, invert it.
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) >0.0){
        return on_unit_sphere;
    } else {
        return -on_unit_sphere;
    }

}

	
#endif

