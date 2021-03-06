
#ifndef PETSTORECOMMAND_H_
#define PETSTORECOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/AiAgent.h"

class PetStoreCommand : public QueueCommand {
public:
	PetStoreCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().castTo<PetControlDevice*>();
		if (controlDevice == NULL)
			return GENERALERROR;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);
		if( pet == NULL )
			return GENERALERROR;

		ManagedReference<CreatureObject*> player = pet->getLinkedCreature().get();
		if (player == NULL || !player->isPlayerCreature() ) {
			return GENERALERROR;
		}

		Locker clocker(player, pet);

		controlDevice->storeObject(player);

		return SUCCESS;
	}

};


#endif /* PETSTORECOMMAND_H_ */
