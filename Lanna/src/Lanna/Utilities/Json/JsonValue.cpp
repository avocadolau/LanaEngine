#include "lnpch.h"

#include "JsonValue.h"

namespace Lanna {

	JsonValue::JsonValue(rapidjson::Value* value)
	{
		m_Value = value;
	}
	JsonValue::~JsonValue()
	{
		
	}
}
