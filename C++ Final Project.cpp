#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <stdlib.h>

using namespace std;

/*******************************************************************************************************

This section is dedicated user input validation, most of these are to ensure that the voter only puts the
allowed input and nothing else without crashing the programming

the last function is dedicated to making sure the user input for the voting ballot would be a valid vote

*******************************************************************************************************/

//Function, used to make sure that the user only inputs an integer and nothing else
int userInputCheckGreaterThanZero(string promptInput,int userInput){
	bool isTrue = 0;
	
	while(isTrue == 0){
		
		cout << promptInput << " ";
		cin >> userInput;
		cout << endl;
		
		if(cin.fail()){
			cin.clear();
			cin.ignore();
			
			cout << "-----------------------------------" << endl;
			cout << "Error: User input is not an integer" << endl;
			cout << "-----------------------------------" << endl << endl;
			
			isTrue = 0;
		}else if (userInput <= 0){
		
			cin.clear();
			cin.ignore();
			
			cout << "-----------------------------------------------" << endl;
			cout << "Error: User input is equal to or less than zero" << endl;
			cout << "-----------------------------------------------" << endl << endl;
			
			isTrue = 0;
		} else{
			isTrue = 1;
		}
	}
	
	return userInput;
}

//Function, used to verify user vote is only an integer
int userInputRankIntCheck(string promptInput,int userInput, bool randomGenerator, bool dialogueBool ){
	if (randomGenerator == 0){
	
		bool isTrue = 0;
		
		while(isTrue == 0){
			
			isTrue = 1;
			
			cout << "\t" << promptInput << " - ";
			cin >> userInput;
			cout << endl;
			
			if(cin.fail()){
				cin.clear();
				cin.ignore();
				
				cout << "-----------------------------------" << endl;
				cout << "Error: User input is not an integer" << endl;
				cout << "-----------------------------------" << endl << endl;
				
				isTrue = 0;
			}
		}
	} else{
		
		bool isTrue = 0;
		
		while(isTrue == 0){
			
			isTrue = 1;
						
			if(cin.fail()){
				cin.clear();
				cin.ignore();
				
				isTrue = 0;
			}
		}
	}
	
	return userInput;
}

double vectorSum ( vector<double> userInput){
	double sum = 0;
	unsigned int i;
	
	for(i=0; i < userInput.size(); ++ i){
		sum += userInput.at(i);
	}	

	return sum;
}

//Function, used to check if the user inputed either a 'Y' or a 'N' only
bool isValidCheck(string prompt, char isValid){

	do{
		cout << prompt << " ";
		cin >> isValid;
	
		cout << endl;
		
		if ((isValid != 'Y')&&(isValid != 'N')) {
			cout << "------------------------" << endl;
			cout << "Error: Only enter Y or N" << endl;
			cout << "------------------------" << endl << endl;
		}
		
	} while ((isValid != 'Y')&&(isValid != 'N'));
	
	if (isValid == 'Y'){
		return 1;
	}else if (isValid == 'N'){
		return 0;}
}

