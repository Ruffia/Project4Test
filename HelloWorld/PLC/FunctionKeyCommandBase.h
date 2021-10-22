#include "BaseCommand.h"
class CFunctionKeyCommandBase : public IPLCCommand
{
public:
	virtual bool CheckResponse();

protected:
	virtual void _Initialize();
	virtual void _BuildOperateData();
	virtual void _BuildStorageCode();
	virtual void _BuildAddress2Send() = 0;
	virtual void _BuildLength();
	virtual void _BuildData();
};