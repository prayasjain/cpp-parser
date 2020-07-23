#include<bits/stdc++.h>

using namespace std ;


vector<string> tables ;		//table name
vector< vector<string> > tval ; // table data
vector< vector<string> > tattr ; // attribute name
vector< vector<string> > tattrtype ; // attribute type
vector< map< string, int > > attr_lookup ; // map between attrib index and name



vector<int> tcount  ; // attribute count
map < string, int > table_lookup ; // map between table name and index

void iter_vec(vector<string> v){ //print a vector of string
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<" "; 
	cout<<"\n" ;
}

bool is_digits(const std::string &str)          // method to check if a string contains only digits
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}
void show_tables(){												// method to print all the tables
	for(int i=0;i<tables.size();i++){
		cout<<"--"<<tables[i]<<"--"<<"\n" ;
		map< string , int > :: iterator it ;
		/*for(it=attr_lookup[i].begin();it!=attr_lookup[i].end();it++){
    			cout<<it->first<<" "<<it->second<<endl;
    		} */
		
		for(int j=0;j<tcount[i];j++){
			cout<<tattr[i][j]<<" " ;
		}
		cout<<"\n" ;
		for(int j=0;j<tcount[i];j++){
			cout<<tattrtype[i][j]<<" " ;
		}
		for(int j=0;j<tval[i].size();j++){
			if(j%tcount[i]==0)
				cout<<"\n" ;
			cout<<tval[i][j]<<" " ;
		}
		cout<<"\n" ;
	}
}


void read_from_file(){
	ifstream myfile ;
	myfile.open("parser.txt") ;
	int tsize;
	
	myfile >> tsize ;
	if(tsize==-1 || tsize==0)
		return ;

	cout<<tsize<<"\n" ;
	
	for(int i=0;i<tsize;i++){
		string nm  ;
		myfile >> nm ;
		tables.push_back(nm) ;
	}
	myfile.close() ;

	iter_vec(tables) ;
	string txt = ".txt" ;
	for(int i=0;i<tsize;i++){
		string filename = tables[i]+txt ;
		myfile.open(filename.c_str()) ; 
		int temp  ;
		myfile >> temp  ;
		tcount.push_back(temp) ;

		
		vector<string> tv ;
		for(int j=0;j<tcount[i];j++){
			string tp ;
			myfile >> tp ;
			tv.push_back(tp) ;
		}
		tattr.push_back(tv) ;
		tv.clear() ;
		for(int j=0;j<tcount[i];j++){
			string tp ;
			myfile >> tp ;
			tv.push_back(tp) ;
		}
		tattrtype.push_back(tv) ;
		tv.clear();
		myfile >> temp ;
		for(int j=0;j<temp;j++){
			string l ;
			myfile >> l ;
			tv.push_back(l) ;
		}
		tval.push_back(tv) ;
		table_lookup[tables[i]] = i ;
		map < string , int > mmap ;
		for(int j=0;j<tcount[i];j++){
			mmap[tattr[i][j]] = j ;
		}
		attr_lookup.push_back(mmap) ;



		myfile.close() ;


	}
	
	show_tables() ;
	/*map<string,int> :: iterator it ;
	for(it=table_lookup.begin();it!=table_lookup.end();it++){
		cout<<it->first<<" "<< it->second <<" \n" ;

	}
	for(int i=0;i<tsize;i++){
		for(it=attr_lookup[i].begin();it!=attr_lookup[i].end();it++){
			cout<<it->first<<" "<< it->second <<" \n" ;

		}	
	} */   //read the data stored in a file

}
void write_to_file(){
	ofstream myfile;
	myfile.open ("parser.txt");
	myfile << tables.size() <<"\n" ;
	for(int i=0;i<tables.size();i++){
		myfile << tables[i] << "\n" ;
	}
	myfile.close() ;
	string txt = ".txt" ;
	for(int i=0;i<tables.size();i++){
		string filename = tables[i]+txt ;
		myfile.open(filename.c_str()) ; 
		myfile << tcount[i] << "\n" ;
		
		for(int j=0;j<tcount[i];j++){
			myfile << tattr[i][j]<<"\n" ;
		}

		for(int j=0;j<tcount[i];j++){
			myfile << tattrtype[i][j]<<"\n" ;
		}

		myfile<<tval[i].size()<<"\n" ;
		for(int j=0;j<tval[i].size();j++){
			myfile<<tval[i][j]<<"\n" ;
		}

		myfile.close() ;
	}   // write the data stored in a file
	
}



int findstr(string q, string f){
	f= " "+f+" " ;
	//cout<<q<<"-"<<f ;
	int i,j,k ;
 	for( i=0;i<q.size();i++){
 		k=i ;
 		for(j=0;j<f.size();j++){
 			if(q[k]==f[j]){
 				k++ ;
 				//cout<< q[k]<< " " << f[j] <<"\n" ;
 			}
 			else
 				break ;
 		}
 		if(j==f.size()){
 			//cout<<"<><><>";
 			return (k-f.size()) ;
 		}
 	}
 	return -1 ;
		
	}			// helper function that finds a sub string in a string
int findopr(string q, string f){
	int i,j ;
 	for( i=0;i<q.size();i++){
 		for(j=0;j<f.size();j++){
 			if(q[i]==f[j])
 				i++ ;
 			else
 				break ;
 		}
 		if(j==f.size()){
 			
 			return (i-f.size()) ;
 		}
 	}
 	return -1 ;				// helper function that finds an operator in a string expression
}

int findstr2(string q, string f){

	//cout<<q<<"-"<<f ;
	int i,j,k ;
 	for( i=0;i<q.size();i++){
 		k=i ;
 		for(j=0;j<f.size();j++){
 			if(q[k]==f[j]){
 				k++ ;
 				//cout<< q[k]<< " " << f[j] <<"\n" ;
 			}
 			else
 				break ;
 		}
 		if(j==f.size()){
 			//cout<<"<><><>";
 			return (k-f.size()) ;
 		}
 	}
 	return -1 ;
		
	}     // helper function that finds a sub string in a string


string rm_space(string q){
	string f_c="" ;
	int i,j ;
	for(i=0;i<q.size();i++){
		if(q[i]!=' ')
			break ;
	}
	for(j=q.size()-1;j>=0;j--){
		if(q[j]!=' ')
			break ;
	}
	for(int k=i;k<=j;k++){
		f_c+=q[k] ;
	}
	//cout<< q << "gg" << f_c <<"\n " ;
	return f_c ;			//helper function that removes starting a trailing spaces in a string
}
vector<string> remove_duplicates(vector<string> vec , int len){
	//cout<<"yo" ;
	//cout<<len ;
	//for(int i=0;i<vec.size();i++)
	//	cout<<vec[i] ;

	vector<string> entry  ;
	vector<string> final ;
	int i =0 ;
	int pass = vec.size()/len ;
	vector<int> flag (pass,0) ;
	//for(int i=0;i<flag.size();i++){
	//	cout<<flag[i]<<" " ;
	//}
	for (int p = 0 ; p<pass;p++){
		if(flag[p]!=0)
			continue ;
		for(i=0;i<len;i++){
			entry.push_back(vec[i+p*len]) ;
			final.push_back(vec[i+p*len]) ;
		}
		for (i = p+1;i<pass;i++){
			int j ;
			for(j=0;j<len;j++){
				if(entry[j]!=vec[i*len + j])
					break ;
			}
			if(j==len){
				flag[i]=1 ;
			}
		}
		entry.clear() ;
	
	}
	return final ; // helper function to remove duplicates from a table
	
}
vector<string> split(string val,char splt){
	vector<string> op ;
	string t = "" ;
	int i = 0;
	for(i=0;i<val.size();i++){
		if(val[i]==splt){
			op.push_back(rm_space(t)) ;
			t="" ;
		}else {
			t+=val[i] ;
		}

	}
	if(t!="")
		op.push_back(rm_space(t)) ;	

	return op ; // splits a string into a vector based on a character
}

