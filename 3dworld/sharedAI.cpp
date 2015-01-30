#include "3dworld.h"
#include "player.h"
#include "rooms/rmesh.h"
#include "rooms/room.h"

#include <cmath>

void world::getRoomList(const irr::core::vector2di &startPos,const irr::core::vector2di &endPos,std::vector<irr::core::vector2di> &roomPath) {

	if (roomArray[startPos.X][startPos.Y]==nullptr) { std::cout<<"err1\n"; return; }
	if (roomArray[endPos.X][endPos.Y]==nullptr) { std::cout<<"err2\n"; return; }
	if (startPos.X<0) { std::cout<<"err3\n"; return; }
	if (startPos.X>=20) { std::cout<<"err4\n"; return; }
	if (startPos.Y<0) { std::cout<<"err5\n"; return; }
	if (startPos.Y>=20) { std::cout<<"err6\n"; return; }
	if (endPos.X<0) { std::cout<<"err7\n"; return; }
	if (endPos.X>=20) { std::cout<<"err8\n"; return; }
	if (endPos.Y<0) { std::cout<<"err9\n"; return; }
	if (endPos.Y>=20) { std::cout<<"err10\n"; return; }
	roomPath.clear();

    irr::core::vector2di sPos = startPos;

	unsigned char startDir = 4;
	unsigned char startDist = 0;

	if (roomArray[startPos.X][startPos.Y]->getType()==roomTypes::ROOM1 || roomArray[startPos.X][startPos.Y]->getType()==roomTypes::ROOM2) {
		unsigned char dist1 = 1;
		while (roomArray[startPos.X+dist1][startPos.Y]!=nullptr && startPos.X+dist1<20) {
			if (roomArray[startPos.X+dist1][startPos.Y]->getType()!=roomTypes::ROOM1 && roomArray[startPos.X+dist1][startPos.Y]->getType()!=roomTypes::ROOM2) {
				startDir = 0;
				startDist = dist1;
				break;
			}
			dist1++;
		}
		dist1 = 1;
		while (roomArray[startPos.X][startPos.Y-dist1]!=nullptr && startPos.Y-dist1>=0) {
			if (roomArray[startPos.X][startPos.Y-dist1]->getType()!=roomTypes::ROOM1 && roomArray[startPos.X][startPos.Y-dist1]->getType()!=roomTypes::ROOM2) {
				if (startDist>dist1 || startDist==0) {
					startDir = 1;
					startDist = dist1;
				}
				break;
			}
			dist1++;
		}
		dist1 = 1;
		while (roomArray[startPos.X-dist1][startPos.Y]!=nullptr && startPos.X-dist1>=0) {
			if (roomArray[startPos.X-dist1][startPos.Y]->getType()!=roomTypes::ROOM1 && roomArray[startPos.X-dist1][startPos.Y]->getType()!=roomTypes::ROOM2) {
				if (startDist>dist1 || startDist==0) {
					startDir = 2;
					startDist = dist1;
				}
				break;
			}
			dist1++;
		}
		dist1 = 1;
		while (roomArray[startPos.X][startPos.Y+dist1]!=nullptr && startPos.Y+dist1<20) {
			if (roomArray[startPos.X][startPos.Y+dist1]->getType()!=roomTypes::ROOM1 && roomArray[startPos.X][startPos.Y+dist1]->getType()!=roomTypes::ROOM2) {
				if (startDist>dist1 || startDist==0) {
					startDir = 3;
					startDist = dist1;
				}
				break;
			}
			dist1++;
		}
		switch (startDir) {
            case 0:
                sPos.X+=startDist;
            break;
            case 1:
                sPos.Y-=startDist;
            break;
            case 2:
                sPos.X-=startDist;
            break;
            case 3:
                sPos.Y+=startDist;
            break;
            default:
                //return;
            break;
		}
	}

	tempPathList* testList = new tempPathList;
    testList->x = sPos.X;
    testList->y = sPos.Y;
    if (roomArray[sPos.X][sPos.Y]->getType()==roomTypes::ROOM1 || roomArray[sPos.X][sPos.Y]->getType()==roomTypes::ROOM2) {
        //std::cout<<"error at start\n";
    }
    testList->prev = nullptr;
    testList->next = nullptr;

    //detect if the first tempPathList should be removed
    switch (startDir) {
        case 0:
            if (testList->next!=nullptr) {
                if (testList->next->x < testList->x) {
                    tempPathList* tempList = testList;
                    testList = testList->next;
                    delete tempList;
                }
            }
        break;
        case 1:
            if (testList->next!=nullptr) {
                if (testList->next->y > testList->y) {
                    tempPathList* tempList = testList;
                    testList = testList->next;
                    delete tempList;
                }
            }
        break;
        case 2:
            if (testList->next!=nullptr) {
                if (testList->next->x > testList->x) {
                    tempPathList* tempList = testList;
                    testList = testList->next;
                    delete tempList;
                }
            }
        break;
        case 3:
            if (testList->next!=nullptr) {
                if (testList->next->y < testList->y) {
                    tempPathList* tempList = testList;
                    testList = testList->next;
                    delete tempList;
                }
            }
        break;
    }

    short result = stepPath(endPos,*testList);
    if (result>=0) {
        while (testList!=nullptr) {
            roomPath.push_back(irr::core::vector2di(testList->x,testList->y));
            tempPathList* tempList = testList;
            testList = testList->next;
            delete tempList;
        }
    }
}

