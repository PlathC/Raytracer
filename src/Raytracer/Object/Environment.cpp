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
#include "Raytracer/Object/BvhNode.hpp"
#include "Raytracer/Object/ConstantDensityMedium.hpp"
#include "Raytracer/Object/FlipFace.hpp"
#include "Raytracer/Object/MovingSphere.hpp"
#include "Raytracer/Object/Plane.hpp"
#include "Raytracer/Object/Rotation.hpp"
#include "Raytracer/Object/Sphere.hpp"
#include "Raytracer/Object/Translation.hpp"

namespace rt
{
    Environment::Environment(std::size_t size):
        m_objects(size)
    {
    }

    Environment Environment::RandomEnvironment() {
        rt::Environment world;

        auto groundMaterial = std::make_shared<rt::Lambertian>(
                std::make_shared<rt::CheckerTexture>(
                        std::make_shared<rt::SolidColor>(glm::vec3(0.2, 0.3, 0.1)),
                        std::make_shared<rt::SolidColor>(glm::vec3(0.9, 0.9, 0.9))
                        )
                );

        world.Add(std::make_shared<rt::Sphere>(glm::vec3(0, -1000, 0), 1000.f, groundMaterial));

        for (int a = -11; a < 11; a++)
        {
            for (int b = -11; b < 11; b++)
            {
                auto chooseMat = rt::Random<double>();
                glm::vec3 center(a + 0.9 * rt::Random<double>(), 0.2, b + 0.9 * rt::Random<double>());

                if (glm::length(center - glm::vec3(4, 0.2, 0)) > 0.9)
                {
                    std::shared_ptr<rt::Material> sphereMaterial = nullptr;

                    if (chooseMat < 0.8)
                    {
                        // diffuse
                        glm::vec3 albedo = rt::VRandom<float>() * rt::VRandom<float>();
                        sphereMaterial = std::make_shared<rt::Lambertian>(std::make_shared<SolidColor>(albedo));
                        glm::vec3 center2 = center + glm::vec3(0, rt::Random<double>(0., .5), 0.f);
                        world.Add(std::make_shared<rt::MovingSphere>(center, center2, 0.f, 1.f, 0.2f, sphereMaterial));
                    }
                    else if (chooseMat < 0.95)
                    {
                        // metal
                        glm::vec3 albedo = rt::VRandom<float>(0.5, 1);
                        auto fuzz = rt::Random<float>(0.f, 0.5f);
                        sphereMaterial = std::make_shared<rt::Metal>(albedo, fuzz);
                        world.Add(std::make_shared<rt::Sphere>(center, 0.2f, sphereMaterial));
                    }
                    else
                    {
                        // glass
                        sphereMaterial = std::make_shared<rt::Dielectric>(1.5);
                        world.Add(std::make_shared<rt::Sphere>(center, 0.2f, sphereMaterial));
                    }
                }
            }
        }
        auto material1 = std::make_shared<rt::Dielectric>(1.5);
        world.Add(std::make_shared<rt::Sphere>(glm::vec3(0, 1, 0), 1.f, material1));

        auto material2 = std::make_shared<rt::Lambertian>(std::make_shared<rt::SolidColor>(glm::vec3(0.4, 0.2, 0.1)));
        world.Add(std::make_shared<rt::Sphere>(glm::vec3(-4, 1, 0), 1.f, material2));

        auto material3 = std::make_shared<rt::Metal>(glm::vec3(0.7, 0.6, 0.5), 0.f);
        world.Add(std::make_shared<rt::Sphere>(glm::vec3(4, 1, 0), 1.f, material3));

        return world;
    }

    Environment Environment::TwoSpheres()
    {
        Environment result;
        auto checker = std::make_shared<rt::Lambertian>(
                std::make_shared<rt::CheckerTexture>(
                        std::make_shared<rt::SolidColor>(glm::vec3(0.2, 0.3, 0.1)),
                        std::make_shared<rt::SolidColor>(glm::vec3(0.9, 0.9, 0.9))
                )
        );

        result.Add(std::make_shared<Sphere>(glm::vec3(0, -10, 0),
                                            10.f, checker));

        result.Add(std::make_shared<Sphere>(glm::vec3(0, 10, 0),
                                            10.f, checker));

        return result;
    }

