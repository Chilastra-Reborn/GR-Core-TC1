the_mos_taike_mayor = Creature:new {
	objectName = "@mob/creature_names:mos_taike_mayor",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 21,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2006,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {20,20,-1,0,0,-1,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_mayor.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 6500000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 2000000}
			},
			lootChance = 2400000
		}			
	},
	weapons = {},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(the_mos_taike_mayor, "the_mos_taike_mayor")
