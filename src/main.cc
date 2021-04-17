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
    auto texture = Texture({1, 1, 15});

// ################################# SIMPLE SHAPES #############################
    auto material_1 = std::make_shared<UniformTexture>(texture, ColorRGB(0,  0, 255));
    auto torus_1 = std::make_shared<Torus>(Point3<>({10, 0, -6}), 3, 1, material_1);

    auto material_2= std::make_shared<UniformTexture>(texture, ColorRGB(255,  0, 0));
    auto cylinder_2 = std::make_shared<Cylinder>(Point3<>({10, 0, 5}),Point3<>({10, 5, 1.2}), 1, material_2);

    auto material_3 = std::make_shared<UniformTexture>(texture, ColorRGB(0,  255, 0));
    auto capsule_3 = std::make_shared<Capsule>(Point3<>({5, -4, -1}),Point3<>({5, -2, -3}), 1, material_3);

    auto material_4= std::make_shared<UniformTexture>(texture, ColorRGB(255,  255, 0));
    auto cube_4 = std::make_shared<Cube>(Point3<>({15, -5, 1}),Point3<>({2, 2, 2}), material_4);

    auto material_5 = std::make_shared<UniformTexture>(texture, ColorRGB(85,107,47));
    auto sphere_5 = std::make_shared<Sphere>(Point3<>({3, 0, 5}), 1, material_5);

    auto material_6 = std::make_shared<UniformTexture>(texture, ColorRGB(76,  251, 194));
    auto sphere_6 = std::make_shared<Sphere>(Point3<>({5, 0, 5}), 2, material_6);

    auto material_7 = std::make_shared<UniformTexture>(texture, ColorRGB(193,248,144));
    auto sphere_7 = std::make_shared<Sphere>(Point3<>({15, 5, -4}), 2, material_7);

    auto material_8 = std::make_shared<UniformTexture>(texture, ColorRGB(72,28,229));
    auto sphere_8 = std::make_shared<Sphere>(Point3<>({15, 4, -3}), 2, material_8);

    auto material_9 = std::make_shared<UniformTexture>(texture, ColorRGB(100,154,213));
    auto sphere_9 = std::make_shared<Sphere>(Point3<>({25, 10, -1}), 3, material_9);

    auto material_10= std::make_shared<UniformTexture>(texture, ColorRGB(46,254,96));
    auto cube_10 = std::make_shared<Cube>(Point3<>({25, 10, 1}),Point3<>({2, 2, 2}), material_10);

// ########### ADDING OBJECTS TO THE SCENE #####################################
    scene.addObject(torus_1);
    scene.addObject(cylinder_2);
    scene.addObject(capsule_3);
    scene.addObject(cube_4);

// ######################## CREATE OPERATORS ###################################
    auto sub = std::make_shared<Subtraction>(sphere_5, sphere_6, material_5);
    auto inter = std::make_shared<Intersection>(sphere_7, sphere_8, material_7);
    auto unio = std::make_shared<Union>(cube_10, sphere_9, material_9);

// ######################## ADDING OPERATORS TO THE SCENE ######################
    scene.addObject(sub);
    scene.addObject(inter);
    scene.addObject(unio);

// ############################# PLANES ########################################
    auto texturePlane = Texture({1, 0.1, 15});

    auto material_11= std::make_shared<CheckeredPatternTexture>(texturePlane, ColorRGB(255,255,255), ColorRGB(100,100,100));
    auto plane_11 = std::make_shared<Plane>(Vector3<>({0, 1, 0}), 50.0, material_11);

    auto material_12= std::make_shared<UniformTexture>(texturePlane, ColorRGB(100,154,213));
    auto plane_12 = std::make_shared<Plane>(Vector3<>({0, -1, 0}), 50.0, material_12);

    auto material_13 = std::make_shared<UniformTexture>(texturePlane, ColorRGB(34, 145, 112));
    auto plane_13 = std::make_shared<Plane>(Vector3<>({0, 0, 1}), 50.0, material_13);

    auto material_14 = std::make_shared<UniformTexture>(texturePlane, ColorRGB(170, 152, 14));
    auto plane_14 = std::make_shared<Plane>(Vector3<>({0, 0, -1}), 50.0, material_14);

    auto material_15 = std::make_shared<UniformTexture>(texturePlane, ColorRGB(123, 94, 232));
    auto plane_15 = std::make_shared<Plane>(Vector3<>({-1, 0, 0}),50.0, material_15);

// ########### ADDING PLANES TO THE SCENE ######################################
    scene.addObject(plane_11);
    scene.addObject(plane_12);
    scene.addObject(plane_13);
    scene.addObject(plane_14);
    scene.addObject(plane_15);

// ########## SCENE LIGHT - POSSIBLE TO ADD MULTIPLE ONES ######################
    auto light1 = std::make_shared<PointLight>(Point3<>({0,0, 0}));

// ############# ADDING LIGHT TO THE SCENE #####################################
    scene.addLight(light1);

    auto resolution = vm["resolution"].as<unsigned >();

// ##################### ANIMATION #############################################
// USEFUL FOR THE ANIMATION - CHANGE IF YOU WANT FRAMES FOR AN ANIMATED SEQUENCE
// START: BEGINNING OF THE POSITION OF THE CAMERA (CAMERA.Z)
// END: LAST POSITION OF THE CAMERA (CAMERA.Z)
// INCREMENT: USEFUL FOR THE NUMBER OF FPS YOU WISH TO HAVE
    double start = -10.0;
    double end = 10.0;
    double increment = 0.1;
    for (double i = start; i <= end; i += increment) {
        auto camera = Camera(
                Point3<>({-2, 5, i}),
                Point3<>({8, 0, 0}),
                Vector3<>({0, 1, 0}),
                M_PI / 2,
                M_PI / 2,
                2.0
        );

// ####### OPERATORS - MOVING DEPENDING ON SIN(I) ##############################;
        sub->getSecondObject()->translate(Point3<>({std::sin(i), 0, 0}));
        inter->getSecondObject()->translate(Point3<>({0, std::sin(i), 0}));
        unio->getSecondObject()->translate(Point3<>({0, 0, std::sin(i)}));
        unio->getFirstObject()->translate(Point3<>({0, 0, - std::sin(i)}));

// ######### GENERATE THE CURRENT IMAGE AND SAVE IT ############################
        Image image(resolution, resolution);
        camera.generateImage(image, scene, vm["thread"].as<unsigned>());
        image.saveImage("RaymarcherDominiqueLea" + std::to_string((int) std::round((i + std::abs(start)) * (1.0/increment))) + ".ppm");

        std::cout << "Generated image " << "RaymarcherDominiqueLea" + std::to_string((int) std::round((i + std::abs(start)) * (1.0/increment))) + ".ppm" << std::endl;
    }

}