#include "T4Loader/ATI.h"
#include "T4Loader/Common.h"
using namespace T4;

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

#ifdef __APPLE__
#include <unistd.h>
#endif

class MinMax
{
    public:
        MinMax() : Min(0), Max(0) { }
        ~MinMax() { }
    
        size_t Min;
        size_t Max;
};

unordered_map<string,u32> BlockTypeCounts;
unordered_map<string,size_t> BlockTypeSizes;
unordered_map<string,MinMax> BlockTypeSizeRange;
unordered_map<string,bool> BlockTypeConstant;
unordered_map<string,vector<ATIBlock*> > BlockData;

void ProcessBlock(ATIBlock* Block)
{
    if(BlockTypeCounts.find(Block->GetHeaderType()->GetBlockType()) == BlockTypeCounts.end())
    {
        BlockTypeCounts     [Block->GetHeaderType()->GetBlockType()] = 1;
        BlockTypeSizes      [Block->GetHeaderType()->GetBlockType()] = Block->GetHeaderType()->GetDataSize();
        BlockTypeConstant   [Block->GetHeaderType()->GetBlockType()] = true;
        BlockData           [Block->GetHeaderType()->GetBlockType()].push_back(Block);
    }
    else
    {
        if(BlockTypeSizes[Block->GetHeaderType()->GetBlockType()] != Block->GetHeaderType()->GetDataSize())
        {
            BlockTypeConstant[Block->GetHeaderType()->GetBlockType()] = false;
            MinMax& m = BlockTypeSizeRange[Block->GetHeaderType()->GetBlockType()];
            
            if(Block->GetHeaderType()->GetDataSize() < m.Min) m.Min = Block->GetHeaderType()->GetDataSize();
            else if(Block->GetHeaderType()->GetDataSize() > m.Max) m.Max = Block->GetHeaderType()->GetDataSize();
        }
        BlockTypeCounts[Block->GetHeaderType()->GetBlockType()]++;
        BlockData      [Block->GetHeaderType()->GetBlockType()].push_back(Block);
    }
    
    for(u32 i = 0;i < Block->GetChildren().size();i++)
    {
        ProcessBlock(Block->GetChildren()[i]);
    }
}

int main(int ArgC,const char* ArgV[])
{
    #ifdef __APPLE__
    
    string Dir(ArgV[0]);
    Dir = Dir.substr(0,Dir.find_last_of("/"));
    chdir(Dir.c_str());
    
    #endif
    
    const char* Fmt = "atr";
    int TestCount = 2033;//54;//125
    cout << "Loading " << TestCount << " " << Fmt << " files..." << endl;
    for(u16 i = 0;i < TestCount;i++)
    {
        //cout << Format("Loading Test%d.%s...",int(i),Fmt) << endl;
        ATI ActorInstances;
        if(!ActorInstances.Load(Format("Actors/ATR/Test%d.%s",int(i),Fmt).c_str()))
        {
            cout << ActorInstances.GetError() << endl;
            break;
        }
        //cout << "Successfully opened ATI file." << endl;
        
        vector<ATIBlock*> Blocks = ActorInstances.GetBlocks();
        for(u32 b = 0;b < Blocks.size();b++) ProcessBlock(Blocks[b]);
    }
    
    vector<u32> Counts;
    vector<string>Strs;
    vector<vector<ATIBlock*> > Blocks;
    
    for(unordered_map<string,u32>::iterator i = BlockTypeCounts.begin();i != BlockTypeCounts.end();i++)
    {
        if(Counts.size() == 0) { Counts.push_back(i->second); Strs.push_back(i->first); }
        else
        {
            bool Inserted = false;
            for(u32 c = 0;c < Counts.size();c++)
            {
                if(Counts[c] > i->second)
                {
                    Inserted = true;
                    Counts.insert(Counts.begin() + c,i->second);
                    Strs.insert(Strs.begin() + c,i->first);
                    break;
                }
            }
            if(!Inserted)
            {
                Counts.push_back(i->second);
                Strs.push_back(i->first);
            }
        }
    }
    
    printf("%lu known block types\n",Counts.size());
    for(int i = (int)Counts.size() - 1;i >= 0;i--)
    {
        string Str0;
        if(!BlockTypeConstant[Strs[i]])
        {
            MinMax& m = BlockTypeSizeRange[Strs[i]];
            Str0 = Format("Min: %7d B Max %7d B",m.Min,m.Max);
        }
        else Str0 = Format("Constant: %16d B",BlockTypeSizes[Strs[i]]);
        printf("[%30s][%s] Used %5d times\n",Strs[i].c_str(),Str0.c_str(),Counts[i]);
    }
    
    printf("Guessing block data types...\n");
    unordered_map<string,string> Notes;
    for(unordered_map<string,vector<ATIBlock*> >::iterator i = BlockData.begin();i != BlockData.end();i++)
    {
        printf("Analyzing block type: %s: ",i->first.c_str());
        
        bool   ConstSize = BlockTypeConstant [i->first];
        size_t Size      = BlockTypeSizes    [i->first];
        MinMax Range     = BlockTypeSizeRange[i->first];
        
        if(ConstSize)
        {
            switch(Size)
            {
                case 1:
                {
                    uByte Min = *i->second[0]->GetData();
                    uByte Max = Min;
                    
                    for(int b = 0;b < i->second.size();b++)
                    {
                        ATIBlock* Block = i->second[b];
                        uByte Val = *Block->GetData();
                        if(Val < Min) Min = Val;
                        if(Val > Max) Max = Val;
                    }
                    printf("Byte: Min: %d Max %d (0x%X to 0x%X).\n",(u32)Min,(u32)Max,Min,Max);
                    break;
                }
                case 2:
                {
                    s16 Min = *(s16*)i->second[0]->GetData();
                    s16 Max = Min;
                    
                    for(int b = 0;b < i->second.size();b++)
                    {
                        ATIBlock* Block = i->second[b];
                        s16 Val = *(s16*)Block->GetData();
                        if(Val < Min) Min = Val;
                        if(Val > Max) Max = Val;
                    }
                    printf("int16: Min: %d Max %d (0x%X to 0x%X).\n",Min,Max,Min,Max);
                    break;
                }
                case 4:
                {
                    s32 Min = *(s32*)i->second[0]->GetData();
                    s32 Max = Min;
                    f32 fMin = *(f32*)i->second[0]->GetData();
                    f32 fMax = fMin;
                    
                    for(int b = 0;b < i->second.size();b++)
                    {
                        ATIBlock* Block = i->second[b];
                        s32 Val = *(s32*)Block->GetData();
                        if(Val < Min) Min = Val;
                        if(Val > Max) Max = Val;
                        
                        f32 fVal = *(f32*)Block->GetData();
                        if(fVal < fMin) fMin = fVal;
                        if(fVal > fMax) fMax = fVal;
                    }
                    if(( Min > -1000000 &&  Min < 1000000) && ( Max > -1000000 &&  Max < 1000000)) printf("int32: Min: %d Max %d.\n",Min,Max);
                    else if((fMin > -1000000 && fMin < 1000000) && (fMax > -1000000 && fMax < 1000000)) printf("float32: Min: %f Max %f.\n",fMin,fMax);
                    else printf("Unsure...\n");
                    break;
                }
                default:
                {
                    printf("Unsure...\n");
                }
            }
        }
        else
        {
            printf("Unsure...\n");
        }
    }

	//cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
	return 0;
}

