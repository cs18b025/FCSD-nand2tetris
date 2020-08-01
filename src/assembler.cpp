#include<bits/stdc++.h>

using namespace std;

string removeSpaces(string str)  
{ 
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    str.erase(remove(str.begin(), str.end(), '\t'), str.end()); 
    return str; 
} 
string remove_comments(string str){
	if(str.find("*/")<str.length()){
		int pos=str.find("*/");
		str=str.substr(pos+2);
		//cout<<str<<endl;
	}
	if(str.find("//")<str.length()){
		int pos=str.find("//");
		str=str.substr(0,pos);
		//cout<<str<<endl;
	}
	if(str.find("/*")<str.length()){
		int pos=str.find("/*");
		str=str.substr(0,pos);
		//cout<<str<<endl;
	}
	//cout<<str<<endl;
	return str;
}

bool is_number(string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}


string to_Binary(int x){
	string str="0";
	str.resize(16,'0');
	int n=15;
	
	while(x>0 || n>=1){
		//cout<<"bla"<<endl;
		if(x%2==1){
			str[n]='1';
			//cout<<str[n];
			
		}else{
			str[n]='0';
			//cout<<str[n];
		}
		x=x/2;
		//cout<<x<<endl;
		n--;
	}

	cout<<str<<endl;
	
	return str;
}