// Function, check the voter's ballad to make sure that it is valid
bool voterBallotCheck(int numReps, vector<int>& rankInput, bool randomGenerator){

//This first part is if this is a manual voter inputs and gives out an error warning	
	if (randomGenerator == 0){
		unsigned int i;
	
		// Verifies that none of the ranks are negative	
		for( i = 0; i < rankInput.size(); ++i){
	        if (rankInput.at(i) < 0){
	        	cout << endl << "******************************************************" << endl;
	            cout << " Error: Cannot rank a representative a negative number" << endl;
	            cout << "******************************************************" << endl<< endl;
	            return 0;
	        }
	    }
	    
	    //Verifies that none of ranks were ranked the same number
	    for( i = 0; i < rankInput.size(); ++i){
	    	int temp;
	    	
	    	temp = rankInput.at(i);
	    	
	    	if (temp > 0){
				for( int j = i+1; j < rankInput.size(); ++j){
	        		if (temp == rankInput.at(j)){
	        			cout << endl << "************************************************************" << endl;
	            		cout << "Error: Cannot rank two representatives with the same ranking" << endl;
	            		cout << "************************************************************" << endl << endl;;
	            		return 0;
	        		}
	        	}
	    	}
	    }
		
		//Finds the maximum value that a voter rank
	    int maxValue = rankInput.at(0);
	
	    for( i = 0; i < rankInput.size(); ++i){
	        if (rankInput.at(i) > maxValue){
	            maxValue = rankInput.at(i);}
	    }
	    
	    //Gives out an error message if one of the rankings is greater than the total number of representatives
	    if (maxValue > numReps){
	    	cout << endl << "************************************************************************************" << endl;
	    	cout << 		"Error: Cannot rank a representative greater than the total number of representatives" << endl;
	    	cout << "************************************************************************************" << endl;
	    	return 0;
		}	
		
		//verifies that the voters ballot is not all zeros
		int zeroCount = 0;
		
		for (i=0; i < rankInput.size(); ++ i){
			if (rankInput.at(i) == 0){
				zeroCount += 1;}
		}
		
		if (zeroCount == numReps){
			cout << endl;
			cout << "********************************************" << endl;
			cout << "Error: Cannot vote zero's for all canadiates" << endl;
			cout << "********************************************" << endl;
			return 0;
		}
	
		//creates a vector of the acceptable votes that can exist based off the maximum voting rank by starting with the largest number and decreasing
		
		/*
		4 3 2 1
		3 2 1 0
		2 1 0 0 
		1 0 0 0 
		
		ex) 3 2 1 4
		
		-> 4 3 2 1
		
		ex) 0 0 1 2

		->  2 1 0 -1
		->  2 1 0 0
		
		ex) 0 3 3 1
		
		-> 3 2 1 0 
		->
		
		*/
	    vector <int> acceptableVotes(numReps);
	
	    acceptableVotes.at(0) = maxValue;
	
	    for (i = 1 ; i < acceptableVotes.size(); ++i){
	        acceptableVotes.at(i) = acceptableVotes.at(i-1)-1;}
	    
		// if any number is negative than it converts to a zero
	    for (i = 0; i < acceptableVotes.size(); ++ i){
	        if (acceptableVotes.at(i) < 0){
	            acceptableVotes.at(i) = 0;}
	    }
	
		//Verifies the user votes is the same as the acceptable votes, ensure that there is a 1st, 2nd etc to their max vote
	
		int countMatch = 0;
		
	    for (i=0; i< acceptableVotes.size(); ++i){
	
	        int temp = acceptableVotes.at(i);
	
	        if( find(rankInput.begin(),rankInput.end(),temp)!=rankInput.end()){
	            countMatch = countMatch + 0;
	        } else{
				countMatch = countMatch + 1;}
	    }
	
	    if (countMatch > 0){
	    	cout << "Your vote is invalid, please try again" << endl;
			return 0;
			
	    } else{
	    	return 1;} 

// This part of the code is the copy-paste of the code above, the only difference being that it does not give out an error code	
	
	}else {
		unsigned int i;
	
		// Verifies that none of the ranks are negative	
		for( i = 0; i < rankInput.size(); ++i){
	        if (rankInput.at(i) < 0){
	            return 0;}
	    }
	    
	    for( i = 0; i < rankInput.size(); ++i){
	    	int temp;
	    	int countPlace = 0;
	    	
	    	temp = rankInput.at(i);
		
	    	if (temp > 0){
				for( int j = i+1; j < rankInput.size(); ++j){
	        		if (temp == rankInput.at(j)){
	            		return 0;}
	        	}
	    	}
	    }
		
		rankInput.resize(numReps);
		//Finds the maximum value that a voter rank
	    int maxValue = rankInput.at(0);
	
	    for( i = 0; i < rankInput.size(); ++i){
	        if (rankInput.at(i) > maxValue){
	            maxValue = rankInput.at(i);
	        }
	    }
	    
	    if (maxValue > numReps){
	    	return 0;}
		
	//verifies that the voters ballot is not all zeros
		int zeroCount = 0;
		
		for (i=0; i < rankInput.size(); ++ i){
			if (rankInput.at(i) == 0){
				zeroCount += 1;}
		}
		
		if (zeroCount == numReps){
			return 0;}
	
		//creates a vector of the acceptable votes that can exist based off the maximum voting rank by starting with the largest number and decreasing
	    vector <int> acceptableVotes(numReps);
	
	    acceptableVotes.at(0) = maxValue;
	
	    for (i = 1 ; i < acceptableVotes.size(); ++i){
	        acceptableVotes.at(i) = acceptableVotes.at(i-1)-1;}
	    
		// if any number is negative than it converts to a zero
	    for (i = 0; i < acceptableVotes.size(); ++ i){
	        if (acceptableVotes.at(i) < 0){
	            acceptableVotes.at(i) = 0;}
	    }
	
		//Verifies the user votes is the same as the acceptable votes, ensure that there is a 1st, 2nd etc to their max vote
	
		int countMatch = 0;
		
	    for (i=0; i< acceptableVotes.size(); ++i){
	
	        int temp = acceptableVotes.at(i);
	
	        if( find(rankInput.begin(),rankInput.end(),temp)!=rankInput.end()){
	            countMatch = countMatch + 0;
	        } else
				countMatch = countMatch + 1;	
	    }
	
	    if (countMatch > 0){
			return 0;
		} else
	    	return 1;
	}
}

