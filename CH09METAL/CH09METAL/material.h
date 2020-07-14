#pragma once
#include "hittable.h"
class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) = 0;
};


class lambertian : public material {
public:
	color albedo;
	lambertian(const color& a) :albedo(a) {};

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) {
		vec3 scatter_direction = rec.normal + random_unit_vector();
		scattered = ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	}

};


class metal : public material {
public:
	color albedo;
	metal(const color& a) :albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) {
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
};