#include <vector>
#include <variant>
#include <utility>
#include <chrono>
#include <array>

#include "boost/container/small_vector.hpp"

namespace cxx_adc_2023_day10 {

namespace {

struct TransformComponent {
	float _x, _y, _z;

	TransformComponent(float x = 0, float y = 0, float z = 0) : _x(x), _y(y), _z(z) {}

	void update() {
		_x += 1.0f;
		_y += 1.0f;
		_z += 1.0f;
	}
};

struct GameObject {
	virtual void update() = 0;
	virtual ~GameObject() = default;
};

struct SomeObject : GameObject {
	TransformComponent transform;
public:
	SomeObject(const TransformComponent& t) : transform{t}{}
	SomeObject(SomeObject&&) = default;

	void update() override {
		transform.update();
	}
};

}

std::array<std::chrono::duration<float, std::milli>, 2> old_style_game_object(std::size_t n) {
	const auto start_creation = std::chrono::high_resolution_clock::now();

	std::vector<std::shared_ptr<GameObject>> gameObjects;
	// gameObject(1000000)とするのはフェアじゃなさそうなので1つずつpush_backしてます。
	for (size_t i = 0; i < n; ++i)
	{
		gameObjects.emplace_back(std::make_shared<SomeObject>(TransformComponent{1.f, 2.f, 3.f}));
	}
	const auto stop_creation = std::chrono::high_resolution_clock::now();
	const auto duration_creation = std::chrono::duration<float, std::milli>{stop_creation - start_creation};

	const auto start_modification = std::chrono::high_resolution_clock::now();

	for (auto& gameObject : gameObjects) {
		gameObject->update();
	}
	const auto stop_modification = std::chrono::high_resolution_clock::now();
	const auto duration_modification = std::chrono::duration<float, std::milli>{stop_modification - start_modification};

	return {duration_creation, duration_modification};
}

}