vector<string> cartesian_product(vector<string> f, vector<string> s , int l1 ,int l2){
	vector<string> op ;
	int pass1 = f.size() / l1 ;
	int pass2 = s.size() / l2 ;
	for(int p1=0;p1<pass1;p1++){
		for(int p2=0;p2<pass2;p2++){
			for(int i=0;i<l1;i++){
				op.push_back(f[p1*l1 + i]) ;
			}

			for(int i=0;i<l2;i++){
				op.push_back(s[p2*l2 + i]) ;
			}
		}
	}
	return op ; // method that returns cartesian product of
																						// two tables
}


int flag_exp = 0  ;

vector<string> logicaland(vector<string> f , vector<string> s , int len) {

	int pass = f.size()/len ;
	int pass2 = s.size()/len ;
	vector<string> op ;
	for(int p=0;p<pass;p++){
		for(int p2 = 0 ;p2<pass2;p2++){
			int i ;
			for( i=0;i<len;i++){
				if(f[p*len+i]!=s[p2*len+i])	
					break ;
			}
			if(i==len){
				for(i=0;i<len;i++){
					op.push_back(f[p*len+i]) ;
				}
			}
		}
	}
	return op ; // method for intersection of 2 tables
}
vector<string> logicalor(vector<string> f , vector<string> s , int len){ // method for union of two tables
	for(int i=0 ;i<s.size();i++){
		f.push_back(s[i]) ;
	}
	return remove_duplicates(f,len) ;
}


vector<string> logicaldiff(vector<string> f , vector<string> s , int len) {

	int pass = f.size()/len ;
	int pass2 = s.size()/len ;
	vector<string> op ;
	for(int p=0;p<pass;p++){
		int flag = 0 ;
		for(int p2 = 0 ;p2<pass2;p2++){
			int i ;
			for( i=0;i<len;i++){
				if(f[p*len+i]!=s[p2*len+i])	
					break ;
			}
			if(i==len){
				flag = 1 ;
				break ;
				
			}
		}
		if(flag==0){
			for(int i=0;i<len;i++){
					op.push_back(f[p*len+i]) ;
				}
		}
	}
	return op ; // method for setdiff of 2 tables
}


vector<string> expression_evaluator(string q,int tno){

	vector<string> opr  ;
	if(flag_exp==1)
		return opr ;

	opr.push_back(">=") ;
	opr.push_back("<=") ;
	
	opr.push_back("=") ;
	opr.push_back(">") ;
	opr.push_back("<") ;
	
	vector<string> connect ;
	connect.push_back("and") ;
	connect.push_back("or") ;
	int res=-1 ,resf = -1 ;
	q= rm_space(q) ;
	string connector ;
	int cflag = 0;
	vector<string> remaining ;
	for(int i=0;i<connect.size();i++){
		res = findstr(q,connect[i]) ;
		if(res==-1)
			continue ;
		else{
			cflag =1 ;
			if(resf==-1){
				resf = res ;
				connector = connect[i] ;
			}
			else if(res < resf){
				resf = res ;
				connector = connect[i] ;	
			}
		}
	}

	if(resf!=-1){
		remaining= expression_evaluator(q.substr(resf+connector.size()+2),tno) ;
		q= q.substr(0,resf) ; 
	}

	// cout<< q ;
	// iter_vec(remaining) ;


	for(int i=0;i<opr.size();i++){
		res = findopr(q,opr[i]) ;
		if(res==-1)
			continue ;
		string var = rm_space(q.substr(0,res)) ;
		string val = rm_space(q.substr(res+opr[i].size(),q.size())) ;
		string opt = opr[i] ;
		//cout<<var<<"-"<<opt<<"-"<<val<<"\n" ;
		if(attr_lookup[tno].find(var)==attr_lookup[tno].end()){
			cout<< "no such attribute" ;
			vector<string> tve;
			flag_exp= 1 ;
			return tve;
		}
		int vind = attr_lookup[tno][var] ;
		vector<string> op ;
		if(val[0]=='\'' || val[0]=='\"' && opt=="=" ) 
			val= val.substr(1,val.size()-2) ;
		else if(val[0]=='\'' && opt!="="){
			cout<<"type mismatch" ;
			flag_exp=1 ;
			return op ;
		}
		
		int len = tcount[tno] ;
		int pass = tval[tno].size()/len ;
		
		//cout<<len<<pass<<vind ;
		//iter_vec(tval[tno]) ;

		for(int p=0;p<pass;p++){
			if(opt=="=" && tval[tno][p*len+vind]==val){
				for(int j=0;j<len;j++){
					op.push_back(tval[tno][p*len+j]) ;
				}
			}if(opt==">" || opt=="<" || opt==">=" || opt =="<="){
				int vali = atoi(val.c_str()) ;
				int flg =0  ;
				if(opt==">" && atoi(tval[tno][p*len+vind].c_str())>vali)
					flg=1 ;
				if(opt=="<" && atoi(tval[tno][p*len+vind].c_str())<vali)
					flg=1 ;
				if(opt==">=" && atoi(tval[tno][p*len+vind].c_str())>=vali)
					flg=1 ;
				if(opt=="<=" && atoi(tval[tno][p*len+vind].c_str())<=vali)
					flg=1 ;
				if(flg==1){
					for(int j=0;j<len;j++){
						op.push_back(tval[tno][p*len+j]) ;
					}
				}

			}
		}
		//iter_vec(op) ;
		if(cflag==0)
			return op ;
		else if(connector=="and"){
			return logicaland(op,remaining,len) ;
		}else if(connector=="or")
			return logicalor(op,remaining,len) ;

	}			 // method for evaluating expression for select query
}
vector<string> expression_evaluator2(string q,vector<string> tbl , vector<string> attr){

	map<string , int > tmap_attr ;
	for(int i=0;i<attr.size();i++){
		tmap_attr[attr[i]] = i ;
	}

	vector<string> opr  ;
	if(flag_exp==1)
		return opr ;

	opr.push_back(">=") ;
	opr.push_back("<=") ;
	
	opr.push_back("=") ;
	opr.push_back(">") ;
	opr.push_back("<") ;
	
	vector<string> connect ;
	connect.push_back("and") ;
	connect.push_back("or") ;
	int res = -1 , resf = -1  ;
	q= rm_space(q) ;
	string connector ;
	int cflag = 0;
	vector<string> remaining ;
	for(int i=0;i<connect.size();i++){
		res = findstr(q,connect[i]) ;
		if(res==-1)
			continue ;
		else{
			if(resf==-1){
				resf = res ;
				cflag =1 ;
				connector = connect[i] ;
			
			}
			else if(res< resf) {
				resf = res ;
				connector = connect[i] ;
			}
			
		}
	}
	if(resf!=-1){
		remaining= expression_evaluator2(q.substr(resf+connector.size()+2),tbl,attr) ;
		q= q.substr(0,res) ; 
	}

	 //cout<< q ;
	 //iter_vec(remaining) ;

	for(int i=0;i<opr.size();i++){
		res = findopr(q,opr[i]) ;
		if(res==-1)
			continue ;
		string var = rm_space(q.substr(0,res)) ;
		string val = rm_space(q.substr(res+opr[i].size(),q.size())) ;
		string opt = opr[i] ;
		//cout<<var<<"-"<<opt<<"-"<<val<<"\n" ;
		if(tmap_attr.find(var)==tmap_attr.end()){
			cout<< "no such attribute" ;
			vector<string> tve;
			flag_exp= 1 ;
			return tve;
		}
		int vind = tmap_attr[var] ;
		vector<string> op ;
		if(val[0]=='\'' || val[0]=='\"' && opt=="=" ) 
			val= val.substr(1,val.size()-2) ;
		else if(val[0]=='\'' && opt!="="){
			cout<<"type mismatch" ;
			flag_exp=1 ;
			return op ;
		}
		
		int len = attr.size() ;
		int pass = tbl.size()/len ;
		
		//cout<<len<<pass<<vind ;
		//iter_vec(tval[tno]) ;

		for(int p=0;p<pass;p++){
			if(opt=="=" && tbl[p*len+vind]==val){
				for(int j=0;j<len;j++){
					op.push_back(tbl[p*len+j]) ;
				}
			}if(opt==">" || opt=="<" || opt==">=" || opt =="<="){
				int vali = atoi(val.c_str()) ;
				int flg =0  ;
				if(opt==">" && atoi(tbl[p*len+vind].c_str())>vali)
					flg=1 ;
				if(opt=="<" && atoi(tbl[p*len+vind].c_str())<vali)
					flg=1 ;
				if(opt==">=" && atoi(tbl[p*len+vind].c_str())>=vali)
					flg=1 ;
				if(opt=="<=" && atoi(tbl[p*len+vind].c_str())<=vali)
					flg=1 ;
				if(flg==1){
					for(int j=0;j<len;j++){
						op.push_back(tbl[p*len+j]) ;
					}
				}

			}
		}
		//iter_vec(op) ;
		if(cflag==0)
			return op ;
		else if(connector=="and"){
			return logicaland(op,remaining,len) ;
		}else if(connector=="or")
			return logicalor(op,remaining,len) ;

	}	 // method for evaluating expression
																							// for select query
}


