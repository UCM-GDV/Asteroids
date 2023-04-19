#pragma once
#include "../ecs/Component.h"
#include <functional>

using CallBack = std::function<void(void)>;

struct Callback : public Component {
public:
	CallBack callback;

	// Identificador
	constexpr static cmpId_type id = _CALLBACK;
	// Constructora
	Callback(CallBack cb) : callback(cb) {}
	// Destructora
	virtual ~Callback() {}
	// Establece el callback
	inline void setCallback(CallBack cb) { callback = cb; }
};