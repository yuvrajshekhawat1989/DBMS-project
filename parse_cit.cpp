#include <iostream>
#include <fstream>
#include <string>
#include<vector>

using namespace std;

ofstream fout;

class citatations_t{
    public:
    int rp_index;
    vector<int> cited_rp_indexes;

    void reset(){
       cited_rp_indexes.clear();
    }
};

 bool make_sql(citatations_t* cit){
         if(cit->cited_rp_indexes.size()==0){
                return false;
         }   
        for(unsigned i=0 ; i< cit->cited_rp_indexes.size() ;i++){
            if(cit->rp_index!= cit->cited_rp_indexes.at(i)){
                    fout <<"INSERT INTO citations(rp_index,cited_rp_index) VALUES ( " << cit->rp_index ;
                    fout << ", " << cit->cited_rp_indexes.at(i) << ");" <<endl ;

            }            
        }
           cit->reset();
            return true;
 }

bool read_line(string line, citatations_t* cit){
    if(line.length()==0){
        return false;
    }

    if(line.at(0)=='#'){
        if(line.substr(1,5) =="index"){   
                cit->rp_index = stoi(line.substr(6));
                return true;
        }
        else if(line.at(1)=='%'){
              cit->cited_rp_indexes.push_back(stoi(line.substr(2)));
        }
        else{
            return false;
        }
    }
     else{
        return false;
     }
    return false;
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
    fin>>num_char;
    citatations_t citations;
    bool print=false;

    while(!fin.eof()){

        getline(fin,line);

        if(line.substr(0,6)=="#index"&& print){
             make_sql(&citations);
        }   
        cond=read_line(line,&citations);
        //unable to read line
        if(!cond){
            continue;
        }
         print=true;
    }
     make_sql(&citations);
    cout <<"Sql File Successfully Created!" <<endl; 
   // make_sql(wri);

    return 0;
}