int check_query1_type = -1 ; // whether to assign or insert a new value
void parse(string r , string l,int tno){  // metohd used for inserting data into the table

	if(r[0]=='{' && r[r.size()-1]=='}'){

		
		int flag = -1 ;
		string val="";
		vector<string> f_v ;
		int temp_size ;
		
		temp_size= tcount[tno] ; 

 		for(int i=1;i<r.size()-1;i++){
			if(r[i]=='('){
				flag =1 ;
				continue ;
			}
			if(r[i]==')'){
				flag = 2 ;
				vector<string> op = split(val,',') ;
				//cout<< val ;
				//for(int iter=0;iter<op.size();iter++){
				//	cout<< op[iter]<<" " ;
				//}
				//cout<<'\n' ; 
				val="" ;
				
				if(temp_size!=op.size()){
					cout<<temp_size<<" "<< op.size()<<" " ;
					cout<<"error2\n" ;
					return ;
				}
				for(int iter=0;iter<op.size();iter++){
					//cout<<op[iter] ;
					f_v.push_back(op[iter]) ;

				}

				continue ; 
			}
			if(flag==1)
				val+=r[i] ;
		}
		


		if(val!=""){
			cout<<"error3\n" ;
			return ;
		}
		
		for(int iter=0;iter<f_v.size();iter++){
			string type = tattrtype[tno][iter%tcount[tno]] ;
			if(type == "int" && !is_digits(f_v[iter])){
				cout<<"type mismatch" ;
				return  ;
			}
			int flgg =0 ;
			if(type=="string"){
				if(f_v[iter][0]=='\'' && f_v[iter][f_v[iter].size()-1]=='\'')
					flgg =1 ;
				if(f_v[iter][0]=='\"' && f_v[iter][f_v[iter].size()-1]=='\"')
					flgg =1 ;
				if(flgg==0){
					cout<<"type mismatch" ;
					return   ;
				}		
			}
		}
		
		if(check_query1_type==-1){
			cout<<"Error" ;
			return ;
		}
		if(check_query1_type==1)
			tval[tno].clear() ;
		
		for(int iter=0;iter<f_v.size();iter++){
			
			if(f_v[iter][0]=='\'' || f_v[iter][0]=='\"')
				f_v[iter] = f_v[iter].substr(1,f_v[iter].size()-2) ;
			tval[tno].push_back(f_v[iter]) ;
		}
		//iter_vec(tval[tno]) ;
		//cout<<tcount[tno] ;
		vector<string> temp = remove_duplicates(tval[tno],tcount[tno]) ;
		tval[tno]= temp ;

			
		
	}
}


pair<string, string>  check_query1(string q) {
	int f =-1 ;
	check_query1_type = -1 ;
	for(int i=0;i<q.size()-1;i++) {
		
		if(q[i]=='<' && q[i+1]=='-'){
			if(i!=0 && q[i-1]=='<')
			{
				f = i-1 ;
				check_query1_type = 2 ;
				break ;
			}	
			f=i ;
			check_query1_type = 1 ;
			break ;
		}
	}
	//cout<<check_query1_type ;
	if(f==-1) 
		return make_pair("","") ;
	string first="", second="" ;
	for(int i=0;i<f;i++){
	
		first+=q[i] ;
	}
	for(int i=f+check_query1_type+1;i<q.size();i++){
		second+=q[i] ;
	}
	
	//cout<< first << second ;
	return make_pair(rm_space(first),rm_space(second)) ;  // method use to check whether query is on insertion
}

