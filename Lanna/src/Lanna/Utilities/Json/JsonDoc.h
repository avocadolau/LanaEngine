#pragma once
#pragma warning(disable : 4251)

#include <Lanna/Core.h>

#include "rapidjson.h"
#include "stringbuffer.h"

#include "JsonValue.h"
#include <string>

namespace Lanna {
	class JsonDoc {
	private:
		rapidjson::Document m_Document;
		rapidjson::StringBuffer m_Buffer;
	public:
		JsonDoc(const char* path);
		JsonDoc();
		~JsonDoc();

		void Parse(const char* string);
		const char* getString();

		template<class T>
		JsonValue AddMember(const char* mem, T value);

		bool HasMember(const char* mem);

		bool load_file(const char* path);
		bool save_file(const char* path);

		JsonValue operator[](const char* key);
	};

	template<class T>
	inline JsonValue JsonDoc::AddMember(const char* mem, T value)
	{
		rapidjson::Value key(mem, m_Document.GetAllocator());
		rapidjson::Value v(value);

		rapidjson::Value& jval = m_Document.AddMember(key, v, m_Document.GetAllocator());

		return JsonValue(&jval);
	}

	template<>
	inline JsonValue JsonDoc::AddMember<const char*>(const char* mem, const char* value) {
		rapidjson::Value key(mem, m_Document.GetAllocator());
		rapidjson::Value v;
		v.SetString(value, m_Document.GetAllocator());

		rapidjson::Value& jval = m_Document.AddMember(key, v, m_Document.GetAllocator());

		return JsonValue(&jval);
	}
}