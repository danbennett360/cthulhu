#include <iostream>
#include <tinyxml2.h>

#include <unistd.h>
#include <time.h>
#include <sys/time.h>


using namespace std;
using namespace tinyxml2;

const string XML_SAVE_VERSION = "0.5";


// global for now.  Decide later how to do it.
XMLDocument doc;
XMLElement * RunData;
XMLElement * CurrentGame;
string SaveFileName;

void XMLSaveFileInit(string filename, int argc, char * argv[]) {

    SaveFileName = filename;

    // create a document
    XMLNode * root = doc.NewElement("CthulhuRun");
    doc.InsertFirstChild(root);

    // add environment information
    XMLNode * tmp;

    tmp = AddEnvironmentInfo(doc, argc, argv);

    root->InsertEndChild(tmp);

    // add run information
    RunData = doc.NewElement("RunData");
    root->InsertEndChild(run);

    return;
}

void XMLSaveFileFinish() {
    doc.SaveFile(FileName.c_str() );
    return;
}

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
    tmp->InsertEndChild(QuickElement(doc,"XML_SAVEFILE", XML_SAVE_VERSION));

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
void StartGame(int number, int players) {
    CurrentGame = doc.NewElement("Game");
    CurrentGame->SetAttribute("GameNumber",number);
    CurrentGame->SetAttribute("Players",players);
    return;
}

void EndGame() {
    RunData ->InsertEndChild(CurrentGame);
    currentGame = NULL;

    return;
}

void SaveTurn(int turnNumber int caster, int victim, string attack, string casterReplace, string reply, string replyReplace) {
    /*
     * <Turn number="number">
     *   <Attack player="player" victim = "victimid">
     *       <Roll>roll </Roll>
     *       <Replace>roll </Replace>
     *    </Attack>
     *    <Respond>
     *       <Roll>roll </Roll>
     *       <Replace>roll </Replace>
     *    </Respond>
     * </Turn>
}
