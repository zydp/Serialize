#ifndef _SERIALIZE_H_
#define _SERIALIZE_H_
#include <string>
#include "CommToolsExportDef.h"
using std::string;

#define SERIALIZE_BUF_SIZE 4096				//getpagesize()
#define SERIALIZE_REALLOC_MAX_COUNT	8		//最大空间扩展次数4096*8
typedef enum {
	LENGTH_CHECK_READ,//反序列化
	LENGTH_CHECK_WRITE,//序列化
}LENGTH_CHECK_TYPE;

/*
* Warning： 一个序列化对象，只能用于序列化或反序列化中的一种用途
*/
typedef struct szBuf  
{
	int iSize;
	char pBuf[SERIALIZE_BUF_SIZE];
}T_SZBUF;
class COMM_TOOLS_API CSerialize
{
public:
	/*序列化时使用*/
	CSerialize(const int TotalBufLen = SERIALIZE_BUF_SIZE);
	/*反序列化时使用*/
	CSerialize(const char* szBuf,const int szBufLen);
	~CSerialize(void);
public:
	CSerialize&  operator<<(const bool _Val);
	CSerialize&  operator>>(bool& _Val);
	CSerialize&  operator<<(const short _Val);
	CSerialize&  operator>>(short& _Val);
	CSerialize&  operator<<(const int _Val);
	CSerialize&  operator>>(int& _Val);
	CSerialize&  operator<<(const unsigned int& _Val);
	CSerialize&  operator>>(unsigned int& _Val);
	CSerialize&  operator<<(const double _Val);
	CSerialize&  operator>>(double& _Val);
	CSerialize&  operator<<(const unsigned long long _Val);
	CSerialize&  operator>>(unsigned long long& _Val);
	CSerialize&  operator<<(const string& _Val); 
	CSerialize&  operator>>(string& _Val);
	CSerialize&  operator<<(const T_SZBUF& _Val); 
	CSerialize&  operator>>(T_SZBUF& _Val);
public:
	/*获取已序列化的buf大小*/
	inline int GetIndex(){return m_iCurrIndex+1;}
	
	/*返回序列化后的buf*/
	inline const char* Serialize(){return m_strBuf;}
	
	/*重置下标为初始位置*/
	inline void ResetIndex(){m_iCurrIndex = 0;}

	/*将buf清空，并重置下标*/
	bool ClearBuffer();

	/*获取序列化对象状态*/
	inline bool GetSerStatus(){return m_SerStatus;}

	/*释放内部空间*/
	void Release();
private:
	/*序列化时内部空间初始化*/
	bool BufInit();
	
	/*buf长度检查*/
	bool CheckLength(const int ValueLen,LENGTH_CHECK_TYPE checkType);
	
	/*序列化一个对象*/
	void ValueWrite(const char* strValue,const int valueLen);
	
	/*反序列化一个对象*/
	void ValueRead(void* ValueAddress,const int valueLen);
private:
	int   m_iTotalLen;				//buf总长
	int   m_iCurrIndex;				//当前下标
	char* m_strBuf;					//buf地址
	bool  m_isSerialize;			//true->序列化,false->反序列化
	bool  m_SerStatus;				//序列化状态，true为正常，false为异常
	unsigned short m_iReallocCount;	//空间扩展次数
private:
	CSerialize(CSerialize& sz){}
	CSerialize& operator=(CSerialize &sz){return *this;}
};

#endif