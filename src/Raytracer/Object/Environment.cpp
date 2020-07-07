//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Object/Environment.hpp"

#include "Raytracer/Material/Dielectric.hpp"
#include "Raytracer/Material/Lambertian.hpp"
#include "Raytracer/Material/SolidColor.hpp"
#include "Raytracer/Material/CheckerTexture.hpp"
#include "Raytracer/Material/ImageTexture.hpp"
#include "Raytracer/Material/PerlinTexture.hpp"
#include "Raytracer/Material/DiffuseLight.hpp"
#include "Raytracer/Material/Metal.hpp"

#include "Raytracer/Object/Box.hpp"
#include "Raytracer/Object/MovingSphere.hpp"
#include "Raytracer/Object/FlipFace.hpp"
#include "Raytracer/Object/Plane.hpp"
#include "Raytracer/Object/Sphere.hpp"

namespace rt
{
    Environment::Environment(std::size_t size):
        m_objects(size)
    {
    }

    Environment Environment::RandomEnvironment() {
        rt::Environment world;

        auto groundMaterial = std::make_unique<rt::Lambertian>(
                std::make_unique<rt::CheckerTexture>(
                        std::make_unique<rt::SolidColor>(glm::vec3(0.2, 0.3, 0.1)),
                        std::make_unique<rt::SolidColor>(glm::vec3(0.9, 0.9, 0.9))
                        )
                );
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
                        sphereMaterial = std::make_unique<rt::Lambertian>(std::make_unique<SolidColor>(albedo));
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

        auto material2 = std::make_unique<rt::Lambertian>(std::make_unique<rt::SolidColor>(glm::vec3(0.4, 0.2, 0.1)));
        world.Add(std::make_shared<rt::Sphere>(glm::vec3(-4, 1, 0), 1.0, std::move(material2)));

        auto material3 = std::make_unique<rt::Metal>(glm::vec3(0.7, 0.6, 0.5), 0.0);
        world.Add(std::make_shared<rt::Sphere>(glm::vec3(4, 1, 0), 1.0, std::move(material3)));

        return world;
    }

    Environment Environment::TwoSpheres()
    {
        Environment result;

        result.Add(std::make_shared<Sphere>(glm::vec3(0, -10, 0),
                                            10,
                                            std::make_unique<rt::Lambertian>(
                                                    std::make_unique<rt::CheckerTexture>(
                                                            std::make_unique<rt::SolidColor>(glm::vec3(0.2, 0.3, 0.1)),
                                                            std::make_unique<rt::SolidColor>(glm::vec3(0.9, 0.9, 0.9))
                                                    )
                                            ))
        );

        result.Add(std::make_shared<Sphere>(glm::vec3(0, 10, 0),
                                            10,
                                            std::make_unique<rt::Lambertian>(
                                                    std::make_unique<rt::CheckerTexture>(
                                                            std::make_unique<rt::SolidColor>(glm::vec3(0.2, 0.3, 0.1)),
                                                            std::make_unique<rt::SolidColor>(glm::vec3(0.9, 0.9, 0.9))
                                                    )
                                            ))
        );
        return result;
    }

    Environment Environment::TwoPerlinSpheres()
    {
        Environment result;

        result.Add(std::make_shared<Sphere>(glm::vec3(0, -1000, 0),
                                            1000,
                                            std::make_unique<rt::Lambertian>(std::make_unique<rt::PerlinTexture>(4.))
                                            )
        );

        result.Add(std::make_shared<Sphere>(glm::vec3(0, 2, 0),
                                            2,
                                            std::make_unique<rt::Lambertian>(std::make_unique<rt::PerlinTexture>(4.))
                                            )
        );
        return result;
    }

    Environment Environment::Earth()
    {
        auto earthTexture = std::make_unique<rt::ImageTexture>("./samples/earthmap.jpg");
        auto earthSurface = std::make_unique<rt::Lambertian>(std::move(earthTexture));
        auto globe = std::make_shared<rt::Sphere>(glm::vec3(0, 0, 0), 2, std::move(earthSurface));

        Environment result;
        result.Add(globe);

        return result;
    }

