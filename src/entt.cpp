// original: https://qiita.com/naritancorp/items/0377004000388ea695da

#include <entt/entt.hpp>
#include <chrono>
#include <array>
#include <cstddef>

namespace cxx_adc_2023_day10 {

namespace {

struct TransformComponent {
	float _x, _y, _z;

	TransformComponent(float x = 0, float y = 0, float z = 0) : _x(x), _y(y), _z(z) {}
};

}

std::array<std::chrono::duration<float, std::milli>, 2> entt(std::size_t n) {
	entt::registry registry;
	const auto start_creation = std::chrono::high_resolution_clock::now();

	for (std::size_t i = 0; i < n; ++i)
	{
		entt::entity entity = registry.create();
		registry.emplace<TransformComponent>(entity, 1.0f, 2.0f, 3.0f);
	}

	const auto stop_creation = std::chrono::high_resolution_clock::now();
	const auto duration_creation = std::chrono::duration<float, std::milli>{stop_creation - start_creation};

	const auto start_modification = std::chrono::high_resolution_clock::now();

	for (auto [entity, transform] : registry.view<TransformComponent>().each()) {
		transform._x += 1.0f;
		transform._y += 1.0f;
		transform._z += 1.0f;
	}

	const auto stop_modification = std::chrono::high_resolution_clock::now();
	const auto duration_modification = std::chrono::duration<float, std::milli>{stop_modification - start_modification};

	return {duration_creation, duration_modification};
}

}
