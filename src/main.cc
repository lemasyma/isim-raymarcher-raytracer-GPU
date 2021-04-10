#include <thread>

#include <scene/objects/sphere.hh>
#include <scene/objects/capsule.hh>
#include <scene/objects/torus.hh>
#include <scene/objects/cube.hh>
#include <scene/objects/cylinder.hh>

#include <scene/objects/operators/subtraction.hh>
#include <scene/objects/operators/intersection.hh>
#include <scene/objects/operators/union.hh>

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
            Point3<>({0, 5, -2}),
            Point3<>({8, 0, 0}),
            Vector3<>({0, 1, 0}),
            M_PI / 2,
            M_PI / 2,
            2.0
    );
    auto scene = Scene();

    auto texture = Texture({1, 1, 15});

    auto material_1 = std::make_shared<UniformTexture>(texture, ColorRGB(0,  0, 255));
    auto torus_1 = std::make_shared<Torus>(Point3<>({10, 0, -4}), 3, 1, material_1);

    auto material_2= std::make_shared<UniformTexture>(texture, ColorRGB(255,  0, 0));
    auto cylinder_2 = std::make_shared<Cylinder>(Point3<>({10, 0, 5}),Point3<>({10, 5, 1.2}), 1, material_2);

    auto material_3 = std::make_shared<UniformTexture>(texture, ColorRGB(0,  255, 0));
    auto capsule_3 = std::make_shared<Capsule>(Point3<>({5, -3, -1}),Point3<>({5, -2, -3}), 1, material_3);

    auto material_4= std::make_shared<UniformTexture>(texture, ColorRGB(255,  255, 0));
    auto cube_4 = std::make_shared<Cube>(Point3<>({15, -5, 1}),Point3<>({2, 2, 2}), material_4);

    auto material_5 = std::make_shared<UniformTexture>(texture, ColorRGB(85,107,47));
    auto sphere_5 = std::make_shared<Sphere>(Point3<>({3, 0, 3}), 1, material_5);

    auto material_6 = std::make_shared<UniformTexture>(texture, ColorRGB(76,  251, 194));
    auto sphere_6 = std::make_shared<Sphere>(Point3<>({5, 0, 3}), 2, material_6);

    auto material_7 = std::make_shared<UniformTexture>(texture, ColorRGB(193,248,144));
    auto sphere_7 = std::make_shared<Sphere>(Point3<>({20, 1, -4}), 2, material_7);

    auto material_8 = std::make_shared<UniformTexture>(texture, ColorRGB(72,28,229));
    auto sphere_8 = std::make_shared<Sphere>(Point3<>({20, 0, -3}), 2, material_8);

    auto material_9 = std::make_shared<UniformTexture>(texture, ColorRGB(100,154,213));
    auto sphere_9 = std::make_shared<Sphere>(Point3<>({30, 10, -1}), 3, material_9);

    auto material_10= std::make_shared<UniformTexture>(texture, ColorRGB(46,254,96));
    auto cube_10 = std::make_shared<Cube>(Point3<>({30, 10, 1}),Point3<>({2, 2, 2}), material_10);

    auto sub = std::make_shared<Subtraction>(sphere_5, sphere_6, material_5);
    auto inter = std::make_shared<Intersection>(sphere_7, sphere_8, material_7);
    auto unio = std::make_shared<Union>(cube_10, sphere_9, material_9);

    auto light1 = std::make_shared<PointLight>(Point3<>({0,0, 0}));

    scene.addObject(torus_1);
    scene.addObject(cylinder_2);
    scene.addObject(capsule_3);
    scene.addObject(cube_4);
    scene.addObject(sub);
    scene.addObject(inter);
    scene.addObject(unio);
    scene.addLight(light1);

    auto resolution = vm["resolution"].as<unsigned >();

    Image image(resolution, resolution);
    camera.generateImage(image, scene, vm["thread"].as<unsigned>());
    image.saveImage("output.ppm");
}