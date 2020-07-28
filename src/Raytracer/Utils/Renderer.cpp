//
// Created by Platholl on 28/06/2020.
//
#ifdef RAYTRACER_WITH_OID
#include <OpenImageDenoise/oidn.hpp>
#endif // RAYTRACER_WITH_OID

#include "Raytracer/Utils/Renderer.hpp"

namespace rt
{
    Renderer::Renderer(const Scene &settings):
            m_settings(settings),
            m_bvh(settings.environment, m_settings.camera.Time0(), m_settings.camera.Time1()),
            m_generatedImage(m_settings.imageSettings.width * m_settings.imageSettings.height * m_settings.imageSettings.channels),
            m_albedoImage(m_settings.imageSettings.width * m_settings.imageSettings.height * m_settings.imageSettings.channels)
    {
    }

    void Renderer::GenerateImage()
    {
        ThreadPool pool;

        struct Pixel
        {
            float x;
            float y;
            float z;
        };

        struct PixelValues
        {
            Pixel resultPixel;
            Pixel albedoPixel;
        };

        auto pixelGeneration = [&](uint32_t j, uint32_t i, const Scene& settings) -> PixelValues
        {
            glm::vec3 result = glm::vec3 {};
            glm::vec3 albedo = glm::vec3 {};

            for(int16_t s = 0; s < settings.samplesPerPixel; ++s)
            {
                const int32_t width  = settings.imageSettings.width;
                const int32_t height = settings.imageSettings.height;

                auto u = static_cast<float>((i + rt::Random<float>()) / (width - 1.f));
                auto v = static_cast<float>((j + rt::Random<float>()) / (height - 1.f));

                rt::Ray ray = settings.camera.GetRay(u, v);
                result += RayColor(ray, m_bvh, settings.maxDepth);
                if(s == 0)
                {
                    albedo = result;
                }
            }

            // Divide the color total by the number of samples and gamma-correct for gamma=2.0.
            auto scale = 1.0 / m_settings.samplesPerPixel;
            auto r = static_cast<float>(std::sqrt(scale * result.x));
            auto g = static_cast<float>(std::sqrt(scale * result.y));
            auto b = static_cast<float>(std::sqrt(scale * result.z));

            return { {
                             static_cast<float>(rt::Clamp(r, 0.0, 0.999)),
                             static_cast<float>(rt::Clamp(g, 0.0, 0.999)),
                             static_cast<float>(rt::Clamp(b, 0.0, 0.999)) },
                     {
                             static_cast<float>(rt::Clamp(albedo.x, 0.0, 0.999)),
                             static_cast<float>(rt::Clamp(albedo.y, 0.0, 0.999)),
                             static_cast<float>(rt::Clamp(albedo.z, 0.0, 0.999)) }
            };
        };

        std::vector<std::future<PixelValues>> results {m_generatedImage.size()};
        size_t imageIterator = 0, albedoIterator = 0, pixelIterator = 0;
        int32_t height = m_settings.imageSettings.height;
        int32_t width = m_settings.imageSettings.width;

        for (int32_t j = height-1; j >= 0; --j)
        {
            for (int32_t i = 0; i < width; ++i)
            {
                results[pixelIterator++] = pool.AddTask(pixelGeneration, j, i, m_settings);
            }
        }
        pixelIterator = 0;

        for (int32_t j = height-1; j >= 0; --j)
        {
            for (int32_t i = 0; i < width; ++i)
            {
                try
                {
                    auto p =  results[pixelIterator++].get();
                    m_generatedImage[imageIterator++] = p.resultPixel.x;
                    m_generatedImage[imageIterator++] = p.resultPixel.y;
                    m_generatedImage[imageIterator++] = p.resultPixel.z;

                    m_albedoImage[albedoIterator++] = p.albedoPixel.x;
                    m_albedoImage[albedoIterator++] = p.albedoPixel.y;
                    m_albedoImage[albedoIterator++] = p.albedoPixel.z;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
    }

#ifdef RAYTRACER_WITH_OID
    void Renderer::Denoise()
    {
        oidn::DeviceRef device = oidn::newDevice();

        const char* errorMessage;
        if (device.getError(errorMessage) != oidn::Error::None)
        {
            throw std::runtime_error(errorMessage);
        }

        device.setErrorFunction( [] (void* /*userPtr*/, oidn::Error /*error*/, const char* message) {
            throw std::runtime_error(message);
        });

        device.commit();

        // Create a denoising filter
        oidn::FilterRef filter = device.newFilter("RT"); // generic ray tracing filter
        m_denoisedImage = std::vector<float>(m_generatedImage.size());

        filter.setImage("color",  m_generatedImage.data(),  oidn::Format::Float3,
                        m_settings.imageSettings.width, m_settings.imageSettings.height);

        filter.setImage("output", m_denoisedImage.data(), oidn::Format::Float3,
                        m_settings.imageSettings.width, m_settings.imageSettings.height);

        filter.set("hdr", false);
        filter.commit();
        filter.execute();
    }
#endif // RAYTRACER_WITH_OID

    std::vector<float> Renderer::GeneratedImage() const
    {
        return m_generatedImage;
    }

    std::vector<float> Renderer::AlbedoImage() const
    {
        return m_albedoImage;
    }

#ifdef RAYTRACER_WITH_OID
    std::vector<float> Renderer::DenoisedImage() const
    {
        return m_denoisedImage;
    }
#endif // RAYTRACER_WITH_OID

    glm::vec3 Renderer::RayColor(const rt::Ray& ray, const rt::IHittable& world, int depth) const
    {
        rt::HitRecord record{};

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