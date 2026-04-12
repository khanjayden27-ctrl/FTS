#include <SDL3/SDL.h>
#include <iostream>

struct Player {
    float x = 640.0f;
    float y = 360.0f;
    float speed = 200.0f;  // pixels per second
    float width = 32.0f;
    float height = 32.0f;
};
struct Tile {
    float x = 200.0f;
    float y = 200.0f;
    float width = 20.0f;
    float height = 20.0f;
};

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL Init failed: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("FTS", 1280, 720, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    Player player;
    Tile tile;

    bool running = true;
    SDL_Event event;

    // For delta time
    Uint64 lastTime = SDL_GetTicks();

    while (running) {
        // --- Delta Time ---
        Uint64 now = SDL_GetTicks();
        float dt = (now - lastTime) / 1000.0f;  // seconds
        lastTime = now;

        // --- Events ---
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_DOWN)
                if (event.key.key == SDLK_ESCAPE) running = false;
        }

        // --- Input ---
        const bool* keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_W]) player.y -= player.speed * dt;
        if (keys[SDL_SCANCODE_S]) player.y += player.speed * dt;
        if (keys[SDL_SCANCODE_A]) player.x -= player.speed * dt;
        if (keys[SDL_SCANCODE_D]) player.x += player.speed * dt;

        // --- Render ---
        // Clear screen (dark grey background)
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        // Draw player (white rectangle)
        SDL_FRect playerRect = { player.x, player.y, player.width, player.height };
        SDL_FRect TileTest = { tile.x, tile.y, tile.width, tile.height };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &playerRect);
        SDL_RenderFillRect(renderer, &TileTest);
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}