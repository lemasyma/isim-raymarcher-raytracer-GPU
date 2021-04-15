#include <thread>
#include "camera.hh"
#include "rayCaster.hh"

Camera::Camera(const Point3<> &position, const Point3<> &lookPoint, const Vector3<> &up,
               double vertAngle, double horizAngle, double distImage)
        : position_(position), lookPoint_(lookPoint), up_(up.normalize()),
          vertAngle_(vertAngle), horizAngle_(horizAngle), distImage_(distImage) {}

std::vector<Vector3<>> Camera::getViewVectors(unsigned rows, unsigned cols) const {
    auto image_w = 2.0 * distImage_ * tan(horizAngle_ / 2.0);
    auto image_h = 2.0 * distImage_ * tan(vertAngle_ / 2.0);
    auto unitx = image_w / cols;
    auto unity = image_w / rows;

    auto front = position_.vectorTo(lookPoint_).normalize();
    auto right_ = front.cross(up_).normalize();

    auto vectToBottom = up_ * -1 * (image_h / 2);
    auto vectToLeft = right_ * -1 * (image_w / 2);
    auto centerImage = position_ + (front * distImage_);
    auto bottomRight = centerImage + vectToBottom + vectToLeft;
    auto bottomRightPixel = bottomRight + (right_ * (unitx / 2)) + (up_ * (unity / 2));

    auto vectors = std::vector<Vector3<>>();
    vectors.reserve(cols * rows);

    for (auto y = 0U; y < rows; ++y) {
        for (auto x = 0U; x < cols; ++x) {
            auto pixelPoint = bottomRightPixel + (right_ * unitx * x) + (up_ * unity * y);
            vectors.emplace_back(position_.vectorTo(pixelPoint));
        }
    }

    return vectors;
}

ColorRGB Camera::getRayResult(const Point3<> &pos, const Vector3<> &dir, const Scene &scene) const {
    return RayCaster(scene, pos, dir, 2).getRayColor();
}

Image &Camera::generateImage(Image &image, const Scene &scene, unsigned threadCount) const {
    threadCount = std::max(threadCount, 1U);

    std::vector<unsigned> indexes{ 0 };
    for (auto i = 1U; i < threadCount; ++i)
        indexes.emplace_back((image.height_ / threadCount) * i);
    indexes.emplace_back(image.height_);

    // do threads
    std::vector<std::thread> threads{};
    auto vectors = getViewVectors(image.height_, image.width_);
    for (auto i = 0U; i < threadCount; ++i) {
        // execute THREADED row number
        auto exec = [&image, &scene, &vectors, &indexes, i, this]() {
            for (auto y = indexes[i]; y < indexes[i + 1]; ++y) {
                for (auto x = 0U; x < image.width_; ++x) {
                    ColorRGB &color = image.at(image.height_ - y - 1, x);
                    auto foundColor = getRayResult(position_, vectors[y * image.width_ + x], scene);
                    color.r_set(foundColor.r_get());
                    color.g_set(foundColor.g_get());
                    color.b_set(foundColor.b_get());
                }
            }
        };
        // execute last thread in current process instead having parent waiting doing nothing
        if (i == threadCount - 1)
            exec();
        else
            threads.emplace_back(exec);
    }

    for (auto& thread : threads)
        thread.join();

    return image;
}
