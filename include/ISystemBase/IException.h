#ifndef _IEXCEPTION_H_
#define _IEXCEPTION_H_

#include <exception>

namespace IObject
{
	namespace ISystembase
	{
		class IException : public exception
		{
		public:
			IException();
			
			const char* what()const throw();
		};
	}
}

#endif