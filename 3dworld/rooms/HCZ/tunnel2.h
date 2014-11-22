#ifndef TUNNEL2_ROOM_INCLUDED
#define TUNNEL2_ROOM_INCLUDED

class tunnel2 : public room {
	private:
		static RMesh* baseRMesh;
		tunnel2() {};
	public:
		virtual roomTypes getType() const { return roomTypes::ROOM2; }
		virtual void updateEvent() { return; }
		virtual const std::vector<irr::video::SLight>& getPointLights();
		static void setBase(RMesh* inRme);
		static tunnel2* createNew(irr::core::vector3df inPosition,char inAngle);
};

#endif
