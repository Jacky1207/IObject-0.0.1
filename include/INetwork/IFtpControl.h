#pragma once

#include "typedef.h"

namespace IObject
{
	namespace INetwork
	{

	#define CONTROL_PORT	20
	#define DATA_PORT		21

	enum Ftp_Com
	{
		USER,
		PASS,
		SIZE,
		REST,
		CWD,
		RETR,
		STOR,
		PASV,
		PORT,
		QUIT
	};
		class IFtpControl
		{
		public:
			IFtpControl();
			virtual ~IFtpControl();

			sg_int32_t	login(const sg_string_t usrname, const sg_string_t pass);
		private:
			
		};
	}
}