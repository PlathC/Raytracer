//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Object/Environment.hpp"

#include "Raytracer/Material/Dielectric.hpp"
#include "Raytracer/Material/Lambertian.hpp"
#include "Raytracer/Material/Metal.hpp"

#include "Raytracer/Object/MovingSphere.hpp"
#include "Raytracer/Object/Sphere.hpp"

namespace rt
{
    Environment::Environment(std::size_t size):
        m_objects(size)
    {
    }

    Environment Environment::RandomEnvironment() {
        rt::Environment world;

        auto groundMaterial = std::make_unique<rt::Lambertian>(glm::vec3(0.5, 0.5, 0.5));
        world.Add(std::make_shared<rt::Sphere>(glm::vec3(0, -1000, 0), 1000, std::move(groundMaterial)));

        for (int a = -11; a < 11; a++)
        {
            for (int b = -11; b < 11; b++)
            {
                auto chooseMat = rt::Random<double>();
                glm::vec3 center(a + 0.9 * rt::Random<double>(), 0.2, b + 0.9 * rt::Random<double>());

                if (glm::length(center - glm::vec3(4, 0.2, 0)) > 0.9)
                {
                    std::unique_ptr<rt::Material> sphereMaterial = nullptr;

                    if (chooseMat < 0.8)
                    {
                        // diffuse
                        glm::vec3 albedo = rt::VRandom<float>() * rt::VRandom<float>();
                        sphereMaterial = std::make_unique<rt::Lambertian>(albedo);
                        glm::vec3 center2 = center + glm::vec3(0, rt::Random<double>(0., .5), 0.f);
                        world.Add(std::make_shared<rt::MovingSphere>(center, center2, 0., 1., 0.2, std::move(sphereMaterial)));
                    }
                    else if (chooseMat < 0.95)
                    {
                        // metal
                        glm::vec3 albedo = rt::VRandom<float>(0.5, 1);
                        auto fuzz = rt::Random<double>(0, 0.5);
                        sphereMaterial = std::make_unique<rt::Metal>(albedo, fuzz);
                        world.Add(std::make_shared<rt::Sphere>(center, 0.2, std::move(sphereMaterial)));
                    }
                    else
                    {
                        // glass
                        sphereMaterial = std::make_unique<rt::Dielectric>(1.5);
                        world.Add(std::make_shared<rt::Sphere>(center, 0.2, std::move(sphereMaterial)));
                    }
                }
            }
        }
        auto material1 = std::make_unique<rt::Dielectric>(1.5);
        world.Add(std::make_shared<rt::Sphere>(glm::vec3(0, 1, 0), 1.0, std::move(material1)));

        auto material2 = std::make_unique<rt::Lambertian>(glm::vec3(0.4, 0.2, 0.1));
        world.Add(std::make_shared<rt::Sphere>(glm::vec3(-4, 1, 0), 1.0, std::move(material2)));

        auto material3 = std::make_unique<rt::Metal>(glm::vec3(0.7, 0.6, 0.5), 0.0);
        world.Add(std::make_shared<rt::Sphere>(glm::vec3(4, 1, 0), 1.0, std::move(material3)));

        return world;
    }

    void Environment::Clear()
    {
        m_objects.clear();
    }

    void Environment::Add(std::shared_ptr<Hittable>&& object)
    {
        m_objects.emplace_back(std::move(object));
    }

    size_t Environment::Size() const
    {
        return m_objects.size();
    }

    std::vector<std::shared_ptr<Hittable>>& Environment::Objects()
    {
        return m_objects;
    }

    bool Environment::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        HitRecord tempRecord;
        bool hitAnything = false;
        auto closestSoFar = tMax;

        for (const auto& object : m_objects)
        {
            if (object->Hit(ray, tMin, closestSoFar, tempRecord))
            {
                hitAnything = true;
                closestSoFar = tempRecord.t;
                record = tempRecord;
            }
        }

        return hitAnything;
    }

    bool Environment::BoundingBox(const double t0, const double t1, AABB& box) const
    {
        if(m_objects.empty())
            return false;

        AABB temp;
        bool isFirstBox = true;

        for(const auto& object : m_objects)
        {
            if(!object->BoundingBox(t0, t1, temp)) return false;
            box = isFirstBox ? temp : AABB(box, temp);
            isFirstBox = false;
        }

        return true;
    }
}