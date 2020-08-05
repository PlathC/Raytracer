
#include <chrono>
#include <iostream>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include "Raytracer/Object/Plane.hpp"
#include "Raytracer/Object/ConstantDensityMedium.hpp"
#include "Raytracer/Object/Triangle.hpp"
#include "Raytracer/Object/TriangleMesh.hpp"
#include "Raytracer/Material/Lambertian.hpp"
#include "Raytracer/Material/DiffuseLight.hpp"
#include "Raytracer/Material/SolidColor.hpp"
#include "Raytracer/Material/Metal.hpp"
#include "Raytracer/Utils/Loader/ObjLoader.hpp"
#include "Raytracer/Utils/Renderer.hpp"

int main(int /*argc*/, char** /*argv*/)
{
    std::cout << "Setup render..." << std::endl;

    auto timeStart = std::chrono::high_resolution_clock::now();
    auto scene = rt::Scene::Suzanne();
    auto timeEnd = std::chrono::high_resolution_clock::now();
    auto passedTime = std::chrono::duration<double, std::milli>(timeEnd - timeStart).count();

    std::cout << "Setup done in : " << passedTime << "ms" << std::endl;

    rt::Renderer renderer = rt::Renderer { scene };

    std::cout << "Launch render !" << std::endl;

    timeStart = std::chrono::high_resolution_clock::now();
    renderer.GenerateImage();
    timeEnd = std::chrono::high_resolution_clock::now();
    passedTime = std::chrono::duration<double, std::milli>(timeEnd - timeStart).count();

    std::cout << "Renderer done in : " << passedTime << "ms" << std::endl;

    auto img = renderer.GeneratedImage();
    auto result = std::vector<uint8_t>(img.size());
    size_t i = 0;
    for(const auto p : img)
    {
        result[i++] = static_cast<uint8_t>(p * 256);
    }
    stbi_write_png("output.png", scene.imageSettings.width, scene.imageSettings.height, scene.imageSettings.channels,
                   result.data(),  scene.imageSettings.width * scene.imageSettings.channels);

#ifdef RAYTRACER_WITH_OID
    renderer.Denoise();

    auto filtered = renderer.DenoisedImage();
    auto filteredResult = std::vector<uint8_t>(filtered.size());
    i = 0;
    for(const auto p : filtered)
    {
        filteredResult[i++] = static_cast<uint8_t>(p * 255);
    }
    stbi_write_png("outputDenoised.png", scene.imageSettings.width, scene.imageSettings.height, scene.imageSettings.channels,
                   filteredResult.data(),  scene.imageSettings.width * scene.imageSettings.channels);
#endif // RAYTRACER_WITH_OID

    return EXIT_SUCCESS;
}