short world::stepPath(const irr::core::vector2di &endPos,tempPathList &roomPath,int depth) {
    ////std::cout<<"asdasdasda"<<depth<<"\n";
	short minDist = -1;

    unsigned char x=roomPath.x;
    unsigned char y=roomPath.y;

    if (roomArray[x][y]->getType()==roomTypes::ROOM1 || roomArray[x][y]->getType()==roomTypes::ROOM2) {
        //std::cout<<"something is wrong with this\n";
    }

    //check if endPos can be reached directly from (x,y)
	if (x==endPos.X) {
        //std::cout<<"testX\n";
        if (y-endPos.Y==0) {
            return 0;
        } else if (y-endPos.Y<0) {
            for (unsigned short iy=y;iy<=endPos.Y;iy++) {
                if (roomArray[x][iy]==nullptr) { break; }
                if (iy==endPos.Y) { return endPos.Y-y; }
            }
            //if (roomArray[x][y]->getLinkedTurnDist(3)>=endPos.Y-y && roomArray[x][y]->getLinkedTurnDist(1)>0) { //std::cout<<"www\n"; return endPos.Y-y; }
        } else /* if (y-endPos.Y>0) */ {
            for (unsigned short iy=endPos.Y;iy<=y;iy++) {
                if (roomArray[x][iy]==nullptr) { break; }
                if (iy==y) { return y-endPos.Y; }
            }
            //if (roomArray[x][y]->getLinkedTurnDist(1)>=y-endPos.Y && roomArray[x][y]->getLinkedTurnDist(3)>0) { //std::cout<<"sss\n"; return y-endPos.Y; }
        }
	} else if (y==endPos.Y) {
        //std::cout<<"testY\n";
        if (x-endPos.X==0) {
            return 0;
        } else if (x-endPos.X<0) {
            for (unsigned short ix=x;ix<=endPos.X;ix++) {
                if (roomArray[ix][y]==nullptr) { break; }
                if (ix==endPos.X) { return endPos.X-x; }
            }
            //if (roomArray[x][y]->getLinkedTurnDist(0)>=endPos.X-x && roomArray[x][y]->getLinkedTurnDist(2)>0) { //std::cout<<"aaa\n"; return endPos.X-x; }
        } else /* if (x-endPos.X>0) */ {
            for (unsigned short ix=endPos.X;ix<=x;ix++) {
                if (roomArray[ix][y]==nullptr) { break; }
                if (ix==x) { return x-endPos.X; }
            }
            //if (roomArray[x][y]->getLinkedTurnDist(2)>=x-endPos.X && roomArray[x][y]->getLinkedTurnDist(0)>0) { //std::cout<<"ddd\n"; return x-endPos.X; }
        }
	}

    //check if visible "turns" can see endPos
    tempPathList* newList = nullptr;
    tempPathList* testList = nullptr;

	short rDist = roomArray[x][y]->getLinkedTurnDist(0);
	if (rDist>0) {
		bool isntInList = true;
        tempPathList* tempList = &roomPath;
        while (tempList!=nullptr) {
            if (tempList->x==x+rDist && tempList->y==y) {
                isntInList = false;
                break;
            }
            tempList=tempList->prev;
        }
        if (isntInList) {
            tempList = roomPath.next;
            while (tempList!=nullptr) {
                if (tempList->x==x+rDist && tempList->y==y) {
                    isntInList = false;
                    break;
                }
                tempList=tempList->next;
            }
        }
		if (isntInList) {
            testList = new tempPathList;
            testList->x = x+rDist;
            testList->y = y;
            testList->prev = &roomPath;
            short dist = stepPath(endPos,*testList,depth+1);
            if ((dist+rDist<minDist || minDist<=0) && dist>=0) {
                minDist = dist+rDist;
                while (newList!=nullptr) {
                    tempList = newList;
                    newList = newList->next;
                    delete tempList;
                }
                newList = testList;
            } else {
                while (testList!=nullptr) {
                    tempList = testList;
                    testList = testList->next;
                    delete tempList;
                }
            }
        }
	}
	rDist = roomArray[x][y]->getLinkedTurnDist(1);
	if (rDist>0) {
		bool isntInList = true;
        tempPathList* tempList = &roomPath;
        while (tempList!=nullptr) {
            if (tempList->x==x && tempList->y==y-rDist) {
                isntInList = false;
                break;
            }
            tempList=tempList->prev;
        }
        if (isntInList) {
            tempList = roomPath.next;
            while (tempList!=nullptr) {
                if (tempList->x==x && tempList->y==y-rDist) {
                    isntInList = false;
                    break;
                }
                tempList=tempList->next;
            }
        }
		if (isntInList) {
            testList = new tempPathList;
            testList->x = x;
            testList->y = y-rDist;
            testList->prev = &roomPath;
            short dist = stepPath(endPos,*testList,depth+1);
            if ((dist+rDist<minDist || minDist<=0) && dist>=0) {
                minDist = dist+rDist;
                while (newList!=nullptr) {
                    tempList = newList;
                    newList = newList->next;
                    delete tempList;
                }
                newList = testList;
            } else {
                while (testList!=nullptr) {
                    tempList = testList;
                    testList = testList->next;
                    delete tempList;
                }
            }
        }
	}
	rDist = roomArray[x][y]->getLinkedTurnDist(2);
	if (rDist>0) {
		bool isntInList = true;
        tempPathList* tempList = &roomPath;
        while (tempList!=nullptr) {
            if (tempList->x==x-rDist && tempList->y==y) {
                isntInList = false;
                break;
            }
            tempList=tempList->prev;
        }
        if (isntInList) {
            tempList = roomPath.next;
            while (tempList!=nullptr) {
                if (tempList->x==x-rDist && tempList->y==y) {
                    isntInList = false;
                    break;
                }
                tempList=tempList->next;
            }
        }
		if (isntInList) {
            testList = new tempPathList;
            testList->x = x-rDist;
            testList->y = y;
            testList->prev = &roomPath;
            short dist = stepPath(endPos,*testList,depth+1);
            if ((dist+rDist<minDist || minDist<=0) && dist>=0) {
                minDist = dist+rDist;
                while (newList!=nullptr) {
                    tempList = newList;
                    newList = newList->next;
                    delete tempList;
                }
                newList = testList;
            } else {
                while (testList!=nullptr) {
                    tempList = testList;
                    testList = testList->next;
                    delete tempList;
                }
            }
        }
	}
	rDist = roomArray[x][y]->getLinkedTurnDist(3);
	if (rDist>0) {
		bool isntInList = true;
        tempPathList* tempList = &roomPath;
        while (tempList!=nullptr) {
            if (tempList->x==x && tempList->y==y+rDist) {
                isntInList = false;
                break;
            }
            tempList=tempList->prev;
        }
        if (isntInList) {
            tempList = roomPath.next;
            while (tempList!=nullptr) {
                if (tempList->x==x && tempList->y==y+rDist) {
                    isntInList = false;
                    break;
                }
                tempList=tempList->next;
            }
        }
		if (isntInList) {
            testList = new tempPathList;
            testList->x = x;
            testList->y = y+rDist;
            testList->prev = &roomPath;
            short dist = stepPath(endPos,*testList,depth+1);
            if ((dist+rDist<minDist || minDist<=0) && dist>=0) {
                minDist = dist+rDist;
                while (newList!=nullptr) {
                    tempList = newList;
                    newList = newList->next;
                    delete tempList;
                }
                newList = testList;
            } else {
                while (testList!=nullptr) {
                    tempList = testList;
                    testList = testList->next;
                    delete tempList;
                }
            }
        }
	}

    if (newList!=nullptr) { roomPath.next = newList; }

    return minDist;
}

