///////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2009, xx科技有限公司(版权声明) 
/// All rights reserved. 
/// 
/// @file         ClientManager.h 
/// @brief       客户端管理模块
///
/// @version   1.0 (版本声明)
/// @author    Jorhy (joorhy@gmail.com) 
/// @date       2013/09/18 16:59 
///
///
/// 修订说明：最初版本
///////////////////////////////////////////////////////////////////////////  
#ifndef __CLIENT_MANAGER_H_
#define __CLIENT_MANAGER_H_
#include "j_includes.h"
#include "x_lock.h"

#ifdef   LIBMANAGER_EXPORTS 
#define   JO_CLIENTMAN_API           __declspec(dllexport) 
#else 
#define   JO_CLIENTMAN_API           __declspec(dllimport) 
#endif 

/// 本类的功能:  管理客户端信息
/// 本类是个管理模块
/// 管理客户端的登录、退出、请求数据等操作
class JO_CLIENTMAN_API CClientManager
{
	typedef std::map<j_socket_t, J_Client *>	ClientMap;
public:
	CClientManager();
	~CClientManager();

public:
	/// 创建客户端对象
	/// @param[in]		nSock 设备连接 
	/// @param[out]   NULL-失败,否则为Client对象
	/// @return			参见j_errtype.h 
	J_Client *CreateClientObj(j_socket_t nSock);
	/// 获取客户端对象
	/// @param[in]		nnSock 设备连接 
	/// @return			Client对象,NULL-未找到   
	J_Client *GetClientObj(j_socket_t nSock);
	///删除客户端对象
	/// @param[in]		nSock 设备连接 
	/// @return			
	void ReleaseClientObj(j_socket_t nSock);
	/// 登录
	/// @param[in]		nSock  连接Socket
	/// @param[in]		pUserName 用户名
	/// @param[in]		pPassWord  密码
	/// @return		    用户ID,=0-登录失败  
	j_uint32_t Login(j_socket_t nSock, const j_char_t *pUserName, const j_char_t *pPassWord);
	/// 注销
	/// @param[in]		nUserId 用户ID 
	/// @return		     
	void Logout(j_uint32_t nUserId);

private:
	J_OS::CTLock m_locker;
	ClientMap m_clientMap;
};

JO_DECLARE_SINGLETON(ClientManager)

#endif //~__CLIENT_MANAGER_H_