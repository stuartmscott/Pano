// Copyright 2026 Stuart Scott
#ifndef TEST_INCLUDE_PANOTEST_APP_H_
#define TEST_INCLUDE_PANOTEST_APP_H_

#include <Pano/app.h>
#include <Pano/window.h>
#include <PanoMaterialColor/provider.h>
#include <PanoMaterialIcon/provider.h>
#include <PanoNotoSans/provider.h>
#include <gtest/gtest.h>

#include <condition_variable>
#include <mutex>
#include <thread>

class AppTest : public ::testing::Test {
 public:
  static void SetUpTestSuite() {
    runner_ = std::thread{[]() {
      SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
      app_ = new Pano::App();
      ASSERT_NE(app_, nullptr);
      app_->SetColorProvider(CreateLightMaterialColorProvider());
      app_->SetIconProvider(CreateMaterialIconProvider());
      app_->SetFontProvider(CreateNotoSansProvider());
      {
        std::lock_guard<std::mutex> guard(mutex_);
        condition_.notify_all();
      }
      app_->Start();
    }};
    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock, [] { return app_ != nullptr; });
  }

  static void TearDownTestSuite() {
    if (app_ != nullptr) {
      app_->Quit();
    }
    runner_.join();
    if (app_ != nullptr) {
      delete app_;
      app_ = nullptr;
    }
  }

  static std::mutex mutex_;
  static std::condition_variable condition_;
  static std::thread runner_;
  static Pano::App* app_;
};

std::mutex AppTest::mutex_;
std::condition_variable AppTest::condition_;
std::thread AppTest::runner_;
Pano::App* AppTest::app_{nullptr};

#endif  // TEST_INCLUDE_PANOTEST_APP_H_