    Environment Environment::TwoPerlinSpheres()
    {
        Environment result;
        auto perlinTexture = std::make_shared<rt::Lambertian>(std::make_shared<rt::PerlinTexture>(4.f));

        result.Add(std::make_shared<Sphere>(glm::vec3(0, -1000, 0), 1000.f, perlinTexture));
        result.Add(std::make_shared<Sphere>(glm::vec3(0, 2, 0),2.f, perlinTexture));

        return result;
    }

    Environment Environment::Earth()
    {
        auto earthTexture = std::make_shared<rt::ImageTexture>("./samples/earthmap.jpg");
        auto earthSurface = std::make_shared<rt::Lambertian>(earthTexture);
        auto globe = std::make_shared<rt::Sphere>(glm::vec3(0, 0, 0), 2.f, earthSurface);

        Environment result;
        result.Add(globe);

        return result;
    }

    Environment Environment::SimpleLight()
    {
        Environment environment;
        auto perlinTexture = std::make_shared<rt::Lambertian>(std::make_shared<PerlinTexture>(4.f));
        auto lightTexture = std::make_shared<rt::DiffuseLight>(std::make_shared<rt::SolidColor>(glm::vec3(4., 4., 4.)));

        environment.Add(std::make_shared<rt::Sphere>(glm::vec3(0, -1000, 0), 1000.f, perlinTexture));
        environment.Add(std::make_shared<rt::Sphere>(glm::vec3(0, 2, 0), 2.f, perlinTexture));

        environment.Add(std::make_shared<rt::Sphere>(glm::vec3(0, 7, 0), 2.f, lightTexture));
        environment.Add(std::make_shared<rt::Plane<2>>(glm::vec2(3, 1), glm::vec2(5, 3), -2., lightTexture));
        return environment;
    }

    Environment Environment::CornellBox()
    {
        Environment environment;
        auto red   = std::make_shared<rt::Lambertian>(std::make_shared<rt::SolidColor>(glm::vec3(.65, .05, .05)));
        auto green = std::make_shared<rt::Lambertian>(std::make_shared<rt::SolidColor>(glm::vec3(.12, .45, .15)));
        auto light = std::make_shared<rt::DiffuseLight>(std::make_shared<rt::SolidColor>(glm::vec3(15, 15, 15)));

        auto white  = std::make_shared<rt::Lambertian>(std::make_shared<rt::SolidColor>(glm::vec3(.73, .73, .73)));

        // Side walls
        environment.Add(std::make_shared<rt::FlipFace>(
                std::make_shared<rt::Plane<0>>(
                        glm::vec2{0, 0},
                        glm::vec2{555, 555},
                        555, green))
                );

        environment.Add(std::make_shared<rt::Plane<0>>(
                glm::vec2{0, 0}, glm::vec2{555, 555},
                0, red));

        // Light
        environment.Add(std::make_shared<rt::Plane<1>>(
                glm::vec2{213, 227}, glm::vec2{343, 332},
                554, light));

        // Bottom + Up
        environment.Add(std::make_shared<rt::FlipFace>(
                std::make_shared<rt::Plane<1>>(
                        glm::vec2{0, 0},
                        glm::vec2{555, 555},
                        0, white))
                );
        environment.Add(std::make_shared<rt::Plane<1>>(
                glm::vec2{0, 0}, glm::vec2{555, 555},
                555, white));

        // Background
        environment.Add(std::make_shared<rt::FlipFace>(
                std::make_shared<rt::Plane<2>>(
                        glm::vec2{0, 0},
                        glm::vec2{555, 555},
                        555, white))
                        );

        auto thinBox = std::make_shared<Translation>(
                std::make_shared<rt::Rotation<1>>(
                    std::make_shared<Box>(glm::vec3(0, 0, 0), glm::vec3(165, 330, 165), white),
                    15.f),
                glm::vec3(265,0,295)
        );

        auto cube = std::make_shared<Translation>(
                std::make_shared<rt::Rotation<1>>(
                    std::make_shared<Box>(glm::vec3(0, 0, 0), glm::vec3(165, 165, 165), white),
                    -18.f),
                glm::vec3(130,0,65)
        );

        environment.Add(std::make_shared<ConstantDensityMedium>(thinBox,
                    std::make_shared<SolidColor>(glm::vec3(0.,0.,0.)), 0.01));

        environment.Add(std::make_shared<ConstantDensityMedium>(cube,
                    std::make_shared<SolidColor>(glm::vec3(1.,1.,1.)), 0.01));

        return environment;
    }

