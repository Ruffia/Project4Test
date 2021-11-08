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
	//���ַ�����ʽ���command
	char* GetCommand();

protected:
	//��ʼ���ڴ�ռ�
	virtual void _Initialize() = 0;

	//�̶�(4�ֽ�)
	virtual void _BuildFixed1();

	//PC IP��ַ(1�ֽ�)
	virtual void _BuildIP1();

	//�̶�(2�ֽ�)
	virtual void _BuildFixed2();

	//PLC IP��ַ(1�ֽ�)
	virtual void _BuildIP2();

	//�̶�(2�ֽ�)
	virtual void _BuildFixed3();

	//д����or������(2�ֽ�)
	//�������д��������޸Ĳ���ͨ������ֵΪ01H��02H
	//��������ϴ��룬ֵΪ01H��01H
	virtual void _BuildOperateData() = 0;

	//�洢������(1�ֽ�)
	//���� д��������޸Ĳ���ͨ����,ֵΪ 0x82
	//������������, ֵΪ 0x30 
	virtual void _BuildStorageCode() = 0;

	//�·���ַ(3�ֽ�)
	//��ָ���·����ݲ�ͬ
	virtual void _BuildAddress2Send() = 0;

	//�·�����(2�ֽ�)
	//���� д��������޸Ĳ���ͨ����,ֵΪ 00H 02H
	//������������, ֵΪ 00H 01H
	virtual void _BuildLength() = 0;

	//����
	//���� д��������޸Ĳ���ͨ����,ֵΪ 0xFF,0xFF,0xFF,0xFF(4�ֽڣ�ʾ��)
	//��������ָ�ֵΪ0x01
	virtual void _BuildData() = 0;

public:
	byte* m_pCommand;               //���͸�PLC��ָ��
	byte* m_pResp;                  //PLC���ص�ָ��
	char  m_szMapAddress[16];       //ӳ���ַ
	char  m_szCommand[128];         //���ַ���ʽ�洢16����ָ��
};