//Matthew Smith-Kennedy
//ms11ag
//Project 6 COP4530
//This program accepts standard input and outputs statistics on word,number, and
//char use.  This program uses a map to store input and hit statistics, then
//passed to a sorted map (by key, and by first stored or lowest ascii value.

//Known issues:  none

#include <string>
#include <cctype>
#include <map>
#include <iostream>

using namespace std;

bool returnchar (char x)
{
  if (x>47 && x < 58)
  {
    return false;
  }
  else 
  {
    return true;
  }
}

bool validwordchar(char x)
{
  if (x>64 && x <91)
  {
    return true;
  }
  if (x>96 && x <123)
  {
    return true;
  }
  return false;
} 

bool returnnumber (char x)
{
  if (x>47 && x <58)
  {
    return true;
  }
  else
  {
    return false;
  }
}
typedef pair<int, int> GROUP;


int main()
{
  char input;
  map<char, int> charmap;  //used to store chars and charcouts
  map<string, int> wordmap;  //same for words
  map<string, int> numbermap;  //same for numbers
  map<string, int> wordusemap;  //stores word and first use (based on wordcount)
  map<string, int> numberusemap;  //stores numberstring and first use(based on numcount)
  bool charflag= false;  //flags for type of input processing
  bool numflag=false;
  bool wordflag=false;
  int wordcount=0; //global new word count
  int numcount=0;  //same for number
  int charcount=0; // same for char
  string numstring=""; //processing strings
  string wordstring="";
  map<char, int>::iterator itrChar;  //iterator for char type
  map<string, int>::iterator itrString;  //iterator for string map
  string wordcopy="";  //processing string to save for char processing

  while (cin.get(input))  //loop while not EOF
  {
    numstring="";
    wordstring=""; 
    wordcopy="";
    if (returnnumber(input))  //if number
    {
      while (returnnumber(input))
      {
        numstring=numstring+input;
        cin.get(input);
        numflag=true;
      }
      cin.putback(input);  //put back cause it needs processing on next loop
    } //end case for number
    else if (validwordchar(input))  //if valid char for word
    {
      while (validwordchar(input))
      {
        wordcopy=wordcopy+input;
        input=tolower(input);
        wordstring=wordstring+input;
        cin.get(input);
        wordflag=true;
      }
      cin.putback(input);  //put back cause it needs processing on next loop
    }  //end case for word and wordchars
    else if (returnchar(input))
    {
      
      charflag=true;
    }
    if (numflag)   //processing for numbers
    {
  
      if (!numbermap.insert(pair<string,int>(numstring, 1)).second)
      {
        numbermap[numstring]++;
      }
      else
      {
        ++numcount;
        numberusemap.insert(pair<string,int>(numstring,numcount));
      }
      //begin char processing of numberstring
      char letter;
      string::iterator itr;
      for (itr= numstring.begin(); itr!=numstring.end(); ++itr)
      {
        letter=*itr;
        if (!charmap.insert(pair<char,int>(letter, 1)).second)
        {
          charmap[letter]++;
        }
        else
        {
          ++charcount;
        }
      }

    } //end number processing

    else if (wordflag)  //processing for words/chars
    {
      if (!wordmap.insert(pair<string,int>(wordstring, 1)).second)
      {
        wordmap[wordstring]++;
      }
      else
      {
        ++wordcount;
        wordusemap.insert(pair<string,int>(wordstring,wordcount));
      }
      char letter;
      string::iterator itr;
      for (itr= wordcopy.begin(); itr!=wordcopy.end(); ++itr)
      {
        letter=*itr;
        if (!charmap.insert(pair<char,int>(letter, 1)).second)
        {
          charmap[letter]++;
        }
        else
        {
          ++charcount;
        }
      }
    }  //end word/char processing
    else if (charflag)
    {
      if (!charmap.insert(pair<char,int>(input, 1)).second)
      {
        charmap[input]++;
      }
      else
      {
        ++charcount;
      }
    }  //end single char processing 

    //    cin.get(input);
    wordflag=false;
    numflag=false;
    charflag=false;
    if (cin.eof()) {break;}
  }  //end while loop

   
  //begin char sort and print
  map <GROUP, char> charsortmap;

  for (itrChar=charmap.begin();itrChar!=charmap.end();++itrChar)
  {
    GROUP thing=pair<int, int>(itrChar->second,-(int)itrChar->first); 
    charsortmap.insert(pair<GROUP,char>(thing,itrChar->first));
  }

  map <GROUP, char>::reverse_iterator itrcharsort;
  int count=0;
  int topsize=9;
  if (charcount<10) {topsize=charcount-1;} 
  cout<<"Total "<<charcount<<" different characters, "<<topsize+1<<"  most used characters:\n";
  for (itrcharsort=charsortmap.rbegin();itrcharsort!=charsortmap.rend();++itrcharsort)
  {
    if (itrcharsort->second=='\n')
    {
      cout<<"No. "<<count<<": " <<"\\n\t\t"<<itrcharsort->first.first<<endl;
    } 
    else if (itrcharsort->second=='\t')
    {
      cout<<"No. "<<count<<": " <<"\\t\t\t"<<itrcharsort->first.first<<endl;
    }
    else
    {
      cout<<"No. "<<count<<": " <<itrcharsort->second<<"\t\t"<<itrcharsort->first.first<<endl;
    }
    if (count==9 || count==topsize)
    {
      break;
    }
    ++count;
  }
  //end char sort and print

  //begin word sort and print
  map <GROUP, string> wordsortmap;
  map<string, int>::iterator itrWordUse;
  itrWordUse=wordusemap.begin();
  for (itrString=wordmap.begin();itrString!=wordmap.end();++itrString)
  {
    GROUP thing=pair<int, int>(itrString->second,-(itrWordUse->second));
    wordsortmap.insert(pair<GROUP,string>(thing,itrString->first));
    ++itrWordUse;
  }

  map <GROUP, string>::reverse_iterator itrSort;
  count=0;
  topsize=9;
  if (wordcount<10) {topsize=wordcount-1;}
  cout<<"Total "<<wordcount<<" different words, "<<topsize+1<<" most used words:"<<endl;
  for (itrSort=wordsortmap.rbegin(); itrSort!=wordsortmap.rend(); ++itrSort)
  {
    cout<<"No. "<<count<<": " <<itrSort->second<<"\t\t"<<itrSort->first.first<<endl;
    // if (count==9 || count==topsize)
    // {
    //  break;
    // }
    ++count;
  }  //end word sort and print


  //begin number sort and print
  map <GROUP, string> numsortmap;
  map<string, int>::iterator itrNumUse;
  itrNumUse=numberusemap.begin();
  map<string, int>::iterator itrNum;
  for (itrNum=numbermap.begin();itrNum!=numbermap.end();++itrNum)
  {
    GROUP thing=pair<int, int>(itrNum->second,-(itrNumUse->second));
    numsortmap.insert(pair<GROUP,string>(thing,itrNum->first));
    ++itrNumUse;
  }
    
  count=0;
  topsize=9;
    map <GROUP, string>::reverse_iterator itrNumSort;
  if (numcount<10) {topsize=numcount-1;}
  cout<<"Total "<<numcount<<" different numbers, "<<topsize+1<<" most used numbers:\n";
  for (itrNumSort=numsortmap.rbegin();itrNumSort!=numsortmap.rend();++itrNumSort)
  {
    cout<<"No. "<<count<<": "<<itrNumSort->second<<"\t\t"<<itrNumSort->first.first<<endl;
    if (count==topsize) 
    {
      break;
    }
    else if (count==9)
    {
      break;
    } 

    ++count;
  }  //end number sort and print
  
  return 0;
}   
      
               
