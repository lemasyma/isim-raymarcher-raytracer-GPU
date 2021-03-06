#include <thread>

#include <scene/objects/sphere.hh>
#include <scene/objects/capsule.hh>
#include <scene/objects/torus.hh>
#include <scene/objects/cube.hh>
#include <scene/objects/cylinder.hh>

#include <scene/light/pointLight.hh>
#include "scene/camera.hh"
#include "scene/material/uniformTexture.hh"
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

    auto camera = Camera(
            Point3<>({0, 5, 0}),
            Point3<>({8, 0, 0}),
            Vector3<>({0, 1, 0}),
            M_PI / 2,
            M_PI / 2,
            2.0
    );
    auto scene = Scene();

    auto texture = Texture({1, 1, 15});

    auto material_1 = std::make_shared<UniformTexture>(texture, ColorRGB(0,  0, 255));
    auto torus_1 = std::make_shared<Torus>(Point3<>({10, 0, -1.2}), 3, 1, material_1);

    auto material_2= std::make_shared<UniformTexture>(texture, ColorRGB(255,  0, 0));
    auto cylinder_2 = std::make_shared<Cylinder>(Point3<>({10, 0, 5}),Point3<>({10, 5, 1.2}), 1, material_2);

    auto material_3 = std::make_shared<UniformTexture>(texture, ColorRGB(0,  255, 0));
    auto capsule_3 = std::make_shared<Capsule>(Point3<>({5, -3, -1}),Point3<>({5, -2, -3}), 1, material_3);

    auto material_4= std::make_shared<UniformTexture>(texture, ColorRGB(255,  255, 0));
    auto cube_4 = std::make_shared<Cube>(Point3<>({5, 0, 5}),Point3<>({1, 1, 1}), material_4);

    auto material_5 = std::make_shared<UniformTexture>(texture, ColorRGB(255,  0, 255));
    auto sphere_5 = std::make_shared<Sphere>(Point3<>({15, 10, 0}), 3, material_5);

    auto light1 = std::make_shared<PointLight>(Point3<>({0,0, 0}));

    scene.addObject(torus_1);
    scene.addObject(cylinder_2);
    scene.addObject(capsule_3);
    scene.addObject(cube_4);
    scene.addObject(sphere_5);
    scene.addLight(light1);

    auto resolution = vm["resolution"].as<unsigned >();

    Image image(resolution, resolution);
    camera.generateImage(image, scene, vm["thread"].as<unsigned>());
    image.saveImage("output.ppm");
}