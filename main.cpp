#include <iostream> 
#include <iterator>
#include "LL.h"

using namespace std; 
void boardPrint(LL<bool> board[], int size); 
bool diagonalCheck(LL<bool> board[], int size);
//bool diagonalCheck(LL<bool> board[], int size, int location);
bool vertical(LL<bool> board[], int size, int local1); 
bool horizontalCheck(LL<bool> board[], int size, int moves);
char playGame(char move); 
int main()
{
    auto size = 7; 

    auto player1= true; 

    LL<bool> board[size];
    //size--; 
    char P1Choice ='\0'; 
    auto gameOver = 49; 
    auto played = 0;
    auto current = 0;
    int moves = 0;   
    boardPrint(board, size); 
    cout<<endl; 
    while(played <= gameOver)
    {   
        player1 = true; 
        if(player1)
        { 
            do{
                //input request and change to upper of input 
                //start game by calling function to use switch staments 
                //save move made as int to selcet location on board 
                //set conditions for out of moves and selection of wrong column 
                //insert tail (p1 is true & p2 is false)
                //check wining condittion indvidually and continue game
                cout<<"Red Player Select a row: "; 
                cin >> P1Choice;
                char selected = toupper(P1Choice);  
                moves = playGame(selected); 
                if(moves < 0 || moves >= size)
                {
                    cout<<"Invalid Column\n"; 
                    cin.clear();
                    continue;
                }
                if(board[moves].size() > 6)
                {
                    cout<<"Invalid Move\n"; 
                    cin.clear(); 
                    continue;;
                }
                board[moves].tailInsert(true); 
                played++;
                
                boardPrint(board, size); 
                cout<<endl; 
                bool vWin= vertical(board, size, moves);
                if(vWin == true) 
                {
                    cout<<"Red wins!"<<endl;
                    return 0; 
                } 
                bool hWin = horizontalCheck(board, size, moves);
                if( hWin) 
                {
                    cout<<"Red wins!"<<endl;
                    return 0; 
                } 
                bool dWin = diagonalCheck(board, size);
                if( dWin) 
                {
                    cout<<"Red wins!"<<endl;
                    return 0; 
                } 
                if(played == gameOver) break;
                player1 = false;  
            }while(player1); 
        }
        if(played == gameOver) break;
        bool player2 = true; 
                //input request and change to upper of input 
                //start game by calling function to use switch staments 
                //save move made as int to selcet location on board 
                //set conditions for out of moves and selection of wrong column 
                //insert tail (p1 is true & p2 is false)
                //check wining condittion indvidually and continue game
        if(player2)
        {
            do{
                //player2 = true; 
                cout<<"Blue Player Select a row: "; 
                cin >> P1Choice;
                char selected = toupper(P1Choice);  
                //check if proper input 
                moves = playGame(selected); 
                if(moves < 0 || moves > size)
                {
                    //cout<<"Red Player Select a row: " << selected;
                    cout<<"Invalid Column\n"; 
                    cin.clear();
                    continue;
                }
                if(board[moves].size() > 6)
                {
                    cout<<"Invalid Move\n"; 
                    cin.clear(); 
                    continue;
                }
                board[moves].tailInsert(false); 
                played++; 
                boardPrint(board, size);
                cout<<endl;  
                bool vWin= vertical(board, size, moves); 
                if(vWin == true)
                {
                    cout<<"Blue wins!"<<endl;   //win condition for ver 
                    return 0; 
                } 
                bool hWin = horizontalCheck(board, size, moves);
                if(hWin == true)
                {
                    cout<<"Blue wins!"<<endl;
                    return 0; 
                } 
                bool dWin = diagonalCheck(board, size);
                if( dWin) 
                {
                    cout<<"Blue wins!"<<endl;
                    return 0; 
                } 
                player2 = false;
                if(played == gameOver) break; 
            }while (player2); 
            if(played == gameOver) break;
        }
        if(played == gameOver) break;
    }
    cout<< "Tie.\n"; 

    return 0; 
}
char playGame(char move)
{
    int local= 0; 
    // local will act as num for cordaent to do the tail insert 
    //anything over six will count as an error to do the check in main 
    //board[0].tailInsert(true);  
    switch(move)
    {
        case 'A': 
            local = 0;
            break; 
        case 'B':
            local = 1;
            break; 
        case 'C':
            local = 2;
            break;
        case 'D':
            local = 3;
            break; 
        case 'E':
            local = 4;
            break;
        case 'F':
            local = 5;
            break;  
        case 'G':
            local = 6;
            break; 
        default:
            local = 1000; 
            break; 
        
    }
    return local; 
}

