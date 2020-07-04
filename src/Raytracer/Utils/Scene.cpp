//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Utils/Scene.hpp"

namespace rt
{
    Scene::Scene(const SceneSettings &settings, Environment&& environment):
            m_settings(settings),
            m_environment(std::move(environment))
    {}

    std::vector<uint8_t> Scene::GenerateImage()
    {
        const uint32_t width  = m_settings.imageSettings.width;
        const uint32_t height = m_settings.imageSettings.height;
        const uint8_t channel = m_settings.imageSettings.channels;

        auto img = std::vector<uint8_t>(width * height * channel);
        size_t imageIterator = 0;

        for (int j = height-1; j >= 0; --j)
        {
            for (int i = 0; i < width; ++i)
            {
                rt::Color pixel = rt::Color(0., 0. , 0.);

                for(uint16_t s = 0; s < m_settings.samplesPerPixel; ++s)
                {
                    auto u = (i + rt::RandomDouble()) / (width - 1);
                    auto v = (j + rt::RandomDouble()) / (height - 1);

                    rt::Ray ray = m_settings.camera.GetRay(u, v);
                    pixel += RayColor(ray, m_environment, m_settings.maxDepth);
                }
                auto r = pixel.X();
                auto g = pixel.Y();
                auto b = pixel.Z();

                // Divide the color total by the number of samples and gamma-correct for gamma=2.0.
                auto scale = 1.0 / m_settings.samplesPerPixel;
                r = std::sqrt(scale * r);
                g = std::sqrt(scale * g);
                b = std::sqrt(scale * b);

                img[imageIterator++] = static_cast<uint8_t>(256 * rt::Clamp(r, 0.0, 0.999));
                img[imageIterator++] = static_cast<uint8_t>(256 * rt::Clamp(g, 0.0, 0.999));
                img[imageIterator++] = static_cast<uint8_t>(256 * rt::Clamp(b, 0.0, 0.999));
            }
        }
        return img;
    }

    rt::Color Scene::RayColor(const rt::Ray& ray, const rt::Hittable& world, const int depth) const
    {
        rt::HitRecord record;

        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return rt::Color(0., 0, 0.);

        if (world.Hit(ray, 1e-08, rt::Infinity, record))
        {
            rt::Ray scattered;
            rt::Color attenuation;
            if(record.material)
            {
                if (record.material->Scatter(ray, record, attenuation, scattered))
                    return attenuation * RayColor(scattered, world, depth-1);
            }
            else
            {
                return rt::Color(1.,0,1.);
            }

            return rt::Color(0,0,0);
        }

        rt::Vec3 unitDirection = rt::UnitVector(ray.Direction());
        double t = 0.5*(unitDirection.Z() + 1.0);

        // Linear interpolation to create skybox
        return (1.0-t) * rt::Color(1., 1., 1.) + t * rt::Color(.2, 0., 1.0);
    }

}