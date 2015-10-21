#include "gameUtil.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

int GameUtil::compute(Square* square, Player* player){ //how far can i go?
  // TODO: Part 1 debug
  double chi = player->getChi();
  double weight = player->getWeight();
  double teleporterEnergy = square->getTeleporterEnergy();
  double cannonPowder = square->getCannonPowder();

  double teleporterCompute = 0;
  for(int i = 0; i <= floor(chi); i=i+1){ //this for loop seems off
    teleporterCompute += sqrt(i * chi  * teleporterEnergy);
  }
  teleporterCompute *= (1.0/(1.0 + chi));

  double cannonCompute = (pow( (pow((int)cannonPowder,1.7) / pow(weight,1.5)),2))/9.8 ; //this is jazzed up !!!should be good now
  std::cout<<"This is the cannon value "<< cannonCompute<<std::endl;
  std::cout<<"This is the teleporter value "<< teleporterCompute<<std::endl;
  
 
  //std::cout<<"this is the max the player can move "<< std::max(cannonCompute , teleporterCompute)<<std::endl;
 // if(cannonCompute == teleporterCompute){return cannonCompute;}
  //else{return std::max(cannonCompute , teleporterCompute);}
   return std::max(cannonCompute > teleporterCompute ? cannonCompute : teleporterCompute, 1.0);
}

bool GameUtil::isValidPath(std::vector<int>& path, Player* player, Game* game){
  // TODO:Part 2
   
  std::vector<Square*> board = game->getBoard();
  int boardSize = board.size();
  int pathSize = path.size();
 
  std::cout<<"this is the size of the board "<<boardSize<<std::endl;
  std::cout<<"this is the path front " <<path.front()<<std::endl;
  if(path.front() != 0){
	  std::cout<<"the first value in the path is not zero!!!!"<<std::endl;
	  return false;}
  
  std::cout<<"this is the first value in the path " <<path.front()<<std::endl;
  std::cout<<"this is the last  value in the path " <<path.back()<<std::endl;
  std::cout<<"this is the size of the path vector " <<path.size()<<std::endl;
  std::cout<<"this si the path back "<<path.back()<<std::endl;
  if(path.back() != (boardSize-1)){
	  std::cout<<"the last value in the path doesnt end on the board itself!!!!"<<std::endl;
	  return false;}
 
	int squareIndex = 0;  
 for( int i=0;i <pathSize-2;i++){
	 int pathValue = path[i];
	 int nextPath = path[i+1];
	 if(nextPath < pathValue){return false;}
	double squareComp = compute(board[squareIndex],player);
  	//int squareComp = round(squareCompd);
	if(nextPath > squareIndex + squareComp){
		// std::cout<<"this step "<< step <<" is too small for "<<path[i+1]<<std::endl; 
		 return false;}
  	squareIndex = nextPath;
 }  
  return true;
 }
 

int GameUtil::shortestPathDistance(Game* game, Player* player){
  // TODO: Part 3
   
  std::vector<Square*> board = game->getBoard();
  int boardlength = board.size();
  int location = 0;
  int pathCounter = 0;
  int nextLocation = 0;
	
   while(location < boardlength -1){
	 int furthestAble = 0;
	 if(location + compute(board[location],player)>=boardlength - 1){return pathCounter +1;}
	 for(int i = 1; i <= compute(board[location],player); i++){//check each possible spot
		
		  if(i + location  >=  boardlength -1){
	//	  std::cout<<" this location could reach out of the board"<<std::endl;
			  return pathCounter + 1;}
		 	
		int check = i + compute(board[location + i],player) + location;  //This is the segfault
		std::cout<<"The check value is "<< check <<std::endl;
		if(check > furthestAble){
				furthestAble = check; 
				nextLocation = location+ i;
			}
	
	  }
	  std::cout<<"the old location is "<< location<<std::endl;
	  std::cout<<"the next location is "<<nextLocation<<std::endl;
	location = nextLocation;//next spot to test from, furthest reaching spot 
	pathCounter +=1;
  }	
   std::cout<<"we made it to the end"<<std::endl;
	return pathCounter;
}
