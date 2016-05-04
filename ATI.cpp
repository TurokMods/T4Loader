#include "ATI.h"
#include "Common.h"

namespace T4
{

	ATI::ATI()
	{
	}
	ATI::~ATI()
	{
	}

	bool ATI::Load(const char* File)
	{
		FILE* fp = 0;
        #ifdef __APPLE__
        fp = fopen(File,"rb");
        #else
        fopen_s(&fp,File,"rb");
        #endif
        
		if(!fp)
		{
			m_Error = Format("Unable to open file <%s>",File);;
			return false;
		}

		size_t Pos = 0;
		size_t fSz = 0;
        
		fseek(fp,0,SEEK_END);
        fSz = ftell(fp);
		fseek(fp,0,SEEK_SET);
        
		memset(m_Signature,0,4);
		if(!Read(fp,m_Signature,4,m_Error)) return false;
        Pos += 4;
        
		if(m_Signature[1] != 'a'
		|| m_Signature[2] != 't'
		||(m_Signature[3] != 'i'
        && m_Signature[3] != 'r'))
		{
			m_Error = Format("File <%s> is not a valid ATI or ATR file (Bad signature: \'%s\' != \'ati|atr\')",File,m_Signature);
			fclose(fp);
			return false;
		}

		while(Pos < fSz)
		{
			ATIBlock* Block = new ATIBlock();
            
            size_t OldPos = Pos;
			if(!Block->Load(fp,m_Error,Pos))
			{
				delete Block;
				return false;
			}

			m_Blocks.push_back(Block);
            
            /*
            if(Block->m_Header->GetBlockType() == "ACTOR")
            {
                ActorInstance* Instance = new ActorInstance();
                size_t Offset = 0;
                if(!Instance->Load(Block,m_Error,Offset))
                {
                    m_Error += Format("\nFailed to load data for actor instance at %lu bytes",OldPos + Block->m_Header->GetHeaderSize() + Offset);
                    delete Block;
                    fclose(fp);
                    return false;
                }
            }
            else
            {
                printf("Warning: Unused block type <%s> at %lu bytes\n",Block->m_Header->GetBlockType().c_str(),OldPos);
            }
            */
		}

		fclose(fp);
		return true;
	}
	bool ATI::Save(const char* File)
	{
		return false;
	}
	