/*******************************************************************************************************

This section is dedicated strictly to collecting votes from the different systems, given two variables:
	If the number of voters is known
	if the voters were randomly generated or not
	
Based off the user input, it goes into one of the options

*******************************************************************************************************/
vector<vector <int> > manualVoterInputUnknownNumVotes(vector<string> repNames, int numReps, int numSeats, int&  numVoters, bool dialogueBool){

	unsigned int i;
	
	bool randomGenerator = 0;
	vector<int> voterVotes;	
	vector<vector<int> > voterBallot;
    int rank;
    
    bool thirdValid = 0 ; // verifies that the voting is done

	do{
		char userValid = 'A';
		bool secondValid = 0; // verifies when each voter is done voting
		
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "\t\t\tVOTER BALLOT" << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "Rank the representatives from the most prefererd choice to least preferred."<< endl;
		cout << "1 - Is the most preferred, 2 - is second most preferred etc." << endl;
		cout << "If you do not want your vote to go to a representative, enter a 0 " << endl << endl;
		cout << "The representatives running are: ";
		
		for (i = 0; i < repNames.size(); ++i){
			if (i < (repNames.size() - 1)){
				cout << repNames.at (i) << ", ";
			} else{
				cout << repNames.at (i) << ". ";
			}
        }	
		
		cout << endl;
	
        while (secondValid ==  0){
        	vector<int> voterVotes;	
        	
        	bool voteCheck = 0;
        	      	
            do {
				for (i = 0; i < repNames.size(); ++i) {
                	string repNamePrompt = repNames.at(i);
                	rank = userInputRankIntCheck(repNamePrompt,rank, randomGenerator, dialogueBool);
                				
                	voterVotes.push_back(rank);
            	}
            	// CHECKS THE VOTERS BALLOT TO MAKER SURE IT IS WITHIN BOUNDS
           		voteCheck = voterBallotCheck(numReps, voterVotes, randomGenerator);
           		
           		if (voteCheck == 0){
               		voterVotes.clear();
                }
            
        	} while (voteCheck == 0);
                                                     
			string userValidate1 = "Submit your vote? (Y/N)";
			secondValid = isValidCheck(userValidate1, userValid);
        
			if (secondValid == 0){
                voterVotes.clear();
                voterVotes.pop_back();
            }else{
            	voterBallot.push_back(voterVotes);
                numVoters += 1;
			}
		}
		
		string userValidate1 = "Is this the final voter?(Y/N)";
		thirdValid = isValidCheck(userValidate1, userValid);
		
	} while (thirdValid == 0);
	
	voterVotes.resize(numVoters);
	 
	return 	voterBallot;
}

vector<vector <int> > manualVoterInputKnownNumVotes(vector<string> repNames, int numReps, int numSeats, int numVoters, bool dialogueBool){
	unsigned int i;
	
	bool randomGenerator = 0;
	vector<int> voterVotes;	
	vector<vector<int> > voterBallot;
    int numVoterCount = 0;
    int rank;     

	do{
		char userValid = 'A';
		bool secondValid = 0; // verifies when each voter is done voting
		
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "\t\t\tVOTER BALLOT" << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "Rank the representatives from the most prefererd choice to least preferred."<< endl;
		cout << "1 - Is the most preferred, 2 - is second most preferred etc." << endl;
		cout << "If you do not want your vote to go to a representative, enter a 0 " << endl << endl;
		cout << "The representatives running are: ";
		
		for (i = 0; i < repNames.size(); ++i){
			if (i < (repNames.size() - 1)){
				cout << repNames.at (i) << ", ";
			} else{
				cout << repNames.at (i) << ". ";
			}
        }	
		
		cout << endl;
	
        while (secondValid ==  0){
        	vector<int> voterVotes;	
        	
        	bool voteCheck = 0;
        	      	
            do {
				for (i = 0; i < repNames.size(); ++i) {
                	string repNamePrompt = repNames.at(i);
                	rank = userInputRankIntCheck(repNamePrompt,rank, randomGenerator, dialogueBool);
                				
                	voterVotes.push_back(rank);
            	}
            	// CHECKS THE VOTERS BALLOT TO MAKER SURE IT IS WITHIN BOUNDS
           		voteCheck = voterBallotCheck(numReps, voterVotes, randomGenerator);
           		
           		if (voteCheck == 0){
               		voterVotes.clear();
                }
            
        	} while (voteCheck == 0);
                                                     
			string userValidate1 = "Submit your vote? (Y/N)";
			secondValid = isValidCheck(userValidate1, userValid);
        
			if (secondValid == 0){
                voterVotes.clear();
                voterVotes.pop_back();
            }else{
            	voterBallot.push_back(voterVotes);
                numVoterCount += 1;
			}
		}
		
		cout << endl << numVoterCount << " votes out of " << numVoters << endl << endl;
		
	} while (numVoters > numVoterCount);
	
	voterVotes.resize(numVoters);
	
 	return voterBallot;
}

vector<vector <int> > randVoterKnownNumVoters(vector<string>& repNames, int numReps, int numSeats, int&  numVoters, bool dialogueBool){
	unsigned int i;
	
	bool randomGenerator = 1;
	vector<int> voterVotes;	
	vector<vector<int> > voterBallot;
    int numVoterCount = 0;
    int rank;
    
    srand(time(0));
    
	do{
		vector<int> voterVotes;	
		bool voteCheck = 0;

		do{        
	
			for (i = 0; i < repNames.size(); ++i) {
				rank = rand() % (numReps+1);
				voterVotes.push_back(rank);
			}
	            	// CHECKS THE VOTERS BALLOT TO MAKER SURE IT IS WITHIN BOUNDS
			voteCheck = voterBallotCheck(numReps, voterVotes, randomGenerator);
	           		
	        if (voteCheck == 0){
				voterVotes.clear();
	        }	
	            
	    } while (voteCheck == 0);
	                                                                      
	        voterBallot.push_back(voterVotes);
	        numVoterCount += 1;
			
	} while (numVoters > numVoterCount);
	
	voterVotes.resize(numVoters);
	
 	return voterBallot;
}

