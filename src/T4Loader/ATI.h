#pragma once
#include <stdio.h>

#include <vector>
#include <string>
using namespace std;

#include "ATITypes.h"
#include "ActorInstance.h"

 namespace T4
 {
	class ATIBlock;
	class ATI
	{
		public:
			ATI();
			~ATI();

			bool Load(const char* File);
			bool Save(const char* File);
			string GetError() const { return m_Error; }
        
            vector<ATIBlock*>& GetBlocks() { return m_Blocks; }

		protected:
			string m_Error;
			char m_Signature[4];
			vector<ATIBlock*>m_Blocks;
	};

	class ATIBlock
	{
		public:
			ATIBlock() { m_Header = 0; m_DataSize = 0; m_Data = 0; }
			~ATIBlock() { if(m_Header) delete m_Header; if(m_Data) delete [] m_Data; };

			bool Load(FILE* fp,string& Error,size_t& Pos);
			bool Save(FILE* fp,string& Error,size_t& Pos);
        
            
            vector<ATIBlock*>& GetChildren() { return m_Children; }
            size_t GetDataSize() { return m_DataSize; }
            uByte* GetData() { return m_Data; }
            BlockHeaderType* GetHeaderType() { return m_Header; }

		protected:
            friend class ATI;
            BlockHeaderType*  m_Header;
            vector<ATIBlock*> m_Children;
        
            size_t m_DataSize;
            uByte* m_Data;
	};
 };