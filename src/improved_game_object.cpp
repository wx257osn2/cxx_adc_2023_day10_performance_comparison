#include <vector>
#include <memory>
#include <chrono>
#include <utility>
#include <array>
#include <cstddef>

namespace cxx_adc_2023_day10 {

namespace {

class Component {
public:
	virtual void update() = 0;
	virtual ~Component() = default;
};

class TransformComponent : public Component {
public:
	float _x, _y, _z;

	TransformComponent(float x = 0, float y = 0, float z = 0) : _x(x), _y(y), _z(z) {}

	void update() override {
		_x += 1.0f;
		_y += 1.0f;
		_z += 1.0f;
	}
};

class GameObject {
private:
	std::vector<std::shared_ptr<Component>> _components;

public:
	GameObject() = default;
	GameObject(GameObject&&) = default;

	template<typename T, typename... Args>
	void addComponent(Args&&... args) {
		_components.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
	}

	void update() {
		for (auto& component : _components) {
			component->update();
		}
	}
};

}

std::array<std::chrono::duration<float, std::milli>, 2> improved_game_object(std::size_t n) {
	const auto start_creation = std::chrono::high_resolution_clock::now();

	std::vector<GameObject> gameObjects;
	// gameObject(1000000)とするのはフェアじゃなさそうなので1つずつpush_backしてます。
	for (size_t i = 0; i < n; ++i)
	{
		GameObject gameObject;
		gameObject.addComponent<TransformComponent>(1.0f, 2.0f, 3.0f);
		gameObjects.emplace_back(std::move(gameObject));
	}
	const auto stop_creation = std::chrono::high_resolution_clock::now();
	const auto duration_creation = std::chrono::duration<float, std::milli>{stop_creation - start_creation};

	const auto start_modification = std::chrono::high_resolution_clock::now();

	for (auto& gameObject : gameObjects) {
		gameObject.update();
	}
	const auto stop_modification = std::chrono::high_resolution_clock::now();
	const auto duration_modification = std::chrono::duration<float, std::milli>{stop_modification - start_modification};

	return {duration_creation, duration_modification};
}

}