/*******************************************************************************************************

This section will be dedicated to calculation of which representatives should get the seat according to
the STV voting method

*******************************************************************************************************/
int surplusVotes(vector<vector<vector<double> > > masterVoterBallot, vector<vector<vector<double> > > &voteTransfer, vector<double> &repToSeat,vector<string> repNames, double thresholdVotes, bool dialogueBool){
	unsigned int i;
	unsigned int j;
	unsigned int k;
	unsigned int l;
	
	int vectorSize = repToSeat.size();
	vector < double > tempVector1(vectorSize);
	vector < vector< double> > tempVector2;
	
	int loopCount = 0;

	if(dialogueBool == 1){	
		cout << endl;
		cout << "=============================================================================================" << endl;
		cout << "\t\t\t\tOVERFLOW VOTES" << endl;
		cout << "=============================================================================================" << endl;
		cout << "This is the calculations dedicated to the representataives with an overflow of voters, " << endl;
		cout << "if a representative has more 1st rank votes than the threshold, those votes will be distributed" << endl;
		cout << "to their second pick proportional to the group and the number of excess votes." << endl;
		cout << "---------------------------------------------------------------------------------------------" << endl;
	}
		
	do{
		
		tempVector2.clear();
		bool addedVotes = 1;
		double addedVotesCount;
		
		for (i = 0; i < masterVoterBallot.size(); ++i){
			double totalNextVote = 0;
	
			for (j = 0; j < masterVoterBallot[i].size(); ++j){
				tempVector1.clear();
				
				for (k = 0; k < masterVoterBallot[i][j].size(); ++k){
					double value = 0;
					double extraVotes = 0;
					double repExtraVote;
	
					//Sets the adding vector to the number of extra votes
					if(masterVoterBallot[i][0][k] > thresholdVotes){
						
						repExtraVote = masterVoterBallot[i][0][k] - thresholdVotes;
						
						voteTransfer[i][0][k] = repExtraVote;
						
						repToSeat.at(i) = 1;
					}
					
					int findRep;
					
					if(loopCount == 0){
						extraVotes = voteTransfer[i][0][i];
					} else{
											
						for(l = 0; l <repToSeat.size(); ++l){
							if ((repToSeat.at(l) == 1) &&(l != i)){
								findRep = l;}
						}
										
						extraVotes = voteTransfer[i][loopCount][findRep];
					}
					totalNextVote = vectorSum(masterVoterBallot[i][loopCount+1]);
										
					//finds the value of the number of votes being transfered to the next rep
					if ((extraVotes > 0) && (totalNextVote > 0)){
						value = ((masterVoterBallot[i][loopCount+1][k]/totalNextVote)*extraVotes);	}	
					
					if(((value + voteTransfer[i][loopCount+1][k]) <= repExtraVote) && (vectorSum(voteTransfer[i][loopCount]) > 0)) {
						voteTransfer[i][loopCount+1][k] = value;}
					
					tempVector1.push_back(voteTransfer[i][loopCount+1][k]);
				}
			}	
			tempVector2.push_back(tempVector1);
		}
	
		for (i = 0; i < tempVector2.size(); ++i){				
			for (j = 0; j < tempVector2[i].size(); ++j){
				
				if((tempVector2[i][j] > 0) && (repToSeat.at(j) == 0)){
					voteTransfer[j][0][j] += tempVector2[i][j];} 
			}
		}		
	
		loopCount += 1;
		
	}while((loopCount+1)<vectorSize);
	
	// If a rep has more votes than needed it turns it into a negative number on the voter transfer ballot
	for (i = 0; i < voteTransfer.size(); ++i){
		if ((masterVoterBallot[i][0][i] - voteTransfer[i][0][i] ) == thresholdVotes){	
			voteTransfer[i][0][i] = -(voteTransfer[i][0][i]);
		}
	}

	// If there is a rep who has seat it turns the value to zero
	for (i = 0; i < voteTransfer.size(); ++i){
		for (j = 0; j < voteTransfer[i].size()-1; ++j){
			for (k = 0; k < voteTransfer[i][j].size(); ++k){
				
				if((vectorSum(voteTransfer[i][j+1]) == voteTransfer[i][j][k]) &&( j != 0)){
					voteTransfer[i][j][k] = 0;}
			}
		}
	}
	if(dialogueBool == 1){
		cout <<"--------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\tOVERFLOW DISTRIBUTION VOTES" << endl;
		cout <<"--------------------------------------------------------------------------" << endl;
		cout << "This section calculates the amount of overflow votes of each representative" << endl;
		cout << "and transfers their votes to the canadaite according to voter's next ranking" << endl;
		cout << endl;
	}
	
	for (i = 0; i < voteTransfer.size(); ++i){
		if(dialogueBool == 1){
			cout <<"__________________________________________________________________________" << endl;
			cout << "\t\t";
			for (j = 0; j < repNames.size(); ++j){
				cout << repNames.at(j) << "\t";}
			cout << endl <<"__________________________________________________________________________" << endl;
		}
		
		for (j = 0; j < voteTransfer[i].size(); ++j){
			if(dialogueBool == 1){
				cout << (j+1) << " rank Vote:\t";}

			for (k = 0; k < voteTransfer[i][j].size(); ++k){
				
				if ((vectorSum(voteTransfer[i][0])< 0) && (voteTransfer[i][j][k] > 0)){
					voteTransfer[i][j][k] = -(voteTransfer[i][j][k]);
				} 
				if(dialogueBool == 1){
					if (voteTransfer[i][j][k] > 0){
						cout << setprecision(3) << "+"<< voteTransfer[i][j][k] << "\t";
					} else{
						cout << setprecision(3) << voteTransfer[i][j][k] << "\t";}		
				}
			}
			if(dialogueBool == 1){
				cout << endl;}
		}
		if(dialogueBool == 1){
			cout << endl;}
	}
	
	if(dialogueBool == 1){
		cout << endl << "After adding the votes to the appropriate representatives, the representative(s) that meet the voting threshold are:" << endl;
		for (i = 0; i < repToSeat.size(); ++i){
			
			if ((masterVoterBallot[i][0][i] + voteTransfer[i][0][i] ) >= thresholdVotes){
				repToSeat.at(i) = 1;
		
				cout << "\t"<< repNames.at(i) << " with " <<(masterVoterBallot[i][0][i]+ voteTransfer[i][0][i])  << " votes."<< endl;
				  
			} else{
				repToSeat.at(i) = 0;}
		}
		cout << endl;
	}
}
	