int check_query_def(string q){		//method to define a new table

	q=rm_space(q) ;
	string tname="" ;
	vector<string> attr2,attr,type ;
	if(q.substr(0,7)=="define "){
		q = rm_space(q.substr(7,q.size())) ;
		int i = 0 ;
		while(q[i]!=' '){
			tname+=q[i] ;
			i++ ;
		}
		q= rm_space(q.substr(i,q.size())) ;
		attr2 = split(q,',') ;
		for(int i=0;i<attr2.size();i++){
			vector<string> tvector ;
			tvector = split(attr2[i],' ') ;
			if(tvector.size()!=2){
				cout<< "error" ;
				return 1 ;
			}
			if(tvector[1]=="string" || tvector[1]=="int")
				type.push_back(tvector[1]) ;
			else {
				cout<< "error!" ;
				return 1 ;
			}
			attr.push_back(tvector[0]) ;

		}

		for(int iter =0 ;iter<tables.size();iter++){
			if(tables[iter]==tname){
				cout<<"table exists" ;
				return 1 ;
			}
		} 
		table_lookup[tname] = tables.size() ;
		tables.push_back(tname) ;
		
		tcount.push_back(attr.size()) ;
		vector<string> temp ;
		tval.push_back(temp) ;
		tattr.push_back(attr) ;
		tattrtype.push_back(type) ;
		map< string , int >  tmap ;
		for(int it=0;it<attr.size();it++){
			tmap[attr[it]]= it ;
		} 
		attr_lookup.push_back(tmap) ;
		show_tables() ;
		return 1 ;
	}
	//cout<<tname<<"\n" ;
	//iter_vec(attr) ;
	return 0 ;
}

int check_query_rename(string q) {
	q= rm_space(q) ;
	if(q.substr(0,7)=="rename "){
		q = rm_space(q.substr(7,q.size())) ;
		vector<string > vec = split(q,' ') ;
		if(vec.size()!=2)
			return 0 ;
		if(table_lookup.find(vec[0])==table_lookup.end()){
    		cout<<"no such table";
    		return 1 ;
    	}

		int tn = table_lookup[vec[0]] ;
		//tables[tn] = vec[1] ;
		//table_lookup.erase (vec[0]) ;
		//table_lookup[vec[1]] = tn ; 
		

		//show_tables() ;
		return 1 ;
		
	}
	return 0 ;  // method to rename a table (temporarily)
}


