#pragma once

#include <Lanna/Core.h>
#include "document.h"

namespace Lanna {

	class JsonValue {
	private:
		rapidjson::Value* m_Value;
	public:
		JsonValue(rapidjson::Value* value);
		~JsonValue();

		template<class T> void set(T data);
		template<class T> void operator=(T data);

		template<class T> T get();

		template<class T> operator T();
	};
	
	template<class T>
	inline void JsonValue::set(T data)
	{
		m_Value->Set<T>(data);
	}

	template<class T>
	inline T JsonValue::get()
	{
		return m_Value->Get<T>();
	}
	template<>
	inline const char* JsonValue::get()
	{
		return m_Value->GetString();
	}

	template<class T>
	inline void JsonValue::operator=(T data)
	{
		set<T>(data);
	}

	template<class T>
	inline JsonValue::operator T()
	{
		return get<T>();
	}

}