#include "BaseCommand.h"
class CDebugCommandBase : public IPLCCommand
{
public:
	virtual bool CheckResponse();
	//要设置的参数
	void SetParameter(byte b0,byte b1,byte b2,byte b3);

protected:
	virtual void _Initialize();
	virtual void _BuildOperateData();
	virtual void _BuildStorageCode();
	virtual void _BuildAddress2Send() = 0;
	virtual void _BuildLength();
	virtual void _BuildData();

protected:
	//写命令的参数
	byte  m_bWrite[4];
};