//Methods used for selection and projection. These work for without nested queries
/*
int check_query_project(string q){

 	q = rm_space(q) ;

 	if(q.substr(0,8)!="project "){
 		return 0 ;
 	}
 	q= rm_space(q.substr(8,q.size())) ;
 	int i = findstr(q,"from") ;
 	if(i==-1)
 		return 0 ;
 	vector<string> attr = split(rm_space(q.substr(0,i)),',') ;
 	string tname =rm_space(q.substr(i+6,q.size())) ;
 	//cout<<tname<<"\n" ;
 	int tind ;
 	if(table_lookup.find(tname)==table_lookup.end()){
 		cout<<"no such table\n" ;
 		return 1 ;
 	}else
 		tind = table_lookup[tname] ;


 	//iter_vec(attr) ;
 	vector<int> indx ;
 	for(int i=0;i<attr.size();i++){
 		if(attr_lookup[tind].find(attr[i])==attr_lookup[tind].end()){
 			cout<<"no such attribute\n" ;
 			return 1 ;
 		}
 		indx.push_back(attr_lookup[tind][attr[i]]) ;
 	}
 	//for(int i=0;i<indx.size();i++){
 	//	cout<<indx[i]<<" " ;
 	//}
 	vector<string> op ; 
 	int pass = tval[tind].size()/tattr[tind].size() ;
 	int s = tattr[tind].size() ;
 	for(int p=0;p<pass;p++){
 		for(int i=0;i<indx.size();i++){
 			op.push_back(tval[tind][p*s+indx[i]]) ;
 		}
 	}
 	op = remove_duplicates(op,indx.size()) ;
 	for(int i=0;i<attr.size();i++){
 		cout<<attr[i]<<" " ;
 	}
 	for(int i=0;i<op.size();i++){
 		if(i%attr.size()==0)
 			cout<<"\n" ;
 		cout<<op[i]<<" " ;
 	}
 	cout<<"\n" ;
 	return 1 ;
}
*/
/*
int check_query_select(string q) {
	
	q= rm_space(q) ;
	if(q.substr(0,7)!="select "){
 		return 0 ;
 	}

 	map<string , string > rname ;
 	
 	q= rm_space(q.substr(7,q.size())) ;
 	int i = findstr(q,"from") ;
 	if(i==-1)
 		return 0 ;
 	
 	
 	vector<string> attr = split(rm_space(q.substr(0,i)),',') ;
 	q=rm_space(q.substr(i+6,q.size())) ;
 	i= findstr(q,"where") ;
 	string tname  ;
 	int whflag= 0 ;
 	if(i==-1){
 		whflag=1 ;
 		tname = q ;
 	}
 	string expr ;
 	if(whflag!=1){
 		expr = rm_space(q.substr(i+7,q.size())) ;
 		tname  = rm_space(q.substr(0,i)) ;
 	}else {
 		expr="" ;
 	}
 	
 	//cout<< tname<<"\n" ;

 	vector<string> table_name = split(tname,',') ;
 	if(table_name.size()==1){
 		tname = table_name[0] ;
 		int tind ;
 		vector<int> indx ;
 		
 		
 		if(table_lookup.find(tname)==table_lookup.end()){
 			cout<<"table doesnt exist\n" ;
 			return 1 ;
 		}
 		tind = table_lookup[tname] ;
 		
 		for(int i=0;i<attr.size();i++){
 			if(attr_lookup[tind].find(attr[i])==attr_lookup[tind].end()){
 				cout<<"no such attribute\n" ;
 				return 1 ;
 			}
 			indx.push_back(attr_lookup[tind][attr[i]]) ;
 		}

 		vector<string> op ;
 		flag_exp=0 ;
 		if(expr!=""){
 			op = expression_evaluator(expr,tind) ;
 			
 		}
 		else 
 			op  = tval[tind] ;
 		flag_exp=0 ;
 		iter_vec(attr) ;
 		int pass = op.size()/tcount[tind] ;
 		for(int i=0;i<pass;i++){
 			for(int j=0;j<indx.size();j++){
 				cout<<op[i*tcount[tind]+indx[j]]<<" " ;
 			}
 			cout<<"\n" ;
 		}
 	
 		return 1 ;
 	}
 	
 	vector<int> table_index  ;
 	for(int it = 0 ;it<table_name.size();it++){
 		//cout<<table_name[it]<< " \n" ;
		if(table_name[it].substr(0,7)=="rename "){

			//cout<<"hello\n" ;
			//return 1 ;
			table_name[it] = rm_space(table_name[it].substr(7,q.size())) ;
			//cout<< table_name[it]<<"\n" ;
			//return 1 ;
			vector<string > vec = split(table_name[it],' ') ;
			//iter_vec(vec) ;
			if(vec.size()!=2)
				return 0 ;
			if(table_lookup.find(vec[0])==table_lookup.end()){
    				cout<<"no such table";
    				return 1 ;
    			}
    			if(table_lookup.find(vec[1])!=table_lookup.end()){
    				cout<<"name exists\n" ;
    				return 0 ;
    			}

    			//cout<<vec[0]<<"-"<<vec[1] <<"\n" ;
    			//return 1 ;
    			table_name[it] = vec[1] ;
    			

    			table_index.push_back(table_lookup[vec[0]]) ;
    			rname[vec[1]] = vec[0] ;

 		}else {
 			if(table_lookup.find(table_name[it])==table_lookup.end()){
    				cout<<"no such table";
    				return 1 ;
    			}
 			table_index.push_back(table_lookup[table_name[it]]) ;
 		}
 	}
 	//return 1 ;
 	//cout<<"\n"<<table_index.size()<< " " ;
 	//for(int it=0;it<table_index.size();it++){
 	//	cout<< table_index[it]<<" " ;
 	//}
 	//iter_vec(table_name) ;
 	//return 1  ;
 	vector<string> table_attr ;
 	vector<string> table_val ;
 	for(int i=0;i<table_name.size();i++){
 		for(int j=0;j<tcount[table_index[i]];j++){
 			table_attr.push_back(table_name[i]+"."+tattr[table_index[i]][j]) ;
 		}
 	}
 	//iter_vec(table_attr) ;
 	//return 1 ;

 	//for(int i=0;i<table_name.size();i++){
 	//	iter_vec(tval[table_index[i]]) ;
 	//}
 	//return 1 ;
 	table_val = cartesian_product(tval[table_index[0]] , tval[table_index[1]],tcount[table_index[0]], tcount[table_index[1]]) ;
 	//iter_vec(table_attr) ;
 	//iter_vec(table_val) ;
 	int s = tcount[table_index[0]]+ tcount[table_index[1]] ;
 	//iter_vec(table_val) ;
 	//return 1 ;
 	for(int i=2;i<table_name.size();i++){
 		table_val = cartesian_product(table_val,tval[table_index[i]],s , tcount[table_index[i]]) ;
 		s=s+tcount[table_index[i]] ;

 	}
 	int pass = table_val.size()/s ;
 	//for(int p=0;p<pass;p++){
 	//	for(int i=0;i<s;i++){
 	//		cout<<table_val[p*s+i]<<" " ;
 	//	}
 	//	cout<<"\n" ;
 	//}
 	//cout<<expr ;
 	//iter_vec(table_val) ;
 	//return 1 ; 
 	vector<string> op2 ;
 	if(expr!=""){
 		op2 = expression_evaluator2(expr,table_val,table_attr) ;
 	}else
 		op2 = table_val ;
 	//iter_vec(op2) ;
 	//return 1 ;


 	map<string ,int> mmap ;
 	for(int i=0 ;i<table_attr.size();i++) {
 		vector<string> tvec = split(table_attr[i],'.') ;
 		if(tvec.size()!=2){
 			cout<<"error4" ;
 			return 1 ;
 		}
 		//iter_vec(tvec) ;

 		if(table_lookup.find(tvec[0])!=table_lookup.end() ){
 			int  j = table_lookup[tvec[0]] ;
 			if(attr_lookup[j].find(tvec[1])!=attr_lookup[j].end()){
 				mmap[table_attr[i]]= i ;
 			}else {
 				cout<<"no such attribute\n" ;
 				return 1 ;
 			}
 		}else if(rname.find(tvec[0])!=rname.end()){

 			string nm = rname[tvec[0]] ;
 			//cout<<nm ;
 			//return 1 ;
 			int  j = table_lookup[nm] ;
 			//cout<<j ;
 			//return 1 ;
 			if(attr_lookup[j].find(tvec[1])!=attr_lookup[j].end()){
 				mmap[table_attr[i]]= i ;

 			}else {
 				cout<<"no such attribute\n" ;
 				return 1 ;
 			}
 		}
 		else {
 			cout<<"no such table\n";
 			return 1 ;
 		}

 	}
 	//return 1 ;
 	//map<string, int> :: iterator itt ;
 	//for(itt = mmap.begin();itt!=mmap.end();itt++){
 	//	cout<<itt->first <<" "<<itt->second<<"\n" ;
 	//}
 	iter_vec(attr) ;
 	pass= op2.size()/s ;

 	
 	vector<string> op3 ;
 	//iter_vec(op2) ;
 	//return 1 ;
 	for(int p=0;p<pass;p++){
 		for(int i=0;i<attr.size();i++){
 	//		cout<<mmap[attr[i]] << " "<<attr[i] << " "<< op2[p*s+mmap[attr[i]]] ;
 			op3.push_back(op2[p*s+mmap[attr[i]]]) ;
 		}
 		
 	}
 	//iter_vec(op3) ;
 	op3 = remove_duplicates(op3,attr.size()) ;
 	//iter_vec(op3) ;
 	pass=op3.size()/attr.size() ;
 	for(int p=0;p<pass;p++){
 		for(int i=0;i<attr.size();i++){

 			cout<<op3[p*attr.size()+i]<<" " ;
 		}
 		cout<<"\n" ;
 		
 	}
 	//cout<<"helllllllllllllllllllllllllllllllll" ;	
 	return 1 ;
} */

int check_query_assign(string q ) {
	pair < string ,string >  p  = check_query1(q) ;
	if(p.first!="" && p.second!=""){
			int i ;

			for( i=0;i<tables.size();i++){
				if(tables[i]==p.first)
					break ;
			}
			//cout<<p.first; 
			if(i==tables.size()){
				cout<<"error! create table first using define" ;
				return 0;
			}
			parse(p.second,p.first,i) ;	
			return 1 ;
	}
	return 0 ;  // wrapper for assignement query

}

pair < vector<string> , int > cart_helper(string q){
	q =rm_space(q) ;
	int i = findstr(q,"cartesian_product") ;
	if(i==-1){
		if(table_lookup.find(q)==table_lookup.end()){
			vector<string> v ;
			//cout<<"error\n" ;
			return make_pair(v,-1) ;
		}
		else {
			
			return make_pair(tval[table_lookup[q]] , tcount[table_lookup[q]] )  ;
		}
	}
	string q1 = rm_space(q.substr(0,i)) ;
	string q2 = rm_space(q.substr(i+18,q.size())) ;
	pair < vector<string> , int > p1, p2 ;
	p1 = cart_helper(q1) ;
	p2 = cart_helper(q2) ;
	if(p1.second == -1 || p2.second == -1){
		//cout<<"No such table\n" ;
		vector<string> v ;
			//cout<<"error\n" ;
		return make_pair(v,-1) ;

	}
	return make_pair(cartesian_product(p1.first , p2.first , p1.second , p2.second) , p1.second + p2.second) ;  // helper method for cartesian product
}