int eliminateRep(vector<vector<vector<double> > > &masterVoterBallot, vector<vector<vector<double> > > &masterVoterBallotEdited, vector<vector<vector<double> > > &voteTransfer1, vector<double> &repToSeat, vector<double> & eliminatedRep, int numSeats , int numReps, vector<string> repNames, double thresholdVotes, int numVoters, bool dialogueBool){
	unsigned int i;
	unsigned int j;
	unsigned int k;
	unsigned int l;
	
	int vectorSize = repToSeat.size();
	
	double numEliminatedReps = numReps-numSeats;
	
	if(dialogueBool == 1){
		cout << endl;
		cout << "=============================================================================================" << endl;
		cout << "\t\t\t\tELIMINATE REPRESENTATIVES" << endl;
		cout << "=============================================================================================" << endl;
		cout << "When there are no representatives that have overflow votes, and there are still available seats" << endl;
		cout << "then we eliminate the representative with the lowest number of votes and distribute them to "<< endl;
		cout << "their next ranking vote. If that representative is not available, then those votes go to there" << endl;
		cout << "next ranking representative and so on and so for." << endl;
		cout << "---------------------------------------------------------------------------------------------" << endl;
	}
	
	int loopNum = 0;
	//tHIS SECTION IS TO FIND WHICH REPRESENTATIVES HAS THE LOWEST NUMBER OF VOTES
	do{
		double smallestVoteCount = numVoters;
		int smallestRep;
		
		for (i = 0; i < masterVoterBallotEdited.size(); ++i){
			for (j = 0; j < masterVoterBallotEdited[i].size(); ++ j){
				for (k = 0; k < masterVoterBallotEdited [i][j].size(); ++ k){
					voteTransfer1[i][j][k] = 0;}
			}
		}
		
		//Finds the rep with the smallest vote count that is not already eliminated or have seat.
		for (i = 0; i < masterVoterBallotEdited.size(); ++i){		
			if ((vectorSum(masterVoterBallotEdited[i][0]) < smallestVoteCount) && (eliminatedRep.at(i) != 1) && (repToSeat.at(i) != 1) ){
				smallestVoteCount = vectorSum(masterVoterBallotEdited[i][0]);}	
		}
		
		//after finding the smallest number of votes, finds the representative that had that number of votes;
		for (i = 0; i < masterVoterBallotEdited.size(); ++i){				
			if (vectorSum(masterVoterBallotEdited[i][0]) == smallestVoteCount){
				smallestRep = i; }	
		}
		
		// sets the rep to have an eliminated seat.
		eliminatedRep.at(smallestRep) = 1;
		if(dialogueBool == 1){
			cout << endl;
			cout << "The rep with the smallest vote count is: " << repNames.at(smallestRep) << " with " << smallestVoteCount << " thus they will be eliminated." <<endl;
			cout << endl;
		}
		
		for (i = 0; i < voteTransfer1.size(); ++i){
			for (j = 0; j < voteTransfer1[i].size()-1; ++ j){
				for (k = 0; k < voteTransfer1[i][j].size(); ++ k){
					double extraVote = smallestVoteCount;
					
					voteTransfer1[smallestRep][0][smallestRep] = - (masterVoterBallotEdited[smallestRep][0][smallestRep]);
					
								
					if((eliminatedRep.at(k) != 1) && (repToSeat.at(k) != 1)){
						voteTransfer1[smallestRep][1][k] = -(masterVoterBallotEdited[smallestRep][1][k]);
					
					} else{

						double extraVotes = voteTransfer1[smallestRep][1][k];
						double totalNextVote = vectorSum(masterVoterBallotEdited[smallestRep][2]);
						
						for (l = 0; l < voteTransfer1[i][j].size(); ++l){
							if((eliminatedRep.at(l) != 1) && (repToSeat.at(l) != 1)){
								voteTransfer1[smallestRep][2][l] = (masterVoterBallotEdited[smallestRep][2][l]/totalNextVote)*extraVotes;}		
						}
					}														
				}								
			}
			
			if((eliminatedRep.at(i) != 1) && (repToSeat.at(i) != 1)){
				voteTransfer1[i][0][i] += masterVoterBallotEdited[smallestRep][j][i];}
		}
		
		if(dialogueBool == 1){
			cout << endl;
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "\t\tCURRENT VOTE TRANSFER LOOP: " << (loopNum+1) << endl;
			cout << "-------------------------------------------------------------------------" << endl;
			
			for (i = 0; i < voteTransfer1.size(); ++i){
				
				cout <<"__________________________________________________________________________" << endl;
				cout << "\t\t";
				for (j = 0; j < repNames.size(); ++j){
					cout << repNames.at(j) << "\t";}
				cout << endl <<"__________________________________________________________________________" << endl;
			
				for (j = 0; j < voteTransfer1[i].size(); ++j){
					cout << (j+1) << " rank Vote:\t";
				
					for (k = 0; k < voteTransfer1 [i][j].size(); ++ k){	
						cout << setprecision(3) << voteTransfer1[i][j][k] << "\t";}
					cout << endl;
				}
				cout << endl;
			}
		}
		
		for(i = 0; i < eliminatedRep.size(); ++ i){
			if (vectorSum(eliminatedRep) == numEliminatedReps){
				
				if (eliminatedRep.at(i) == 0){
					repToSeat.at(i) = 1;
				} else{
					repToSeat.at(i) = 0;
				}
			}
		}
	
		if(dialogueBool == 1){
			cout << endl;
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "\tMASTER VOTER BALLOT WITH VOTES TRANSFERED LOOP: " << (loopNum+1) << endl;
			cout << "-------------------------------------------------------------------------" << endl;
		}
	
		for (i = 0; i < masterVoterBallotEdited.size(); ++i){
			if(dialogueBool == 1){	
				cout <<"__________________________________________________________________________" << endl;
				cout << "\t\t";
				for (j = 0; j < repNames.size(); ++j){
					cout << repNames.at(j) << "\t";}
				cout << endl <<"__________________________________________________________________________" << endl;
			}
			
			for (j = 0; j < voteTransfer1[i].size(); ++j){		
				if(dialogueBool == 1){				
					cout << (j+1) << " rank Vote:\t";}
					
				for (k = 0; k < masterVoterBallotEdited [i][j].size(); ++ k){
					
					masterVoterBallotEdited[i][j][k] = masterVoterBallotEdited[i][j][k] + voteTransfer1[i][j][k];
						
					if (vectorSum(masterVoterBallotEdited[i][0]) >= thresholdVotes){
						repToSeat.at(i) = 1;
					}
					if(dialogueBool == 1){
						cout << setprecision(3) <<  masterVoterBallotEdited[i][j][k] << "\t";}		
				}
				if(dialogueBool == 1){
					cout << endl;}
			}
			if(dialogueBool == 1){
				cout << endl;}
		}
				
		loopNum +=1;
	}while (vectorSum(repToSeat) <  numSeats);
	
	if(dialogueBool == 1){
		cout << endl;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "\t\tOVERALL ELIMINATED REPRESENTATIVES " << endl;
		cout << "-------------------------------------------------------------------------" << endl;
			
		cout << "The representatives that has been eliminated is: " << endl << "\t";
		for (i = 0; i < eliminatedRep.size(); ++i){
			if ( eliminatedRep.at(i) == 1 ){
				cout << repNames.at(i) << " ";}
		}
		cout << endl << endl;
	}
}