void world::getRoomListToPlayer(const irr::core::vector2di &startPos,std::vector<irr::core::vector2di> &roomPath) {
    std::cout<<"::::: "<<mainPlayer->getPosition().X<<"\n";
    getRoomList(startPos,irr::core::vector2di(coordToRoomGrid(mainPlayer->getPosition().X),coordToRoomGrid(mainPlayer->getPosition().Z)),roomPath);
}

void room::findWPPath(RMesh* rme,irr::core::vector3df startPos,irr::core::vector3df destPos,std::vector<irr::core::vector3df> &posList) {
    bool found1,found2;
    found1=found2=false;
    node->updateAbsolutePosition();
    startPos-=node->getAbsolutePosition();
    destPos-=node->getAbsolutePosition();
    irr::core::matrix4 invRotMatrix;
    invRotMatrix.setRotationDegrees(irr::core::vector3df(0.f,-angle*90.f,0.f));
    invRotMatrix.transformVect(startPos);
    invRotMatrix.transformVect(destPos);
    float found1dist,found2dist;
    unsigned int found1index,found2index;
    for (unsigned int i=0;i<rme->waypoints.size();i++) {
        if (!found1 || found1dist>startPos.getDistanceFromSQ(rme->waypoints[i]->position)) {
            found1dist=startPos.getDistanceFromSQ(rme->waypoints[i]->position);
            found1=true;
            found1index = i;
        }
        if (!found2 || found2dist>destPos.getDistanceFromSQ(rme->waypoints[i]->position)) {
            found2dist=destPos.getDistanceFromSQ(rme->waypoints[i]->position);
            found2=true;
            found2index = i;
        }
    }
    if (found1&&found2) {
        tempWPPathList* startPathList = new tempWPPathList;
        startPathList->prev = nullptr;
        startPathList->next = nullptr;
        startPathList->index = found1index;
        short result = wpPathStep(rme,found2index,*startPathList);
        if (result>=0) {
            while (startPathList!=nullptr) {
                irr::core::vector3df pushPos = rme->waypoints[startPathList->index]->position;
                rotMatrix.transformVect(pushPos);
                node->updateAbsolutePosition();
                pushPos+=node->getAbsolutePosition();
                posList.push_back(pushPos);
                //std::cout<<"asdasdasd "<<pushPos.Y<<"\n";
                tempWPPathList* tempList = startPathList;
                startPathList = startPathList->next;
                delete tempList;
                std::cout<<"spl ::::: "<<posList.size()<<" "<<result<<"\n";
            }
        } else {
            std::cout<<"waypoint pathfinding failed ("<<found1index<<","<<found2index<<";"<<rme->waypoints.size()<<") \n";
            if (rme->waypoints.size()==2) {
                std::cout<<"______ "<<rme->waypoints[0]->position.X<<","<<rme->waypoints[0]->position.Y<<","<<rme->waypoints[0]->position.Z<<"\n";
                std::cout<<"______ "<<rme->waypoints[1]->position.X<<","<<rme->waypoints[1]->position.Y<<","<<rme->waypoints[1]->position.Z<<"\n";
            }
            while (startPathList!=nullptr) {
                tempWPPathList* tempList = startPathList;
                startPathList = startPathList->next;
                delete tempList;
            }
        }
    }
}

