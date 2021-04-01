#include <SDL2/SDL.h>
#include "../src/scene/scene.hh"
#include "../src/scene/camera.hh"

#define WINDOW_WIDTH 600

Scene createScene(const Camera& camera) {
    auto scene = Scene();
    return scene;
}

int main() {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    auto camera = Camera(
            Point3<>({0, 0, 0}),
            Point3<>({8, 0, 0}),
            Vector3<>({0, 1, 0}),
            M_PI / 2,
            M_PI / 2,
            2.0
    );
    auto scene = createScene(camera);
    Image image(WINDOW_WIDTH, WINDOW_WIDTH);
    while (true) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;

        SDL_RenderClear(renderer);
        int x = 0, y = 0;
        for (auto i = 0; i < WINDOW_WIDTH * WINDOW_WIDTH; ++i) {
            auto color = image.data_get()[i];
            SDL_SetRenderDrawColor(renderer, color.r_get(), color.g_get(), color.b_get(), 0);
            SDL_RenderDrawPoint(renderer, x, y);
            ++x;
            if (x == WINDOW_WIDTH) {
                x = 0;
                y += 1;
            }
        }
        camera.generateImage(image, scene, 6);
        SDL_RenderPresent(renderer);
        camera.translate(Point3<>({0.1, 0.15, 0.0}));
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}