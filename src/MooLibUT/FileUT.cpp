#include "pch.h"
#include "catch.hpp"

namespace {
	ml::string256 testpath_ = "testfile.txt";

	bool FileExists(const char* path)
	{
		DWORD dwAttrib = GetFileAttributesA(path);
		return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}

	bool TestFileValue(const char* path, const char* expected_value, uint32_t length)
	{
		ml::Handle handle = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (!handle.IsValid()) {
			return false;
		}

		std::unique_ptr<char[]> data(new char[length + 1]);
		DWORD dwBytesRead;
		if (!ReadFile(handle.GetNative(), data.get(), length, &dwBytesRead, nullptr)) {
			return false;
		}

		data[length] = '\0';

		return strcmp(data.get(), expected_value) == 0;
	}
}


using namespace ml;
using namespace ml::FileSystem;


TEST_CASE( "can default construct file", "[file]" )
{
	File file;

	REQUIRE(!file.IsValid());
}


TEST_CASE( "can create file via construction", "[file]" )
{
	File file(testpath_.data(), OpenMode::Create);

	REQUIRE(file.IsValid());
	file.Close();

	REQUIRE(FileExists(testpath_.data()));
	REQUIRE(file.Delete());
}


TEST_CASE( "can create file via open function", "[file]" )
{
	File file;
	file.Open(testpath_.data(), OpenMode::Create);

	REQUIRE(file.IsValid());
	file.Close();

	REQUIRE(FileExists(testpath_.data()));
	REQUIRE(file.Delete());
}


TEST_CASE( "can write to file", "[file]" )
{
	File file(testpath_.data(), OpenMode::Create | OpenMode::Write);

	REQUIRE(file.IsValid());
	REQUIRE(file.Write("test", 4) == 4);
	file.Close();

	REQUIRE(!file.IsValid());
	REQUIRE(TestFileValue(testpath_.data(), "test", 4));
	REQUIRE(file.Delete());
}


TEST_CASE( "can append to file", "[file]" )
{
	File file(testpath_.data(), OpenMode::Create | OpenMode::Write);

	REQUIRE(file.IsValid());
	REQUIRE(file.Write("test", 4) == 4);
	file.Close();

	file.Open(testpath_.data(), OpenMode::Write | OpenMode::Append);

	REQUIRE(file.IsValid());
	REQUIRE(file.Write("1234", 4) == 4);
	file.Close();

	REQUIRE(TestFileValue(testpath_.data(), "test1234", 8));
	REQUIRE(file.Delete());
}


TEST_CASE( "can read from file", "[file]" )
{
	File file(testpath_.data(), OpenMode::Create | OpenMode::Write);

	REQUIRE(file.IsValid());
	REQUIRE(file.Write("test1234", 8) == 8);
	file.Close();

	file.Open(testpath_.data(), OpenMode::Create | OpenMode::Read);
	std::array<char, 16> data;

	REQUIRE(file.IsValid());
	REQUIRE(file.Read(data) == 8);

	data[8] = '\0';
	REQUIRE(strcmp(data.data(), "test1234") == 0);
	REQUIRE(file.Delete());
}


TEST_CASE( "can get size of file", "[file]" )
{
	File file(testpath_.data(), OpenMode::Create | OpenMode::Write);

	REQUIRE(file.IsValid());
	REQUIRE(file.Write("test1234", 8) == 8);
	file.Close();

	file.Open(testpath_.data(), OpenMode::Read);

	REQUIRE(file.IsValid());
	REQUIRE(file.GetSize() == 8);
	REQUIRE(file.Delete());
}


TEST_CASE( "can seek position in file using current position", "[file]" )
{
	File file(testpath_.data(), OpenMode::Create | OpenMode::Write);

	REQUIRE(file.IsValid());
	REQUIRE(file.Write("test1234", 8) == 8);
	file.Close();

	file.Open(testpath_.data(), OpenMode::Read);
	std::array<char, 16> data;

	REQUIRE(file.IsValid());
	REQUIRE(file.GetPosition() == 0);

	REQUIRE(file.Seek(4, SeekType::Current));
	REQUIRE(file.GetPosition() == 4);
	REQUIRE(file.Read(data.data(), 4) == 4);
	REQUIRE(file.GetPosition() == 8);
	data[4] = '\0';

	REQUIRE(strcmp(data.data(), "1234") == 0);
	REQUIRE(file.Delete());
}


TEST_CASE( "can seek negative position in file using current position", "[file]" )
{
	File file(testpath_.data(), OpenMode::Create | OpenMode::Write);

	REQUIRE(file.IsValid());
	REQUIRE(file.Write("test1234", 8) == 8);
	file.Close();

	file.Open(testpath_.data(), OpenMode::Read);

	REQUIRE(file.IsValid());
	REQUIRE(file.GetPosition() == 0);

	REQUIRE(file.Seek(-4, SeekType::Current) == false);
	REQUIRE(file.GetPosition() == 0);
	REQUIRE(file.Seek(4, SeekType::Current));
	REQUIRE(file.GetPosition() == 4);
	REQUIRE(file.Seek(-4, SeekType::Current));
	REQUIRE(file.GetPosition() == 0);
	REQUIRE(file.Delete());
}


TEST_CASE( "can seek position in file using begin position", "[file]" )
{
	File file(testpath_.data(), OpenMode::Create | OpenMode::Write);

	REQUIRE(file.IsValid());
	REQUIRE(file.Write("test1234", 8) == 8);
	file.Close();

	file.Open(testpath_.data(), OpenMode::Read);

	REQUIRE(file.IsValid());
	REQUIRE(file.GetPosition() == 0);

	REQUIRE(file.Seek(-4, SeekType::Begin) == false);
	REQUIRE(file.GetPosition() == 0);
	REQUIRE(file.Seek(4, SeekType::Begin));
	REQUIRE(file.GetPosition() == 4);
	REQUIRE(file.Seek(8, SeekType::Begin));
	REQUIRE(file.GetPosition() == 8);
	REQUIRE(file.Seek(0, SeekType::Begin));
	REQUIRE(file.GetPosition() == 0);
	REQUIRE(file.Delete());
}


TEST_CASE( "can seek position in file using end position", "[file]" )
{
	File file(testpath_.data(), OpenMode::Create | OpenMode::Write);

	REQUIRE(file.IsValid());
	REQUIRE(file.Write("test1234", 8) == 8);
	file.Close();

	file.Open(testpath_.data(), OpenMode::Read);

	REQUIRE(file.IsValid());
	REQUIRE(file.GetPosition() == 0);

	REQUIRE(file.Seek(4, SeekType::End) == false);
	REQUIRE(file.GetPosition() == 0);
	REQUIRE(file.Seek(-4, SeekType::End));
	REQUIRE(file.GetPosition() == 4);
	REQUIRE(file.Seek(-8, SeekType::End));
	REQUIRE(file.GetPosition() == 0);
	REQUIRE(file.Seek(0, SeekType::End));
	REQUIRE(file.GetPosition() == 8);
	REQUIRE(file.Delete());
}