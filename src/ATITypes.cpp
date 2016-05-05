#include "ATITypes.h"
#include "Common.h"

namespace T4
{
    uByte* BlockHeaderA::Load(FILE *fp,string &Error,size_t &Pos)
    {
        if(!Read(fp,&m_Unknown0,1,Error))
        {
            Error += Format("\nFailed to read unknown byte of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos++;
        
        if(!Read(fp,&m_DataSize,2,Error))
        {
            Error += Format("\nFailed to read data size of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos += 2;
        
        u8 NameLen = 0;
        if(!Read(fp,&NameLen,1,Error))
        {
            Error += Format("\nFailed to read block name length of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos += 1;
        
        //Names always include trailing zero
        NameLen += 1;
        
        char *Name = new char[NameLen];
        if(!Read(fp,Name,NameLen,Error))
        {
            delete [] Name;
            Error += Format("\nFailed to read block name of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        m_TypeName = Name;
        delete [] Name;
        Pos += NameLen;
        
        /*
        uByte* Data = new uByte[m_DataSize];
        if(!Read(fp,Data,m_DataSize,Error))
        {
            delete [] Data;
            Error += Format("\nFailed to read block data (%lu bytes) of type <%s> at %lu bytes",m_DataSize,GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        
        Pos += m_DataSize;
        */
        
        //Any non null will do here
        return (uByte*)0x10;//Data;
    }
    bool BlockHeaderA::Save(FILE *fp,string &Error,size_t &Pos)
    {
        Error = "BlockHeaderA::Save Not yet implemented";
        fclose(fp);
        return false;
    }
    
    uByte* BlockHeaderB::Load(FILE *fp,string &Error,size_t &Pos)
    {
        if(!Read(fp,&m_Unknown0,1,Error))
        {
            Error += Format("\nFailed to read unknown byte of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos++;
        
        if(!Read(fp,&m_DataSize,1,Error))
        {
            Error += Format("\nFailed to read data size of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos += 1;
        
        u8 NameLen = 0;
        if(!Read(fp,&NameLen,1,Error))
        {
            Error += Format("\nFailed to read block name length of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos += 1;
        
        //Names always include trailing zero
        NameLen += 1;
        
        char *Name = new char[NameLen];
        if(!Read(fp,Name,NameLen,Error))
        {
            delete [] Name;
            Error += Format("\nFailed to read block name of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        m_TypeName = Name;
        delete [] Name;
        Pos += NameLen;
        
        /*
        uByte* Data = new uByte[m_DataSize];
        if(!Read(fp,Data,m_DataSize,Error))
        {
            delete [] Data;
            Error += Format("\nFailed to read block data (%lu bytes) of type <%s> at %lu bytes",m_DataSize,GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        
        Pos += m_DataSize;
        */
        
        //Any non null will do here
        return (uByte*)0x10;//Data;
    }
    bool BlockHeaderB::Save(FILE *fp,string &Error,size_t &Pos)
    {
        Error = "BlockHeaderB::Save Not yet implemented";
        fclose(fp);
        return false;
    }
    
    uByte* BlockHeaderD::Load(FILE *fp,string &Error,size_t &Pos)
    {
        if(!Read(fp,&m_Unknown0,1,Error))
        {
            Error += Format("\nFailed to read unknown byte of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos++;
        
        if(!Read(fp,&m_DataSize,4,Error))
        {
            Error += Format("\nFailed to read data size of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos += 4;
        
        u8 NameLen = 0;
        if(!Read(fp,&NameLen,1,Error))
        {
            Error += Format("\nFailed to read block name length of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos += 1;
        
        //Names always include trailing zero
        NameLen += 1;
        
        char *Name = new char[NameLen];
        if(!Read(fp,Name,NameLen,Error))
        {
            delete [] Name;
            Error += Format("\nFailed to read block name of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        m_TypeName = Name;
        delete [] Name;
        Pos += NameLen;
        
        /*
        uByte* Data = new uByte[m_DataSize];
        if(!Read(fp,Data,m_DataSize,Error))
        {
            delete [] Data;
            Error += Format("\nFailed to read block data (%lu bytes) of type <%s> at %lu bytes",m_DataSize,GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        
        Pos += m_DataSize;
        */
        
        //Any non null will do here
        return (uByte*)0x10;//Data;
    }
    bool BlockHeaderD::Save(FILE *fp,string &Error,size_t &Pos)
    {
        Error = "BlockHeaderD::Save Not yet implemented";
        fclose(fp);
        return false;
    }
    
    
    uByte* BlockHeaderI::Load(FILE *fp,string &Error,size_t &Pos)
    {
        if(!Read(fp,&m_Unknown0,1,Error))
        {
            Error += Format("\nFailed to read unknown byte[0] of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos++;
        
        if(!Read(fp,&m_DataSize,1,Error))
        {
            Error += Format("\nFailed to read data size of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos += 1;
        
        if(!Read(fp,&m_Unknown1,1,Error))
        {
            Error += Format("\nFailed to read unknown byte[1] of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos++;
        
        if(!Read(fp,&m_Unknown2,1,Error))
        {
            Error += Format("\nFailed to read unknown byte[2] of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos++;
        
        u8 NameLen = 0;
        if(!Read(fp,&NameLen,1,Error))
        {
            Error += Format("\nFailed to read block name length of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos += 1;
        
        //Names always include trailing zero
        NameLen += 1;
        
        char *Name = new char[NameLen];
        if(!Read(fp,Name,NameLen,Error))
        {
            delete [] Name;
            Error += Format("\nFailed to read block name of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        m_TypeName = Name;
        delete [] Name;
        Pos += NameLen;
        
        /*
        uByte* Data = new uByte[m_DataSize];
        if(!Read(fp,Data,m_DataSize,Error))
        {
            delete [] Data;
            Error += Format("\nFailed to read block data (%lu bytes) of type <%s> at %lu bytes",m_DataSize,GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        
        Pos += m_DataSize;
        */
        
        //Any non null will do here
        return (uByte*)0x10;//Data;
    }
    bool BlockHeaderI::Save(FILE *fp,string &Error,size_t &Pos)
    {
        Error = "BlockHeaderI::Save Not yet implemented";
        fclose(fp);
        return false;
    }
    
    uByte* BlockHeaderK::Load(FILE *fp,string &Error,size_t &Pos)
    {
        if(!Read(fp,&m_Unknown0,1,Error))
        {
            Error += Format("\nFailed to read unknown byte[0] of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos++;
        
        if(!Read(fp,&m_DataSize,2,Error))
        {
            Error += Format("\nFailed to read data size of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos += 2;
        
        if(!Read(fp,&m_Unknown1,1,Error))
        {
            Error += Format("\nFailed to read unknown byte[1] of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos++;
        
        if(!Read(fp,&m_Unknown2,1,Error))
        {
            Error += Format("\nFailed to read unknown byte[2] of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos++;
        
        u8 NameLen = 0;
        if(!Read(fp,&NameLen,1,Error))
        {
            Error += Format("\nFailed to read block name length of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos += 1;
        
        //Names always include trailing zero
        NameLen += 1;
        
        char *Name = new char[NameLen];
        if(!Read(fp,Name,NameLen,Error))
        {
            delete [] Name;
            Error += Format("\nFailed to read block name of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        m_TypeName = Name;
        delete [] Name;
        Pos += NameLen;
        
        /*
        uByte* Data = new uByte[m_DataSize];
        if(!Read(fp,Data,m_DataSize,Error))
        {
            delete [] Data;
            Error += Format("\nFailed to read block data (%lu bytes) of type <%s> at %lu bytes",m_DataSize,GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        
        Pos += m_DataSize;
        */
        
        //Any non null will do here
        return (uByte*)0x10;//Data;
    }
    bool BlockHeaderK::Save(FILE *fp,string &Error,size_t &Pos)
    {
        Error = "BlockHeaderK::Save Not yet implemented";
        fclose(fp);
        return false;
    }
    
    uByte* BlockHeaderP::Load(FILE *fp,string &Error,size_t &Pos)
    {
        if(!Read(fp,&m_Unknown0,1,Error))
        {
            Error += Format("\nFailed to read unknown byte of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos++;
        
        if(!Read(fp,&m_DataSize,4,Error))
        {
            Error += Format("\nFailed to read data size of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos += 4;
        
        if(!Read(fp,&m_Unknown1,1,Error))
        {
            Error += Format("\nFailed to read unknown byte of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos++;
        
        if(!Read(fp,&m_Unknown1,1,Error))
        {
            Error += Format("\nFailed to read unknown byte of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos++;
        
        u8 NameLen = 0;
        if(!Read(fp,&NameLen,1,Error))
        {
            Error += Format("\nFailed to read block name length of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        Pos += 1;
        
        //Names always include trailing zero
        NameLen += 1;
        
        char *Name = new char[NameLen];
        if(!Read(fp,Name,NameLen,Error))
        {
            delete [] Name;
            Error += Format("\nFailed to read block name of <%s> at %lu bytes",GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        m_TypeName = Name;
        delete [] Name;
        Pos += NameLen;
        
        /*
        uByte* Data = new uByte[m_DataSize];
        if(!Read(fp,Data,m_DataSize,Error))
        {
            delete [] Data;
            Error += Format("\nFailed to read block data (%lu bytes) of type <%s> at %lu bytes",m_DataSize,GetHeaderTypeName().c_str(),Pos);
            return 0;
        }
        
        Pos += m_DataSize;
        */
        
        //Any non null will do here
        return (uByte*)0x10;//Data;
    }
    bool BlockHeaderP::Save(FILE *fp,string &Error,size_t &Pos)
    {
        Error = "BlockHeaderP::Save Not yet implemented";
        fclose(fp);
        return false;
    }
};