pair < vector<string> , vector<string> > expr_helper(string q){
	q =rm_space(q) ;
	int i = findstr(q,"union") ;
	int j = findstr(q,"intersect") ;
	int k = findstr(q,"setdiff") ;
	int type = -1 ;
	if(i==-1 && j==-1 && k==-1){
		if(table_lookup.find(q)==table_lookup.end()){
			vector<string> v ;
			//cout<<"error\n" ;
			return make_pair(v,v) ;
		}
		else {
			
			return make_pair(tval[table_lookup[q]] , tcount[table_lookup[q]] )  ;
		}
	}
	//vector<string> v ;
			//cout<<"error\n" ;
	//	return make_pair(v,v) ;

	type = 1 ;
	if(i==-1){
		i=j ;
		type =2 ;
	}
	else if (i!=-1 && j!=-1){
		i = min(i,j) ;
		if(i==j)
			type = 2 ;
		else 
			type =1 ;
	}

	if(k!=-1){

		if(k<i || i==-1){
			i=k ;
			type=3 ;
		}

	}
	//cout<<type ;
	string q1 = rm_space(q.substr(0,i)) ;
	string q2 ;
	if(type==1)
		q2 = rm_space(q.substr(i+6,q.size())) ;
	else if(type==2)
		q2 = rm_space(q.substr(i+10,q.size())) ;
	else
		q2 = rm_space(q.substr(i+8,q.size())) ;
	pair < vector<string> , vector<string> > p1, p2 ;
	p1 = expr_helper(q1) ;
	p2 = expr_helper(q2) ;
	if(p1.second.size() == 0 || p2.second.size() == 0 || p1.second.size()!=p2.second.size()){
		//cout<<"No such table\n" ;
		vector<string> v ;
			//cout<<"error\n" ;
		return make_pair(v,v) ;

	}
	for(int th =0 ;th < p1.second.size();th++){
		if(p1.second[th]!=p2.second[th]){
			vector<string> v ;
			//cout<<"error\n" ;
			return make_pair(v,v) ;

		}

	}

	if(type==1){
		return make_pair(logicalor(p1.first , p2.first , p1.second.size()) , p1.second) ;
	}
	else if(type==2)
		return make_pair(logicaland(p1.first , p2.first , p1.second.size()) , p1.second) ; // helper method for expressions
	else 
		return make_pair(logicaldiff(p1.first , p2.first , p1.second.size()) , p1.second) ;
}

pair < vector<string> , vector<string> > project_nested(string q){ // metohd for project query

 	
 	int i = findstr(q,"from") ;
 	vector <string> v ;
 	if(i==-1)
 		return make_pair(v,v);
 	vector<string> attr = split(rm_space(q.substr(0,i)),',') ;
 	string tname =rm_space(q.substr(i+6,q.size())) ;
 	//cout<<tname<<"\n" ;
 	int tind ;
 	if(table_lookup.find(tname)==table_lookup.end()){
 		//cout<<"no such table\n" ;
 		return make_pair(v,v);
 	}else
 		tind = table_lookup[tname] ;


 	//iter_vec(attr) ;
 	vector<int> indx ;
 	for(int i=0;i<attr.size();i++){

 		vector<string> tert =  split(attr[i],'.') ;
 		attr[i] = tert[1] ;
 		if(attr_lookup[tind].find(attr[i])==attr_lookup[tind].end() || tert[0]!= tname){
 			//cout<<"no such attribute\n" ;
 			return make_pair(v,v) ;
 		}
 		indx.push_back(attr_lookup[tind][attr[i]]) ;
 	}
 	//for(int i=0;i<indx.size();i++){
 	//	cout<<indx[i]<<" " ;
 	//}
 	vector<string> op ; 
 	int pass = tval[tind].size()/tattr[tind].size() ;
 	int s = tattr[tind].size() ;
 	for(int p=0;p<pass;p++){
 		for(int i=0;i<indx.size();i++){
 			op.push_back(tval[tind][p*s+indx[i]]) ;
 		}
 	}
 	op = remove_duplicates(op,indx.size()) ;
 	for(int i=0;i<attr.size();i++){
 		attr[i] = tname + "." + attr[i] ;
 	}
 	return make_pair(op,attr) ;
 	
 	
}