int main(int argc,char* argv[]){
	cout<<argc<<endl;
	ifstream fin;
	fin.open(argv[1]);
	ofstream fout;
	fout.open("myprogram.ir",ios::out);
	
	

	//remove spaces and comments and put in output file
	string line;
	
	while(fin){
		
		getline(fin,line);
		if(line.length()!=0){
			//cout<<"bla"<<endl;
			line=removeSpaces(line);
			if(line.find("/*")<line.length() && line.find("//")>line.find("/*")){
				line=remove_comments(line);
				if(line.length()!=0){
					fout<<line<<endl;
				}
				while(!(line.find("*/")<line.length())){
					getline(fin,line);
				}
			}
			line=remove_comments(line);
			if(line.length()!=0){
				fout<<line<<endl;
			}
			//cout<<line<<endl;
		}
		//getline(fin,line);
	}
	fin.close();
	fout.close();

	//output.txt has file without spaces and comments

	//using maps to write the symbol table

	map <string,int> SymbolTable;

	SymbolTable.insert(pair<string,int>("SP",0));
	SymbolTable.insert(pair<string,int>("LCL",1));
	SymbolTable.insert(pair<string,int>("ARG",2));
	SymbolTable.insert(pair<string,int>("THIS",3));
	SymbolTable.insert(pair<string,int>("THAT",4));
	SymbolTable.insert(pair<string,int>("R0",0));
	SymbolTable.insert(pair<string,int>("R1",1));
	SymbolTable.insert(pair<string,int>("R2",2));
	SymbolTable.insert(pair<string,int>("R3",3));
	SymbolTable.insert(pair<string,int>("R4",4));
	SymbolTable.insert(pair<string,int>("R5",5));
	SymbolTable.insert(pair<string,int>("R6",6));
	SymbolTable.insert(pair<string,int>("R7",7));
	SymbolTable.insert(pair<string,int>("R8",8));
	SymbolTable.insert(pair<string,int>("R9",9));
	SymbolTable.insert(pair<string,int>("R10",10));
	SymbolTable.insert(pair<string,int>("R11",11));
	SymbolTable.insert(pair<string,int>("R12",12));
	SymbolTable.insert(pair<string,int>("R13",13));
	SymbolTable.insert(pair<string,int>("R14",14));
	SymbolTable.insert(pair<string,int>("R15",15));
	SymbolTable.insert(pair<string,int>("SCREEN",16384));
	SymbolTable.insert(pair<string,int>("KBD",24576));
	
	//till 16385 because till that RAM space is available for variables


	//initialisation done 
	//all the variable spaces which have not been filled have address -1 and string value as NULL

	fin.open("myprogram.ir");
	
	int line_number=-1;
	string instruction;

	vector<string> order_table;

	while(fin){
		getline(fin,instruction);

		int check=0;		//for the case (label)@var
		int flag=0;
		//if it is a label
		if(instruction.find("(")==0){
			//cout<<"bla"<<endl;
			int end_label=instruction.find(")");
			flag=1;
			if(!(end_label+1==instruction.length())){
				check=1;
				//cout<<check<<" ";
			}
			//cout<<check<<endl;

			string temp=instruction.substr(1,end_label-1);
			int x=(line_number+1);
			SymbolTable[temp]=x;
			//cout<<SymbolTable[temp]<<": "<<temp<<endl;;
			/*if(SymbolTable.find(temp)==SymbolTable.end()){		
				SymbolTable[temp]=line_number;
			}*/
		}



		// case one :the variable is not in the SymbolTable and is being put for the first time
		if(check==1){
			int end_label=instruction.find(")");
			string temp1=instruction.substr(end_label+2,instruction.length()-end_label-2);
			if(instruction.find("@")==end_label+1 && SymbolTable.find(temp1)==SymbolTable.end()){  //(label)@var evaluating the var part
				if(!is_number(temp1)){//it is not a constant 
					
					SymbolTable[temp1]=-100000000;
					order_table.push_back(temp1);
				}
			}
		}
		if(instruction.find("@")==0)
		{
			if(SymbolTable.find(instruction.substr(1,instruction.length()-1))==SymbolTable.end()){
				string temp=instruction.substr(1,instruction.length()-1);
				if(!is_number(temp)){
					SymbolTable[temp]=-100000000;
					order_table.push_back(temp);
				}
			}
		}

		if(flag!=1){
			line_number++;
		}
	}
	fin.close();

	//vector<string> :: iterator iter;
	vector<string> v;
	//iter=order_table.begin();
	for(int i=0;i<order_table.size();i++){
		string temp1=order_table[i];
		if(SymbolTable[temp1]==-100000000){
			v.push_back(temp1);
		}
	}
	//order_table.clear();


	fin.open("myprogram.ir");

	map<string, int>::iterator it;
	
	int RAM=16;
	/*r ( it = SymbolTable.begin(); it != SymbolTable.end(); it++ ){
		if(it->second==-100000000){
			it->second=RAM;
			RAM++;
		}
	}*/
	for(int i=0;i<v.size();i++){
		//cout<<bla<<endl;
		//cout<<order_table[i]<<endl;
		string temporary=v[i];
		SymbolTable[temporary]=RAM;
		RAM++;
	}

	//symbol table prepared
	for ( it = SymbolTable.begin(); it != SymbolTable.end(); it++ ){
		cout<<it->first<<" : "<<it->second<<endl;
	}

	fin.close();

	//pass 1 is complete
	//negetive entries in the table are R0M data
	fout.open(argv[2],ios::out);
	fin.open("myprogram.ir");
	string str;

	map<string,string> ALU;
	//X+Y
	ALU.insert(pair<string,string> ("D+A","000010"));
	ALU.insert(pair<string,string> ("A+D","000010"));
	ALU.insert(pair<string,string> ("D+M","000010"));
	ALU.insert(pair<string,string> ("M+D","000010"));
	//X-Y
	ALU.insert(pair<string,string> ("D-A","010011"));
	ALU.insert(pair<string,string> ("D-M","010011"));
	//Y-X
	ALU.insert(pair<string,string> ("A-D","000111"));
	ALU.insert(pair<string,string> ("M-D","000111"));
	//X-1
	ALU.insert(pair<string,string> ("D-1","001110"));
	//Y-1
	ALU.insert(pair<string,string> ("A-1","110010"));
	ALU.insert(pair<string,string> ("M-1","110010"));
	//X+1
	ALU.insert(pair<string,string> ("D+1","011111"));
	//Y+1
	ALU.insert(pair<string,string> ("A+1","110111"));
	ALU.insert(pair<string,string> ("M+1","110111"));
	//-X
	ALU.insert(pair<string,string> ("-D","001111"));
	//-Y
	ALU.insert(pair<string,string> ("-A","110011"));
	ALU.insert(pair<string,string> ("-M","110011"));
	//!Y
	ALU.insert(pair<string,string> ("!A","110001"));
	ALU.insert(pair<string,string> ("!M","110001"));
	//!X
	ALU.insert(pair<string,string> ("!D","001101"));
	//Y
	ALU.insert(pair<string,string> ("A","110000"));
	ALU.insert(pair<string,string> ("M","110000"));
	//X
	ALU.insert(pair<string,string> ("D","001100"));
	//0
	ALU.insert(pair<string,string> ("0","101010"));
	//1
	ALU.insert(pair<string,string> ("1","111111"));
	//-1
	ALU.insert(pair<string,string> ("-1","111010"));
	//X&Y
	ALU.insert(pair<string,string> ("D&A","000000"));
	ALU.insert(pair<string,string> ("D&M","000000"));
	ALU.insert(pair<string,string> ("A&D","000000"));
	ALU.insert(pair<string,string> ("M&D","000000"));
	//X|Y
	ALU.insert(pair<string,string> ("D|A","010101"));
	ALU.insert(pair<string,string> ("A|D","010101"));
	ALU.insert(pair<string,string> ("M|D","010101"));
	ALU.insert(pair<string,string> ("D|M","010101"));

	map<string,string> jump;

	jump.insert(pair<string,string>("NOJUMP","000"));
	jump.insert(pair<string,string>("JGT","001"));
	jump.insert(pair<string,string>("JEQ","010"));
	jump.insert(pair<string,string>("JGE","011"));
	jump.insert(pair<string,string>("JLT","100"));
	jump.insert(pair<string,string>("JNE","101"));
	jump.insert(pair<string,string>("JLE","110"));
	jump.insert(pair<string,string>("JMP","111"));

	map<string,string>::iterator it1;
	while(fin){
		getline(fin,str);
		string temp;
		//A Type instruction
		if(str.find("@")==0){ 	
			//fout<<"bla"<<endl;
			temp=str.substr(1,str.length()-1);					
			if(!is_number(temp)){	
			//fout<<"bla"<<endl;	
				it=SymbolTable.find(temp);
				int x=it->second;
				//fout<<x<<endl;
				fout<<to_Binary(x)<<endl;
			}
			else{
				//fout<<"bla1"<<endl;
				stringstream s(temp);
				int x;
				s>>x;
				//fout<<x<<endl;
				fout<<to_Binary(x)<<endl;
			}
		}
		else if(str.find("=")<str.length()){
			string output="0";
			output.resize(16,'0');
			//initialisation for c type instruction
			output[0]='1';
			output[1]='1';
			output[2]='1';
			output[13]='0';
			output[14]='0';
			output[15]='0';

			string c_after=str.substr(str.find("=")+1,str.length()-str.find("=")-1);
			string c_before=str.substr(0,str.find("="));

			//a=0 or a=1
			if(c_after.find("M")<c_after.length()){
				output[3]='1';
			}/*else{
				output[3]='1';
			}*/

			if(c_before.find("A")<c_before.length()){
				output[10]='1';
			}
			if(c_before.find("D")<c_before.length()){
				output[11]='1';
			}
			if(c_before.find("M")<c_before.length()){
				output[12]='1';
			}

			it1=ALU.find(c_after);
			if(it1==ALU.end()){
				fout<<"error: invalid operation"<<endl;
			}
			string string1=it1->second;
			output.replace(4,6,string1);

			fout<<output<<endl;
		}
		else if(str.find(";")<str.length()){
			string output="0";
			output.resize(16,'0');
			//initialisation for c type instruction
			output[0]='1';
			output[1]='1';
			output[2]='1';

			output[10]='0';
			output[11]='0';
			output[12]='0';

			string c_before=str.substr(0,str.find(";"));

			if(c_before.find("M")<c_before.length()){
				output[3]='1';
			}/*else{
				output[3]='1';
			}*/
			it1=ALU.find(c_before);
			if(it1==ALU.end()){
				fout<<"error: invalid operation"<<endl;
			}
			string string1=it1->second;
			output.replace(4,6,string1);

			string c_after=str.substr(str.find(";")+1,str.length()-str.find(";")-1);
			it1=jump.find(c_after);
			string1=it1->second;
			output.replace(13,3,string1);

			fout<<output<<endl;
		}
	}
	fout.close();
	fin.close();
	//second pass finished

	//input file is "input.txt"
	//outputfile is "output3.txt"
	//intermediate file is "output.txt"


return 0;

}