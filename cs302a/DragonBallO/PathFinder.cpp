#include "PathFinder.h"
#include "Grid.h"

#define ADJ_WEIGHT 10
#define DIAG_WEIGHT 14

extern Grid gGrid;

PathFinder::PathFinder()
{
}


PathFinder::~PathFinder()
{
}

void PathFinder::ClearPath() {
	mPath.clear();
}


//1.) Initialize PathFinder (add start position & destination position)

void PathFinder::StartSearching(Int2 start, Int2 dest) {

	vector<Node*> openList;
	vector<Node*> closedList;

	ClearPath();

	//2.) Create first Cell for start position, and add it to OpenList
	Node node(start);
	openList.push_back(&node);
	
	// 3.) While OpenList is Not empty...
	while (openList.size() > 0) {
		// a.) Find the Node with the smallest f value (which i will refer to as the
		auto parent = openList[0];
		int parentNodeIndex = 0;

		for (int i = 0; i < openList.size(); ++i) {
			if (parent->mF > openList[i]->mF) {
				parent = openList[i];
				parentNodeIndex = i;
			}
		}

		openList.erase(openList.begin() + parentNodeIndex);

		// b.) Create 8 new Nodes from the neighbors surrounding "parentNode", calculate g, and
		Node nodes[8] = {
			Node(parent,parent->mG + ADJ_WEIGHT,parent->mPos + Int2(1,0)),
			Node(parent,parent->mG + DIAG_WEIGHT,parent->mPos + Int2(1,1)),
			Node(parent,parent->mG + DIAG_WEIGHT,parent->mPos + Int2(1,-1)),
			Node(parent,parent->mG + ADJ_WEIGHT,parent->mPos + Int2(-1,0)),
			Node(parent,parent->mG + DIAG_WEIGHT,parent->mPos + Int2(-1,1)),
			Node(parent,parent->mG + DIAG_WEIGHT,parent->mPos + Int2(-1,-1)),
			Node(parent,parent->mG + ADJ_WEIGHT,parent->mPos + Int2(0,1)),
			Node(parent,parent->mG + ADJ_WEIGHT,parent->mPos + Int2(0,-1))
		};

		for (auto childNode : nodes) {
			
			// i.) If Node is NOT valid (blocked, etc.) continue....
			if (gGrid.IsValid(childNode.mPos)) {
				continue;
			}
			
			// ii.) If Node in ClosedList has same position as "childNode" continue...
                //      closed list are nodes previously searched. so we dont search the same node over again.
                //      m_closedList.Find is a predicate and the stuff in () is a lamda
                //      n => is the parameter and then n.x == && n.y == is the "if statement"
			bool found = false;
			for (auto node : closedList) {
				if (childNode.mPos == node->mPos) {
					found = true;
					break;
				}
			}
			if (found) {
				continue;
			}
			
			// iii.) Calculate h. If goal has been reached (h value is zero),
            //      stop search and set PathNode. Else, calculate f....
            //      this code ends the search ("i found my paths destination")
			childNode.mH = (Abs(dest.x - childNode.mPos.x) +
				Abs(dest.y - childNode.mPos.y)) * ADJ_WEIGHT;
		
			// reached destination...
			if (childNode.mH == 0) {
				//TODO: ClearSearch();
				//GeneratePath(childNode);
				
				mPath.push_back(childNode);
				Node *parent = childNode.mParent;
				
				while (parent != nullptr) {
					mPath.push_back(*parent);
					parent = parent->mParent;
				}
				
				reverse(mPath.begin(), mPath.end());

				//Cleans up stuff
				for (auto node : openList) delete node;
				for (auto node : closedList) delete node;
				
				
				
				
				return;
			}
			// calculate F value
			childNode.mF = childNode.mH + childNode.mG;

			// iv.) if node in openlist has same position as "childnode", but has
			// lower f value, assign has lower f value, continue
			found = false;
			for (auto node : openList) {
				if (childNode.mPos == node->mPos) {
					if (childNode.mF < node->mF) {
						node->mParent = childNode.mParent;
						node->mF = childNode.mF;
					}
					found = true;
					break;
				}
			}
			Node *childNodePtr = new Node(childNode);
			openList.push_back(childNodePtr);
		}
	}

	//Clear search...
	for (auto node : openList) delete node;
	for (auto node : closedList) delete node;
}