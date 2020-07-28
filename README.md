# Raytracer

 Raytracer strongly based on the series 
 [Raytracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html).

## Features 

| Feature                          | Progress                                  |
|----------------------------------|-------------------------------------------|
| Raytraced primitive              | Done (Spheres, Triangles, Squares, Cubes) |
| Meshes                           | Done (Obj)                                |
| Multi-threading                  | Done (CPU)                                |
| Denoiser                         | Done                                      |
| PBR                              | Todo                                      |

## Results

After the first book, the result looked like this :

![](outputs/w-e1stResult.png)

Rendered meshes (OBJ) :

![](outputs/meshLoader.png)

BVH result (9s) :

![](outputs/BVHResult.png)

Final scene (Raytracing : The next week) :

![](outputs/FinalScene.png)

Denoise with OpenImageDenoise :

![](outputs/noise2.png)![](outputs/noise1.png) 

## Based on

[_ScratchaPixel_](https://www.scratchapixel.com/)

[_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

[_Ray Tracing: The Next Week_](https://raytracing.github.io/books/RayTracingTheNextWeek.html)

[_Ray Tracing: The Rest of Your Life_](https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html)

[_ThreadPool_](https://vorbrodt.blog/2019/02/12/simple-thread-pool/)