    Environment Environment::FinalScene()
    {
        Environment boxes;
        const uint8_t boxesPerSide = 20;

        auto boxMat = std::make_shared<Lambertian>(std::make_shared<SolidColor>(glm::vec3(0.48, 0.83, 0.53)));
        for(uint8_t i = 0; i < boxesPerSide; i++)
        {
            for(uint8_t j = 0; j < boxesPerSide; j++)
            {
                float w = 100.f;
                float x0 = -1000.f + i * w;
                float z0 = -1000.f + j * w;
                float y0 = 0.f;
                float x1 = x0 + w;
                float y1 = rt::Random<float>(1, 101);
                float z1 = z0 + w;

                boxes.Add(std::make_shared<Box>(glm::vec3(x0, y0, z0), glm::vec3(x1, y1, z1), boxMat));
            }
        }

        Environment objects;
        objects.Add(std::make_shared<BVHNode>(boxes, 0, 1));

        auto light = std::make_shared<DiffuseLight>(std::make_shared<SolidColor>(glm::vec3(7, 7, 7)));
        objects.Add(std::make_shared<rt::Plane<1>>(glm::vec2(123, 147), glm::vec2(423, 412), 554, light));

        constexpr glm::vec3 fCenter = glm::vec3(400, 400, 400);
        constexpr glm::vec3 sCenter = fCenter + glm::vec3(30, 0, 0);

        auto movingSphereMaterial = std::make_shared<Lambertian>(std::make_shared<SolidColor>(glm::vec3(0.7, 0.3, 0.1)));
        objects.Add(std::make_shared<MovingSphere>(fCenter, sCenter, 0.f, 1.f, 50.f, movingSphereMaterial));

        objects.Add(std::make_shared<Sphere>(glm::vec3(260, 150, 45), 50.f, std::make_shared<Dielectric>(1.5)));
        objects.Add(std::make_shared<Sphere>(
                glm::vec3(0, 150, 145), 50.f,
                std::make_shared<Metal>(glm::vec3(0.8, 0.8, 0.9), 10.f)
                ));

        auto boundary = std::make_shared<Sphere>(glm::vec3(360, 150, 145), 70.f, std::make_shared<Dielectric>(1.5));
        objects.Add(boundary);
        objects.Add(std::make_shared<ConstantDensityMedium>(boundary, std::make_shared<SolidColor>(glm::vec3(0.2, 0.4, 0.9)), 0.2));

        boundary = std::make_shared<Sphere>(glm::vec3(0., 0., 0.), 5000.f, std::make_shared<Dielectric>(1.5));
        objects.Add(std::make_shared<ConstantDensityMedium>(
                boundary, std::make_shared<SolidColor>(glm::vec3(1, 1, 1)), .0001));

        auto earthMap = std::make_shared<Lambertian>(std::make_shared<ImageTexture>("samples/earthmap.jpg"));
        objects.Add(std::make_shared<Sphere>(glm::vec3(400, 200, 400), 100.f, earthMap));

        auto perlinTexture = std::make_shared<Lambertian>(std::make_shared<PerlinTexture>(0.1f));
        objects.Add(std::make_shared<Sphere>(glm::vec3(220, 280, 300), 80.f, perlinTexture));

        Environment boxes2;
        auto white = std::make_shared<Lambertian>(std::make_shared<SolidColor>(glm::vec3(.73, .73, .73)));
        constexpr uint16_t ns = 1000;
        for(uint16_t j = 0; j < ns; j++)
        {
            boxes2.Add(std::make_shared<Sphere>(rt::VRandom<float>(0, 165), 10.f, white));
        }

        objects.Add(std::make_shared<rt::Translation>(std::make_shared<rt::Rotation<1>>(
                std::make_shared<rt::BVHNode>(boxes2, 0., 1.), 15.f),
                        glm::vec3(-100, 270, 395)));

        return objects;
    }

    void Environment::Clear()
    {
        m_objects.clear();
    }

    void Environment::Add(std::shared_ptr<IHittable> object)
    {
        m_objects.emplace_back(object);
    }

    size_t Environment::Size() const
    {
        return m_objects.size();
    }

    std::vector<std::shared_ptr<IHittable>> Environment::Objects() const
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