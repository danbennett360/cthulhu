#include "player.h"
#include <iostream>
#include <cstdlib>

#include <vector>


using namespace std;

bool TestEye(PlayerT & player, int role, int oSane, int CTSane, int res);
bool TestIncrement(PlayerT & player, bool add, int count, bool sane);

int main() {

    srand(time(NULL));
    StateT result;

    PlayerT player1, player2(DOUG);

    // tell me about the players.
    cout << " We have two players " << endl;
    cout << "Player 1: " << player1 << endl;
    cout << "Player 2: " << player2 << endl;

    cout << "Player 1 loses/gains a sanity point" << endl;
    if(!TestIncrement(player1, false, 2, true)) return -1;
    if(!TestIncrement(player1, false, 1, true)) return -1;
    if(!TestIncrement(player1, false, 0, false)) return -1;
    if(!TestIncrement(player1, false, 0, false)) return -1;
    if(!TestIncrement(player1, true, 1, true)) return -1;
    if(!TestIncrement(player1, true, 2, true)) return -1;
    if(!TestIncrement(player1, true, 3, true)) return -1;



    cout << endl;

    // test for Doug's strategy
    cout << "Testing for eye decisions,DOUG" << endl;
    if(!TestEye(player2, ATTACKER, 2,1 , Tentacle)) return(-1);
    if(!TestEye(player2, DEFENDER, 1,3 , YellowSign)) return(-1);
    if(!TestEye(player2, DEFENDER, 2,3 , ElderSign)) return(-1);
    if(!TestEye(player2, DEFENDER, 3,0 , YellowSign)) return(-1);

    cout << endl;
    cout << "Testing for eye decisions, random" << endl;
    TestEye(player1, ATTACKER, 2,1 , RANDOM);
    TestEye(player1, ATTACKER, 1,3 , RANDOM);
    TestEye(player1, ATTACKER, 2,3 , RANDOM);
    TestEye(player1, ATTACKER, 0,3 , RANDOM);
    TestEye(player1, ATTACKER, 3,0 , RANDOM);
    TestEye(player1, DEFENDER, 3,0 , RANDOM);
    TestEye(player1, DEFENDER, 2,1 , RANDOM);
    TestEye(player1, DEFENDER, 1,3 , RANDOM);
    TestEye(player1, DEFENDER, 2,3 , RANDOM);
    TestEye(player1, DEFENDER, 0,3 , RANDOM);

    return 0;
}

bool TestIncrement(PlayerT & player, bool add, int count, bool sane){

    cout << "\tPlayer Before Action: " << player << endl;

    if (!add) { 
        player.GiveToken();
	cout << "\tRemoving a point " << endl;
    } else {
        player.GetToken();
	cout << "\tAdding a point " << endl;
    }

    cout << "\tPlayer After Action:  " << player << endl;


    if (player.Sanity() == count) {
       cout << "\tCount Test: Good" << endl;;
    } else {
       cout << "\tCount Test: BAD BAD BAD" << endl;
       return(false);
    }

    if (player.IsSane()== sane ) {
       cout << "\tSanity Test: Good" << endl;;
    } else {
       cout << "\tSanity Test: BAD BAD BAD" << endl;
       return(false);
    }
    cout << endl;

    return true;
}

bool TestEye(PlayerT & player, int role, int oSane, int CTSane, int res){
     StateT result;
     bool rv = true;

     result = player.DecideResult(role, oSane, CTSane);
     cout << "Testing Eye Strategy" << endl;

     cout << "\tPlayer: " << player  << endl;
     cout << "\tStrategy: " << player.EyeStrategy()  << endl;

     cout << "\tRole: ";
     if (role == ATTACKER) {
         cout <<"Attacker";
     } else {
         cout <<"Victim";
     }
     cout << endl;

     cout << "\tOther Sanity: " << oSane 
          << ", Cthulhu Sanity " << CTSane << endl;

     cout << "\tResult : " << StateTToString(result) << endl;
     if (res == RANDOM) {
         cout << "\tExpected Result :  RANDOM" << endl;
         cout << "\tgood" << endl;
     } else {
         cout << "\tExpected Result : " <<  StateTToString(StateT(res)) << endl;
	 if (res == result) {
             cout << "\tGOOD!" << endl;
	 } else {
             cout << "\tBAD BAD BAD!" << endl;
	     rv = false;
	 }
     }
     cout << endl;

     return rv;
}

