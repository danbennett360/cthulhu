#include <iostream>
#include <tinyxml2.h>

#include <unistd.h>
#include <time.h>
#include <sys/time.h>


using namespace std;
using namespace tinyxml2;

const string PROGRAM_VERSION = "1.0";
const string DICE_VERSION = "1.2";
const string PLAYER_VERSION = "1.0";
const string RULES_VERSION = "0.5";

XMLElement * AddEnvironmentInfo(XMLDocument & doc, int argc, char * argv[]);

XMLElement * QuickElement (XMLDocument & doc,  string name, string value) {
    XMLElement * tmp2;
    tmp2 = doc.NewElement(name.c_str());
    tmp2->SetText(value.c_str());
    return tmp2;
}

XMLElement * AddEnvironmentInfo(XMLDocument & doc, int argc, char * argv[]){

    // bail if NULL
    //      this might let us be lazy if we really don't want to save
    if (doc == NULL) {
        return NULL;
    }

    char buf[100];

    XMLElement * env = doc.NewElement("Environment");
    XMLElement * tmp, * tmp2;

    // program info
        // version info
	// arguments
    tmp = doc.NewElement("Version");
    
    tmp->InsertEndChild(QuickElement(doc,"ProgramName", argv[0]));
    tmp->InsertEndChild(QuickElement(doc,"Dice", DICE_VERSION));
    tmp->InsertEndChild(QuickElement(doc,"Player", PLAYER_VERSION));
    tmp->InsertEndChild(QuickElement(doc,"Rules", RULES_VERSION));
    tmp->InsertEndChild(QuickElement(doc,"Program", PROGRAM_VERSION));

    env ->InsertEndChild(tmp);

    if (argc > 1) {
        tmp = doc.NewElement("Arguments");
            for(int i=1;i<argc;i++) {
               tmp2 = doc.NewElement("arg");
	       tmp2->SetAttribute("Position",i);
               tmp2->SetText(argv[i]);
               tmp->InsertEndChild(tmp2);
    	    }

        env ->InsertEndChild(tmp);
    }

    tmp = doc.NewElement("Runtime");
    // Other information
        // hostname
    gethostname(buf, 100);
    tmp->InsertEndChild(QuickElement(doc,"Host", buf));
	// date

    time_t  tp;
    string tString;

    time(&tp);
    tString = ctime(&tp);
    // kill the trailing \n that unix supplies
    tString = tString.substr(0,tString.size()-1); 
    tmp->InsertEndChild(QuickElement(doc,"Date", tString));
	
    env ->InsertEndChild(tmp);

    return env;
}

int main(int argc, char * argv[]) {

    XMLDocument doc;

    // create a document
    XMLNode * root = doc.NewElement("CthulhuRun");
    doc.InsertFirstChild(root);

    // add environment information
    XMLNode * tmp;

    tmp = AddEnvironmentInfo(doc, argc, argv);

    root->InsertEndChild(tmp);

    // add run information
    XMLElement * run = doc.NewElement("RunData");
    root->InsertEndChild(run);

    doc.SaveFile( "madeByHand.xml" );

    return 0;
}
