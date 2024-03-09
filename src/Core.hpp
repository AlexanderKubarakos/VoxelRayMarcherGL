#pragma once

#include "Window.hpp"
#include <memory>
namespace VRM {
	class Core {
	public:
		Core();
		~Core();
		
		void run();
	private:
		std::unique_ptr<Window> _window;
	};
}