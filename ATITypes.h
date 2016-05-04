#pragma once
#include "T4Types.h"
#include <stdio.h>
#include <string>
using namespace std;

namespace T4
{
	class BlockHeaderType
	{
		public:
			BlockHeaderType() { }
			virtual ~BlockHeaderType() { }

			virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos) = 0;
			virtual bool	Save(FILE* fp,string& Error,size_t& Pos) = 0;

			virtual u8		GetSignature() const = 0;
			virtual size_t	GetDataSize() const = 0;
            virtual string  GetBlockType() const { return m_TypeName; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Unknown"; }
			virtual string  GetHeaderTypeInfo() const { return "Unknown"; }
            virtual size_t  GetHeaderSize() const = 0;
        
        protected:
            string m_TypeName;
	};

	class BlockHeaderA : public BlockHeaderType
	{
        public:
            BlockHeaderA() { }
            ~BlockHeaderA() { }
        
            virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0x82; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header A"; }
			virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 2 byte data size, 1 byte name length, name string"; }
            virtual size_t  GetHeaderSize() const { return 5 + m_TypeName.length(); }
        
        protected:
            u8  m_Unknown0;
            u16 m_DataSize;
	};
    
    class BlockHeaderB : public BlockHeaderType
	{
        public:
            BlockHeaderB() { }
            ~BlockHeaderB() { }
        
            virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0x42; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header B"; }
			virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 1 byte data size, 1 byte name length, name string"; }
            virtual size_t  GetHeaderSize() const { return 4 + m_TypeName.length(); }
        
        protected:
            u8 m_Unknown0;
            u8 m_DataSize;
	};
    
    class BlockHeaderC : public BlockHeaderA
	{
        public:
            BlockHeaderC() { }
            ~BlockHeaderC() { }
        
            //virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			//virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0x81; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header C"; }
			virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 2 byte data size, 1 byte name length, name string"; }
            //virtual size_t  GetHeaderSize() const { return 5 + m_TypeName.length(); }
        
        protected:
            //u8 m_Unknown0;
            //u8 m_DataSize;
	};
    
    class BlockHeaderD : public BlockHeaderType
	{
        public:
            BlockHeaderD() { }
            ~BlockHeaderD() { }
        
            virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0xC2; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header D"; }
			virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 4 byte data size, 1 byte name length, name string"; }
            virtual size_t  GetHeaderSize() const { return 7 + m_TypeName.length(); }
        
        protected:
            u8 m_Unknown0;
            u32 m_DataSize;
	};
    
    class BlockHeaderE : public BlockHeaderD
	{
        public:
            BlockHeaderE() { }
            ~BlockHeaderE() { }
        
            //virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			//virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0xC1; }
			virtual size_t	GetDataSize() const { return m_DataSize; }
            //virtual size_t  GetHeaderSize() const { return 7 + m_TypeName.length(); }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header E"; }
			virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 4 byte data size, 1 byte name length, name string"; }
        
        protected:
            //u8 m_Unknown0;
            //u8 m_DataSize;
	};
    
    class BlockHeaderF : public BlockHeaderB
	{
        public:
            BlockHeaderF() { }
            ~BlockHeaderF() { }
        
            //virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			//virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0x45; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header F"; }
			//virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 1 byte data size, 1 byte name length, name string"; }
            //virtual size_t  GetHeaderSize() const { return 4 + m_TypeName.length(); }
        
        protected:
            //u8 m_Unknown0;
            //u8 m_DataSize;
	};
    
    class BlockHeaderG : public BlockHeaderB
	{
        public:
            BlockHeaderG() { }
            ~BlockHeaderG() { }
        
            //virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			//virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0x4B; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header G"; }
			//virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 1 byte data size, 1 byte name length, name string"; }
            //virtual size_t  GetHeaderSize() const { return 4 + m_TypeName.length(); }
        
        protected:
            //u8 m_Unknown0;
            //u8 m_DataSize;
	};
    
    class BlockHeaderH : public BlockHeaderB
	{
        public:
            BlockHeaderH() { }
            ~BlockHeaderH() { }
        
            //virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			//virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0x4A; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header H"; }
			//virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 1 byte data size, 1 byte name length, name string"; }
            //virtual size_t  GetHeaderSize() const { return 4 + m_TypeName.length(); }
        
        protected:
            //u8 m_Unknown0;
            //u8 m_DataSize;
	};
    
    class BlockHeaderI : public BlockHeaderType
    {
        public:
            BlockHeaderI() { }
            ~BlockHeaderI() { }
        
            virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0x61; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header I"; }
			virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 1 byte data size, 2 byte unknown, 1 byte name length, name string"; }
            virtual size_t  GetHeaderSize() const { return 4 + m_TypeName.length(); }
        
        protected:
            u8 m_Unknown0;
            u8 m_DataSize;
            u8 m_Unknown1;
            u8 m_Unknown2;
    };
    
    class BlockHeaderJ : public BlockHeaderB
	{
        public:
            BlockHeaderJ() { }
            ~BlockHeaderJ() { }
        
            //virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			//virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0x41; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header J"; }
			//virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 1 byte data size, 1 byte name length, name string"; }
            //virtual size_t  GetHeaderSize() const { return 4 + m_TypeName.length(); }
        
        protected:
            //u8 m_Unknown0;
            //u8 m_DataSize;
	};
    
    class BlockHeaderK : public BlockHeaderType
    {
        public:
            BlockHeaderK() { }
            ~BlockHeaderK() { }
        
            virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0xA1; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header K"; }
			virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 2 byte data size, 2 byte unknown, 1 byte name length, name string"; }
            virtual size_t  GetHeaderSize() const { return 4 + m_TypeName.length(); }
        
        protected:
            u8  m_Unknown0;
            u16 m_DataSize;
            u8  m_Unknown1;
            u8  m_Unknown2;
    };
    
    class BlockHeaderL : public BlockHeaderB
	{
        public:
            BlockHeaderL() { }
            ~BlockHeaderL() { }
        
            //virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			//virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0x47; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header L"; }
			//virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 1 byte data size, 1 byte name length, name string"; }
            //virtual size_t  GetHeaderSize() const { return 4 + m_TypeName.length(); }
        
        protected:
            //u8 m_Unknown0;
            //u8 m_DataSize;
	};
    
    class BlockHeaderM : public BlockHeaderB
	{
        public:
            BlockHeaderM() { }
            ~BlockHeaderM() { }
        
            //virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			//virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0x48; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header M"; }
			//virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 1 byte data size, 1 byte name length, name string"; }
            //virtual size_t  GetHeaderSize() const { return 4 + m_TypeName.length(); }
        
        protected:
            //u8 m_Unknown0;
            //u8 m_DataSize;
	};
    
    class BlockHeaderN : public BlockHeaderB
	{
        public:
            BlockHeaderN() { }
            ~BlockHeaderN() { }
        
            //virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			//virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0x46; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header M"; }
			//virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 1 byte data size, 1 byte name length, name string"; }
            //virtual size_t  GetHeaderSize() const { return 4 + m_TypeName.length(); }
        
        protected:
            //u8 m_Unknown0;
            //u8 m_DataSize;
	};
    
    class BlockHeaderO : public BlockHeaderB
	{
        public:
            BlockHeaderO() { }
            ~BlockHeaderO() { }
        
            //virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			//virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0x49; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header O"; }
			//virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 1 byte data size, 1 byte name length, name string"; }
            //virtual size_t  GetHeaderSize() const { return 4 + m_TypeName.length(); }
        
        protected:
            //u8 m_Unknown0;
            //u8 m_DataSize;
	};
    class BlockHeaderP : public BlockHeaderType
	{
        public:
            BlockHeaderP() { }
            ~BlockHeaderP() { }
        
            virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0xE1; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header O"; }
			virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 4 byte data size, 2 byte unknown, 1 byte name length, name string"; }
            virtual size_t  GetHeaderSize() const { return 7 + m_TypeName.length(); }
        
        protected:
            u8 m_Unknown0;
            u32 m_DataSize;
            u8 m_Unknown1;
            u8 m_Unknown2;
	};
    class BlockHeaderQ : public BlockHeaderI
    {
        public:
            BlockHeaderQ() { }
            ~BlockHeaderQ() { }
        
            //virtual uByte*  Load(FILE* fp,string& Error,size_t& Pos);
			//virtual bool	Save(FILE* fp,string& Error,size_t& Pos);
        
			virtual u8		GetSignature() const { return 0x6C; }
			virtual size_t	GetDataSize() const { return m_DataSize; }

			/* Additional info for documentation of the format */
			virtual string  GetHeaderTypeName() const { return "Block Header Q"; }
			//virtual string  GetHeaderTypeInfo() const { return "1 byte unknown, 1 byte data size, 2 byte unknown, 1 byte name length, name string"; }
            //virtual size_t  GetHeaderSize() const { return 4 + m_TypeName.length(); }
        
        protected:
            //u8 m_Unknown0;
            //u8 m_DataSize;
            //u8 m_Unknown1;
            //u8 m_Unknown2;
    };
};