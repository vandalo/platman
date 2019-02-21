#include "pch.h"

#include <unordered_map>
#include <memory>
#include <time.h>

#include "IModule.h"
#include "CScreenManager.h"

class Application
{
public:
	Application();
	~Application();
	bool Init();
	bool Update();
	bool CleanUp();

	CScreenManager* GetScreenManager() { return m_screanManager; }

	template<typename T>
	T* Add()
	{
		std::size_t hash = CHash<T>::Hash();
		auto it = m_modules.find(hash);
		if (it == m_modules.end())
		{
			m_modules[hash] = std::make_unique<T>();
		}
		return static_cast<T*>(m_modules[hash].get());
	}

	template<typename T>
	T* GetModule()
	{
		std::size_t hash = CHash<T>::Hash();
		auto it = m_modules.find(hash);
		if (it == m_modules.end())
		{
			return nullptr;
		}
		return static_cast<T*>(m_modules[hash].get());
	}

private:
	std::unordered_map<std::size_t, std::unique_ptr<IModule>> m_modules;
	CScreenManager* m_screanManager;

	clock_t timer;
	float deltaTime;
};

extern Application* App;

