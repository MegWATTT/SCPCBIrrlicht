#include "itemEyedrops.h"

irr::scene::IMeshSceneNode* itemEyedrops::baseNode = nullptr;
btConvexHullShape* itemEyedrops::shape = nullptr;
irr::core::vector3df itemEyedrops::offset = irr::core::vector3df(0,0,0);
//dynRegister* itemEyedrops::dynamics = nullptr;

itemEyedrops::itemEyedrops() {}

void itemEyedrops::setMeshNode(irr::scene::IMeshSceneNode* &node) {
    if (itemEyedrops::baseNode == nullptr) {
        itemEyedrops::baseNode = node;
        node->setVisible(false);
    }
    node = nullptr;
}

itemEyedrops* itemEyedrops::createItemEyedrops() {
    if (itemEyedrops::baseNode == nullptr) return nullptr;

    if (itemEyedrops::shape == nullptr) {

        //get the mesh
        irr::scene::IMesh* irrMesh = itemEyedrops::baseNode->getMesh();

        //generate the collision shape
        irr::core::vector3df scaling = itemEyedrops::baseNode->getScale();//irr::core::vector3df(scale,scale,scale);
        irr::u32 i,k,numVertices,precLoss;
        btConvexHullShape* dynShape = new btConvexHullShape();

        float mx,Mx,my,My,mz,Mz;
        Mx = My = Mz = -INFINITY;
        mx = my = mz = INFINITY;

        irr::u32 bufferCount = irrMesh->getMeshBufferCount();
        for (i=0; i<bufferCount; i++) //get mesh boundaries
        {
            irr::scene::IMeshBuffer* mb=irrMesh->getMeshBuffer(i);
            if(mb->getVertexType()==irr::video::EVT_STANDARD)
            {
                irr::video::S3DVertex* mb_vertices=(irr::video::S3DVertex*)mb->getVertices();
                //mb_indices = mb->getIndices();
                numVertices = mb->getVertexCount();

                precLoss = 1;

                while (numVertices/precLoss>250) {
                    precLoss++;
                }

                for (k=0;k<numVertices;k+=precLoss) {
                    irr::core::vector3df irrPos2 = mb_vertices[k].Pos;

                    mx = std::min(mx,irrPos2.X * scaling.X);
                    Mx = std::max(Mx,irrPos2.X * scaling.X);
                    my = std::min(my,irrPos2.Y * scaling.Y);
                    My = std::max(My,irrPos2.Y * scaling.Y);
                    mz = std::min(mz,irrPos2.Z * scaling.Z);
                    Mz = std::max(Mz,irrPos2.Z * scaling.Z);
                }
            }
            else if(mb->getVertexType()==irr::video::EVT_2TCOORDS)
            {
                irr::video::S3DVertex2TCoords* mb_vertices=(irr::video::S3DVertex2TCoords*)mb->getVertices();
                numVertices = mb->getVertexCount();

                precLoss = 1;

                while (numVertices/precLoss>250) {
                    precLoss++;
                }

                for (k=0;k<numVertices;k+=precLoss) {
                    irr::core::vector3df irrPos2 = mb_vertices[k].Pos;

                    mx = std::min(mx,irrPos2.X * scaling.X);
                    Mx = std::max(Mx,irrPos2.X * scaling.X);
                    my = std::min(my,irrPos2.Y * scaling.Y);
                    My = std::max(My,irrPos2.Y * scaling.Y);
                    mz = std::min(mz,irrPos2.Z * scaling.Z);
                    Mz = std::max(Mz,irrPos2.Z * scaling.Z);
                }
            }
            else if(mb->getVertexType()==irr::video::EVT_TANGENTS)
            {
                irr::video::S3DVertexTangents* mb_vertices=(irr::video::S3DVertexTangents*)mb->getVertices();
                numVertices = mb->getVertexCount();

                precLoss = 1;

                while (numVertices/precLoss>250) {
                    precLoss++;
                }

                for (k=0;k<numVertices;k+=precLoss) {
                    irr::core::vector3df irrPos2 = mb_vertices[k].Pos;

                    mx = std::min(mx,irrPos2.X * scaling.X);
                    Mx = std::max(Mx,irrPos2.X * scaling.X);
                    my = std::min(my,irrPos2.Y * scaling.Y);
                    My = std::max(My,irrPos2.Y * scaling.Y);
                    mz = std::min(mz,irrPos2.Z * scaling.Z);
                    Mz = std::max(Mz,irrPos2.Z * scaling.Z);
                }
            }
        }

        itemEyedrops::offset.X = (mx+Mx)/2.f;
        itemEyedrops::offset.Y = (my+My)/2.f;
        itemEyedrops::offset.Z = (mz+Mz)/2.f;

        //float ccdThreshold = std::min(Mx-mx,std::min(My-my,Mz-mz));

        for (i=0; i<bufferCount; i++) //set offset to vertices
        {
            irr::scene::IMeshBuffer* mb=irrMesh->getMeshBuffer(i);
            if(mb->getVertexType()==irr::video::EVT_STANDARD)
            {
                irr::video::S3DVertex* mb_vertices=(irr::video::S3DVertex*)mb->getVertices();
                numVertices = mb->getVertexCount();

                precLoss = 1;

                while (numVertices/precLoss>250) {
                    precLoss++;
                }

                for (k=0;k<numVertices;k+=precLoss) {
                    irr::core::vector3df irrPos2 = mb_vertices[k].Pos;

                    btVector3 btPos2((irrPos2.X * scaling.X)-itemEyedrops::offset.X, (irrPos2.Y * scaling.Y)-itemEyedrops::offset.Y, (irrPos2.Z * scaling.Z)-itemEyedrops::offset.Z);
                    dynShape->addPoint(btPos2);
                }
            }
            else if(mb->getVertexType()==irr::video::EVT_2TCOORDS)
            {
                irr::video::S3DVertex2TCoords* mb_vertices=(irr::video::S3DVertex2TCoords*)mb->getVertices();
                numVertices = mb->getVertexCount();

                precLoss = 1;

                while (numVertices/precLoss>250) {
                    precLoss++;
                }

                for (k=0;k<numVertices;k+=precLoss) {
                    irr::core::vector3df irrPos2 = mb_vertices[k].Pos;

                    btVector3 btPos2((irrPos2.X * scaling.X)-itemEyedrops::offset.X, (irrPos2.Y * scaling.Y)-itemEyedrops::offset.Y, (irrPos2.Z * scaling.Z)-itemEyedrops::offset.Z);
                    dynShape->addPoint(btPos2);
                }
            }
            else if(mb->getVertexType()==irr::video::EVT_TANGENTS)
            {
                irr::video::S3DVertexTangents* mb_vertices=(irr::video::S3DVertexTangents*)mb->getVertices();
                numVertices = mb->getVertexCount();

                precLoss = 1;

                while (numVertices/precLoss>250) {
                    precLoss++;
                }

                for (k=0;k<numVertices;k+=precLoss) {
                    irr::core::vector3df irrPos2 = mb_vertices[k].Pos;

                    btVector3 btPos2((irrPos2.X * scaling.X)-itemEyedrops::offset.X, (irrPos2.Y * scaling.Y)-itemEyedrops::offset.Y, (irrPos2.Z * scaling.Z)-itemEyedrops::offset.Z);
                    dynShape->addPoint(btPos2);
                }
            }
        }

        itemEyedrops::shape = dynShape;
        itemEyedrops::shape->setMargin(0.1f);
    }

    itemEyedrops* newIt = new itemEyedrops;

    newIt->irrObj = itemEyedrops::baseNode->clone();

    //Add the Bullet rigid body
    newIt->irrObj->updateAbsolutePosition();
	irr::core::vector3df irrPos = newIt->irrObj->getAbsolutePosition();
	btVector3 btPos(irrPos.X, irrPos.Y, irrPos.Z);
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(btPos);

	btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);

    btVector3 localInertia;
	itemEyedrops::shape->calculateLocalInertia(5.0, localInertia);

    newIt->rbody = new btRigidBody(5.0, MotionState, itemEyedrops::shape, localInertia);
    newIt->rbody->setSleepingThresholds(5.0f,5.0f);

    newIt->irrObj->setVisible(false);

    return newIt;
}