pair < vector<string> , vector<string> > select_nested(string q){
	q= rm_space(q) ;
	vector<string> pfirst ;

	vector<string> empv ;

 	map<string , string > rname ;
 	
 	
 	int i = findstr(q,"from") ;
 	if(i==-1)
 		return make_pair(empv,empv) ;
 	
 	
 	vector<string> attr = split(rm_space(q.substr(0,i)),',') ;
 	//iter_vec(attr) ;
 	q=rm_space(q.substr(i+6,q.size())) ;
 	i= findstr(q,"where") ;
 	string tname  ;
 	int whflag= 0 ;
 	if(i==-1){
 		whflag=1 ;
 		tname = q ;
 	}
 	string expr ;
 	if(whflag!=1){
 		expr = rm_space(q.substr(i+7,q.size())) ;
 		tname  = rm_space(q.substr(0,i)) ;
 	}else {
 		expr="" ;
 	}
 	
 	//cout<< tname<<"\n" ;

 	vector<string> table_name = split(tname,',') ;
 	if(table_name.size()==1){
 		tname = table_name[0] ;
 		int tind ;
 		vector<int> indx ;
 		
 		
 		if(table_lookup.find(tname)==table_lookup.end()){
 			cout<<"table doesnt exist\n" ;
 			return make_pair(empv,empv) ;
 		}
 		tind = table_lookup[tname] ;
 		
 		for(int i=0;i<attr.size();i++){
 			if(attr_lookup[tind].find(attr[i])==attr_lookup[tind].end()){
 				cout<<"no such attribute\n" ;
 				return make_pair(empv,empv) ;
 			}
 			indx.push_back(attr_lookup[tind][attr[i]]) ;
 		}

 		vector<string> op ;
 		flag_exp=0 ;
 		if(expr!=""){
 			op = expression_evaluator(expr,tind) ;
 			
 		}
 		else 
 			op  = tval[tind] ;
 		flag_exp=0 ;
 		//iter_vec(attr) ;
 		
 		int pass = op.size()/tcount[tind] ;
 		for(int i=0;i<pass;i++){
 			for(int j=0;j<indx.size();j++){
 				pfirst.push_back(op[i*tcount[tind]+indx[j]]) ;
 			}
 			
 		}
 	
 		return make_pair(pfirst,attr) ;
 	}
 	
 	vector<int> table_index  ;
 	for(int it = 0 ;it<table_name.size();it++){
 		//cout<<table_name[it]<< " \n" ;
		if(table_name[it].substr(0,7)=="rename "){

			//cout<<"hello\n" ;
			//return 1 ;
			table_name[it] = rm_space(table_name[it].substr(7,q.size())) ;
			//cout<< table_name[it]<<"\n" ;
			//return 1 ;
			vector<string > vec = split(table_name[it],' ') ;
			//iter_vec(vec) ;
			if(vec.size()!=2)
				return make_pair(empv,empv) ;
			if(table_lookup.find(vec[0])==table_lookup.end()){
    				cout<<"no such table";
    				return make_pair(empv,empv) ;
    			}
    			if(table_lookup.find(vec[1])!=table_lookup.end()){
    				cout<<"name exists\n" ;
    				return make_pair(empv,empv) ;
    			}

    			//cout<<vec[0]<<"-"<<vec[1] <<"\n" ;
    			//return 1 ;
    			table_name[it] = vec[1] ;
    			

    			table_index.push_back(table_lookup[vec[0]]) ;
    			rname[vec[1]] = vec[0] ;

 		}else {
 			if(table_lookup.find(table_name[it])==table_lookup.end()){
    				cout<<"no such table";
    				return make_pair(empv,empv) ;
    			}
 			table_index.push_back(table_lookup[table_name[it]]) ;
 		}
 	}
 	//return 1 ;
 	/*cout<<"\n"<<table_index.size()<< " " ;
 	for(int it=0;it<table_index.size();it++){
 		cout<< table_index[it]<<" " ;
 	}
 	iter_vec(table_name) ;
 	return 1  ;*/
 	vector<string> table_attr ;
 	vector<string> table_val ;
 	for(int i=0;i<table_name.size();i++){
 		for(int j=0;j<tcount[table_index[i]];j++){
 			table_attr.push_back(table_name[i]+"."+tattr[table_index[i]][j]) ;
 		}
 	}
 	//iter_vec(table_attr) ;
 	//return 1 ;

 	//for(int i=0;i<table_name.size();i++){
 	//	iter_vec(tval[table_index[i]]) ;
 	//}
 	//return 1 ;
 	table_val = cartesian_product(tval[table_index[0]] , tval[table_index[1]],tcount[table_index[0]], tcount[table_index[1]]) ;
 	//iter_vec(table_attr) ;
 	//iter_vec(table_val) ;
 	int s = tcount[table_index[0]]+ tcount[table_index[1]] ;
 	//iter_vec(table_val) ;
 	//return 1 ;
 	for(int i=2;i<table_name.size();i++){
 		table_val = cartesian_product(table_val,tval[table_index[i]],s , tcount[table_index[i]]) ;
 		s=s+tcount[table_index[i]] ;

 	}
 	int pass = table_val.size()/s ;
 	/*for(int p=0;p<pass;p++){
 		for(int i=0;i<s;i++){
 			cout<<table_val[p*s+i]<<" " ;
 		}
 		cout<<"\n" ;
 	}*/
 	//cout<<expr ;
 	//iter_vec(table_val) ;
 	//return 1 ; 
 	vector<string> op2 ;
 	if(expr!=""){
 		op2 = expression_evaluator2(expr,table_val,table_attr) ;
 	}else
 		op2 = table_val ;
 	//iter_vec(op2) ;
 	//return make_pair(empv,empv) ;


 	map<string ,int> mmap ;
 	for(int i=0 ;i<table_attr.size();i++) {
 		//cout<<table_attr[i]<<" " ;
 		vector<string> tvec = split(table_attr[i],'.') ;
 		if(tvec.size()!=2){
 			cout<<"error4" ;
 			return make_pair(empv,empv) ;
 		}
 		//iter_vec(tvec) ;

 		if(table_lookup.find(tvec[0])!=table_lookup.end() ){
 			int  j = table_lookup[tvec[0]] ;
 			if(attr_lookup[j].find(tvec[1])!=attr_lookup[j].end()){
 				mmap[table_attr[i]]= i ;
 			}else {
 				cout<<"no such attribute\n" ;
 				return make_pair(empv,empv) ;
 			}
 		}else if(rname.find(tvec[0])!=rname.end()){

 			string nm = rname[tvec[0]] ;
 			//cout<<nm ;
 			//return 1 ;
 			int  j = table_lookup[nm] ;
 			//cout<<j ;
 			//return 1 ;
 			if(attr_lookup[j].find(tvec[1])!=attr_lookup[j].end()){
 				mmap[table_attr[i]]= i ;

 			}else {
 				cout<<"no such attribute\n" ;
 				return make_pair(empv,empv) ;
 			}
 		}
 		else {
 			cout<<"no such table\n";
 			return make_pair(empv,empv) ;
 		}

 	}
 	//return 1 ;
 	//map<string, int> :: iterator itt ;
 	//for(itt = mmap.begin();itt!=mmap.end();itt++){
 	//	cout<<itt->first <<" "<<itt->second<<"\n" ;
 	//}
 	//iter_vec(attr) ;
 	pass= op2.size()/s ;

 	
 	vector<string> op3 ;
 	//iter_vec(op2) ;
 	//return 1 ;
 	for(int p=0;p<pass;p++){
 		for(int i=0;i<attr.size();i++){
 	//		cout<<mmap[attr[i]] << " "<<attr[i] << " "<< op2[p*s+mmap[attr[i]]] ;
 			op3.push_back(op2[p*s+mmap[attr[i]]]) ;
 		}
 		
 	}
 	//iter_vec(op3) ;
 	op3 = remove_duplicates(op3,attr.size()) ;
 	//iter_vec(op3) ;
 	pass=op3.size()/attr.size() ;
 	for(int p=0;p<pass;p++){
 		for(int i=0;i<attr.size();i++){

 			pfirst.push_back(op3[p*attr.size()+i]) ;
 		}
 		//cout<<"\n" ;
 		
 	}
 	//cout<<"helllllllllllllllllllllllllllllllll" ;	
 	return make_pair(pfirst,attr) ;  // method for select query
}

pair < vector<string> , vector<string> > nested_helper(string q ){
	q = rm_space(q) ;
	int type ;
	//cout<<q ;
	//cout<<"\n" << q.substr(0,7) ;
	if(q.substr(0,7)=="select ")
		type = 1 ;
	else if(q.substr(0,8)=="project ")
			type = 2 ; 
	//cout<< q<<" "<< type <<"\n" ;	
	q = rm_space(q.substr(6+type,q.size())) ;
	//cout<<type ;

	 int oltype = type ;


 	//cout<<"-"<< q ;
	if(findstr(q,"select")== -1 && findstr(q,"project") == -1 ){
		
		if(type==1){
			//cout<<q ;	
			return select_nested(q) ;
		}
		else
			return project_nested(q) ;
	}else {
		
		int i = findstr2(q,"select") ;
		int j = findstr2(q,"project") ;
		
		if(i==-1 || j==-1) {
			if(i==-1){
				i=j  ;
				type=2 ; 
			}else
				type = 1 ;
		}else if (i>j){
			type=2 ;
			i=j ;
		}else{
			type = 1 ;
		}

		//cout<<q<<"\n" << type ;
		
		vector<string> attrlist ;
		string condition ;
		//cout<<rm_space(q.substr(0,i)) ;
		if(oltype==2)
			attrlist = split(rm_space(q.substr(0,i)), ',') ;
		else if(oltype==1)
			condition = rm_space(q.substr(0,i)) ;
		//cout<<attrlist.size() ;
		//for(int at = 0 ;at<attrlist.size();at++)
		//	cout<<attrlist[at] <<"-" ;
		

		pair< vector<string> , vector<string> > pa = nested_helper(q.substr(i,q.size())) ;
		vector<string> tbl ,attributes ;


		
		if(oltype==2){
			vector<int> cntr ;
			for(int i=0;i<attrlist.size();i++){
				for(int j=0;j<pa.second.size();j++){
					if(attrlist[i]==pa.second[j])
						cntr.push_back(j) ;
				}
			}
			

			int pass = pa.first.size()/pa.second.size() ;
			vector<string> finop ;
			

			for(int i=0;i<pass;i++){
				for(int j=0;j<cntr.size();j++){
					
					finop.push_back(pa.first[i*pa.second.size()+cntr[j]]) ;
				}
			}
			//iter_vec(finop) ;
			
			return make_pair(remove_duplicates(finop,attrlist.size()),attrlist) ;
		}else if(oltype==1){
			//cout << condition <<"\n" ;
			//iter_vec(pa.first) ;
			//iter_vec(pa.second) ;
			return make_pair(expression_evaluator2(condition, pa.first , pa.second),pa.second) ;
		}


	}

	vector<string> v ;
	return make_pair(v,v) ;  // method for nested queries of select project and rename




}