short room::wpPathStep(RMesh* rme,unsigned char destWP,tempWPPathList &currWP) {
    RMesh::waypoint* wp = rme->waypoints[currWP.index];
    RMesh::waypoint* dwp = rme->waypoints[destWP];
    if (wp==dwp) { std::cout<<"wppathstep returned 0\n"; return 0; }

    tempWPPathList* tempList = nullptr;
    tempWPPathList* bestList = nullptr;

    for (int i=0;i<20;i++) {
        if (wp->connected[i]==dwp) {
            unsigned int j=0;
            for (j=0;j<rme->waypoints.size();j++) {
                if (rme->waypoints[j]==dwp) {
                    break;
                }
            }
            tempList = new tempWPPathList;
            tempList->prev = &currWP;
            tempList->next = nullptr;
            tempList->index = j;
            currWP.next = tempList;
            return 1;
        }
    }
    short bestListDist = -1;
    for (int i=0;i<20;i++) {
        RMesh::waypoint* awp = wp->connected[i];
        if (awp==nullptr) { continue; }
        unsigned int j=0;
        for (j=0;j<rme->waypoints.size();j++) {
            if (rme->waypoints[j]==awp) {
                break;
            }
        }
        tempWPPathList* testList = currWP.prev;
        bool isInList = false;
        while (testList!=nullptr) {
            if (testList->index==j) { isInList=true; break; }
            testList = testList->prev;
        }
        if (!isInList) {
            if (tempList!=nullptr) { delete tempList; tempList=nullptr; }
            tempList = new tempWPPathList;
            tempList->prev = &currWP;
            tempList->next = nullptr;
            tempList->index = j;
            short currDist = wpPathStep(rme,destWP,*tempList);
            if (currDist>=0) {
                if (bestList==nullptr) {
                    bestList=tempList; tempList=nullptr;
                    bestListDist = currDist;
                } else if (currDist<bestListDist) {
                    tempWPPathList* rmvList = bestList;
                    while (bestList!=nullptr) {
                        bestList = rmvList->next;
                        delete rmvList;
                        rmvList = bestList;
                    }
                    bestList=tempList; tempList=nullptr;
                    bestListDist = currDist;
                } else {
                    tempWPPathList* rmvList = tempList;
                    while (tempList!=nullptr) {
                        tempList = rmvList->next;
                        delete rmvList;
                        rmvList = tempList;
                    }
                    tempList = nullptr;
                }
            }
        }
    }
    if (bestList!=nullptr) {
        currWP.next = bestList;
        return bestListDist+1;
    }
    return -1;
}

void world::npcPathFind(const irr::core::vector3df &startPos,const irr::core::vector3df &endPos,const irr::core::vector2di &roomPos,std::vector<irr::core::vector3df> &posList) {
    if (roomPos.X<0) { std::cout<<"err3\n"; return; }
	if (roomPos.X>=20) { std::cout<<"err4\n"; return; }
	if (roomPos.Y<0) { std::cout<<"err5\n"; return; }
	if (roomPos.Y>=20) { std::cout<<"err6\n"; return; }
    if (roomArray[roomPos.X][roomPos.Y]==nullptr) { std::cout<<"error with npcpathfind: room is null\n"; return; }
    marked = roomPos;
    roomArray[roomPos.X][roomPos.Y]->findWPPath(startPos,endPos,posList);
}
