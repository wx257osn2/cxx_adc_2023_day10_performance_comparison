#include <array>
#include <chrono>
#include <cstddef>

namespace cxx_adc_2023_day10 {

std::array<std::chrono::duration<float, std::milli>, 2> game_object(std::size_t n);
std::array<std::chrono::duration<float, std::milli>, 2> entt(std::size_t n);
std::array<std::chrono::duration<float, std::milli>, 2> improved_game_object(std::size_t n);
std::array<std::chrono::duration<float, std::milli>, 2> static_polymorph_game_object(std::size_t n);
std::array<std::chrono::duration<float, std::milli>, 2> old_style_game_object(std::size_t n);

}

#include <algorithm>
#include <vector>

template<std::array<std::chrono::duration<float, std::milli>, 2> (*F)(std::size_t)>
static std::array<std::chrono::duration<float, std::milli>, 2> median(std::size_t n, std::size_t m) {
	if (m == 0)
		return {};
	std::vector<std::array<std::chrono::duration<float, std::milli>, 2>> vec(m);
	F(n);  // warmup
	for(auto&& x : vec)
		x = F(n);
	std::ranges::sort(vec, [](const auto& a, const auto& b){return a[1] < b[1];});
	return m % 2 == 0 ? std::array{(vec[m/2][0] + vec[m/2+1][0])/2.f, (vec[m/2][1] + vec[m/2+1][1])/2.f} : vec[m/2];
}

#include <iostream>

int main(){
	static constexpr std::size_t n = 1000000;
#ifdef NDEBUG
	static constexpr std::size_t m = 11;
#else
	static constexpr std::size_t m = 3;
#endif
	{
		const auto [creation, modification] = median<cxx_adc_2023_day10::game_object>(n, m);
		std::cout <<
			"---\n"
			"original game object\n"
			"GameObjectの作成とコンポーネントの追加: " << creation << "\n"
			"コンポーネントの変更にかかった時間: " << modification << '\n';
	}
	{
		const auto [creation, modification] = median<cxx_adc_2023_day10::entt>(n, m);
		std::cout <<
			"---\n"
			"entt\n"
			"エンティティの作成とコンポーネントの追加: " << creation << "\n"
			"コンポーネントの変更にかかった時間: " << modification << '\n';
	}
	{
		const auto [creation, modification] = median<cxx_adc_2023_day10::improved_game_object>(n, m);
		std::cout <<
			"---\n"
			"improved game object\n"
			"GameObjectの作成とコンポーネントの追加: " << creation << "\n"
			"コンポーネントの変更にかかった時間: " << modification << '\n';
	}
	{
		const auto [creation, modification] = median<cxx_adc_2023_day10::static_polymorph_game_object>(n, m);
		std::cout <<
			"---\n"
			"static-polymorph game object\n"
			"GameObjectの作成とコンポーネントの追加: " << creation << "\n"
			"コンポーネントの変更にかかった時間: " << modification << '\n';
	}
	{
		const auto [creation, modification] = median<cxx_adc_2023_day10::old_style_game_object>(n, m);
		std::cout <<
			"---\n"
			"old style game object\n"
			"GameObjectの作成とコンポーネントの追加: " << creation << "\n"
			"コンポーネントの変更にかかった時間: " << modification << '\n';
	}
}
