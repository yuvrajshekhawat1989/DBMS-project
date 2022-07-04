#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ofstream fout;
// int count=0;

class research_paper_t{
    public:
    string index;
    string title;
    string year;
    string abstract;
    string venue;
    bool author_exist;

    void reset(){
        index.clear();
        title.clear();
        year.clear();
        abstract.clear();
        venue.clear();
        author_exist=false;
    }
};
class authors_t
{
    public:
    string author_name;
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
 void make_sql(research_paper_t* rp){

      fout <<"INSERT INTO research_paper(rp_index,title,year,abstract,venue,author_exist) VALUES ( " << rp->index ;
            if(rp->title.length()==0 || rp->title=="NULL"){
             fout <<", NULL ";   
            }
            else{
                 fout <<", '" << rp->title <<"'";
            }
            if(rp->year.length()==0 || rp->year=="NULL"){
                fout <<" , NULL ";
            }
            else{
                fout<<", "<<rp->year;
            }
            if(rp->abstract.length()==0 || rp->abstract=="NULL"){
                 fout  << ", NULL ";
            }
            else{
                fout<< ", '" << rp->abstract <<"'";
            }
            if(rp->venue.length()==0 || rp->venue=="NULL"){
                 fout <<", NULL ";
            }
            else{
                 fout <<", '" << rp->venue <<"' ";
            }
             if(rp->author_exist){
                 fout <<", TRUE );"<< endl;
            }
            else{
                 fout <<", NULL );"<< endl;
            }
            
           if(rp->author_exist && !(rp->venue.length()==0 || rp->venue=="NULL") && (rp->abstract.length()==0 || rp->abstract=="NULL")&& !(rp->year.length()==0 || rp->year=="NULL")){
                // cout << rp->index <<endl;
                // count++;
           }
           rp->reset();
 }
void print_sql_author(authors_t* author){
     fout <<"INSERT INTO authors(author_name) VALUES ('" << author->author_name << "'); "<< endl;
 }
 bool authors(string line,authors_t* author){
      if(line.length()==0){
            return false;
      }
      if(line.at(0)=='#'){
          if(line.at(1)=='@'){
              line=cleanse(line);
              line=line.substr(2);
              int index1=0,index2=-1;
     
           while(index1<=line.length()){
              
                index1=line.find(',',index1+1);
                 author->author_name= line.substr(index2+1,index1-index2-1);
                 if(author->author_name.length()!=0){
                       print_sql_author(author);
                 }
                 index2=index1;
           } 


              return true;
          }
      }
      else{
          return false;
      }
      return true;
 }


bool read_line(string line, research_paper_t *rp){
    if(line.length()==0){
        return false;
    }

    if(line.at(0)=='#'){

        if(line.at(1)=='*'){
            if(line.size()==2){
                rp->title="NULL";
            }
            else{
                line=cleanse(line);
                rp->title = line.substr(2);
            }

        }

        else if(line.at(1)=='t'){
            if(line.size()==2){
                rp->year="NULL";
            }
            else{
                rp->year = line.substr(2);
            }
        }
         else if(line.at(1)=='@'){
            if(line.size()==2){
                rp->author_exist=false;
            }
            else{
                rp->author_exist=true;
            }
        }

        else if(line.at(1)=='c'){
            if(line.size()==2){
                rp->venue="NULL";
            }
            else{
              line=cleanse(line);
                rp->venue = line.substr(2);
            }
        }

        else if(line.substr(1,5) =="index"){
            if(line.size()==2){
                rp->index="NULL";
            }
            else{
                rp->index = line.substr(6);
            }
        }

        else if(line.at(1)=='!'){
            if(line.size()==2){
                rp->abstract="NULL";
            }
            else{
                line=cleanse(line);
                rp->abstract = line.substr(2);
            }
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
    
    
    fout.open("loader.sql");
    if(fout.is_open()==0){
        std::cout<<"file not found\n";
        return 1;
    }

    int num_char;
    std::string line;
    bool cond;
    research_paper_t rp;
    bool print=false;
    authors_t author;
    fin>>num_char;

    while(!fin.eof()){

        getline(fin,line);

        if(line.substr(0,2)=="#*" && print){
           make_sql(&rp);
        }
   
        cond=read_line(line,&rp);
        authors(line,&author);
        
        //unable to read line
        if(!cond){
            continue;
        }
        print=true;
       
    }
       make_sql(&rp);
    cout <<"Sql File Successfully Created!" <<endl; 
 
    // cout<<count<<endl;
    return 0;
}