void voterResults(vector <double> repToSeat, vector <double> eliminateRep, vector <string> repNames){
	unsigned int i;
	
	cout << endl;
	cout << "=========================================================================" << endl;
	cout << "\t\tVOTING CALCULATIONS ARE COMPLETE" << endl;
	cout << "=========================================================================" << endl;	
	cout << "The voting calculations are now completed." << endl;
	cout << "The representatives that have a seat are: " << endl;
	
	for(i = 0; i < repToSeat.size(); ++i){
		
		if(eliminateRep.at(i) == 0){
			repToSeat.at(i) == 1;}
		
		if (repToSeat.at(i) == 1){
			cout << "\t" << repNames.at(i) << endl;}
	}
	
}

void voteCalculations( vector<vector<int> > voterBallots, int numVoters, vector<string> repNames, int numSeats, int numReps, double thresholdVotes, bool dialogueBool){
	
	unsigned int i;
	unsigned int j;
	unsigned int k;
	unsigned int l;

	vector <double> repToSeat(numReps);
	vector <double> eliminatedRep (numReps);
	
	vector <double> tempVector1(numReps);
	vector <double> tempVector1A(numReps);
	
	vector < vector <double> > tempVector2;
	vector < vector <double> > tempVector2A;

	
	vector < vector < vector <double> > > masterVoterBallot;	
	
	vector < vector < vector <double> > > masterVoterBallotEdited;
		
	vector < vector < vector <double> > > voteTransfer;	 /// used for the surplus votes
	vector < vector < vector <double> > > voteTransfer1; /// used for the eliminated reps

/**********************************************************************************

This giant for loop is to make the 3D Vector each section is for each representative,
the first row is how many voters ranked that Rep 1 as there first rank,
the second row is how many voters ranked Rep 1 as there first rank AND what the voters second option is 
and etcera etcera

Rep 1
1 - x x x x ...
2 - x x x x ...
3 - x x x x ...
4 - x x x x ...
5 - x x x x ...

Rep 2 
1 - x x x x ...
2 - x x x x ...
3 - x x x x ...
4 - x x x x ...
5 - x x x x ...

etc...

NOTE: vectorName[section][row][column]
NOTE: vectorName[row][column]
**********************************************************************************/

//this creates the 3D vector,
	for (i=0; i < numReps; ++i){
		tempVector2.clear();
		tempVector2A.clear();
			
		for (j = 1; j < numReps + 1; ++j){
			
			// sets the temporary vector to zero	
			for (k = 0; k < tempVector1.size(); ++k){
				tempVector1.at(k)=0;
				tempVector1A.at(k)=0;
			}
				
			// reading the mastor ballot, it converts it to how the citizens voted according to there 1st Ranking
			for (k = 0; k < voterBallots.size(); ++k) { 
				for (l = 0; l < voterBallots[k].size(); ++l) {
			
					if ((voterBallots[k][i] == 1) && (voterBallots[k][l] == j )){
						tempVector1.at(l) +=1;}
				}
			}
			tempVector2.push_back(tempVector1);	
			tempVector2A.push_back(tempVector1A);		
		}
		masterVoterBallot.push_back(tempVector2);
		masterVoterBallotEdited.push_back(tempVector2);	
		voteTransfer.push_back(tempVector2A);
		voteTransfer1.push_back(tempVector2A);
	}
	
//Displays the 3D vector;	

	if(dialogueBool == 1){
		cout << endl;
		cout << "=============================================================================================" << endl;
		cout << "\t\t\t\tMASTER VOTER BALLOT" << endl;
		cout << "=============================================================================================" << endl;
		cout << "This is the Master Voter Ballot, it is a ballot used to organized the voters by who they " << endl;
		cout << "voted as there 1st pick representative, then out of those voters who they voted for " << endl;
		cout << "second. Each column is still oraganized by each representative in order of how it was entered." << endl;
		cout << "---------------------------------------------------------------------------------------------" << endl;
	}
	
	for (i = 0; i < masterVoterBallot.size(); ++i){
		if(dialogueBool == 1){
			cout <<"__________________________________________________________________________" << endl;
			cout << "\t\t";
			for (j = 0; j < repNames.size(); ++j){
				cout << repNames.at(j) << "\t";
			}
			cout << endl <<"__________________________________________________________________________" << endl;
		}

		for (j = 0; j < masterVoterBallot[i].size(); ++j){
			if(dialogueBool == 1){
				cout << (j+1) << " rank Vote:\t";}
			
			for (k = 0; k < masterVoterBallot[i][j].size(); ++k){
			
				if(vectorSum(masterVoterBallot[i][0]) >= thresholdVotes){
					repToSeat.at(i) = 1;
				} else{
					repToSeat.at(i) = 0;
				}
				
			if(dialogueBool == 1){
				cout << masterVoterBallot[i][j][k] << "\t";}
				
			}
			if(dialogueBool == 1){
				cout << endl;}
		}
		if(dialogueBool == 1){
			cout << endl;}	
	}	
	
	//Sets the eliminated rep vector to 0 since none of them have been eliminated yet
	for (i = 0; i < eliminatedRep.size(); ++i){
		eliminatedRep.at(i) = 0;
	}
	
	// checks to see if any of the representatives has a surplus votes
	
	int surplusVote = 0;
	for (i = 0; i < masterVoterBallot.size(); ++i){
		if (vectorSum(masterVoterBallot[i][0]) > thresholdVotes){
			surplusVote = surplusVote + 1;}
	}
	
	if (surplusVote > 0){
		surplusVotes(masterVoterBallot, voteTransfer, repToSeat, repNames, thresholdVotes, dialogueBool);}
	
	
	//After running the surplus votes count, it creates an edited master voter ballot based off the changes		
	for (i = 0; i < masterVoterBallotEdited.size(); ++i){		
		for (j = 0; j < masterVoterBallotEdited[i].size(); ++j){
			for (k = 0; k < masterVoterBallotEdited[i][j].size(); ++k){
				masterVoterBallotEdited[i][j][k] = masterVoterBallot[i][j][k]+voteTransfer[i][j][k];}
		}
	}
		
	if (vectorSum(repToSeat) <  numSeats){
		eliminateRep(masterVoterBallot, masterVoterBallotEdited, voteTransfer1, repToSeat, eliminatedRep, numSeats, numReps, repNames, thresholdVotes, numVoters, dialogueBool);
	}

	voterResults(repToSeat, eliminatedRep, repNames);
		
}

