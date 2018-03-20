#include "ISelect.h"
#include "ILog.h"

namespace IObject
{
	namespace ISystemBase
	{
		ISelect::ISelect() : 
			_epollfd(-1),
			_isActive(true)
		{
			_epollfd = epoll_create(EPOLL_LISTEN_CNT);
			if(_epollfd < 0)
			{
				LOG_WRITE(ISELECT , LOG_ERROR, "epoll_create failed!");
			}
			
			_pThread.start(this);
		}
		
		ISelect::~ISelect()
		{
			_isActive  = false;
			
			close(_epollfd);
			_epollfd = -1;
			
			LOG_WRITE(ISELECT , LOG_INFO, "~ISelect");
		}
		
		sg_int32_t ISelect::addEvent(const sg_int32_t fd)
		{
			if(_epollfd < 0)
				return -1;
			LOG_WRITE(ISELECT ,LOG_DEBUG, "add select event %d",fd);
			struct epoll_event event;
			memset(&event, 0, sizeof(struct epoll_event));
			event.data.fd = fd;
			event.events = EPOLLIN | EPOLLET;
			
			int ret = epoll_ctl(_epollfd, EPOLL_CTL_ADD, fd, &event);
			if(ret < 0)
			{
				LOG_WRITE(ISELECT ,LOG_ERROR, "add select event %d failed",fd);
			}
		}
		
		sg_int32_t ISelect::removeEvent(const sg_int32_t fd)
		{
			if(_epollfd < 0)
				return -1;
				
			LOG_WRITE(ISELECT ,LOG_DEBUG, "remove select event %d",fd);
			int ret = epoll_ctl(_epollfd, EPOLL_CTL_DEL, fd, 0);
			if(ret < 0)
			{
				LOG_WRITE(ISELECT ,LOG_ERROR, "del select  event failed %d",fd);
				perror("epool_ctl :");
				return -1;
			}
			
			LOG_WRITE(ISELECT ,LOG_DEBUG, "del select event success %d",fd);
			return 0;
		}
		
		sg_void_t ISelect::run()
		{
			int fd_cnt = 0;
			int tmpfd;
			
			LOG_WRITE(ISELECT ,LOG_INFO, "ISelect thread run");
			
			while(_isActive)
			{
				struct epoll_event events[EPOLL_LISTEN_CNT]= {0};
				if(_epollfd < 0)
					break;
				
//				LOG_WRITE(ISELECT ,LOG_DEBUG, "ISelect epoll_wait start.");
				fd_cnt = epoll_wait(_epollfd, events, EPOLL_LISTEN_CNT, EPOLL_LISTEN_TIMEOUT);
//				LOG_WRITE(ISELECT ,LOG_DEBUG, "ISelect epoll_wait finish.");

				if(fd_cnt > 0)
					LOG_WRITE(ISELECT ,LOG_DEBUG, "event come %d",fd_cnt);
				else
					continue;
				
				for(int i=0;i<fd_cnt;i++)
				{
					tmpfd = events[i].data.fd;
					LOG_WRITE(ISELECT ,LOG_DEBUG, "event %d",tmpfd);
					eventHandle(tmpfd);
				}
			}
			printf("----------------------\n");
			
			LOG_WRITE(ISELECT ,LOG_INFO, "ISelect thread finish!");
		}
	}
}