int check_query_cartesian(string q) {
	q = rm_space(q) ;
	int i = findstr(q,"cartesian_product") ;
	if(i==-1)
		return 0 ;
	pair < vector<string> ,int >values  = cart_helper(q) ;
	
	if(values.second==-1){
		cout<<"No such table\n" ;
		return 0 ;
	}


	for(int i=0;i<values.first.size();i++){
		if(i%values.second==0)
			cout<<"\n" ;
		cout<< values.first[i]<< " " ;
	}
	cout<<"\n" ;
	return 1 ;  // metohd for cartesian product
}

int check_query_expression(string q) {
	q = rm_space(q) ;
	int i = findstr(q,"union") ;
	int j = findstr(q,"intersect") ;
	int k = findstr(q,"setdiff") ;
	if(i==-1 && j==-1 && k==-1)
		return 0 ;
	pair < vector<string> , vector<string> >values  = expr_helper(q) ;
	//cout<<"hell" ;
	if(values.second.size()==0){
		cout<<"No such table\n" ;
		return 0 ;
	}


	for(int i=0;i<values.first.size();i++){
		if(i%values.second.size()==0)
			cout<<"\n" ;
		cout<< values.first[i]<< " " ;
	}
	cout<<"\n" ;
	return 1 ; // method for writing and evaluating expressions
}






int check_query_nested(string q) {
	q= rm_space(q) ;
	if(q.substr(0,7)!="select " && q.substr(0,8)!="project ")
		return 0 ;
	
	
	pair< vector<string> , vector<string> > pa = nested_helper(q) ;

	for(int i=0;i<pa.second.size();i++){
 		cout<<pa.second[i]<<" " ;
 	}
 	for(int i=0;i<pa.first.size();i++){
 		if(i%pa.second.size()==0)
 			cout<<"\n" ;
 		cout<<pa.first[i]<<" " ;
 	}
 	cout<<"\n" ;
	
	return 1 ;  // method to check if it is a nested query

}

int check_query_join(string q){  // method for implementing natural join


	q= rm_space(q) ;
	if(q.substr(0,5)!="join ")
		return 0 ;

	q= rm_space(q.substr(5,q.size())) ;
	int i=findstr(q,"{") ;
	if(i==-1)
		return 0 ;
	string tabname = rm_space(q.substr(0,i)) ;
	if(table_lookup.find(tabname)==table_lookup.end()){
		return 0 ;
	}
	int tind = table_lookup[tabname] ;
	q =rm_space(q.substr(i+2,q.size()-3-i)) ;
	vector<string> jatt = split(q,',') ;
	vector<int> indx ;
 	for(int i=0;i<jatt.size();i++){
 		if(attr_lookup[tind].find(jatt[i])==attr_lookup[tind].end()){
 			//cout<<"no such attribute\n" ;
 			return 0 ;
 		}
 		//cout<< attr_lookup[tind][jatt[i]] ;
 		indx.push_back(attr_lookup[tind][jatt[i]]) ;
 	}

 	//for(int it=0;it<indx.size();it++){
 	//	cout<<indx[i] << " ";
 	//}
 	vector<string> finop ;
 	vector<string> op1 = cartesian_product(tval[tind], tval[tind] , tcount[tind] , tcount[tind]) ;
 	int pass = op1.size()/(tcount[tind]*2) ;
 	sort(indx.begin(), indx.end()) ;
 	//cout<<pass<< tcount[tind]*2<< "\n" ;
 	//iter_vec(op1) ;
 	//cout<< indx[0] << indx[1] ;
 	for(int i=0;i<pass;i++){
 		int flg = 0 ;
 		for(int j=0;j<indx.size();j++){
 			int t = indx[j] ;
 			assert(tcount[tind]*2*i+t < op1.size()) ;
 			assert(tcount[tind]*2*i+t + tcount[tind] < op1.size()) ;
 			
 			if(op1[tcount[tind]*2*i+t] != op1[tcount[tind]*2*i+t + tcount[tind]]){
 				flg =1 ;
 				break ;
 			}
 		}
 		if(flg==0){
 			int pq =0  ;
 			for(int pt=0;pt<2*tcount[tind];pt++){
 				//cout<< op1[tcount[tind]*2*i + pt] << " " ;
 				if(pq < indx.size() && pt == indx[pq]){
 					pq++ ;
 					continue ;
 				}
 				else {
 					//cout << op1[tcount[tind]*2*i+pt] << " " ;
 					finop.push_back(op1[tcount[tind]*2*i+pt]) ;
 				}
 			}
 		} 

 	}

 	pass = finop.size() / (2*tcount[tind] - indx.size()) ;
 	int len  = (2*tcount[tind] - indx.size()) ;
 	for(int i= 0 ;i < pass ;i++){
 		for(int j=0;j<len;j++){
 			cout<< finop[len*i+j] << " " ;
 		}
 		cout<<"\n" ;
 	}	
 	return 1 ;

}
int main(){
	string q ;
	read_from_file() ;	 // read data from file

	while(1){
		write_to_file() ; // write data to file
		cout<<">>" ;
		getline(cin,q,'\n') ;
		//cout<<"1" ;
		//cout<< q<<"\n" ;

		int res ; // check the query by parsing the string and take approporiate action
		

		res = check_query_nested(q) ;
		//cout<<res ;
		if(res!=0)
		
			continue ;
		
		res = check_query_join(q) ;
		if(res!=0)
			continue ;
		res = check_query_def(q) ;
		if(res!=0)
			continue ;
		res = check_query_rename(q) ;
		if(res!=0)
			continue ;
		
		//res = check_query_project(q) ;
		//if(res!=0)
		//	continue ;
		
		//res = check_query_select(q) ;
		//if(res!=0)
		//	continue ;
		
		res = check_query_assign(q) ; // assignment
		if(res!=0)
			continue ;

		res = check_query_cartesian(q) ;
		if(res!=0)
			continue ;
		res = check_query_expression(q) ;
		if(res!=0)
			continue ;

		
		//show_tables() ;
	}

	return 0 ;
}