int main (){

/**************************************************************************************************************

Section 1 - asks for the number of options and what the name for options are

***************************************************************************************************************/
    cout << endl << endl;
	cout << "==========================================================================================================" << endl; 
    cout << "\t\t\t\tSINGULAR TRANSFERABLE VOTE METHOD CALCULATOR" << endl;
	cout << "==========================================================================================================" << endl; 
	cout << "This program is created to simulate the Singular Transferale Vote (STV) voting method with at least 100 " << endl; 
	cout << "voters and three or more representatives. This voting system is designed to maximize voter happiness by " << endl;
	cout << "allowing voters to vote for more than one representative by using a ranking system." << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl; 
	
	vector < string > repNames; // will be the  columns of the vector of vectors, contains the names of the representatives
    string repName;
	
	int numReps = 0;
	int numSeats = 0;
	
    unsigned int i;
    
    bool firstValid = 0 ; // verifies the number of seats, representatives and the name of the representatives
	char userValid;

    while (firstValid == 0){
		do{
			string prompt1 = "How many representatives are running?('2','3'...)";
			numReps = userInputCheckGreaterThanZero(prompt1,numReps);
			        
	       	string prompt2 = "How many seats are avaliable?('2','3'...)";
	       	numSeats = userInputCheckGreaterThanZero(prompt2,numSeats);
	            
			if(numSeats > numReps){
				cout << "***********************************************************" << endl;
	           	cout << "Error: There are more seats than there are representatives." << endl;
	           	cout << "***********************************************************" << endl << endl;
	            	
			}else if(numSeats == numReps){
	           	cout << "***************************************************************************" << endl;
				cout << "Error: There are an equal amount of seats to the number of representatives." << endl;
	           	cout << "***************************************************************************" << endl << endl;
			}
			
			cout << "-------------------------------------------------" << endl;
			
		}while (numReps <= numSeats);
			        
        //resizes the vector for repNames to adjust for number of representatives running from previous answers
        repNames.resize(numReps);
        
        //Ask for user input on what the representatives names are
        for (i=0; i < repNames.size(); ++i){
        	string repName;
		    cout << "What is the name of representative " << (i+1) << "? \t";
        	cin >> repName;

        	repNames.at(i) = repName;
        	cout << endl;
		}
        
        //States the number of representatives, their names and the number of seats open, then ask for user verification
        cout << endl <<"----------------------------------------------------------------" << endl;
        cout << "There are " << numReps << " representatives running and " << numSeats << " seat(s) avaliable." << endl;
		cout << endl << "The representatives that are running are: " << endl;
        
        for (i = 0; i < repNames.size(); ++i){
            cout << "\t" <<repNames.at (i) << endl;
        }
		cout << endl;
		
		string userValidate = "Is the given information correct? (Y/N)";
		firstValid = isValidCheck(userValidate, userValid);
		        
    }
   
    bool knownNumberVoters ; /// known number of voters is 1; unknown number of voters is 0
    bool randomNumberVoters ; // generate random votes is 1; manual input votes is 0
    bool dialogueBool;
    vector <vector <int> > voterBallots;
    int numVoters = 0;
    
    bool redoBool = 1;
    int choice = 0;
   

    string numVotersPrompt = "Do you know the number of voters? (Y/N)";
    knownNumberVoters = isValidCheck(numVotersPrompt,userValid);
		
	if (knownNumberVoters ==1 ){
		
		string numVoterPrompt = "How many voters are there?";
		numVoters = userInputCheckGreaterThanZero(numVoterPrompt, numVoters);
		
		string randNumVotersPrompt = "Are the votes randomly generated votes? (Y/N)";
	    randomNumberVoters = isValidCheck(randNumVotersPrompt,userValid);
	    
	    if (randomNumberVoters == 0){
	    	choice = 0;
		}else{		
			choice = 1;}
		
	}else{
		choice = 3;}
		
	string dialoguePrompt = "Would you like to see the calcualtions? (Y/N) ";
	dialogueBool = isValidCheck(dialoguePrompt,userValid);
		
	do{
		if (choice == 0){
			voterBallots = manualVoterInputKnownNumVotes (repNames, numReps, numSeats, numVoters, dialogueBool);
		} else if (choice == 1 ){
			voterBallots = randVoterKnownNumVoters(repNames, numReps, numSeats, numVoters, dialogueBool);
		} else{
			voterBallots = manualVoterInputUnknownNumVotes (repNames, numReps, numSeats, numVoters, dialogueBool);
		}
		
		cout << endl;
		cout << "=============================================================================================" << endl;
		cout << "\t\t\t\tALL VOTER BALLOT" << endl;
		cout << "=============================================================================================" << endl;
		cout << "This is the collective of all of the voter's ballot, each row is one individual voter ballot" << endl;
		cout << "each column is a representative in order that was entered. The number represents the rank "<< endl;
		cout << "that a voter ranked that representative. If that ranking is a '0' then they did not want " << endl;
		cout << "their vote to go to that representative." << endl;
		cout << "---------------------------------------------------------------------------------------------" << endl;
		
		cout <<"__________________________________________________________________________" << endl;
		cout << "\t\t";
		for (i = 0; i < repNames.size(); ++i){
			cout << repNames.at(i) << "\t";
		}
		cout << endl <<"__________________________________________________________________________" << endl;
		
		for (int i = 0; i < voterBallots.size(); ++i) { 
			cout << "Voter " << (i+1) << ":\t";
			for (int j = 0; j < voterBallots[i].size(); ++j){
				cout << voterBallots[i][j] << "\t"; 	}		
			cout << endl; 
		}
		
		double thresholdVotes = (numVoters/(numSeats+1))+1;
		
		cout << endl << endl;
		
			cout << endl;
		cout << "=============================================================================================" << endl;
		cout << "\t\t\t\tVOTE CALCULATION SUMMARY" << endl;
		cout << "=============================================================================================" << endl;
		cout << "In this voting election, there was a total of " << numVoters << " voters that had a valid vote in this campaign." << endl;
		cout << "The voters had " << numReps << " representatives to choose from and there were " << numSeats << " seats available." << endl;
		cout << "In order for a representative to secure a seat they needed at least " << thresholdVotes << " votes." << endl;
		cout << "---------------------------------------------------------------------------------------------" << endl;
		
		voteCalculations(voterBallots, numVoters, repNames, numSeats, numReps, thresholdVotes, dialogueBool);
		
		cout << endl;
		cout  << "-----------------------------------------" << endl;
		string userValidate = "Would you like to rerun the votes? (Y/N)";
		redoBool = isValidCheck(userValidate, userValid);
		
	}while (redoBool == 1);

    return 0; 
} 

