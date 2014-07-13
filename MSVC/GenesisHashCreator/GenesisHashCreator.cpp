// GenesisHashCreator.cpp : Defines the entry point for the console application.
//
#include "..\..\src\main.h"
#include "..\..\src\util.h"

using namespace std;
using namespace boost;

int main(int argc, char* argv[])
{
   fPrintToConsole = true;
   printf("Enter your line of text you wish to use to make the genesis block\nOr just hit return to test your changes:\n");
   std::string line;
   std::getline(std::cin, line);
   if (line.empty())
      printf("nothing entered, will use compiled string, time, and nonce values\n");
   else
      printf("will use this: %s\n", line.data());
   
   
   // Genesis block
   uint256 hashGenesisBlock;
   const char* pszTimestamp = "It's a wonderful, Lego Universe!";
   hashGenesisBlock = uint256("0x76ea165ff8258061e9007ad2efa619ddaeaf2efad1519e828200362434fc1457");
   CTransaction txNew;
   txNew.vin.resize(1);
   txNew.vout.resize(1);
   if (line.empty())
      txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
   else
      txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>(line.data(), line.data() + line.length());
   txNew.vout[0].nValue = 50 * COIN;
   txNew.vout[0].scriptPubKey = CScript() << ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;
   CBlock block;
   block.vtx.push_back(txNew);
   block.hashPrevBlock = 0;
   block.hashMerkleRoot = block.BuildMerkleTree();
   assert(block.hashMerkleRoot == uint256("0x2ded040aee6643d3c49d264245371e6b8489e45ba1d4582a39b1ff2caea0f2fe"));
   block.nVersion = 1;
   block.nBits    = 0x1e0ffff0;
   block.nTime = 1394647973;
   block.nNonce = 2090133410;
   if (!line.empty())
      block.nTime = GetTime();
   

   uint256 hash = block.GetHash();
   
   static CBigNum bnProofOfWorkLimit(~uint256(0) >> 4);
   // If genesis block hash does not match, then generate new genesis hash.
   if (block.GetHash() != hashGenesisBlock)
   {
      printf("Searching for genesis block...\n");
      // This will figure out a valid hash and Nonce if you're
      // creating a different genesis block:
      uint256 hashTarget = CBigNum().SetCompact(block.nBits).getuint256();
       uint256 thash;
      char scratchpad[SCRYPT_SCRATCHPAD_SIZE];

      loop
      {
         scrypt_1024_1_1_256_sp(BEGIN(block.nVersion), BEGIN(thash), scratchpad);
         if (thash <= hashTarget) {
            printf("Found one!!!\n");
            break;
         }
         if ((block.nNonce & 0xFFF) == 0)
         {
           // printf("nonce %08X: hash = %s (target = %s)\n", block.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
         }
         ++block.nNonce;
         if (block.nNonce == 0)
         {
            //printf("NONCE WRAPPED, incrementing time\n");
            ++block.nTime;
         }
      }
      printf("Here are the new lines of code:\n");
      printf("const char* pszTimestamp = \"%s\";\n",line.data());
      printf("hashGenesisBlock = uint256(\"%s\");\n", block.GetHash().ToString().c_str());
      printf("merkle root = %s\n", block.hashMerkleRoot.ToString().c_str());
      printf("block.nTime = %u; \n", block.nTime);
      printf("block.nNonce = %u; \n", block.nNonce);
      printf("\n\nHere is the block:\n");
      block.print();
   }
   else {
      printf("It all looks good!\n\n");
      printf("const char* pszTimestamp = \"%s\";\n", pszTimestamp);
      printf("merkle root = %s\n", block.hashMerkleRoot.ToString().c_str());
      printf("block.nTime = %u \n", block.nTime);
      printf("block.nNonce = %u \n", block.nNonce);
      printf("block.GetHash = %s\n", block.GetHash().ToString().c_str());
      printf("\n\nHere is the block:\n");
      block.print();
   }

   printf("Hit return to end this\n");
   std::getline(std::cin, line);
   return 0;
}

