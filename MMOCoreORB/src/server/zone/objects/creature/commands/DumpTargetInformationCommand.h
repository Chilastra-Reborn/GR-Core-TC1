/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef DUMPTARGETINFORMATIONCOMMAND_H_
#define DUMPTARGETINFORMATIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DumpTargetInformationCommand : public QueueCommand {
public:

	DumpTargetInformationCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);

		//Apparently this command doesn't actually pass the targetid, so that probably means that it only accepts a player name
		//TODO: Reimplement this command as @getPlayerInfo
		uint64 targetID = player->getTargetID();

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(targetID);

		if (obj == NULL)
			return INVALIDTARGET;

		ManagedReference<SceneObject*> cell = obj->getParent();

		int cellid = 0;
		uint32 buildingTemplate = 0;

		if (cell != NULL && cell->isCellObject()) {
			cellid = (cast<CellObject*>(cell.get()))->getCellNumber();
			ManagedReference<SceneObject*> building = cell->getParent();
			buildingTemplate = building->getServerObjectCRC();
		}

		StringBuffer msg;

		float posX = obj->getPositionX(), posZ = obj->getPositionZ(), posY = obj->getPositionY();
		Quaternion* direction = obj->getDirection();

		msg << "x = " << posX << ", z = " << posZ << ", y = " << posY << ", ow = " << direction->getW()
				<< ", ox = " << direction->getX() << ", oz = " << direction->getZ() << ", oy = " << direction->getY()
				<< ", cellid = " << cellid;

		if (buildingTemplate != 0)
			msg << endl << TemplateManager::instance()->getTemplateFile(buildingTemplate);

		player->sendSystemMessage(msg.toString());

		ChatManager* chatManager = server->getZoneServer()->getChatManager();
		chatManager->sendMail("System", "dumpZoneInformation", msg.toString(), player->getFirstName());

		return SUCCESS;
	}

};

#endif //DUMPTARGETINFORMATIONCOMMAND_H_
