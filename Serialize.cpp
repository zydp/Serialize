#include "Serialize.h"
#include <assert.h>
#include <string.h>
#ifndef __iOS__
#include <malloc.h>
#endif


CSerialize::CSerialize(const int TotalBufLen /*= SERIALIZE_BUF_SIZE*/)
{
	m_iReallocCount = 0;
	m_isSerialize = true;
	m_strBuf = NULL;
	if(TotalBufLen<=0)
	{
		m_iTotalLen = SERIALIZE_BUF_SIZE;
		//m_iTotalLen = getpagesize();
	}else{
		m_iTotalLen = TotalBufLen;
	}
	m_iCurrIndex = 0;
	if(!BufInit())
	{
		m_strBuf = NULL;
		m_SerStatus = false;
		m_iTotalLen = 0;
		return;
	}
	m_SerStatus = true;
}

CSerialize::CSerialize(const char* szBuf,const int szBufLen)
{
	m_iReallocCount = 0;
	m_isSerialize = false;
	if(NULL==szBuf || szBufLen<=0)
	{
		m_strBuf = NULL;
		m_iTotalLen = 0;
		m_SerStatus = false;
		return;
	}
	m_strBuf = (char*)szBuf;
	m_iTotalLen = szBufLen;
	m_iCurrIndex = 0;
	m_SerStatus = true;
}
CSerialize::~CSerialize()
{
	if(m_isSerialize && m_strBuf)
	{
		Release();
	}
}

bool CSerialize::BufInit()
{
	m_strBuf = (char*)malloc(m_iTotalLen);
	if(NULL==m_strBuf)
	{
		//LOG
		return false;
	}
	memset(m_strBuf,0,m_iTotalLen);
	m_SerStatus = true;
	return true;
}

bool CSerialize::CheckLength(const int ValueLen,LENGTH_CHECK_TYPE checkType)
{
	if(!m_SerStatus)
	{
		return false;
	}
	if (m_iCurrIndex+ValueLen>=m_iTotalLen)
	{
		if(LENGTH_CHECK_READ==checkType)
		{
			m_SerStatus = false;
			return false;
		}
		if(m_iReallocCount>=SERIALIZE_REALLOC_MAX_COUNT)
		{
			m_SerStatus = false;
			return false;
		}
		++m_iReallocCount;
		char* newSizeBuf = (char*)realloc(m_strBuf,m_iTotalLen+SERIALIZE_BUF_SIZE);
		if(NULL==newSizeBuf)
		{
			m_SerStatus = false;
			return false;
		}
		m_strBuf = newSizeBuf;
		memset(m_strBuf+m_iCurrIndex,0,SERIALIZE_BUF_SIZE);
		m_iTotalLen+=SERIALIZE_BUF_SIZE;
	}
	return true;
}

void CSerialize::ValueWrite(const char* strValue,const int valueLen)
{
	memcpy(m_strBuf+m_iCurrIndex,strValue,valueLen);
	m_iCurrIndex+=valueLen;
}

void CSerialize::ValueRead(void* ValueAddress,const int valueLen)
{
	memcpy(ValueAddress,m_strBuf+m_iCurrIndex,valueLen);
	m_iCurrIndex+=valueLen;
}

/*将buf清空，并重置下标*/
bool CSerialize::ClearBuffer()
{
	if(NULL==m_strBuf || !m_iCurrIndex || !m_iTotalLen)
	{
		return false;
	}
	memset(m_strBuf,0,m_iTotalLen);
	m_iCurrIndex = 0;
	m_SerStatus = true;
	return true;
}

void CSerialize::Release()
{
	if(m_isSerialize && m_strBuf)
	{
		free(m_strBuf);
	}
	m_strBuf = NULL;
	m_iTotalLen = 0;
	m_iCurrIndex = 0;
	m_SerStatus = false;
}

//----------------------------------------------------


CSerialize&  CSerialize::operator<<(const bool _Val)
{
	do{
		int ilen = sizeof(_Val);
		if(!CheckLength(ilen, LENGTH_CHECK_WRITE))
		{
			break;
		}
		ValueWrite((char*)&_Val,ilen);
	}while(false);
	return *this;
}

CSerialize&  CSerialize::operator>>(bool& _Val)
{
	do{
		int ilen = sizeof(_Val);
		if(!CheckLength(ilen, LENGTH_CHECK_READ))
		{
			break;
		}
		ValueRead(&_Val,ilen);
	}while(false);
	return *this;
}

CSerialize&  CSerialize::operator<<(const short _Val)
{
	do{
		int ilen = sizeof(_Val);
		if(!CheckLength(ilen, LENGTH_CHECK_WRITE))
		{
			break;
		}
		ValueWrite((char*)&_Val,ilen);
	}while(false);
	return *this;
}

