#include "ATI.h"
#include "Common.h"
using namespace T4;

#include <iostream>
#include <unordered_map>
using namespace std;

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

void ProcessBlock(ATIBlock* Block)
{
    if(BlockTypeCounts.find(Block->GetHeaderType()->GetBlockType()) == BlockTypeCounts.end())
    {
        BlockTypeCounts     [Block->GetHeaderType()->GetBlockType()] = 1;
        BlockTypeSizes      [Block->GetHeaderType()->GetBlockType()] = Block->GetHeaderType()->GetDataSize();
        BlockTypeConstant   [Block->GetHeaderType()->GetBlockType()] = true;
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
    }
    
    for(u32 i = 0;i < Block->GetChildren().size();i++)
    {
        ProcessBlock(Block->GetChildren()[i]);
    }
}

int main(int ArgC,const char* ArgV[])
{
    const char* Fmt = "atr";
    int TestCount = 2033;//54;//125
    
    for(u16 i = 0;i < TestCount;i++)
    {
        cout << Format("Loading Test%d.%s...",int(i),Fmt) << endl;
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
            Str0 = Format("Min: %5d B Max %5d B",m.Min,m.Max);
        }
        else Str0 = Format("Constant: %12d B",BlockTypeSizes[Strs[i]]);
        printf("[%25s][%s] Used %5d times\n",Strs[i].c_str(),Str0.c_str(),Counts[i]);
    }

	//cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
	return 0;
}