    Environment Environment::SimpleLight()
    {
        Environment environment;
        environment.Add(std::make_shared<rt::Sphere>(
                glm::vec3(0, -1000, 0), 1000,
                std::make_unique<rt::Lambertian>(std::make_unique<PerlinTexture>(4))
        ));
        environment.Add(std::make_shared<rt::Sphere>(
                glm::vec3(0, 2, 0), 2,
                std::make_unique<rt::Lambertian>(std::make_unique<PerlinTexture>(4))
        ));

        environment.Add(std::make_shared<rt::Sphere>(
                glm::vec3(0, 7, 0), 2,
                std::make_unique<rt::DiffuseLight>(
                        std::make_unique<rt::SolidColor>(glm::vec3(4., 4., 4.))
                )
        ));
        environment.Add(std::make_shared<rt::Plane<2>>(
                glm::vec2(3, 1), glm::vec2(5, 3), -2,
                std::make_unique<rt::DiffuseLight>(
                        std::make_unique<rt::SolidColor>(glm::vec3(4., 4., 4.))
                )
        ));
        return environment;
    }

    Environment Environment::CornellBox()
    {
        Environment environment;
        auto red   = std::make_unique<rt::Lambertian>(std::make_unique<rt::SolidColor>(glm::vec3(.65, .05, .05)));
        auto green = std::make_unique<rt::Lambertian>(std::make_unique<rt::SolidColor>(glm::vec3(.12, .45, .15)));
        auto light = std::make_unique<rt::DiffuseLight>(std::make_unique<rt::SolidColor>(glm::vec3(15, 15, 15)));

        // TODO: Register material in some kind of structure to avoid those kind of storage
        auto white  = std::make_unique<rt::Lambertian>(std::make_unique<rt::SolidColor>(glm::vec3(.73, .73, .73)));
        auto white1 = std::make_unique<rt::Lambertian>(std::make_unique<rt::SolidColor>(glm::vec3(.73, .73, .73)));
        auto white2 = std::make_unique<rt::Lambertian>(std::make_unique<rt::SolidColor>(glm::vec3(.73, .73, .73)));

        // Side walls
        environment.Add(std::make_shared<rt::FlipFace>(
                std::make_shared<rt::Plane<0>>(
                        glm::vec2{0, 0},
                        glm::vec2{555, 555},
                        555, std::move(green)))
                );

        environment.Add(std::make_shared<rt::Plane<0>>(
                glm::vec2{0, 0}, glm::vec2{555, 555},
                0, std::move(red)));

        // Light
        environment.Add(std::make_shared<rt::Plane<1>>(
                glm::vec2{213, 227}, glm::vec2{343, 332},
                554, std::move(light)));

        // Bottom + Up
        environment.Add(std::make_shared<rt::FlipFace>(
                std::make_shared<rt::Plane<1>>(
                        glm::vec2{0, 0},
                        glm::vec2{555, 555},
                        0, std::move(white)))
                );
        environment.Add(std::make_shared<rt::Plane<1>>(
                glm::vec2{0, 0}, glm::vec2{555, 555},
                555, std::move(white1)));

        // Background
        environment.Add(std::make_shared<rt::FlipFace>(
                std::make_shared<rt::Plane<2>>(
                        glm::vec2{0, 0},
                        glm::vec2{555, 555},
                        555, std::move(white2)))
                        );

        environment.Add(std::make_shared<Box>(glm::vec3(130, 0, 65), glm::vec3(295, 165, 230),
                                              std::make_unique<rt::Lambertian>(std::make_unique<rt::SolidColor>(glm::vec3(.73, .73, .73)))));

        environment.Add(std::make_shared<Box>(glm::vec3(265, 0, 295), glm::vec3(430, 330, 460),
                                              std::make_unique<rt::Lambertian>(std::make_unique<rt::SolidColor>(glm::vec3(.73, .73, .73)))));

        return environment;
    }

    void Environment::Clear()
    {
        m_objects.clear();
    }

    void Environment::Add(std::shared_ptr<Hittable> object)
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