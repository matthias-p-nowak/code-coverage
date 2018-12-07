#include "reached.h"

using namespace std;

int main(int argc,char *argv[]){
	if(argc<2){
		cerr<< "use "<< argv[0]<< " <file>"<<endl;
		exit(EXIT_FAILURE);
	}
	ifstream ifs;
	ifs.open(argv[1],ifstream::in);
	map<string,set<int>>found;
	while(!ifs.eof()){
		string line;
		getline(ifs,line);
		if(line.find("REACHED:")==0){
			int p1=line.find(":")+1;
			int p2=line.find(":",p1);
			string file=line.substr(p1,p2-p1);
			p1=p2+1;
			p2=line.find(":",p1);
			string linenr=line.substr(p1,p2-p1);
			int l=atoi(linenr.c_str());
			cout << file << "(" << l << ")"<<endl;
			found[file].insert(l);
		}
	}
	cerr << "now handling files" << endl;
	for(auto f: found){
		cout << "file " << f.first << endl;
		auto fileName=f.first;
		string origName=fileName+string(".orig");
		if(rename(fileName.c_str(),origName.c_str())){
			perror("renaming file");
			continue; // next file
		}
		ifstream orig;
		orig.open(origName,ifstream::in);
		ofstream copy;
		copy.open(fileName,ofstream::out);
		auto lineSet=f.second;
		auto skipLine=lineSet.begin();
		int curLine=0;
		while(!orig.eof()){
			string line;
			getline(orig,line);
			if(++curLine == *skipLine){
				int f=line.find("UNREACHED");
				if(f<0){
					cout << "no UNREACHED found" << endl;
					skipLine=lineSet.end();
					copy << line <<endl;
					continue;
				}else{
				cout << "skipping" << endl;
				if(skipLine != lineSet.end())
					++skipLine;
				}
			}else{
				cout << line << endl;
				copy << line <<endl;
			}
		}
	}	
 return 0;	
}