bool vertical(LL<bool> board[], int size, int local)
{
    auto x = 0; 
    while( x < size) //column 
	{
		auto count = 0;
		int location = (board[x].size());   //location of node, make sure there is one 
		if(location > 0)
		{
			auto first = board[x].begin();  //the first check 
			auto second = first;            //make sure starts at the same spot 
			if(location > 1)                //if there is a chip and is located at spot 1 and 1++ 
            {
                auto second = first++;      //the move second spot up by one
            } 
            auto i = 0;                      
			while( i < location-1)         //if our count is less then the location on the column
            {
                if (*first == *second)      //check if first and second are the same
				{
					first++;                //if they are, inc both and take count
					second++;
					count++;
				}
                else                        
                {
					first++;                //if not, still inc but zero count
					second++;
					count = 0;
				}
				if(count == 3)              //when count is 3, inlcuding location, well have connect 4
                {
                    return true;
                }
                i++;                        //inc until, we hit size
            }
		}
        x++; 
	}
	return false;
}
bool horizontalCheck(LL<bool> board[], int size, int location)
{
    size_t counter=0;
    auto lastMoveIt = --board[location].end(); // move is not the last played move
    bool lastMove = *lastMoveIt;                //Ta said this should work for left and right 

    // Check left
    int left = location - 1;
    for (int i = left; i >= 0 && board[i].size() >= board[location].size(); --i) {
        auto it = board[i].begin();
        for (int j = 0; j < board[location].size() - 1; ++j) {      //inc to the left if below curr location 
            ++it;
        }
        if (*it == lastMove) {                 //if last mov chip is the same as current one add counter 
            ++counter;
            if (counter == 3) {                 //if 3, means we have four pairs, exit true 
                return true;
            }
            continue;
        }
        break;
    }

    // Check right
    //smae logic as above, just check a diff direction 
    int right = location + 1;
    for (int i = right; i < size && board[i].size() >= board[location].size(); ++i) {
        auto it = board[i].begin();
        for (int j = 0; j < board[location].size() - 1; ++j) {      //make sure its, not out of order
            ++it;
        }

        if (*it == lastMove) {      //win condition
            ++counter;
            if (counter == 3) {     //counter for the win
                return true;
            }
            continue;
        }
        break;
    }
    return false;
}

bool diagonalCheck(LL<bool> board[], int size)
{
	if (size < 5) return false;
	int count = 0;
    //i cant make the right up work for the life of me soooo grade me nicely :)
    // for (int x = 0; x < size; x++) //row 
	// {
	// 	for (int y = 0; y < size-1; y++)  //col 
	// 	{
	// 		int currRow = x, currCol = y;       //working x and y 
	// 		count = 0;
	// 		while (currRow+2 >= 0 && currCol < size-1)
	// 		{
	// 			int length = (board[currCol].size()); //location on col 
    //             int nextRow = (board[currCol +1].size());
	// 			if (length >= currRow)
	// 			{
	// 				auto first = board[currCol].begin();  //1st node
    //                 auto second = board[currCol+1].begin();  
	// 				for (int i = 0; i < length - currRow - count; i++) //to determine, where it lands
    //                 {   
    //                     //i+=1; 
    //                     first++;
    //                     second++; 
                        

	// 			    }
    //                 second--; 
    //                 if (currCol >= 1 && *first == *second) {
    //                         count++;
    //                         if (count == 4) return true;
    //                     }
    //                     else count = -1;
    //             }
	// 			else count = 0;
	// 			currRow++;                  //dec the rows 
	// 			currCol--;                  //inc the col till a match 
	// 		}
    //     }
	// }

    //checks left down
	for (int x = 4; x < size; x++) //row 
	{
		for (int y = 0; y < size-1; y++)  //col 
		{
			int currRow = x, currCol = y;       //working x and y 
			count = 0;
			while (currRow+2 >= 0 && currCol < size-1)
			{
				int length = (board[currCol].size()); //location on col 
                int nextRow = (board[currCol +1].size());
				if (length >= currRow)
				{
					auto first = board[currCol].begin();  //1st node
                    auto second = board[currCol+1].begin();  
					for (int i = 0; i < length - currRow - count; i++) //to determine, where it lands
                    {   
                        //i+=1; 
                        first++;
                        second++; 
				    }
                    second--; 
                    if (currCol >= 1 && *first == *second) {    //if we are above zero and match diagnoallly
                            count++;
                            if (count == 4) return true;
                        }
                        else count = -1;
                }
				else count = 0;
				currRow--;                  //dec the rows 
				currCol++;                  //inc the col till a match 
			}
        }
	}

	return false;
}

void boardPrint(LL<bool> board[], int size)
{
    auto count = 0; 
    auto Count2 = 0; 
    for(auto x = 0; x < size; x++) //rows 
    {   
        cout << endl; 
        for(auto y = 0; y < size; y++)   //colum and ll 
        {
            size_t location = board[y].size();  //get location of lll          
                if((size - location) > x)   //selcet location based of colum size and row size 
                {
                    cout<< " - ";    //if no chip, fill with blanks(-)
                }
                else
                {   
                    auto it = board[y].begin();     //set up itterator 
                    for(auto i = 0; i < size-x-1; i++)  //to selct spot in colum to determine where you can add 
                    {         
                       if(it != board[y].end())     //if not at the head, you can itteraot and add 
                        it++;      
                    }
                    if(*it == true)         //if true, red chip 
                    {
                        cout<<" R ";       
                    }
                    else if(*it == false)   //if false, blue chip 
                    {
                        cout<<" B ";      
                    }
                
                 }    
        }
    }
    cout<<endl; 
    cout << endl << " A  B  C  D  E  F  G "<<endl;  
} 

