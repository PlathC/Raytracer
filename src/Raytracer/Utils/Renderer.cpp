//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Utils/Renderer.hpp"

#include <omp.h>

namespace rt
{
    Renderer::Renderer(const SceneSettings &settings, Environment environment):
            m_settings(settings),
            m_environment(std::move(environment)),
            m_bvh(m_environment, m_settings.camera.Time0(), m_settings.camera.Time1())
    {
    }

    std::vector<uint8_t> Renderer::GenerateImage()
    {
        const int32_t width  = m_settings.imageSettings.width;
        const int32_t height = m_settings.imageSettings.height;
        const uint8_t channel = m_settings.imageSettings.channels;

        auto img = std::vector<uint8_t>(width * height * channel);
        size_t imageIterator = 0;

        for (int32_t j = height-1; j >= 0; --j)
        {
            for (int32_t i = 0; i < width; ++i)
            {
                glm::vec3 pixel = glm::vec3 {};

                for(int16_t s = 0; s < m_settings.samplesPerPixel; ++s)
                {
                    auto u = (i + rt::Random<double>()) / (width - 1);
                    auto v = (j + rt::Random<double>()) / (height - 1);

                    rt::Ray ray = m_settings.camera.GetRay(u, v);
                    pixel += RayColor(ray, m_bvh, m_settings.maxDepth);
                }

                // Divide the color total by the number of samples and gamma-correct for gamma=2.0.
                auto scale = 1.0 / m_settings.samplesPerPixel;
                float r = std::sqrt(scale * pixel.x);
                float g = std::sqrt(scale * pixel.y);
                float b = std::sqrt(scale * pixel.z);

                img[imageIterator++] = static_cast<uint8_t>(256 * rt::Clamp(r, 0.0, 0.999));
                img[imageIterator++] = static_cast<uint8_t>(256 * rt::Clamp(g, 0.0, 0.999));
                img[imageIterator++] = static_cast<uint8_t>(256 * rt::Clamp(b, 0.0, 0.999));
            }
        }
        return img;
    }

    glm::vec3 Renderer::RayColor(const rt::Ray& ray, const rt::IHittable& world, const int depth) const
    {
        rt::HitRecord record;

        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return glm::vec3(0., 0., 0.);

        if(!world.Hit(ray, 0.001, rt::Infinity<double>, record))
            return m_settings.backgroundColor;

        rt::Ray scattered;
        glm::vec3 attenuation;

        if(!record.material)
        {
            // TODO: Store default color
            return glm::vec3(1., 0, 1.);
        }
        else
        {
            glm::vec3 emitted = record.material->Emitted(record.uv, record.point);

            if (!record.material->Scatter(ray, record, attenuation, scattered))
                return emitted;

            return emitted + attenuation * RayColor(scattered, world, depth-1);
        }
    }

}