// Copyright 2026 Stuart Scott
#ifndef TEST_INCLUDE_PANOTEST_GOLDEN_H_
#define TEST_INCLUDE_PANOTEST_GOLDEN_H_

#include <SDL3_image/SDL_image.h>

#include <filesystem>
#include <string>

const std::filesystem::path GoldenPath = "../../../data/golden/";

void CheckGolden(std::string filename) {
  const auto GoldenSurface{SDL_LoadPNG((GoldenPath / filename).c_str())};
  if (GoldenSurface == nullptr) {
    ADD_FAILURE() << "Failed to load Golden Image: " << SDL_GetError();
    return;
  }

  const auto SnapshotSurface{SDL_LoadPNG(filename.c_str())};
  if (SnapshotSurface == nullptr) {
    ADD_FAILURE() << "Failed to load Snapshot Image: " << SDL_GetError();
    SDL_DestroySurface(GoldenSurface);
    return;
  }

  const auto w{GoldenSurface->w};
  const auto h{GoldenSurface->h};

  if (w != SnapshotSurface->w || h != SnapshotSurface->h) {
    ADD_FAILURE() << "Incorrect snapshot dimensions";
    SDL_DestroySurface(GoldenSurface);
    SDL_DestroySurface(SnapshotSurface);
    return;
  } else {
    const auto DiffSurface{SDL_CreateSurface(w, h * 3, GoldenSurface->format)};

    auto success{true};

    const auto count{static_cast<size_t>(w * h)};
    const auto GoldenPixels{(Uint32*)GoldenSurface->pixels};
    const auto SnapshotPixels{(Uint32*)SnapshotSurface->pixels};
    const auto DiffPixels{(Uint32*)DiffSurface->pixels};
    const auto details{SDL_GetPixelFormatDetails(GoldenSurface->format)};
    const auto error{SDL_MapRGB(details, nullptr, 255, 0, 0)};
    for (size_t i{0}; i < count; ++i) {
      const auto gp{GoldenPixels[i]};
      DiffPixels[i] = gp;
      const auto sp{SnapshotPixels[i]};
      DiffPixels[i + count] = sp;
      if (gp == sp) {
        DiffPixels[i + count + count] = gp;
      } else {
        DiffPixels[i + count + count] = error;
        success = false;
      }
    }

    if (!success) {
      if (!SDL_SavePNG(DiffSurface, ("diff_" + filename).c_str())) {
        ADD_FAILURE() << "Failed to save Diff Image: " << SDL_GetError();
      }
    }
    SDL_DestroySurface(DiffSurface);
    SDL_DestroySurface(GoldenSurface);
    SDL_DestroySurface(SnapshotSurface);

    EXPECT_TRUE(success);
  }
}

#endif  // TEST_INCLUDE_PANOTEST_GOLDEN_H_
