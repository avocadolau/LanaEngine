#include "lnpch.h"
#include "JsonDoc.h"

#include "writer.h"
#include "filereadstream.h"
#include "filewritestream.h"

namespace Lanna {

	JsonDoc::JsonDoc(const char* path)
	{
		if (!load_file(path)) {
			LN_WARN("Couldn't load file \"{0}\"", path);
		}
	}

	JsonDoc::JsonDoc()
	{
		m_Document.SetObject();
	}

	/*JsonDoc::JsonDoc()
	{
	}*/

	void JsonDoc::Parse(const char * string)
	{
		m_Document.Parse(string);
	}

	const char* JsonDoc::getString()
	{
		m_Buffer.Clear();
		rapidjson::Writer<rapidjson::StringBuffer> writer(m_Buffer);

		m_Document.Accept(writer);

		return m_Buffer.GetString();
	}

	bool JsonDoc::HasMember(const char* mem)
	{
		return m_Document.HasMember(mem);
	}

	bool JsonDoc::load_file(const char* path)
	{
		FILE* fp = fopen(path, "rb");

		if (!fp)
			return false;

		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

		m_Document.ParseStream(is);

		fclose(fp);

		return true;
	}

	bool JsonDoc::save_file(const char* path)
	{
		FILE* fp = fopen(path, "wb");

		if (!fp)
			return false;

		char writeBuffer[65536];
		rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

		rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
		m_Document.Accept(writer);

		fclose(fp);

		return true;
	}

	JsonValue JsonDoc::operator[](const char * key)
	{
		return JsonValue(&m_Document[key]);
	}
}
