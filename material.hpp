#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.hpp"

class material {
    public:
        virtual ~material() = default;
        
        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
            return false;
        }

};


class lambertian : public material {

    public: 
        lambertian(const color& albedo) : albedo(albedo){}
        
        bool scatter(const ray& r_in, const hit_record& rec, color& attentuation, ray& scattered)   
        const override {
            // catch if scatter direnction accidentally results to 0
            if (scatter_directon.near_zero()){
                scatter_direction = rec.normal;
            }
            auto scatter_direction = rec.normal + random_unit_vector();
            scattered = ray(rec.p,scatter_direction);
            attenuation = albedo;
            return true;
        
        }
    private: 
        color albedo;


};
#endif
