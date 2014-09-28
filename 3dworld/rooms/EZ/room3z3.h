#ifndef ROOM3Z3_ROOM_INCLUDED
#define ROOM3Z3_ROOM_INCLUDED

class room3z3 : public room {
	private:
		static irr::scene::IMeshSceneNode* baseNode;
		static RMesh* baseRMesh;
		room3z3() {};
	public:
		virtual roomTypes getType() { return roomTypes::ROOM3; }
		virtual void updateEvent() { return; }
		virtual const std::vector<irr::video::SLight>& getPointLights();
		static void setBase(irr::scene::IMeshSceneNode* inNode,RMesh* inRme);
		static room3z3* createNew(irr::core::vector3df inPosition,char inAngle);
};

#endif
