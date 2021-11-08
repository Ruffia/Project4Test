#pragma once
#define PLC_Command_Length  64

#define CHECK_RESP(HexCode)  \
	if(m_pResp[nSeq++] != HexCode) return false;

class IPLCCommand
{
public:
	IPLCCommand();
	virtual ~IPLCCommand();

public:
	void BuildCommand();
	virtual bool CheckResponse() = 0;
	//以字符串形式输出command
	char* GetCommand();

protected:
	//初始化内存空间
	virtual void _Initialize() = 0;

	//固定(4字节)
	virtual void _BuildFixed1();

	//PC IP地址(1字节)
	virtual void _BuildIP1();

	//固定(2字节)
	virtual void _BuildFixed2();

	//PLC IP地址(1字节)
	virtual void _BuildIP2();

	//固定(2字节)
	virtual void _BuildFixed3();

	//写数据or读数据(2字节)
	//操作命令，写命令（额外修改参数通道），值为01H，02H
	//读命令，故障代码，值为01H，01H
	virtual void _BuildOperateData() = 0;

	//存储区代码(1字节)
	//对于 写命令（额外修改参数通道）,值为 0x82
	//对于其他命令, 值为 0x30 
	virtual void _BuildStorageCode() = 0;

	//下发地址(3字节)
	//各指令下发内容不同
	virtual void _BuildAddress2Send() = 0;

	//下发长度(2字节)
	//对于 写命令（额外修改参数通道）,值为 00H 02H
	//对于其他命令, 值为 00H 01H
	virtual void _BuildLength() = 0;

	//数据
	//对于 写命令（额外修改参数通道）,值为 0xFF,0xFF,0xFF,0xFF(4字节，示意)
	//对于其他指令，值为0x01
	virtual void _BuildData() = 0;

public:
	byte* m_pCommand;               //发送给PLC的指令
	byte* m_pResp;                  //PLC返回的指令
	char  m_szMapAddress[16];       //映射地址
	char  m_szCommand[128];         //以字符形式存储16进制指令
};