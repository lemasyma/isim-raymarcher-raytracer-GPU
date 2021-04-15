#include <thread>

#include <scene/objects/sphere.hh>
#include <scene/objects/capsule.hh>
#include <scene/objects/torus.hh>
#include <scene/objects/cube.hh>
#include <scene/objects/cylinder.hh>
#include <scene/objects/plane.hh>

#include <scene/objects/operators/subtraction.hh>
#include <scene/objects/operators/intersection.hh>
#include <scene/objects/operators/union.hh>

#include <scene/light/pointLight.hh>
#include "scene/camera.hh"
#include "scene/material/uniformTexture.hh"
#include "scene/material/checkeredPatternTexture.hh"
#include "main.hh"

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    try {
        auto const& desc = define_options();
        auto const& vm = parse_options(desc, argc, argv);
        run(desc, vm);
    } catch (po::error &e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return 2;
    }
    return 0;
}

po::options_description define_options()
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "show usage");
    desc.add_options()
            ("resolution,r",
             po::value<unsigned>()->default_value(500),
             "height width specify wanted resolution");
    desc.add_options()
            ("thread,t",
             po::value<unsigned>()->default_value(std::max(std::thread::hardware_concurrency() - 1, 1U)),
             "height width specify wanted resolution");
    return desc;
}

po::variables_map parse_options(const po::options_description& desc, int argc,
        char** argv)
{
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    return vm;
}

void run(const po::options_description& desc, const po::variables_map& vm)
{
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return;
    }

    auto scene = Scene();

    auto camera = Camera(
            Point3<>({0, 0, 0}),
            Point3<>({8, 0, 0}),
            Vector3<>({0, 1, 0}),
            M_PI / 2,
            M_PI / 2,
            2.0
    );

    auto texturePlane = Texture({1, 0.1, 15});
    auto textureSphere = Texture({1, 0.35, 15});

    auto material_1= std::make_shared<CheckeredPatternTexture>(texturePlane, ColorRGB(255,255,255), ColorRGB(100,100,100));
    auto plane_1 = std::make_shared<Plane>(Vector3<>({0, 1, 0}), 10.0, material_1);

    auto material_2= std::make_shared<UniformTexture>(texturePlane, ColorRGB(100,154,213));
    auto plane_2 = std::make_shared<Plane>(Vector3<>({0, -1, 0}), 10.0, material_2);
//
    auto material_3 = std::make_shared<UniformTexture>(texturePlane, ColorRGB(34, 145, 112));
    auto plane_3 = std::make_shared<Plane>(Vector3<>({0, 0, 1}), 10.0, material_3);

    auto material_4 = std::make_shared<UniformTexture>(texturePlane, ColorRGB(170, 152, 14));
    auto plane_4 = std::make_shared<Plane>(Vector3<>({0, 0, -1}), 10.0, material_4);

    auto material_5 = std::make_shared<UniformTexture>(texturePlane, ColorRGB(123, 94, 232));
    auto plane_5 = std::make_shared<Plane>(Vector3<>({-1, 0, 0}),20.0, material_5);

    auto light1 = std::make_shared<PointLight>(Point3<>({0,0, 0}));

    scene.addObject(plane_1);
    scene.addObject(plane_2);
//    scene.addObject(plane_3);
//    scene.addObject(plane_4);
    scene.addObject(plane_5);
    scene.addLight(light1);

    auto resolution = vm["resolution"].as<unsigned >();

//    Image image(resolution, resolution);
//    camera.generateImage(image, scene, vm["thread"].as<unsigned>());
//    image.saveImage("plane.ppm");

    double start = -16.0;
    double end = 16.0;
    double increment = 0.1;
    for (double i = start; i <= end; i += increment) {

        auto material_6 = std::make_shared<UniformTexture>(textureSphere, ColorRGB(85,107,47));
        auto sphere_6 = std::make_shared<Sphere>(Point3<>({15, 0, i}), 3, material_6);

        auto unio1 = std::make_shared<Union>(plane_3, sphere_6, material_5);
        auto unio2 = std::make_shared<Union>(plane_4, unio1, material_5);

        scene.addObject(unio1);
        scene.addObject(unio2);

        Image image(resolution, resolution);
        camera.generateImage(image, scene, vm["thread"].as<unsigned>());
        auto fileName = "plane" + std::to_string(((i + std::abs(start)) * (1/increment))) + ".ppm";
        image.saveImage(fileName);

        std::cout << "Generated image " << fileName << std::endl;

        scene.removeObject(unio1);
        scene.removeObject(unio2);
    }
}