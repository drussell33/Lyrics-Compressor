#ifndef ADTEXCEPTION_HPP
#define ADTEXCEPTION_HPP

#include <exception>
#include <ostream>
#include <string>

namespace data_structures
{

	class AdtException final : public std::exception
	{
	public:
		explicit AdtException(const char* what)
			: exception(what) { }

		const wchar_t* Message() const
		{
			auto str = std::string(exception::what());
			auto wide_str = std::wstring(str.length(), L' ');

			std::copy(str.begin(), str.end(), wide_str.begin());

			return wide_str.c_str();
		}

		friend std::ostream& operator<<(std::ostream& stream, const AdtException& exception)
		{
			stream << exception.what() << "\n";
			return stream;
		}
	};
}


#endif