CSerialize&  CSerialize::operator>>(short& _Val)
{
	do{
		int ilen = sizeof(_Val);
		if(!CheckLength(ilen, LENGTH_CHECK_READ))
		{
			break;
		}
		ValueRead(&_Val,ilen);
	}while(false);
	return *this;
}


CSerialize&  CSerialize::operator<<(const int _Val)
{
	do{
		int ilen = sizeof(_Val);
		if(!CheckLength(ilen, LENGTH_CHECK_WRITE))
		{
			break;
		}
		ValueWrite((char*)&_Val,ilen);
	}while(false);
	return *this;
}

CSerialize&  CSerialize::operator>>(int& _Val)
{
	do{
		int ilen = sizeof(_Val);
		if(!CheckLength(ilen, LENGTH_CHECK_READ))
		{
			break;
		}
		ValueRead(&_Val,ilen);
	}while(false);
	return *this;
}

CSerialize&  CSerialize::operator<<(const unsigned int& _Val)
{
	do{
		int ilen = sizeof(_Val);
		if(!CheckLength(ilen, LENGTH_CHECK_WRITE))
		{
			break;
		}
		ValueWrite((char*)&_Val,ilen);
	}while(false);
	return *this;
}

CSerialize&  CSerialize::operator>>(unsigned int& _Val)
{
	do{
		int ilen = sizeof(_Val);
		if(!CheckLength(ilen, LENGTH_CHECK_READ))
		{
			break;
		}
		ValueRead(&_Val,ilen);
	}while(false);
	return *this;
}

CSerialize&  CSerialize::operator<<(const double _Val)
{
	do{
		int ilen = sizeof(_Val);
		if(!CheckLength(ilen, LENGTH_CHECK_WRITE))
		{
			break;
		}
		ValueWrite((char*)&_Val,ilen);
	}while(false);
	return *this;
}

CSerialize&  CSerialize::operator>>(double& _Val)
{
	do{
		int ilen = sizeof(_Val);
		if(!CheckLength(ilen, LENGTH_CHECK_READ))
		{
			break;
		}
		ValueRead(&_Val,ilen);
	}while(false);
	return *this;
}

CSerialize&  CSerialize::operator<<(const unsigned long long _Val)
{
	do{
		int ilen = sizeof(_Val);
		if(!CheckLength(ilen, LENGTH_CHECK_WRITE))
		{
			break;
		}
		ValueWrite((char*)&_Val,ilen);
	}while(false);
	return *this;
}

CSerialize&  CSerialize::operator>>(unsigned long long& _Val)
{
	do{
		int ilen = sizeof(_Val);
		if(!CheckLength(ilen, LENGTH_CHECK_READ))
		{
			break;
		}
		ValueRead(&_Val,ilen);
	}while(false);
	return *this;
}

CSerialize&  CSerialize::operator<<(const string&  _Val)
{
	do{
		int ilen = (int)_Val.size()+1;
		if(!CheckLength(ilen, LENGTH_CHECK_WRITE))
		{
			break;
		}
		ValueWrite(_Val.c_str(),ilen);
	}while(false);
	return *this;
}

CSerialize&  CSerialize::operator>>(string& _Val)
{  
	if(m_iCurrIndex>=m_iTotalLen)
	{
		return *this;
	}
	_Val = m_strBuf+m_iCurrIndex; 
	int len = (int)_Val.size()+1;
	m_iCurrIndex+=len;
	return *this;
}

CSerialize&  CSerialize::operator<<(const T_SZBUF& _Val)
{

	do{
		int ilen = sizeof(_Val.iSize);
		if(!CheckLength(ilen, LENGTH_CHECK_WRITE))
		{
			break;
		} 
		ValueWrite((char*)&_Val.iSize,ilen);
		if(!CheckLength(_Val.iSize, LENGTH_CHECK_WRITE))
		{
			break;
		}
		ValueWrite(_Val.pBuf,_Val.iSize);
	}while(false);
	return *this;
}
CSerialize&  CSerialize::operator>>(T_SZBUF& _Val)
{

	int iLen = sizeof(_Val.iSize);
	do{ 
		if(!CheckLength(iLen, LENGTH_CHECK_READ))
		{
			break;
		}
		ValueRead(&_Val.iSize,iLen);
		if(!CheckLength(_Val.iSize, LENGTH_CHECK_READ))
		{
			break;
		}
		ValueRead(_Val.pBuf,_Val.iSize);
	}while(false);
	return *this;
} 