void itemEyedrops::Pick() {
    if (!picked) {
        //rbody->translate(-rbody->getCenterOfMassPosition()+btVector3(0,1000000.0*RoomScale,0));
        irrObj->setVisible(false);
        dynamics->sharedUnregisterRBody(rbody);
        rbody->setLinearVelocity(btVector3(0,0,0)); rbody->setAngularVelocity(btVector3(0,0,0));
        rbody->setLinearFactor(btVector3(0,0,0)); rbody->setAngularFactor(btVector3(0,0,0));
        rbody->forceActivationState(DISABLE_SIMULATION);
        picked = true;
    }
}

void itemEyedrops::Unpick(irr::core::vector3df position) {
    if (picked) {
        rbody->translate(-rbody->getCenterOfMassPosition()+btVector3(position.X,position.Y,position.Z));
        irrObj->setVisible(true);
        dynamics->sharedRegisterRBody(irrObj,rbody,-1,2,2,itemEyedrops::offset);
        rbody->setLinearVelocity(btVector3(0,0,0)); rbody->setAngularVelocity(btVector3(0,0,0));
        rbody->setLinearFactor(btVector3(1,1,1)); rbody->setAngularFactor(btVector3(1,1,1));
        rbody->forceActivationState(ACTIVE_TAG); rbody->activate();
        picked = false;
    }
}
