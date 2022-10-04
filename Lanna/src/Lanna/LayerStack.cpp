#include "lnpch.h"
#include "LayerStack.h"

namespace Lanna {
	//Layers belong to layer stack, layerstack is owned by the application
	LayerStack::LayerStack()
	{
	}
	//Ass long as the layer is given to layerstack, it will be deallocated when application shuts down
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}
	//Layers get pushed to the 1st half of the list 
	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer); //layerstack recieves the layer and pushes it into the right place
		m_LayerInsertIndex++;
	}
	//Overlayers get pushed to the 2nd half of the list, bc we want to render them last
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}
	//When we pop layers, we dont actually lose them, only when we destroy them
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it); //Layer isnt deleted, just removed from the actual vector
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}

}