#pragma once

#include "Lanna/Core.h"
#include "Layer.h"

#include <vector>

namespace Lanna {
	//Wrapper over this vector of layers. This is not an actual stack bc we will need to push things in the middle
	class LANNA_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers; //Using a vector bc every frame this will be ittirated over, we will also need a reverse itterator
		unsigned int m_LayerInsertIndex = 0;
	};

}
