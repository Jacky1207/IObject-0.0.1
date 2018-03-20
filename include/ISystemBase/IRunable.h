#pragma once


namespace IObject
{
	namespace ISystemBase
	{
		class IRunable
		{
		public:
			IRunable(){};
			virtual ~IRunable(){};
			
			virtual void run() = 0;
		};
	}
}
