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

using Component = std::variant<TransformComponent>;

template<typename>
static inline constexpr std::size_t tuple_size_v;

template<typename... Ts>
static inline constexpr std::size_t tuple_size_v<std::variant<Ts...>> = sizeof...(Ts);

struct GameObject {
	boost::container::small_vector<Component, tuple_size_v<Component>> _components;

public:
	GameObject() = default;
	GameObject(GameObject&&) = default;

	template<typename T, typename... Args>
	void addComponent(Args&&... args) {
		_components.emplace_back(std::in_place_type<T>, std::forward<Args>(args)...);
	}

	void update() {
		for (auto& component : _components) {
			std::visit([](auto&& c){c.update();}, component);
		}
	}
};

}

std::array<std::chrono::duration<float, std::milli>, 2> static_polymorph_game_object(std::size_t n) {
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
