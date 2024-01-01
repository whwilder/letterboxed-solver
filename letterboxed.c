#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

struct match{
   char* str;
   float score;
   int len;
};

int main(int arc, char** argv)
{
   char* wordFile = "./words_alpha.txt";
   //char* wordFile = "/usr/share/dict/words";
   char** words;
   size_t length;
   ssize_t read;
   FILE* fp;
   
   words = malloc(466550 * sizeof(size_t));
   fp = fopen(wordFile, "r");
   if(fp == NULL){
      exit(2);
   }

   //unsigned char b1[3] = { ((unsigned char)'m'), ((unsigned char)'d'), ((unsigned char)'o') };
   //unsigned char b2[3] = { ((unsigned char)'s'), ((unsigned char)'r'), ((unsigned char)'u') };
   //unsigned char b3[3] = { ((unsigned char)'e'), ((unsigned char)'p'), ((unsigned char)'t') };
   //unsigned char b4[3] = { ((unsigned char)'a'), ((unsigned char)'q'), ((unsigned char)'x') };

   //unsigned char bytes[4][3] = {{ ((unsigned char)'m'), ((unsigned char)'d'), ((unsigned char)'o') },
   // { ((unsigned char)'s'), ((unsigned char)'r'), ((unsigned char)'u') },
   // { ((unsigned char)'e'), ((unsigned char)'p'), ((unsigned char)'t') },
   // { ((unsigned char)'a'), ((unsigned char)'q'), ((unsigned char)'x') }};

   int matches = 0;
   int wordIdx = 0;
   uint32_t idxs = 0x04030201;
   char* word = malloc(100 * sizeof(char));
   int len = 0;
   struct match* matchingWords = malloc(466550 * sizeof(struct match));;
   while ((read = getline(&word, &length, fp)) != -1) {
      wordIdx++;
      word[read-1] = '\0';
      word[read-2] = '\0';
      len = read - 2;


   //b1 = args[0].ToArray().Select(ch => ((byte)ch)).ToArray();
   //b2 = args[1].ToArray().Select(ch => ((byte)ch)).ToArray();
   //b3 = args[2].ToArray().Select(ch => ((byte)ch)).ToArray();
   //b4 = args[3].ToArray().Select(ch => ((byte)ch)).ToArray();

   unsigned char bytes[4][3] = {{argv[1][0], argv[1][1], argv[1][2]},
                                {argv[2][0], argv[2][1], argv[2][2]},
                                {argv[3][0], argv[3][1], argv[3][2]},
                                {argv[4][0], argv[4][1], argv[4][2]}
   };

   //unsigned char* bytes[4] = { b1, b2, b3, b4 };
   //List<string> letters = new List<string>() { "mdo", "sru", "ept", "aqx" };
   //List<string> optimalSolution = new List<string>() { "masquerade", "export" };
   //List<string> letters = new List<string>() { "esp", "ltm", "obi", "chr" };
   //List<string> letters = Console.ReadLine().Split(" ").ToList();
   //List<string> letters = new List<string>() { args[0], args[1], args[2], args[3]};
   //byte[] idxs = new byte[] { 0, 1, 2, 3 };
   //List<Tuple<string, float>> matchingWords = new List<Tuple<string, float>>();
   //words = new List<string>() { "masquerade" };
   //words = new List<string>() { "adamsite" };
       unsigned char ch = (unsigned char)word[0]; // get the last 5 bits of the char, we don't care about the leading two
       //Console.WriteLine(Convert.ToString(ch, 2));
       //Console.WriteLine(Convert.ToString(ch | ch << 8 | ch << 16, 2).PadLeft(32, '0'));
       uint32_t i1 = (uint32_t)(bytes[0][0] | bytes[0][1] << 8 | bytes[0][2] << 16);
       uint32_t i2 = (uint32_t)(bytes[1][0] | bytes[1][1] << 8 | bytes[1][2] << 16);
       uint32_t i3 = (uint32_t)(bytes[2][0] | bytes[2][1] << 8 | bytes[2][2] << 16);
       uint32_t i4 = (uint32_t)(bytes[3][0] | bytes[3][1] << 8 | bytes[3][2] << 16);

       //Console.WriteLine(Convert.ToString(i1, 2).PadLeft(32, '0'));
       //Console.WriteLine(Convert.ToString(i2, 2).PadLeft(32, '0'));
       //Console.WriteLine(Convert.ToString(i3, 2).PadLeft(32, '0'));
       //Console.WriteLine(Convert.ToString(i4, 2).PadLeft(32, '0'));

       uint32_t a1 = (uint32_t)(i1 ^ ch ^ (ch << 8) ^ (ch << 16) | 0xff000000);
       uint32_t a2 = (uint32_t)(i2 ^ ch ^ (ch << 8) ^ (ch << 16) | 0xff000000);
       uint32_t a3 = (uint32_t)(i3 ^ ch ^ (ch << 8) ^ (ch << 16) | 0xff000000);
       uint32_t a4 = (uint32_t)(i4 ^ ch ^ (ch << 8) ^ (ch << 16) | 0xff000000);

       //Console.WriteLine(Convert.ToString(a1, 2));
       //Console.WriteLine(Convert.ToString(a2, 2));
       //Console.WriteLine(Convert.ToString(a3, 2));
       //Console.WriteLine(Convert.ToString(a4, 2));
       //Console.WriteLine();

       //uint a = (uint)(BitOperations.PopCount((a1 - 0x01010101) & ~(a1) & 0x80808080));
       //uint b = (uint)(BitOperations.PopCount((a2 - 0x01010101) & ~(a2) & 0x80808080));
       //uint c = (uint)(BitOperations.PopCount((a3 - 0x01010101) & ~(a3) & 0x80808080));
       //uint d = (uint)(BitOperations.PopCount((a4 - 0x01010101) & ~(a4) & 0x80808080));
       uint32_t a = (uint32_t)__builtin_popcount(~((((a1 & 0x7F7F7F7F) + 0x7F7F7F7F) | a1) | 0x7F7F7F7F));
       uint32_t b = (uint32_t)__builtin_popcount(~((((a2 & 0x7F7F7F7F) + 0x7F7F7F7F) | a2) | 0x7F7F7F7F));
       uint32_t c = (uint32_t)__builtin_popcount(~((((a3 & 0x7F7F7F7F) + 0x7F7F7F7F) | a3) | 0x7F7F7F7F));
       uint32_t d = (uint32_t)__builtin_popcount(~((((a4 & 0x7F7F7F7F) + 0x7F7F7F7F) | a4) | 0x7F7F7F7F));
       //Console.WriteLine(Convert.ToString(a, 2));
       //Console.WriteLine(Convert.ToString(b, 2));
       //Console.WriteLine(Convert.ToString(c, 2));
       //Console.WriteLine(Convert.ToString(d, 2));
       //Console.WriteLine();

       //bool a = letters[0].Contains(word[0].ToString());
       //bool b = letters[1].Contains(word[0].ToString());
       //bool c = letters[2].Contains(word[0].ToString());
       //bool d = letters[3].Contains(word[0].ToString());
       uint32_t abcd = a | (b << 1) | (c << 2) | (d << 3);
       unsigned int idx;
           __asm__(
            "mov %1, %%eax\n"      // copy abcd into %eax register
            "tzcnt %%eax, %1\n" // get trailing zeroes, store in idx
            :"=r" (idx)            // %0: output variable list
            :"r" (abcd)            // %1: input variable list
            :"%eax"                // Overwritten registers (may need to change which register is used)
      );

       //Console.WriteLine(Convert.ToString(idx, 2));

       //List<bool> arr = new List<bool> { a > 0,b > 0,c > 0,d > 0};
       //int idx = arr.IndexOf(true);
       if(idx == 32)
       {
           continue;
       }
       //Console.WriteLine(letters[indexes[idx]] + " " + indexes[idx]);
       //uint test = (uint)(idxs ^ (idx + 1) ^ ((idx + 1) << 8) ^ ((idx + 1) << 16) ^ ((idx + 1) << 24));
       uint32_t test = (uint32_t)(idxs ^ ((idx+1) << (idx * 8)));
       //uint test = (uint)(idxs >> ((~idx + 1) * 8));
       //uint test = (uint)(idxs ^ ((idx + 1) << ((idx) * 8)));
       //uint n = (((0xffff0000 & test) >> (((idx + 1) & 1) * 8) >> (idx & 1) * 8) | (0x0000ffff & test >> (((idx - 1) & 1) * 8)));
       uint32_t n = ((((0xffff0000 & test) >> ((((idx+1) & 3) >> (((idx+1)) >> 1)))*8)) | ((0x0000ffff & test) >> ((((idx+1) & 1) & ~(idx >> 1)) * 8)));
       //n >>= (((((idx) >> 1) ^ 1) & 1) * 8);

       //Console.WriteLine(Convert.ToString(test, 16));
       //Console.WriteLine(Convert.ToString(n, 16));

       //byte n = (byte)(BitOperations.TrailingZeroCount(~((((test & 0x7F7F7F7F) + 0x7F7F7F7F) | test) | 0x7F7F7F7F))/8);

       //List<int> availIndexes = indexes.Where(i => i != idx).ToList();
       bool isMatch = true;
       //availIndexes.Reverse<int>().ToList().ForEach(ix => Console.Write((ix + 1).ToString("D2")));
       //Console.WriteLine();

       for (int j = 1; j < len; j++)
       {
           //Console.WriteLine(string.Join(" ", availIndexes));

           ch = (char)word[j]; // get the last 5 bits of the char, we don't care about the leading two
           //i1 = (uint)(bytes[availIndexes[0]][0] | bytes[availIndexes[0]][1] << 8 | bytes[availIndexes[0]][2] << 16);
           //i2 = (uint)(bytes[availIndexes[1]][0] | bytes[availIndexes[1]][1] << 8 | bytes[availIndexes[1]][2] << 16);
           //i3 = (uint)(bytes[availIndexes[2]][0] | bytes[availIndexes[2]][1] << 8 | bytes[availIndexes[2]][2] << 16);
           i1 = (uint32_t)(bytes[(int)((n & 0x0000ff) - 1)][0] | bytes[(int)(n & 0x0000ff) - 1][1] << 8 | bytes[(int)(n & 0x0000ff) - 1][2] << 16);
           i2 = (uint32_t)(bytes[(int)(((n & 0x00ff00) >> 8) - 1)][0] | bytes[(int)(((n & 0x00ff00) - 1) >> 8)][1] << 8 | bytes[(int)(((n & 0x00ff00) >> 8) - 1)][2] << 16);
           i3 = (uint32_t)(bytes[(int)(((n & 0xff0000) >> 16) - 1)][0] | bytes[(int)(((n & 0xff0000) - 1) >> 16)][1] << 8 | bytes[(int)(((n & 0xff0000) >> 16) - 1)][2] << 16);

           a1 = (uint32_t)(i1 ^ ch ^ (ch << 8) ^ (ch << 16) | 0xff000000);
           a2 = (uint32_t)(i2 ^ ch ^ (ch << 8) ^ (ch << 16) | 0xff000000);
           a3 = (uint32_t)(i3 ^ ch ^ (ch << 8) ^ (ch << 16) | 0xff000000);

           a = (uint32_t)(__builtin_popcount(~((((a1 & 0x7F7F7F7F) + 0x7F7F7F7F) | a1) | 0x7F7F7F7F)));
           b = (uint32_t)(__builtin_popcount(~((((a2 & 0x7F7F7F7F) + 0x7F7F7F7F) | a2) | 0x7F7F7F7F)));
           c = (uint32_t)(__builtin_popcount(~((((a3 & 0x7F7F7F7F) + 0x7F7F7F7F) | a3) | 0x7F7F7F7F)));

           //a = letters[availIndexes[0]].Contains(word[i].ToString());
           //b = letters[availIndexes[1]].Contains(word[i].ToString());
           //c = letters[availIndexes[2]].Contains(word[i].ToString());
           abcd = a | (b << 1) | (c << 2);
    __asm__(
      "mov %1, %%eax\n"      // copy abcd into %eax register
      "tzcnt %%eax, %0\n" // get trailing zeroes, store in idx
      :"=r" (idx) // %0: output variable list
      :"r" (abcd)             // %1: input variable list
      :"%eax"                // Overwritten registers (may need to change register used)
   );


           //arr = new List<bool> { a>0, b>0, c>0 };
           //idx = arr.IndexOf(true);
           if (idx == 32)
           {
               isMatch = false;
               break;
           }
           unsigned char x = (unsigned char)((n & ((0xff) << (idx)*8)) >> (idx)*8);
           test = (uint32_t)(idxs ^ ((x) << ((x-1) * 8)));
           //n = (((0xffff0000 & test) >> (((idx + 1) & 1) * 8)) | ((0x0000ffff & test) >> (((((idx) >> 1) ^ 1) & 1) * 8)));
           n = ((((0xffff0000 & test) >> ((((x) & 3) >> (((x)) >> 1))) * 8)) | ((0x0000ffff & test) >> ((((x) & 1) & ~(x >> 1)) * 8)));
           //Console.WriteLine(Convert.ToString(test, 16));
           //Console.WriteLine(Convert.ToString(n, 16));
           //Console.WriteLine(idx);
           //Console.WriteLine(letters[availIndexes[idx]] + " " + availIndexes[idx]);
           //availIndexes = indexes.Where(ix => ix != indexes[availIndexes[idx]]).ToList();
           //availIndexes.Reverse<int>().ToList().ForEach(ix => Console.Write((ix + 1).ToString("D2")));
           //Console.WriteLine();
       }
       if (!isMatch)
       {
           continue;
       }
      if(len > 2){
         matchingWords[matches].str = malloc(len * sizeof(char));
         strcpy(matchingWords[matches].str, word);
         //matchingWords[matches].str = word;
         matchingWords[matches].len = len;
         matches++;
      }
       //matchingWords.Add(Tuple.Create(word, (float) word.Distinct().Count() / (float) word.Length ));
   }
   //matchingWords = matchingWords.Where(w => w.Item1.Length > 4 && w.Item2 > 0.7).ToList();

   struct match* ends[32];
   struct match* starts[32];
   int startIdxs[32] = {0};
   int endIdxs[32] = {0};
   for(int i = 0; i < 32; i++)
   {
      ends[i] = malloc(200 * sizeof(struct match));
      starts[i] = malloc(200 * sizeof(struct match));
   }
   for (int i = 0; i < matches; i++)
   {
      struct match s = matchingWords[i];
       char* word = s.str;
       uint32_t letters = 0;
       for (int i = 0; i < s.len; i++)
       {
           letters = (letters | (uint32_t) (1 << (((unsigned char)word[i]) & 0x1f)));  // get last 5 bits of char
       }
       //if(BitOperations.PopCount(letters) < 8)
       //{
       //    continue;
       //}


       unsigned char first = (unsigned char)(word[0] & 0x1f);
       unsigned char last = (unsigned char)(word[s.len - 1] & 0x1f);

      ends[last][endIdxs[last]] = s;
      starts[first][startIdxs[first]] = s;
      endIdxs[last]++;
      startIdxs[first]++;
   }

   //List<string> pairs = new List<string>();
   //char** pairs = malloc(200 * sizeof(size_t));

   for(int i = 0; i < 31; i++)
   {
       for(int j = 0; j < endIdxs[i]; j++)
       {
           for(int k = 0; k < startIdxs[i]; k++)
           {
               struct match a = ends[i][j];
               struct match b = starts[i][k];
               char word[100];
               strcpy(word, a.str);
               strcpy(word+a.len, b.str);
               uint32_t letters = 0;
               for (int l = 0; l < a.len + b.len; l++)
               {
                   letters = (letters | (uint32_t)(1 << (((unsigned char)word[l]) & 0x1f)));
               }
               if(__builtin_popcount(letters) == 12)
                  printf("%s %s\n", a.str, b.str);
                   //pairs.Add(a + " " + b);
           }
       }
   }

   //foreach (Tuple<string, float> pair in matchingWords)
   //{
   //    List<Tuple<string, bool>> matchingEnds = matchingWords.Where(w => pair.Item1[0] == w.Item1[w.Item1.Length - 1])
   //        .Select(w => Tuple.Create(w.Item1 + " " + pair.Item1, (pair.Item1 + w.Item1).Distinct().Count() == 12)).ToList();
   //    pairs.AddRange(matchingEnds.Where(w => w.Item2).Select(w => w.Item1).ToList());
   //}

   //Console.WriteLine(words.Count);
   //Console.WriteLine(matchingWords.Count);
   //matchingWords.ForEach(w => Console.WriteLine(w));
   //pairs.OrderBy(w => w.Length).ToList().ForEach(w => Console.WriteLine(w));

   //Console.ReadLine();
}
