#include <iostream>
#include <fstream>
#include <string>
#include<vector>

using namespace std;

ofstream fout;

class written_by_t{
    public:
    string rp_index;
    vector<string> author_names;

    void reset(){
        rp_index.clear();
        author_names.clear();
    }
};

string cleanse (string line){
    string temp;
    int index1=-1, index2=0;
    if(line.find("'")==line.npos){
         return line;
    }
    
    while(true){
         index1=line.find("'",index1+1);
         temp+=line.substr(index2,index1-index2+1);
          index2=index1;   
          if(index1==line.npos){
              break;
          }
    }
      return temp;
}

 bool make_sql(written_by_t* wr){
         if(wr->author_names.size()==0){
                return false;
         }   
        for(unsigned i=0 ; i< wr->author_names.size() ;i++){
                 fout <<"INSERT INTO written_by(rp_index,author_name,rank) VALUES ( " << wr->rp_index ;
                 fout <<", '" <<wr->author_names.at(i) <<"'"; 
                 if(i==0)
                      fout << ", " << 1 << ");" <<endl ;
                 else
                      fout << ", " << 0 << ");" <<endl ;   

        }
            wr->reset();
            return true;
 }

bool enter_authors(string line,written_by_t* wr){

              line=cleanse(line);
              line=line.substr(2);
              if(line.length()==0)
                    return false;

              int index1=0,index2=-1;
     
           while(index1<=line.length()){    
                index1=line.find(',',index1+1);
                 wr->author_names.push_back(line.substr(index2+1,index1-index2-1)) ;
                 index2=index1;
           } 
        return true;
 }


bool read_line(string line, written_by_t* wr){
    if(line.length()==0){
        return false;
    }

    if(line.at(0)=='#'){

         if(line.at(1)=='@'){
            if(line.size()==2){
                   return false;
            }
            else{
                  enter_authors(line,wr);
            }
        }
        else if(line.substr(1,5) =="index"){
            
                wr->rp_index = line.substr(6);
        }

        else{
            return false;
        }
    }
     else{
        return false;
     }
    return true;
}

int main(){
    //taking input
    ifstream fin;
    fin.open("source.txt");
    if(fin.is_open()==0){
        std::cout<<"file not found\n";
        return 1;
    }
    
    
    fout.open("loader.sql",std::ios_base::app);
    if(fout.is_open()==0){
        std::cout<<"file not found\n";
        return 1;
    }

    int num_char;
    std::string line;
    bool cond;
    written_by_t writers;
    fin>>num_char;

    while(!fin.eof()){

        getline(fin,line);
        cond=read_line(line,&writers);

        if(line.substr(0,6)=="#index"){
             make_sql(&writers);
        }   
        //unable to read line
        if(!cond){
            continue;
        }
    }
    cout <<"Sql File Successfully Created!" <<endl; 
   // make_sql(wri);

    return 0;
}