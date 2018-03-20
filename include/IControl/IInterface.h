#ifndef _IINTERFACE_H_
#define _IINTERFACE_H_

#include "typedef.h"
#include "ISelect.h"

using namespace IObject::ISystembase;
namespace IObject
{
	namespace IControl
	{
		class IInterface  : virtual public ISelect
		{
		public:
			IInterface();
			virtual ~IInterface();
		
			typedef sg_int32_t(* ReadyReadFun)(sg_int32_t comm, sg_char_t *pData, sg_int32_t len);

			void eventHandle(const sg_int32_t fd);
			sg_void_t registerReadFun(ReadyReadFun fun){ _readyReadFun = fun;}

			static IInterface *getInstance();
		private:
			ReadyReadFun _readyReadFun;

			static IInterface *m_pInterface;
		};
	}
}

#endif