	bool ATIBlock::Load(FILE* fp,string& Error,size_t& Pos)
	{
        size_t OldPos = Pos;
        u8 HeaderTypeID;
		if(!Read(fp,&HeaderTypeID,1,Error)) { Error += "\nFailed to read ATI block"; return false; }
        
        switch(HeaderTypeID)
        {
            /* Top level (level file) ATI block types ? */
            case 0x82: { m_Header = new BlockHeaderA(); break; }
            case 0x42: { m_Header = new BlockHeaderB(); break; }
            case 0x81: { m_Header = new BlockHeaderC(); break; }
            case 0xC2: { m_Header = new BlockHeaderD(); break; }
            case 0xC1: { m_Header = new BlockHeaderE(); break; }
            
            /* Sub-block types ? */
            case 0x45: { m_Header = new BlockHeaderF(); break; }
            case 0x4B: { m_Header = new BlockHeaderG(); break; }
            case 0x4A: { m_Header = new BlockHeaderH(); break; }
            case 0x61: { m_Header = new BlockHeaderI(); break; }
            case 0x41: { m_Header = new BlockHeaderJ(); break; }
            case 0xA1: { m_Header = new BlockHeaderK(); break; }
            case 0x47: { m_Header = new BlockHeaderL(); break; }
            case 0x48: { m_Header = new BlockHeaderM(); break; }
            case 0x46: { m_Header = new BlockHeaderN(); break; }
            case 0x49: { m_Header = new BlockHeaderO(); break; }
            case 0xE1: { m_Header = new BlockHeaderP(); break; }
            case 0x6C: { m_Header = new BlockHeaderQ(); break; }
            default:
                {
                    Error = Format("Unknown header type <0x%X> at %lu bytes",HeaderTypeID,Pos);
                    fclose(fp);
                    return false;
                }
        }
        Pos++;
        
        if(!m_Header->Load(fp,Error,Pos))
        {
            Error += Format("\nFailed to load header with type <%s> at %lu bytes",m_Header->GetHeaderTypeName().c_str(),OldPos);
            return false;
        }
        
        string Type = m_Header->GetBlockType();
        m_DataSize = m_Header->GetDataSize();
        if(Type == "ACTOR")
        {
            u8 PathLen = 0;
            if(!Read(fp,&PathLen,1,Error)) { Error += Format("\nUnable to read actor path length at %lu bytes",Pos); return false; }
            Pos += 1;
            
            m_DataSize = PathLen + 1;
            m_Data = new uByte[PathLen + 1];
            if(!Read(fp,m_Data,PathLen,Error)) { Error += Format("\nUnable to read actor path at %lu bytes",Pos); return false; }
            m_Data[PathLen] = '\0';
            Pos += PathLen;
            
            //PathLen does not include trailing null, but there always is one?
            uByte Dummy;
            if(!Read(fp,&Dummy,1,Error)) { Error += Format("\nUnable to read actor path terminator at %lu bytes",Pos); return false; }
            Pos += 1;
            
            //printf("Actor: %s.\n",m_Data);
        }
        else if(Type == "ID")
        {
            m_Data = new uByte[m_Header->GetDataSize()];
            if(!Read(fp,m_Data,m_Header->GetDataSize(),Error)) { Error += Format("\nUnable to read actor ID at %lu bytes",Pos); return false; }
            Pos += m_Header->GetDataSize();
            //printf("ID: %d.\n",int(m_Data[0]));
        }
        else if(Type == "NAME")
        {
            m_Data = new uByte[m_Header->GetDataSize()];
            if(!Read(fp,m_Data,m_Header->GetDataSize(),Error)) { Error += Format("\nUnable to read actor name at %lu bytes",Pos); return false; }
            Pos += m_Header->GetDataSize();
            //printf("Name: %s.\n",m_Data);
        }
        else if(Type == "POS" || Type == "ROT" || Type == "SCALE")
        {
            m_Data = new uByte[m_Header->GetDataSize()];
            if(!Read(fp,m_Data,m_Header->GetDataSize(),Error)) { Error += Format("\nUnable to read actor %s at %lu bytes",Type.c_str(),Pos); return false; }
            Pos += m_Header->GetDataSize();
            //printf("%s: %f,%f,%f.\n",Type.c_str(),((float*)m_Data)[0],((float*)m_Data)[1],((float*)m_Data)[2]);
        }
        else if(Type == "ACTOR_VARIABLES")
        {
            //printf("Actor Variables: %d bytes.\n",(int)m_Header->GetDataSize());
        }
        else if(Type == "W_SP")
        {
            m_Data = new uByte[m_Header->GetDataSize()];
            if(!Read(fp,m_Data,m_Header->GetDataSize(),Error)) { Error += Format("\nUnable to read actor W_SP at %lu bytes",Pos); return false; }
            Pos += m_Header->GetDataSize();
            //printf("W_SP: %d.\n",int(m_Data[0]));
        }
        else if(Type == "W_FON")
        {
            m_Data = new uByte[m_Header->GetDataSize()];
            if(!Read(fp,m_Data,m_Header->GetDataSize(),Error)) { Error += Format("\nUnable to read actor W_FON at %lu bytes",Pos); return false; }
            Pos += m_Header->GetDataSize();
            //printf("W_FON: %s.\n",m_Data);
        }
        else if(Type == "W_TMF")
        {
            m_Data = new uByte[m_Header->GetDataSize()];
            if(!Read(fp,m_Data,m_Header->GetDataSize(),Error)) { Error += Format("\nUnable to read actor W_TMF at %lu bytes",Pos); return false; }
            Pos += m_Header->GetDataSize();
            //printf("W_TMF: %s.\n",m_Data);
        }
        else
        {
            //We don't know what it is yet, consume the data to skip over it
            m_Data = new uByte[m_Header->GetDataSize()];
            if(!Read(fp,m_Data,m_Header->GetDataSize(),Error)) { Error += Format("\nUnable to read unknown block type <%s> at %lu bytes",Type.c_str(),Pos); return false; }
            Pos += m_Header->GetDataSize();
            //printf("Unknown Block: %15s Size: %6d bytes : at %7lu bytes.\n",Type.c_str(),(int)m_Header->GetDataSize(),Pos - m_Header->GetDataSize());
        }
        
        
        while((Pos - OldPos) < m_Header->GetDataSize())
		{
			ATIBlock* Block = new ATIBlock();
            
			if(!Block->Load(fp,Error,Pos))
			{
				delete Block;
				return false;
			}

			m_Children.push_back(Block);
		}
        
        /*
        m_Data = m_Header->Load(fp,Error,Pos);
        if(!m_Data)
        {
            Error += "\nFailed to read ATI block";
            delete m_Header;
            m_Header = 0;
            return false;
        }
        
        printf("Loaded %s at %lu: %s: %lu bytes (%lu children).\n", m_Header->GetHeaderTypeName().c_str(),
                                                                    OldPos,
                                                                    m_Header->GetBlockType().c_str(),
                                                                    m_Header->GetDataSize(),
                                                                    m_Children.size());
        */
        
        return true;
	}
	bool ATIBlock::Save(FILE* fp,string& Error,size_t& Pos)
	{
        return false;
	}
};