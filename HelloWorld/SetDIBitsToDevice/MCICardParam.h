
#if !defined(MCICardParam__INCLUDE_)
#define MCICardParam__INCLUDE_

const DWORD	g_dwUSB_UpdateDelay				= 8;//13;

const CSize	g_szUSB_FrameImage				= CSize(8192,8192);	//CSize(2048,1536);
const CSize	g_szUSB_FrameGraph				= CSize(2048,2048);	//CSize(1024,768);
const CSize	g_szUSB_FrameLabel				= CSize(2048,64);	//CSize(1024,64);
//const CSize	g_szUSB_FrameMobileUScale		= CSize(1024,32);
const CSize	g_szUSB_FrameMobileUScale		= CSize(2048,40);	//CSize(1024,40);
const CSize	g_szUSB_FrameOscillograph		= CSize(2048,128);	//CSize(1024,128);
/*
enum USB_Image_Resolution{
	USB_RESO_16_16,
	USB_RESO_32_32,
	USB_RESO_64_64,
	USB_RESO_128_128,
	USB_RESO_256_256,
	USB_RESO_512_512,
	USB_RESO_1024_1024,
	USB_RESO_2048_2048,
	USB_RESO_4096_4096,
	USB_RESO_8192_8192,
};

const CSize	g_sizeUSB_RESO_512_512		= CSize(512,512);
const CSize	g_sizeUSB_RESO_1024_1024	= CSize(1024,1024);
const CSize	g_sizeUSB_RESO_2048_2048	= CSize(2048,2048);
const CSize	g_sizeUSB_RESO_4096_4096	= CSize(4096,4096);
const CSize	g_sizeUSB_RESO_8192_8192	= CSize(8192,8192);
const CSize	g_sizeUSB_RESO_256_256		= CSize(256,256);
const CSize	g_sizeUSB_RESO_128_128		= CSize(128,128);
const CSize	g_sizeUSB_RESO_16_16		= CSize(16,16);
const CSize	g_sizeUSB_RESO_32_32		= CSize(32,32);
const CSize	g_sizeUSB_RESO_64_64		= CSize(64,64);
const CSize g_sizeUSB_RESOs[] = { CSize(16,16), CSize(32,32), CSize(64,64), CSize(128,128), CSize(256,256), CSize(512,512), CSize(1024,1024), CSize(2048,2048), CSize(4096,4096), CSize(8192,8192), CSize(1,1) };
*/

enum USB_FRAME_ZODER{
	USB_FrameDebugInfo,
	USB_FrameMobileUScale,
	USB_FrameLabel,
	USB_FrameEdit,
	USB_FrameGraphic,
	USB_FrameImage,
};

const COLORREF g_clrUSB_Transparent		= RGB(0,0,0);		// 0x00rrggbb
const COLORREF g_clrUSB_Background		= RGB(0,0,127);//RGB(0,0,1);//RGB(0,0,127);		// 0x00rrggbb

const COLORREF g_clrUSB_EditText		= RGB(155,255,255);
const COLORREF g_clrUSB_LabelText		= RGB(155,255,255);
const COLORREF g_clrUSB_LabelLogoText	= RGB(155,255,255);

const COLORREF g_clrUSB_MobileUScale	= RGB(255,255,155);//RGB(55, 146, 200);//
const COLORREF g_clrUSB_MobileUScaleLine= RGB(255,0,0);

#endif // MCICardParam__INCLUDE_

