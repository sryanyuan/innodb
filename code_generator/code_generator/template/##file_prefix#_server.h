#ifndef __##marco_prefix#_SERVER_H
#define __##marco_prefix#_SERVER_H

#include "core/core_msg_.h"
#include "core/core_cmd_target.h"
#include "core/core_daemon_event.h"
#include "revolver/base_event_handler.h"
#include "core/core_tcp_disconnect_notify.h"

using namespace BASE;

//��Ϣ���������������ö��
class ##class_prefix#Server : public ICmdTarget,			//��Ϣ�����ӿ�
					 public IDaemonEvent,		//daemon client�¼��ӿ�
					 public ICoreServerNotify,	//������߽ӿ�
					 public CEventHandler		//��ʱ��handler
{
public:
	##class_prefix#Server();
	~##class_prefix#Server();

public:
	void				init();
	void				destroy();

public:
	//TCP���ӺͶϿ��źŴ���
	int32_t				on_connect_event(CBasePacket* packet, uint32_t sid, CConnection* connection);
	int32_t				on_disconnect_event(CBasePacket* packet, uint32_t sid, CConnection* connection);

	//����SAMPLE_MSGID
	int32_t				on_sample_msg(CBasePacket* packet, uint32_t sid, CConnection* connection);

	//DAEMON CLIENT�¼�
	//�Ǽ�daemond�¼�����ȡ��sid, net type, ��ַ��Ϣ��ͨ��
	void				on_register(uint32_t sid, uint8_t stype, uint16_t net_type, const Inet_Addr& tel_addr, const Inet_Addr& cnc_addr);
	//�������֪�ķ���Ԫ����
	void				on_add_server(uint32_t sid, uint8_t stype, uint16_t net_type, const Inet_Addr& tel_addr, const Inet_Addr& cnc_addr);
	//�������֪�ķ�����daemond�Ͽ���������Ϊ����Ԫ����������
	void				on_del_server(uint32_t sid, uint8_t stype);

	//������ֹͣ������߶���ͨ�棬��Ϊ����Ԫֹͣ���������
	void				on_server_dead(uint32_t sid, uint8_t stype);

	//��ʱ�¼�
	int32_t				handle_timeout(const void *act, uint32_t timer_id);

protected:
	void				set_timer();
	void				cancel_timer();

	//��ʱ�������ͷŽӿ�
	void				release_timer_act(const void* act);

	void				heartbeat();

protected:
	//��ʱ����ID
	uint32_t			_heartbeat_timer_id;

protected:
	//��Ϣӳ��ص���������
	DECLARE_MSGCALL_MAP()
};

#endif