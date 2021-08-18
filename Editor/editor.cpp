#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <list>
#include <string>
#include <queue>
#include <limits>
#include <algorithm>
// #include <simple_svg100.hpp>
#include "app.hpp"
#include "editor.hpp"

using namespace spt;

#if _MSC_VER
// Disables the console window on Windows
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

template<typename T, int array_size = 1>
class lazy_ptr {
protected:
	T _new_val[array_size];
public:
	T* pval;

	explicit lazy_ptr(T* ptr) : pval(ptr) {
	}

	operator T*() {
		std::memcpy(_new_val, pval, sizeof(T) * array_size);
		return _new_val;
	}

	bool update() {
		bool ret = false;
		for (int i = 0; i < array_size; ++i) {
			if (_new_val[i] != pval[i]) {
				pval[i] = _new_val[i];
				ret = true;
			}
		}
		return ret;
	}
};

template<typename T>
class lazy_ptr<T, 1> {
protected:
	T _new_val;
public:
	T* pval;

	explicit lazy_ptr(T* ptr) : pval(ptr) {
	}

	operator T*() {
		_new_val = *pval;
		return &_new_val;
	}

	bool update() {
		if (_new_val == *pval) return false;
		else {
			*pval = _new_val;
			return true;
		}
	}
};

enum class DragState {
	None = 0, Begin, End, During
};

class DragStateMachine {
protected:
	int s;
	ImVec2 p0;

public:
	ImVec2 delta;

	DragStateMachine() : s(0) {
	}

	DragState Update(int is_mouse_down, const ImVec2& mouse_position) {
		s = (s << 1) | is_mouse_down;
		auto state = static_cast<DragState>(s & 0x3);
		switch (state) {
		case DragState::None:
		case DragState::Begin:
			p0 = mouse_position;
			break;
		case DragState::End:
		case DragState::During:
			delta.x = mouse_position.x - p0.x;
			delta.y = mouse_position.y - p0.y;
			break;
		}
		return state;
	}
};

int main() {
	auto app = AppEngine::App::Initialize();
	if (!app.ok) return 1;
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImVec4 clear_color = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);

	DragStateMachine dsm;

	while (AppEngine::App::EventLoop()) {
		const ImVec2 m = ImGui::GetMousePos();
		auto drawList = ImGui::GetBackgroundDrawList();

		switch (dsm.Update(io.MouseDown[0], m)) {
		case DragState::Begin:
			
			break;
		case DragState::During:
			
			break;
		case DragState::End:
			
			break;
		}

		ImGui::Begin("HSEditor");
		
		ImGui::End();
		AppEngine::App::Render(clear_color);
	}

	return 0;
}
