#include "tokens.h"
#include "parse.h"
#include <fstream>
#include <iostream>
#include "tokens.h"
#include <string>
#include <istream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream file;
	int linenum = 0;

    //
    //CHECK ARGUMENTS LOAD FILES
    //
    /*
    bool vflag = false;
	bool allidsflag = false;
	bool sumflag = false;

    
	for( int i=1; i<argc; i++ ) {
		string arg( argv[i] );
        if( arg[0] != '-' ) continue;
		if(      arg == "-v"      ) vflag      = true;
		else if( arg == "-allids" ) allidsflag = true;
		else if( arg == "-sum"    ) sumflag    = true;
		else  { cerr << "INVALID FLAG " << arg << endl; return 0; }
    }*/
    
	istream *in = &cin;
    bool foundfile = false;
    for( int i=1; i<argc; i++ ) {
		string arg( argv[i] );
        if( arg[0] == '-' ) continue;
		if( foundfile ) { cerr << "TOO MANY FILENAMES" << endl; return 0; }
        file.open(arg);
        if( file.is_open() == false ) {
            cerr << "COULD NOT OPEN " << arg << endl;
            return 0;
        }
        foundfile = true;
        in = &file;
	}
/*
    int lineNumber = 0;
	Token	tok;
	int tokCount = 0;
	int stringCount = 0;
	int identCount = 0;
	map<string,bool> identifiers;
	while( (tok = getNextToken(in, &lineNumber)) != DONE && tok != ERR ) {
		if( vflag )
			cout << tok << endl;

		++tokCount;
		if( tok == SCONST ) {
			stringCount++;
		}
		else if( tok == IDENT ) {
			identCount++;
			identifiers[ tok.GetLexeme() ] = true;
		}
	}

	if( tok == ERR ) {
		cout << "Error on line " << lineNumber << " (" << tok.GetLexeme() << ")" << endl;
		return 0;
	}

	if( allidsflag && identifiers.size() > 0 ) {
     	cout << "IDENTIFIERS: ";
     	auto it = identifiers.begin();
     	cout << it->first;

		for( it++; it != identifiers.end(); it++ )
			cout << ", " << it->first;
		cout << endl;
	}

	if( sumflag ) {
		cout << "Total lines: " << lineNumber << endl;
		cout << "Total tokens: " << tokCount << endl;
		if( tokCount > 0 ) {
			cout << "Total identifiers: " << identCount << endl;
			cout << "Total strings: " << stringCount << endl;
		}
	}*/

    
    ParseTree *prog = Prog(in, &linenum);

	if( prog == 0 )
		return 0; // quit on error
    
    
    cout << "LEAF COUNT: " << (*prog).LeafCount() << endl;
    cout << "STRING COUNT: " << (*prog).StringCount() << endl;
    vector<string> idents = (*prog).GetIdents();
    cout << "IDENT COUNT: " << idents.size() << endl;
    map<string, int> identMap;
    for(int i = 0; i < idents.size(); i++) {
        if(identMap.find(idents[i]) == identMap.end())
            identMap[idents[i]] = 1;
        else
            identMap[idents[i]] += 1;
    }
    int c = 0;
    for(map<string, int>::iterator i = identMap.begin(); i != identMap.end(); i++) {
        cout << i->first;
        if(++c < identMap.size()) cout << ", ";
    }
    cout << endl;
	return 0;
}
