#include <gtest/gtest.h>
#include <fmt/format.h>
#include <memory>
#include <fstream>

struct Logger {
  virtual void log(std::string_view message) = 0;
  virtual ~Logger() = default;
};


struct ConsoleLogger final : Logger {
  void log(std::string_view message) override {
    fmt::println("{}", message);
  }
};

struct FileLogger final : Logger {
  FileLogger(const char* fileName) {
    fstream.open(fileName, std::ios::out);
    if (!fstream) {
      throw std::runtime_error("FileLogger initialization failed");
    }
  }

  FileLogger() : FileLogger{"test.txt"} {
    fstream.close();
  }
  void log(std::string_view message) override {
      fstream << message.data();
  }

  std::fstream fstream;
};

struct Animal {
  Animal(int weight) : _weight(weight) {}
  int _weight {0};
};

struct Lizard final : Animal {
  Lizard(int weight, int height) : Animal(weight), _height(height) {}
  int _height {0};
};


class TestOOP : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(TestOOP, testConstructor) {
  auto cl{std::make_unique<ConsoleLogger>()};
  Logger *logger{cl.get()};
  EXPECT_NE(logger, nullptr);
  EXPECT_EQ(sizeof(*logger), sizeof(void*));  // sizeof vptr
  logger->log("Hello world");
}

TEST_F(TestOOP, testPolymorphism) {

  auto logHelloWorld = [](Logger* logger) {
    logger->log("Hello World");
  };

  auto cl{std::make_unique<ConsoleLogger>()};
  Logger *clogger{cl.get()};

  auto fl{std::make_unique<FileLogger>()};
  Logger *flogger{fl.get()};

  logHelloWorld(clogger);
  logHelloWorld(flogger);

}

TEST_F(TestOOP, testSlicing) {

  Lizard lizard1{Lizard{100,200}};
  Lizard lizard2{Lizard{10,20}};

  Animal *a1 = &lizard1;
  Animal *a2 = &lizard2;

  *a1 = *a2; // slicing

  EXPECT_EQ(lizard1._weight, 10);
  EXPECT_NE(lizard1._height, 20);
  EXPECT_EQ(lizard1._height, 200);
}